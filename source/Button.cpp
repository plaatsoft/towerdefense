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

#include <wiiuse/wpad.h>

#include "General.h"
#include "GRRLIB.h"
#include "Button.h"
#include "Pointer.h"
#include "Trace.h"
#include "Sound.h" 

extern Game    game; 
extern Trace   *trace;
extern Sound   *sound;
extern Pointer *pointers[MAX_POINTERS];

// ------------------------------
// Constructor
// ------------------------------

Button::Button()
{
   const char *s_fn="Button::Button";
   trace->event(s_fn,0,"enter");

   x=0;
   y=0;	
   height=0;
   width=0;
   
   trace->event(s_fn,0,"leave [void]");
}
	
// ------------------------------
// Destructor
// ------------------------------

Button::~Button()
{
   const char *s_fn="Button::~Button";
   trace->event(s_fn,0,"enter");

   trace->event(s_fn,0,"leave [void]");  
}

// ------------------------------
// Others
// ------------------------------

void Button::draw()
{
	focus=false;
	for (int i=0; i<MAX_POINTERS; i++)
	{
		if (pointers[i]!=NULL)
		{	
			if ((pointers[i]->getXOffset()>=x) && (pointers[i]->getXOffset()<=(x+width)) 
				&& (pointers[i]->getYOffset()>=y) && (pointers[i]->getYOffset()<=(y+height)))
			{
				// Only buttons with a label can be selected
				//if (strlen(label)>0)
				{
					focus=true;	
					break;
				}
			}
		}
	}
	
	if (focus)
	{
		GRRLIB_DrawImg( x, y, imageFocus, 0, 1, 1, color );	
		//pointers[i].setRumble(MAX_RUMBLE);
	}
	else
	{
		GRRLIB_DrawImg( x, y, imageNormal, 0, 1, 1, color );	
	}
}

void Button::text(int offset)
{	
	if (focus)
	{
		GRRLIB_Printf2(x+35+offset, y+3, label, 16, GRRLIB_BLUE); 
	}
	else
	{
		GRRLIB_Printf2(x+35+offset, y+3, label, 16, GRRLIB_WHITESMOKE); 	
	}
}

bool Button::onSelect(int x1, int y1)
{
   const char *s_fn="Button::onSelect";
   trace->event(s_fn,0,"enter [x=%d|y=%d]",x1,y1);

   boolean selected=false;
   if ( (x1>=x) && (x1<=(x+width)) && (y1>=y) && (y1<=(y+height)) )
   {      
	  trace->event(s_fn,0,"Button selected");
	  
	  // Click
	  sound->effect(SOUND_CLICK);
	  selected=true;
   }
   else
   {
	  trace->event(s_fn,0,"No button selected");
	  selected=false;
   }
   trace->event(s_fn,0,"leave");
   
   return selected;
}	   
	   
// ------------------------------
// Setters
// ------------------------------

void Button::setImageNormal(GRRLIB_texImg *imageNormal1)
{
	const char *s_fn="Button::setImageNormal";
	trace->event(s_fn,0,"image");

	imageNormal=imageNormal1;
	height=imageNormal->h;
	width=imageNormal->w;
}

void Button::setImageFocus(GRRLIB_texImg *imageFocus1)
{
	const char *s_fn="Button::setImageSelect";
	trace->event(s_fn,0,"image");
	
	imageFocus=imageFocus1;
}
		
void Button::setX(int x1)
{
	const char *s_fn="Button::setX";
	trace->event(s_fn,0,"%d",x1);
	
	if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
	{
		x = x1;
	}
}

void Button::setY(int y1)
{
	const char *s_fn="Button::setY";
	trace->event(s_fn,0,"%d",y1);
	
	if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
	{
		y = y1;
	}
}

void Button::setLabel(const char *label1)
{
	//const char *s_fn="Button::setLabel";
	//trace->event(s_fn,0,"%s",label1);
	
    strcpy(label,label1);
}

void Button::setColor(u32 color1)
{
	//const char *s_fn="Button::setColor";
	//trace->event(s_fn,0,"%s",label1);
	
    color=color1;
}

// ------------------------------
// The End
// ------------------------------