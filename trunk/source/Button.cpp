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
**
**  History:
**   24-11-2009  Create
**   27-11-2009  Add draw method with rumble support
*/

#include <wiiuse/wpad.h>

#include "General.h"
#include "GRRLIB.h"
#include "Button.h"
#include "Trace.h"

#define RUMBLE 25

extern Trace trace;

// ------------------------------
// Constructor
// ------------------------------

Button::Button()
{
   const char *s_fn="Button::Button";
   trace.event(s_fn,0,"enter");

   x=0;
   y=0;	
   height=0;
   width=0;
   rumble=RUMBLE;
   
   trace.event(s_fn,0,"leave [void]");
}


Button::Button(	int x1,
				int y1, 
				GRRLIB_texImg *imageNormal1, 
				GRRLIB_texImg *imageFocus1 )
{
   const char *s_fn="Button::Button";
   trace.event(s_fn,0,"enter");

   x = x1;
   y = y1;
   imageNormal=imageNormal1;
   imageFocus=imageFocus1;
   
   trace.event(s_fn,0,"leave [void]");
}
	
// ------------------------------
// Destructor
// ------------------------------

Button::~Button()
{

   const char *s_fn="Button::~Button";
   trace.event(s_fn,0,"enter");

   trace.event(s_fn,0,"leave [void]");  
}

// ------------------------------
// Others
// ------------------------------

void Button::draw(int pointerX, int pointerY)
{
    if ((pointerX>x) && (pointerX<x+width) 
		&& (pointerY>y) && (pointerY<y+height))
	{
		GRRLIB_DrawImg( x, y, imageNormal, 0, width, height, IMAGE_COLOR );		
	}
	else
	{
		GRRLIB_DrawImg( x, y, imageFocus, 0, width, height, IMAGE_COLOR );	
		if (rumble==0)
		{
			rumble=RUMBLE;
		}
	}
	
	if (--rumble>0)  WPAD_Rumble(0,1); else WPAD_Rumble(0,0);
}

// ------------------------------
// Getter and Setters
// ------------------------------

void Button::setImageNormal(GRRLIB_texImg *imageNormal1)
{
	const char *s_fn="Button::setImageNormal";
	trace.event(s_fn,0,"enter");

	imageNormal=imageNormal1;
	height=imageNormal->w;
	width=imageNormal->h;
	
	trace.event(s_fn,0,"leave [void]");
}

void Button::setImageSelect(GRRLIB_texImg *imageFocus1)
{
	const char *s_fn="Button::setImageSelect";
	trace.event(s_fn,0,"enter");
	
	imageFocus=imageFocus1;
	
	trace.event(s_fn,0,"leave [void]");
}
		
void Button::setX(int x1)
{
	const char *s_fn="Button::setX";
	trace.event(s_fn,0,"enter");
	
	if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
	{
		x = x1;
	}
	
	trace.event(s_fn,0,"leave [void]");
}

void Button::setY(int y1)
{
	const char *s_fn="Button::setY";
	trace.event(s_fn,0,"enter");
	
	if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
	{
		y = y1;
	}
   
	trace.event(s_fn,0,"leave [void]");
}

// ------------------------------
// The End
// ------------------------------