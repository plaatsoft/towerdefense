#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GRRLIB.h"
#include "Enemy.h"

// ------------------------------
// Defines
// ------------------------------

#define MAX_HORZ_PIXELS		640
#define MAX_VERT_PIXELS		480
#define MAX_ANGLE			360
#define MAX_ALFA			255
#define MAX_STEP		    25
#define MAX_SIZE		    2
#define COLOR_WHITESMOKE    0xFFFFFF

// ------------------------------
// Constructor // Destructor
// ------------------------------

Enemy::Enemy()
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

Enemy::Enemy(int x1,int y1, int height1, int width1, float size1, int angle1, int alfa1, GRRLIB_texImg image1 )
{
   xDirection=true;
   yDirection=true;
   step=1;
   targetAngle=angle1;
   
   x = x1;
   y = y1;
   height=height1;
   width=width1;
   size=size1;
   alfa=alfa1;
   angle=angle1;
   image=image1;
}

Enemy::~Enemy()
{
  
}

// ------------------------------
// Setters
// ------------------------------

void Enemy::setX(int x1)
{
   if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
   {
      x = x1;
   }
}

void Enemy::setY(int y1)
{
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
}

void Enemy::setAlfa(int alfa1)
{
   if ((alfa1>=0) && (alfa1<=MAX_ALFA))
   {
      alfa=alfa1;
   }
}

void Enemy::setAngle(int angle1)
{
   if ((angle1>=0) && (angle1<=MAX_ANGLE))
   {
      angle=angle1;
   }
} 

void Enemy::setSize(float size1)
{
   if ((size>=0) && (size1<=MAX_SIZE))
   {
     size=size1;
   }
}

void Enemy::setWidth(int width1)
{
   if ((width1>=0) && (width1<=MAX_HORZ_PIXELS))
   {
      width=width1;
   }
}

void Enemy::setHeight(int height1)
{
   if ((height1>=0) && (height1<=MAX_VERT_PIXELS))
   { 
      height=height1;
   }
}

void Enemy::setStep(int step1)
{
   if ((step1>=0) && (step1<=MAX_STEP))
   {
      step=step1;
   } 
}

// ------------------------------
// Getters
// ------------------------------

int Enemy::getX()
{
	return x;
}

int Enemy::getY()
{
	return y;
}
		
int Enemy::getAlfa(void)
{
   return alfa;
}

float Enemy::getSize(void)
{
   return size;
}

int Enemy::getAngle(void)
{
   return angle;
}

int Enemy::getWidth(void)
{
   return width;
}

int Enemy::getHeight(void)
{
   return height;
}

int Enemy::getStep(void)
{
   return step;
}

// ------------------------------
// Others
// ------------------------------
	
void Enemy::properties(void)
{
   char tmp[50];
   int yoffset=10;
   int size=14;
   
   GRRLIB_Printf2(10, yoffset, "Characteristics of this Enemy", size, COLOR_WHITESMOKE); 

   yoffset+=size;
   sprintf(tmp, "x=%d", getX());
   GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE); 

   yoffset+=size;
   sprintf(tmp, "y=%d", getY());
   GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
   
   yoffset+=size;
   sprintf(tmp, "angle=%d", getAngle());
   GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
   
   yoffset+=size;
   sprintf(tmp, "targetAngle=%d", targetAngle);
   GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
   
   yoffset+=size;
   sprintf(tmp, "step=%d", step);
   GRRLIB_Printf2(10, yoffset, tmp, size, COLOR_WHITESMOKE);
}

void Enemy::draw(void)
{
   // Draw wiimote ir pointer
   GRRLIB_DrawImg( x, y, image, angle, size, size, 0xffffff );		
//inline void GRRLIB_DrawImg(f32 xpos, f32 ypos, GRRLIB_texImg tex, float degrees, float scaleX, f32 scaleY, u32 color );	 			
}

void Enemy::move(void)
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
// The end
// ------------------------------
