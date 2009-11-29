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

#include "General.h"
#include "GRRLIB.h"
#include "Pointer.h"
#include "Trace.h"
  
extern Trace trace;

extern int stateMachine;
extern boolean stopApplication;

boolean selectedA=false;

// ------------------------------
// Constructor 
// ------------------------------

Pointer::Pointer()
{
   const char *s_fn="Pointer::Pointer";
   trace.event(s_fn,0,"enter");
   
   x=0;
   y=0;
   angle=0;
   
   trace.event(s_fn,0,"leave [void]");
}

// ------------------------------
// Destructor
// ------------------------------

Pointer::~Pointer()
{
  const char *s_fn="Pointer::~Pointer";
  trace.event(s_fn,0,"enter");
  
  trace.event(s_fn,0,"leave [void]");
}

// ------------------------------
// Others
// ------------------------------

void buttonA(int x, int y)
{
  const char *s_fn="Pointer::buttonA";

  if (selectedA) return;
  selectedA=true;
	  
  switch (stateMachine)
  {
     case stateIntro1:
	 {
	   trace.event(s_fn,0,"stateMachine=stateIntro2");
	   stateMachine=stateIntro2;
	 }
	 break;

	 case stateIntro2:
	 {
	   trace.event(s_fn,0,"stateMachine=stateIntro3");
	   stateMachine=stateIntro3;
	 }
	 break;
	 
	 case stateIntro3:
	 {
	   trace.event(s_fn,0,"stateMachine=stateMenu");
	   stateMachine=stateMenu;
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
	  trace.event(s_fn,0,"Home button pressed");
	  stopApplication = true;
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
   trace.event(s_fn,0,"enter [index=%d]",index1);
  
   index = index1;
   
   trace.event(s_fn,0,"leave [void]");
}

void Pointer::setX(int x1)
{
   const char *s_fn="Pointer::setX";
   trace.event(s_fn,0,"enter [x=%d]",x1);
   
   if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
   {
      x = x1;
   }
   
   trace.event(s_fn,0,"leave [void]");
}

void Pointer::setY(int y1)
{
   const char *s_fn="Pointer::setY";
   trace.event(s_fn,0,"enter [y=%d]",y1);
   
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
   
   trace.event(s_fn,0,"leave [void]");
}

void Pointer::setAngle(int angle1)
{
   const char *s_fn="Pointer::setAngle";
   trace.event(s_fn,0,"enter [angle=%d]",angle1);
   
   if ((angle1>=0) && (angle1<=MAX_ANGLE))
   {
      angle=angle1;
   }
   
   trace.event(s_fn,0,"leave [void]");
} 

void Pointer::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Pointer::setImage";
   trace.event(s_fn,0,"enter");
   
   image = image1;
   
   trace.event(s_fn,0,"leave [void]");
}

// ------------------------------
// The End
// ------------------------------