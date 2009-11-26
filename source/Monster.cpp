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
  
// ------------------------------
// Constructor 
// ------------------------------

Monster::Monster()
{
   xDirection=true;
   yDirection=true;
   
   x=0;
   y=0;
   size=0;
   alfa=255;
   angle=0;
   targetAngle=0;
   //image=NULL;
   height=0;
   width=0;
   step=0;
}

// ------------------------------
// Destructor
// ------------------------------

Monster::~Monster()
{
  
}


// ------------------------------
// Others
// ------------------------------
	
void Monster::properties(void)
{
   char tmp[50];
   int yoffset=10;
   int size=14;
   
   //GRRLIB_Printf2(10, yoffset, "Characteristics of this Monster", size, COLOR_WHITESMOKE); 

   yoffset+=size;
   sprintf(tmp, "x=%d", getX());
   //GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE); 

   yoffset+=size;
   sprintf(tmp, "y=%d", getY());
   //GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
   
   yoffset+=size;
   sprintf(tmp, "angle=%d", getAngle());
   //GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
   
   yoffset+=size;
   sprintf(tmp, "targetAngle=%d", targetAngle);
   //GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
   
   yoffset+=size;
   sprintf(tmp, "step=%d", step);
   //GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
}

void Monster::draw(void)
{
   // Draw Monster on screen
   GRRLIB_DrawImg( x, y, image, angle, size, size, IMAGE_COLOR );		
}

void Monster::move(void)
{  
   if (angle==targetAngle)
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
    
	 if (xDirection) 
     {
       if (yDirection) targetAngle=45; else targetAngle=45+270;
     }
     else
     {
       if (yDirection) targetAngle=45+180; else targetAngle=45+90;
	 }    	
   }

   if (angle<targetAngle)
   {
     angle+=step;
	 if (angle>MAX_ANGLE-step) angle=0;
   }
   else if (angle>targetAngle)
   {
     angle-=step;
	 if (angle<step) angle=MAX_ANGLE;
   }   
}

// ------------------------------
// Setters and getters 
// ------------------------------

void Monster::setX(int x1)
{
   if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
   {
      x = x1;
   }
}

int Monster::getX()
{
	return x;
}

void Monster::setY(int y1)
{
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
}

int Monster::getY()
{
	return y;
}

void Monster::setAlfa(int alfa1)
{
   if ((alfa1>=0) && (alfa1<=MAX_ALFA))
   {
      alfa=alfa1;
   }
}
		
int Monster::getAlfa(void)
{
   return alfa;
}

void Monster::setSize(float size1)
{
   if ((size>=0) && (size1<=MAX_SIZE))
   {
     size=size1;
   }
}

float Monster::getSize(void)
{
   return size;
}

void Monster::setAngle(int angle1)
{
   if ((angle1>=0) && (angle1<=MAX_ANGLE))
   {
      angle=angle1;
   }
} 

int Monster::getAngle(void)
{
   return angle;
}

void Monster::setWidth(int width1)
{
   if ((width1>=0) && (width1<=MAX_HORZ_PIXELS))
   {
      width=width1;
   }
}

int Monster::getWidth(void)
{
   return width;
}

void Monster::setHeight(int height1)
{
   if ((height1>=0) && (height1<=MAX_VERT_PIXELS))
   { 
      height=height1;
   }
}

int Monster::getHeight(void)
{
   return height;
}

void Monster::setStep(int step1)
{
   if ((step1>=0) && (step1<=MAX_STEP))
   {
      step=step1;
   } 
}

int Monster::getStep(void)
{
   return step;
}

void Monster::setImage(GRRLIB_texImg *image1)
{
   image = image1;
}

 

// ------------------------------
// The end
// ------------------------------
