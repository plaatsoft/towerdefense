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
  
extern Game game;

extern Settings *settings;
extern Trace *trace;
extern Button *buttons[MAX_BUTTONS];

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
	GRRLIB_Printf2(10, 10, tmp, size, COLOR_WHITESMOKE); 
	
	sprintf(tmp, "y=%d", y);
	GRRLIB_Printf2(10, 20, tmp, size, COLOR_WHITESMOKE);
}

void Pointer::buttonPlus(int index)
{
  char letter;

   switch (index)
   {	 
	  case 0:
		  // First Character
		  letter=settings->getFirstChar();
		  if (letter<90) 
		  {
			settings->setFirstChar(letter++);
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
			settings->setSecondChar(letter++);
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
			settings->setThirdChar(letter++);
		  }
		  else 
		  {
			settings->setThirdChar('A');
		  }		
		  break;
   }
}

void Pointer::buttonMinus(int index)
{
   char letter;
   switch (index)   
   {
	    case 0:
		  // First Character		  
		  letter=settings->getFirstChar();
		  if (letter>65) 
		  {
			settings->setFirstChar(letter--);
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
			settings->setSecondChar(letter--);
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
			settings->setThirdChar(letter--);
		  }
		  else 
		  {
			settings->setThirdChar('Z');
		  }		
		  break;   }
}


void Pointer::buttonExit(int index)
{    
   // Stop network thread
   //tcp_stop_thread();
	
   // Stop rumble
   WPAD_Rumble(0,0);
		
   // Stop music
   //MODPlay_Stop(&snd1);
	
   // Exit game
   if (index==0)
   {   
       // Exit to loader
	   exit(0);
   }
   else
   {
       // Reset Wii
	   SYS_ResetSystem(SYS_RESTART,0,0);	
   }
}


void Pointer::buttonA(int x, int y)
{
  //const char *s_fn="Pointer::buttonA";

  if (selectedA) return;
  selectedA=true;
	  
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
	   game.stateMachine=stateMenu;
	 }
	 break;
	 
	 case stateIntro3:
	 {
	   game.stateMachine=stateMenu;
	 }
	 break;
	 
	 case stateMenu:
	 {
	    if (buttons[0]->onSelect(x,y))
		{
          // Map1 button	      
		  game.stateMachine=stateGame;
		  game.selectedMap=1;
		}
		
		if (buttons[1]->onSelect(x,y))
		{
          // Map2 button	      
		  game.stateMachine=stateGame;
		  game.selectedMap=2;
		}
		
		if (buttons[2]->onSelect(x,y))
		{
          // Map3 button	      
		  game.stateMachine=stateGame;
		  game.selectedMap=3;
		}
		
		if (buttons[3]->onSelect(x,y))
		{
          // Highscore button	      
		  game.stateMachine=stateLocalHighScore;
		}
		
		if (buttons[4]->onSelect(x,y))
		{
          // Credits button	      
		  game.stateMachine=stateHelp;
		}
		
		if (buttons[5]->onSelect(x,y))
		{
          // Credits button	      
		  game.stateMachine=stateCredits;
		}
		
		if (buttons[6]->onSelect(x,y))
		{
          // Sound Settings button	      
		  game.stateMachine=stateSound;
		}
		
		if (buttons[7]->onSelect(x,y))
		{
          // Release Notes button	      
		  game.stateMachine=stateReleaseNotes;
		}
		
		if (buttons[8]->onSelect(x,y))
		{
          // User Initials button	      
		  game.stateMachine=stateSettings;
		}
		
		if (buttons[9]->onSelect(x,y))
		{
		  buttonExit(0);
		}
		
		if (buttons[10]->onSelect(x,y))
		{
		  buttonExit(1);
		}		
	 }
	 break;
   
	 case stateCredits:
     {
        if (buttons[0]->onSelect(x,y))
	    {
           // Next button	
		   game.stateMachine=stateMenu;	     
	    }
     }
	 break;

	 case stateHelp:
     {
        if (buttons[0]->onSelect(x,y))
	    {
           // Next button	
		   game.stateMachine=stateMenu;	     
	    }
     }
	 break;

	 case stateReleaseNotes:
     {
        if (buttons[0]->onSelect(x,y))
	    {
           // Next button	
		   game.stateMachine=stateMenu;	     
	    }
     }
	 break;

	 case stateLocalHighScore:
     {
        if (buttons[0]->onSelect(x,y))
	    {
           // Next button	
		   game.stateMachine=stateMenu;	     
	    }
     }
	 break;
	 
   	 case stateSettings:
     { 
        if (buttons[0]->onSelect(x,y))
	    {
			// + First Character button event           
			buttonPlus(3);  
	    }
		
        if (buttons[1]->onSelect(x,y))
	    {
			// - First Character button event           
			buttonPlus(3);  
	    }
					

        if (buttons[2]->onSelect(x,y))
	    {
			// + Second Character button event           
			buttonPlus(4);  
	    }
		
        if (buttons[3]->onSelect(x,y))
	    {
			// - Second Character button event           
			buttonPlus(4);  
	    }
					    
        if (buttons[4]->onSelect(x,y))
	    {
			// + Third Character button event           
			buttonPlus(5);  
	    }
		
        if (buttons[5]->onSelect(x,y))
	    {
			// - Third Character button event           
			buttonMinus(5);  
	    }
		
        if (buttons[6]->onSelect(x,y))
	    {
           // Next button	
		   settings->save(SETTING_FILENAME); 
		   game.stateMachine=stateMenu;	     
	    }
		
		if (buttons[7]->onSelect(x,y))
	    {
           // Exit button
		   game.stateMachine=stateQuit;
	    }
		
		if (buttons[8]->onSelect(x,y))
	    {
           // Reset button
		   game.stateMachine=stateQuit;
	    }
     }
	 break; 
  }
}


void Pointer::draw(void)
{   
    const char *s_fn="Pointer::draw";

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
	
	if (wpaddown & BUTTON_A) buttonA(xOffset,yOffset); 
	if (wpadup & BUTTON_A) selectedA=false;

	// Scan for button events
	if (wpaddown & WPAD_BUTTON_HOME) 
	{
	  if (game.stateMachine==stateMenu)
	  {
		trace->event(s_fn,0,"Home button pressed");
		game.stateMachine=stateQuit;
	  }
	  else
	  {
		game.stateMachine=stateMenu;
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
				
    // Draw Pointer on screen
    GRRLIB_DrawImg( x, y, image, angle, 1.0, 1.0, IMAGE_COLOR );		
}

// ------------------------------
// Setters and getters 
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