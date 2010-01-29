/** 
 *  @file 
 *  @brief The file contains the Button class
 *
 *  Created by wplaat (www.plaatsoft.nl)
 *
 *  Copyright (C) 2009-2010
 *  =======================
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
 
#include <wiiuse/wpad.h>

#include "General.h"
#include "GRRLIB.h"
#include "Button.h"
#include "Trace.h"
#include "Sound.h" 
#include "Pointer.h"

extern Game    game; 
extern Trace   *trace;
extern Sound   *sound;
extern Pointer *pointers[MAX_POINTERS];

// ------------------------------
// Constructor
// ------------------------------

/**
 * Constructor
 * Init all properties with default values.
 */
Button::Button()
{
	const char *s_fn="Button::Button";
	trace->event(s_fn,0,"enter");

	x=0;
	y=0;	
	height=0;
	width=0;
	index=0;
   
	for (int i=0; i<MAX_POINTERS; i++)
	{
		rumble[i]=false;
	}
   
	trace->event(s_fn,0,"leave [void]");
}
	
// ------------------------------
// Destructor
// ------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
Button::~Button()
{
   const char *s_fn="Button::~Button";
   trace->event(s_fn,0,"enter");

   trace->event(s_fn,0,"Button [%d] destroyed", index);
   
   trace->event(s_fn,0,"leave [void]");  
}

// ------------------------------
// Others
// ------------------------------

/**
 * Draw Button on screen.
 */
void Button::draw()
{
	focus=false;
	
	for (int i=0; i<MAX_POINTERS; i++)
	{
		if (pointers[i]!=NULL)
		{	
			if ( (pointers[i]->getXOffset()>=(x+3)) && 
			     (pointers[i]->getXOffset()<=(x+width+3))	&& 
				 (pointers[i]->getYOffset()>=(y-3)) && 
				 (pointers[i]->getYOffset()<=(y+height+3)))
			{
				focus=true;	
				
				if (!rumble[i])
				{
					pointers[i]->setRumble(MAX_RUMBLE);
					rumble[i]=true;
				}
			}
			else
			{
				rumble[i]=false;	
			}
		}
	}
	
	if (focus)
	{
		GRRLIB_DrawImg( x, y, imageFocus, 0, 1, 1, color );	
	}
	else
	{
		GRRLIB_DrawImg( x, y, imageNormal, 0, 1, 1, color );	
		
	}
}

/**
 * Draw Button text on screen.
 * @param offset The text offset in pixels.
 */
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

/**
 * Detect if button is selected
 * @param x1 The WiiMote pointer x position.
 * @param y1 The WiiMote pointer y position.
 * @param clickEffect The wanted click sound effect (true=on, false=off)
 */
bool Button::onSelect(int x1, int y1, bool clickEffect)
{
   const char *s_fn="Button::onSelect";
   trace->event(s_fn,0,"enter [x=%d|y=%d]",x1,y1);

   boolean selected=false;
   if ( (x1>=(x-3)) && (x1<=(x+width+3)) && (y1>=(y-3) && (y1<=(y+height+3))) )
   {      
	  trace->event(s_fn,0,"Selected");
	  
	  // Click sound
	  if (clickEffect) sound->effect(SOUND_CLICK);
	  selected=true;
   }
   else
   {
	  trace->event(s_fn,0,"No selected");
	  selected=false;
   }
   trace->event(s_fn,0,"leave");
   
   return selected;
}	   
	   
// ------------------------------
// Setters
// ------------------------------

/**
 * Set x postion.
 * @param x1 The X position of the button.
 */		
void Button::setX(int x1)
{
	const char *s_fn="Button::setX";
	trace->event(s_fn,0,"%d",x1);
	
	if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
	{
		x = x1;
	}
}

/**
 * Set y postion.
 * @param y1 The Y position of the button.
 */
void Button::setY(int y1)
{
	const char *s_fn="Button::setY";
	trace->event(s_fn,0,"%d",y1);
	
	if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
	{
		y = y1;
	}
}

/**
 * Set index of button.
 * @param index1 The index of the button.
 */
void Button::setIndex(int index1)
{
	const char *s_fn="Button::setIndex";
	trace->event(s_fn,0,"%d",index1);
	
    index=index1;
}

/**
 * Set label of button.
 * @param label1 The text label of the button.
 */
void Button::setLabel(const char *label1)
{	
    strcpy(label,label1);
}

/**
 * Set color of the button.
 * @param color1 The color of the button in RGB format.
 */
void Button::setColor(u32 color1)
{	
    color=color1;
}

/**
 * Set normal button image.
 * @param imageNormal1 The no focus image.
 */
void Button::setImageNormal(GRRLIB_texImg *imageNormal1)
{
	imageNormal=imageNormal1;
	height=imageNormal->h;
	width=imageNormal->w;
}

/**
 * Set focus button image.
 * @param imageFocus1 The focus image.
 */
void Button::setImageFocus(GRRLIB_texImg *imageFocus1)
{	
	imageFocus=imageFocus1;
}

// ------------------------------
// Getters
// ------------------------------

/**
 * Get X position of button.
 * @return The current X position of the button.
 */
int Button::getX(void)
{
    return x;
}

/**
 * Get Y position of button.
 * @return The current Y position of the button.
 */
int Button::getY(void)
{
    return y;
}

// ------------------------------
// The End
// ------------------------------