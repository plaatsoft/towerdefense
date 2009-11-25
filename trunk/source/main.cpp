/* 
**  TowerDefense for Wii - Created by wplaat (www.plaatsoft.nl)
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
**  23/11/2009 Version 0.21
**  - Refactor Waepon, Monster, Button classes
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

#include <iostream>
#include <list>

#include "General.h"
#include "http.h"
#include "Trace.h"
#include "GRRLIB.h"
#include "Monster.h"
#include "Weapon.h"
#include "Button.h"
#include "Base.h"
#include "Pointer.h"

// -----------------------------------------------------------
// DEFINES
// -----------------------------------------------------------

// -----------------------------------------------------------
// TYPEDEF
// -----------------------------------------------------------

typedef struct 
{
  // png + jpg Image index     
  GRRLIB_texImg intro1;
  GRRLIB_texImg intro2;
  GRRLIB_texImg intro3;
  
  GRRLIB_texImg logo1;
  GRRLIB_texImg logo2;
  GRRLIB_texImg logo3;
  GRRLIB_texImg logo4;
  GRRLIB_texImg logo5;
  GRRLIB_texImg logo6;
  
  GRRLIB_texImg background1;
  
  GRRLIB_texImg pointer1;

  GRRLIB_texImg monster1;
  GRRLIB_texImg monster2;
  GRRLIB_texImg monster3;
  GRRLIB_texImg monster4;
  GRRLIB_texImg monster5;  
  GRRLIB_texImg monster6;
  GRRLIB_texImg monster7;
  GRRLIB_texImg monster8;
  GRRLIB_texImg monster9;
  GRRLIB_texImg monster10;
  GRRLIB_texImg monster11;
  GRRLIB_texImg monster12;
  GRRLIB_texImg monster13;
  GRRLIB_texImg monster14;
  GRRLIB_texImg monster15;
  GRRLIB_texImg monster16;
  GRRLIB_texImg monster17;
  GRRLIB_texImg monster18;
  GRRLIB_texImg monster19;
  GRRLIB_texImg monster20;
  GRRLIB_texImg monster21;
  GRRLIB_texImg monster22;
  GRRLIB_texImg monster23;
  GRRLIB_texImg monster24;
  GRRLIB_texImg monster25;
  
  GRRLIB_texImg base1;
  GRRLIB_texImg base2;
  GRRLIB_texImg base3;
  GRRLIB_texImg base4;
  GRRLIB_texImg base5;
  GRRLIB_texImg base6;
  
  GRRLIB_texImg road1;
  GRRLIB_texImg road2;
  GRRLIB_texImg road3;
  GRRLIB_texImg road4;
} 
image;

image images;

// -----------------------------------------------------------
// VARIABLES
// -----------------------------------------------------------

// intro1 Image
extern const unsigned char     pic1data[];
extern int      pic1length;

// intro2 Image
extern const unsigned char     pic2data[];
extern int      pic2length;

// intro3 Image
extern const unsigned char     pic3data[];
extern int      pic3length;

// logo1 Image
extern const unsigned char     pic4data[];
extern int      pic4length;

// logo2 Image
extern const unsigned char     pic5data[];
extern int      pic5length;

// logo3 Image
extern const unsigned char     pic6data[];
extern int      pic6length;

// logo4 Image
extern const unsigned char     pic7data[];
extern int      pic7length;

// logo5 Image
extern const unsigned char     pic8data[];
extern int      pic8length;

// logo6 Image
extern const unsigned char     pic9data[];
extern int      pic9length;

// Background1 Image
extern const unsigned char     pic10data[];
extern int      pic10length;

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

// Monster5 Image
extern const unsigned char     pic105data[];
extern int      pic105length;

// Monster6 Image
extern const unsigned char     pic106data[];
extern int      pic106length;

// Monster7 Image
extern const unsigned char     pic107data[];
extern int      pic107length;

// Monster8 Image
extern const unsigned char     pic108data[];
extern int      pic108length;

// Monster9 Image
extern const unsigned char     pic109data[];
extern int      pic109length;

// Monster10 Image
extern const unsigned char     pic110data[];
extern int      pic110length;

// Monster11 Image
extern const unsigned char     pic111data[];
extern int      pic111length;

// Monster12 Image
extern const unsigned char     pic112data[];
extern int      pic112length;

// Monster13 Image
extern const unsigned char     pic113data[];
extern int      pic113length;

// Monster14 Image
extern const unsigned char     pic114data[];
extern int      pic114length;

// Monster15 Image
extern const unsigned char     pic115data[];
extern int      pic115length;

// Monster16 Image
extern const unsigned char     pic116data[];
extern int      pic116length;

// Monster17 Image
extern const unsigned char     pic117data[];
extern int      pic117length;

// Monster18 Image
extern const unsigned char     pic118data[];
extern int      pic118length;

// Monster19 Image
extern const unsigned char     pic119data[];
extern int      pic119length;

// Monster20 Image
extern const unsigned char     pic120data[];
extern int      pic120length;

// Monster21 Image
extern const unsigned char     pic121data[];
extern int      pic121length;

// Monster22 Image
extern const unsigned char     pic122data[];
extern int      pic122length;

// Monster23 Image
extern const unsigned char     pic123data[];
extern int      pic123length;

// Monster24 Image
extern const unsigned char     pic124data[];
extern int      pic124length;

// Monster25 Image
extern const unsigned char     pic125data[];
extern int      pic125length;

// Pointer1 Image
extern const unsigned char     pic200data[];
extern int      pic200length;

// Base1 Image
extern const unsigned char     pic301data[];
extern int      pic301length;

// Base2 Image
extern const unsigned char     pic302data[];
extern int      pic302length;

// Base3 Image
extern const unsigned char     pic303data[];
extern int      pic303length;

// Base4 Image
extern const unsigned char     pic304data[];
extern int      pic304length;

// Base5 Image
extern const unsigned char     pic305data[];
extern int      pic305length;

// Base6 Image
extern const unsigned char     pic306data[];
extern int      pic306length;

// Road1 Image
extern const unsigned char     pic401data[];
extern int      pic401length;

// Road2 Image
extern const unsigned char     pic402data[];
extern int      pic402length;

// Road3 Image
extern const unsigned char     pic403data[];
extern int      pic403length;

// Road4 Image
extern const unsigned char     pic404data[];
extern int      pic404length;


u32         *frameBuffer[1] = {NULL};
GXRModeObj  *rmode = NULL;
Mtx         GXmodelView2D;
//static  MODPlay snd1;
char        appl_user3[MAX_LEN];

int         yOffset           = 0;
int         yjpegOffset       = 0;

Trace trace;

Monster monster[100];
Base base[8];
Pointer pointer[1];

int maxPointer = 1;
int maxMonster = 25;
int maxBase    = 6;

// -----------------------------------
// Game logic
// -----------------------------------

void initImages(void)
{
   char *s_fn="initImages";
   trace.event(s_fn,0,"enter");
     
   images.intro1=GRRLIB_LoadTexture( pic1data );
   images.intro2=GRRLIB_LoadTexture( pic2data );
   images.intro2=GRRLIB_LoadTexture( pic3data );

   images.logo1=GRRLIB_LoadTexture( pic4data );
   images.logo2=GRRLIB_LoadTexture( pic5data );
   images.logo3=GRRLIB_LoadTexture( pic6data );
   images.logo4=GRRLIB_LoadTexture( pic7data );
   images.logo5=GRRLIB_LoadTexture( pic8data );
   images.logo6=GRRLIB_LoadTexture( pic9data );
   
   images.background1=GRRLIB_LoadTexture( pic10data );
	 
   images.monster1=GRRLIB_LoadTexture( pic101data );
   images.monster2=GRRLIB_LoadTexture( pic102data );
   images.monster3=GRRLIB_LoadTexture( pic103data );
   images.monster4=GRRLIB_LoadTexture( pic104data );
   images.monster5=GRRLIB_LoadTexture( pic105data );
   images.monster6=GRRLIB_LoadTexture( pic106data );
   images.monster7=GRRLIB_LoadTexture( pic107data );
   images.monster8=GRRLIB_LoadTexture( pic108data );
   images.monster9=GRRLIB_LoadTexture( pic109data );
   images.monster10=GRRLIB_LoadTexture( pic110data );
   images.monster11=GRRLIB_LoadTexture( pic111data );
   images.monster12=GRRLIB_LoadTexture( pic112data );   
   images.monster13=GRRLIB_LoadTexture( pic113data );
   images.monster14=GRRLIB_LoadTexture( pic114data );
   images.monster15=GRRLIB_LoadTexture( pic115data );
   images.monster16=GRRLIB_LoadTexture( pic116data );
   images.monster17=GRRLIB_LoadTexture( pic117data );
   images.monster18=GRRLIB_LoadTexture( pic118data );
   images.monster19=GRRLIB_LoadTexture( pic119data );
   images.monster20=GRRLIB_LoadTexture( pic120data );
   images.monster21=GRRLIB_LoadTexture( pic121data );
   images.monster22=GRRLIB_LoadTexture( pic122data );
   images.monster23=GRRLIB_LoadTexture( pic123data );
   images.monster24=GRRLIB_LoadTexture( pic124data );
   images.monster25=GRRLIB_LoadTexture( pic125data );		

   images.pointer1=GRRLIB_LoadTexture( pic200data); 
   
   images.base1=GRRLIB_LoadTexture( pic301data );	
   images.base2=GRRLIB_LoadTexture( pic302data );	
   images.base3=GRRLIB_LoadTexture( pic303data );	
   images.base4=GRRLIB_LoadTexture( pic304data );	
   images.base5=GRRLIB_LoadTexture( pic305data );	
   images.base6=GRRLIB_LoadTexture( pic306data );	

   images.road1=GRRLIB_LoadTexture( pic401data );	
   images.road2=GRRLIB_LoadTexture( pic402data );	
   images.road3=GRRLIB_LoadTexture( pic403data );	
   images.road4=GRRLIB_LoadTexture( pic404data );	

   trace.event(s_fn,0,"leave [void]");
}

// Init monster
void initMonsters(void)
{
   char *s_fn="initMonsters";
   trace.event(s_fn,0,"enter");
   
   for( int i = 0; i < maxMonster-1; i++ ) 
   {
	  int x = (int) rand() % 400;
	  int y = (int) rand() % 400;
	 
      monster[i].setX(x);
	  monster[i].setY(y);
	  monster[i].setSize(1);
	  monster[i].setAngle(0);
	  monster[i].setWidth(32);
	  monster[i].setHeight(32);
	  monster[i].setStep(2);
	  
	  trace.event(s_fn,0,"Init monster [%d|x=%d|y=%d]",i,x,y);
	  
	  switch (i+1)
	  {
	     case 1: monster[i].setImage(images.monster1);
				 break;
				 
	     case 2: monster[i].setImage(images.monster2);
				 break;

	     case 3: monster[i].setImage(images.monster3);
				 break;				 

	     case 4: monster[i].setImage(images.monster4);
				 break;
				 
		 case 5: monster[i].setImage(images.monster5);
				 break;

		 case 6: monster[i].setImage(images.monster6);
				 break;

		 case 7: monster[i].setImage(images.monster7);
				 break;

		 case 8: monster[i].setImage(images.monster8);
				 break;

		 case 9: monster[i].setImage(images.monster9);
				 break;

		 case 10: monster[i].setImage(images.monster10);
				 break;

		 case 11: monster[i].setImage(images.monster11);
				 break;

		 case 12: monster[i].setImage(images.monster12);
				 break;

		 case 13: monster[i].setImage(images.monster13);
				 break;

		 case 14: monster[i].setImage(images.monster14);
				 break;

		 case 15: monster[i].setImage(images.monster15);
				 break;

		 case 16: monster[i].setImage(images.monster16);
				 break;
				 
		 case 17: monster[i].setImage(images.monster17);
				 break;
				 
		 case 18: monster[i].setImage(images.monster18);
				 break;

		 case 19: monster[i].setImage(images.monster19);
				 break;
				 
		 case 20: monster[i].setImage(images.monster20);
				 break;
				 
		 case 21: monster[i].setImage(images.monster21);
				 break;

		 case 22: monster[i].setImage(images.monster22);
				 break;
				 
		 case 23: monster[i].setImage(images.monster23);
				 break;

		 case 24: monster[i].setImage(images.monster24);
				 break;
				 
		 case 25: monster[i].setImage(images.monster25);
				 break;
	  }
   }
   trace.event(s_fn,0,"leave [void]");
}

// Init bases
void initBases(void)
{
    char *s_fn="initBases";
    trace.event(s_fn,0,"enter");
   
    base[0].setX(500);
	base[0].setY(10);
	base[0].setImage(images.base1);

    base[1].setX(500);
	base[1].setY(80);
	base[1].setImage(images.base2);

    base[2].setX(500);
	base[2].setY(170);
	base[2].setImage(images.base3);

    base[3].setX(500);
	base[3].setY(240);
	base[3].setImage(images.base4);

    base[4].setX(500);
	base[4].setY(310);
	base[4].setImage(images.base5);
	
    base[5].setX(500);
	base[5].setY(370);
	base[5].setImage(images.base6);
	
	trace.event(s_fn,0,"leave [void]");
}

// Init monster
void initPointers(void)
{
   char *s_fn="initPointers";
   trace.event(s_fn,0,"enter");
   
   pointer[0].setX(0);
   pointer[0].setY(0);
   pointer[0].setAngle(0);
   pointer[0].setImage(images.pointer1);
	
   trace.event(s_fn,0,"leave [void]");
}
	  

// Draw monster on screen
void drawMonsters(void)
{
   int i;
   for( i=0; i<maxMonster; i++ ) 
   {
	 monster[i].draw();
   }
}

// Draw base on screen
void drawBases(void)
{
   int i;
   for( i=0; i<maxBase; i++ ) 
   {
	 base[i].draw();
   }
}

// Draw base on screen
void drawPointers(void)
{
   int i;
   for( i=0; i<maxPointer; i++ ) 
   {
	 pointer[i].draw();
   }
}

// -----------------------------------
// main
// -----------------------------------

int main()
{
    char *s_fn="main";
	
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
	
	// Init Images
	initImages();
   
    // Init pointers
    initPointers();
	
    // Init monster
    initMonsters();
	
	// Init base
	initBases();
		
	// Init FreeType font engine
	GRRLIB_InitFreetype();
	  			
    // Init GRRLib graphics library
    GRRLIB_Init();
        
	// Make screen black
	GRRLIB_FillScreen(0xFFFFFF);
    GRRLIB_Render();
	
	// Repeat forever
    while( true )
	{				
		// Draw background1 image
        GRRLIB_DrawImg(0, 0, images.background1, 0, 1.0, 1.0, IMAGE_COLOR);
		
		drawMonsters();
		drawBases();
	
        // Init text layer	  
        GRRLIB_initTexture();
		GRRLIB_Printf2(10, 10, "Hello", 14, COLOR_DARKBLACK); 
        GRRLIB_DrawImg2(0, 0, (u8*) GRRLIB_GetTexture(), 0, 1.0, 1.0, 255);

		// Draw Wii Motion Pointers
		drawPointers();
			
		// Render screen
		GRRLIB_Render();
	}
	GRRLIB_Exit();
	
	return 0; 
}