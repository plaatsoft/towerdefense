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
#include "Sound.h"

// ------------------------------
// Variables
// ------------------------------

extern Game game;
extern Trace *trace;
extern Grid *grids[MAX_GRIDS];
extern Sound *sound;
extern GXRModeObj *rmode;

// ------------------------------
// Constructor 
// ------------------------------

Monster::Monster()
{
   const char *s_fn="Monster::Monster";
   trace->event(s_fn,0,"enter");
   
   x=0;
   targetX=0;
   y=0;
   targetY=0;
   size=1;
   index=0;
   
   alfa=255;
   energy=0.0;
   maxEnergy=0.0;
   
   height=0;
   width=0;
   step=0;
   pos=0;
   grid=0;  
   visible=false;
   
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// ------------------------------

Monster::~Monster()
{
   const char *s_fn="Monster::~Monster";
   trace->event(s_fn,0,"enter");
  
   trace->event(s_fn,0,"Monster [%d] destroyed", index);
  
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Others
// ------------------------------
	
// Draw Monster on screen
void Monster::draw(int xOffset, int yOffset, float size1)
{
	if (visible) 	
	{	
		// Draw monster on screen
		GRRLIB_DrawImg( (x/size1)+xOffset, (y/size1)+yOffset, 
			image, 0, (size/size1), (size/size1), IMAGE_COLOR );
	}
}

// Draw Monster text on screen
void Monster::text(void)
{
   char tmp[5];
	
	if (visible) 
	{
		sprintf(tmp, "%2.0f", energy);
		GRRLIB_Printf2(x+8, y-14, tmp, 12, 0x000000); 
	}
}

// Move Monster
bool Monster::move(void)
{  	
	const char *s_fn="Monster::move";
		
	if (delay>0)
	{
		delay--;
		if (delay==0)
		{
			visible=true;			
			if (game.stateMachine==stateGame) sound->effect(SOUND_START);	
		}
		return false;
	}

	if ((abs(x-targetX)<=step) && (abs(y-targetY)<=step))
	{
		// Set monster on target position.
		x=targetX;
		y=targetY;
		
		// and get new target position 
		targetX=grids[grid]->getLocationX(pos);
		targetY=grids[grid]->getLocationY(pos);
		pos++;
		if (pos>=grids[grid]->getMaxLocations())	
		{
			trace->event(s_fn,0,"Monster %d has reach the final destination.", index);
			visible=false;
			
			if (game.stateMachine==stateGame) sound->effect(SOUND_FINISH);	
			return true;
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
	else if (y<targetY)
	{
		y=y+step;
	}
	else if (y>targetY)
	{
		y=y-step;	
	}	
	return false;
}

int Monster::hit(int hit)
{
	const char *s_fn="Monster::hit";
	
	energy-=hit;
	if (energy<=0) 
	{
		trace->event(s_fn,0,"Monster %d is dead!", index);
		energy=0;
	}
	
	return energy;
}

// ------------------------------
// Setters 
// ------------------------------

void Monster::setImage(GRRLIB_texImg *image1)
{   
   image = image1;
   
   height=image->h;
   width=image->w;
}

void Monster::setStep(int step1)
{
   const char *s_fn="Monster::setStep";
   trace->event(s_fn,0,"%d",step1);
   
   step=step1;
}

void Monster::setDelay(int delay1)
{ 
	const char *s_fn="Monster::setDelay";
    trace->event(s_fn,0,"%d",delay1);   
	
	delay=delay1;
	visible=false;
}

void Monster::setEnergy(int energy1)
{
	const char *s_fn="Monster::setEnergy";
    trace->event(s_fn,0,"%d",energy1);  
	
	energy=energy1;
	maxEnergy=energy;
}

void Monster::setIndex(int index1)
{
	const char *s_fn="Monster::setIndex";
    trace->event(s_fn,0,"%d",index1);  
	
	index=index1;
}

void Monster::setGrid(int grid1)
{
	const char *s_fn="Monster::setGrid";
   trace->event(s_fn,0,"%d",grid1);  
	
	grid=grid1;
	
	pos = 0;
   
   x=grids[grid]->getLocationX(pos);
   targetX=x;
			
   y=grids[grid]->getLocationY(pos);
   targetY=y;

   pos++;
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

int Monster::getMaxEnergy(void)
{
   return maxEnergy;
}

int Monster::getGrid(void)
{
   return grid;
}

// ------------------------------
// The end
// ------------------------------
