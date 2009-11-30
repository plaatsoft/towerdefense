/* 
**  TowerDefense for Wii - Created by wplaat (www.plaatsoft.nl)
**
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
**  30/11/2009 Version 0.23
**  - Use libogc 1.8.1 library as Wii interface engine
**  - Very basic Game menu page.
**  - Improve grid.
**  - Align monster movement on grid.
**
**  29/11/2009 Version 0.22
**  - FreeType is working again with GRRLIB 4.1.1
**  - Added four WiiMote controllers support
**  - Parsing map grid from file.
**
**  27/11/2009 Version 0.21
**  - Added GRRLib 4.1.1 library
**  - Refactor Weapon, Monster, Button class
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

#include "GRRLIB.h"
#include "General.h"
#include "http.h"
#include "Trace.h"
#include "Monster.h"
#include "Weapon.h"
#include "Button.h"
#include "Base.h"
#include "Pointer.h"
#include "Grid.h"

// -----------------------------------------------------------
// TYPEDEF
// -----------------------------------------------------------

typedef struct 
{
  // png + jpg Image index     
  GRRLIB_texImg *intro1;
  GRRLIB_texImg *intro2;
  GRRLIB_texImg *intro3;
  
  GRRLIB_texImg *logo1;
  GRRLIB_texImg *logo2;
  GRRLIB_texImg *logo3;
  GRRLIB_texImg *logo4;
  GRRLIB_texImg *logo5;
  GRRLIB_texImg *logo6;
  GRRLIB_texImg *logo;
  
  GRRLIB_texImg *background1;
  GRRLIB_texImg *background2;

  GRRLIB_texImg *monster1;
  GRRLIB_texImg *monster2;
  GRRLIB_texImg *monster3;
  GRRLIB_texImg *monster4;
  GRRLIB_texImg *monster5;  
  GRRLIB_texImg *monster6;
  GRRLIB_texImg *monster7;
  GRRLIB_texImg *monster8;
  GRRLIB_texImg *monster9;
  GRRLIB_texImg *monster10;
  GRRLIB_texImg *monster11;
  GRRLIB_texImg *monster12;
  GRRLIB_texImg *monster13;
  GRRLIB_texImg *monster14;
  GRRLIB_texImg *monster15;
  GRRLIB_texImg *monster16;
  GRRLIB_texImg *monster17;
  GRRLIB_texImg *monster18;
  GRRLIB_texImg *monster19;
  GRRLIB_texImg *monster20;
  GRRLIB_texImg *monster21;
  GRRLIB_texImg *monster22;
  GRRLIB_texImg *monster23;
  GRRLIB_texImg *monster24;
  GRRLIB_texImg *monster25;
  
  GRRLIB_texImg *base1;
  GRRLIB_texImg *base2;
  GRRLIB_texImg *base3;
  GRRLIB_texImg *base4;
  GRRLIB_texImg *base5;
  GRRLIB_texImg *base6;
  
  GRRLIB_texImg *road1;
  GRRLIB_texImg *road2;
  GRRLIB_texImg *road3;
  GRRLIB_texImg *road4;
  GRRLIB_texImg *road5;

  GRRLIB_texImg *weapon1;
  
  GRRLIB_texImg *button1;
  GRRLIB_texImg *buttonFocus1;
    
  GRRLIB_texImg *pointer1;
  GRRLIB_texImg *pointer2;
  GRRLIB_texImg *pointer3; 
  GRRLIB_texImg *pointer4;
  
} 
image;

image images;

// -----------------------------------------------------------
// VARIABLES
// -----------------------------------------------------------

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

// Background2 Image
extern const unsigned char     pic11data[];
extern int      pic11length;

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

// Pointer2 Image
extern const unsigned char     pic201data[];
extern int      pic201length;

// Pointer3 Image
extern const unsigned char     pic202data[];
extern int      pic202length;

// Pointer4 Image
extern const unsigned char     pic203data[];
extern int      pic203length;

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

// Road5 Image
extern const unsigned char     pic405data[];
extern int      pic405length;

// Rocket Image
extern const unsigned char     pic500data[];
extern int      pic500length;

// Button1 Image
extern const unsigned char     pic600data[];
extern int      pic600length;

// Button1Focus Image
extern const unsigned char     pic601data[];
extern int      pic601length;


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
Pointer pointer[4];
Grid grid;
Weapon weapon[1];
Button button[10];

int maxPointer  = 4;
int maxMonster  = 25;
int maxBase     = 6;
int maxMap	    = 1;
int maxWeapon   = 1;
int maxButton   = 0;

int day=0;

int stateMachine=stateIntro1;
int selectedMap = 0; 
int prevSelectedMap = 0; 

float   wave1 = 0;
float   wave2 = 0;

boolean stopApplication = false;

// -----------------------------------
// INIT and DESTOY METHODES
// -----------------------------------

void initImages(void)
{
   const char *s_fn="initImages";
   trace.event(s_fn,0,"enter");

   images.logo2=GRRLIB_LoadTexture( pic5data );
   images.logo3=GRRLIB_LoadTexture( pic6data );
   images.logo4=GRRLIB_LoadTexture( pic7data );
   images.logo5=GRRLIB_LoadTexture( pic8data );
   images.logo6=GRRLIB_LoadTexture( pic9data );
   
   images.logo=GRRLIB_LoadTexture( pic5data );
   GRRLIB_InitTileSet(images.logo, images.logo->w, 1, 0);
   
   images.background1=GRRLIB_LoadTexture( pic10data );
   images.background2=GRRLIB_LoadTexture( pic11data );
	 
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
   images.pointer2=GRRLIB_LoadTexture( pic201data);
   images.pointer3=GRRLIB_LoadTexture( pic202data);
   images.pointer4=GRRLIB_LoadTexture( pic203data);
   
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
   images.road5=GRRLIB_LoadTexture( pic405data );	

   images.weapon1=GRRLIB_LoadTexture( pic500data );

   images.button1=GRRLIB_LoadTexture( pic600data );
   images.buttonFocus1=GRRLIB_LoadTexture( pic601data );
      
   trace.event(s_fn,0,"leave [void]");
}

void destroyImages(void)
{
   const char *s_fn="destroyImages";
   trace.event(s_fn,0,"enter");
   
   GRRLIB_FreeTexture(images.logo2);
   GRRLIB_FreeTexture(images.logo3);
   GRRLIB_FreeTexture(images.logo4);
   GRRLIB_FreeTexture(images.logo5);
   GRRLIB_FreeTexture(images.logo6);
   
   GRRLIB_FreeTexture(images.background1);
   GRRLIB_FreeTexture(images.background2);
   
   GRRLIB_FreeTexture(images.monster1);
   GRRLIB_FreeTexture(images.monster2);
   GRRLIB_FreeTexture(images.monster3);
   GRRLIB_FreeTexture(images.monster4);
   GRRLIB_FreeTexture(images.monster5);
   GRRLIB_FreeTexture(images.monster6);
   GRRLIB_FreeTexture(images.monster7);
   GRRLIB_FreeTexture(images.monster8);
   GRRLIB_FreeTexture(images.monster9);
   GRRLIB_FreeTexture(images.monster10);
   GRRLIB_FreeTexture(images.monster11);
   GRRLIB_FreeTexture(images.monster12);
   GRRLIB_FreeTexture(images.monster13);
   GRRLIB_FreeTexture(images.monster14);
   GRRLIB_FreeTexture(images.monster15);
   GRRLIB_FreeTexture(images.monster16);
   GRRLIB_FreeTexture(images.monster17);
   GRRLIB_FreeTexture(images.monster18);
   GRRLIB_FreeTexture(images.monster19);
   GRRLIB_FreeTexture(images.monster20);
   GRRLIB_FreeTexture(images.monster21);
   GRRLIB_FreeTexture(images.monster22);
   GRRLIB_FreeTexture(images.monster23);
   GRRLIB_FreeTexture(images.monster24);
   GRRLIB_FreeTexture(images.monster25);
   
   GRRLIB_FreeTexture(images.pointer1);
   GRRLIB_FreeTexture(images.pointer2);
   GRRLIB_FreeTexture(images.pointer3);
   GRRLIB_FreeTexture(images.pointer4);
   
   GRRLIB_FreeTexture(images.base1);
   GRRLIB_FreeTexture(images.base2);
   GRRLIB_FreeTexture(images.base3);
   GRRLIB_FreeTexture(images.base4);
   GRRLIB_FreeTexture(images.base5);
   GRRLIB_FreeTexture(images.base6);
   
   GRRLIB_FreeTexture(images.road1);
   GRRLIB_FreeTexture(images.road2);
   GRRLIB_FreeTexture(images.road3);
   GRRLIB_FreeTexture(images.road4);
   GRRLIB_FreeTexture(images.road5);
   
   GRRLIB_FreeTexture(images.weapon1);
	
   GRRLIB_FreeTexture(images.button1);
   GRRLIB_FreeTexture(images.buttonFocus1);
	
   trace.event(s_fn,0,"leave");
}


// Init Weapons
void initWeapons(void)
{
    const char *s_fn="initWeapons";
    trace.event(s_fn,0,"enter");
   
	weapon[0].setImage(images.weapon1);
	weapon[0].setX(100);
	weapon[0].setY(100);
	weapon[0].setAngle(0);
	weapon[0].setStep(2);
	
	trace.event(s_fn,0,"leave [void]");
}

// Init monster
void initMonsters(void)
{
   const char *s_fn="initMonsters";
   trace.event(s_fn,0,"enter");
   
   int delay=0;
   for( int i = 0; i < maxMonster; i++ ) 
   {
   	  trace.event(s_fn,0,"Init monster [%d]",i);
	 	  
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
	  	 
	  //int step = (int) (rand() % 3)+1;
 
	  monster[i].setStep(1);
	  monster[i].setDelay(delay);
	  monster[i].setEnergy(10);
	  
	  // Wait +/- two seconds before new monster is lanched.
	  delay+=100;
   }
   trace.event(s_fn,0,"leave [void]");
}

// Init Pointes
void initPointers(void)
{
   const char *s_fn="initPointers";
   trace.event(s_fn,0,"enter");
   
   pointer[0].setIndex(0);
   pointer[0].setX(320);
   pointer[0].setY(240);
   pointer[0].setAngle(0);
   pointer[0].setImage(images.pointer1);

   pointer[1].setIndex(1);
   pointer[1].setX(320);
   pointer[1].setY(240);
   pointer[1].setAngle(0);
   pointer[1].setImage(images.pointer2);

   pointer[2].setIndex(2);
   pointer[2].setX(320);
   pointer[2].setY(240);
   pointer[2].setAngle(0);
   pointer[2].setImage(images.pointer3);

   pointer[3].setIndex(3);
   pointer[3].setX(320);
   pointer[3].setY(240);
   pointer[3].setAngle(0);
   pointer[3].setImage(images.pointer4);	
   
   trace.event(s_fn,0,"leave [void]");
}

// Init Grid
void initGrid(int level)
{
    const char *s_fn="initGrid";
    trace.event(s_fn,0,"enter [level=%d]",level);
   
	grid.setImage1(images.road1);
	grid.setImage2(images.road2);
	grid.setImage3(images.road3);
	grid.setImage4(images.road4);
	grid.setImage5(images.road5);
	
	switch( level )
	{
		case 1: grid.setImageBase(images.base1);
				grid.create(GRID1_FILENAME );
				break;
			
		case 2: grid.setImageBase(images.base2);
				grid.create(GRID2_FILENAME );
				break;
				
		case 3: grid.setImageBase(images.base3);
				grid.create(GRID3_FILENAME );
				break;
	}

	trace.event(s_fn,0,"leave [void]");
}

void initButtons(void)
{
	//switch( stateMachine )	
	{	
		//case stateMenu:
			{
				// Button (Play Map1)
				button[0].setX(100);
				button[0].setY(100);
				button[0].setImageNormal(images.button1);
				button[0].setImageFocus(images.buttonFocus1);
				button[0].setLabel("Map1");
				
				// Button (Play Map2)
				button[1].setX(100);
				button[1].setY(200);
				button[1].setImageNormal(images.button1);
				button[1].setImageFocus(images.buttonFocus1);
				button[1].setLabel("Map2");
				
				// Button (Play Map2)
				button[2].setX(100);
				button[2].setY(300);
				button[2].setImageNormal(images.button1);
				button[2].setImageFocus(images.buttonFocus1);
				button[2].setLabel("Map3");
				
				maxButton=3;
			}
			//break;
	}
}

void initGame(void)
{
	const char *s_fn="initGame";
	trace.event(s_fn,0,"enter");
   
	trace.event(s_fn,0,"stateMachine=stateIntro1");
	stateMachine=stateIntro1;
   
   	// Init Images
	initImages();
   
    // Init pointers
    initPointers();
		
	// Init Buttons
	initButtons();
	
	trace.event(s_fn,0,"leave");
}
	
// -----------------------------------
// DRAW METHODES
// -----------------------------------

static u8 CalculateFrameRate() 
{
    static u8 frameCount = 0;
    static u32 lastTime;
    static u8 FPS = 0;
    u32 currentTime = ticks_to_millisecs(gettime());

    frameCount++;
    if(currentTime - lastTime > 1000) {
        lastTime = currentTime;
        FPS = frameCount;
        frameCount = 0;
    }
    return FPS;
}	  

// Draw monster on screen
void drawGrid(void)
{
   grid.draw();
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

// Draw monster on screen
void drawMonsters(void)
{
   int i;
   for( i=0; i<maxMonster; i++ ) 
   {
	  monster[i].move();
	  monster[i].draw();
	  monster[i].properties();
   }
}

// Draw base on screen
void drawWeapons(void)
{
   int i;
   for( i=0; i<maxWeapon; i++ ) 
   {
     weapon[i].move();
	 weapon[i].draw();
	 weapon[i].properties();
   }
}

// Draw buttons on screen
void drawButtons(void)
{
   int i;
   for( i=0; i<maxButton; i++ ) 
   {
	 button[i].draw(pointer[0].getX(), pointer[0].getY());
   }
}

void drawText(int x, int y, int type, const char *text)
{
   char tmp[MAX_LEN];
   memset(tmp,0x00,sizeof(tmp));
   
   if (text!=NULL)
   {    		
     strcpy(tmp, text);
	 
     switch (type)
     {	   	   	 
       case fontTitle: 
	   {
	      if (x==0) x=320-((strlen(tmp)*34)/2);  
		  GRRLIB_Printf2(x, y, tmp, 72, COLOR_WHITESMOKE); 
	   }
	   break;
  
       case fontWelcome: 
	   {
		  GRRLIB_Printf2(x, y, tmp, 40, COLOR_WHITESMOKE); 
	   }
	   break;
	   
	   case fontSubTitle:
	   {
	      if (x==0) x=320-((strlen(tmp)*20)/2);
		  GRRLIB_Printf2(x, y, tmp, 30, COLOR_WHITESMOKE);          
	   }
	   break;
	   
	   case fontSubTitle2:
	   {
	      if (x==0) x=320-((strlen(tmp)*20)/2);
		  GRRLIB_Printf2(x, y, tmp, 30, COLOR_LIGHTRED);          
	   }
	   break;
	   	   
	   case fontParagraph:
	   {
	       if (x==0) x=320-((strlen(tmp)*10)/2);	   
		   GRRLIB_Printf2(x, y, tmp, 24, COLOR_WHITESMOKE);            
	   }
	   break;
	   	   
	   case fontNormal:
	   {
	       if (x==0) x=320-((strlen(tmp)*7)/2);
		   GRRLIB_Printf2(x, y, tmp, 18, COLOR_WHITESMOKE);            
	   }
	   break;
	         
	   case fontNew:
	   {
	       if (x==0) x=320-((strlen(tmp)*8)/2);	   
		   GRRLIB_Printf2(x, y, tmp, 22, COLOR_WHITESMOKE);            
	   }
	   break;
	   
	   case fontSpecial:
	   {
	       if (x==0) x=320-((strlen(tmp)*10)/2);
		   GRRLIB_Printf2(x, y, tmp, 10, COLOR_WHITESMOKE);            
	   }
	   break;
	   
	   case fontButton:
	   {
	       if (strlen(tmp)==1)
		   {
		      GRRLIB_Printf2(x+35, y, tmp, 24, COLOR_WHITESMOKE);            
		   }
		   else
		   {
		      GRRLIB_Printf2(x+20, y, tmp, 24, COLOR_WHITESMOKE);    
		   }		   
	   }
	   break;
	 }
   }
}

void drawScreen(void)
{ 	   	
    //int i=0;
	char tmp[MAX_LEN];
				  
    switch( stateMachine )	
	{	
	
	   case stateIntro1:
	   {
	      int  ypos=yOffset;
		
	      // Draw background
		  GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR );
		  
		  // Draw background
		  //GRRLIB_DrawImg(((640-images.logo1->w)/2) , ((480-images.logo1->h)/2)-20, images.logo1, 0, size, size, IMAGE_COLOR );
		  
		  // Init text layer	  
          GRRLIB_initTexture();	
		  
		  drawText(0, ypos, fontParagraph,  "Created by wplaat"  );
		  ypos+=20;
		  drawText(0, ypos, fontParagraph,  "http://www.plaatsoft.nl"  );
		  ypos+=340;
		  drawText(40, ypos, fontNormal,  "This software is open source and may be copied, distributed or modified"  );
		  ypos+=20;
		  drawText(60, ypos, fontNormal,  "under the terms of the GNU General Public License (GPL) version 2" );
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 460, fontSpecial, tmp);
		  
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }	   
	   break;
	   
	   case stateIntro2:
	   {
	      int  ypos=yOffset+320;
		  unsigned int  j;
		  
	      // Draw background
		  GRRLIB_DrawImg(0,0, images.background2, 0, 1, 1, IMAGE_COLOR );

		  // Draw Plaatsoft logo		 
   	      for(j=0;j<images.logo->h;j++)
		  {
             GRRLIB_DrawTile(((640-images.logo2->w)/2)+sin(wave1)*50, (((480-images.logo2->h)/2)-50)+j, images.logo, 0, 1, 1, IMAGE_COLOR,j );
             wave1+=0.02;
          }
		  wave2+=0.02;
          wave1=wave2;
		  
		  // Init text layer	  
          GRRLIB_initTexture();	
		  
		  drawText(0, ypos, fontParagraph,  "Please visit my website for more information."  );
		  ypos+=40;
		  drawText(0, ypos, fontParagraph,  "http://www.plaatsoft.nl"  );
			  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 460, fontSpecial, tmp);
		  
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }	   
	   break;
	   	   
	   case stateIntro3:
	   {
	      int  ypos=yOffset+390;

		  // Draw backg
		  GRRLIB_DrawImg(0,0, images.logo3, 0, 0.95, 0.98, IMAGE_COLOR );
		  GRRLIB_DrawImg(310,0, images.logo4, 0, 0.95, 0.98, IMAGE_COLOR );
		  GRRLIB_DrawImg(0,240, images.logo5, 0, 0.95, 0.98, IMAGE_COLOR );
		  GRRLIB_DrawImg(310,240, images.logo6, 0, 0.95, 0.98, IMAGE_COLOR );
		  
          GRRLIB_DrawImg(350, 240, images.logo2, 0, 0.5, 0.5, IMAGE_COLOR );

		  // Init text layer	  
          GRRLIB_initTexture();	
		  
		  drawText(350, ypos, fontNormal,  "Some more Wii games developed"  );
		  ypos+=20;
		  drawText(400, ypos, fontNormal,  "by www.plaatsoft.nl"  );
			 
		  sprintf(tmp,"%d fps", CalculateFrameRate()); 
		  drawText(590, 460, fontSpecial, tmp); 
 
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }	   
	   break;
	 
	 case stateMenu:
		{
			 // Init text layer	  
          GRRLIB_initTexture();
	
		  pointer[0].properties();	  
		  drawButtons();
		  
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
	
	 case stateGame:
		{
		  // Init text layer	  
          GRRLIB_initTexture();
		  
	 	  drawGrid();
		  drawMonsters();
		  drawBases();
		  drawWeapons();
		  			 
		  sprintf(tmp,"%d fps", CalculateFrameRate()); 
		  GRRLIB_Printf2(20, 460, tmp, 10, COLOR_DARKBLACK);
 
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
	}
}

// -----------------------------------
// main
// -----------------------------------

int main()
{
    const char *s_fn="main";
	
	 // Init video layer
    VIDEO_Init();
	
	// Init wiimote layer
    WPAD_Init();
	
	// Wiimote is shutdown after 60 seconds of innactivity.
    WPAD_SetIdleTimeout(60); 
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
	
	// Init Game parameters
	initGame();
		
	// Init FreeType font engine
	GRRLIB_InitFreetype();
			  			
    // Init GRRLib graphics library
    GRRLIB_Init();
        	
	// Make screen black
	GRRLIB_FillScreen(0xFFFFFF);
    GRRLIB_Render();
	
	// Repeat forever
    while( !stopApplication )
	{			
		// draw Screen
		drawScreen();

		// Draw Wii Motion Pointers
		drawPointers();
		
		if (selectedMap!=prevSelectedMap)
		{
		    // Init Map
		   initGrid(selectedMap);
	
		   // Init monster
		   initMonsters();
	
		   // Init Weapons
		   initWeapons();
		   
		   prevSelectedMap=selectedMap;
		}
			
		// Render screen
		GRRLIB_Render();
	}
		  
	GRRLIB_Exit();
	
	destroyImages();
	
	trace.event(s_fn, 0,"%s %s Leaving", PROGRAM_NAME, PROGRAM_VERSION);
	trace.close();
	
	exit(0);
	return 0; 
}

// ------------------------------
// The end
// ------------------------------
