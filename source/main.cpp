/* 
**  TowerDefense for Wii - Created by wplaat (www.plaatsoft.nl)
**
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
**  Release Notes:
**  ==============
**
**  22/11/2009 Version 0.20
**  - Added trace library functionality
**  - Added network thread
**  - Use libfat 1.0.6 as disk access engine
**  - Use libmxml 2.6 library as xml engine
**  - Use libogc 1.8.0 library as Wii interface engine
**  - Build game with devkitPPC r19 compiler.
**
**  22/03/2009 Version 0.10
**  - Started programming.
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <ogcsys.h>
#include <gccore.h>
#include <gcmodplay.h> 
#include <wiiuse/wpad.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h> 
#include <asndlib.h>
#include <fat.h>
#include <mxml.h>
#include <sys/dir.h>
#include <mp3player.h>
#include <ogc/lwp_watchdog.h>	

#include "http.h"
#include "trace.h"
#include "GRRLIB.h"
#include "Enemy.h"

// -----------------------------------------------------------
// DEFINES
// -----------------------------------------------------------

#define PROGRAM_NAME	   		"TowerDefense"
#define PROGRAM_VERSION     	"0.20"
#define RELEASE_DATE        	"22-11-2009" 

// Check latest available version 
#define URL1                	"http://www.plaatsoft.nl/service/releasenotes5.html"
#define ID1			        	"UA-6887062-1"

// Fetch Release notes
#define URL2                	"http://www.plaatsoft.nl/service/releasenotes5.html"
#define ID2				   	 	"UA-6887062-1"

// Set Get Today HighScore
#define URL3                	"http://www.plaatsoft.nl/service/score_set_today.php"
#define ID3				    	"UA-6887062-1"

// Set Get Global HighScore
#define URL4                	"http://www.plaatsoft.nl/service/score_set_global.php"
#define ID4				    	"UA-6887062-1"

#define URL_TOKEN           	" Version "
#define HIGHSCORE_FILENAME  	"sd:/apps/TowerDefense/highscore.xml"
#define SETTING_FILENAME    	"sd:/apps/TowerDefense/setting.xml"
#define TRACE_FILENAME      	"sd:/apps/TowerDefense/towerdefense.trc"
#define GAME_DIRECTORY      	"sd:/apps/TowerDefense/"

#define WSP_POINTER_X       	200
#define WSP_POINTER_Y       	250

#define COLOR_WHITESMOKE    	0xFFFFFF
#define COLOR_LIGHTRED      	0x3333FF
#define COLOR_DARKBLACK     	0x000000
#define IMAGE_COLOR         	0xFFFFFFFF

#define MAX_BUTTONS         10
#define MAX_RUMBLE			4
#define MAX_BOARDSIZE 		14
#define MAX_BUBBLES   		(MAX_BOARDSIZE*MAX_BOARDSIZE)
#define MAX_HORZ_PIXELS		640
#define MAX_VERT_PIXELS		480
#define MAX_HIGHSCORES 		50
#define MAX_SETTINGS		10
#define MAX_BEST	 		50
#define MAX_LEVEL    	    7
#define MAX_LEN			    256
#define MAX_ANGLE			360
#define MIN_ALFA			127
#define MAX_ALFA			255
#define MIN_SIZE			1.0
#define MAX_SIZE			1.2
#define MAX_SOUND_VOLUME	10
#define MAX_MUSIC_TRACK     16
#define MAX_LINES		    200
#define MAX_BUFFER_SIZE		8192
#define MAX_IDLE_TIME	    10
#define MAX_POINTER         1
#define EXPLODE_STEP	    4
#define OUT_OF_TIME		    15
#define IR_X_OFFSET         40
#define IR_Y_OFFSET         40
#define SCROLLBAR_x         600
#define SCROLLBAR_Y_MIN     150
#define SCROLLBAR_Y_MAX     310

#define MUSIC_MULTIPLER		5
#define EFFECT_MULTIPLER	20

#define BUTTON_A            (WPAD_BUTTON_A     | WPAD_CLASSIC_BUTTON_A)
#define BUTTON_HOME         (WPAD_BUTTON_HOME  | WPAD_CLASSIC_BUTTON_HOME)
#define BUTTON_1            (WPAD_BUTTON_1     | WPAD_CLASSIC_BUTTON_X)
#define BUTTON_2            (WPAD_BUTTON_2     | WPAD_CLASSIC_BUTTON_Y)

#define BUTTON_UP           (WPAD_BUTTON_UP    | WPAD_CLASSIC_BUTTON_UP)
#define BUTTON_DOWN         (WPAD_BUTTON_DOWN  | WPAD_CLASSIC_BUTTON_DOWN)
#define BUTTON_LEFT         (WPAD_BUTTON_LEFT  | WPAD_CLASSIC_BUTTON_LEFT)
#define BUTTON_RIGHT        (WPAD_BUTTON_RIGHT | WPAD_CLASSIC_BUTTON_RIGHT)

// -----------------------------------------------------------
// TYPEDEF
// -----------------------------------------------------------

typedef struct 
{
  // png + jpg Image index     
  GRRLIB_texImg pointer1;

  GRRLIB_texImg monster1;
  GRRLIB_texImg monster2;
  GRRLIB_texImg monster3;
  GRRLIB_texImg monster4;
  
} 
image;

image images;

// -----------------------------------------------------------
// VARIABLES
// -----------------------------------------------------------

// Monster1 Image
extern const unsigned char     pic101data[];
extern int      pic101length;

// Monster2 Image
extern const unsigned char     pic102data[];
extern int      pic102length;

// Monster3 Image
extern const unsigned char     pic103data[];
extern int      pic103length;

// Monster4 Image
extern const unsigned char     pic104data[];
extern int      pic104length;


// Pointer1 Image
extern const unsigned char     pic200data[];
extern int      pic200length;


u32     *frameBuffer[1] = {NULL};
GXRModeObj *rmode = NULL;
Mtx     GXmodelView2D;
//static  MODPlay snd1;
char    appl_user3[MAX_LEN];

int     yOffset           = 0;
int     yjpegOffset       = 0;

Trace trace;

// -----------------------------------
// TYPEDEFS
// -----------------------------------

typedef struct 
{
  ir_t    ir;
  int     x;
  int     xOffset;
  int     y;
  int     yOffset;
  int     angle;
  int     rumble;
  GRRLIB_texImg image;
}
pointer;

pointer pointers[MAX_POINTER];

// -----------------------------------
// Game logic
// -----------------------------------

void initImages(void)
{
   char *s_fn="initImages";
   trace.event(s_fn,0,"enter");
     
   images.monster1=GRRLIB_LoadTexture( pic101data );
   images.monster2=GRRLIB_LoadTexture( pic102data );
   images.monster3=GRRLIB_LoadTexture( pic103data );
   images.monster4=GRRLIB_LoadTexture( pic104data );
    
   images.pointer1=GRRLIB_LoadTexture( pic200data); 
   pointers[0].image=images.pointer1;
   
   trace.event(s_fn,0,"leave [void]");
}


// -----------------------------------
// main
// -----------------------------------

int main()
{
    char *s_fn="main";
    int i;
	
	 // Init video layer
    VIDEO_Init();
	
	// Init wiimote layer
    WPAD_Init();
    WPAD_SetIdleTimeout(60); // Wiimote is shutdown after 60 seconds of innactivity.
	//WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);	// enable accelerometers and IR
    WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);
  
    // Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);
		
	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);
	
	if (rmode->xfbHeight==528)
	{
	    // TV mode PAL 50Hz
	    yOffset = 25;  
		yjpegOffset = 25;
	}
	else
	{      
	    // TV mode PAL 60Hz
	    yOffset = 25;
		yjpegOffset = 0;
	}

    // Init Fat
    fatInitDefault();

	// Open trace module
	trace.open(TRACE_FILENAME);
	trace.event(s_fn, 0,"%s %s Started", PROGRAM_NAME, PROGRAM_VERSION);
	
	initImages();
   
	Enemy enemy1(100,100,32,32,1,45,255,images.monster1);
	Enemy enemy2(150,150,32,32,1,45,255,images.monster2);
	Enemy enemy3(200,200,32,32,1,45,255,images.monster3);
	Enemy enemy4(250,250,32,32,1,45,255,images.monster4);
	
	
	// Repeat forever
    while( true )
	{				
		enemy1.draw();
		enemy2.draw();		
		enemy3.draw();
		enemy4.draw();
		
		enemy1.move();
		
        // Init text layer	  
        GRRLIB_initTexture();

        enemy1.properties();
		
        // Draw text layer on top of gameboard 
        GRRLIB_DrawImg2(0, 0, (u8*) GRRLIB_GetTexture(), 0, 1.0, 1.0, 255);

		 // Scan for button events
		WPAD_SetVRes(0, 640, 480);
        WPAD_ScanPads();
			
		for (i=0; i<MAX_POINTER; i++)
		{
		  u32 wpaddown = WPAD_ButtonsDown(i);
		
          // Scan for ir events 
		  WPAD_IR(i, &pointers[i].ir); 
		  pointers[i].x=pointers[i].ir.sx-WSP_POINTER_X;
		  pointers[i].xOffset=pointers[i].x+IR_X_OFFSET;
		  pointers[i].y=pointers[i].ir.sy-WSP_POINTER_Y;
		  pointers[i].yOffset=pointers[i].y+IR_Y_OFFSET;
		  pointers[i].angle=pointers[i].ir.angle;
				
		  // Scan for button events
		  if (wpaddown & WPAD_BUTTON_HOME) 
		  {
			  trace.event(s_fn, 0,"%s %s Stopped", PROGRAM_NAME, PROGRAM_VERSION);
		      exit(0);
		  }
				
		  if (wpaddown & WPAD_BUTTON_PLUS) 
		  {
		     int value=enemy1.getStep();
		     enemy1.setStep(++value);
		  }
       				
     	  if (wpaddown & WPAD_BUTTON_MINUS) 
		  {
		     int value=enemy1.getStep();
		     enemy1.setStep(--value);
		  }
			
       	  // Draw wiimote ir pointer
           GRRLIB_DrawImg( pointers[i].x, pointers[i].y, pointers[i].image, pointers[i].angle, 1, 1, IMAGE_COLOR );			 
		}
		
		GRRLIB_Render();
	}
	return 0; 
}

