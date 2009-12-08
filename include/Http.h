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
*/

#ifndef _HTTP_H_
#define _HTTP_H_

// -----------------------------------------------------------
// DEFINES
// -----------------------------------------------------------

#define TCP_CONNECT_TIMEOUT     5000
#define TCP_BLOCK_SIZE          (16 * 1024)
#define TCP_BLOCK_RECV_TIMEOUT  4000
#define TCP_BLOCK_SEND_TIMEOUT  4000
#define HTTP_TIMEOUT            300000
#define MAX_LEN        			256
#define NUM_THREADS             1
#define MAX_BUFFER_SIZE		    8192

// -----------------------------------------------------------
// ENUM
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

enum
{
    TCP_INIT=0,
	TCP_REQUEST1a=1,
	TCP_REQUEST1b=2,
	TCP_REQUEST2a=3,
	TCP_REQUEST2b=4,
	TCP_REQUEST3a=5,
	TCP_REQUEST3b=6,
	TCP_REQUEST4a=7,
	TCP_REQUEST4b=8,
	TCP_ERROR=9,
	TCP_RETRY=10,
	TCP_IDLE=11,
	TCP_END=12
};

class Http
{
  private:

	lwp_t threads[NUM_THREADS];
	mutex_t mutexcheck;
	mutex_t mutexversion;
	bool do_tcp_treat;

	char *appl_host; 
	char *appl_path;

	char appl_new_version[MAX_LEN];
	char appl_release_notes[MAX_BUFFER_SIZE];
	char appl_token[MAX_LEN];
	char appl_global_highscore[MAX_BUFFER_SIZE];
	char appl_today_highscore[MAX_BUFFER_SIZE];

	char appl_name[MAX_LEN];
	char appl_version[MAX_LEN];

	char appl_id1[MAX_LEN];
	char appl_url1[MAX_LEN];

	char appl_id2[MAX_LEN];
	char appl_url2[MAX_LEN];

	char appl_id3[MAX_LEN];
	char appl_url3[MAX_LEN];

	char appl_id4[MAX_LEN];
	char appl_url4[MAX_LEN];

	char appl_userData2[MAX_LEN];
	char appl_userData3[MAX_LEN];

	char var_cookie[MAX_LEN];

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
	//u32 http_status;
	u32 outlen;
	u8  *outbuf;

	s32 tcp_socket(void);
	s32 tcp_connect(char *host, const u16 port);
	char* tcp_readln(const s32 s, const u16 max_length, const u64 start_time, const u16 timeout);
	bool tcp_read(const s32 s, u8 **buffer, const u32 length);
	bool tcp_write(const s32 s, const u8 *buffer, const u32 length);
	int  tcp_init(void);
	void tcp_sleep(unsigned int seconds);
	bool http_split_url(char **host, char **path, const char *url);
	char* http_replaceString(char *orgstr, char *oldstr, char *newstr);
	const char* http_convertHTMlToAscii(char *in, int inSize);
	char http_bin2hex(int val);
	char *http_encode_url(char *buf, const char *str);
	void http_googleAnalysicUrl(char *buffer, char *domain, char *url, char *id);
	bool http_request(char *url, const u32 max_size);
	bool http_get_result(u32 *_http_status, u8 **content, u32 *length);
	char * http_findToken(u8 *buffer, int bufsize, char *token);
	void *tcp_thread(void *threadid);
	void tcp_clear_memory(void);

  public:
  	Http();
 	~Http();
 
    // Start HTTP thread
   int tcp_start_thread(const char *name, const char *version, 
						const char *id1, const char *url1, 
						const char *id2, const char *url2, 
						const char *id3, const char *url3, 
 						const char *id4, const char *url4,
						const char *token, const char *userData2, 
						const char *userData3);
						
	// Stop HTTP thread
	int tcp_stop_thread(void);

	// Fetch current thread state (String)
	const char *tcp_get_state(void);

	// Feth current thread state (int)
	int tcp_get_state_nr(void);

	// Set current thread state (int)
	int tcp_set_state(int state, const char *userData3);

	// Get version (String format)
	const char *tcp_get_version(void);

	// Get releasenotes (HTML format)
	const char *tcp_get_releasenote(void);

	// Get today highscore (XML format)
	const char *tcp_get_today_highscore(void);

	// Get global highscore (XML format)
	const char *tcp_get_global_highscore(void);
}

#endif
