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

#ifndef HTTP_H
#define HTTP_H

enum
{
    TCP_INIT=0,
	TCP_REQUEST1a=1,
	TCP_REQUEST1b=2,
	TCP_REQUEST2a=3,
	TCP_REQUEST2b=4,
	TCP_REQUEST3a=5,
	TCP_REQUEST3b=6,
	TCP_ERROR=7,
	TCP_RETRY=8,
	TCP_IDLE=9,
	TCP_END=10
};

extern int tcp_start_thread(char *name, 
							char *version, 
							char *id1, 
							char *url1, 
							char*id2, 
							char *url2, 
							char *id3, 
							char *url3, 
							char *token, 
							char *userData2, 
							char *userData3);
							
extern int tcp_stop_thread(void);

extern char *tcp_get_state(void);

extern int tcp_get_state_nr(void);

int tcp_set_state(int state, char *userData3);

extern char *tcp_get_version(void);

extern char *tcp_get_releasenote(void);

extern char *tcp_get_highscore(void);

#endif
