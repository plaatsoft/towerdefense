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
*/

#include <wiiuse/wpad.h>

#include "General.h"
#include "GRRLIB.h"
#include "Button.h"
#include "Pointer.h"
#include "Trace.h"

extern Trace trace;
extern Pointer pointer[MAX_POINTERS];

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

void Button::draw()
{
	boolean focus=false;
	for (int i=0; i<MAX_POINTERS; i++)
	{
		if ((pointer[i].getX()>=x) && (pointer[i].getX()<=(x+width)) 
			&& (pointer[i].getY()>=y) && (pointer[i].getY()<=(y+height)))
		{
			GRRLIB_DrawImg( x, y, imageFocus, 0, 1, 1, IMAGE_COLOR );	
		    focus=true;
			pointer[i].setRumble(MAX_RUMBLE);
			break;
		}
	}
	if (!focus)
	{
		GRRLIB_DrawImg( x, y, imageNormal, 0, 1, 1, IMAGE_COLOR );		
	}
	
	// Draw Button label
    GRRLIB_Printf2((200-((strlen(label)*7)/2)), y+5, label, 18, COLOR_WHITESMOKE);  
}


boolean Button::onSelect(int x1, int y1)
{
   boolean selected=false;
   if ( (x1>=x) && (x1<=(x+width)) && (y1>=y) && (y1<=(y+height)) )
   {
      //SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 0, (char *) effect3_pcm, effect3_pcm_size, effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
	  selected=true;
   }
   return selected;
}	   
	   
// ------------------------------
// Getter and Setters
// ------------------------------

void Button::setImageNormal(GRRLIB_texImg *imageNormal1)
{
	const char *s_fn="Button::setImageNormal";
	trace.event(s_fn,0,"enter");

	imageNormal=imageNormal1;
	height=imageNormal->h;
	width=imageNormal->w;
	
	trace.event(s_fn,0,"leave [void]");
}

void Button::setImageFocus(GRRLIB_texImg *imageFocus1)
{
	const char *s_fn="Button::setImageSelect";
	trace.event(s_fn,0,"enter");
	
	imageFocus=imageFocus1;
	
	trace.event(s_fn,0,"leave [void]");
}
		
void Button::setX(int x1)
{
	const char *s_fn="Button::setX";
	trace.event(s_fn,0,"enter [x=%d]",x1);
	
	if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
	{
		x = x1;
	}
	
	trace.event(s_fn,0,"leave [void]");
}

void Button::setY(int y1)
{
	const char *s_fn="Button::setY";
	trace.event(s_fn,0,"enter [y=%d]",y1);
	
	if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
	{
		y = y1;
	}
   
	trace.event(s_fn,0,"leave [void]");
}

void Button::setLabel(const char *label1)
{
	const char *s_fn="Button::setLabel";
	trace.event(s_fn,0,"enter [label=%s]",label1);
	
    strcpy(label,label1);
	
	trace.event(s_fn,0,"leave [void]");
}

// ------------------------------
// The End
// ------------------------------