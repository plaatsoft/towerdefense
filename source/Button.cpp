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

extern Game    game; 
extern Trace   *trace;
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
	boolean focus=false;
	for (int i=0; i<game.maxPointers; i++)
	{
		if ((pointers[i]->getX()>=x) && (pointers[i]->getX()<=(x+width)) 
			&& (pointers[i]->getY()>=y) && (pointers[i]->getY()<=(y+height)))
		{
			// Only buttons with a label can be selected
			if (strlen(label)>0)
			{
				focus=true;	
				break;
			}
		}
	}
	
	if (focus)
	{
		GRRLIB_DrawImg( x, y, imageFocus, 0, 1, 1, IMAGE_COLOR );	
			
		// Draw Button label
		GRRLIB_Printf2(x+35, y+3, label, 16, GRRLIB_BLUE); 
			
		//pointers[i].setRumble(MAX_RUMBLE);
	}
	else
	{
		GRRLIB_DrawImg( x, y, imageNormal, 0, 1, 1, IMAGE_COLOR );	

		// Draw Button label
		GRRLIB_Printf2(x+35, y+3, label, 16, GRRLIB_WHITESMOKE); 	
	}
}


bool Button::onSelect(int x1, int y1)
{
   const char *s_fn="Button::onSelect";

   boolean selected=false;
   if ( (x1>=x) && (x1<=(x+width)) && (y1>=y) && (y1<=(y+height)) )
   {
      trace->event(s_fn,0,"enter [x=%|y=%d]",x,y);
	  trace->event(s_fn,0,"Button selected");
	  trace->event(s_fn,0,"leave");
	  
      //SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 0, (char *) effect3_pcm, effect3_pcm_size, effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
	  selected=true;
   }
   return selected;
}	   
	   
// ------------------------------
// Setters
// ------------------------------

void Button::setImageNormal(GRRLIB_texImg *imageNormal1)
{
	const char *s_fn="Button::setImageNormal";
	trace->event(s_fn,0,"enter");

	imageNormal=imageNormal1;
	height=imageNormal->h;
	width=imageNormal->w;
	
	trace->event(s_fn,0,"leave [void]");
}

void Button::setImageFocus(GRRLIB_texImg *imageFocus1)
{
	const char *s_fn="Button::setImageSelect";
	trace->event(s_fn,0,"enter");
	
	imageFocus=imageFocus1;
	
	trace->event(s_fn,0,"leave [void]");
}
		
void Button::setX(int x1)
{
	const char *s_fn="Button::setX";
	trace->event(s_fn,0,"enter [x=%d]",x1);
	
	if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
	{
		x = x1;
	}
	
	trace->event(s_fn,0,"leave [void]");
}

void Button::setY(int y1)
{
	const char *s_fn="Button::setY";
	trace->event(s_fn,0,"enter [y=%d]",y1);
	
	if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
	{
		y = y1;
	}
   
	trace->event(s_fn,0,"leave [void]");
}

void Button::setLabel(const char *label1)
{
	//const char *s_fn="Button::setLabel";
	//trace->event(s_fn,0,"enter [label=%s]",label1);
	
    strcpy(label,label1);
	
	//trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// The End
// ------------------------------