/*  
**  Created by wplaat (www.plaatsoft.nl)
**
**  Copyright (C) 2009-2010
**  =======================
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

#ifndef GENERAL_H
#define GENERAL_H

// -----------------------------------------------------------
// Defines
// -----------------------------------------------------------

#define PROGRAM_NAME	   		"TowerDefense"
#define PROGRAM_VERSION     	"0.93"
#define RELEASE_DATE        	"22-01-2010" 

// Check latest available version 
#define URL1                	"http://www.plaatsoft.nl/service/releasenotes5.html"
#define ID1			        		"UA-6887062-1"

// Fetch Release notes
#define URL2                	"http://www.plaatsoft.nl/service/releasenotes5.html"
#define ID2				   	 	"UA-6887062-1"

// Set Get Today HighScore
#define URL3                	"http://www.plaatsoft.nl/service/score_set_today.php"
#define ID3				    		"UA-6887062-1"

// Set Get Global HighScore
#define URL4                	"http://www.plaatsoft.nl/service/score_set_global.php"
#define ID4				    		"UA-6887062-1"

#define URL_TOKEN           	" Version "
#define HIGHSCORE_FILENAME  	"sd:/apps/TowerDefense/highscore.xml"
#define SETTING_FILENAME    	"sd:/apps/TowerDefense/settings.xml"
#define TRACE_FILENAME      	"sd:/apps/TowerDefense/TowerDefense.trc"
#define GAME_DIRECTORY      	"sd:/apps/TowerDefense/"

// Easy Maps
#define GRID1_DIRECTORY			"sd:/apps/TowerDefense/map01"
#define GRID2_DIRECTORY			"sd:/apps/TowerDefense/map02"
#define GRID3_DIRECTORY   	  	"sd:/apps/TowerDefense/map03"
#define GRID4_DIRECTORY   	  	"sd:/apps/TowerDefense/map04"
#define GRID5_DIRECTORY   	  	"sd:/apps/TowerDefense/map05"
#define GRID6_DIRECTORY   	  	"sd:/apps/TowerDefense/map06"

// Medium Maps
#define GRID7_DIRECTORY   	  	"sd:/apps/TowerDefense/map07"
#define GRID8_DIRECTORY   	  	"sd:/apps/TowerDefense/map08"
#define GRID9_DIRECTORY   	  	"sd:/apps/TowerDefense/map09"
#define GRID10_DIRECTORY   	"sd:/apps/TowerDefense/map10"
#define GRID11_DIRECTORY   	"sd:/apps/TowerDefense/map11"
#define GRID12_DIRECTORY   	"sd:/apps/TowerDefense/map12"

// Hard Maps
#define GRID13_DIRECTORY		"sd:/apps/TowerDefense/map13"
#define GRID14_DIRECTORY   	"sd:/apps/TowerDefense/map14"
#define GRID15_DIRECTORY   	"sd:/apps/TowerDefense/map15"
#define GRID16_DIRECTORY   	"sd:/apps/TowerDefense/map16"
#define GRID17_DIRECTORY   	"sd:/apps/TowerDefense/map17"
#define GRID18_DIRECTORY   	"sd:/apps/TowerDefense/map18"

#define WSP_POINTER_X      	200
#define WSP_POINTER_Y      	250

#define GRRLIB_WHITESMOKE   	0xFFFFFFFF
#define GRRLIB_WHITE_TRANS   	0xFFFFFF44
#define GRRLIB_LIGHTRED     	0x3333FFFF
#define GRRLIB_BLACK 			0x000000FF
#define GRRLIB_BLACK_TRANS		0x00000044
#define GRRLIB_BLACK_TRANS_2	0x000000AA
#define GRRLIB_MAROON  			0x800000FF
#define GRRLIB_GREEN   			0x008000FF
#define GRRLIB_OLIVE   			0x808000FF
#define GRRLIB_NAVY    			0x000080FF
#define GRRLIB_PURPLE  			0x800080FF
#define GRRLIB_TEAL    			0x008080FF
#define GRRLIB_GRAY    			0x808080FF
#define GRRLIB_SILVER  			0xC0C0C0FF
#define GRRLIB_RED     			0xFF0000FF
#define GRRLIB_LIME    			0x00FF00FF
#define GRRLIB_YELLOW  			0xFFFF00FF
#define GRRLIB_BLUE    			0x0000FFFF
#define GRRLIB_FUCHSIA 			0xFF00FFFF
#define GRRLIB_AQUA    			0x00FFFFFF
#define GRRLIB_WHITE   			0xFFFFFFFF

#define IMAGE_COLOR				0xFFFFFFFF
#define IMAGE_COLOR1        	0xEEEEEEEE
#define IMAGE_COLOR2        	0xDDDDDDDD
#define IMAGE_COLOR3        	0x44444444
#define IMAGE_COLOR4        	0xAAAAAAAA

#define MAX_WEAPONS				200
#define MAX_MONSTERS				300
#define MAX_BUTTONS         	15
#define MAX_POINTERS         	4
#define MAX_LOCAL_HIGHSCORE 	100
#define MAX_TODAY_HIGHSCORE	50
#define MAX_GLOBAL_HIGHSCORE	50
#define MAX_SETTINGS				9
#define MAX_WEAPON_TYPE       6
#define MAX_GRIDS  				6
#define MAX_MONSTER_IN_BASE   10

#define MAX_SOUND_VOLUME		10
#define MAX_MUSIC_TRACK     	9

#define MAX_RUMBLE				1
#define MAX_HORZ_PIXELS			640
#define MAX_VERT_PIXELS			480
#define MAX_LEN			    	256
#define MAX_ANGLE					360
#define MAX_ALFA					255
#define MAX_SIZE					1

#define MAX_LINES		    		200
#define MAX_BUFFER_SIZE			8192
#define MAX_IDLE_TIME	    	10

#define MAX_GRID_X 				20
#define MAX_GRID_Y 				17

#define IR_X_OFFSET         	40
#define IR_Y_OFFSET         	40

#define SCROLLBAR_x         	600
#define SCROLLBAR_Y_MIN			150
#define SCROLLBAR_Y_MAX     	334

#define MUSIC_MULTIPLER			5
#define EFFECT_MULTIPLER		20

#define AVERAGE_FPS				25

#define BUTTON_A           	(WPAD_BUTTON_A     | WPAD_CLASSIC_BUTTON_A)
#define BUTTON_B           	(WPAD_BUTTON_B     | WPAD_CLASSIC_BUTTON_B)
#define BUTTON_HOME         	(WPAD_BUTTON_HOME  | WPAD_CLASSIC_BUTTON_HOME)
#define BUTTON_1            	(WPAD_BUTTON_1     | WPAD_CLASSIC_BUTTON_X)
#define BUTTON_2            	(WPAD_BUTTON_2     | WPAD_CLASSIC_BUTTON_Y)

#define BUTTON_UP           	(WPAD_BUTTON_UP    | WPAD_CLASSIC_BUTTON_UP)
#define BUTTON_DOWN         	(WPAD_BUTTON_DOWN  | WPAD_CLASSIC_BUTTON_DOWN)
#define BUTTON_LEFT         	(WPAD_BUTTON_LEFT  | WPAD_CLASSIC_BUTTON_LEFT)
#define BUTTON_RIGHT        	(WPAD_BUTTON_RIGHT | WPAD_CLASSIC_BUTTON_RIGHT)
#define BUTTON_PLUS         	(WPAD_BUTTON_PLUS  | WPAD_CLASSIC_BUTTON_PLUS)
#define BUTTON_MINUS         	(WPAD_BUTTON_MINUS | WPAD_CLASSIC_BUTTON_MINUS)

// -----------------------------------------------------------
// ENUMS
// -----------------------------------------------------------

// State machine states
enum
{
	stateNone=0,
	
	stateIntro1=1,   
	stateIntro2=2, 
	stateIntro3=3,
	
	stateMainMenu=4,
	stateLevelMenu=5,
	stateMapSelectMenu=6,
	
	stateGame=7,
	stateGameOver=8,
	stateQuitGame=9,
	
	stateLocalHighScore=10,
	stateTodayHighScore=11,
	stateGlobalHighScore=12,
	
	stateHelp1=13,
	stateHelp2=14,
	stateHelp3=15,
	stateHelp4=16,
	
	stateCredits=17,
	stateReleaseNotes=18,
	stateSoundSettings=19,
	stateGameSettings=20,
	stateQuit=21
};

// Event machine events
enum
{
	eventNone=0,
	eventLaunch=1,  
	eventSaveHighScore=2,
	
	eventWeaponPowerUpgrade=3,
	eventWeaponRangeUpgrade=4,
	eventWeaponRateUpgrade=5,
	
	eventWeaponNext=6,
	eventWeaponPrevious=7,
	eventWeaponSelected=8,
	eventweaponDeployed=9,
	eventWeaponSell=10,
	
	eventInitEasyLevels=11,
	eventInitMediumLevels=12,
	eventInitHardLevels=13
};

enum
{
   fontTitle=0,
   fontSubTitle=1,
	fontPanel=2,
   fontParagraph=3,
   fontNew=4,
   fontNormal=5,
   fontSmall=6,
   fontButton=7,
   fontWelcome=8,
	fontBanner=9
};

enum
{
   gameEasy=0,
	gameMedium=1,
   gameHard=2
};

typedef struct 
{
	// State Machine status
	int stateMachine;
	int prevStateMachine;
	
	// Events
	int event;
	int prevEvent;
		
	// Highscore markers
	int maxTodayHighScore;
	int maxGlobalHighScore;

	// Game variables
	char name[MAX_LEN];	
	int selectedMap; 
	int monsterInBase;	
	int selectedWeapon;	
	bool selectedNewWeapon;
	int mode;
	int level;
		
	// game panel variables
	int panelXOffset;
	int panelYOffset;
	int score;
	int cash;	
	int wave;
	int weaponType;
	int waveCountDown;
	
	// Variables for graphical animations
	int alfa;
	int angle;
	int location;
	float size;
	float wave1;
	float wave2;
	int scrollIndex;
	int frameCounter;
	int frameDelay;
	int frame;
}
Game;

#endif

// -----------------------------------------------------------
// The End
// -----------------------------------------------------------
 