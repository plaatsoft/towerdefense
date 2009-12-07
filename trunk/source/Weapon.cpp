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
#include <math.h>

#include "Weapon.h" 

// ------------------------------
// Variables
// ------------------------------

extern GXRModeObj  *rmode;

extern Game game; 
extern Trace   *trace;

// ------------------------------
// Constructor 
// ------------------------------

Weapon::Weapon()
{
   const char *s_fn="Weapon::Weapon";
   trace->event(s_fn,0,"enter");
   
   x=0;
   y=0;
   alfa=255;
   angle=0;
   targetAngle=0;
   height=0;
   width=0;
   step=0;
   range=0;
   power=0;
   delay=0;
   actualDelay=0;
   
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// ------------------------------

Weapon::~Weapon()
{
   const char *s_fn="Weapon::~Weapon";
   trace->event(s_fn,0,"enter");
  
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Others
// ------------------------------
	
void Weapon::draw(Pointer *pointers[MAX_POINTERS])
{
	char tmp[50];
	int size=12;
	
	// Draw range circle if pointer is on weapon 
	for (int i=0; i<MAX_POINTERS; i++)
	{
		if (pointers[i]!=NULL)
		{
			if ((x>=pointers[i]->getX()) && (x+width<=pointers[i]->getX()))
			{
				if ((y>=pointers[i]->getY()) && (y+height<=pointers[i]->getY()))
				{
					GRRLIB_Circle(x + 16, y + 16, range, GRRLIB_OLIVE, 1);
				}
			}
		}
	}
	
	// Draw Weapon on screen
	GRRLIB_DrawImg( x, y, image, angle, 1, 1, IMAGE_COLOR );		

	// Draw energy level on screen
	sprintf(tmp, "%d", actualDelay);
	GRRLIB_Printf2(x, y, tmp, size, GRRLIB_BLACK); 		
}

void Weapon::fire(Monster *monsters[MAX_MONSTERS])
{
	if (actualDelay>0) 
	{
		actualDelay--;
	}
	else
	{
		// fire
		for (int i=0; i<MAX_MONSTERS; i++)
		{			
			if (monsters[i]!=NULL)
			{
				if ( !monsters[i]->getDead() )
				{
					float distance= 
						sqrt( ( (monsters[i]->getX()-x) * (monsters[i]->getX()-x) ) + 
				 	  	  ( (monsters[i]->getY()-y) * (monsters[i]->getY()-y) ) );
						  				
					if (distance<range)
					{
						game.score+=power;
						monsters[i]->setHit(power);
						actualDelay=delay;
						break;
					}
				}
			}
		}
	}
}

void Weapon::move(void)
{  
	angle=angle+step;
	if (angle>MAX_ANGLE) angle=0;
}

// ------------------------------
// Setters 
// ------------------------------

void Weapon::setX(int x1)
{
	const char *s_fn="Weapon::setX";
	trace->event(s_fn,0,"enter [x=%d]",x1);
   
	if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
	{
		x = x1;
	}
	trace->event(s_fn,0,"leave [void]");
}

void Weapon::setY(int y1)
{
   const char *s_fn="Weapon::setY";
   trace->event(s_fn,0,"enter [y=%d]",y1);
   
   if ((y1>=0) && (y1<=rmode->xfbHeight))
   {
      y = y1;
   }
   
   trace->event(s_fn,0,"leave [void]");
}

void Weapon::setAlfa(int alfa1)
{
   const char *s_fn="Weapon::setAlfa";
   trace->event(s_fn,0,"enter [alfa=%d]",alfa1);
   
   if ((alfa1>=0) && (alfa1<=MAX_ALFA))
   {
      alfa=alfa1;
   }
   
    trace->event(s_fn,0,"leave");
}
		
void Weapon::setAngle(int angle1)
{
   const char *s_fn="Weapon::setAngle";
   trace->event(s_fn,0,"enter [angle=%d]",angle1);
   
   if ((angle1>=0) && (angle1<=MAX_ANGLE))
   {
      angle=angle1;
   } 
   
   trace->event(s_fn,0,"leave");
}
		
void Weapon::setStep(int step1)
{
   const char *s_fn="Weapon::setStep";
   trace->event(s_fn,0,"enter [step=%d]",step1);
   
   if ((step1>=0) && (step1<=MAX_STEP))
   {
      step=step1;
   } 
   
   trace->event(s_fn,0,"leave");
}

void Weapon::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Weapon::setImage";
   trace->event(s_fn,0,"enter");
   
   image = image1;
   
   height=image->h;
   width=image->w;
   
   trace->event(s_fn,0,"leave");
}

void Weapon::setDelay(int delay1)
{
   const char *s_fn="Weapon::setDelay";
   trace->event(s_fn,0,"enter [delay=%d]",delay1);
   
   delay=delay1;
   actualDelay=delay;
   
   trace->event(s_fn,0,"leave");
}

void Weapon::setRange(int range1)
{
   const char *s_fn="Weapon::setRange";
   trace->event(s_fn,0,"enter [range=%d]",range1);
   
   range=range1;
   
   trace->event(s_fn,0,"leave");
}

void Weapon::setPower(int power1)
{
   const char *s_fn="Weapon::setPower";
   trace->event(s_fn,0,"enter [power=%d]",power1);
   
   power=power1;
   
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// The end
// ------------------------------