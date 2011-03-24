/**
 * @file 
 * @brief The file contain the general game constants
 * @author wplaat
 * @note Tab size of source code is two
 *
 * Copyright (c) 2008-2010 Plaatsoft
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
 
#ifndef GENERAL_H
#define GENERAL_H

// -----------------------------------------------------------
// Defines
// -----------------------------------------------------------

#define PROGRAM_NAME	   		"TowerDefense"
#define PROGRAM_VERSION     	"0.98"
#define RELEASE_DATE        	"24-03-2011" 

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

#define IR_X_OFFSET         	48
#define IR_Y_OFFSET         	48

#define SCROLLBAR_x         	600
#define SCROLLBAR_Y_MIN			150
#define SCROLLBAR_Y_MAX     	334

#define MUSIC_MULTIPLER			5
#define EFFECT_MULTIPLER		20

#define AVERAGE_FPS				40

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
	stateIntro4=4,
	
	stateMainMenu=5,
	stateLevelMenu=6,
	stateMapSelectMenu=7,
	stateGame=8,
	stateGameOver=9,
	stateQuitGame=10,
	
	stateLocalHighScore=11,
	stateTodayHighScore=12,
	stateGlobalHighScore=13,
	
	stateHelp1=14,
	stateHelp2=15,
	stateHelp3=16,
	stateHelp4=17,
	
	stateCredits=18,
	stateReleaseNotes=19,
	stateSoundSettings=20,
	stateGameSettings=21,
	stateDonate=22,
	stateQuit=23
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
	
	int stateMachine;			/**< State Machine status */
	int prevStateMachine;	/**< Previous State Machine status */
	
	int event; 						/**< Current event state */
	int prevEvent;				/**< Previous event state */
	
	int maxTodayHighScore;	/**< maximum Today highscore entries [0..40] */	
	int maxGlobalHighScore;	/**< maximum Global highscore entries [0..40] */
	
	int selectedMap; 			/**< game select Map id */	
	int monsterInBase;		/**< game monsters in base. */
	int selectedWeapon;		/**< game selected weapon id */
	bool selectedNewWeapon;	/**< game selected new weapon (draging mode). */
	int level; 					/**< Game level mode (easy, medium, hard) */
		
	int panelXOffset;			/**< game panel X offset */
	int panelYOffset;			/**< game panel Y offset */
	int score;					/**< game score */
	int cash;					/**< game cash */
	int wave;					/**< game wave number */
	int weaponType;			/**< game weapon type */
	int waveCountDown;		/**< game wave count down counter */
	
	int alfa;					/**< general graphical image alfa value [0..255] */
	int angle;					/**< general graphical image angle value [0..360] */
	int location;				/**< general graphical location counter */
	float size;					/**< general graphical size [0..1] */	
	float wave1;				/**< general graphical wave1 counter */
	float wave2;				/**< general graphical wave2 counter */
	int scrollIndex;			/**< general graphical scrollbar index counter */

	int frameCounter;			/**< general FPS frame counter */
	int frameDelay;			/**< general sprite animation frame delay counter */
	int frame;					/**< general sprite active frame index */
}
Game;

#endif

// -----------------------------------------------------------
// The End
// -----------------------------------------------------------
 
/**
 * @mainpage Wii TowerDefense Documentation
 * @image html TowerDefense.png
 * Welcome to the TowerDefense documentation.
 *
 * @section Introduction
 * WiiTowerDefense is a 2D classic game for the Nintendo Wii.
 *
 * @section Links
 * Website: http://www.plaatsoft.nl\n
 * Code: http://code.google.com/p/wiitowerdefense\n
 *
 * @section Credits
 * Documentation: wplaat\n
 *  
 * @section WishList
 * - Added dragable game information panels
 * 
 * @section ReleaseNotes
 *
 * <b>24-03-2011 Version 0.98</b>
 * - GUI:
 *  - Update menu screen information.
 *  - Improve deployment Wiimote cursor position.
 *  - Added WarQuest intro screen.
 * - Core:
 *  - Some performance tuning.
 * - General:
 *  - Correct include files.
 *  - Build game with devkitPPC r21 compiler.
 * 
 * <b>13-09-2010 Version 0.97</b>
 * - GUI:
 *  - Update menu screen information.
 * - Core:
 *  - Improve wave release time calculation.
 *  - Solve random freeze problem during startup of game.
 * - General:
 *  - Build game with devkitPPC r21 compiler.
 *
 * <b>11-09-2010 Version 0.96</b>
 * - GUI:
 *  - Update menu screen information.
 * - Core:
 *  - Use GRRLIB 4.3.0 as graphical engine.
 *  - libpng was updated to version 1.4.2
 *  - libjpeg was updated to version 8b
 *  - zlib was updated to version 1.2.5
 *  - FreeType was updated to 2.3.12
 * - General:
 *  - Maintenance release.
 *  - Build game with devkitPPC r21 compiler.
 *
 * <b>31-03-2010 Version 0.95</b>
 * - GUI:
 *  - Update menu screen information.
 * - Core:
 *  - WiiMote timeout increase from 60 to 300 seconds.
 *  - Improve stability.
 *  - Use libfat 1.0.7 as disk access engine.
 *  - Use libogc 1.8.3 as Wii interface engine
 * - General:
 *  - Make source code compliant with r21 compiler.
 *  - Build game with devkitPPC r21 compiler.
 *
 * <b>05-02-2010 Version 0.94</b>
 * - GUI:
 *  - Improve video initialization.
 *  - Overall FPS has improved 50 percent. Thanks Crayon.
 *  - Lots of other small GUI changes. 
 * - Core:
 *  - Mixed the weapon fire mode a little bit more!
 *  - Nuke is 500 dollar cheaper!
 *  - Increase http buffer size to 10Kb.
 *  - Use GrrLib 4.2.1 BETA library (Now native FreeType support available).
 * - General:
 *  - Added inline source code remarks in javadoc style.
 *  - Use Doxygen (windows tool) to create HTML source code documentation.
 *  - Build game with devkitPPC r19 compiler.
 * 
 * <b>22-01-2010 Version 0.93</b>
 * - GUI:
 *  - Added weapon fire mode information on weapon help screen.
 *  - Improve weapon reload delay initialisation.
 *  - Added donate screen.
 *  - Bugfix Weapon fire sprites were 22 degree misaligned. 
 * - Core:
 *  - Introduce different weapon fire modes.
 *  - Fire at enemy in range nearest to base (Gun + Rifle)
 *  - Fire at enemy in range with highest energy level (Cannon + Missile).
 *  - Fire at fastest enemy in range (Laser + Nuke).
 *  - Rebalance weapon specifications. Mix features more!
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>16-01-2010 Version 0.92</b>
 * - GUI:
 *  - Added 6 animated weapons. Thanks Applicant!
 *  - Improve enemy animated sprite frame sequence.
 *  - Improve help and level select screens.
 *  - Lots of other small changes.
 * - Core:
 *  - Weapons now fire on strongest enemy in range.
 *  - Increase bonus money when wave is cleared.
 *  - Increase initial weapon power.
 *  - Decrease weapon prices.
 *  - Added weapon sell functionality with minus button.
 *  - User initials are now default based on Wii nickname.
 *  - Bugfix: Monsters can not be shooted before launch.
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>09-01-2010 Version 0.91</b>
 * - GUI:
 *  - Added 25 animated enemy sprites. Thanks Applicant!
 *  - Added game setting screen.
 *  - Added intro screen 3.
 *  - Improve winter theme sprites.
 *  - Improve help screens.
 *  - Improve main menu screen.
 *  - Lots of other small changes.
 * - Core:
 *  - Less start money.
 *  - Enemy minimum / maximum speed depend on wave nr.
 *  - Increase weapon prices.
 *  - Increase maximum concurrent monsters in action.
 *  - Decrease weapons effective range.
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>02-01-2010 Version 0.90</b>
 * - GUI:
 *  - Improve background images.
 *  - Remove some english typos.
 *  - Improve first intro screen.
 *  - Added WiiMote control help screen.
 * - Core:
 *  - Improve first music track.
 *  - Enable B button for faster building. 
 *  - Enable left and right button for faster weapon type selection.
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>30-12-2009 Version 0.80</b>
 * - GUI:
 *  - Added map id column to local highscore screen.
 *  - Improve background images.
 *  - Remove typo (nuck->nuke).
 *  - Added 60Hz (640x480 pixel) TV Mode support.
 *  - Improve sound setting screen.
 *  - Optimised enemy images.
 * - Core:
 *  - Adapt game parameters to make game play better.
 *  - Increase start money depending on game level.
 *  - Enemy walk speed is now a randomized value. 
 *  - Map id information is added to webservice call.
 *  - Only scores above 20.000 points are send to webservice.
 *  - Store the best 100 entries in the local highscore.
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>27-12-2009 Version 0.70</b>
 * - GUI:
 *  - Added "Easy, Medium, Hard" level select screen.
 *  - Added six medium level and six hard level maps.
 *  - Added version information is webservice call.
 *  - BugFix: Highscore screens now show correct amount of entries!
 * - Core:
 *  - Adapted weapon specifications (Weapons are more powerfull).
 *  - Adapted enemy specifications (enemies are less powerfull).
 *  - Adapted six easy maps to be more easy. 
 *  - Increase enemy walk speed after each 20 waves. 
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>24-12-2009 Version 0.60</b>
 * - GUI:
 *  - Update credit screen. 
 *  - Improve game information panel design.
 *  - Show price and strengh information about new weapons.
 *  - Show detail information about selected weapon.
 *  - Show mini enemies moving on map select screen.
 *  - Bugfix: Map six background images are now showed correct.
 *  - Snap weapons to 32x32 grid!
 * - Core:
 *  - Increase enemy walk speed after each 25 waves.
 *  - Only allow to build weapons on land (not bridges or road).
 *  - Not allowed anymore to stack weapons on same place.
 *  - BugfiX: The rumble is now working for all the four WiiMotes. 
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *  
 * <b>20-12-2009 Version 0.50</b>
 * - GUI:
 *  - Improve "Game Over" screen. 
 *  - Improve game information panel on screen. 
 *  - Improve scroll bar button design.
 *  - Improve Help text.
 * - Core:
 *  - Reduced amount of enemies in one wave.
 *  - Increase user initials for 3 to 6 digits. 
 *  - Balance sound effect volume.
 *  - Improve weapons upgrade ranges.
 *  - Use GRRLib v4.2.0 as graphic engine.
 * - General:
 *  - First official release for the Wii Homebrew Scene.
 *  - Process most of the comments of the Beta testers.
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>18-12-2009 Version 0.45</b>
 * - GUI:
 *  - Added game map 4, 5 and 6.
 *  - Show when weapon upgrade is not possible anymore!
 *  - Added reload bar move weapon.
 *  - Added remaining energy bar below the base.
 *  - Rendering realtime grid examples on map select screen.
 *  - Added help screen two and three.
 *  - Added "Quit Game" screen. 
 *  - Placing weapons under the information panel is not allowed anymore.
 *  - Added today and global Highscore screen.
 *  - Added release notes screen.
 *  - Added dynamic weapon placement on the gameboard.
 *  - Added Release Notes screen.
 * - Core:
 *  - Load map images (sprites) directly from SdCard.
 *  - Improve objects cleanup when stopping game.
 *  - Limit weapon upgrade levels. 
 *  - Added WiiMote rumble support when pointer is on a button. 
 *  - Improve button pointer detection area. 
 *  - Added bonus cash (score) when wave is cleared.
 *  - Fetch latest available version information from internet.
 *  - Fetch latest release notes information from internet.
 *  - Fetch Global and today highscore from internet.
 *  - Added functionality to store game score on internet.
 *  - Added Google analistics network calls.
 * - General:
 *  - Beta release for testers.
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>13-12-2009 Version 0.40</b>
 * - GUI:
 *  - Added music & effect control screen.
 *  - Added wave launch button on game board.
 *  - Added game information panel.
 *  - Added functionality to upgrade power, range and rate of weapon.
 *  - Added Map Select menu screen.
 *  - Added Local highscore screen.
 *  - Added User Initials screen.
 *  - Added Credits screen.
 *  - Added Help screen.
 *  - Improve main menu screen.
 * - Core:
 *  - Added basic weapon fire graphic effect.
 *  - Added event engine.
 *  - Added nigh tracks background music.
 *  - Added game sound effects.
 *  - Added continues monster wave principle.
 *  - Added functionality to load/save local highscore from/to SD card.
 *  - Added functionality to load/save game settings from/to SD card.
 *  - Added functionality to make screenshots (Press + button).
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>06-12-2009 Version 0.30</b>
 * - GUI:
 *  - Added third game map.
 *  - Added water and bridge map component.
 *  - Added very basic main menu screen.
 * - Core:
 *  - Added gameOver detection.
 *  - Improve memory usage (load classes dynamicly when needed).
 *  - Added functionality that weapons can fire.
 *  - Added more comment to source code.
 *  - Added state machine functionality.
 *  - Align monster movement on grid.
 *  - Use libogc 1.8.1 library as Wii interface engine.
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>29-11-2009 Version 0.20</b>
 * - GUI:
 *  - Created intro screen.
 *  - Created main menu screen.
 *  - Created two game maps.
 * - Core:
 *  - Added four WiiMote controllers support.
 *  - Added functionality to load a map from a xml file.
 *  - Ported my GRRLIB freeType extention to work with GRRLIB 4.1.1.
 *  - Ported trace library from c to C++.
 *  - Use GRRLib v4.1.1 as graphic engine.
 *  - Use libfat v1.0.6 as disk access engine.
 *  - Use libmxml v2.6 library as xml engine.
 *  - Use libogc v1.8.0 library as Wii interface engine.
 * - General:
 *  - Build game with devkitPPC r19 compiler.
 *
 * <b>21-11-2009 Version 0.10</b>
 * - General:
 *  - Started programming in C++.
 *  - Finding free graphics for game.
 *  - Setup basic directory structure for new project.
 *  - Store source code in Google code SVN repository.
 *  - Build game with devkitPPC r19 compiler.
 *
 * @section Licence
 * Copyright (c) 2008-2010 Plaatsoft
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
