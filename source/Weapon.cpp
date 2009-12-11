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

extern GXRModeObj   *rmode;
extern Game 		game; 
extern Trace    	*trace;

// ------------------------------
// Constructor 
// ------------------------------

Weapon::Weapon()
{
   const char *s_fn="Weapon::Weapon";
   trace->event(s_fn,0,"enter");
   
   x=0;
   y=0;
   
   height=0;
   width=0;
   
   alfa=255;   
   angle=0;
   targetAngle=0;
   delay=0;
   selected=false;
   index=0;
   
   power=0;
   range=0;   
   rate=0;
   
   powerPrice=0;
   rangePrice=0;
   ratePrice=0;
      
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
	
void Weapon::draw()
{
	if (selected)
	{	
		GRRLIB_Circle(x+16, y+16, range, IMAGE_COLOR3, 1);
	}
	
	// Draw Weapon on screen
	GRRLIB_DrawImg( x, y, image, angle, 1, 1, IMAGE_COLOR );				
}

void Weapon::text()
{
	char tmp[50];
	int size=12;
		
	// Draw fire delay counter on screen
	sprintf(tmp, "%d", (delay/10));
	GRRLIB_Printf2(x+6, y-16, tmp, size, GRRLIB_BLACK); 		
}

void Weapon::fire(Monster *monsters[MAX_MONSTERS])
{
	if (delay>0) 
	{
		delay--;
	}
	else
	{
		// fire
		for (int i=0; i<MAX_MONSTERS; i++)
		{			
			if (monsters[i]!=NULL)
			{
				float distance= 
					sqrt( ( (monsters[i]->getX()-x) * (monsters[i]->getX()-x) ) + 
						  ( (monsters[i]->getY()-y) * (monsters[i]->getY()-y) ) );
						  				
				if (distance<range)
				{
					game.score+=power;
					game.cash+=power;
					
					if (monsters[i]->hit(power))
					{
						delete monsters[i];
						monsters[i]=NULL;
					}
					delay=rate;
					break;
				}
			}
		}
	}
}

void Weapon::move(void)
{  
	angle++;
	if (angle>MAX_ANGLE) angle=0;
}

int Weapon::upgrade(int type)
{
	const char *s_fn="Weapon::upgrade";
	trace->event(s_fn,0,"enter [type=%d]",type);
	
	switch (type)
	{
		// Power upgrade
		case 0:	if (game.cash>=powerPrice)
				{
					power+=1;
					trace->event(s_fn,0,"Weapon %d upgrade power to %d",index, power);
					game.cash-=powerPrice;
					powerPrice=powerPrice*2;
				}
				break;

		// Range upgrade
		case 1:	if (game.cash>=rangePrice)
				{
					range+=5;
					trace->event(s_fn,0,"Weapon %d upgrade range to %d",index, range);
					game.cash-=rangePrice;
					rangePrice=rangePrice*2;
				}
				break;

		// Rate upgrade		
		case 2:	if (game.cash>=ratePrice)
				{
					rate-=5;
					trace->event(s_fn,0,"Weapon %d upgrade rate to %d",index, rate);
					game.cash-=ratePrice;
					ratePrice=ratePrice*2;
				}
				break;
	}	
	trace->event(s_fn,0,"leave [0]");
	return 0;
}

bool Weapon::onSelect(int x1, int y1)
{   
	const char *s_fn="Weapon::onSelect";
	if ( (x1>=x) && (x1<=(x+width)) && (y1>=y) && (y1<=(y+height)) )
	{      	 	
		trace->event(s_fn,0,"Weapon %d selected", index);	
		return true;
	}
	return false;
}

// ------------------------------
// Setters 
// ------------------------------

void Weapon::setX(int x1)
{
	const char *s_fn="Weapon::setX";
	trace->event(s_fn,0,"%d",x1);
   
	if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
	{
		x = x1;
	}
}

void Weapon::setY(int y1)
{
   const char *s_fn="Weapon::setY";
   trace->event(s_fn,0,"%d",y1);
   
   if ((y1>=0) && (y1<=rmode->xfbHeight))
   {
      y = y1;
   }
}
				
void Weapon::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Weapon::setImage";
   trace->event(s_fn,0,"data");
   
   image = image1;
   
   height=image->h;
   width=image->w;
}

void Weapon::setPower(int power1)
{
   const char *s_fn="Weapon::setPower";
   trace->event(s_fn,0,"%d",power1);
   
   power=power1;
}

void Weapon::setRange(int range1)
{
   const char *s_fn="Weapon::setRange";
   trace->event(s_fn,0,"%d",range1);
   
   range=range1;
 }

void Weapon::setRate(int rate1)
{
   const char *s_fn="Weapon::setRate";
   trace->event(s_fn,0,"%d",rate1);
   
   rate=rate1;
   delay=rate;
}


void Weapon::setPowerPrice(int price)
{
   const char *s_fn="Weapon::setPowerPrice";
   trace->event(s_fn,0,"%d",price);
   
   powerPrice=price;
}

void Weapon::setRangePrice(int price)
{
	const char *s_fn="Weapon::setRangePrice";
	trace->event(s_fn,0,"%d",price);
   
	rangePrice=price;
}

void Weapon::setRatePrice(int price)
{
	const char *s_fn="Weapon::setRatePrice";
	trace->event(s_fn,0,"%d",price);
	
	ratePrice=price;
}

void Weapon::setIndex(int index1)
{
	const char *s_fn="Weapon::setIndex";
	trace->event(s_fn,0,"%d",index1);
	
	index=index1;
}

void Weapon::setSelected(int selected1)
{
	selected=selected1;
}

// ------------------------------
// Getters 
// ------------------------------

int Weapon::getPowerPrice(void)
{
	return powerPrice;
}

int Weapon::getRangePrice(void)
{
	return rangePrice;
}

int Weapon::getRatePrice(void)
{
	return ratePrice;
}
	
// ------------------------------
// The end
// ------------------------------