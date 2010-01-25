/*  
**  Created by wplaat (www.plaatsoft.nl)
**
**  Copyright (C) 2009-2010
**  =======================
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

/**
 * Constructor
 * Init all properties with default values.
 */
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
	frameCounter=0;
	frameStep=0;
	state=stateEnemyWaiting;
	prevState=stateEnemyWaiting;
   
	moveUp=false;
	moveDown=false;
	moveRight=false;
	moveLeft=false;
	
   alfa=255;
   energy=0.0;
   
   height=0;
   width=0;
   step=0;
   pos=0;
   grid=0;  
   
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// ------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
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
	
//n1 	e1 	s1 	w1
//n2 	e2 	s2 	w2
//n3 	e3 	s3 	w3
//d1 	d2 	d3 	d4 

int Monster::getFrame(void)
{	
	if (height==32) 
	{
		// No animation sprite available, direct dead!;
		if (state==stateEnemyDying)
		{
			state=stateEnemyDead;
		}
		return 0;
	}
	
	// Enemy stopped freece animation
	if (state==stateEnemyStopped)
	{
	   return frame;
	}
	
	// Check framecounter every X screen frames the sprite change.
	if (frameCounter!=0) 
	{
		frameCounter--; 
		
		// return previous frame
		return frame;
	}
	
	if (state==stateEnemyMoving)
	{
		frameCounter=3;
	
		if (moveUp)
		{
			switch (frameStep)
			{
				case 0:  frame=0;
							frameStep++;
							break;
					  
				case 1:  frame=4;
							frameStep++;
							break;
						
				case 2:  frame=0;
							frameStep++;
							break;
							
				case 3:  frame=8;
							frameStep=0;
							break;
			}
		}
					
		if (moveDown)
		{
			switch (frameStep)
			{
				case 0:  frame=2;
							frameStep++;
							break;
					  
				case 1:  frame=6;
							frameStep++;
							break;
						
				case 2:  frame=2;
							frameStep++;
							break;
							
				case 3:  frame=10;
							frameStep=0;
							break;
			}
		}
	
		if (moveRight)
		{
			switch (frameStep)
			{
				case 0:  frame=1;
							frameStep++;
							break;
					  
				case 1:  frame=5;
							frameStep++;
							break;
							
				case 2:  frame=1;
							frameStep++;
							break;
						
				case 3:  frame=9;
							frameStep=0;
							break;
			}		
		}
	
		if (moveLeft)
		{
			switch (frameStep)
			{
				case 0:  frame=3;
							frameStep++;
							break;
					  
				case 1:  frame=7;
							frameStep++;
							break;
						
				case 2:  frame=3;
							frameStep++;
							break;
							
				case 3:  frame=11;
							frameStep=0;
							break;	
			}
		}
	}
	
	if (state==stateEnemyDying)
	{
		frameCounter=3;
	
		switch (frameStep)
		{
			case 0:  frame=12;
						frameStep++;
					   break;
					  
			case 1:  frame=13;
						frameStep++;
					   break;
						
			case 2:  frame=14;
						frameStep++;
						break;
						
			case 3:  frame=15;
						frameStep++;
						break;
						
			case 4:  state=stateEnemyDead;
						break;
		} 
	}
	return frame;
}

// Draw Monster on screen
void Monster::draw(int xOffset, int yOffset, float size1)
{
	if ( (state==stateEnemyMoving) || 
		  (state==stateEnemyStopped) || 
		  (state==stateEnemyDying) )
	{				
		GRRLIB_DrawTile(  (x/size1)+xOffset, (y/size1)+yOffset, 
			image , 0, (size/size1), (size/size1), IMAGE_COLOR, getFrame());
	}
}

// Draw Monster text on screen
void Monster::text(void)
{
   char tmp[5];
	
	if ( (state==stateEnemyMoving) || 
		  (state==stateEnemyStopped) || 
		  (state==stateEnemyDying) )
	{
		sprintf(tmp, "%2.0f", energy);
		GRRLIB_Printf2(x+8, y-14, tmp, 12, 0x000000); 
	}
}

// Move Monster
void Monster::move(void)
{  	
	const char *s_fn="Monster::move";

   // If stopping state return direct
	if ((state==stateEnemyStopped) || (state==stateEnemyDying)) return;
	
	// waiting state check if delay time is zero!
	if (state==stateEnemyWaiting) 
	{	
		delay--;
		if (delay==0)
		{
			state=stateEnemyMoving;			
			if (game.stateMachine==stateGame) 
			{
				sound->effect(SOUND_START);				
			}
		}
		return;
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
			state=stateEnemyDead;
	
			// Monster has reach the final destination. Destroy it!
			game.monsterInBase++;
		
			if (game.stateMachine==stateGame) 
			{
				sound->effect(SOUND_FINISH);	
			}
		}
	}
	else if (x<targetX)
	{
		x=x+step;
		
		if (!moveRight) frameCounter=0;
		moveUp=false;
		moveDown=false;
		moveRight=true;
		moveLeft=false;
	}
	else if (x>targetX)
	{
		x=x-step;	
		
		if (!moveLeft) frameCounter=0;
		moveUp=false;
		moveDown=false;
		moveRight=false;
		moveLeft=true;
	}	
	else if (y<targetY)
	{
		y=y+step;
		
		if (!moveDown) frameCounter=0;
		moveUp=false;
		moveDown=true;
		moveRight=false;
		moveLeft=false;
	}
	else if (y>targetY)
	{
		y=y-step;	

		if (!moveUp) frameCounter=0;
		moveUp=true;
		moveDown=false;
		moveRight=false;
		moveLeft=false;
	}	
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
}

void Monster::setEnergy(int energy1)
{	
	energy=energy1;
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

void Monster::setState(int state1)
{
	prevState=state;
	state=state1;
}

void Monster::setMove(bool enabled)
{
	if (enabled)
	{
		if (state==stateEnemyStopped)
		{
			state=stateEnemyMoving;
		}
	}
	else
	{
		if (state==stateEnemyMoving)
		{
			state=stateEnemyStopped;
		}
	}
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

int Monster::getEnergy(void)
{
   return energy;
}

int Monster::getGrid(void)
{
   return grid;
}

int Monster::getIndex(void)
{
	return index;
}

int Monster::getState(void)
{
	return state;
}

// ------------------------------
// The end
// ------------------------------
