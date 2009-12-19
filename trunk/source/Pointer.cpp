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

#include <mxml.h>

#include "General.h"
#include "GRRLIB.h"
#include "Pointer.h"
#include "Settings.h"
#include "Trace.h"
#include "Button.h"
#include "Weapon.h"
#include "Sound.h"
  
extern  Game 		game;
extern 	Settings	*settings;
extern 	Sound		*sound;
extern 	Trace 		*trace;
extern 	Button 		*buttons[MAX_BUTTONS];
extern  Weapon    	*weapons[MAX_WEAPONS];

bool selected1;
bool selected2;
bool selectedA;
bool selectNewWeapon;

// ------------------------------
// Constructor 
// ------------------------------

Pointer::Pointer()
{
   const char *s_fn="Pointer::Pointer";
   trace->event(s_fn,0,"enter");
   
   x=0;
   xOffset=0;
   y=0;
   yOffset=0;
   angle=0;
   index=0;
   rumble=0;
   rumbleGo=false;
   
   selectedA=false;   
   selected1=false;
   selected2=false;
   selectNewWeapon=false;
   
   trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Destructor
// ------------------------------

Pointer::~Pointer()
{
  const char *s_fn="Pointer::~Pointer";
  trace->event(s_fn,0,"enter");
  
  trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Others
// ------------------------------

// Get Next of Previous letter & number or space character.
char Pointer::getLetter(char letter, bool up)
{
	if (up)
	{	
		if ((letter>=65) && (letter<90))
		{
			return letter++;
		}
		else 
		{
			return '0';
		}	
		
		if ((letter>=48) && (letter<57))
		{
			return letter++;
		}
		else 
		{
			return ' ';
		}	
		
		if (letter==30)
		{
			return 'A';
		}		
	}
	else
	{	
		if ((letter>65) && (letter<=90))
		{
			return letter--;
		}
		else
		{
			return ' ';
		}
		
		if ((letter>48) && (letter<=57))
		{
			return letter--;
		}
		else 
		{
			return 'Z';
		}
		
		if (letter==30)
		{
			return '9';
		}	
	}
}

void Pointer::button1x(void)
{
   if (!selected1)
   {
      selected1=true;
	  
	  int track=sound->getMusicTrack();
	  sound->setMusicTrack(++track);
   }        
}

void Pointer::button2y(void)
{
   if (!selected2)
   { 
      selected2=true;   
	  
	  int track=sound->getMusicTrack();
	  sound->setMusicTrack(--track);
   }
}

void Pointer::buttonPlus(int index)
{
	const char *s_fn="Pointer::buttonPlus";
	trace->event(s_fn,0,"enter [index=%d]",index);
  
	int volume;
	int track;

	switch (index)
	{	 
		case 0:	// First Character
				settings->setFirstChar(getLetter(settings->getFirstChar(),true));
				break;
		  
		case 1: // Second Character
				settings->setSecondChar(getLetter(settings->getSecondChar(),true));	
				break;
		  
		case 2: // Third Character
				settings->setThirdChar(getLetter(settings->getThirdChar(),true));	
				break;
		  
		case 3:	// Music volume
				volume=sound->getMusicVolume();
				sound->setMusicVolume(++volume);   
				break;
       
		case 4:	// Effect volume
				volume=sound->getEffectVolume();
				sound->setEffectVolume(++volume);  
				break;

		case 5:	// Prev music track
				track=sound->getMusicTrack();
				sound->setMusicTrack(++track);   
				break;
		  
		case 6: // Fourth Character
				settings->setFourthChar(getLetter(settings->getFourthChar(),true));	
				break;
				
		case 7: // Fifth Character
				settings->setFifthChar(getLetter(settings->getFifthChar(),true));
				break;
				
		case 8: // Sixth Character
				settings->setSixthChar(getLetter(settings->getSixthChar(),true));	
				break;
   }
   trace->event(s_fn,0,"leave");
}


void Pointer::buttonMinus(int index)
{
	const char *s_fn="Pointer::buttonMinus";
	trace->event(s_fn,0,"enter [index=%d]",index);
   
	int volume;
	int track;
	
	switch (index)   
	{
	    case 0:  // First Character		  
				settings->setFirstChar(getLetter(settings->getFirstChar(),false));		
				break;
			
		case 1:	// Second Character
				settings->setSecondChar(getLetter(settings->getSecondChar(),false));	
				break;
		  
		case 2: // Third Character
				settings->setThirdChar(getLetter(settings->getThirdChar(),false));
				break;   
		  
		case 3:	// Music volume
				volume=sound->getMusicVolume();
				sound->setMusicVolume(--volume);   
				break;
       
		case 4: // Effect volume
				volume=sound->getEffectVolume();
				sound->setEffectVolume(--volume);  
				break;

		case 5:  // Music track
				track=sound->getMusicTrack();
				sound->setMusicTrack(--track);   
				break;
				
		case 6: // Fourth Character
				settings->setFourthChar(getLetter(settings->getFourthChar(),false));	
				break; 
				
		case 7: // Fifth Character
				settings->setFifthChar(getLetter(settings->getFifthChar(),false));	
				break; 

		case 8: // Sixth Character
				settings->setSixthChar(getLetter(settings->getSixthChar(),false));	
				break;

	}
	trace->event(s_fn,0,"leave");
}


void Pointer::buttonScroll(int x,int y )
{ 
  switch (game.stateMachine)
  {
     case stateLocalHighScore:
	 case stateTodayHighScore:
	 case stateGlobalHighScore:
	 case stateReleaseNotes:
	 {     
  	    if ((buttons[1]!=NULL) && (buttons[1]->onSelect(x,y,false)))
		{
			if ((y-40)>SCROLLBAR_Y_MIN && (y-40)<SCROLLBAR_Y_MAX) 
			{
			    buttons[1]->setY(y-40);	
			    game.scrollIndex=(buttons[1]->getY()-SCROLLBAR_Y_MIN)/6;
			}
        }
	 }
  }
}

void Pointer::buttonA(int x, int y)
{
	const char *s_fn="Pointer::buttonA";

	if (selectedA) return;
	selectedA=true;
	  
    trace->event(s_fn,0,"enter [x=%d|y=%d]",x,y);
	 
	switch (game.stateMachine)
	{
		case stateIntro1:
		{
			// if A button is pressed continue to next intro screen
			game.stateMachine=stateIntro2;
		}
		break;

		case stateIntro2:
		{
			// if A button is pressed continue to next intro screen
			//game.stateMachine=stateIntro3;
						
			game.stateMachine=stateMainMenu;
		}
		break;
	 
	 	case stateMainMenu:
		{	
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Highscore button	      
				game.stateMachine=stateLocalHighScore;
			}
		
			if ((buttons[1]!=NULL) && (buttons[1]->onSelect(x,y,true)))
			{
				// Credits button	      
				game.stateMachine=stateHelp1;
			}
		
			if ((buttons[2]!=NULL) && (buttons[2]->onSelect(x,y,true)))
			{
				// Credits button	      
				game.stateMachine=stateCredits;
			}
		
			if ((buttons[3]!=NULL) && (buttons[3]->onSelect(x,y,true)))
			{
				// Sound Settings button	      
				game.stateMachine=stateSoundSettings;
			}
		
			if ((buttons[4]!=NULL) && (buttons[4]->onSelect(x,y,true)))
			{
				// Release Notes button	      
				game.stateMachine=stateReleaseNotes;
			}
		
			if ((buttons[5]!=NULL) && (buttons[5]->onSelect(x,y,true)))
			{
				// User Initials button	      
				game.stateMachine=stateUserSettings;
			}
			
			if ((buttons[6]!=NULL) && (buttons[6]->onSelect(x,y,true)))
			{
				// SelectMapMenu button	      
				game.stateMachine=stateMapSelectMenu;
			}
			
			if ((buttons[7]!=NULL) && (buttons[7]->onSelect(x,y,true)))
			{
				// Go back to HBC button    
				game.stateMachine=stateQuit;
			}
			
			if ((buttons[8]!=NULL) && (buttons[8]->onSelect(x,y,true)))
			{
				// Stop rumble
				WPAD_Rumble(0,0);
			
				// Reset Wii
				SYS_ResetSystem(SYS_RESTART,0,0);		   
			}					
		}
		break;
   
		case stateMapSelectMenu:
		{	
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Map1 button	      
				game.stateMachine=stateGame;
				game.selectedMap=0;
			}
		
			if ((buttons[1]!=NULL) && (buttons[1]->onSelect(x,y,true)))
			{
				// Map2 button	      
				game.stateMachine=stateGame;
				game.selectedMap=1;
			}
		
			if ((buttons[2]!=NULL) && (buttons[2]->onSelect(x,y,true)))
			{
				// Map3 button	      
				game.stateMachine=stateGame;
				game.selectedMap=2;
			}
			
			if ((buttons[3]!=NULL) && (buttons[3]->onSelect(x,y,true)))
			{
				// Map4 button	      
				game.stateMachine=stateGame;
				game.selectedMap=3;
			}
		
			if ((buttons[4]!=NULL) && (buttons[4]->onSelect(x,y,true)))
			{
				// Map5 button	      
				game.stateMachine=stateGame;
				game.selectedMap=4;
			}
		
			if ((buttons[5]!=NULL) && (buttons[5]->onSelect(x,y,true)))
			{
				// Map6 button	      
				game.stateMachine=stateGame;
				game.selectedMap=5;
			}
			
			if ((buttons[6]!=NULL) && (buttons[6]->onSelect(x,y,true)))
			{
				// Main Menu button	      
				game.stateMachine=stateMainMenu;
			}
		}
		break;
	
		case stateHelp1:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Next button	 
				game.stateMachine=stateHelp2;	     
			}
		}
		break;

		case stateHelp2:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Next button	 
				game.stateMachine=stateHelp3;	     
			}
		}
		break;

		case stateHelp3:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Main Menu button	 
				game.stateMachine=stateMainMenu;	     
			}
		}
		break;
		
		case stateReleaseNotes:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Main Menu button	 
				game.stateMachine=stateMainMenu;	    
			}
		}
		break;

		case stateLocalHighScore:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Main Menu button	 
				game.stateMachine=stateTodayHighScore;	     
			}
		}
		break;
		
		case stateTodayHighScore:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Main Menu button	 
				game.stateMachine=stateGlobalHighScore;	     
			}
		}
		break;

		case stateGlobalHighScore:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Main Menu button	 
				game.stateMachine=stateMainMenu;	     
			}
		}
		break;
		
		case stateSoundSettings:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Main Menu button	 
				game.stateMachine=stateMainMenu;	
				settings->setMusicVolume(sound->getMusicVolume());
				settings->setEffectVolume(sound->getEffectVolume());
				settings->save(SETTING_FILENAME); 
			}
			
			if ((buttons[1]!=NULL) && (buttons[1]->onSelect(x,y,true)))
			{
				// - music volume button event	           
			    buttonMinus(3);   
			}
			
			if ((buttons[2]!=NULL) && (buttons[2]->onSelect(x,y,true)))
			{
				// + music volume button event	           
			    buttonPlus(3); 
			}
				
			if ((buttons[3]!=NULL) && (buttons[3]->onSelect(x,y,true)))
			{
				// - effect volume button event	           
			    buttonMinus(4);  
			}
			 
			if ((buttons[4]!=NULL) && (buttons[4]->onSelect(x,y,true)))
			{
				// + effect volume button event	           
			    buttonPlus(4);
			}
			
			if ((buttons[5]!=NULL) && (buttons[5]->onSelect(x,y,true)))
			{
				// - music track button event	           
			    buttonMinus(5); 
			}

			if ((buttons[6]!=NULL) && (buttons[6]->onSelect(x,y,true)))
			{			
				// + music track  button event	           
			    buttonPlus(5);
			}
		}
		break;
	 
		case stateUserSettings:
		{ 			
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Main Menu button	 
				settings->save(SETTING_FILENAME); 
				game.stateMachine=stateMainMenu;	     
			}
			
			// Check if button is pressed on screen
			if ((buttons[1]!=NULL) && (buttons[1]->onSelect(x,y,true)))
			{
				// + First Character button event           
				buttonPlus(0);  
			}
		
			if ((buttons[2]!=NULL) && (buttons[2]->onSelect(x,y,true)))
			{
				// - First Character button event           
				buttonMinus(0);  
			}
						
			if ((buttons[3]!=NULL) && (buttons[3]->onSelect(x,y,true)))
			{
				// + Second Character button event           
				buttonPlus(1);  
			}
		
			if ((buttons[4]!=NULL) && (buttons[4]->onSelect(x,y,true)))
			{
				// - Second Character button event           
				buttonMinus(1); 
			}
					    
			if ((buttons[5]!=NULL) && (buttons[5]->onSelect(x,y,true)))
			{
				// + Third Character button event           
				buttonPlus(2);  
			}
			
			if ((buttons[6]!=NULL) && (buttons[6]->onSelect(x,y,true)))
			{
				// - Third Character button event           
				buttonMinus(2);  
			}
			
			if ((buttons[7]!=NULL) && (buttons[7]->onSelect(x,y,true)))
			{
				// + Fourth Character button event           
				buttonPlus(6);  
			}
			
			if ((buttons[8]!=NULL) && (buttons[8]->onSelect(x,y,true)))
			{
				// - Fourth Character button event           
				buttonMinus(6);  
			}
			
			if ((buttons[9]!=NULL) && (buttons[9]->onSelect(x,y,true)))
			{
				// + Fifth Character button event           
				buttonPlus(7);  
			}
			
			if ((buttons[10]!=NULL) && (buttons[10]->onSelect(x,y,true)))
			{
				// - Fifth Character button event           
				buttonMinus(7);  
			}

			if ((buttons[11]!=NULL) && (buttons[11]->onSelect(x,y,true)))
			{
				// + Sixth Character button event           
				buttonPlus(8);  
			}
			
			if ((buttons[12]!=NULL) && (buttons[12]->onSelect(x,y,true)))
			{
				// - Sixth Character button event           
				buttonMinus(8);  
			}
			
		}
		break; 

		case stateCredits:
		{
			// Check if button is pressed on screen
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Main Menu button	 	
				game.stateMachine=stateMainMenu;	    
			}
		}
		break;
			
		case stateGame:
		{	
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Lanch button	(set lanch timer on 0 (24/25ste) second.
				game.waveCountDown=24;
			}
			
			if ((buttons[4]!=NULL) && (buttons[4]->onSelect(x,y,true)))
			{
				// Select previous weapon	
				game.event=eventNewWeaponPrevious;
			}					
				
			if ((buttons[5]!=NULL) && (buttons[5]->onSelect(x,y,true)))
			{
				// Select next weapon
				game.event=eventNewWeaponNext;    		
			}
			
			// New weapon is selected
			if ((buttons[6]!=NULL) && (buttons[6]->onSelect(x,y,true)))
			{				
				game.event=eventNewWeaponSelected;	
				selectNewWeapon=true;
			}
			
			// Check if weapon is selected on screen
			for (int i=0;i<MAX_WEAPONS; i++)
			{
				if ((weapons[i]!=NULL) && (weapons[i]->onSelect(x,y)))
				{
					// Deselected all weapons
					for (int j=0;j<MAX_WEAPONS; j++)
					{
						if (weapons[j]!=NULL) 
						{
							weapons[j]->setSelected(false);
						}
					}
				
					// Selected new weapons
					game.weaponSelect=i;
					weapons[i]->setSelected(true);
				}
			}
				
			// Check if weapon upgrade button is pressed on screen
			if (weapons[game.weaponSelect]!=NULL)
			{
				if ((buttons[1]!=NULL) && (buttons[1]->onSelect(x,y,true)))
				{
					// Power button	      
					game.event=eventWeaponPowerUpgrade;
				}
		
				if ((buttons[2]!=NULL) && (buttons[2]->onSelect(x,y,true)))
				{
					// Range button	      
					game.event=eventWeaponRangeUpgrade;
				}
			
				if ((buttons[3]!=NULL) && (buttons[3]->onSelect(x,y,true)))
				{
					// Rate button	      		
					game.event=eventWeaponRateUpgrade;
				}						
			}		
		}
		break;
		
		case stateGameQuit:
		{
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Yes button
				game.stateMachine=stateMapSelectMenu;
				
				// Score current score;
				game.event=eventSaveHighScore;
			}

			if ((buttons[1]!=NULL) && (buttons[1]->onSelect(x,y,true)))
			{
				// No button
				game.stateMachine=stateGame;
			}	
		}
		break;
		
		case stateGameOver:
		{
			if ((buttons[0]!=NULL) && (buttons[0]->onSelect(x,y,true)))
			{
				// Retry button
				game.stateMachine=stateGame;
			}

			if ((buttons[1]!=NULL) && (buttons[1]->onSelect(x,y,true)))
			{
				// Quit button
				game.stateMachine=stateMainMenu;
			}	
		}
		break;
	}
	trace->event(s_fn,0,"leave");
}

void Pointer::action(void)
{
	const char *s_fn="Pointer::action";

	// Scan for button events
	WPAD_SetVRes(index, 640, 528);
	WPAD_ScanPads();

	// Scan for ir events 
	WPAD_IR(index, &ir); 
	x=ir.sx-WSP_POINTER_X;
	xOffset=x+IR_X_OFFSET;
	y=ir.sy-WSP_POINTER_Y;
	yOffset=y+IR_Y_OFFSET;
	angle=ir.angle;
	
	// disable angle to improve navigation.
	angle=0;
				
	// Only the first WiiMote can control the game.
	if (index==0)
	{
		u32 wpaddown = WPAD_ButtonsDown(index);
		u32 wpadup   = WPAD_ButtonsUp(index);
		u32 wpadheld = WPAD_ButtonsHeld(index);

		if (wpaddown & BUTTON_A) 
		{
			buttonA(xOffset,yOffset); 
		}
		
		if (wpadup & BUTTON_A) 
		{
			selectedA=false;
			if (selectNewWeapon) 
			{
				selectNewWeapon=false;
				game.event=eventNewweaponDeployed;
			}
		}
			
		if (wpaddown & BUTTON_1 ) 
		{
			button1x();								
		}
    
		if (wpadup & BUTTON_1) 
		{
			selected1=false;		
		}
			
		if (wpaddown & BUTTON_2 ) 
		{
			button2y();		
		}
	
		if (wpadup & BUTTON_2) 
		{
			selected2=false;
		}

		if (wpadheld & BUTTON_A) 
		{
			buttonScroll(xOffset,yOffset);	 
		}
		
		// Scan for button events
		if (wpaddown & WPAD_BUTTON_HOME) 
		{
			trace->event(s_fn,0,"Home button pressed");
			if (game.stateMachine==stateMainMenu)
			{			
				game.stateMachine=stateQuit;
			}
			else
			{
				if (game.stateMachine==stateGame)
				{
					game.stateMachine=stateGameQuit;
				}
				else if (game.stateMachine!=stateGameQuit)
				{
					game.stateMachine=stateMainMenu;
				}
			}		
		}
	
		// Make screenshot 
		if (wpadheld & BUTTON_PLUS)
		{
			char filename[MAX_LEN];
			struct tm *level;	   
			time_t dt=time(NULL);
			level = localtime(&dt);
			sprintf(filename,"%sTowerDefense-%04d%02d%02d%02d%02d%02d.png", GAME_DIRECTORY, level->tm_year+1900,level->tm_mon+1, level->tm_mday,  level->tm_hour, level->tm_min, level->tm_sec);		  
			GRRLIB_ScrShot(filename);	
		}

		if (rumble>0) 
		{
			rumble--;
			WPAD_Rumble(index,1); 
		}
		else 
		{
			WPAD_Rumble(index,0);
		}
	}
}

void Pointer::draw(void)
{   	
    // Draw Pointer on screen
    GRRLIB_DrawImg( x, y, image, angle, 1.0, 1.0, IMAGE_COLOR );		
}

// ------------------------------
// Setters 
// ------------------------------

void Pointer::setIndex(int index1)
{
   const char *s_fn="Pointer::setIndex";
   trace->event(s_fn,0,"%d",index1);
  
   index = index1;
}

void Pointer::setX(int x1)
{
   const char *s_fn="Pointer::setX";
   trace->event(s_fn,0,"%d",x1);
   
   if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
   {
      x = x1;
   }
}

void Pointer::setY(int y1)
{
   const char *s_fn="Pointer::setY";
   trace->event(s_fn,0,"%d",y1);
   
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
}

void Pointer::setAngle(int angle1)
{
   const char *s_fn="Pointer::setAngle";
   trace->event(s_fn,0,"%d",angle1);
   
   if ((angle1>=0) && (angle1<=MAX_ANGLE))
   {
      angle=angle1;
   }
} 

void Pointer::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Pointer::setImage";
   trace->event(s_fn,0,"data");
   
   image = image1;
}

void Pointer::setRumble(int rumble1)
{
   const char *s_fn="Pointer::setRumble";
   trace->event(s_fn,0,"%d",rumble1);
   
   rumble=rumble1;
}

// ------------------------------
// Getters
// ------------------------------

int Pointer::getX()
{
	return x;
}

int Pointer::getY()
{
	return y;
}
	

int Pointer::getXOffset()
{
	return xOffset;
}

int Pointer::getYOffset()
{
	return yOffset;
}

// ------------------------------
// The End
// ------------------------------