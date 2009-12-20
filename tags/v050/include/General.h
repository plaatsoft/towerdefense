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

#ifndef GENERAL_H
#define GENERAL_H

// -----------------------------------------------------------
// Defines
// -----------------------------------------------------------

#define PROGRAM_NAME	   		"TowerDefense"
#define PROGRAM_VERSION     	"0.50"
#define RELEASE_DATE        	"20-12-2009" 

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
#define SETTING_FILENAME    	"sd:/apps/TowerDefense/settings.xml"
#define TRACE_FILENAME      	"sd:/apps/TowerDefense/TowerDefense.trc"
#define GAME_DIRECTORY      	"sd:/apps/TowerDefense/"

#define GRID1_DIRECTORY    	  	"sd:/apps/TowerDefense/map1"
#define GRID2_DIRECTORY    	  	"sd:/apps/TowerDefense/map2"
#define GRID3_DIRECTORY   	  	"sd:/apps/TowerDefense/map3"
#define GRID4_DIRECTORY   	  	"sd:/apps/TowerDefense/map4"
#define GRID5_DIRECTORY   	  	"sd:/apps/TowerDefense/map5"
#define GRID6_DIRECTORY   	  	"sd:/apps/TowerDefense/map6"

#define YOFFSET					25
#define WSP_POINTER_X      		200
#define WSP_POINTER_Y      		250

#define GRRLIB_WHITESMOKE   	0xFFFFFFFF
#define GRRLIB_LIGHTRED     	0x3333FFFF
#define GRRLIB_BLACK 			0x000000FF
#define GRRLIB_BLACK_TRANS		0x00000044
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

#define IMAGE_COLOR        		0xFFFFFFFF
#define IMAGE_COLOR2        	0x66666666
#define IMAGE_COLOR3        	0x44444444

#define MAX_WEAPONS				100
#define MAX_MONSTERS			250
#define MAX_BUTTONS         	15
#define MAX_POINTERS         	4
#define MAX_LOCAL_HIGHSCORE 	50
#define MAX_TODAY_HIGHSCORE	 	50
#define MAX_GLOBAL_HIGHSCORE	50
#define MAX_SETTINGS			8
#define MAX_WEAPON_TYPE         6
#define MAX_GRIDS  				6
#define MAX_MONSTER_IN_BASE     10

#define MAX_SOUND_VOLUME		10
#define MAX_MUSIC_TRACK     	9

#define MAX_RUMBLE				2
#define MAX_HORZ_PIXELS			640
#define MAX_VERT_PIXELS			480
#define MAX_LEN			    	256
#define MAX_ANGLE				360
#define MAX_ALFA				255
#define MAX_SIZE				40

#define MAX_LINES		    	200
#define MAX_BUFFER_SIZE			8192
#define MAX_IDLE_TIME	    	10

#define MAX_GRID_X 				20
#define MAX_GRID_Y 				17

#define IR_X_OFFSET         	40
#define IR_Y_OFFSET         	40

#define SCROLLBAR_x         	600
#define SCROLLBAR_Y_MIN			150
#define SCROLLBAR_Y_MAX     	310

#define MUSIC_MULTIPLER			5
#define EFFECT_MULTIPLER		20

#define BUTTON_A           	 	(WPAD_BUTTON_A     | WPAD_CLASSIC_BUTTON_A)
#define BUTTON_HOME         	(WPAD_BUTTON_HOME  | WPAD_CLASSIC_BUTTON_HOME)
#define BUTTON_1            	(WPAD_BUTTON_1     | WPAD_CLASSIC_BUTTON_X)
#define BUTTON_2            	(WPAD_BUTTON_2     | WPAD_CLASSIC_BUTTON_Y)

#define BUTTON_UP           	(WPAD_BUTTON_UP    | WPAD_CLASSIC_BUTTON_UP)
#define BUTTON_DOWN         	(WPAD_BUTTON_DOWN  | WPAD_CLASSIC_BUTTON_DOWN)
#define BUTTON_LEFT         	(WPAD_BUTTON_LEFT  | WPAD_CLASSIC_BUTTON_LEFT)
#define BUTTON_RIGHT        	(WPAD_BUTTON_RIGHT | WPAD_CLASSIC_BUTTON_RIGHT)
#define BUTTON_PLUS         	(WPAD_BUTTON_PLUS  | WPAD_CLASSIC_BUTTON_PLUS)

#define AVERAGE_FPS			25

#define POWER_UPGRADE_STEP  2
#define RANGE_UPGRADE_STEP  5
#define RATE_UPGRADE_STEP   1

#define GUN_START_PRICE 	100
#define GUN_UPGRADE_PRICE   10
#define GUN_START_POWER 	2
#define GUN_START_RANGE 	50
#define GUN_START_RATE 		10
#define GUN_END_POWER   	10
#define GUN_END_RANGE   	75
#define GUN_END_RATE    	6

#define RIFLE_START_PRICE 	200
#define RIFLE_UPGRADE_PRICE 25
#define RIFLE_START_POWER 	4
#define RIFLE_START_RANGE 	80
#define RIFLE_START_RATE  	8
#define RIFLE_END_POWER   	14
#define RIFLE_END_RANGE   	100
#define RIFLE_END_RATE   	4

#define CANON_START_PRICE 	500
#define CANON_UPGRADE_PRICE 50
#define CANON_START_POWER 	12
#define CANON_START_RANGE 	60
#define CANON_START_RATE  	10
#define CANON_END_POWER   	24
#define CANON_END_RANGE   	80
#define CANON_END_RATE    	6

#define MISSLE_START_PRICE 	1000
#define MISSLE_UPGRADE_PRICE 100
#define MISSLE_START_POWER 	20
#define MISSLE_START_RANGE 	80
#define MISSLE_START_RATE  	8
#define MISSLE_END_POWER   	34
#define MISSLE_END_RANGE   	100
#define MISSLE_END_RATE    	4

#define LASER_START_PRICE 	2000
#define LASER_UPGRADE_PRICE 100
#define LASER_START_POWER 	30
#define LASER_START_RANGE 	80
#define LASER_START_RATE  	6
#define LASER_END_POWER   	44
#define LASER_END_RANGE   	100
#define LASER_END_RATE    	2

#define NUCK_START_PRICE 	4000
#define NUCK_UPGRADE_PRICE  250
#define NUCK_START_POWER 	100
#define NUCK_START_RANGE 	80
#define NUCK_START_RATE  	10
#define NUCK_END_POWER   	114
#define NUCK_END_RANGE   	100
#define NUCK_END_RATE    	6

// -----------------------------------------------------------
// ENUMS
// -----------------------------------------------------------

// State machine states
enum
{
	stateNone=0,
	stateIntro1=1,   
	stateIntro2=2, 
	stateMainMenu=3,
	stateMapSelectMenu=4,
	stateGame=5,
	stateGameOver=6,
	stateGameQuit=7,
	stateLocalHighScore=8,
	stateTodayHighScore=9,
	stateGlobalHighScore=10,
	stateHelp1=11,
	stateHelp2=12,
	stateHelp3=13,
	stateCredits=14,
	stateSoundSettings=15,
	stateReleaseNotes=16,
	stateUserSettings=17,
	stateQuit=18
};

// Event machine events
enum
{
	eventNone=0,
	eventLanch=1,  
	eventSaveHighScore=2,
	eventWeaponPowerUpgrade=3,
	eventWeaponRangeUpgrade=4,
	eventWeaponRateUpgrade=5,
	
	eventNewWeaponNext=6,
	eventNewWeaponPrevious=7,
	eventNewWeaponSelected=8,
	eventNewweaponDeployed=9
};

enum
{
   fontTitle=0,
   fontSubTitle=1,
   fontSubTitle2=2,
   fontParagraph=3,
   fontNew=4,
   fontNormal=5,
   fontSpecial=6,
   fontButton=7,
   fontWelcome=8
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
	int	maxTodayHighScore;
	int	maxGlobalHighScore;

	// Game variables
	char name[MAX_LEN];	
	int selectedMap; 
	int monsterInBase;	
	int weaponSelect;	
	int waveDelay;
		
	// game panel variables
	int panelXOffset;
	int panelYOffset;
	int score;
	int cash;	
	int wave;
	int weaponType;
	int waveCountDown;
	
	// Variables for graphical animations
	int   alfa;
	int   angle;
	float wave1;
	float wave2;
	int   scrollIndex;
}
Game;

#endif

// -----------------------------------------------------------
// The End
// -----------------------------------------------------------
 