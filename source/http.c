/* 
**  Created by wplaat (www.plaatsoft.nl)
**
**  Copyright (C) 2009
**  ==================
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, version 2.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
**  History:
**   20-11-2008  Start programming
**   30-11-2008  Added google analysic http request
**   07-12-2008  Add user_var parameter in google analysic http request
**   30-12-2008  Added store highscore on internet.
**   06-01-2009  Google analysic function improved.
**   15-01-2009  Add http chunked frame support.
**   21-01-2009  Create one unique cookie during startup.
**   26-01-2009  Increase internal buffersize to 8kB.
*/

#include <stdio.h>
#include <ctype.h>
#include <gccore.h>
#include <ogcsys.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h> 
#include <malloc.h>
#include <network.h>
#include <ogc/lwp_watchdog.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h>

#include "http.h"

// -----------------------------------------------------------
// DEFINES
// -----------------------------------------------------------

#define DEBUG(X) 

#define TCP_CONNECT_TIMEOUT     5000
#define TCP_BLOCK_SIZE          (16 * 1024)
#define TCP_BLOCK_RECV_TIMEOUT  4000
#define TCP_BLOCK_SEND_TIMEOUT  4000
#define HTTP_TIMEOUT            300000
#define MAX_LEN        			256
#define NUM_THREADS             1
#define MAX_BUFFER_SIZE		    8192

// -----------------------------------------------------------
// ENUMS
// -----------------------------------------------------------

typedef enum 
{
	HTTPR_OK,
	HTTPR_ERR_CONNECT,
	HTTPR_ERR_REQUEST,
	HTTPR_ERR_STATUS,
	HTTPR_ERR_TOOBIG,
	HTTPR_ERR_RECEIVE
} 
http_res;

// -----------------------------------------------------------
// VARIABLES
// -----------------------------------------------------------

lwp_t threads[NUM_THREADS];
mutex_t mutexcheck;
mutex_t mutexversion;
bool do_tcp_treat;

char *appl_host; 
char *appl_path;

char appl_new_version[MAX_LEN];
char appl_release_notes[MAX_BUFFER_SIZE];
char appl_token[MAX_LEN];
char appl_highscore[MAX_BUFFER_SIZE];

char appl_name[MAX_LEN];
char appl_version[MAX_LEN];

char appl_id1[MAX_LEN];
char appl_url1[MAX_LEN];

char appl_id2[MAX_LEN];
char appl_url2[MAX_LEN];
char appl_userData2[MAX_LEN];

char appl_id3[MAX_LEN];
char appl_url3[MAX_LEN];
char appl_userData3[MAX_LEN];

char var_cookie[MAX_LEN];

extern GXRModeObj *rmode;
int  tcp_state;
int  tcp_state_prev;

char *http_host;
u16 http_port;
char *http_path;
u32 http_max_size;

http_res result;
u32 http_status;
u32 content_length;
u8 *http_data;

int retval;
u32 http_status;
u32 outlen;
u8  *outbuf;

// -----------------------------------------------------------
// TCP METHODES
// -----------------------------------------------------------

s32 tcp_socket(void) 
{
        //DEBUG( printf("tcp_socket:enter\n"); )
        s32 s;

        s = net_socket (AF_INET, SOCK_STREAM, IPPROTO_IP);
        if (s < 0) 
		{
			DEBUG ( printf("net_socket failed: %d\n",s); )
        }

	    //DEBUG ( printf("tcp_socket: leave [%d]\n",s); )
        return s;
}

s32 tcp_connect(char *host, const u16 port)
{
	    //DEBUG ( printf("tcp_connect:enter [host=%s|port=%d]\n",host,port); )
		
        struct hostent *hp;
        struct sockaddr_in sa;
        s32 s, res;
        s64 t;

        hp = net_gethostbyname(host);
        if (!hp || !(hp->h_addrtype == PF_INET)) 
		{            
			DEBUG ( printf("net_gethostbyname failed: %d\n",errno); )
            return errno;
        }

        s = tcp_socket();
        if (s < 0)
		{
		   DEBUG ( printf("Error creating socket, exiting"); )
           return s;
	    }

        memset (&sa, 0, sizeof (struct sockaddr_in));
        //sa.sin_family= PF_INET;
		sa.sin_family= AF_INET;
        sa.sin_len = sizeof (struct sockaddr_in);
        sa.sin_port= htons(port);
        memcpy ((char *) &sa.sin_addr, hp->h_addr_list[0], hp->h_length);

        DEBUG ( printf("DNS resolve=%d.%d.%d.%d\n", (unsigned char) hp->h_addr_list[0][0], (unsigned char) hp->h_addr_list[0][1], (unsigned char) hp->h_addr_list[0][2], (unsigned char)  hp->h_addr_list[0][3]); )

        t = gettime();
        while (true) 
		{
                if (ticks_to_millisecs (diff_ticks (t, gettime ())) > TCP_CONNECT_TIMEOUT) 
				{
					DEBUG ( printf("tcp_connect timeout\n"); )
                    net_close (s);
                    return -ETIMEDOUT;
                }

                res = net_connect (s, (struct sockaddr *) &sa, sizeof (struct sockaddr_in));

                if (res < 0) 
				{
                   if (res == -EISCONN)  break;

                   if (res == -EINPROGRESS || res == -EALREADY) 
				   {
                       usleep (20 * 1000);
                       continue;
                   }

   				   DEBUG ( printf("net_connect failed: %d\n",res); )
                   net_close(s);
                   return res;
                }
                break;
        }
		//DEBUG ( printf("tcp_connect:leave\n"); )
        return s;
}

char * tcp_readln(const s32 s, const u16 max_length, const u64 start_time, const u16 timeout) 
{		
        char *buf;
        u16 c;
        s32 res;
        char *ret;

        buf = (char *) malloc (max_length);

        c = 0;
        ret = NULL;
        while (true) 
		{
                if (ticks_to_millisecs (diff_ticks (start_time, gettime ())) > timeout)
                        break;

                res = net_read (s, &buf[c], 1);

                if ((res == 0) || (res == -EAGAIN)) 
				{
                        usleep (20 * 1000);
                        continue;
                }

                if (res < 0) 
				{                       
						DEBUG ( printf("tcp_readln failed: %d\n", res); )
                        break;
                }

                if ((c > 0) && (buf[c - 1] == '\r') && (buf[c] == '\n')) 
				{
                        if (c == 1) 
						{
                                ret = strdup ("");
                                break;
                        }
                        ret = strndup (buf, c - 1);
                        break;
                }
                c++;
                if (c == max_length) break;
        }
        free (buf);
		return ret;
}

bool tcp_read(const s32 s, u8 **buffer, const u32 length) 
{
	    //DEBUG ( printf("tcp_read:enter\n"); )
		
        u8 *p;
        u32 step, left, block, received;
        s64 t;
        s32 res;

        step = 0;
        p = *buffer;
        left = length;
        received = 0;

        t = gettime ();
        while (left) 
		{
                if (ticks_to_millisecs (diff_ticks (t, gettime ())) > TCP_BLOCK_RECV_TIMEOUT)
			    {
				   DEBUG ( printf("tcp_read timeout\n"); )
                   break;
                }

                block = left;
                if (block > 2048) block = 2048;
				
                res = net_read (s, p, block);
                if ((res == 0) || (res == -EAGAIN)) 
				{
                    usleep (20 * 1000);
                    continue;
                }

                if (res < 0) 
				{
					DEBUG ( printf("net_read failed %d\n", res); )
                    break;
                }

                received += res;
                left -= res;
                p += res;

                if ((received / TCP_BLOCK_SIZE) > step) 
				{
                    t = gettime ();
                    step++;
                }
        }

		//DEBUG ( printf("tcp_read:leave\n"); )
        return left == 0;
}

bool tcp_write(const s32 s, const u8 *buffer, const u32 length)
{
	    //DEBUG ( printf("tcp_write: enter\n"); )
		
        const u8 *p;
        u32 step, left, block, sent;
        s64 t;
        s32 res;

        step = 0;
        p = buffer;
        left = length;
        sent = 0;

        t = gettime ();
        while (left) 
		{
                if (ticks_to_millisecs (diff_ticks (t, gettime ())) > TCP_BLOCK_SEND_TIMEOUT) 
				{
 					DEBUG ( printf("tcp_write: timeout\n"); )
                    break;
                }

                block = left;
                if (block > 2048) block = 2048;

                res = net_write (s, p, block);
                if ((res == 0) || (res == -56))
				{
                    usleep (20 * 1000);
                    continue;
                }

                if (res < 0) 
				{
					DEBUG ( printf("tcp_write: failed:%d\n",res); )
                    break;
                }
                sent += res;
                left -= res;
                p += res;

                if ((sent / TCP_BLOCK_SIZE) > step)
				{
                    t = gettime ();
                    step++;
                }
        }
        return left == 0;
		//DEBUG ( printf("tcp_write: leave\n"); )
}


int tcp_init(void) 
{    
    //DEBUG ( printf("tcp_init: enter\n"); )
	 	
    DEBUG ( printf("Waiting for network to initialise...\n"); )
			
	s32 result;
    while ((result = net_init()) == -EAGAIN);
	
    if ( result>= 0) 
    {
        char myIP[16];
        if (if_config(myIP, NULL, NULL, true) < 0) 
        {
            DEBUG ( printf("Error reading IP address, exiting"); )
			return 1;
        }
        DEBUG ( printf("Network initialised [%s].\n",myIP); )
    } 
    else 
    {
      DEBUG ( printf("Unable to initialise network, exiting"); )
	  return 1;
    }
	
	//DEBUG ( printf("tcp_init: leave\n"); )
	return 0;
}


void tcp_sleep(unsigned int seconds)
{
   //DEBUG ( printf("mssleep:enter\n"); )
   //DEBUG ( printf("sleep %d sec.\n",seconds); )
   sleep(seconds);
   //DEBUG ( printf("mssleep:leave\n"); )
}

// -----------------------------------------------------------
// HTTP METHODES
// -----------------------------------------------------------

bool http_split_url(char **host, char **path, const char *url)
{
		//DEBUG ( printf("http_split_url: enter\n"); )
		
        const char *p;
        char *c;

        if (strncasecmp (url, "http://", 7))
		{
		   DEBUG ( printf("http_split_url: leave [false]\n"); )
           return false;
		}

        p = url + 7;
        c = strchr (p, '/');

        if (c[0] == 0)
		{
		    DEBUG ( printf("http_split_url: leave [false]\n"); )
		    return false;
	    }

        *host = strndup (p, c - p);
        *path = strdup (c);

		//DEBUG ( printf("http_split_url: leave [true]\n"); )		
        return true;
}


char *http_replaceString(char *orgstr, char *oldstr, char *newstr)
{
  int oldlen, newlen;
  char *s, *p;
  s = orgstr;
  while (s != NULL)
  {
    p = strstr(s, oldstr);
    if (p == NULL ) return orgstr;
    oldlen = strlen(oldstr);
    newlen = strlen(newstr);
    orgstr = (char*)realloc(orgstr, strlen(orgstr)-oldlen+newlen+1);
    if (orgstr == NULL) return NULL;
    memmove(p + newlen, p + oldlen, strlen(p + oldlen) + 1);
    memcpy(p, newstr, newlen);
    s = p + newlen;
  }
  return orgstr;
}

// This function remove all html tag and return and ascii line buffer
bool http_convertHTMlToAscii(char *in, int inSize)
{  
   DEBUG ( printf("http_convertHTMlToAscii: enter\n"); )
   
   int i;
   int startpos=0;
   int size=0;
   bool tag=true;

   // replace some html tags 
   in = http_replaceString(in,"\r","");
   in = http_replaceString(in,"\n","");
   in = http_replaceString(in,"</title>","\n");
   in = http_replaceString(in,"<h1>","\n");
   in = http_replaceString(in,"<h2>","\n");
   in = http_replaceString(in,"<h3>","\n");
   in = http_replaceString(in,"</h1>","\n\n");
   in = http_replaceString(in,"</h2>","\n");
   in = http_replaceString(in,"</h3>","\n");
   in = http_replaceString(in,"</br>","\n");
   in = http_replaceString(in,"<br/>","\n");
   
   // remove all html tags
   for (i=0; i<inSize; i++)
   {
      if (in[i]=='<')
	  {	     
	  	 if (!tag)
		 {		    
		   int len=i-startpos;	
		   if (len>4) 
			{  
               if (size+len<MAX_BUFFER_SIZE)
			   {
			      strncat(appl_release_notes+size, (char *) in+startpos, len);	
			      size+=len;
			   }
			}				            
	     }
         tag=true;	
	  }
	  
	  if (in[i]=='>')
	  {	    
		 tag=false;	
		 startpos=i+1;	
	  }
   }   
   						
   DEBUG ( printf("http_convertHTMlToAscii: leave [%d]\n",strlen(appl_release_notes)); )
   return true;
}

char http_bin2hex(int val)
{
    int i;
	
    i = val & 0x0F;
    if (i >= 0 && i < 10)
        return '0' + i;
    else
        return 'A' + (i - 10);
}
 	
char *http_encode_url(char *buf, const char *str)
{
    //DEBUG ( printf("http_encode_url [%s]:enter\n", str); )

    int i, j;
    int len;
    unsigned char c;
	int buflen=MAX_LEN;
    len = strlen(str); 
   
    for (i = 0, j = 0; i < len && j < (buflen - 1); i++) 
	{
        c = (unsigned char) str[i];
        		
		if ((c!='.') && (!isalnum(c)))
		{
            buf[j++] = '%';
            if (j < (buflen - 1))
                buf[j++] = http_bin2hex((c >> 4) & 0x0F);
            if (j < (buflen - 1))
                buf[j++] = http_bin2hex(c & 0x0F);
        } 
		else 
		{
          buf[j] = str[i];
          j++;
        }
    }
    buf[j] = '\0';
	
	//DEBUG ( printf("http_encode_url [%s]:leave\n",buf); )
	
    return buf;
}
		
// Google Analytic without JavaScript
void http_googleAnalysicUrl(char *buffer, char *domain, char *url, char *id)
{
    DEBUG ( printf("http_googleAnalysicUrl:enter\n"); )

	DEBUG ( printf("domain=%s\n", domain); )
	DEBUG ( printf("url=%s\n", url); )
	DEBUG ( printf("id=%s\n", id); )
		
    char utmhn[MAX_LEN];
    char utmac[MAX_LEN];
    char utmcs[MAX_LEN];
    char utmsr[MAX_LEN];
    char utmsc[MAX_LEN];
    char utmn[MAX_LEN];
    char utmp[MAX_LEN];
    char utmr[MAX_LEN];
    char utmdt[MAX_LEN];
    
    char var_random[MAX_LEN];
    char var_prev_day[MAX_LEN];
    char var_today[MAX_LEN];
    char var_next_day[MAX_LEN];
    char var_uservar[MAX_LEN];
	char tmp1[300];
    char tmp2[300];

    memset( utmhn,0x00,sizeof(utmhn));
    memset( utmac,0x00,sizeof(utmac));
    memset( utmcs,0x00,sizeof(utmcs));
    memset( utmsr,0x00,sizeof(utmsr));
    memset( utmsc,0x00,sizeof(utmsc));
    memset( utmn,0x00,sizeof(utmn));
    memset( utmp,0x00,sizeof(utmp));
    memset( utmr,0x00,sizeof(utmr));
    memset( utmdt,0x00,sizeof(utmdt));
   
    memset( var_random,0x00,sizeof(var_random));
    memset( var_prev_day,0x00,sizeof(var_prev_day));
    memset( var_today,0x00,sizeof(var_today));
    memset( var_next_day,0x00,sizeof(var_next_day));
    memset( var_uservar,0x00,sizeof(var_uservar));
	memset( tmp1,0x00,sizeof(tmp1));
    memset( tmp2,0x00,sizeof(tmp2));
	
	 /* URL EXAMPLE 
 
    ?utmwv=1 				// Analytics version
    &utmn=634440486         // Random transaction number
	&utmcs=URF-8    		//document encoding
	&utmsr=1440x900 		//screen resolution
	&utmsc=32-bit 			//color depth
	&utmul=nl 				//user language
	&utmje=1 				//java enabled
	&utmfl=9.0%20%20r28 	//flash version
	&utmcr=1 				//carriage return
	&utmdt=Linklove » The optimum keyword density //document title
	&utmhn=www.vdgraaf.info //document hostname
	&utmr=http://www.google.nl/search?q=seo+optimal+keyword+density&sourceid=navclient-ff&ie=UTF-8&rlz=1B3GGGL_nlNL210NL211 //referer URL
	&utmp=/the-optimum-keyword-density.html //document page URL
	&utmac=UA-320536-6 		// Google Analytics account
	&utmcc= 				// cookie settings
	__utma=
					21661308. //cookie number
					1850772708. //number under 2147483647
					1169320752. //time (20-01-2007) cookie first set
					1172328503. //time (24-02-2007) cookie previous set
					1172935717. //time (03-03-2007) today
					3;+
	__utmb=
					21661308;+ //cookie number
	__utmc=
					21661308;+ //cookie number
	__utmz=
					21661308. //cookie number
					1172936273. //time (03-03-2007) today
					3.
					2.
		utmccn=(organic)| //utm_campaign
		utmcsr=google| //utm_source
		utmctr=seo+optimal+keyword+density| //utm_term
		utmcmd=organic;+ //utm_medium*/	
				
	// Your Domain
	http_encode_url(utmhn, domain);  
		
	// Referer url	
	sprintf(tmp1,"http://www.google.com/search?q=%s+Wii",appl_name); 
	http_encode_url(utmr, tmp1 );
	
	// Document page URL
    http_encode_url(utmp, url );
				
    // screen size
    sprintf(tmp1,"%dx%d", rmode->fbWidth, rmode->xfbHeight ); 	
    strcpy(utmsr, tmp1 );
	
	// color depth
    strcpy(utmsc, "32-bit" );
	
	// user language
	char *utmul = "en";											 
	
	// support for java
	char *utmje = "1";
				
    // flash version							 
	char *utmfl = "";			

    time_t  today =time(NULL);
	long base = (long) today;
				
	// random number under 2147483647
	long c = base + 100000000; 		
    sprintf(var_random, "%ld",c);
	
	// random request number (1000000000,9999999999);
	long d = base + 500000000; 		
    sprintf(utmn, "%ld",d);
	
    // page title				
    sprintf(tmp1,"WiiBrew %s %s",appl_name, appl_version); 				
    http_encode_url(utmdt, tmp1 );								
			
	// Google Analytics account	
	strcpy(utmac, id );

	//DEBUG ( printf("utmac=%s\n", utmac); )
		   
	sprintf(tmp1, "utmwv=1&utmn=%s&utmcs=UTF-8&utmsr=%s&utmsc=%s&utmul=%s&utmje=%s&utmfl=%s&utmcr=1&utmdt=%s&utmhn=%s&utmr=%s&utmp=%s&utmac=%s",
		utmn, 
		utmsr, 
		utmsc, 
		utmul, 
		utmje, 
		utmfl, 
		utmdt,
        utmhn, 
		utmr, 
		utmp,
		utmac );
			
	// Timestamps					
	sprintf(var_prev_day, "%ld", base - (60*60*24) );				
	sprintf(var_today, "%ld", base);		
	sprintf(var_next_day, "%ld", base + (60*60*24) );
		
	// User defined				
    http_encode_url(var_uservar, appl_userData2 );	
	
    sprintf(tmp2, "&utmcc=__utma=%s.%s.%s.%s.%s.3%%3B%%2B__utmb=%s%%3B%%2B__utmc=%s%%3B%%2B__utmz=%s.%s.3.2.utmccn=(direct)%%3Dutmcsr=(direct)%%3Dutmctr=(none)%%3Dutmcmd=(none)%%3B%%2B__utmv%%3D%s.%s%%3B",
	    var_cookie,
		var_random,
		var_prev_day,
		var_next_day,
		var_today,
		var_cookie,
		var_cookie,
		var_cookie,
		var_today,
		var_cookie,
		var_uservar);
				
    sprintf(buffer,"http://www.google-analytics.com/__utm.gif?%s%s", tmp1, tmp2 );
	
	//DEBUG ( printf("http_googleAnalysicUrl:leave\n"); )
}

// Google Analytic without JavaScript (php example)
/*header("Content-type:image/gif");
$var_utmac=$_REQUEST['t']?$_REQUEST['t']:'UA-5199105-1'; //enter the new urchin code
$var_utmhn=$_REQUEST['d']?$_REQUEST['d']:'wap.metamobile.com.my'; //enter your domain
$var_utmn=rand(  1000000000,9999999999);//random request number
$var_cookie=rand(10000000,99999999);//random cookie number
$var_random=rand(1000000000,2147483647); //number under 2147483647
$var_today=time(); //today
$var_referer=$_SERVER['HTTP_REFERER']; //referer url

$var_uservar='-'; //enter your own user defined variable
$var_utmp='/rss/'.$_SERVER['REMOTE_ADDR']; //this example adds a fake page request to the (fake) rss directory (the viewer IP to check for absolute unique RSS readers)
$urchinUrl='http://www.google-analytics.com/__utm.gif?utmwv=1&utmn='.$var_utmn.'&utmsr=-&utmsc=-&utmul=-&utmje=0&utmfl=-&utmdt=-&utmhn='.$var_utmhn.'&utmr='.$var_referer.'&utmp='.$var_utmp.'&utmac='.$var_utmac.'&utmcc=__utma%3D'
.$var_cookie.'.'.$var_random.'.'.$var_today.'.'.$var_today.'.'.$var_today.'.2%3B%2B__utmb%3D'.$var_cookie.'%3B%2B__utmc%3D'.$var_cookie.'%3B%2B__utmz%3D'.$var_cookie.'.'.$var_today.'.2.2.utmccn%3D(direct)%7Cutmcsr%3D(direct)
                                                                                                                                            %7Cutmcmd%3D(none)%3B%2B__utmv%3D'.$var_cookie.'.'.$var_uservar.'%3B';

$urchinUrl='http://www.google-analytics.com/__utm.gif';
 
echo Curl_to_GA($urchinUrl); 

function Curl_to_GA($target,$post_vars=''){
    while (list($k,$v) = each($_SERVER)) {
        if (strstr ($k,"HTTP_") && $k != 'HTTP_HOST')    
            $reqHeaders[] = str_replace(" ","-",ucwords(strtolower(str_replace("_"," ",str_replace("HTTP_","",$k))))) . ": " . $v;
    }
	$ch = curl_init(); //var_dump($reqHeaders);
	curl_setopt($ch, CURLOPT_URL, $target);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
	if (count($reqHeaders) > 0) {
		curl_setopt($ch, CURLOPT_HTTPHEADER, $reqHeaders);
	} 	if ($post_vars != '') { 
		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS, $post_vars);
	}
	$response = curl_exec($ch);
	curl_close($ch);
    return $response;
}*/

extern bool http_request(char *url, const u32 max_size)
{
	    //DEBUG ( printf("http_request: enter\n"); )
 		
        int linecount;
		boolean chunked=false;
		int emptycount=0;
		
        if (!http_split_url(&http_host, &http_path, url)) return false;

        http_port = 80;
        http_max_size = max_size;
       
        http_status = 404;
        content_length = 0;
        http_data = NULL;

        int s = tcp_connect(http_host, http_port);

		DEBUG ( printf("tcp_connect(%s, %hu) = %d\n",http_host, http_port, s); )
        if (s < 0) 
		{
            result = HTTPR_ERR_CONNECT;
            return false;
        }

        char *request = (char *) malloc(2048);
        char *r = request;
        r += sprintf (r,"GET %s HTTP/1.1\r\n", http_path); 
        r += sprintf (r,"Host: %s\r\n", http_host);
		r += sprintf (r,"User-Agent: %s/%s (compatible; v3.X; Nintendo Wii)\r\n", appl_name, appl_version);  
        r += sprintf (r,"Accept: text/xml,text/html,text/plain,image/gif\r\n");
        r += sprintf (r,"Cache-Control: no-cache\r\n\r\n");

        DEBUG ( printf("request = %s", request); )

        bool b = tcp_write (s, (u8 *) request, strlen (request));

        free (request);
        linecount = 0;

        for (linecount=0; linecount < 32; linecount++) 
		{
            char *line = tcp_readln ((s32) s, (u16) 0xff, (u64) gettime(), (u16) HTTP_TIMEOUT);
		    DEBUG ( printf("tcp_readln: %s\n", line ? line:"(null)"); )
          
            if (!line) 
			{
                http_status = 404;
                result = HTTPR_ERR_REQUEST;
                break;
            }

            if (chunked && (emptycount==1))
			{			   
			   sscanf (line, "%x", &content_length);	
			   
			   // Protect against crash frame
			   if (content_length>5000) content_length=0;
			   
			   free (line);
               line = NULL;			 
               break;		
			}
			
            if (strlen(line)<1) 
			{
			    if (chunked) 
				{
				    if (++emptycount>1) 
					{
					  free (line);
					  line = NULL;
                      break;
					}
					//DEBUG ( printf("Empty line\n"); )
				}	
                else
                {				
                  free (line);
                  line = NULL;
                  break;
			    }
            }

            sscanf (line, "HTTP/1.%*u %u", &http_status);
            sscanf (line, "Content-Length: %u", &content_length);
			if ( strstr(line, "Transfer-Encoding: chunked")!=0 )
			{
				//DEBUG ( printf("Chunked frame found\n"); )
				free (line);
				line = NULL;
				chunked=true;
            }
						
            free (line);
            line = NULL;
        }
        
		DEBUG ( printf("content_length = %d, status = %d, linecount = %d\n", content_length, http_status, linecount); )

        if (http_status != 200) 
		{
            result = HTTPR_ERR_STATUS;
            net_close (s);
            return false;
        }
      	
	    if (linecount == 32 || !content_length) http_status = 404;
				
        if (content_length > http_max_size) 
		{
           result = HTTPR_ERR_TOOBIG;
           net_close (s);
           return false;
        }
        http_data = (u8 *) malloc (content_length);
        b = tcp_read (s, &http_data, content_length);
        if (!b) 
		{
           free (http_data);
           http_data = NULL;
           result = HTTPR_ERR_RECEIVE;
           net_close (s);
           return false;
        }
        		
        result = HTTPR_OK;
        net_close(s);

		//DEBUG ( printf("http_request: leave\n"); )
        return true;
}

extern bool http_get_result(u32 *_http_status, u8 **content, u32 *length) 
{
		//DEBUG ( printf("http_get_result: enter\n"); )
		
        if (http_status) *_http_status = http_status;

        if (result == HTTPR_OK) 
		{
           *content = http_data;
           *length = content_length;
        } 
		else 
		{
           *content = NULL;
           *length = 0;
        }

        free (http_host);
        free (http_path);

		//DEBUG ( printf("http_get_result: leave\n"); )
        return true;
}

char * http_findToken(u8 *buffer, int bufsize, char *token)
{
   //DEBUG ( printf("http_findToken:enter [%s]\n",token); )
   
   int i, j=0;
   int startpos=-1;
   int endpos;
   int len=strlen(token);
   bool found=false;
   
   // find token begin
   startpos=-1;
   j=0;
   
   //DEBUG ( printf("len=%d\n",len); )
	
   for (i=0; i<bufsize; i++)
   {
      if (buffer[i]==token[j])
	  {	     
	     if (startpos==-1) startpos=i;	
		 if (++j>=len) 
		 {  
		    //DEBUG ( printf("startpos=%d\n",startpos); )
		    found=true;
			break;
	     }
	  }
	  else
	  {
	     // No token match, continue...
	     if (startpos!=-1)
		 {
		    j=0;
			startpos=-1;
	     }
	  }
   }
   
   if (found) 
   {
       startpos+=len;
	  
       // find end of token value   
       for (i=startpos; i<bufsize; i++)
       {	      
         if ((buffer[i]=='\n') || (buffer[i]=='\r') || (buffer[i]==' '))
	     {  	     
		    endpos=i;
			//DEBUG ( printf("endpos=%d\n",endpos); )
			
			// (small hack) End string
			buffer[endpos]=0x00;
			
			DEBUG ( printf("http_findToken:leave [%s]\n", buffer+startpos); )
			return (char*) buffer+startpos;
	     }
	  }
   }   
   //DEBUG ( printf("http_findToken:leave [NULL]\n"); )
   return NULL;
}


// -----------------------------------------------------------
// THREAD STUFF
// -----------------------------------------------------------
	
 void *tcp_thread(void *threadid)
{
   DEBUG ( printf("tcp_thread:enter\n"); )

   int retval;
   u32 http_status;
   u8  *outbuf;
   u32 outlen;
  
   //int tid = (int)threadid;

   LWP_MutexLock (mutexcheck);
   while(do_tcp_treat)
   {
      LWP_MutexUnlock(mutexcheck);
	  
	  switch (tcp_state)
	  {
	    // Init ethernet DHCP network
	    case TCP_INIT:   
		{
		  DEBUG ( printf("\n\nstateMachine=TCP_INIT\n"); )
		  retval=tcp_init();
		  if (retval==0) 
		  { 
		     tcp_state=TCP_REQUEST1a; 
		  }
		  else 
		  {
		     tcp_state=TCP_ERROR;
		  }
		}
		break;
		
		// Error ocure during network init, retry after 60 seconds.				  
		case TCP_ERROR:
		{
		    DEBUG ( printf("\n\nstateMachine=TCP_ERROR\n"); )
	        tcp_sleep(60);
		    tcp_state=TCP_INIT;
	    }
		break;
		
        // Check for new application version					 
		case TCP_REQUEST1a: 
		{		
		  DEBUG ( printf("\n\nstateMachine=TCP_REQUEST1a\n"); )
          retval = http_request(appl_url1, 1 << 31);
          if (!retval) 
          {
		     tcp_state_prev=tcp_state;
		     tcp_state=TCP_RETRY;
	         DEBUG ( printf("Error making http request1a\n"); )
          }
          else
          {     
	         char *tmp;	
	         http_get_result(&http_status, &outbuf, &outlen);   	 			
			 tmp=http_findToken(outbuf, outlen, appl_token);		 
			 
			 LWP_MutexLock(mutexversion);
			 if (tmp!=NULL) 
			 {
			     strncpy(appl_new_version, tmp, sizeof(tmp));	 	 
				 DEBUG ( printf("version: %s\n",appl_new_version); )
		     }
			 else
			 {
			     DEBUG ( printf("version: <none>\n");  )
			 }
			 LWP_MutexUnlock(mutexversion);
			 
	         free(outbuf);			 
			 tcp_state=TCP_REQUEST1b;
          } 	 
          DEBUG( tcp_sleep(10) );	 		  
		} 	
        break;	 
		
		// Update Google Statistics
		case TCP_REQUEST1b: 
		{	
		  DEBUG ( printf("\n\nstateMachine=TCP_REQUEST1b\n"); )
				  
		  char buffer[512];
		  memset(buffer,0x00,sizeof(buffer));
		
          char url1[MAX_LEN];
          memset(url1,0x00,sizeof(url1));
          sprintf(url1,"/start/%s/%s",appl_name,appl_version);		    
			
		  if (!http_split_url(&appl_host, &appl_path, appl_url1)) return false;
			
		  http_googleAnalysicUrl(buffer,appl_host,url1,appl_id1);
          retval = http_request(buffer, 1 << 31);
          if (!retval) 
          {
		     tcp_state_prev=tcp_state;
		     tcp_state=TCP_RETRY;
	         DEBUG ( printf("Error making http request1b\n"); )			 
          }
          else
          {     		    
	         http_get_result(&http_status, &outbuf, &outlen);   	
			 DEBUG ( int i; for (i=0; i<outlen; i++) printf("%c", outbuf[i] ); printf("\n\n\n"); ) 			
			 free(outbuf);
			 tcp_state=TCP_REQUEST2a;
          } 	
		  free (appl_host);
          free (appl_path);	 
		  
          DEBUG( tcp_sleep(10); )
	    }
		break;
				
		// Get Release note information
		case TCP_REQUEST2a: 
		{		  
		  DEBUG ( printf("\n\nstateMachine=TCP_REQUEST2a\n"); )
          retval = http_request(appl_url2, 1 << 31);
          if (!retval) 
          {
		  	 tcp_state_prev=tcp_state;
		     tcp_state=TCP_RETRY;
	         DEBUG ( printf("Error making http request2a\n"); )			 
          }
          else
          {     		    
			 http_get_result(&http_status, &outbuf, &outlen);   			 
			 http_convertHTMlToAscii((char *) outbuf, outlen);  	          
			 
			 // Terminated received data
			 char* result=strstr(appl_release_notes,"Other:");
			 if (result!=NULL) result[0]=0x00;
			 			
			 DEBUG ( int i;  for (i=0; i<strlen(appl_release_notes); i++) printf("%c", appl_release_notes[i] ); )
	
			 free(outbuf);			 
			 tcp_state=TCP_REQUEST2b;			
          } 	
          DEBUG( tcp_sleep(10) );	  
		} 	
        break;	 
		
		// Update Google Statistics
		case TCP_REQUEST2b: 
		{		
		  char buffer[512];
		  memset(buffer,0x00,sizeof(buffer));
		  
		  DEBUG ( printf("\n\nstateMachine=TCP_REQUEST2b\n"); )
		 	  
		  if (!http_split_url(&appl_host, &appl_path, appl_url2)) return false;
			  		  		  		    
		  http_googleAnalysicUrl(buffer, appl_host, appl_path, appl_id2);
          retval = http_request(buffer, 1 << 31);
          if (!retval) 
          {
		  	 tcp_state_prev=tcp_state;
		     tcp_state=TCP_RETRY;
	         DEBUG ( printf("Error making http request2b\n"); )			 
          }
          else
          {     		    
	         http_get_result(&http_status, &outbuf, &outlen);   	
			 DEBUG ( int i; for (i=0; i<outlen; i++) printf("%c", outbuf[i] ); printf("\n\n\n"); ) 			
			 free(outbuf);
			 tcp_state=TCP_REQUEST3a;
          } 
		  free (appl_host);
          free (appl_path);	 
		  DEBUG( tcp_sleep(10) );	 
		} 	
        break;	 
						
		// Get best high score from all players in the world.
		case TCP_REQUEST3a: 
		{
		  DEBUG ( printf("\n\nstateMachine=TCP_REQUEST3a\n"); )
		  
		  int i;
		  int key=0;
		  for (i=0; i<strlen(appl_url3);i++) key+=appl_url3[i];
		  key%=314159265;
          char url[MAX_LEN];
		  		  
		  memset(url,0x00,sizeof(url));		  
		  sprintf(url, "%s?%s&key=%d",appl_url3, appl_userData3, key);		  
          retval = http_request(url, 1 << 31);
          if (!retval) 
          {
		  	 tcp_state_prev=tcp_state;
		     tcp_state=TCP_RETRY;
	         DEBUG ( printf("Error making http request3a\n"); )			 
          }
          else
          {  
		     http_get_result(&http_status, &outbuf, &outlen);   	
 
			 int i;   		   					 
			 memset(appl_highscore,0x00,sizeof(appl_highscore));
  		     for (i=0; i<outlen; i++) appl_highscore[i]=outbuf[i];	

			 
		     char* result=strstr(appl_highscore,"</highscore>");
			 if (result!=NULL) 
			 {
			    // Terminated received xml data 
			    result[13]=0x00; 
    			DEBUG ( for (i=0; i<strlen(appl_highscore); i++) printf("%c", appl_highscore[i] ); )       
				   
				tcp_state=TCP_REQUEST3b;
			 }
			 else
			 {
			    // Something is wrong with the response
				DEBUG( printf("Received xml data is corrupt\n" ); )
				
				// Clear received trash
				memset(appl_highscore,0x00,sizeof(appl_highscore));
				
				// Try again.
				tcp_state_prev=tcp_state;
		        tcp_state=TCP_RETRY;  
			 }
			 free(outbuf);			 			
          } 	 
		  DEBUG( tcp_sleep(10) );	 
		} 	
        break;	 
				
		// Update Google Statistics
		case TCP_REQUEST3b: 
		{		
		  char buffer[512];
		  memset(buffer,0x00,sizeof(buffer));
		  
		  DEBUG ( printf("\n\nstateMachine=TCP_REQUEST3b\n"); )
		 		  
		  if (!http_split_url(&appl_host, &appl_path, appl_url3)) return false;
		  		  
		  http_googleAnalysicUrl(buffer, appl_host, appl_path, appl_id3);
          retval = http_request(buffer, 1 << 31);
          if (!retval) 
          {
		  	 tcp_state_prev=tcp_state;
		     tcp_state=TCP_RETRY;
	         DEBUG ( printf("Error making http request3b\n"); )			 
          }
          else
          {     		    
	         http_get_result(&http_status, &outbuf, &outlen);   	
			 DEBUG ( int i; for (i=0; i<outlen; i++) printf("%c", outbuf[i] ); printf("\n\n\n"); ) 			
			 free(outbuf);
			 tcp_state=TCP_IDLE;
          } 	
		  free (appl_host);
          free (appl_path); 
		  DEBUG( tcp_sleep(10) );	 
		} 	
        break;	 
		
		// Error ocure during http request, retry after 120 seconds.
		case TCP_RETRY:
		{
		    DEBUG ( printf("\nstateMachine=TCP_RETRY" ); )
	        tcp_sleep(10);
		    tcp_state=tcp_state_prev;
	    }
		break;
				
        // Do nothing, wait for new order.
		case TCP_IDLE:
		{
		    //DEBUG ( printf("\nstateMachine=TCP_IDLE" ); )
	        tcp_sleep(2);	
	    }
		break;
	
		// Thread is ready, shut it down.
		case TCP_END:
		{
		   DEBUG ( printf("\n\nstateMachine=TCP_END"); )
           do_tcp_treat=false;
		}		
        break;			
      }	  
      LWP_MutexLock(mutexcheck);
   }
   LWP_MutexUnlock(mutexcheck);
   //LWP_SuspendThread(tid);
   
   DEBUG ( printf("tcp_thread:leave [0]\n"); )
   return 0;
}

void tcp_clear_memory(void)
{
	memset( appl_release_notes,0x00,sizeof(appl_release_notes));
	memset( appl_highscore,0x00,sizeof(appl_highscore));
}
	
// -----------------------------------------------------------
// INTERFACE API
// -----------------------------------------------------------

extern int tcp_get_state_nr(void)
{
   return tcp_state;
}

extern char *tcp_get_state(void)
{
   switch (tcp_state)
   {
     case TCP_INIT: 
	        return "INIT";
            break;
					
	 case TCP_REQUEST1a:
	        return "REQUEST_1A";
            break;
	 
	 case TCP_REQUEST1b:
	        return "REQUEST_1B";
            break;
	 
	 case TCP_REQUEST2a:
	        return "REQUEST_2A";
            break;
	 
	 case TCP_REQUEST2b:
	        return "REQUEST_2B";
            break;	 
			
	 case TCP_REQUEST3a:
	 	    return "REQUEST_3A";
            break;
			
	 case TCP_REQUEST3b:
	        return "REQUEST_3B";
            break;
	 
	 case TCP_ERROR:
	        return "ERROR";
            break;
	 
	 case TCP_RETRY:
	        return "RETRY";
            break;
	 
	 case TCP_IDLE:
	        return "IDLE";
            break;
	 
	 case TCP_END:
	        return "END";
            break;
	 
	 default: return "UNKNOWN";
	          break;
   }
}

extern int tcp_set_state(int state, char *userData3)
{
   LWP_MutexLock(mutexversion);
   if (tcp_state==TCP_IDLE)
   {
      strcpy(appl_userData3, userData3);
      tcp_state=state;
   }
   LWP_MutexUnlock(mutexversion);
   return state;
}

extern char *tcp_get_version(void)
{
   LWP_MutexLock(mutexversion);
   return appl_new_version;
   LWP_MutexUnlock(mutexversion);
}

extern char *tcp_get_releasenote(void)
{
   LWP_MutexLock(mutexversion);  
   return appl_release_notes;
   LWP_MutexUnlock(mutexversion);
}

extern char *tcp_get_highscore(void)
{
   LWP_MutexLock(mutexversion);  
   return appl_highscore;
   LWP_MutexUnlock(mutexversion);
}

extern int tcp_start_thread(char *name, char *version, char *id1, char *url1, char*id2, char *url2, char *id3, char *url3, char *token, char *userData2, char *userData3)
{
    //DEBUG ( printf("tcp_start_thread:enter [%s]\n", url); )

    tcp_state=TCP_INIT;
    do_tcp_treat = true;

    tcp_clear_memory();

    memset(appl_new_version,0x00,sizeof(appl_new_version));
	memset(appl_name,0x00,sizeof(appl_name));
	memset(appl_version,0x00,sizeof(appl_version));
	
	memset(appl_id1,0x00,sizeof(appl_id1));
	memset(appl_url1,0x00,sizeof(appl_url1));
	
	memset(appl_id2,0x00,sizeof(appl_id2));
	memset(appl_url2,0x00,sizeof(appl_url2));
	memset(appl_userData2,0x00,sizeof(appl_userData2));
	
	memset(appl_id3,0x00,sizeof(appl_id3));	
	memset(appl_url3,0x00,sizeof(appl_url3));
	memset(appl_userData3,0x00,sizeof(appl_userData3));
	
	memset(appl_token,0x00,sizeof(appl_token));	
	memset(var_cookie,0x00,sizeof(var_cookie));
	 
	strcpy(appl_name, name);
	strcpy(appl_version, version);
	
	strcpy(appl_id1, id1);
	strcpy(appl_url1, url1);
	
	strcpy(appl_id2, id2);
	strcpy(appl_url2, url2);
	strcpy(appl_userData2, userData2);
	
	strcpy(appl_id3, id3);
	strcpy(appl_url3, url3);
	strcpy(appl_userData3, userData3);
	
	strcpy(appl_token, token);
	
	// Create cookie 
	time_t today =time(NULL);
	long base = (long) today;		
	long b = base - 1200009099; 			
    sprintf(var_cookie, "%ld",b);
	
	int rc = LWP_CreateThread(&threads[0], tcp_thread, NULL, NULL, 0, 1);
    if(rc!=0) 
	{
        DEBUG ( printf("ERROR; return code from LWP_CreateThread is %d\n", rc); )
    }
	
	//DEBUG ( printf("tcp_start_thread:leave [%d]\n",rc); )
	return rc;
}
	
extern int tcp_stop_thread(void)
{
   //DEBUG ( printf("tcp_stop_thread:enter\n"); )

   LWP_MutexLock (mutexcheck);
   do_tcp_treat = false;
   LWP_MutexUnlock (mutexcheck);
   
   //DEBUG ( printf("tcp_stop_thread:leave [0]\n"); )
   return 0;
}

// -----------------------------------------------------------
// THE END
// -----------------------------------------------------------

