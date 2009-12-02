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

extern Grid *grid;

extern GXRModeObj *rmode;

// ------------------------------
// Constructor 
// ------------------------------

Monster::Monster()
{
   const char *s_fn="Monster::Monster";
   trace.event(s_fn,0,"enter");
   
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
   visible=true;
   
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
	
// Draw Monster on screen
void Monster::draw(void)
{
    char tmp[50];
	
	if (!visible) return;
	
	GRRLIB_DrawImg( x, y, image, 0, size, size, IMAGE_COLOR );	
	
	sprintf(tmp, "%d", energy);
	GRRLIB_Printf2(x+8, y-14, tmp, 12, COLOR_DARKBLACK); 
}

void Monster::move(void)
{  
	if (startDelay>0)
	{
		startDelay--;
		if (startDelay==0)
		{
			// First movement on screen. Make monster visible!
			visible=true;
		}
	}
	else
	{
		if ((x==targetX) && (y==targetY))
		{
			// Get new target postion 
			targetX=grid->getLocationX(pos);
			targetY=grid->getLocationY(pos);
			pos++;
			if (pos>=grid->getMaxLocations())	
			{
				// Monster has reach the final destination. Disable it!
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
// Setters 
// ------------------------------

void Monster::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Monster::setImage";
   trace.event(s_fn,0,"enter");
   
   image = image1;
   
   height=image->h;
   width=image->w;

   pos = 0;
   
   x=grid->getLocationX(pos);
   targetX=x;
			
   y=grid->getLocationY(pos);
   targetY=y;

   visible=false;
   
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

void Monster::setStartDelay(int startDelay1)
{
	startDelay=startDelay1;
}

void Monster::setEnergy(int energy1)
{
	energy=energy1;
}

void Monster::setHit(int hit)
{
	energy-=hit;
	if (energy<=0) visible=false;
}

// ------------------------------
// Getters 
// ------------------------------

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

bool Monster::getVisible(void)
{
	return visible;
}

// ------------------------------
// The end
// ------------------------------
