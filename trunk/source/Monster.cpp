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
#include "Monster.h"
#include "Trace.h"  
#include "Grid.h"  

// ------------------------------
// Variables
// ------------------------------

extern Trace trace;
extern Grid grid;
extern GXRModeObj  *rmode;

// ------------------------------
// Constructor 
// ------------------------------

Monster::Monster()
{
   const char *s_fn="Monster::Monster";
   trace.event(s_fn,0,"enter");
   
   xDirection=true;
   yDirection=true;
   visible=true;
   
   x=0;
   targetX=0;
   y=0;
   targetY=0;
   size=1;
   alfa=255;
   energy=0;
   height=0;
   width=0;
   step=0;
   pos=0;
   
   trace.event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// ------------------------------

Monster::~Monster()
{
   const char *s_fn="Monster::~Monster";
   trace.event(s_fn,0,"enter");
  
   trace.event(s_fn,0,"leave");
}


// ------------------------------
// Others
// ------------------------------
	
void Monster::properties(void)
{  
	char tmp[50];
	int size=12;
   
   if (!visible) return;
   
	sprintf(tmp, "%d", energy);
	GRRLIB_Printf2(x+8, y-14, tmp, size, COLOR_DARKBLACK); 
}

void Monster::draw(void)
{
	// Draw Monster on screen
	
	if (!visible) return;
	
	GRRLIB_DrawImg( x, y, image, 0, size, size, IMAGE_COLOR );	
}

void Monster::move(void)
{  
    if (!visible) return;
	
	if (delay>0)
	{
		delay--;
	}
	else
	{
		if ((x==targetX) && (y==targetY))
		{
			// Target Postion reached. Get new target position
			targetX=grid.getLocationX(pos);
			targetY=grid.getLocationY(pos);
			pos++;
			if (pos>=grid.getMaxLocations())	
			{
				// Monster has reach the final destination (Base)
				visible=false;
			}
		}
		else if (x<targetX)
		{
			x=x+step;
		}
		else if (x>targetX)
		{
			x=x-step;	
		}
			
		if (y<targetY)
		{
			y=y+step;
		}
		else if (y>targetY)
		{
			y=y-step;	
		}
	}
}

// ------------------------------
// Setters and getters 
// ------------------------------

void Monster::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Monster::setImage";
   trace.event(s_fn,0,"enter");
   
   image = image1;
   
   height=image->h;
   width=image->w;

   pos = 0;
   visible=true;
   
   x=grid.getLocationX(pos);
   targetX=x;
			
   targetY=grid.getLocationY(pos);
   targetY=y;
   
   pos++;
   
   trace.event(s_fn,0,"leave");
}

void Monster::setStep(int step1)
{
   const char *s_fn="Monster::setStep";
   trace.event(s_fn,0,"enter [step=%d]",step1);
   
   if ((step1>=0) && (step1<=MAX_STEP))
   {
      step=step1;
   } 
   
   trace.event(s_fn,0,"leave");
}

void Monster::setDelay(int delay1)
{
	delay=delay1;
}

void Monster::setEnergy(int energy1)
{
	energy=energy1;
}

int Monster::getX()
{
	return x;
}

int Monster::getY()
{
	return y;
}
		
int Monster::getAlfa(void)
{
   return alfa;
}

int Monster::getStep(void)
{
   return step;
}

// ------------------------------
// The end
// ------------------------------
