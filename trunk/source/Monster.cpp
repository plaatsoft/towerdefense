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

// ------------------------------
// Variables
// ------------------------------

extern Trace trace;

// ------------------------------
// Constructor 
// ------------------------------

Monster::Monster()
{
   const char *s_fn="Monster::Monster";
   trace.event(s_fn,0,"enter");
   
   xDirection=true;
   yDirection=true;
   
   x=0;
   y=0;
   size=1;
   alfa=255;

   height=0;
   width=0;
   step=0;
   
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
   const char *s_fn="Monster::properties";
   trace.event(s_fn,0,"enter");
   
   char tmp[50];
   int yoffset=10;
   int size=14;
   
	GRRLIB_Printf2(10, yoffset, "Characteristics of this Monster", size, COLOR_WHITESMOKE); 

	yoffset+=size;
	sprintf(tmp, "x=%d", getX());
	GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE); 

	yoffset+=size;
	sprintf(tmp, "y=%d", getY());
	GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
      
	yoffset+=size;
	sprintf(tmp, "step=%d", step);
	GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
   
    trace.event(s_fn,0,"leave");
}

void Monster::draw(void)
{
	// Draw Monster on screen
	GRRLIB_DrawImg( x, y, image, 0, size, size, IMAGE_COLOR );		
}

void Monster::move(void)
{  
	if (xDirection)
    {
      if (x<(MAX_HORZ_PIXELS-width-step)) x+=step; else xDirection=false;
    }
    else
    {
      if (x>step) x-=step; else xDirection=true;
    }
 
    if (yDirection)
    {
      if (y<(MAX_VERT_PIXELS-height-step)) y+=step; else yDirection=false;
    }
    else
    {
       if (y>step) y-=step; else yDirection=true;
    }
}

// ------------------------------
// Setters and getters 
// ------------------------------

void Monster::setX(int x1)
{
	const char *s_fn="Monster::setX";
	trace.event(s_fn,0,"enter [x=%d]",x1);
   
	if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
	{
		x = x1;
	}
	trace.event(s_fn,0,"leave [void]");
}

int Monster::getX()
{
	return x;
}

void Monster::setY(int y1)
{
   const char *s_fn="Monster::setY";
   trace.event(s_fn,0,"enter [y=%d]",y1);
   
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
   
   trace.event(s_fn,0,"leave [void]");
}

int Monster::getY()
{
	return y;
}

void Monster::setAlfa(int alfa1)
{
   const char *s_fn="Monster::setAlfa";
   trace.event(s_fn,0,"enter [alfa=%d]",alfa1);
   
   if ((alfa1>=0) && (alfa1<=MAX_ALFA))
   {
      alfa=alfa1;
   }
   
    trace.event(s_fn,0,"leave");
}
		
int Monster::getAlfa(void)
{
   return alfa;
}

void Monster::setSize(float size1)
{
   const char *s_fn="Monster::setSize";
   trace.event(s_fn,0,"enter [size=%d]",size);
   
   if ((size>=0) && (size1<=MAX_SIZE))
   {
     size=size1;
   }
   
   trace.event(s_fn,0,"leave");
}

float Monster::getSize(void)
{
   return size;
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

int Monster::getStep(void)
{
   return step;
}

void Monster::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Monster::setImage";
   trace.event(s_fn,0,"enter");
   
   image = image1;
   
   height=image->h;
   width=image->w;
   
   trace.event(s_fn,0,"leave");
}

 
// ------------------------------
// The end
// ------------------------------
