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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "General.h"
#include "GRRLIB.h"
#include "Pointer.h"
#include "Trace.h"
  
// ------------------------------
// Constructor 
// ------------------------------

Pointer::Pointer()
{
   x=0;
   y=0;
   angle=0;
}

// ------------------------------
// Destructor
// ------------------------------

Pointer::~Pointer()
{
  
}

// ------------------------------
// Others
// ------------------------------

void Pointer::draw(void)
{   
   // Scan for button events
   WPAD_SetVRes(0, 640, 480);
   WPAD_ScanPads();
			
   u32 wpaddown = WPAD_ButtonsDown(0);
		
   // Scan for ir events 
	WPAD_IR(0, &ir); 
	x=ir.sx-WSP_POINTER_X;
	xOffset=x+IR_X_OFFSET;
	y=ir.sy-WSP_POINTER_Y;
	yOffset=y+IR_Y_OFFSET;
	angle=ir.angle;
				
	// Scan for button events
	if (wpaddown & WPAD_BUTTON_HOME) 
	{
	  exit(0);
	}
				
    // Draw Pointer on screen
    GRRLIB_DrawImg( x, y, image, angle, image->w, image->h, IMAGE_COLOR );		
}

void Pointer::mouse(int x, int y)
{

}

boolean Pointer::onClick(void)
{
   
   return false;
}

// ------------------------------
// Setters and getters 
// ------------------------------

void Pointer::setX(int x1)
{
   if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
   {
      x = x1;
   }
}

void Pointer::setY(int y1)
{
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
}

void Pointer::setAngle(int angle1)
{
   if ((angle1>=0) && (angle1<=MAX_ANGLE))
   {
      angle=angle1;
   }
} 

void Pointer::setImage(GRRLIB_texImg *image1)
{
   image = image1;
}

// ------------------------------
// The End
// ------------------------------