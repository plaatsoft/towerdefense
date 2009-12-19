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
**  WISHLIST:
**  - Realtime monsters animation on map select page.
**  - Improve weapon graphics
**  - Improve graphical fire effect!
**  - Add rotating sound icon on sound setting screen.
**  - Snap weapons to (32x32) grid!
**  - Multi language support
**
**  19/12/2009 Version 0.46
**  - Improve "Game Over" screen. 
**  - Improve game information panel on screen. 
**  - Increase user initials for 3 to 6 digits. 
**  - Improve scroll bar button design.
**  - Balance sound effect volume.
**  - Build game with devkitPPC r19 compiler.
**
**  18/12/2009 Version 0.45
**  - Load map images (sprites) directly from SdCard.
**  - Improve objects cleanup when stopping game.
**  - Added Google analistics network calls.
**  - Added map 4, 5 and 6.
**  - Show when weapon upgrade is not possible anymore!
**  - Build game with devkitPPC r19 compiler.
**
**  17/12/2009 Version 0.44
**  - Bugfix: Protect button access against NULL pointers.
**  - Added reload bar move weapon.
**  - Added remaining energy bar below the base.
**  - Optimise game core to improve Frame-Per-Seconds.
**  - Cleanup not used images and source code.
**  - BugFix: Solve crash when game is over.
**  - Rendering realtime grid examples on map select screen.
**  - Build game with devkitPPC r19 compiler.
**
**  16/12/2009 Version 0.43
**  - Added help screen two and three.
**  - Limit weapon upgrade levels. 
**  - Added WiiMote rumble support when pointer is on a button. 
**  - Improve button pointer detection area. 
**  - Added "Quit Game" screen. 
**  - Bugfix: Placing weapons under the information panel is not allowed anymore.
**  - Build game with devkitPPC r19 compiler.
**
**  15/12/2009 Version 0.42
**  - Added Network thread.
**  	- Fetch latest available version information from internet.
**  	- Fetch latest release notes information from internet.
**      - Fetch Global and today highscore from internet
**  	- Added functionality to store game score on internet.
**  	- Added Release Notes screen.
**  - Added today and global Highscore screen.
**  - Added release notes screen.
**  - Build game with devkitPPC r19 compiler.
**
**  14/12/2009 Version 0.41
**  - Added dynamic weapon placement on the gameboard
**  - Added bonus cash (score) when wave is cleared
**  - Improve Game Over and Next Wave information on screen
**  - Added "coming soon" teaser for Map 4, 5 and 6.
**  - Improve map2 base location.
**  - Build game with devkitPPC r19 compiler.
**
**  13/12/2009 Version 0.40
**  - Added basic weapon fire graphic effect 
**  - Added event engine.
**  - Added music & effect control screen.
**  	- Added nigh tracks background music.
**  	- Added game sound effects.
**  - Added wave lanch button on game board.
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
**  06/12/2009 Version 0.30
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
**  - Started programming in C++.
**  - Finding free graphics for game.
**  - Setup basic directory structure for new project.
**  - Store source code in Google code SVN repository.
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
#include "Sound.h"
#include "Monster.h"
#include "Weapon.h"
#include "Button.h"
#include "Pointer.h"
#include "Grid.h"
#include "http.h"

// -----------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------

static u8 CalculateFrameRate();
void checkGameOver(void);
void checkNextWave(void);
void moveMonsters(void);
void moveWeapons(void);
GRRLIB_texImg *getNewWeaponImage(int type);
int  getWeaponPrice(int type);
void loadTodayHighScore(char *buffer);
void loadGlobalHighScore(char *buffer);

// -----------------------------------------------------------
// TYPEDEF
// -----------------------------------------------------------

typedef struct 
{
  // png + jpg Image index     
  GRRLIB_texImg *intro1;
  GRRLIB_texImg *intro2;
  GRRLIB_texImg *intro3;
  
  GRRLIB_texImg *soundIcon;
  
  GRRLIB_texImg *logo2;
  GRRLIB_texImg *logo;
  
  GRRLIB_texImg *background1;
  GRRLIB_texImg *background2;
  GRRLIB_texImg *bar;
  GRRLIB_texImg *barCursor;  
  GRRLIB_texImg *scrollbar;
  GRRLIB_texImg *scrollTop;
  GRRLIB_texImg *scrollMiddle;
  GRRLIB_texImg *scrollBottom;
  
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
    
  GRRLIB_texImg *weapon1;
  GRRLIB_texImg *weapon2;
  GRRLIB_texImg *weapon3;
  GRRLIB_texImg *weapon4;
  GRRLIB_texImg *weapon5;
  GRRLIB_texImg *weapon6;

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
  
  GRRLIB_texImg *map4;
} 
image;

image images;

typedef struct
{
   time_t dt;
   char   score[MAX_LEN];
   char   name[MAX_LEN];
   char   location[MAX_LEN];
}
topscore;

topscore todayHighScore[MAX_TODAY_HIGHSCORE+1];
topscore globalHighScore[MAX_GLOBAL_HIGHSCORE+1];

// -----------------------------------------------------------
// VARIABLES
// -----------------------------------------------------------

// sound Image
extern const unsigned char     pic1data[];
extern int      pic1length;

// logo2 Image
extern const unsigned char     pic5data[];
extern int      pic5length;

// Background1 Image
extern const unsigned char     pic10data[];
extern int      pic10length;

// Background2 Image
extern const unsigned char     pic11data[];
extern int      pic11length;

// Bar Image
extern const unsigned char     pic14data[];
extern int      pic14length;

// Bar_cursor Image
extern const unsigned char     pic15data[];
extern int      pic15length;

// Scrollbar image
extern const unsigned char     pic33data[];
extern const int      pic33length;

// ScrollTop image
extern const unsigned char     pic34data[];
extern const int      pic34length;

// ScrollMiddle image
extern const unsigned char     pic35data[];
extern const int      pic35length;

// scrollBottom image
extern const unsigned char     pic36data[];
extern const int      pic36length;



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


u32         *frameBuffer[1] 	= {NULL};
GXRModeObj  *rmode 				= NULL;
Mtx         GXmodelView2D;
int     	maxTodayHighScore  	= 0;
int     	maxGlobalHighScore 	= 0;

Game 		game;
Trace     	*trace;
Settings  	*settings;
HighScore 	*highScore;
Grid      	*grids[MAX_GRIDS];
Sound      	*sound;
Monster   	*monsters[MAX_MONSTERS];
Pointer   	*pointers[MAX_POINTERS];
Weapon    	*weapons[MAX_WEAPONS];
Button    	*buttons[MAX_BUTTONS];

// -----------------------------------
// Destroy METHODES
// -----------------------------------

void destroyWeapons(void)
{
	const char *s_fn="destroyWeapons";
	trace->event(s_fn,0,"enter");
	
	// Destroy all Weapons
	for( int i=0; i<MAX_WEAPONS; i++)
    {
		if (weapons[i]!=NULL)
		{
			delete weapons[i];
			trace->event(s_fn,0,"delete weapon %d",i);
			weapons[i]=NULL;
		}
    }
	
	trace->event(s_fn,0,"leave");
}

void destroyButtons(void)
{
	const char *s_fn="destroyButtons";
	trace->event(s_fn,0,"enter");
	
	// Destroy all Buttons
	for( int i=0; i<MAX_BUTTONS; i++)
    {
		if (buttons[i]!=NULL)
		{
			delete buttons[i];
			trace->event(s_fn,0,"delete button %d",i);
			buttons[i]=NULL;
		}
    }	
	trace->event(s_fn,0,"leave");
}

void destroyMonsters()
{
	const char *s_fn="clearMonsters";
	trace->event(s_fn,0,"enter");
	
	// Clear monster array
	for( int i=0; i<MAX_MONSTERS; i++)	
	{
		if (monsters[i]!=NULL)
		{
			delete monsters[i];
			trace->event(s_fn,0,"delete monster %d",i);
			monsters[i]=NULL;
		}
	}
	trace->event(s_fn,0,"leave");
}

void destroyPointers(void)
{
	const char *s_fn="destroyPointers";
	trace->event(s_fn,0,"enter");
	
	// Destroy Pointers
	for( int i=0; i<MAX_POINTERS; i++)
	{
		if (pointers[i]!=NULL)
		{
			delete pointers[i];
			trace->event(s_fn,0,"delete pointer %d",i);
			pointers[i]=NULL;
		}
	}	
	
	trace->event(s_fn,0,"leave");
}

void destroyGrids(void)
{
	const char *s_fn="destroyGrids";
	trace->event(s_fn,0,"enter");
	
	// Destroy Grid
	for( int i=0; i<MAX_GRIDS; i++)
	{
		if (grids[i]!=NULL)
		{
			delete grids[i];
			trace->event(s_fn,0,"delete grid %d",i);
			grids[i]=NULL;
		}
	}
	
	trace->event(s_fn,0,"leave");
}

void destroySound(void)
{
	const char *s_fn="destroySound";
	trace->event(s_fn,0,"enter");
  
	// Destroy Sound
	if (sound!=NULL)
	{
		delete sound;
		trace->event(s_fn,0,"delete sound");
		sound=NULL;
	}	
	trace->event(s_fn,0,"leave");
}

void destroyHighScore(void)
{
	const char *s_fn="destroyHighScore";
	trace->event(s_fn,0,"enter");
	
	// Destroy Highscore
	if (highScore!=NULL)
	{
		delete highScore;
		trace->event(s_fn,0,"delete highScore");
		highScore=NULL;
	}
	
	trace->event(s_fn,0,"leave");
}

void destroySettings(void)
{
	const char *s_fn="destroySettings";
	trace->event(s_fn,0,"enter");
	
	// Destroy Settings
	if (settings!=NULL)
	{
		delete settings;
		trace->event(s_fn,0,"delete settings");
		settings=NULL;
	}
	
	trace->event(s_fn,0,"leave");
}

void destroyTrace(void)
{	
	// Destroy Trace
	if (trace!=NULL)
	{
		delete trace;
		trace=NULL;
	}
}

// -----------------------------------
// INIT METHODES
// -----------------------------------

void initTodayHighScore(void)
{
	const char *s_fn="initTodayHighScore";
	trace->event(s_fn,0,"enter");
   
	// Init today highscore memory
	for(int i=0; i<MAX_TODAY_HIGHSCORE; i++)
	{
		todayHighScore[i].score[0]=0x00;
		todayHighScore[i].dt=0;
		todayHighScore[i].name[0]=0x00;
		todayHighScore[i].location[0]=0x00;
	} 
	trace->event(s_fn,0,"leave [void]");
}

void initGlobalHighScore(void)
{
	const char *s_fn="initGlobalHighScore";	
	trace->event(s_fn,0,"enter");
    
	// Init global highscore memory
	for(int i=0; i<MAX_GLOBAL_HIGHSCORE; i++)
	{
		globalHighScore[i].score[0]=0x00;
		globalHighScore[i].dt=0;
		globalHighScore[i].name[0]=0x00;
		globalHighScore[i].location[0]=0x00;
	} 
  
	trace->event(s_fn,0,"leave [void]");
}

void initImages(void)
{
	const char *s_fn="initImages";
	trace->event(s_fn,0,"enter");

	images.soundIcon=GRRLIB_LoadTexture( pic1data );

	images.logo2=GRRLIB_LoadTexture( pic5data );
	images.logo=GRRLIB_LoadTexture( pic5data );
	GRRLIB_InitTileSet(images.logo, images.logo->w, 1, 0);
   
	images.background1=GRRLIB_LoadTexture( pic10data );
	images.background2=GRRLIB_LoadTexture( pic11data );
   
	images.bar=GRRLIB_LoadTexture( pic14data );
	images.barCursor=GRRLIB_LoadTexture( pic15data );
   
	images.scrollbar=GRRLIB_LoadTexture(pic33data);
	images.scrollTop=GRRLIB_LoadTexture( pic34data);
	images.scrollMiddle=GRRLIB_LoadTexture( pic35data);
	images.scrollBottom=GRRLIB_LoadTexture( pic36data);
   
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
   
	images.weapon1=GRRLIB_LoadTexture( pic500data );
	images.weapon2=GRRLIB_LoadTexture( pic501data );
	images.weapon3=GRRLIB_LoadTexture( pic502data );
	images.weapon4=GRRLIB_LoadTexture( pic503data );
	images.weapon5=GRRLIB_LoadTexture( pic504data );
	images.weapon6=GRRLIB_LoadTexture( pic505data );
   
	images.button1=GRRLIB_LoadTexture( pic600data );
	images.buttonFocus1=GRRLIB_LoadTexture( pic601data );  
	images.button2=GRRLIB_LoadTexture( pic602data );
	images.buttonFocus2=GRRLIB_LoadTexture( pic603data );  
	images.button3=GRRLIB_LoadTexture( pic604data );
	images.buttonFocus3=GRRLIB_LoadTexture( pic605data );  
	images.button4=GRRLIB_LoadTexture( pic606data );
	images.buttonFocus4=GRRLIB_LoadTexture( pic607data );  
     
	trace->event(s_fn,0,"leave [void]");
}

	
// Init monster
void initMonsters(bool special)
{
	const char *s_fn="initMonsters";
	trace->event(s_fn,0,"enter");
   
	int delay=1;   
   
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
		
		if (!special)
		{
			// Set monster in selected grid (Game screen behalvior)
			monsters[id]->setGrid(game.selectedMap);
		}
		else
		{
		    // Move monster over random grids (Map Select screen behalvior)
			int grid = (int) (rand() % MAX_GRIDS)+1;
			monsters[id]->setGrid(grid);
		}
			  	  
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
      
   pointers[0] = new Pointer();   
   pointers[0]->setIndex(0);
   pointers[0]->setX(320);
   pointers[0]->setY(240);
   pointers[0]->setAngle(0);
   pointers[0]->setImage(images.pointer1);
   pointers[0]->setIndex(0);

   pointers[1] = new Pointer(); 
   pointers[1]->setIndex(1);
   pointers[1]->setX(320);
   pointers[1]->setY(240);
   pointers[1]->setAngle(0);
   pointers[1]->setImage(images.pointer2);
   pointers[1]->setIndex(1);

   pointers[2] = new Pointer(); 
   pointers[2]->setIndex(2);
   pointers[2]->setX(320);
   pointers[2]->setY(240);
   pointers[2]->setAngle(0);
   pointers[2]->setImage(images.pointer3);
   pointers[2]->setIndex(2);

   pointers[3] = new Pointer(); 
   pointers[3]->setIndex(3);
   pointers[3]->setX(340);
   pointers[3]->setY(240);
   pointers[3]->setAngle(0);
   pointers[3]->setImage(images.pointer4);	
   pointers[3]->setIndex(3);
      
   trace->event(s_fn,0,"leave [void]");
}

// Init Grid 1 until grid 3
void initGrid1(void)
{
    const char *s_fn="initGrid";
    trace->event(s_fn,0,"enter");

	for (int i=0; i<3; i++)
	{
		grids[i] = new Grid();
		grids[i]->setIndex(i);
	
		switch( i )
		{
			case 0: grids[i]->create(GRID1_DIRECTORY);
					break;
			
			case 1: grids[i]->create(GRID2_DIRECTORY);
					break;
				
			case 2: grids[i]->create(GRID3_DIRECTORY);
					break;
		}
	}
	trace->event(s_fn,0,"leave [void]");
}

// Init Grid 4 until Grid 6
void initGrid2(void)
{
    const char *s_fn="initGrid";
    trace->event(s_fn,0,"enter");

	for (int i=3; i<MAX_GRIDS; i++)
	{
		grids[i] = new Grid();
		grids[i]->setIndex(i);
	
		switch( i )
		{
			case 3: grids[i]->create(GRID4_DIRECTORY);
					break;
					
			case 4: grids[i]->create(GRID5_DIRECTORY);
					break;
					
			case 5: grids[i]->create(GRID6_DIRECTORY);
					break;
		}
	}
	trace->event(s_fn,0,"leave [void]");
}

void initButtons(void)
{
	const char *s_fn="initButtons";
	trace->event(s_fn,0,"enter");

	// First destroy existing buttons
	destroyButtons();
   
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
			buttons[6]->setColor(IMAGE_COLOR);
			
			// HighScore Button 
			buttons[0]=new Button();
			buttons[0]->setX(440);
			buttons[0]->setY(80);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("High Score");
			buttons[0]->setColor(IMAGE_COLOR);
			
			// Help Button 
			buttons[1]=new Button();
			buttons[1]->setX(440);
			buttons[1]->setY(120);
			buttons[1]->setImageNormal(images.button2);
			buttons[1]->setImageFocus(images.buttonFocus2);
			buttons[1]->setLabel("Help");			
			buttons[1]->setColor(IMAGE_COLOR);

			// Credits Button 
			buttons[2]=new Button();
			buttons[2]->setX(440);
			buttons[2]->setY(160);
			buttons[2]->setImageNormal(images.button2);
			buttons[2]->setImageFocus(images.buttonFocus2);
			buttons[2]->setLabel("Credits");	
			buttons[2]->setColor(IMAGE_COLOR);

			// Release Notes Button 
			buttons[4]=new Button();
			buttons[4]->setX(440);
			buttons[4]->setY(200);
			buttons[4]->setImageNormal(images.button2);
			buttons[4]->setImageFocus(images.buttonFocus2);
			buttons[4]->setLabel("Release Notes");	
			buttons[4]->setColor(IMAGE_COLOR);
			
			// Sound Settings Button 
			buttons[3]=new Button();
			buttons[3]->setX(440);
			buttons[3]->setY(240);
			buttons[3]->setImageNormal(images.button2);
			buttons[3]->setImageFocus(images.buttonFocus2);
			buttons[3]->setLabel("Sound Settings");	
			buttons[3]->setColor(IMAGE_COLOR);

			// User initials Button 
			buttons[5]=new Button();
			buttons[5]->setX(440);
			buttons[5]->setY(280);
			buttons[5]->setImageNormal(images.button2);
			buttons[5]->setImageFocus(images.buttonFocus2);
			buttons[5]->setLabel("User initials");	
			buttons[5]->setColor(IMAGE_COLOR);
						
			// Exit HBC Button 
			buttons[7]=new Button();
			buttons[7]->setX(440);
			buttons[7]->setY(400);
			buttons[7]->setImageNormal(images.button2);
			buttons[7]->setImageFocus(images.buttonFocus2);
			buttons[7]->setLabel("Exit HBC");	
			buttons[7]->setColor(IMAGE_COLOR);
	 
			// Reset Wii Button 
			buttons[8]=new Button();
			buttons[8]->setX(440);
			buttons[8]->setY(440);
			buttons[8]->setImageNormal(images.button2);
			buttons[8]->setImageFocus(images.buttonFocus2);
			buttons[8]->setLabel("Reset Wii");	
			buttons[8]->setColor(IMAGE_COLOR);
		}
		break;
				
		case stateMapSelectMenu:
		{	
			// Button (Play Map1)
			buttons[0]=new Button();
			buttons[0]->setX(40);
			buttons[0]->setY(250);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Map1");
			buttons[0]->setColor(IMAGE_COLOR);
						
			// Button (Play Map2)
			buttons[1]=new Button();
			buttons[1]->setX(240);
			buttons[1]->setY(250);
			buttons[1]->setImageNormal(images.button2);
			buttons[1]->setImageFocus(images.buttonFocus2);
			buttons[1]->setLabel("Map2");
			buttons[1]->setColor(IMAGE_COLOR);
				
			// Button (Play Map3)
			buttons[2]=new Button();
			buttons[2]->setX(440);
			buttons[2]->setY(250);
			buttons[2]->setImageNormal(images.button2);
			buttons[2]->setImageFocus(images.buttonFocus2);
			buttons[2]->setLabel("Map3");
			buttons[2]->setColor(IMAGE_COLOR);
			
			// Button (Play Map4)
			buttons[3]=new Button();
			buttons[3]->setX(40);
			buttons[3]->setY(410);
			buttons[3]->setImageNormal(images.button2);
			buttons[3]->setImageFocus(images.buttonFocus2);
			buttons[3]->setLabel("Map4");
			buttons[3]->setColor(IMAGE_COLOR);
						
			// Button (Play Map5)
			buttons[4]=new Button();
			buttons[4]->setX(240);
			buttons[4]->setY(410);
			buttons[4]->setImageNormal(images.button2);
			buttons[4]->setImageFocus(images.buttonFocus2);
			buttons[4]->setLabel("Map5");
			buttons[4]->setColor(IMAGE_COLOR);
				
			// Button (Play Map6)
			buttons[5]=new Button();
			buttons[5]->setX(440);
			buttons[5]->setY(410);
			buttons[5]->setImageNormal(images.button2);
			buttons[5]->setImageFocus(images.buttonFocus2);
			buttons[5]->setLabel("Map6");
			buttons[5]->setColor(IMAGE_COLOR);
			
			// Button (Main Menu)
			buttons[6]=new Button();
			buttons[6]->setX(240);
			buttons[6]->setY(460);
			buttons[6]->setImageNormal(images.button2);
			buttons[6]->setImageFocus(images.buttonFocus2);
			buttons[6]->setLabel("Main Menu");
			buttons[6]->setColor(IMAGE_COLOR);
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
			buttons[0]->setColor(IMAGE_COLOR);
			
			// Scrollbar button 
			buttons[1]=new Button();
			buttons[1]->setX(SCROLLBAR_x);
			buttons[1]->setY(SCROLLBAR_Y_MIN);
			buttons[1]->setImageNormal(images.scrollbar);
			buttons[1]->setImageFocus(images.scrollbar);
			buttons[1]->setLabel("");
			buttons[1]->setColor(IMAGE_COLOR);
		}
		break;
		
		case stateTodayHighScore:
	    {
			// Next Button
			buttons[0]=new Button();
			buttons[0]->setX(225);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Next");	
			buttons[0]->setColor(IMAGE_COLOR);
			
			// Scrollbar button 
			buttons[1]=new Button();
			buttons[1]->setX(SCROLLBAR_x);
			buttons[1]->setY(SCROLLBAR_Y_MIN);
			buttons[1]->setImageNormal(images.scrollbar);
			buttons[1]->setImageFocus(images.scrollbar);
			buttons[1]->setLabel("");
			buttons[1]->setColor(IMAGE_COLOR);
		}
		break;
		
		case stateGlobalHighScore:
	    {
			// Next Button
			buttons[0]=new Button();
			buttons[0]->setX(225);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");	
			buttons[0]->setColor(IMAGE_COLOR);
			
			// Scrollbar button 
			buttons[1]=new Button();
			buttons[1]->setX(SCROLLBAR_x);
			buttons[1]->setY(SCROLLBAR_Y_MIN);
			buttons[1]->setImageNormal(images.scrollbar);
			buttons[1]->setImageFocus(images.scrollbar);
			buttons[1]->setLabel("");
			buttons[1]->setColor(IMAGE_COLOR);
		}
		break;
		
		case stateHelp1:
		{
			// Next Button
			buttons[0]=new Button();
			buttons[0]->setX(240);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Next");	
			buttons[0]->setColor(IMAGE_COLOR);	
		}
		break;
		
		case stateHelp2:
		{
			// Next Button
			buttons[0]=new Button();
			buttons[0]->setX(240);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Next");	
			buttons[0]->setColor(IMAGE_COLOR);	
		}
		break;
		
		case stateHelp3:
		{
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(240);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");	
			buttons[0]->setColor(IMAGE_COLOR);	
		}
		break;
		
		case stateCredits:
		{
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(240);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");	
			buttons[0]->setColor(IMAGE_COLOR);
		}
		break;

		case stateReleaseNotes:
		{
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(240);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");		
			buttons[0]->setColor(IMAGE_COLOR);
			
			// Scrollbar button 
			buttons[1]=new Button();
			buttons[1]->setX(SCROLLBAR_x);
			buttons[1]->setY(SCROLLBAR_Y_MIN);
			buttons[1]->setImageNormal(images.scrollbar);
			buttons[1]->setImageFocus(images.scrollbar);
			buttons[1]->setLabel("");
			buttons[1]->setColor(IMAGE_COLOR);
		}
		break;
		
		case stateSoundSettings:
		{
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(240);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");	
			buttons[0]->setColor(IMAGE_COLOR);
			
			// Music Volume - button 
			buttons[1]=new Button();
			buttons[1]->setX(20);
			buttons[1]->setY(135+YOFFSET);
			buttons[1]->setImageNormal(images.button1);
			buttons[1]->setImageFocus(images.buttonFocus1);
			buttons[1]->setLabel("-");	
			buttons[1]->setColor(IMAGE_COLOR);
			
			// Music Volume + button 
			buttons[2]=new Button();
			buttons[2]->setX(540);
			buttons[2]->setY(130+YOFFSET);
			buttons[2]->setImageNormal(images.button1);
			buttons[2]->setImageFocus(images.buttonFocus1);
			buttons[2]->setLabel("+");	
			buttons[2]->setColor(IMAGE_COLOR);
			
			// Effect Volume - button 
			buttons[3]=new Button();
			buttons[3]->setX(20);
			buttons[3]->setY(230+YOFFSET);
			buttons[3]->setImageNormal(images.button1);
			buttons[3]->setImageFocus(images.buttonFocus1);
			buttons[3]->setLabel("-");	
			buttons[3]->setColor(IMAGE_COLOR);
			
			// Effect Volume + button 
			buttons[4]=new Button();
			buttons[4]->setX(540);
			buttons[4]->setY(230+YOFFSET);
			buttons[4]->setImageNormal(images.button1);
			buttons[4]->setImageFocus(images.buttonFocus1);
			buttons[4]->setLabel("+");	
			buttons[4]->setColor(IMAGE_COLOR);
			
			// Music track - button 
			buttons[5]=new Button();
			buttons[5]->setX(140);
			buttons[5]->setY(310+YOFFSET);
			buttons[5]->setImageNormal(images.button1);
			buttons[5]->setImageFocus(images.buttonFocus1);
			buttons[5]->setLabel("-");	
			buttons[5]->setColor(IMAGE_COLOR);
		
			// Music track + button 
			buttons[6]=new Button();
			buttons[6]->setX(420);
			buttons[6]->setY(310+YOFFSET);
			buttons[6]->setImageNormal(images.button1);
			buttons[6]->setImageFocus(images.buttonFocus1);
			buttons[6]->setLabel("+");	
			buttons[6]->setColor(IMAGE_COLOR);
		}
		break;
				
		case stateUserSettings:
	    {
			int xpos=35;
			
			// Main Menu Button
			buttons[0]=new Button();
			buttons[0]->setX(240);
			buttons[0]->setY(460);
			buttons[0]->setImageNormal(images.button2);
			buttons[0]->setImageFocus(images.buttonFocus2);
			buttons[0]->setLabel("Main Menu");	
			buttons[0]->setColor(IMAGE_COLOR);
			
			// First letter + button 
			buttons[1]=new Button();
			buttons[1]->setX(xpos);
			buttons[1]->setY(150);
			buttons[1]->setImageNormal(images.button1);
			buttons[1]->setImageFocus(images.buttonFocus1);
			buttons[1]->setLabel("+");	
			buttons[1]->setColor(IMAGE_COLOR);

			// First letter - button 
			buttons[2]=new Button();
			buttons[2]->setX(xpos);
			buttons[2]->setY(295);
			buttons[2]->setImageNormal(images.button1);
			buttons[2]->setImageFocus(images.buttonFocus1);
			buttons[2]->setLabel("-");	
			buttons[2]->setColor(IMAGE_COLOR);

			// Second letter + button 
			xpos+=80;
			buttons[3]=new Button();
			buttons[3]->setX(xpos);
			buttons[3]->setY(150);
			buttons[3]->setImageNormal(images.button1);
			buttons[3]->setImageFocus(images.buttonFocus1);
			buttons[3]->setLabel("+");	
			buttons[3]->setColor(IMAGE_COLOR);

			// second letter - button 
			buttons[4]=new Button();
			buttons[4]->setX(xpos);
			buttons[4]->setY(295);
			buttons[4]->setImageNormal(images.button1);
			buttons[4]->setImageFocus(images.buttonFocus1);
			buttons[4]->setLabel("-");	
			buttons[4]->setColor(IMAGE_COLOR);

			// Third letter + button 
			xpos+=80;
			buttons[5]=new Button();
			buttons[5]->setX(xpos);
			buttons[5]->setY(150);
			buttons[5]->setImageNormal(images.button1);
			buttons[5]->setImageFocus(images.buttonFocus1);
			buttons[5]->setLabel("+");	
			buttons[5]->setColor(IMAGE_COLOR);

			// Third letter - button 
			buttons[6]=new Button();
			buttons[6]->setX(xpos);
			buttons[6]->setY(295);
			buttons[6]->setImageNormal(images.button1);
			buttons[6]->setImageFocus(images.buttonFocus1);
			buttons[6]->setLabel("-");
			buttons[6]->setColor(IMAGE_COLOR);		

			// Fourth letter + button 
			xpos+=80;
			buttons[7]=new Button();
			buttons[7]->setX(xpos);
			buttons[7]->setY(150);
			buttons[7]->setImageNormal(images.button1);
			buttons[7]->setImageFocus(images.buttonFocus1);
			buttons[7]->setLabel("+");	
			buttons[7]->setColor(IMAGE_COLOR);

			// Fourth letter - button 
			buttons[8]=new Button();
			buttons[8]->setX(xpos);
			buttons[8]->setY(295);
			buttons[8]->setImageNormal(images.button1);
			buttons[8]->setImageFocus(images.buttonFocus1);
			buttons[8]->setLabel("-");
			buttons[8]->setColor(IMAGE_COLOR);		
			
			// Fifth letter + button 
			xpos+=80;
			buttons[9]=new Button();
			buttons[9]->setX(xpos);
			buttons[9]->setY(150);
			buttons[9]->setImageNormal(images.button1);
			buttons[9]->setImageFocus(images.buttonFocus1);
			buttons[9]->setLabel("+");	
			buttons[9]->setColor(IMAGE_COLOR);

			// Fifth letter - button 
			buttons[10]=new Button();
			buttons[10]->setX(xpos);
			buttons[10]->setY(295);
			buttons[10]->setImageNormal(images.button1);
			buttons[10]->setImageFocus(images.buttonFocus1);
			buttons[10]->setLabel("-");
			buttons[10]->setColor(IMAGE_COLOR);	
			
			// Sixth letter + button 
			xpos+=80;
			buttons[11]=new Button();
			buttons[11]->setX(xpos);
			buttons[11]->setY(150);
			buttons[11]->setImageNormal(images.button1);
			buttons[11]->setImageFocus(images.buttonFocus1);
			buttons[11]->setLabel("+");	
			buttons[11]->setColor(IMAGE_COLOR);

			// Sixth letter - button 
			buttons[12]=new Button();
			buttons[12]->setX(xpos);
			buttons[12]->setY(295);
			buttons[12]->setImageNormal(images.button1);
			buttons[12]->setImageFocus(images.buttonFocus1);
			buttons[12]->setLabel("-");
			buttons[12]->setColor(IMAGE_COLOR);
			
		}
		break;	
		
		case stateGame:
	    {									
			int ypos=70;
			
			// New Wave lanch Button
			buttons[0]=new Button();
			buttons[0]->setX(10+game.panelXOffset);
			buttons[0]->setY(ypos+game.panelYOffset);
			buttons[0]->setImageNormal(images.button3);
			buttons[0]->setImageFocus(images.buttonFocus3);
			buttons[0]->setLabel("");
			buttons[0]->setColor(IMAGE_COLOR3);
			
			// Power Upgrade Button
			ypos+=150;
			buttons[1]=new Button();
			buttons[1]->setX(10+game.panelXOffset);
			buttons[1]->setY(ypos+game.panelYOffset);
			buttons[1]->setImageNormal(images.button3);
			buttons[1]->setImageFocus(images.buttonFocus3);
			buttons[1]->setLabel("");
			buttons[1]->setColor(IMAGE_COLOR3);
			
			// Range Upgrade Button
			ypos+=60;
			buttons[2]=new Button();
			buttons[2]->setX(10+game.panelXOffset);
			buttons[2]->setY(ypos+game.panelYOffset);
			buttons[2]->setImageNormal(images.button3);
			buttons[2]->setImageFocus(images.buttonFocus3);
			buttons[2]->setLabel("");
			buttons[2]->setColor(IMAGE_COLOR3);

			// Rate Upgrade Button
			ypos+=60;
			buttons[3]=new Button();
			buttons[3]->setX(10+game.panelXOffset);
			buttons[3]->setY(ypos+game.panelYOffset);
			buttons[3]->setImageNormal(images.button3);
			buttons[3]->setImageFocus(images.buttonFocus3);
			buttons[3]->setLabel("");
			buttons[3]->setColor(IMAGE_COLOR3);
								
			// Select previous weapon Button
			ypos+=60;
			buttons[4]=new Button();
			buttons[4]->setX(10+game.panelXOffset);
			buttons[4]->setY(ypos+game.panelYOffset);
			buttons[4]->setImageNormal(images.button4);
			buttons[4]->setImageFocus(images.buttonFocus4);
			buttons[4]->setLabel("<");
			buttons[4]->setColor(IMAGE_COLOR3);

			// Select next weapon Button
			buttons[5]=new Button();
			buttons[5]->setX(66+game.panelXOffset);
			buttons[5]->setY(ypos+game.panelYOffset);
			buttons[5]->setImageNormal(images.button4);
			buttons[5]->setImageFocus(images.buttonFocus4);
			buttons[5]->setLabel(">");
			buttons[5]->setColor(IMAGE_COLOR3);
								
			// Select next weapon Button
			buttons[6]=new Button();
			buttons[6]->setX(33+game.panelXOffset);
			buttons[6]->setY(400+game.panelYOffset);
			buttons[6]->setImageNormal(getNewWeaponImage(game.weaponType));
			buttons[6]->setImageFocus(getNewWeaponImage(game.weaponType));
			buttons[6]->setLabel("");			
			buttons[6]->setColor(IMAGE_COLOR);
		}
		break;
	
		case stateGameQuit:	
		{
			// Yes button 
			buttons[0]=new Button();
			buttons[0]->setX(230);
			buttons[0]->setY(270);
			buttons[0]->setImageNormal(images.button3);
			buttons[0]->setImageFocus(images.buttonFocus3);
			buttons[0]->setLabel("YES");	
			buttons[0]->setColor(IMAGE_COLOR3);
			
			// No button 
			buttons[1]=new Button();
			buttons[1]->setX(330);
			buttons[1]->setY(270);
			buttons[1]->setImageNormal(images.button3);
			buttons[1]->setImageFocus(images.buttonFocus3);
			buttons[1]->setLabel("NO");	
			buttons[1]->setColor(IMAGE_COLOR3);		
		}
		break;
		
		case stateGameOver:	
		{
			// Retry button 
			buttons[0]=new Button();
			buttons[0]->setX(230);
			buttons[0]->setY(270);
			buttons[0]->setImageNormal(images.button3);
			buttons[0]->setImageFocus(images.buttonFocus3);
			buttons[0]->setLabel("RETRY" );	
			buttons[0]->setColor(IMAGE_COLOR3);
			
			// Quit button 
			buttons[1]=new Button();
			buttons[1]->setX(330);
			buttons[1]->setY(270);
			buttons[1]->setImageNormal(images.button3);
			buttons[1]->setImageFocus(images.buttonFocus3);
			buttons[1]->setLabel("QUIT");	
			buttons[1]->setColor(IMAGE_COLOR3);		
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
	 
   tcp_init_layer();
    
   tcp_start_thread(PROGRAM_NAME, PROGRAM_VERSION, 
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
	game.panelXOffset=20;
	game.angle = 0;
	game.alfa = 0;
				
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
	
	// Init Sound (Start play first mode file)
	sound = new Sound();
	sound->setMusicVolume(settings->getMusicVolume());
	sound->setEffectVolume(settings->getEffectVolume());	
	
	initTodayHighScore();
	initGlobalHighScore();
	
	// Init network Thread
	initNetwork();
		
	trace->event(s_fn,0,"leave");
}
	
// -----------------------------------
// DRAW METHODES
// -----------------------------------

// Draw grid on screen
void drawGrid()
{
    switch (game.selectedMap)
    {
		case 0: grids[0]->draw(0,0,1);   
			    break;
				
		case 1: grids[1]->draw(0,0,1);   
			    break;
				
		case 2: grids[2]->draw(0,0,1);   
			    break;
				
		case 3: grids[3]->draw(0,0,1);   
			    break;
				
		case 4: grids[4]->draw(0,0,1);   
			    break;
				
		case 5: grids[5]->draw(0,0,1);   
			    break;
	}				
}


// Draw grid on screen
void drawGridText()
{
    switch (game.selectedMap)
    {
		case 0: grids[0]->text();   
				break;
				
		case 1: grids[1]->text();   
				break;
				
		case 2: grids[2]->text();   
				break;
				
		case 3: grids[3]->text();   
				break;
				
		case 4: grids[4]->text();   
				break;
				
		case 5: grids[5]->text();   
				break;
	}
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
		monsters[i]->draw(0,0,1);
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
void drawButtons()
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
void drawButtonsText(int offset)
{
	for( int i=0; i<MAX_BUTTONS; i++ ) 
	{
		if (buttons[i]!=NULL)
		{
			buttons[i]->text(offset);
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
				
// Draw score panel on screen
void drawGamePanel1(void)
{
	// Draw panel
	GRRLIB_Rectangle(game.panelXOffset, 0, 100, 124, GRRLIB_BLACK_TRANS, 1);
}
		
// Draw Game panel on screen
void drawGamePanel2(void)
{
	// Draw panel
	GRRLIB_Rectangle(game.panelXOffset, 134, 100, 144, GRRLIB_BLACK_TRANS, 1);
}

// Draw weapon upgrade/build panel on screen
void drawGamePanel3(void)
{
	// Draw panel
	GRRLIB_Rectangle(game.panelXOffset, 290, 100, 182, GRRLIB_BLACK_TRANS, 1);
}


// Draw wave text panel on screen
void drawGamePanelText1(void)
{
	char tmp[MAX_LEN];
	int  ypos=10;
	
	// General info + control
	GRRLIB_Printf2(25+game.panelXOffset, ypos+game.panelYOffset,"WAVE", 18, GRRLIB_WHITESMOKE);	
	ypos+=15;
	sprintf(tmp,"%02d", game.wave); 
	GRRLIB_Printf2(40+game.panelXOffset, ypos+game.panelYOffset, tmp, 16, GRRLIB_WHITESMOKE);	
	ypos+=25;
	GRRLIB_Printf2(22+game.panelXOffset, ypos+game.panelYOffset, "LANCH", 18, GRRLIB_WHITESMOKE);
	
	// Set button label values
	sprintf(tmp,"      %d", game.waveCountDown/25 );
	if (buttons[0]!=NULL) buttons[0]->setLabel(tmp);	
}


// Draw score/cash text panel on screen
void drawGamePanelText2(void)
{
	char tmp[MAX_LEN];
	int  ypos=110;
	
	GRRLIB_Printf2(20+game.panelXOffset, ypos+game.panelYOffset,"SCORE", 18, GRRLIB_WHITESMOKE);	
	ypos+=15;	
	sprintf(tmp,"%06d", game.score); 
	GRRLIB_Printf2(20+game.panelXOffset, ypos+game.panelYOffset, tmp, 16, GRRLIB_WHITESMOKE);
	ypos+=25;
	GRRLIB_Printf2(25+game.panelXOffset, ypos+game.panelYOffset,"CASH", 18, GRRLIB_WHITESMOKE);	
	ypos+=15;
	sprintf(tmp,"$%04d", game.cash);
	GRRLIB_Printf2(25+game.panelXOffset, ypos+game.panelYOffset, tmp, 16, GRRLIB_WHITESMOKE);
}


// Draw Weapon upgrade/build text game panel on screen
void drawGamePanelText3(void)
{
	char power[MAX_LEN];
	char range[MAX_LEN];
	char rate[MAX_LEN];
	
	int  ypos=190;
	
	// Upgrade information + control
	GRRLIB_Printf2(20+game.panelXOffset, ypos+game.panelYOffset, "POWER", 18, GRRLIB_WHITESMOKE);	
	ypos+=60;
	GRRLIB_Printf2(20+game.panelXOffset, ypos+game.panelYOffset, "RANGE", 18, GRRLIB_WHITESMOKE);
	ypos+=60;
	GRRLIB_Printf2(30+game.panelXOffset, ypos+game.panelYOffset, "RATE", 18, GRRLIB_WHITESMOKE);
	
	// Build information + control
	ypos+=60;
	GRRLIB_Printf2(28+game.panelXOffset, ypos+game.panelYOffset, "BUILD", 18, GRRLIB_WHITESMOKE);
		
	if (weapons[game.weaponSelect]!=NULL)
	{
		// Get upgrade prices of selected weapon.
		if (weapons[game.weaponSelect]->isPowerUpgradeble())
		{
			sprintf(power,"$%d", weapons[game.weaponSelect]->getPowerPrice() );		
		}
		else
		{
			sprintf(power,"MAX");
		}
		
		if (weapons[game.weaponSelect]->isRangeUpgradeble())
		{
			sprintf(range,"$%d", weapons[game.weaponSelect]->getRangePrice() );		
		}
		else
		{
			sprintf(range,"MAX");
		}
		
		if (weapons[game.weaponSelect]->isRateUpgradeble())
		{
			sprintf(rate,"$%d", weapons[game.weaponSelect]->getRatePrice() );
		}
		else
		{
			sprintf(rate,"MAX");
		}
	}
	else
	{
		// No weapon selected yet!
		strcpy(power,"");
		strcpy(range,"");
		strcpy(rate,"");
	}
		

	if (buttons[1]!=NULL) buttons[1]->setLabel(power);
	if (buttons[2]!=NULL) buttons[2]->setLabel(range);
	if (buttons[3]!=NULL) buttons[3]->setLabel(rate);
	
	// Set button 
	if (buttons[6]!=NULL)
	{
		if (game.cash>=getWeaponPrice(game.weaponType))
		{
			// Weapon normal
			buttons[6]->setColor(IMAGE_COLOR);
		}
		else
		{
			// Weapon Transparent (Not for sale)
			buttons[6]->setColor(IMAGE_COLOR3);
		}
		buttons[6]->setImageNormal(getNewWeaponImage(game.weaponType));
		buttons[6]->setImageFocus(getNewWeaponImage(game.weaponType));
	}
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
	   	   
		case stateMainMenu:
		{
		  char *version=NULL;

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
	
		  version=tcp_get_version();
          if ( (version!=NULL) && (strlen(version)>0) && (strcmp(version,PROGRAM_VERSION)!=0) )
          {    
			 ypos+=235;
	         sprintf(tmp,"New version [v%s] is available.",version);
	         drawText(20, ypos, fontNew, tmp);
				 		
			 ypos+=20;	 			 
			 sprintf(tmp,"Check the release notes.");
	         drawText(20, ypos, fontNew, tmp);			 
          }  
		  
		  char *state=NULL;
		  state=tcp_get_state();
		  
		  sprintf(tmp,"NETWORK THREAD: %s",state);
		  drawText(20, 485, fontSpecial, tmp);
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate()); 
		  drawText(20, 500, fontSpecial, tmp); 
		   
		  // Draw Button Text labels
		  drawButtonsText(0);
		  
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
		  grids[0]->draw(60,135,5); 
		  grids[1]->draw(260,135,5); 
		  grids[2]->draw(460,135,5);
			
		  grids[3]->draw(60,300,5); 
		  grids[4]->draw(260,300,5); 
		  grids[5]->draw(460,300,5);
		   
		  // Draw some moving monsters on the sample maps
		  /*for( int i=0; i<MAX_MONSTERS; i++ ) 
		  {
			 if (monsters[i]!=NULL)
			 {
				switch (monsters[i]->getGrid())
				{
					case 0: monsters[i]->draw(60,300,5);
							monsters[i]->move();
							break;
							
					case 1: monsters[i]->draw(260,300,5);
							monsters[i]->move();
							break;
							
					case 2: monsters[i]->draw(460,300,5);
							monsters[i]->move();
							break;
				}
			 }
		  }*/
	  
		  // Init text layer	  
          GRRLIB_initTexture();

		  // Draw title
	      drawText(120, ypos, fontTitle, "Choose Map");	

		  // Draw Button Text labels
		  drawButtonsText(0);
		  
		  ypos+=435;	
		  sprintf(tmp,"%d fps", CalculateFrameRate()); 
		  drawText(20, 500, fontSpecial, tmp); 
	   		  
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
	
		case stateLocalHighScore:
	    {
	      struct tm *local;
		  int startEntry;
		  int endEntry;
		  		  
		  if (highScore->getAmount()<15)
		  {
		    startEntry=0;
			endEntry=highScore->getAmount();
		  }
		  else
		  {
			 startEntry=(((float) highScore->getAmount()-15.0)/26.0)*(float)game.scrollIndex;
			 endEntry=startEntry+15;
		  }
				   
          // Draw background
          GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
		  
		  // Draw scrollbar
		  ypos=SCROLLBAR_Y_MIN;
          GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
		  for (int i=0; i<9; i++) 
		  {
		     ypos+=24;
		     GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
		  }
		  ypos+=24;
		  GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
		  		  
		  // Draw buttons
	      drawButtons(); 
		  
		  // Init text layer	  
          GRRLIB_initTexture();
 
	      // Draw title
		  ypos=YOFFSET;
	      drawText(80, ypos, fontTitle, "Local High Score");	

          // Show Content
          ypos+=90;
		  drawText(60, ypos, fontParagraph, "TOP"  );
	      drawText(130, ypos, fontParagraph, "DATE"  );
	      drawText(320, ypos, fontParagraph, "SCORE" );
		  drawText(410, ypos, fontParagraph, "NAME"  );
		  drawText(500, ypos, fontParagraph, "WAVE" );
		  ypos+=10;
		  
		  for (int i=startEntry; i<endEntry; i++)
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
		  drawButtonsText(0);
		  
		  // Show FPS information
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
          // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);	 	   
	    }
	    break;

		case stateTodayHighScore:
	    {	      
	      struct tm *local;
		  int startEntry;
		  int endEntry;
		  		  
		  if (maxTodayHighScore<15)
		  {
		    startEntry=0;
			endEntry=maxTodayHighScore;
		  }
		  else
		  {
			 startEntry=(((float) maxTodayHighScore-13.0)/26.0)*(float)game.scrollIndex;
			 endEntry=startEntry+15;
		  }
		  
          // Init text layer	  
          GRRLIB_initTexture();
		   
          // Draw background
          GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
      	     	
		  // Draw scrollbar
		  ypos=SCROLLBAR_Y_MIN;
          GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
		  for (int i=0; i<9; i++) 
		  {
		    ypos+=24;
		    GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
		  }
		  ypos+=24;
		  GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
		  		  
	      // Draw title
		  ypos=YOFFSET;
	      drawText(0, ypos, fontTitle, "   Today High Score");	

          // Show Content
          ypos+=90;

		  drawText(20, ypos, fontParagraph,  "TOP"  );
	      drawText(80, ypos, fontParagraph, "DATE" );
	      drawText(270, ypos, fontParagraph, "SCORE" );
		  drawText(350, ypos, fontParagraph, "NAME"  );
		  drawText(430, ypos, fontParagraph, "LOCATION" );
		  ypos+=10;
		  
		  if (todayHighScore[0].dt!=0)
		  {
            for (int i=startEntry; i<endEntry; i++)
            {
  	          ypos+=20;  
	    
		      sprintf(tmp,"%02d", i+1);
		      drawText(20, ypos, fontNormal, tmp);
			  			  
	          local = localtime(&todayHighScore[i].dt);
	          sprintf(tmp,"%02d-%02d-%04d %02d:%02d:%02d", 
			     local->tm_mday, local->tm_mon+1, local->tm_year+1900, 
			     local->tm_hour, local->tm_min, local->tm_sec);
		      drawText(80, ypos, fontNormal, tmp);
	   
		      drawText(270, ypos, fontNormal, todayHighScore[i].score);			  
			  drawText(350, ypos, fontNormal, todayHighScore[i].name);			  
			  drawText(430, ypos, fontNormal, todayHighScore[i].location);
		    }			
		  }
		  else
		  {
		      ypos+=120;
		      drawText(0, ypos, fontParagraph, "No information available!");
			  ypos+=20;
			  drawText(0, ypos, fontParagraph, "Information could not be fetch from internet.");
		  }
			 
          // Draw buttons
	      drawButtons(); 
		  
		  // Draw Button Text labels
		  drawButtonsText(0);
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
          // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);	 	   
	    }
	    break;
	   
		case stateGlobalHighScore:
	    {	      
	      struct tm *local;
		  int startEntry;
		  int endEntry;
		  		  
		  if (maxGlobalHighScore<13)
		  {
		    startEntry=0;
			endEntry=maxGlobalHighScore;
		  }
		  else
		  {
			 startEntry=(((float) maxGlobalHighScore-13.0)/26.0)*(float)game.scrollIndex;
			 endEntry=startEntry+13;
		  }
		  
          // Init text layer	  
          GRRLIB_initTexture();
		   
          // Draw background
          GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
      	     	
		  // Draw scrollbar
		  ypos=SCROLLBAR_Y_MIN;
          GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
		  for (int i=0; i<9; i++) 
		  {
		    ypos+=24;
		    GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
		  }
		  ypos+=24;
		  GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
		  		  
	      // Draw titl
		  ypos=YOFFSET;
	      drawText(0, ypos, fontTitle, "   Global High Score");	

          // Show Content
          ypos+=90;

		  drawText(20, ypos, fontParagraph,  "TOP"  );
	      drawText(80, ypos, fontParagraph,  "DATE" );
	      drawText(270, ypos, fontParagraph, "SCORE" );
		  drawText(350, ypos, fontParagraph, "NAME"  );
		  drawText(430, ypos, fontParagraph, "LOCATION" );
		  ypos+=10;
		  
		  if (globalHighScore[0].dt!=0)
		  {
            for (int i=startEntry; i<endEntry; i++)
            {
  	          ypos+=20;  
	    
		      sprintf(tmp,"%02d", i+1);
		      drawText(20, ypos, fontNormal, tmp);
			  			  
	          local = localtime(&globalHighScore[i].dt);
	          sprintf(tmp,"%02d-%02d-%04d %02d:%02d:%02d", 
			     local->tm_mday, local->tm_mon+1, local->tm_year+1900, 
			     local->tm_hour, local->tm_min, local->tm_sec);
		      drawText(80, ypos, fontNormal, tmp);
	   
		      drawText(270, ypos, fontNormal, globalHighScore[i].score);			  
			  drawText(350, ypos, fontNormal, globalHighScore[i].name);			  
			  drawText(430, ypos, fontNormal, globalHighScore[i].location);
		    }			
		  }
		  else
		  {
		      ypos+=120;
		      drawText(0, ypos, fontParagraph, "No information available!");
			  ypos+=20;
			  drawText(0, ypos, fontParagraph, "Information could not be fetch from internet.");
		  }
			 
          // Draw buttons
	      drawButtons(); 
		  
		  // Draw Button Text labels
		  drawButtonsText(0);
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
          // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);	 	   
	    }
	    break;

	    case stateHelp1:
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
		  drawButtonsText(0);
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
		  // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
	    }
	    break;

		case stateHelp2:
	    {	  
	      // Draw background
		  GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
		 
		  // Draw buttons
	      drawButtons(); 
		  
		  // Init text layer	  
          GRRLIB_initTexture();
 
		   // Show title
		  drawText(170, ypos, fontTitle, "Weapons");
		  
		  int xoffset=50;
		  
          ypos+=100;
		  drawText(30+xoffset, ypos,  fontParagraph, "Icon");
		  drawText(80+xoffset, ypos,  fontParagraph, "Type");
		  drawText(155+xoffset, ypos, fontParagraph, "Price");
		  drawText(240+xoffset, ypos, fontParagraph, "Power");
		  drawText(340+xoffset, ypos, fontParagraph, "Range");
		  drawText(440+xoffset, ypos, fontParagraph, "Rate");
	
		  ypos+=50;	  
		  GRRLIB_DrawImg(30+xoffset,ypos, images.weapon1, 0, 1, 1, IMAGE_COLOR );
		  drawText(80+xoffset, ypos, fontNormal, "Gun");
		  drawText(155+xoffset, ypos, fontNormal, "$100");
		  drawText(240+xoffset, ypos, fontNormal, "002-005");
		  drawText(340+xoffset, ypos, fontNormal, "050-075");
		  drawText(440+xoffset, ypos, fontNormal, "050-100");
		  					
		  ypos+=40;
		  GRRLIB_DrawImg(30+xoffset,ypos, images.weapon2, 0, 1, 1, IMAGE_COLOR );
		  drawText(80+xoffset, ypos, fontNormal, "Rifle");
		  drawText(155+xoffset, ypos, fontNormal, "$200");
		  drawText(240+xoffset, ypos, fontNormal, "004-010");
		  drawText(340+xoffset, ypos, fontNormal, "090-100");
		  drawText(440+xoffset, ypos, fontNormal, "045-080");
					
		  ypos+=40;
		  GRRLIB_DrawImg(30+xoffset,ypos, images.weapon3, 0, 1, 1, IMAGE_COLOR );
		  drawText(80+xoffset, ypos, fontNormal, "Canon");
		  drawText(155+xoffset, ypos, fontNormal, "$500");
		  drawText(240+xoffset, ypos, fontNormal, "008-030");
		  drawText(340+xoffset, ypos, fontNormal, "060-125");
		  drawText(440+xoffset, ypos, fontNormal, "030-080");
		
		  ypos+=40;
		  GRRLIB_DrawImg(30+xoffset,ypos, images.weapon4, 0, 1, 1, IMAGE_COLOR );
		  drawText(80+xoffset, ypos, fontNormal, "Missle");
		  drawText(155+xoffset, ypos, fontNormal, "$1000");
		  drawText(240+xoffset, ypos, fontNormal, "015-040");
		  drawText(340+xoffset, ypos, fontNormal, "080-125");
		  drawText(440+xoffset, ypos, fontNormal, "040-080");
					
		  ypos+=40;
		  GRRLIB_DrawImg(30+xoffset,ypos, images.weapon5, 0, 1, 1, IMAGE_COLOR );
		  drawText(80+xoffset, ypos, fontNormal, "Laser");
		  drawText(155+xoffset, ypos, fontNormal, "$2000");
		  drawText(240+xoffset, ypos, fontNormal, "030-060");
		  drawText(340+xoffset, ypos, fontNormal, "050-075");
		  drawText(440+xoffset, ypos, fontNormal, "040-080");
			
		  ypos+=40;
		  GRRLIB_DrawImg(30+xoffset,ypos, images.weapon6, 0, 1, 1, IMAGE_COLOR );
		  drawText(80+xoffset, ypos, fontNormal, "Nuck");
		  drawText(155+xoffset, ypos, fontNormal, "$4000");
		  drawText(240+xoffset, ypos, fontNormal, "100-200");
		  drawText(340+xoffset, ypos, fontNormal, "080-100");
		  drawText(440+xoffset, ypos, fontNormal, "100-200");			
		
		  drawText(130, 420, fontNormal, "Overview of upgrade range of each weapon system.");	
		
		  // Draw Button Text labels
		  drawButtonsText(0);
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
		  
		  // Draw text layer on top of gameboard 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
		
		case stateHelp3:
	    {	  
	      // Draw background
		  GRRLIB_DrawImg(0,0, images.background1, 0, 1, 1, IMAGE_COLOR2 );
		 
		  // Draw buttons
	      drawButtons(); 
		  
		  // Init text layer	  
          GRRLIB_initTexture();
 
		   // Show title
		  drawText(0, ypos, fontTitle, "Monsters");
        
		  ypos=130;
		  int xpos=50;
		  GRRLIB_DrawImg( xpos, ypos, images.monster1, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "5");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster2, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "10");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster3, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "15");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster4, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "20");

		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster5, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "25");		  

		  ypos+=40;	  
		  GRRLIB_DrawImg( xpos, ypos, images.monster6, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "30");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster7, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "35");
		  
		  ypos=130;
		  xpos+=150;
		  	
		  GRRLIB_DrawImg( xpos, ypos, images.monster8, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "40");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster9, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "45");

		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster10, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "50");
		  
		  ypos+=40;
		  GRRLIB_DrawImg( xpos, ypos, images.monster11, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "60");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster12, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "80");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster13, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "100");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster14, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "120");

		  ypos=130;
		  xpos+=150;
		  	
		  GRRLIB_DrawImg( xpos, ypos, images.monster15, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "140");		  

		  ypos+=40;	  
		  GRRLIB_DrawImg( xpos, ypos, images.monster16, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "160");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster17, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "190");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster18, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "230");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster19, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "250");

		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster20, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "280");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster21, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "300");
		  
		  ypos=130;
		  xpos+=150;
		  	
		  GRRLIB_DrawImg( xpos, ypos, images.monster22, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "350");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster23, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "300");
		  
		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster24, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "400");

		  ypos+=40;	
		  GRRLIB_DrawImg( xpos, ypos, images.monster25, 0, 1, 1, IMAGE_COLOR );
		  drawText(xpos+40, ypos, fontNormal, "500");	

   	      drawText(130, 420, fontNormal, "Overview of energy level of each monster type.");	
		  	   		  \
					  \
		  // Draw Button Text labels
		  drawButtonsText(0);
		  
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
		  ypos+=20;
	      drawText(0, ypos, fontNormal, "MLtm");
		  ypos+=20;
	      drawText(0, ypos, fontNormal, "shango64");
		  
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
		  drawButtonsText(0);
		  
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
	      //GRRLIB_DrawImg((640/2)-128, ((480/2)-140)+YOFFSET, images.soundIcon, game.angle, 1.4, 1.4, IMAGE_COLOR );
		  if (game.angle<MAX_ANGLE) game.angle++; else game.angle=0;
	
		  // Show title
		  drawText(100, ypos, fontTitle, "Sound Settings");
          ypos+=100;
		  
          // Draw content	
          drawText(0, ypos, fontParagraph, "Music Volume");	
	      ypos+=20;
          GRRLIB_DrawImg(104,ypos,images.bar, 0, 1, 1, IMAGE_COLOR );
	      ypos+=10;
	      GRRLIB_DrawImg(115+(sound->getMusicVolume()*40),ypos, images.barCursor, 0, 1, 1, IMAGE_COLOR );
  
          ypos+=80;
          drawText(0, ypos, fontParagraph, "Effects Volume" );
	      ypos+=20;	
	      GRRLIB_DrawImg(104,ypos, images.bar, 0, 1, 1, IMAGE_COLOR );
	      ypos+=10;
	      GRRLIB_DrawImg(115+(sound->getEffectVolume()*40),ypos,images.barCursor, 0, 1, 1, IMAGE_COLOR );
	
	      ypos+=70;
		  sprintf(tmp,"  Music track [%d]", sound->getMusicTrack());
	      drawText(0, ypos, fontParagraph, tmp);	
		  		  		
		  // Draw Button Text labels
		  drawButtonsText(0);
		  
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
		  char *buffer=NULL;
		  char text[MAX_BUFFER_SIZE];
		  
		  int startEntry;
		  int endEntry;
		  		  
		  // Fetch release notes from network thread
		  buffer=tcp_get_releasenote();
          if (buffer!=NULL) 
		  {
		     strncpy(text,buffer,MAX_BUFFER_SIZE);
			 len=strlen(text);
			 for (i=0;i<len;i++) if (text[i]=='\n') maxLines++;
		  }
		  
		  // Calculate start and end line.
		  if (maxLines<20)
		  {
		    startEntry=0;
			endEntry=maxLines;
		  }
		  else
		  {
			 startEntry=(((float) maxLines-18.0)/26.0)*(float)game.scrollIndex;
			 endEntry=startEntry+20;
		  }
		   
	      // Draw background
		  GRRLIB_DrawImg(0,0,images.background1, 0, 1.0, 1.0, IMAGE_COLOR2 );

		  // Draw buttons
	      drawButtons(); 
		  
	      // Init text layer	  
          GRRLIB_initTexture();
		  
          // Draw scrollbar
		  ypos=SCROLLBAR_Y_MIN;
          GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
		  for (i=0; i<9; i++) 
		  {
				ypos+=24;
				GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
		  }
		  ypos+=24;
		  GRRLIB_DrawImg(SCROLLBAR_x,ypos, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
		  		 
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
				 
				 // Show only 19 lines on screen
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
		  drawButtonsText(0);
		  
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
		        	  

		  // Draw initial characters
		  ypos+=50;	
		  int xpos=50;
		  sprintf(tmp, "%c", settings->getFirstChar());
		  drawText(xpos, ypos, fontTitle, tmp);
		  
		  xpos=+80;
		  sprintf(tmp, "%c", settings->getSecondChar());
		  drawText(xpos, ypos, fontTitle, tmp);
		  
		  xpos=+80;
		  sprintf(tmp, "%c", settings->getThirdChar());
		  drawText(xpos, ypos, fontTitle, tmp);

		  xpos=+80;
		  sprintf(tmp, "%c", settings->getFourthChar());
		  drawText(xpos, ypos, fontTitle, tmp);
		  
  		  xpos=+80;
		  sprintf(tmp, "%c", settings->getFifthChar());
		  drawText(xpos, ypos, fontTitle, tmp);
		  
  		  xpos=+80;
		  sprintf(tmp, "%c", settings->getSixthChar());
		  drawText(xpos, ypos, fontTitle, tmp);

		  ypos+=200;
	  	  drawText(0, ypos, fontParagraph, "This initials are used in the highscore area.");	
	     		  
		  // Draw Button Text labels
		  drawButtonsText(0);
		  
		  sprintf(tmp,"%d fps", CalculateFrameRate());
		  drawText(20, 500, fontSpecial, tmp);
				  
          // Draw text layer on top of gameboard 
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
		  drawGamePanel1();		  
		  drawGamePanel2();	
		  drawGamePanel3();	
		  
		  drawButtons();
		  
		  checkGameOver();
		  checkNextWave();
		  
		  // Init text layer	  
          GRRLIB_initTexture();
		  
		  if (game.alfa>0)
		  {
			ypos=210;	
			sprintf(tmp,"WAVE %02d", game.wave);
			GRRLIB_Printf2(180, ypos, tmp, 80, GRRLIB_RED);
			game.alfa-=5;
		  }
		  
		  drawMonstersText();
		  drawGamePanelText1();
		  drawGamePanelText2();
		  drawGamePanelText3();
		  drawButtonsText(-28);
		  
		  // Draw text layer on top of background 
		  GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
				
		case stateGameOver:
		{	  
		  drawGrid(); 
		  drawMonsters();
		  drawWeapons();
		  drawGamePanel2();	
	      drawButtons();
			
		  // Draw Transparent Box
		  GRRLIB_Rectangle(210, 220, 220, 100, GRRLIB_BLACK_TRANS, 1);
			 
		  // Init text layer	  
          GRRLIB_initTexture();
 
 		  drawMonstersText();
		  drawGamePanelText2();
		  drawButtonsText(-28);
			  
		  drawText(0, 230, fontParagraph, "Game Over!");
		 
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
		
		case stateGameQuit:
		{
		  drawGrid(); 
		  drawMonsters();
		  drawWeapons();
		  drawGamePanel2();	
		  drawButtons();
	
		  // Draw Transparent Box
		  GRRLIB_Rectangle(210, 220, 220, 100, GRRLIB_BLACK_TRANS, 1);
	
		  // Init text layer	  
          GRRLIB_initTexture();
 
 		  drawMonstersText();
		  drawGamePanelText2();
		  drawButtonsText(-10);
	
 	      drawText(0, 230, fontParagraph, "Quit game?");	
	     
		  // Draw text layer on top of background 
          GRRLIB_DrawImg(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, IMAGE_COLOR);
		}
		break;
	}
}

// -----------------------------------
// SUPPORT METHODES
// -----------------------------------

void loadTodayHighScore(char *buffer)
{
    const char *s_fn="loadTodayHighScore";
    trace->event(s_fn,0,"enter");
	
   int i;
   mxml_node_t *tree=NULL;
   mxml_node_t *data=NULL;
   const char *tmp;
   char temp[MAX_LEN];
   
   maxTodayHighScore=0;
   
   // Clear memory
   for(i=0; i<MAX_TODAY_HIGHSCORE; i++)
   {
      	todayHighScore[i].score[0]=0x00;
		todayHighScore[i].dt=0;
		todayHighScore[i].name[0]=0x00;
		todayHighScore[i].location[0]=0x00;
   } 
	 
   // If xml data available, parse it....
   if ((buffer!=NULL) && (strlen(buffer)>0))
   {  
      tree = mxmlLoadString(NULL, buffer, MXML_NO_CALLBACK);

      for(i=0; i<MAX_TODAY_HIGHSCORE; i++)
      {		
	    sprintf(temp, "item%d", i+1);
        data = mxmlFindElement(tree, tree, temp, NULL, NULL, MXML_DESCEND);

        tmp=mxmlElementGetAttr(data,"dt");   
        if (tmp!=NULL) todayHighScore[maxTodayHighScore].dt=atoi(tmp); else todayHighScore[maxTodayHighScore].dt=0; 
		
		tmp=mxmlElementGetAttr(data,"score");   
        if (tmp!=NULL) strcpy(todayHighScore[maxTodayHighScore].score,tmp); else strcpy(todayHighScore[maxTodayHighScore].score,"");
		
        tmp=mxmlElementGetAttr(data,"name");   
        if (tmp!=NULL) strcpy(todayHighScore[maxTodayHighScore].name,tmp); else strcpy(todayHighScore[maxTodayHighScore].name,"");

		tmp=mxmlElementGetAttr(data,"location");   
        if (tmp!=NULL) strcpy(todayHighScore[maxTodayHighScore].location,tmp); else strcpy(todayHighScore[maxTodayHighScore].location,"");
		
		// Entry is valid (Keep the inforamtion)
        if (strlen(todayHighScore[maxTodayHighScore].score)>0) maxTodayHighScore++;	
      }   
      mxmlDelete(data);
      mxmlDelete(tree);
   }
   
    trace->event(s_fn,0,"leave [void]");
}

void loadGlobalHighScore(char *buffer)
{
    const char *s_fn="loadGlobalHighScore";
    trace->event(s_fn,0,"enter");
	
   int i;
   mxml_node_t *tree=NULL;
   mxml_node_t *data=NULL;
   const char *tmp;
   char temp[MAX_LEN];
   
   maxGlobalHighScore=0;
   
   // Clear memory
   for(i=0; i<MAX_GLOBAL_HIGHSCORE; i++)
   {
      	globalHighScore[i].score[0]=0x00;
		globalHighScore[i].dt=0;
		globalHighScore[i].name[0]=0x00;
		globalHighScore[i].location[0]=0x00;
   } 
	 
   // If xml data available, parse it....
   if ((buffer!=NULL) && (strlen(buffer)>0))
   {  
      tree = mxmlLoadString(NULL, buffer, MXML_NO_CALLBACK);

      for(i=0; i<MAX_GLOBAL_HIGHSCORE; i++)
      {		
	    sprintf(temp, "item%d", i+1);
        data = mxmlFindElement(tree, tree, temp, NULL, NULL, MXML_DESCEND);

        tmp=mxmlElementGetAttr(data,"dt");   
        if (tmp!=NULL) globalHighScore[maxGlobalHighScore].dt=atoi(tmp); else globalHighScore[maxGlobalHighScore].dt=0; 
		
		tmp=mxmlElementGetAttr(data,"score");   
        if (tmp!=NULL) strcpy(globalHighScore[maxGlobalHighScore].score,tmp); else strcpy(globalHighScore[maxGlobalHighScore].score,"");
		
        tmp=mxmlElementGetAttr(data,"name");   
        if (tmp!=NULL) strcpy(globalHighScore[maxGlobalHighScore].name,tmp); else strcpy(globalHighScore[maxGlobalHighScore].name,"");

		tmp=mxmlElementGetAttr(data,"location");   
        if (tmp!=NULL) strcpy(globalHighScore[maxGlobalHighScore].location,tmp); else strcpy(globalHighScore[maxGlobalHighScore].location,"");
		
		// Entry is valid (Keep the inforamtion)
        if (strlen(globalHighScore[maxGlobalHighScore].score)>0) maxGlobalHighScore++;	
      }   
      mxmlDelete(data);
      mxmlDelete(tree);
   }
   
    trace->event(s_fn,0,"leave [void]");
}

// Create new weapon with correct game parameters
void createWeapon(int x, int y, int id, int type)
{
	const char *s_fn="createWeapon";
	trace->event(s_fn,0,"enter");
   
	weapons[id]= new Weapon();	
	weapons[id]->setX(x);
	weapons[id]->setY(y);
	weapons[id]->setSelected(true);
	weapons[id]->setIndex(id);
	weapons[id]->setImage(getNewWeaponImage(type));
	weapons[id]->setType(type);
	
	switch (type)
	{
		case 0:	{
					// Gun
					weapons[id]->setPower(2);
					weapons[id]->setRange(50);
					weapons[id]->setRate(100);
					
					weapons[id]->setMaxPower(5);
					weapons[id]->setMaxRange(75);
					weapons[id]->setMaxRate(50);
					
					weapons[id]->setPowerPrice(10);
					weapons[id]->setRangePrice(10);
					weapons[id]->setRatePrice(10);		
				}
				break;
				
		case 1:	{
					
					// Rifle
					weapons[id]->setPower(4);
					weapons[id]->setRange(55);
					weapons[id]->setRate(90);
					
					weapons[id]->setMaxPower(10);
					weapons[id]->setMaxRange(100);
					weapons[id]->setMaxRate(50);
					
					weapons[id]->setPowerPrice(25);
					weapons[id]->setRangePrice(25);
					weapons[id]->setRatePrice(25);		
				}
				break;
				
		case 2:	{
					// Canon
					weapons[id]->setPower(8);
					weapons[id]->setRange(60);
					weapons[id]->setRate(80);
					
					weapons[id]->setMaxPower(20);
					weapons[id]->setMaxRange(125);
					weapons[id]->setMaxRate(40);
					
					weapons[id]->setPowerPrice(50);
					weapons[id]->setRangePrice(50);
					weapons[id]->setRatePrice(50);		
				}
				break;
				
		case 3:	{
					// Missle				
					weapons[id]->setPower(15);
					weapons[id]->setRange(80);
					weapons[id]->setRate(80);
					
					weapons[id]->setMaxPower(40);
					weapons[id]->setMaxRange(125);
					weapons[id]->setMaxRate(40);
					
					weapons[id]->setPowerPrice(75);
					weapons[id]->setRangePrice(75);
					weapons[id]->setRatePrice(75);		
				}
				break;
								
		case 4:	{
					// Laser
					weapons[id]->setPower(30);
					weapons[id]->setRange(50);
					weapons[id]->setRate(80);
					
					weapons[id]->setMaxPower(60);
					weapons[id]->setMaxRange(75);
					weapons[id]->setMaxRate(40);
					
					weapons[id]->setPowerPrice(100);
					weapons[id]->setRangePrice(100);
					weapons[id]->setRatePrice(100);		
				}
				break;
				
		case 5:	{
					// Nuck
					weapons[id]->setPower(100);
					weapons[id]->setRange(80);
					weapons[id]->setRate(200);
					
					weapons[id]->setMaxPower(200);
					weapons[id]->setMaxRange(100);
					weapons[id]->setMaxRate(100);
					
					weapons[id]->setPowerPrice(250);
					weapons[id]->setRangePrice(250);
					weapons[id]->setRatePrice(250);		
				}
				break;
	}
	trace->event(s_fn,0,"leave");
}
		
// Return Weapon Image per Type		
GRRLIB_texImg *getNewWeaponImage(int type)
{
	switch (game.weaponType)
	{
		case 0:  // Gun
				 return images.weapon1;
				 break;
				
		case 1:  // Rifle
				 return images.weapon2;
				 break;
				
		case 2:  // Canon
				 return images.weapon3;
				 break;
				
		case 3:  // Missle
				 return images.weapon4;
				 break;
				
		case 4:  // Laser
				 return images.weapon5;
				 break;
				
		default: // unknown (TODO)
				 return images.weapon6;
				 break;
	}
}


// Return Weapon price per type
int getWeaponPrice(int type)
{
	switch (game.weaponType)
	{
		case 0:  // Gun
				 return 100;
				 break;
				
		case 1:  // Rifle
				 return 200;
				 break;
				
		case 2:  // Canon
				 return 500;
				 break;
				
		case 3:  // Missle
				 return 1000;
				 break;
				
		case 4:  // Laser
				 return 2000;
				 break;
				
		default: // unknown (TODO)
				 return 3000;
				 break;
	}
}

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
   if (game.monsterInBase>=MAX_MONSTER_IN_BASE)
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
	
	// If event is idle
	if (game.event==eventNone)
	{	
		// Lanch new monster wave else wait one game cycle
		game.event=eventLanch;
	}
}

void destroyImages(void)
{
   const char *s_fn="destroyImages";
   trace->event(s_fn,0,"enter");
   
   GRRLIB_FreeTexture(images.soundIcon);
   GRRLIB_FreeTexture(images.logo2);
   
   GRRLIB_FreeTexture(images.background1);
   GRRLIB_FreeTexture(images.background2);
   
   GRRLIB_FreeTexture(images.bar);
   GRRLIB_FreeTexture(images.barCursor);
   
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
      
   GRRLIB_FreeTexture(images.weapon1);
   GRRLIB_FreeTexture(images.weapon2);
   GRRLIB_FreeTexture(images.weapon3);
   GRRLIB_FreeTexture(images.weapon4);
   GRRLIB_FreeTexture(images.weapon5);
   GRRLIB_FreeTexture(images.weapon6);
   	
   GRRLIB_FreeTexture(images.button1);
   GRRLIB_FreeTexture(images.buttonFocus1);
   GRRLIB_FreeTexture(images.button2);
   GRRLIB_FreeTexture(images.buttonFocus2);
   GRRLIB_FreeTexture(images.button3);
   GRRLIB_FreeTexture(images.buttonFocus3);
   GRRLIB_FreeTexture(images.button4);
   GRRLIB_FreeTexture(images.buttonFocus4);
   
   GRRLIB_FreeTexture(images.map4);
   
   trace->event(s_fn,0,"leave");
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
		case eventNewWeaponSelected:		
		{
			trace->event(s_fn,0,"event=eventNewWeaponSelected");
			
			if (game.cash>=getWeaponPrice(game.weaponType))
			{
				// Change pointer image to weapon image (For location defination)
				pointers[0]->setImage(getNewWeaponImage(game.weaponType));
			}
		}
		break;
		
		case eventNewweaponDeployed:
		{
			trace->event(s_fn,0,"event=eventNewweaponDeployed");

			// First restore pointer image
			pointers[0]->setImage(images.pointer1);
			
			if ((game.cash>=getWeaponPrice(game.weaponType)) &&
				( pointers[0]->getX()>=115) &&
				( pointers[0]->getX()<=600))
			{
				// Find first empty place in weapons array
				int id=0;
				while (weapons[id]!=NULL) 
				{
					if (++id>=(MAX_WEAPONS-1)) 
					{
						id=(MAX_WEAPONS-1);
						break;
					}
				}
					
				// Deselected all weapons
				for (int j=0;j<MAX_WEAPONS; j++)
				{
					if (weapons[j]!=NULL) 
					{
						weapons[j]->setSelected(false);
					}
				}
				
				createWeapon(pointers[0]->getX(),pointers[0]->getY(),id, game.weaponType);
							
				// Selected new weapon
				game.weaponSelect=id;	

				// Pay for the weapon
				game.cash-=getWeaponPrice(game.weaponType);
			}
		}		
		break;
		
		case eventNewWeaponNext:		
		{
			trace->event(s_fn,0,"event=eventNewWeaponNext");
			
			if (game.weaponType<(MAX_WEAPON_TYPE-1)) 
			{
				game.weaponType++; 
			}
	 
	 		// Set button 
			if (game.cash>=getWeaponPrice(game.weaponType))
			{
				// Weapon normal
				buttons[6]->setColor(IMAGE_COLOR);
			}
			else
			{
				// Weapon Transparent (Not for sale)
				buttons[6]->setColor(IMAGE_COLOR3);
			}			
			buttons[6]->setImageNormal(getNewWeaponImage(game.weaponType));
			buttons[6]->setImageFocus(getNewWeaponImage(game.weaponType));
		}
		break;

		case eventNewWeaponPrevious:		
		{
			trace->event(s_fn,0,"event=eventNewWeaponPrevious");
			
			if (game.weaponType>0) 
			{
				game.weaponType--; 
			}
	
			// Set button 
			if (game.cash>=getWeaponPrice(game.weaponType))
			{
				// Weapon normal
				buttons[6]->setColor(IMAGE_COLOR);
			}
			else
			{
				// Weapon Transparent (Not for sale)
				buttons[6]->setColor(IMAGE_COLOR3);
			}
			buttons[6]->setImageNormal(getNewWeaponImage(game.weaponType));
			buttons[6]->setImageFocus(getNewWeaponImage(game.weaponType));
		}
		break;
				
		case eventLanch:
		{
			trace->event(s_fn,0,"event=eventLanch");	
			
			// Check if there is room in monster array for new wave.
			int count=0;
			for(int i=0;i<MAX_MONSTERS;i++)
			{
				if (monsters[i]==NULL) count++;
			}
			int amount=3+(game.wave*2);
			
			if (amount<count)
			{
				// Create next monster wave
				if (game.waveDelay>500) game.waveDelay-=100;
				game.waveCountDown=game.waveDelay;
				game.wave++;
				initMonsters(false);	
				
				// Get Bonus score and Bonus cash
				game.score+=(game.wave*100);
				game.cash+=(game.wave*100);

				// Show WAVE text on screen
				game.alfa=MAX_ALFA;

				// Lanch sound effect
				sound->effect(SOUND_LANCH);	
			}
			else
			{
				// No room in monster array wait 250 cycles (+/- 10 sec.) and try again!
				game.waveCountDown=250;
			}				
		}
		break;
		
		case eventSaveHighScore:
		{				
			trace->event(s_fn,0,"event=eventSaveHighScore");
			
			// Store highscore local
			char tmp[MAX_LEN];
			sprintf(tmp,"%c%c%c%c%c%c",
				settings->getFirstChar(), 
				settings->getSecondChar(), 
				settings->getThirdChar(),
				settings->getFourthChar(),
				settings->getFifthChar(),
				settings->getSixthChar());			
			highScore->setScore(tmp, game.wave, game.score);
			highScore->save(HIGHSCORE_FILENAME);
			
			// Store highscore on internet
			char tmp2[MAX_LEN];
			sprintf(tmp2,"appl=%s&level=%d&score=%d&name=%s&dt=%d",
				PROGRAM_NAME, game.wave, game.score, tmp, (int)time(NULL));
			tcp_set_state(TCP_REQUEST3a, tmp2);	
		}
		break;
		
		case eventWeaponPowerUpgrade:
		{
			trace->event(s_fn,0,"event=eventWeaponPowerUpgrade");			
			
			if (weapons[game.weaponSelect]!=NULL)
			{
				weapons[game.weaponSelect]->upgrade(0);
			}
		}
		break;
				
		case eventWeaponRangeUpgrade:
		{ 			
			trace->event(s_fn,0,"event=eventWeaponRangeUpgrade");						
			
			if (weapons[game.weaponSelect]!=NULL)
			{
				weapons[game.weaponSelect]->upgrade(1);
			}
		}
		break;
			
		case eventWeaponRateUpgrade:
		{ 
 			trace->event(s_fn,0,"event=eventWeaponRateUpgrade");
			
			if (weapons[game.weaponSelect]!=NULL)
			{
				weapons[game.weaponSelect]->upgrade(2);
			}
		}
		break;			
	}
	
	// Event is progress, set event handler to none!
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
	
		// Start background music
		sound->play();
	
		// Init Map1 until map3
		initGrid1();
	}
	break;

	case stateIntro2:
	{
		trace->event(s_fn,0,"stateMachine=stateIntro2");
		
		// Init Map4 until map6
		initGrid2();
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
		
		// Init game variables
		/*game.score=0;
		game.cash=2000;
		game.weaponSelect=0;
		game.weaponType=0;
		game.panelXOffset=20;
		game.panelYOffset=0;
		game.wave=10;           // Set to 10 to have more monster on screen
		game.monsterInBase=0;
		game.waveDelay = 3000;  // Start delay between two waves
		game.waveCountDown=game.waveDelay;
		game.alfa=MAX_ALFA;     // Show New Wave text on screen
		game.selectedMap=0;

		// clear monster array (clean up previous game)
		destroyMonsters();

		// Init Weapons
		initWeapons();
			
		// Create monsters for the selected wave
		initMonsters(true);	*/
	}
	break;
	
	case stateGame:
	{
		// Init buttons
		initButtons();	
			
		if (game.prevStateMachine!=stateGameQuit)
		{
			trace->event(s_fn,0,"stateMachine=stateGame");
	 
			// Init game variables
			game.score=0;
			game.cash=2000;
			game.weaponSelect=0;
			game.weaponType=0;
			game.panelXOffset=20;
			game.panelYOffset=0;
			game.wave=0;
			game.monsterInBase=0;
			game.waveDelay = 3000;  // Start delay between two waves
			game.waveCountDown=game.waveDelay;
			game.alfa=MAX_ALFA;     // Show New Wave text on screen
		
			// clear monster array (clean up previous game)
			destroyMonsters();
	
			// Destroy Weapons
			destroyWeapons();
	
			// Lanch first monster wave
			game.event=eventLanch;
		}
	}
	break;
	
	case stateGameQuit:	
	{
		trace->event(s_fn,0,"stateMachine=stateGameQuit");
		
		// Init buttons
		initButtons();	
	}
	break;
	
	case stateGameOver:
	{
		trace->event(s_fn,0,"stateMachine=stateGameOver");
		
		// Init buttons
		initButtons();	
	}
	break;
	
	case stateReleaseNotes:
	{
		trace->event(s_fn,0,"stateMachine=stateReleaseNotes");
		game.scrollIndex=0;
	
		// Init buttons
		initButtons();		
	}
	break;
	
	case stateLocalHighScore:
	{
		trace->event(s_fn,0,"stateMachine=stateLocalHighScore");
		game.scrollIndex=0;
		
		// Init buttons
		initButtons();		
	}
	break;
	
	case stateTodayHighScore:
	{
		trace->event(s_fn,0,"stateMachine=stateTodayHighScore");
		game.scrollIndex=0;
		
		// Fetch data for network thread
		char *buffer=NULL;
		
		buffer=tcp_get_today_highscore();
		loadTodayHighScore(buffer);		     
			  
		// Init buttons
		initButtons();		
	}
	break;
	
	case stateGlobalHighScore:
	{
		trace->event(s_fn,0,"stateMachine=stateGlobalHighScore");
		game.scrollIndex=0;
		
		// Fetch data for network thread
		char *buffer=NULL;
		
		buffer=tcp_get_global_highscore();
		loadGlobalHighScore(buffer);		     
			  
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
	
	case stateHelp1:
	{
		trace->event(s_fn,0,"stateMachine=stateHelp1");
		
		// Init buttons
		initButtons();		
	}
	break;

	case stateHelp2:
	{
		trace->event(s_fn,0,"stateMachine=stateHelp2");
		
		// Init buttons
		initButtons();		
	}
	break;
	
	case stateHelp3:
	{
		trace->event(s_fn,0,"stateMachine=stateHelp3");
		
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
    while( game.stateMachine!=stateQuit )
	{			
		// draw Screen
		drawScreen();

		// Draw Wii Motion Pointers
		drawPointers();
			
		// Render screen
		GRRLIB_Render();
		
		// Process state machine
		processStateMachine();
		
		// Process event
		processEvent();
	}
		  
	GRRLIB_Exit();
	
	// Stop network thread
	tcp_stop_thread();
	
	// Stop rumble
	WPAD_Rumble(0,0);
		
	// Destroy all created objects
	destroyImages();
	destroyWeapons();
	destroyButtons();
	destroyMonsters();
	destroyPointers();
	destroySound();
	destroyHighScore();
	destroySettings();
	destroyGrids();
	
	// Trace last line
	trace->event(s_fn, 0,"%s %s Leaving", PROGRAM_NAME, PROGRAM_VERSION);
	
	// Close trace file.
	trace->close();

	// Destroy trace class
	destroyTrace();
	
	// Exit to loader
	exit(0);
}

// ------------------------------
// The end
// ------------------------------