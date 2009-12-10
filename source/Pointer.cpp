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
  
extern Game game;

extern 	Settings	*settings;
extern 	Trace 		*trace;
extern 	Button 		*buttons[MAX_BUTTONS];
extern  Weapon    	*weapons[MAX_WEAPONS];

boolean selectedA=false;

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
   rumble=0;
   rumbleGo=false;
   
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

void Pointer::properties(void)
{  
	char tmp[50];
	int size=12;
 
	sprintf(tmp, "x=%d", x);
	GRRLIB_Printf2(10, 10, tmp, size, GRRLIB_WHITESMOKE); 
	
	sprintf(tmp, "y=%d", y);
	GRRLIB_Printf2(10, 20, tmp, size, GRRLIB_WHITESMOKE);
}

void Pointer::buttonPlus(int index)
{
   const char *s_fn="Pointer::buttonPlus";
   trace->event(s_fn,0,"enter [index=%d]",index);
  
   char letter;

   switch (index)
   {	 
	  case 0:
		  // First Character
		  letter=settings->getFirstChar();
		  if (letter<90) 
		  {
			settings->setFirstChar(++letter);
		  }
		  else 
		  {
			settings->setFirstChar('A');
		  }		
		  break;
		  
	  case 1:
		  // Second Character
		  letter=settings->getSecondChar();
		  if (letter<90) 
		  {
			settings->setSecondChar(++letter);
		  }
		  else 
		  {
			settings->setSecondChar('A');
		  }		
		  break;
		  
	  case 2:
		  // Third Character
		  letter=settings->getThirdChar();
		  if (letter<90) 
		  {
			settings->setThirdChar(++letter);
		  }
		  else 
		  {
			settings->setThirdChar('A');
		  }		
		  break;
   }
   trace->event(s_fn,0,"leave");
}

void Pointer::buttonMinus(int index)
{
	const char *s_fn="Pointer::buttonMinus";
	trace->event(s_fn,0,"enter [index=%d]",index);
   
	char letter;
	switch (index)   
	{
	    case 0:
		  // First Character		  
		  letter=settings->getFirstChar();
		  if (letter>65) 
		  {
			settings->setFirstChar(--letter);
		  }
		  else 
		  {
			settings->setFirstChar('Z');
		  }		
		  break;
		   
		case 1:
		  // Second Character
		  letter=settings->getSecondChar();
		  if (letter>65) 
		  {
			settings->setSecondChar(--letter);
		  }
		  else 
		  {
			settings->setSecondChar('Z');
		  }		
		  break;
		  
		case 2:
		  // Third Character
		  letter=settings->getThirdChar();
		  if (letter>65) 
		  {
			settings->setThirdChar(--letter);
		  }
		  else 
		  {
			settings->setThirdChar('Z');
		  }		
		  break;   
	}
	trace->event(s_fn,0,"leave");
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
			game.stateMachine=stateIntro2;
		}
		break;

		case stateIntro2:
		{
			//game.stateMachine=stateIntro3;
			game.stateMachine=stateMainMenu;
		}
		break;
	 
		case stateIntro3:
		{
			game.stateMachine=stateMainMenu;
		}
		break;
	 
		case stateMainMenu:
		{	
			if (buttons[0]->onSelect(x,y))
			{
				// Highscore button	      
				game.stateMachine=stateLocalHighScore;
				break;
			}
		
			if (buttons[1]->onSelect(x,y))
			{
				// Credits button	      
				game.stateMachine=stateHelp;
				break;
			}
		
			if (buttons[2]->onSelect(x,y))
			{
				// Credits button	      
				game.stateMachine=stateCredits;
				break;
			}
		
			if (buttons[3]->onSelect(x,y))
			{
				// Sound Settings button	      
				game.stateMachine=stateSoundSettings;
				break;
			}
		
			if (buttons[4]->onSelect(x,y))
			{
				// Release Notes button	      
				game.stateMachine=stateReleaseNotes;
				break;
			}
		
			if (buttons[5]->onSelect(x,y))
			{
				// User Initials button	      
				game.stateMachine=stateUserSettings;
				break;
			}
			
			if (buttons[6]->onSelect(x,y))
			{
				// SelectMapMenu button	      
				game.stateMachine=stateMapSelectMenu;
				break;
			}
			
			if (buttons[7]->onSelect(x,y))
			{
				// Go back to HBC button    
				game.stateMachine=stateQuit;
				break;
			}
			
			if (buttons[8]->onSelect(x,y))
			{
				// Stop rumble
				WPAD_Rumble(0,0);
			
				// Reset Wii
				SYS_ResetSystem(SYS_RESTART,0,0);		   
				break;
			}					
		}
		break;
   
		case stateMapSelectMenu:
		{	
			if (buttons[0]->onSelect(x,y))
			{
				// Map1 button	      
				game.stateMachine=stateGame;
				game.selectedMap=1;
				break;
			}
		
			if (buttons[1]->onSelect(x,y))
			{
				// Map2 button	      
				game.stateMachine=stateGame;
				game.selectedMap=2;
				break;
			}
		
			if (buttons[2]->onSelect(x,y))
			{
				// Map3 button	      
				game.stateMachine=stateGame;
				game.selectedMap=3;
				break;
			}
			
			if (buttons[3]->onSelect(x,y))
			{
				// Main Menu button	      
				game.stateMachine=stateMainMenu;
				break;
			}
		}
		break;
	
		case stateGame:
		{	
			if (weapons[game.weaponSelect]!=NULL)
			{
				if (buttons[0]->onSelect(x,y))
				{
					// Power button	      
					weapons[game.weaponSelect]->upgrade(0);
					break;
				}
		
				if (buttons[1]->onSelect(x,y))
				{
					// Range button	      
					weapons[game.weaponSelect]->upgrade(1);
					break;
				}
			
				if (buttons[2]->onSelect(x,y))
				{
					// Rate button	      		
					weapons[game.weaponSelect]->upgrade(2);
					break;
				}
				
				/*if (buttons[3]->onSelect(x,y))
				{
					// Select previous weapon	      		
					break;
				}
				
				if (buttons[4]->onSelect(x,y))
				{
					// Select next weapon	      		
					break;
				}*/
			}
		}
		break;
		
		case stateCredits:
		{
			if (buttons[0]->onSelect(x,y))
			{
				// Main Menu button	 	
				game.stateMachine=stateMainMenu;	
				break;     
			}
		}
		break;

		case stateHelp:
		{
			if (buttons[0]->onSelect(x,y))
			{
				// Main Menu button	 
				game.stateMachine=stateMainMenu;	
				break;      
			}
		}
		break;

		case stateSoundSettings:
		{
			if (buttons[0]->onSelect(x,y))
			{
				// Main Menu button	 
				game.stateMachine=stateMainMenu;	     
				break; 
			}
		}
		break;
	 
		case stateReleaseNotes:
		{
			if (buttons[0]->onSelect(x,y))
			{
				// Main Menu button	 
				game.stateMachine=stateMainMenu;	
				break;      
			}
		}
		break;

		case stateLocalHighScore:
		{
			if (buttons[0]->onSelect(x,y))
			{
				// Main Menu button	 
				game.stateMachine=stateMainMenu;	
				break;      
			}
		}
		break;
	 
		case stateUserSettings:
		{ 
			if (buttons[0]->onSelect(x,y))
			{
				// + First Character button event           
				buttonPlus(0);  
				break; 
			}
		
			if (buttons[1]->onSelect(x,y))
			{
				// - First Character button event           
				buttonMinus(0);  
				break; 
			}
						
			if (buttons[2]->onSelect(x,y))
			{
				// + Second Character button event           
				buttonPlus(1);  
				break; 
			}
		
			if (buttons[3]->onSelect(x,y))
			{
				// - Second Character button event           
				buttonMinus(1); 
				break;  
			}
					    
			if (buttons[4]->onSelect(x,y))
			{
				// + Third Character button event           
				buttonPlus(2);  
				break; 
			}
			
			if (buttons[5]->onSelect(x,y))
			{
				// - Third Character button event           
				buttonMinus(2);  
				break; 
			}
			
			if (buttons[6]->onSelect(x,y))
			{
				// Main Menu button	 
				settings->save(SETTING_FILENAME); 
				game.stateMachine=stateMainMenu;	     
				break; 
			}
		}
		break; 
	}
	
	// Check if weapon is selected
	if (game.stateMachine==stateGame)
	{
		for (int i=0;i<MAX_WEAPONS; i++)
		{
			if ((weapons[i]!=NULL) && (weapons[i]->onSelect(x,y)))
			{
				// Deselected all weapons
				for (int j=0;j<MAX_WEAPONS; j++)
				{
					if (weapons[j]!=NULL) weapons[j]->setSelected(false);
				}
				
				// Selected new weapons
				game.weaponSelect=i;
				weapons[i]->setSelected(true);
				break;
			}
		}		
	}	
	trace->event(s_fn,0,"leave");
}

void Pointer::action(void)
{
	const char *s_fn="Pointer::action";

	// Scan for button events
	WPAD_SetVRes(index, 640, 480);
	WPAD_ScanPads();
			
	u32 wpaddown = WPAD_ButtonsDown(index);
	u32 wpadup   = WPAD_ButtonsUp(index);
	u32 wpadheld = WPAD_ButtonsHeld(index);

	// Scan for ir events 
	WPAD_IR(index, &ir); 
	x=ir.sx-WSP_POINTER_X;
	xOffset=x+IR_X_OFFSET;
	y=ir.sy-WSP_POINTER_Y;
	yOffset=y+IR_Y_OFFSET;
	angle=ir.angle;
	
	if (wpaddown & BUTTON_A) 
	{
		buttonA(xOffset,yOffset); 
	}
	
	if (wpadup & BUTTON_A) 
	{
		selectedA=false;
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
				game.stateMachine=stateMapSelectMenu;
			}
			else
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
   trace->event(s_fn,0,"enter [index=%d]",index1);
  
   index = index1;
   
   trace->event(s_fn,0,"leave [void]");
}

void Pointer::setX(int x1)
{
   const char *s_fn="Pointer::setX";
   trace->event(s_fn,0,"enter [x=%d]",x1);
   
   if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
   {
      x = x1;
   }
   
   trace->event(s_fn,0,"leave [void]");
}

void Pointer::setY(int y1)
{
   const char *s_fn="Pointer::setY";
   trace->event(s_fn,0,"enter [y=%d]",y1);
   
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
   
   trace->event(s_fn,0,"leave [void]");
}

void Pointer::setAngle(int angle1)
{
   const char *s_fn="Pointer::setAngle";
   trace->event(s_fn,0,"enter [angle=%d]",angle1);
   
   if ((angle1>=0) && (angle1<=MAX_ANGLE))
   {
      angle=angle1;
   }
   
   trace->event(s_fn,0,"leave [void]");
} 

void Pointer::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Pointer::setImage";
   trace->event(s_fn,0,"enter");
   
   image = image1;
   
   trace->event(s_fn,0,"leave [void]");
}

void Pointer::setRumble(int rumble1)
{
   const char *s_fn="Pointer::setRumble";
   trace->event(s_fn,0,"enter [rumble=%d]",rumble1);
   
   rumble=rumble1;

   trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Getters
// ------------------------------

int Pointer::getX()
{
	return xOffset;
}

int Pointer::getY()
{
	return yOffset;
}
	
// ------------------------------
// The End
// ------------------------------