/** 
 *  @file 
 *  @brief The file contain the http (network) class
 *  @author wplaat
 *
 *  Copyright (C) 2008-2010 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef HTTP_H
#define HTTP_H

//==============================================================================
// C++ header
//==============================================================================
#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

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

// Init tcp layer
void tcp_init_layer(void);

// Start HTTP thread
int tcp_start_thread(	const char *name,  const char *version, 
						const char *id1,   const char *url1, 
						const char *id2,   const char *url2, 
						const char *id3,   const char *url3, 
						const char *id4,   const char *url4,
						const char *token, const char *userData2, 
						const char *userData3);
						
// Stop HTTP thread
int tcp_stop_thread(void);

// Fetch current thread state (String)
char *tcp_get_state(void);

// Feth current thread state (int)
int tcp_get_state_nr(void);

// Set current thread state (int)
int tcp_set_state(int state, char *userData3);

// Get version (String format)
char *tcp_get_version(void);

// Get releasenotes (HTML format)
char *tcp_get_releasenote(void);

// Get today highscore (XML format)
char *tcp_get_today_highscore(void);

// Get global highscore (XML format)
char *tcp_get_global_highscore(void);

#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif
