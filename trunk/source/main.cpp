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
**  10/12/2009 Version 0.40
**
**  NOT TESTED YET:
**  - Added Network thread.
**  	- Fetch latest available version information from internet.
**  	- Fetch latest release notes information from internet.
**  - Added Release Notes screen.
**
**  TESTED:
*   - Added wave lanch button on game board.
**  - Added game information panel.
**		- Added functionality to upgrade power, range and rate of weapon.
**  - Added continues monster wave principle.
**  - Added Map Select menu screen.
**  - Added Local highscore page.
**		- Added functionality to load/save local highscore from/to SD card.
**  - Added User Initials screen.
**		- Added functionality to load/save game settings from/to SD card.
**  - Added Credits screen.
**  - Added Help screen.
**  - Improve main menu screen.
**  - Added functionality to make screenshots (Press + button).
**  - Build game with devkitPPC r19 compiler.
**
**  03/12/2009 Version 0.30
**  - Added gameOver detection
**  - Improve memory usage (load classes dynamicly when needed)
**  - Added functionality that weapons can fire.
**  - Added more comment to source code.
**  - Added state machine functionality
**  - Added third game map.
**  - Added water and bridge map component.
**  - Added very basic main menu screen.
**  - Align monster movement on grid.
**  - Use libogc 1.8.1 library as Wii interface engine.
**  - Build game with devkitPPC r19 compiler.
**
**  29/11/2009 Version 0.20
**  - Added four WiiMote controllers support
**  - Added two game maps
**  - Added functionality to load a map from a xml file.
**  - Ported my GRRLIB freeType extention to work with GRRLIB 4.1.1
**  - Ported trace library from c to C++
**  - Use GRRLib v4.1.1 as graphic engine
**  - Use libfat v1.0.6 as disk access engine
**  - Use libmxml v2.6 library as xml engine
**  - Use libogc v1.8.0 library as Wii interface engine
**  - Build game with devkitPPC r19 compiler.
**
**  21/11/2009 Version 0.10 
**  - Started programming.
**  - Finding free graphics for game.
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
#include "Trace.h"
#include "Settings.h"
#include "HighScore.h"
#include "Monster.h"
#include "Weapon.h"
#include "Button.h"
#include "Pointer.h"
#include "Grid.h"
#include "Http.h"

// -----------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------

static u8 CalculateFrameRate();
void checkGameOver(void);
void checkNextWave(void);
void moveMonsters(void);
void moveWeapons(void);

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
  GRRLIB_texImg *panel1;
  
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
  GRRLIB_texImg *water1;
  GRRLIB_texImg *bridge1;
  
  GRRLIB_texImg *weapon1;
  GRRLIB_texImg *weapon2;
  GRRLIB_texImg *weapon3;
  GRRLIB_texImg *weapon4;
  GRRLIB_texImg *weapon5;
  GRRLIB_texImg *weapon6;
  GRRLIB_texImg *weapon7;

  GRRLIB_texImg *button1;
  GRRLIB_texImg *buttonFocus1;  
  GRRLIB_texImg *button2;
  GRRLIB_texImg *buttonFocus2;
  GRRLIB_texImg *button3;
  GRRLIB_texImg *buttonFocus3;
  GRRLIB_texImg *button4;
  GRRLIB_texImg *buttonFocus4;
  
  GRRLIB_texImg *pointer1;
  GRRLIB_texImg *pointer2;
  GRRLIB_texImg *pointer3; 
  GRRLIB_texImg *pointer4;
  
  GRRLIB_texImg *map1;
  GRRLIB_texImg *map2;
  GRRLIB_texImg *map3;
  
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

// Panel1 Image
extern const unsigned char     pic13data[];
extern int      pic13length;

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

// Water1 Image
extern const unsigned char     pic406data[];
extern int      pic406length;

// Bridge1 Image
extern const unsigned char     pic407data[];
extern int      pic407length;

// Weapon1 Image
extern const unsigned char     pic500data[];
extern int      pic500length;

// Weapon2 Image
extern const unsigned char     pic501data[];
extern int      pic501length;

// Weapon3 Image
extern const unsigned char     pic502data[];
extern int      pic502length;

// Weapon4 Image
extern const unsigned char     pic503data[];
extern int      pic503length;

// Weapon5 Image
extern const unsigned char     pic504data[];
extern int      pic504length;

// Weapon6 Image
extern const unsigned char     pic505data[];
extern int      pic505length;

// Weapon7 Image
extern const unsigned char     pic506data[];
extern int      pic506length;

// Button1 Image
extern const unsigned char     pic600data[];
extern int      pic600length;

// Button1Focus Image
extern const unsigned char     pic601data[];
extern int      pic601length;

// Button2 Image
extern const unsigned char     pic602data[];
extern int      pic602length;

// Button2Focus Image
extern const unsigned char     pic603data[];
extern int      pic603length;

// Button3 Image
extern const unsigned char     pic604data[];
extern int      pic604length;

// Button3Focus Image
extern const unsigned char     pic605data[];
extern int      pic605length;

// Button4 Image
extern const unsigned char     pic606data[];
extern int      pic606length;

// Button4Focus Image
extern const unsigned char     pic607data[];
extern int      pic607length;

// Map1 Sample Image
extern const unsigned char     pic700data[];
extern int      pic700length;

// Map2 Sample Image
extern const unsigned char     pic701data[];
extern int      pic701length;

// Map3 Sample Image
extern const unsigned char     pic702data[];
extern int      pic702length;


u32         *frameBuffer[1] 	= {NULL};
GXRModeObj  *rmode 				= NULL;
Mtx         GXmodelView2D;
int     	scrollIndex      	= 0;
bool    	scrollEnabled    	= false;

Game 		game;
Trace     	*trace;
Http		*http;
Settings  	*settings;
HighScore 	*highScore;
Grid      	*grid;
Monster   	*monsters[MAX_MONSTERS];
Pointer   	*pointers[MAX_POINTERS];
Weapon    	*weapons[MAX_WEAPONS];
Button    	*buttons[MAX_BUTTONS];

// -----------------------------------
// INIT METHODES
// -----------------------------------

void initImages(void)
{
   const char *s_fn="initImages";
   trace->event(s_fn,0,"enter");

   images.logo2=GRRLIB_LoadTexture( pic5data );
   images.logo3=GRRLIB_LoadTexture( pic6data );
   images.logo4=GRRLIB_LoadTexture( pic7data );
   images.logo5=GRRLIB_LoadTexture( pic8data );
   images.logo6=GRRLIB_LoadTexture( pic9data );
   
   images.logo=GRRLIB_LoadTexture( pic5data );
   GRRLIB_InitTileSet(images.logo, images.logo->w, 1, 0);
   
   images.background1=GRRLIB_LoadTexture( pic10data );
   images.background2=GRRLIB_LoadTexture( pic11data );
   images.panel1=GRRLIB_LoadTexture( pic13data );
	 
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
   images.water1=GRRLIB_LoadTexture( pic406data );	
   images.bridge1=GRRLIB_LoadTexture( pic407data );	

   images.weapon1=GRRLIB_LoadTexture( pic500data );
   images.weapon2=GRRLIB_LoadTexture( pic501data );
   images.weapon3=GRRLIB_LoadTexture( pic502data );
   images.weapon4=GRRLIB_LoadTexture( pic503data );
   images.weapon5=GRRLIB_LoadTexture( pic504data );
   images.weapon6=GRRLIB_LoadTexture( pic505data );
   images.weapon7=GRRLIB_LoadTexture( pic506data );
   
   images.button1=GRRLIB_LoadTexture( pic600data );
   images.buttonFocus1=GRRLIB_LoadTexture( pic601data );  
   images.button2=GRRLIB_LoadTexture( pic602data );
   images.buttonFocus2=GRRLIB_LoadTexture( pic603data );  
   images.button3=GRRLIB_LoadTexture( pic604data );
   images.buttonFocus3=GRRLIB_LoadTexture( pic605data );  
   images.button4=GRRLIB_LoadTexture( pic606data );
   images.buttonFocus4=GRRLIB_LoadTexture( pic607data );  
   
   images.map1=GRRLIB_LoadTexture( pic700data );  
   images.map2=GRRLIB_LoadTexture( pic701data );  
   images.map3=GRRLIB_LoadTexture( pic702data );  
   
   trace->event(s_fn,0,"leave [void]");
}

// Init some Weapons (Just for debugging)
void initWeapons(void)
{
    const char *s_fn="initWeapons";
    trace->event(s_fn,0,"enter");

    // Clear first array
    for( int i=0; i<MAX_WEAPONS; i++)
    {
      if (weapons[i]!=NULL)
	  {
	    trace->event(s_fn,0,"delete weapon %d",i);
		delete weapons[i];
		weapons[i]=NULL;
	  }
    }
    
	weapons[0]= new Weapon();
	weapons[0]->setImage(images.weapon1);
	weapons[0]->setX(200);
	weapons[0]->setY(180);
	weapons[0]->setPower(2);
	weapons[0]->setRange(50);
	weapons[0]->setRate(50);
	weapons[0]->setPowerPrice(10);
	weapons[0]->setRangePrice(10);
	weapons[0]->setRatePrice(10);
	weapons[0]->setSelected(true);
	weapons[0]->setIndex(0);
		
	weapons[1]= new Weapon();
	weapons[1]->setImage(images.weapon2);
	weapons[1]->setX(300);
	weapons[1]->setY(180);
	weapons[1]->setPower(4);
	weapons[1]->setRange(50);
	weapons[1]->setRate(100);
	weapons[1]->setPowerPrice(10);
	weapons[1]->setRangePrice(10);
	weapons[1]->setRatePrice(10);
	weapons[1]->setSelected(false);
	weapons[1]->setIndex(1);
	
	weapons[2]= new Weapon();
	weapons[2]->setImage(images.weapon3);
	weapons[2]->setX(400);
	weapons[2]->setY(180);
	weapons[2]->setPower(6);	
	weapons[2]->setRange(50);
	weapons[2]->setRate(150);
	weapons[2]->setPowerPrice(10);
	weapons[2]->setRangePrice(10);
	weapons[2]->setRatePrice(10);
	weapons[2]->setSelected(false);
	weapons[2]->setIndex(2);
	
	weapons[3]= new Weapon();
	weapons[3]->setImage(images.weapon4);
	weapons[3]->setX(200);
	weapons[3]->setY(400);
	weapons[3]->setPower(6);	
	weapons[3]->setRange(50);
	weapons[3]->setRate(150);
	weapons[3]->setPowerPrice(10);
	weapons[3]->setRangePrice(10);
	weapons[3]->setRatePrice(10);
	weapons[3]->setSelected(false);
	weapons[3]->setIndex(3);
	
	weapons[4]= new Weapon();
	weapons[4]->setImage(images.weapon5);
	weapons[4]->setX(300);
	weapons[4]->setY(400);
	weapons[4]->setPower(6);	
	weapons[4]->setRange(50);
	weapons[4]->setRate(150);
	weapons[4]->setPowerPrice(10);
	weapons[4]->setRangePrice(10);
	weapons[4]->setRatePrice(10);
	weapons[4]->setSelected(false);
	weapons[4]->setIndex(4);
	
	weapons[5]= new Weapon();
	weapons[5]->setImage(images.weapon7);
	weapons[5]->setX(400);
	weapons[5]->setY(400);
	weapons[5]->setPower(6);	
	weapons[5]->setRange(50);
	weapons[5]->setRate(150);
	weapons[5]->setPowerPrice(10);
	weapons[5]->setRangePrice(10);
	weapons[5]->setRatePrice(10);
	weapons[5]->setSelected(false);
	weapons[5]->setIndex(5);
	
	trace->event(s_fn,0,"leave [void]");
}

// Init monster
void initMonsters(bool clear)
{
	const char *s_fn="initMonsters";
	trace->event(s_fn,0,"enter");
   
	int delay=1;   
   
	if (clear)
	{
		trace->event(s_fn,0,"Clear monster array");
	
		// Clear monster array
		for( int i=0; i<MAX_MONSTERS; i++)	
		{
			if (monsters[i]!=NULL)
			{
				delete monsters[i];
				monsters[i]=NULL;
			}
		}
	}
	
	// Calculate how much monster will be in the wave
	int amount=3+(game.wave*2);
	if (amount>MAX_MONSTERS) amount=MAX_MONSTERS;
   
	for( int i=0; i<amount; i++ ) 
	{		
		trace->event(s_fn,0,"Init monster [%d]",i);
	
		// Find first empty place in monster array
		int id=0;
		while (monsters[id]!=NULL) 
		{
			if (++id>=(MAX_MONSTERS-1)) 
			{
				id=(MAX_MONSTERS-1);
				break;
			}
		}
		
		monsters[id]=new Monster();	  		
		monsters[id]->setIndex(id);
		monsters[id]->setDelay(delay);
			  	  
		// Calculate delay between two monsters.
		int delayOffset=game.wave*3;
		if (delayOffset>90) delayOffset=90;
		delay+=(100-delayOffset);

		// Each wave a new monster is introduced.
		int type = (int) (rand() % game.wave)+1;
		switch (type)
		{
			case 1 : 	monsters[id]->setImage(images.monster1);
						monsters[id]->setEnergy(5);
						monsters[id]->setStep(1);
						break;
					
			case 2 : 	monsters[id]->setImage(images.monster2);
						monsters[id]->setEnergy(10);
						monsters[id]->setStep(1);
						break;

			case 3 : 	monsters[id]->setImage(images.monster3);
						monsters[id]->setEnergy(15);
						monsters[id]->setStep(1);
						break;				 

			case 4 : 	monsters[id]->setImage(images.monster4);
						monsters[id]->setEnergy(20);
						monsters[id]->setStep(1);
						break;
				 
			case 5 : 	monsters[id]->setImage(images.monster5);
						monsters[id]->setEnergy(25);
						monsters[id]->setStep(1);						
						break;

			case 6 : 	monsters[id]->setImage(images.monster6);
						monsters[id]->setEnergy(30);
						monsters[id]->setStep(1);
						break;

			case 7 : 	monsters[id]->setImage(images.monster7);
						monsters[id]->setEnergy(35);
						monsters[id]->setStep(1);
						break;
			
			case 8 : 	monsters[id]->setImage(images.monster8);
						monsters[id]->setEnergy(40);
						monsters[id]->setStep(1);
						break;

			case 9 : 	monsters[id]->setImage(images.monster9);
						monsters[id]->setEnergy(45);
						monsters[id]->setStep(1);
						break;
			
			case 10: 	monsters[id]->setImage(images.monster10);
						monsters[id]->setEnergy(50);
						monsters[id]->setStep(1);
						break;

			case 11: 	monsters[id]->setImage(images.monster11);
						monsters[id]->setEnergy(60);
						monsters[id]->setStep(1);
						break;
	
			case 12: 	monsters[id]->setImage(images.monster12);
						monsters[id]->setEnergy(80);
						monsters[id]->setStep(1);
						break;

			case 13: 	monsters[id]->setImage(images.monster13);
						monsters[id]->setEnergy(100);
						monsters[id]->setStep(1);
						break;

			case 14: 	monsters[id]->setImage(images.monster14);
						monsters[id]->setEnergy(120);
						monsters[id]->setStep(1);
						break;

			case 15: 	monsters[id]->setImage(images.monster15);
						monsters[id]->setEnergy(140);
						monsters[id]->setStep(1);
						break;

			case 16: 	monsters[id]->setImage(images.monster16);
						monsters[id]->setEnergy(160);
						monsters[id]->setStep(1);
						break;
				 
			case 17: 	monsters[id]->setImage(images.monster17);
						monsters[id]->setEnergy(190);
						monsters[id]->setStep(1);
						break;
				 
			case 18: 	monsters[id]->setImage(images.monster18);
						monsters[id]->setEnergy(230);
						monsters[id]->setStep(1);
						break;

			case 19: 	monsters[id]->setImage(images.monster19);
						monsters[id]->setEnergy(250);
						monsters[id]->setStep(1);						
						break;
				 
			case 20: 	monsters[id]->setImage(images.monster20);
						monsters[id]->setEnergy(280);
						monsters[id]->setStep(1);
						break;
				 
			case 21: 	monsters[id]->setImage(images.monster21);
						monsters[id]->setEnergy(300);
						monsters[id]->setStep(1);
						break;

			case 22: 	monsters[id]->setImage(images.monster22);
						monsters[id]->setEnergy(350);
						monsters[id]->setStep(1);
						break;
				 
			case 23: 	monsters[id]->setImage(images.monster23);
						monsters[id]->setEnergy(400);
						monsters[id]->setStep(1);
						break;
					
			case 24: 	monsters[id]->setImage(images.monster24);
						monsters[id]->setEnergy(450);
						monsters[id]->setStep(1);
						break;
				 
			default: 	monsters[id]->setImage(images.monster25);
						monsters[id]->setEnergy(500);
						monsters[id]->setStep(1);
						break;
		}  
	}
	trace->event(s_fn,0,"leave [void]");
}

// Init Pointers
void initPointers(void)
{
   const char *s_fn="initPointers";
   trace->event(s_fn,0,"enter");

   // First clear array
   for( int i=0; i<MAX_POINTERS; i++)
   {
      if (pointers[i]!=NULL)
	  {
		trace->event(s_fn,0,"delete pointer %d",i);
		delete pointers[i];
		pointers[i]=NULL;
	  }
   }
      
   pointers[0] = new Pointer();   
   pointers[0]->setIndex(0);
   pointers[0]->setX(320);
   pointers[0]->setY(240);
   pointers[0]->setAngle(0);
   pointers[0]->setImage(images.pointer1);

   pointers[1] = new Pointer(); 
   pointers[1]->setIndex(1);
   pointers[1]->setX(320);
   pointers[1]->setY(240);
   pointers[1]->setAngle(0);
   pointers[1]->setImage(images.pointer2);

   pointers[2] = new Pointer(); 
   pointers[2]->setIndex(2);
   pointers[2]->setX(320);
   pointers[2]->setY(240);
   pointers[2]->setAngle(0);
   pointers[2]->setImage(images.pointer3);

   pointers[3] = new Pointer(); 
   pointers[3]->setIndex(3);
   pointers[3]->setX(340);
   pointers[3]->setY(240);
   pointers[3]->setAngle(0);
   pointers[3]->setImage(images.pointer4);	
      
   trace->event(s_fn,0,"leave [void]");
}

// Init Grid
void initGrid(int level)
{
    const char *s_fn="initGrid";
    trace->event(s_fn,0,"enter [level=%d]",level);
   
    grid = new Grid();
	grid->setImageRoad1(images.road1);
	grid->setImageRoad2(images.road2);
	grid->setImageRoad3(images.road3);
	grid->setImageRoad4(images.road4);
	grid->setImageRoad5(images.road5);
	grid->setImageWater(images.water1);
	grid->setImageBridge(images.bridge1);
	
	switch( level )
	{
		case 1: grid->setImageBase(images.base1);
				grid->create(GRID1_FILENAME);
				break;
			
		case 2: grid->setImageBase(images.base2);
				grid->create(GRID2_FILENAME);
				break;
				
		case 3: grid->setImageBase(images.base3);
				grid->create(GRID3_FILENAME);
				break;
	}

	trace->event(s_fn,0,"leave [void]");
}

void initButtons(void)
{
	const char *s_fn="initButtons";
	trace->event(s_fn,0,"enter");

	// First clear array
	for( int i=0; i<MAX_BUTTONS; i++)
	{
		if (buttons[i]!=NULL)
		{
			trace->event(s_fn,0,"delete button %d",i);
			delete buttons[i];
			buttons[i]=NULL;
		}
	}
   
	switch( game.stateMachine )	
	{			
		case stateMainMenu:
		{			
			// Play Button 
			buttons[6]=new Button();
			buttons[6]->setX(440);
			buttons[6]->setY(40);
			buttons[6]->setImageNormal(images.button2);
			buttons[6]->setImageFocus(images.buttonFocus2);
			buttons[6]->setLabel("Play");
			
			// HighScore Button 
			buttons[0]=new Button();
			buttons[0]->setX(440);
			buttons[0]->setY(80);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("High Score");
			
			// Help Button 
			buttons[1]=new Button();
			buttons[1]->setX(440);
			buttons[1]->setY(120);
			buttons[1]->setImageNormal(images.button2);
			buttons[1]->setImageFocus(images.buttonFocus2);
			buttons[1]->setLabel("Help");			

			// Credits Button 
			buttons[2]=new Button();
			buttons[2]->setX(440);
			buttons[2]->setY(160);
			buttons[2]->setImageNormal(images.button2);
			buttons[2]->setImageFocus(images.buttonFocus2);
			buttons[2]->setLabel("Credits");	

			// Release Notes Button 
			buttons[4]=new Button();
			buttons[4]->setX(440);
			buttons[4]->setY(200);
			buttons[4]->setImageNormal(images.button2);
			buttons[4]->setImageFocus(images.buttonFocus2);
			buttons[4]->setLabel("Release Notes");	
			
			// Sound Settings Button 
			buttons[3]=new Button();
			buttons[3]->setX(440);
			buttons[3]->setY(240);
			buttons[3]->setImageNormal(images.button2);
			buttons[3]->setImageFocus(images.buttonFocus2);
			buttons[3]->setLabel("Sound Settings");	

			// User initials Button 
			buttons[5]=new Button();
			buttons[5]->setX(440);
			buttons[5]->setY(280);
			buttons[5]->setImageNormal(images.button2);
			buttons[5]->setImageFocus(images.buttonFocus2);
			buttons[5]->setLabel("User initials");	
						
			// Exit HBC Button 
			buttons[7]=new Button();
			buttons[7]->setX(440);
			buttons[7]->setY(400);
			buttons[7]->setImageNormal(images.button2);
			buttons[7]->setImageFocus(images.buttonFocus2);
			buttons[7]->setLabel("Exit HBC");	
	 
			// Reset Wii Button 
			buttons[8]=new Button();
			buttons[8]->setX(440);
			buttons[8]->setY(440);
			buttons[8]->setImageNormal(images.button2);
			buttons[8]->setImageFocus(images.buttonFocus2);
			buttons[8]->setLabel("Reset Wii");	
		}
		break;
				
		case stateMapSelectMenu:
		{	
			// Button (Play Map1)
			buttons[0]=new Button();
			buttons[0]->setX(25);
			buttons[0]->setY(150);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Map1");
						
			// Button (Play Map2)
			buttons[1]=new Button();
			buttons[1]->setX(225);
			buttons[1]->setY(150);
			buttons[1]->setImageNormal(images.button2);
			buttons[1]->setImageFocus(images.buttonFocus2);
			buttons[1]->setLabel("Map2");
				
			// Button (Play Map3)
			buttons[2]=new Button();
			buttons[2]->setX(425);
			buttons[2]->setY(150);
			buttons[2]->setImageNormal(images.button2);
			buttons[2]->setImageFocus(images.buttonFocus2);
			buttons[2]->setLabel("Map3");
			
			// Button (Main Menu)
			buttons[3]=new Button();
			buttons[3]->setX(225);
			buttons[3]->setY(460);
			buttons[3]->setImageNormal(images.button2);
			buttons[3]->setImageFocus(images.buttonFocus2);
			buttons[3]->setLabel("Main Menu");
		}
		break;	
		
		case stateGame:
	    {
			// Power Upgrade Button
			buttons[0]=new Button();
			buttons[0]->setX(30);
			buttons[0]->setY(200);
			buttons[0]->setImageNormal(images.button1);
			buttons[0]->setImageFocus(images.buttonFocus1);
			buttons[0]->setLabel("");
			
			// Range Upgrade Button
			buttons[1]=new Button();
			buttons[1]->setX(30);
			buttons[1]->setY(270);
			buttons[1]->setImageNormal(images.button1);
			buttons[1]->setImageFocus(images.buttonFocus1);
			buttons[1]->setLabel("");

			// Rate Upgrade Button
			buttons[2]=new Button();
			buttons[2]->setX(30);
			buttons[2]->setY(340);
			buttons[2]->setImageNormal(images.button1);
			buttons[2]->setImageFocus(images.buttonFocus1);
			buttons[2]->setLabel("");
						
			// Rate Lanch Button
			buttons[3]=new Button();
			buttons[3]->setX(30);
			buttons[3]->setY(400);
			buttons[3]->setImageNormal(images.button1);
			buttons[3]->setImageFocus(images.buttonFocus1);
			buttons[3]->setLabel("Lanch");
			
			// Select previous weapon Button
			//buttons[3]=new Button();
			//buttons[3]->setX(25);
			//buttons[3]->setY(400);
			//buttons[3]->setImageNormal(images.button4);
			//buttons[3]->setImageFocus(images.buttonFocus4);
			//buttons[3]->setLabel("");

			// Select next weapon Button
			//buttons[4]=new Button();
			//buttons[4]->setX(55);
			//buttons[4]->setY(400);
			//buttons[4]->setImageNormal(images.button4);
			//buttons[4]->setImageFocus(images.buttonFocus4);
			//buttons[4]->setLabel("");
		}
		break;
		
		case stateLocalHighScore:
	    {
			// Next Button
			buttons[0]=new Button();
			buttons[0]->setX(225);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Next");	
		}
		break;
		
		case stateHelp:
		{
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(225);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");		
		}
		break;
		
		case stateCredits:
		{
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(225);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");	
		}
		break;

		case stateSoundSettings:
		{
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(225);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");	
		}
		break;
		
		case stateReleaseNotes:
		{
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(225);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");		
		}
		break;
		
		case stateUserSettings:
	    {
			// First letter + button 
			buttons[0]=new Button();
			buttons[0]->setX(100);
			buttons[0]->setY(150);
			buttons[0]->setImageNormal(images.button1);
			buttons[0]->setImageFocus(images.buttonFocus1);
			buttons[0]->setLabel("+");	

			// First letter - button 
			buttons[1]=new Button();
			buttons[1]->setX(100);
			buttons[1]->setY(295);
			buttons[1]->setImageNormal(images.button1);
			buttons[1]->setImageFocus(images.buttonFocus1);
			buttons[1]->setLabel("-");	

			// Second letter + button 
			buttons[2]=new Button();
			buttons[2]->setX(280);
			buttons[2]->setY(150);
			buttons[2]->setImageNormal(images.button1);
			buttons[2]->setImageFocus(images.buttonFocus1);
			buttons[2]->setLabel("+");	

			// second letter - button 
			buttons[3]=new Button();
			buttons[3]->setX(280);
			buttons[3]->setY(295);
			buttons[3]->setImageNormal(images.button1);
			buttons[3]->setImageFocus(images.buttonFocus1);
			buttons[3]->setLabel("-");	

			// Third letter + button 
			buttons[4]=new Button();
			buttons[4]->setX(460);
			buttons[4]->setY(150);
			buttons[4]->setImageNormal(images.button1);
			buttons[4]->setImageFocus(images.buttonFocus1);
			buttons[4]->setLabel("+");	

			// Third letter - button 
			buttons[5]=new Button();
			buttons[5]->setX(460);
			buttons[5]->setY(295);
			buttons[5]->setImageNormal(images.button1);
			buttons[5]->setImageFocus(images.buttonFocus1);
			buttons[5]->setLabel("-");
			
			// Main Menu Button
			buttons[6]=new Button();
			buttons[6]->setX(225);
			buttons[6]->setY(460);
			buttons[6]->setImageNormal(images.button2);
			buttons[6]->setImageFocus(images.buttonFocus2);
			buttons[6]->setLabel("Main Menu");	
		}
		break;	
	}
	trace->event(s_fn,0,"leave [void]");
}

// Init Network Module
void initNetwork(void)
{ 
   const char *s_fn="initNetwork";
   trace->event(s_fn,0,"enter");
   
   char userData1[MAX_LEN];
   char userData2[MAX_LEN];

   // Set userData1   		 
   memset(userData1,0x00,sizeof(userData1));
   sprintf(userData1,"%s=%s",PROGRAM_NAME,PROGRAM_VERSION);
		
   // Get userData2 
   memset(userData2,0x00,sizeof(userData2));
   sprintf(userData2,"appl=%s",PROGRAM_NAME);
	   
   http = new Http();
	   
   http->tcp_start_thread(PROGRAM_NAME, PROGRAM_VERSION, 
			ID1, URL1, 
			ID2, URL2, 
			ID3, URL3, 
			ID4, URL4, 
			URL_TOKEN, userData1, userData2);
   
   trace->event(s_fn,0,"leave [void]");
}

void initGame(void)
{
	const char *s_fn="initGame";
	
	// Open trace module
	trace = new Trace();
	trace->open(TRACE_FILENAME);
	trace->event(s_fn, 0,"%s %s Started", PROGRAM_NAME, PROGRAM_VERSION);
	
	trace->event(s_fn,0,"enter");
   
    // Set statemachine
	game.stateMachine=stateIntro1;
	game.prevStateMachine=stateNone;
	
	// Set event
	game.event=eventNone;
   
	game.wave1 = 0;
	game.wave2 = 0;
	
   	// Init Images
	initImages();
   
    // Init pointers
    initPointers();

	// Load Settings from SDCard	
	settings = new Settings();
	settings->load(SETTING_FILENAME);
	
	// Load Local Highscore
	highScore = new HighScore();
	highScore->load(HIGHSCORE_FILENAME);
	
	// Init network Thread
	initNetwork();
	
	trace->event(s_fn,0,"leave");
}
	
// -----------------------------------
// DRAW METHODES
// -----------------------------------

// Draw grid on screen
void drawGrid(void)
{
   grid->draw();   
}


// Draw grid on screen
void drawGridText(void)
{
   grid->text();   
}

// Draw pointers on screen
void drawPointers(void)
{
   for( int i=0; i<MAX_POINTERS; i++ ) 
   {
	  if (pointers[i]!=NULL) 
	  {
		pointers[i]->action();
		pointers[i]->draw();
	  }
   }
}

// Draw monsters on screen
void drawMonsters(void)
{
   for( int i=0; i<MAX_MONSTERS; i++ ) 
   {
	  if (monsters[i]!=NULL)
	  {
		monsters[i]->draw();
	  }
   }
}

// Draw monsters Text on screen
void drawMonstersText(void)
{
   for( int i=0; i<MAX_MONSTERS; i++ ) 
   {
	  if (monsters[i]!=NULL)
	  {
		monsters[i]->text();
	  }
   }
}

// Draw weapons on screen
void drawWeapons(void)
{
	for( int i=0; i<MAX_WEAPONS; i++ ) 
	{
		if (weapons[i]!=NULL)
		{
			weapons[i]->draw();
		}
	}
}

// Draw weapons Text on screen
void drawWeaponsText(void)
{
	for( int i=0; i<MAX_WEAPONS; i++ ) 
	{
		if (weapons[i]!=NULL)
		{
			weapons[i]->text();
		}
	}
}

// Draw buttons on screen
void drawButtons(void)
{
	for( int i=0; i<MAX_BUTTONS; i++ ) 
	{
		if (buttons[i]!=NULL)
		{
			buttons[i]->draw();
		}
	}
}

// Draw buttons Text on screen
void drawButtonsText(void)
{
	for( int i=0; i<MAX_BUTTONS; i++ ) 
	{
		if (buttons[i]!=NULL)
		{
			buttons[i]->text();
		}
	}
}

// Draw text on screen
void drawText(int x, int y, int type, const char *text)
{
   char tmp[MAX_LEN];
   memset(tmp,0x00,sizeof(tmp));
   
   if (text!=NULL)
   {    		
     strcpy(tmp, text);
	 
     switch (type)
     {  	
       case fontWelcome: 
	   {
		  GRRLIB_Printf2(x, y, tmp, 40, GRRLIB_WHITESMOKE); 
	   }
	   break;
 
       case fontTitle: 
	   {
	      if (x==0) x=320-((strlen(tmp)*34)/2);  
		  GRRLIB_Printf2(x, y, tmp, 72, GRRLIB_AQUA); 
	   }
	   break;
  	   
	   case fontSubTitle:
	   {
	      if (x==0) x=320-((strlen(tmp)*20)/2);
		  GRRLIB_Printf2(x, y, tmp, 30, GRRLIB_WHITESMOKE);          
	   }
	   break;
	   
	   case fontSubTitle2:
	   {
	      if (x==0) x=320-((strlen(tmp)*20)/2);
		  GRRLIB_Printf2(x, y, tmp, 30, GRRLIB_LIGHTRED);          
	   }
	   break;
	   	   
	   case fontParagraph:
	   {
	       if (x==0) x=320-((strlen(tmp)*10)/2);	   
		   GRRLIB_Printf2(x, y, tmp, 24, GRRLIB_WHITESMOKE);            
	   }
	   break;
	   	   
	   case fontNormal:
	   {
	       if (x==0) x=320-((strlen(tmp)*7)/2);
		   GRRLIB_Printf2(x, y, tmp, 18, GRRLIB_WHITESMOKE);            
	   }
	   break;
	         
	   case fontNew:
	   {
	       if (x==0) x=320-((strlen(tmp)*8)/2);	   
		   GRRLIB_Printf2(x, y, tmp, 22, GRRLIB_WHITESMOKE);            
	   }
	   break;
	   
	   case fontSpecial:
	   {
	       if (x==0) x=320-((strlen(tmp)*10)/2);
		   GRRLIB_Printf2(x, y, tmp, 10, GRRLIB_WHITESMOKE);            
	   }
	   break;
	   
	   case fontButton:
	   {
	       if (strlen(tmp)==1)
		   {
		      GRRLIB_Printf2(x+35, y, tmp, 24, GRRLIB_WHITESMOKE);            
		   }
		   else
		   {
		      GRRLIB_Printf2(x+20, y, tmp, 24, GRRLIB_WHITESMOKE);    
		   }		   
	   }
	   break;
	 }
   }
}

// Draw Game panel on screen
void drawGamePanel(void)
{
	int  xoffset=20;

	// Draw background
	GRRLIB_DrawImg(xoffset,0, images.panel1, 0, 1, 1, IMAGE_COLOR3 );
}
	
	
// Draw Game panel Text on screen
void drawGamePanelText(void)
{
	char tmp[MAX_LEN];
	int  ypos=YOFFSET;
	int  xoffset=20;
	
	GRRLIB_Printf2(20+xoffset, ypos,"SCORE", 18, GRRLIB_BLACK);	
	ypos+=20;	
	sprintf(tmp,"%06d", game.score); 
	GRRLIB_Printf2(20+xoffset, ypos, tmp, 16, GRRLIB_BLACK);

	ypos+=30;
	GRRLIB_Printf2(25+xoffset, ypos,"CASH", 18, GRRLIB_BLACK);	
	ypos+=20;
	sprintf(tmp,"$%04d", game.cash);
	GRRLIB_Printf2(25+xoffset, ypos, tmp, 16, GRRLIB_BLACK);

	ypos+=30;	
	GRRLIB_Printf2(25+xoffset, ypos,"WAVE", 18, GRRLIB_BLACK);	
	ypos+=20;
	sprintf(tmp,"%02d", game.wave); 
	GRRLIB_Printf2(40+xoffset, ypos, tmp, 16, GRRLIB_BLACK);

	ypos+=30;
	GRRLIB_Printf2(20+xoffset, ypos, "POWER", 18, GRRLIB_BLACK);	

	ypos+=70;
	GRRLIB_Printf2(20+xoffset, ypos, "RANGE", 18, GRRLIB_BLACK);

	ypos+=70;
	GRRLIB_Printf2(25+xoffset, ypos, "RATE", 18, GRRLIB_BLACK);
		
	if (weapons[game.weaponSelect]!=NULL)
	{
		sprintf(tmp,"$%d", weapons[game.weaponSelect]->getPowerPrice() );
		buttons[0]->setLabel(tmp);
		
		sprintf(tmp,"$%d", weapons[game.weaponSelect]->getRangePrice() );
		buttons[1]->setLabel(tmp);
		
		sprintf(tmp,"$%d", weapons[game.weaponSelect]->getRatePrice() );
		buttons[2]->setLabel(tmp);
	}
	  
	sprintf(tmp,"%d fps", CalculateFrameRate()); 
	drawText(20, 500, fontSpecial, tmp);
}

// draw screens
void drawScreen(void)
{ 	   	
	char tmp[MAX_LEN];
	int  ypos=YOFFSET;
		  
    switch( game.stateMachine )	
	{		   
	   case stateIntro1:
	   {
	      // Draw background
		  GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR );
		  
		  // Init text layer	  
          GRRLIB_initTexture();	
		  
		  sprintf(tmp,"%s", PROGRAM_NAME); 
		  drawText(20, ypos, fontWelcome,  tmp );
		  ypos+=60;
		  drawText(20, ypos, fontNormal,  "Created by wplaat"  );
		  ypos+=20;
		  drawText(20, ypos, fontNormal,  "http://www.plaatsoft.nl"  );
		  ypos+=350;
		  drawText(40, ypos, fontNormal,  "This software is open source and may be copied, distributed or modified"  );
		  ypos+=20;
		  drawText(60, ypos, fontNormal,  "under the terms of the GNU General Public License (GPL) version 2" );
		  ypos+=30;
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }	   
	   break;
	   
	   case stateIntro2:
	   {
		  unsigned int j;
		  
	      // Draw background
		  GRRLIB_DrawImg(0,0, images.background2, 0, 1, 1, IMAGE_COLOR );

		  // Draw Plaatsoft logo		 
   	      for(j=0;j<images.logo->h;j++)
		  {
             GRRLIB_DrawTile(((640-images.logo2->w)/2)+sin(game.wave1)*50, (((480-images.logo2->h)/2)-50)+j, images.logo, 0, 1, 1, IMAGE_COLOR,j );
             game.wave1+=0.02;
          }
		  game.wave2+=0.02;
          game.wave1=game.wave2;
		  
		  // Init text layer	  
          GRRLIB_initTexture();	
		  
		  ypos+=320;
		  drawText(0, ypos, fontParagraph,  "Please visit my website for more information." );
		  ypos+=40;
		  drawText(0, ypos, fontParagraph,  "http://www.plaatsoft.nl" );
			  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }	   
	   break;
	   	   
	   case stateIntro3:
	   {
		  // Draw backg
		  GRRLIB_DrawImg(0,0, images.logo3, 0, 0.95, 0.98, IMAGE_COLOR );
		  GRRLIB_DrawImg(310,0, images.logo4, 0, 0.95, 0.98, IMAGE_COLOR );
		  GRRLIB_DrawImg(0,240, images.logo5, 0, 0.95, 0.98, IMAGE_COLOR );
		  GRRLIB_DrawImg(310,240, images.logo6, 0, 0.95, 0.98, IMAGE_COLOR );
		  
          GRRLIB_DrawImg(350, 240, images.logo2, 0, 0.5, 0.5, IMAGE_COLOR );

		  // Init text layer	  
          GRRLIB_initTexture();	
		  
		  ypos+=390;
		  drawText(350, ypos, fontNormal,  "Some more Wii games developed"  );
		  ypos+=20;
		  drawText(400, ypos, fontNormal,  "by www.plaatsoft.nl"  );
			 
		  sprintf(tmp,"%d fps", CalculateFrameRate()); 
		  drawText(590, 500, fontSpecial, tmp); 
 
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }	   
	   break;
	 
		case stateMainMenu:
		{
		  const char *version;

		  // Draw background
		  GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
		  
		  // Draw Buttons
		  drawButtons();
			
		  // Init text layer	  
          GRRLIB_initTexture();
		  
		  sprintf(tmp,"%s v%s", PROGRAM_NAME, PROGRAM_VERSION); 
		  drawText(20, ypos, fontWelcome,  tmp );
		  ypos+=60;
		  sprintf(tmp,"%s", RELEASE_DATE); 
		  drawText(20, ypos, fontParagraph,  tmp );
	
		  version=http->tcp_get_version();
          if ( (version!=NULL) && (strlen(version)>0) && (strcmp(version,PROGRAM_VERSION)!=0) )
          {    
			 ypos+=275;
	         sprintf(tmp,"New version [v%s] is available.",version);
	         drawText(20, ypos, fontNew, tmp);
				 		
			 ypos+=20;	 			 
			 sprintf(tmp,"Check the release notes.");
	         drawText(20, ypos, fontNew, tmp);			 
          }  
		  
		  sprintf(tmp,"NETWORK THREAD: %s",http->tcp_get_state());
		  drawText(20, 485, fontSpecial, tmp);
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate()); 
		  drawText(20, 500, fontSpecial, tmp); 
		   
		  // Draw Button Text labels
		  drawButtonsText();
		  
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
		
		case stateMapSelectMenu:
		{
		  // Draw background
		  GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
		
		  // Draw Buttons
		  drawButtons();
		  
		  // Draw samples maps
		  GRRLIB_DrawImg(40,200, images.map1, 0, 1, 1, IMAGE_COLOR );
		  GRRLIB_DrawImg(230,200, images.map2, 0, 1, 1, IMAGE_COLOR );
		  GRRLIB_DrawImg(440,200, images.map3, 0, 1, 1, IMAGE_COLOR );
			  
		  // Init text layer	  
          GRRLIB_initTexture();

		  // Draw title
	      drawText(120, ypos, fontTitle, "Choose Map");	

		  // Draw Button Text labels
		  drawButtonsText();
		  
		  ypos+=435;	
		  sprintf(tmp,"%d fps", CalculateFrameRate()); 
		  drawText(20, 500, fontSpecial, tmp); 
	   		  
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
	
		case stateGame:
		{		  
		  moveMonsters();
		  moveWeapons();
		  
		  drawGrid();		  
		  drawMonsters();
		  drawWeapons();
		  drawGamePanel();		  
		  drawButtons();
		  
		  checkGameOver();
		  checkNextWave();
		  
		  // Init text layer	  
          GRRLIB_initTexture();
		  
		  drawGridText();	
		  drawMonstersText();
		  drawWeaponsText();
		  drawGamePanelText();
		  drawButtonsText();
		  
		  // Draw text layer on top of background 
		  GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
		
		case stateGameOver:
		{	  
		  drawGrid(); 
		  drawMonsters();
		  drawWeapons();
		  drawGamePanel();
			 
		  // Init text layer	  
          GRRLIB_initTexture();
 
		  drawGridText();	
 		  drawMonstersText();
		  drawWeaponsText();
		  drawGamePanelText();
			  
		  ypos+=225;	
		  
		  GRRLIB_Printf2(200, ypos, "GAME OVER", 60, GRRLIB_BLACK);
		 
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
		
		case stateLocalHighScore:
	    {
	      struct tm *local;
		  	  				   
          // Draw background
          GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
		  
		  // Draw buttons
	      drawButtons(); 
		  
		  // Init text layer	  
          GRRLIB_initTexture();
 
	      // Draw title
	      drawText(80, ypos, fontTitle, "Local High Score");	

          // Show Content
          ypos+=90;
		  drawText(60, ypos, fontParagraph, "TOP"  );
	      drawText(130, ypos, fontParagraph, "DATE"  );
	      drawText(320, ypos, fontParagraph, "SCORE" );
		  drawText(410, ypos, fontParagraph, "NAME"  );
		  drawText(500, ypos, fontParagraph, "WAVE" );
		  ypos+=10;
		  
          for (int i=0; i<MAX_LOCAL_HIGHSCORE; i++)
	      {
  	          // Only show highscore entries which contain data
			  if (highScore->getDate(i)!=0)
			  {
				ypos+=20;  
	    
				sprintf(tmp,"%02d", i+1);
				drawText(60, ypos, fontNormal, tmp);
			  
				local = localtime(highScore->getDate(i));
				sprintf(tmp,"%02d-%02d-%04d %02d:%02d:%02d", 
					local->tm_mday, local->tm_mon+1, local->tm_year+1900, 
					local->tm_hour, local->tm_min, local->tm_sec);
				drawText(130, ypos, fontNormal, tmp);
	   
				sprintf(tmp,"%05d", highScore->getScore(i));
				drawText(320, ypos, fontNormal, tmp);
	
				drawText(410, ypos, fontNormal, highScore->getName(i));
	  
				sprintf(tmp,"%02d", highScore->getWave(i));
				drawText(500, ypos, fontNormal, tmp);
			 }
		  }	
		  
		  // Draw Button Text labels
		  drawButtonsText();
		  
		  // Show FPS information
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
          // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);	 	   
	    }
	    break;

	    case stateHelp:
	    {	  
	      // Draw background
		  GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
		 
		  // Draw buttons
	      drawButtons(); 
		  
		  // Init text layer	  
          GRRLIB_initTexture();
 
		   // Show title
		  drawText(0, ypos, fontTitle, "Help");
          ypos+=100;
		  
		  drawText(0, ypos, fontParagraph, "Wii TowerDefense is an classic 2D action game. Protect ");
		  ypos+=25;
     	  drawText(0, ypos, fontParagraph, "your base with all kind of defense systems and kill");	
		  ypos+=25;
	      drawText(0, ypos, fontParagraph, "all the waves of enemies.");		
		
          ypos+=60;
	      drawText(0, ypos, fontParagraph, "Tip: You can control which music track is played during");
		  ypos+=25;
	      drawText(0, ypos, fontParagraph, "the game with the 1 and 2 button on your WiiMote!");
		  
		  ypos+=60;
	      drawText(0, ypos, fontParagraph, "Note: The global highscore contains the Top 40 of best");
		  ypos+=25;
	      drawText(0, ypos, fontParagraph, "internet players. Only one entry per player is showed.");	  

		  // Draw Button Text labels
		  drawButtonsText();
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
		  // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	    }
	    break;

	    case stateCredits:
	    {  
	      // Draw background
		  GRRLIB_DrawImg(0,0,images.background1, 0, 1.0, 1.0, IMAGE_COLOR2 );
		  
		  // Draw buttons
	      drawButtons(); 
		  
		  // Init text layer	  
          GRRLIB_initTexture();
		  
		  // Show title
		  drawText(220, ypos, fontTitle, "Credits");
          ypos+=90;
		  
		  // Show Content
	      drawText(0, ypos, fontParagraph, "GAME LOGIC ");
          ypos+=20;
	      drawText(0, ypos, fontNormal, "wplaat");

	      ypos+=30;
	      drawText(0, ypos, fontParagraph, "GAME GRAPHICS  ");
  	      ypos+=20;
	      drawText(0, ypos, fontNormal, "wplaat");
		  
	      ypos+=30;
	      drawText(0, ypos, fontParagraph, "MUSIC ");
	      ypos+=20;
	      drawText(0, ypos, fontNormal, "modarchive.org  ");

	      ypos+=30;
	      drawText(0, ypos, fontParagraph, "SOUND EFFECTS  ");
	      ypos+=20;
	      drawText(0, ypos, fontNormal, "wplaat");
  
  	      ypos+=30;
	      drawText(0, ypos, fontParagraph, "TESTERS");
	      ypos+=20;
	      drawText(0, ypos, fontNormal, "wplaat");	  
				  	  	
												
	      ypos+=30;
	      drawText(0, ypos, fontNormal,"Greetings to everybody in the Wii homebrew scene");
		  
		  // Draw Button Text labels
		  drawButtonsText();
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
		  // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }
	   break;
	   	   
	   case stateSoundSettings:
	   { 
	      // Draw background
		  GRRLIB_DrawImg(0,0,images.background1, 0, 1.0, 1.0, IMAGE_COLOR2 );
		
		  // Draw buttons
	      drawButtons(); 
		  
		  
	      // Init text layer	  
          GRRLIB_initTexture();
  
	      // Draw Sound icon
	      //GRRLIB_DrawImg((640/2)-128, ((480/2)-140)+yOffset, images.sound, angle, 1.4, 1.4, IMAGE_COLOR );
	
		  // Show title
		  drawText(100, ypos, fontTitle, "Sound Settings");
          ypos+=100;
		  
          // Draw content	
          drawText(0, ypos, fontParagraph, "Music Volume");	
	      ypos+=20;
          //GRRLIB_DrawImg(104,ypos,images.bar, 0, 1, 1, IMAGE_COLOR );
	      ypos+=10;
	      //GRRLIB_DrawImg(115+(musicVolume*40),ypos, images.barCursor, 0, 1, 1, IMAGE_COLOR );
  
          ypos+=80;
          drawText(0, ypos, fontParagraph, "Effects Volume" );
	      ypos+=20;	
	      //GRRLIB_DrawImg(104,ypos, images.bar, 0, 1, 1, IMAGE_COLOR );
	      ypos+=10;
	      //GRRLIB_DrawImg(115+(effectVolume*40),ypos,images.barCursor, 0, 1, 1, IMAGE_COLOR );
	
	      ypos+=70;
		  //sprintf(tmp,"  Music track [%d]", selectedMusic);
	      //drawText(0, ypos, fontParagraph, tmp);	
		  		  		
		  // Draw Button Text labels
		  drawButtonsText();
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
		  // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }
	   break;
	   
	   case stateReleaseNotes:
	   {
	      int  i=0;
		  int  len=0;
		  int  lineCount=0;
		  int  maxLines=0;
		  const char *buffer;
		  char text[MAX_BUFFER_SIZE];
		  
		  int startEntry;
		  int endEntry;
		  		  
		  // Fetch release notes from network thread
		  buffer=http->tcp_get_releasenote();
          if (buffer!=NULL) 
		  {
		     strncpy(text,buffer,MAX_BUFFER_SIZE);
			 len=strlen(text);
			 for (i=0;i<len;i++) if (text[i]=='\n') maxLines++;
		  }
		  
		  // Calculate start and end line.
		  if (maxLines<18)
		  {
		    startEntry=0;
			endEntry=maxLines;
			scrollEnabled=false;
		  }
		  else
		  {
			 startEntry=(((float) maxLines-18.0)/26.0)*(float)scrollIndex;
			 endEntry=startEntry+18;
			 scrollEnabled=true;
		  }
		   
	      // Draw background
		  GRRLIB_DrawImg(0,0,images.background1, 0, 1.0, 1.0, IMAGE_COLOR2 );

		  // Draw buttons
	      drawButtons(); 
		  
	      // Init text layer	  
          GRRLIB_initTexture();
		  
          // Draw scrollbar
		  if (scrollEnabled)
		  {
		    ypos=SCROLLBAR_Y_MIN;
            //GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
		    for (i=0; i<9; i++) 
		    {
		      ypos+=24;
		      //GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
		    }
		    ypos+=24;
		    //GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
		  }
		 
	      // Draw Title	
		  ypos=YOFFSET;
          drawText(100, ypos, fontTitle, "Release Notes");
          ypos+=80;
	      
		  if (len!=0)
		  {		  
		    int startpos=0;
  		    for (i=0; i<len; i++)
		    {
			  if (text[i]=='\n') 
			  {			   
			     text[i]=0x00;
				 
				 // Show only 17 lines on screen
			     if ((lineCount++)>endEntry) break;
			     if (lineCount>startEntry) 
				 {				   
			        ypos+=15;
				    sprintf(tmp,"%s",text+startpos);
			        drawText(40, ypos, fontNormal, tmp);	
				 }		
			     startpos=i+1;
		
		      }
		    }
		  }
		  else
		  {
		     ypos+=120;
			 drawText(0, ypos, fontParagraph, "No information available!" );	
		     ypos+=20;
			 drawText(0, ypos, fontParagraph, "Information could not be fetch from internet.");
		  }
		  
		  // Draw Button Text labels
		  drawButtonsText();
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
		  // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	   }
	   break;

	   case stateUserSettings:
	   {         	
	      // Draw background
		  GRRLIB_DrawImg(0,0,images.background1, 0, 1.0, 1.0, IMAGE_COLOR2 );
      	
		  // Draw buttons
	      drawButtons(); 
		  
	      // Init text layer	  
          GRRLIB_initTexture();
	
	      // Draw Title	
          drawText(150, ypos, fontTitle, "User Initials");
          ypos+=120;
		  
	      // Draw panels		 
		  GRRLIB_Rectangle(60, ypos, 100, 100, GRRLIB_BLACK, 1); 
		  GRRLIB_Rectangle(240, ypos, 100, 100, GRRLIB_BLACK, 1);
		  GRRLIB_Rectangle(420, ypos, 100, 100, GRRLIB_BLACK, 1);
      	  
		  ypos+=50;		  
		  // Draw initial characters
		  sprintf(tmp, "%c", settings->getFirstChar());
		  drawText(110, ypos, fontTitle, tmp);
		  sprintf(tmp, "%c", settings->getSecondChar());
		  drawText(300, ypos, fontTitle, tmp);
		  sprintf(tmp, "%c", settings->getThirdChar());
		  drawText(480, ypos, fontTitle, tmp);

		  ypos+=200;
	  	  drawText(0, ypos, fontParagraph, "This initials are used in the highscore area.");	
	     		  
		  // Draw Button Text labels
		  drawButtonsText();
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
				  
          // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);	
	   }
	   break;
	}
}

// -----------------------------------
// SUPPORT METHODES
// -----------------------------------

// Move monsters on screen
void moveMonsters(void)
{
   //const char *s_fn="moveMonsters";

   for( int i=0; i<MAX_MONSTERS; i++ ) 
   {
	  if (monsters[i]!=NULL)
	  {		
		if (monsters[i]->move())
		{
			// Monster has reach the final destination. Destroy it!
			game.monsterInBase++;
			
			delete monsters[i];
			monsters[i]=NULL;
		}
	  }
   }
}

// Move weapons on screen
void moveWeapons(void)
{
	for( int i=0; i<MAX_WEAPONS; i++ ) 
	{
		if (weapons[i]!=NULL)
		{
			//weapons[i]->move();
			weapons[i]->fire(monsters);
		}
	}
}

// Check if game is over!
void checkGameOver(void)
{
   if (game.monsterInBase>=10)
   {
		// Too many monster in Base 
		game.stateMachine=stateGameOver; 
		game.event=eventSaveHighScore;		
   }
}

void checkNextWave(void)
{		
	if (--game.waveCountDown>0)
	{
		// Check if there are any monster left. If not start next wave
		for (int i=0;i<MAX_MONSTERS;i++)
		{
			if (monsters[i]!=NULL)
			{
				return;
			}
		}
	}	
	
	// Lanch new monster wave;
	game.event=eventLanch;
}

void destroyImages(void)
{
   const char *s_fn="destroyImages";
   trace->event(s_fn,0,"enter");
   
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
   GRRLIB_FreeTexture(images.water1);
   GRRLIB_FreeTexture(images.bridge1);
   
   GRRLIB_FreeTexture(images.weapon1);
   GRRLIB_FreeTexture(images.weapon2);
   GRRLIB_FreeTexture(images.weapon3);
   GRRLIB_FreeTexture(images.weapon4);
   GRRLIB_FreeTexture(images.weapon5);
   GRRLIB_FreeTexture(images.weapon6);
   GRRLIB_FreeTexture(images.weapon7);
   	
   GRRLIB_FreeTexture(images.button2);
   GRRLIB_FreeTexture(images.buttonFocus2);
   GRRLIB_FreeTexture(images.button3);
   GRRLIB_FreeTexture(images.buttonFocus3);
   GRRLIB_FreeTexture(images.button4);
   GRRLIB_FreeTexture(images.buttonFocus4);
   
   GRRLIB_FreeTexture(images.map1);
   GRRLIB_FreeTexture(images.map2);
   GRRLIB_FreeTexture(images.map3);
   
   trace->event(s_fn,0,"leave");
}

void destroyObjects()
{
	// Destroy Weapons
	for( int i=0; i<MAX_WEAPONS; i++)
    {
		if (weapons[i]!=NULL)
		{
			delete weapons[i];
			weapons[i]=NULL;
		}
    }
	
	// Destroy Buttons
	for( int i=0; i<MAX_BUTTONS; i++)
    {
		if (buttons[i]!=NULL)
		{
			delete buttons[i];
			buttons[i]=NULL;
		}
    }
	
	// Destroy Monsters
	for( int i=0; i<MAX_MONSTERS; i++)
	{
		if (monsters[i]!=NULL)
		{
			delete monsters[i];
			monsters[i]=NULL;
		}
	}  
	
	// Destroy Pointers
	for( int i=0; i<MAX_POINTERS; i++)
	{
		if (pointers[i]!=NULL)
		{
			delete pointers[i];
			pointers[i]=NULL;
		}
	}	
	
	// Destroy Grid
	if (grid!=NULL)
	{
		delete grid;
	}
	
	// Destroy Trace
	if (trace!=NULL)
	{
		delete trace;
	}
}
	

// Calculate Video Frame Rate (Indication how game engine performs)
static u8 CalculateFrameRate(void) 
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

// Proces event changes
void processEvent()
{
	const char *s_fn="processEvent";
	    
    // If event is none return directly!
    if (game.event==eventNone) return;
  
	// Event state
	switch (game.event)
	{
		case eventLanch:
		{
			trace->event(s_fn,0,"event=eventLanch");	

			int count=0;
			for(int i=0;i<MAX_MONSTERS;i++)
			{
				if (monsters[i]==NULL) count++;
			}
			int amount=3+(game.wave*2);
			
			if (amount<count)
			{
				// Create next monster wave
				if (game.waveDelay>100) game.waveDelay-=100;
				game.waveCountDown=game.waveDelay;
				game.wave++;
				initMonsters(false);		
			}
		}
		break;
		
		case eventSaveHighScore:
		{				
			trace->event(s_fn,0,"event=eventSaveHighScore");
			
			// Store highscore
			char tmp[MAX_LEN];
			sprintf(tmp,"%c%c%c",settings->getFirstChar(), 
				settings->getSecondChar(), settings->getThirdChar());			
			highScore->setScore(tmp, game.wave, game.score);
			highScore->save(HIGHSCORE_FILENAME);
		}
		break;
		
		case eventWeaponPowerUpgrade:
		{
			trace->event(s_fn,0,"event=eventWeaponPowerUpgrade");			
			weapons[game.weaponSelect]->upgrade(0);
		}
		break;
				
		case eventWeaponRangeUpgrade:
		{ 			
			trace->event(s_fn,0,"event=eventWeaponRangeUpgrade");			
			weapons[game.weaponSelect]->upgrade(1);
		}
		break;
			
		case eventWeaponRateUpgrade:
		{ 
 			trace->event(s_fn,0,"event=eventWeaponRateUpgrade");
			weapons[game.weaponSelect]->upgrade(2);
		}
		break;			
	}
	
	// Clear event
	game.event=eventNone;
}


// Process state Machine change
void processStateMachine()
{
  const char *s_fn="processStateMachine";
	
  // If state is not changed return directly!
  if (game.prevStateMachine==game.stateMachine) return;
    
  // Process new state
  switch (game.stateMachine)
  {
    case stateIntro1:
	{
		trace->event(s_fn,0,"stateMachine=stateIntro1");
	}
	break;

	case stateIntro2:
	{
		trace->event(s_fn,0,"stateMachine=stateIntro2");
	}
	break;
	 
	case stateIntro3:
	{
		trace->event(s_fn,0,"stateMachine=stateIntro3");
	}
	break;
	 
	case stateMainMenu:
	{
		trace->event(s_fn,0,"stateMachine=stateMainMenu");
		
		// Init buttons
		initButtons();
	}
	break;

	case stateMapSelectMenu:
	{
		trace->event(s_fn,0,"stateMachine=stateMapSelectMenu");
		
		// Init buttons
		initButtons();	
	}
	break;
	
	case stateGame:
	{
		trace->event(s_fn,0,"stateMachine=stateGame");
	 
		// Init game variables
		game.score=0;
		game.cash=50;
		game.wave=1;
		game.monsterInBase=0;
		game.weaponSelect=0;
			
		// Start delay between to waves is +/- 25 seconds.
		game.waveDelay = 2500;
		game.waveCountDown=game.waveDelay;
		
		// Init buttons
		initButtons();	
		
		// Init Map
		initGrid(game.selectedMap);
	
		// Init monster
		initMonsters(true);
	
		// Init Weapons
		initWeapons();
	}
	break;
	
	case stateGameOver:
	{
		trace->event(s_fn,0,"stateMachine=stateGameOver");
		
		game.size=0;
	}
	break;
	
	case stateReleaseNotes:
	{
		trace->event(s_fn,0,"stateMachine=stateReleaseNotes");
		
		// Init buttons
		initButtons();		
	}
	break;
	
	case stateLocalHighScore:
	{
		trace->event(s_fn,0,"stateMachine=stateLocalHighScore");
		
		// Init buttons
		initButtons();		
	}
	break;
	
	case stateCredits:
	{
		trace->event(s_fn,0,"stateMachine=stateCredits");
		
		// Init buttons
		initButtons();	
	}
	break;
	 
	case stateSoundSettings:
	{
		trace->event(s_fn,0,"stateMachine=stateSoundSettings");
		
		// Init buttons
		initButtons();	
	}
	break;
	
	case stateHelp:
	{
		trace->event(s_fn,0,"stateMachine=stateHelp");
		
		// Init buttons
		initButtons();		
	}
	break;
	   	
	case stateUserSettings:
	{
		trace->event(s_fn,0,"stateMachine=stateUserSettings");
		
		// Init buttons
		initButtons();	
	}
	break;	 
  }
  
  // Store new state
  game.prevStateMachine=game.stateMachine;
}

// -----------------------------------
// main
// -----------------------------------

int main(void)
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
	
    // Init Fat
    fatInitDefault();

	// Init Game variables and objects
	initGame();
		
	// Init FreeType font engine
	GRRLIB_InitFreetype();
			  			
    // Init GRRLib graphics library
    GRRLIB_Init();
        	
	// Make screen black
	GRRLIB_FillScreen(0xFFFFFF);
    GRRLIB_Render();
	
	// Repeat forever
    while( game.stateMachine != stateQuit )
	{			
		// Process state machine
		processStateMachine();
		
		// Process event
		processEvent();
				
		// draw Screen
		drawScreen();

		// Draw Wii Motion Pointers
		drawPointers();
			
		// Render screen
		GRRLIB_Render();
	}
		  
	GRRLIB_Exit();
	
	// Stop network thread
	http->tcp_stop_thread();
	
	// Stop rumble
	WPAD_Rumble(0,0);
		
	// Stop music
	//MODPlay_Stop(&snd1);
	
	// Destroy all Images
	destroyImages();
	
	// Trace last line
	trace->event(s_fn, 0,"%s %s Leaving", PROGRAM_NAME, PROGRAM_VERSION);
	
	// Close trace file.
	trace->close();
	
	// Destroy all objects
	destroyObjects();
	
	// Exit to loader
	exit(0);
}

// ------------------------------
// The end
// ------------------------------