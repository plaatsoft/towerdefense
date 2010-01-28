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
#include <stdarg.h>
#include <math.h>

#include "Weapon.h" 
#include "Trace.h" 
#include "Sound.h" 

// ------------------------------
// Variables
// ------------------------------

extern Game  game; 
extern Trace *trace;
extern Sound *sound;
extern Monster *monsters[MAX_MONSTERS];

// ------------------------------
// Constructor 
// ------------------------------

/**
 * Constructor
 * Init all properties with default values.
 */
Weapon::Weapon()
{
   const char *s_fn="Weapon::Weapon";
   trace->event(s_fn,0,"enter");
   
   x=0;
   y=0;
   
	angle=4;
   
	delay=0.0;
   selected=false;
   index=0;
   
   fireDelay=0;
	fireMode=FIRE_MODE_NEAREST_TO_BASE;
	
   monsterX=0;
   monsterY=0;
   
   power=0;
   range=0;   
   rate=0.0;
   
   maxPower=0;
   maxRange=0;   
   maxRate=0;
   
   powerPrice=0;
   rangePrice=0;
   ratePrice=0;

   totalPrice=0;
	
	frame=0;
	frameDelay=0;
      
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// ------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
Weapon::~Weapon()
{
   const char *s_fn="Weapon::~Weapon";
   trace->event(s_fn,0,"enter");

   trace->event(s_fn,0,"Weapon [%d] destroyed", index);
  
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// private methods
// ------------------------------

/**
 * find nearest enemy to base in range 
 *
 * @return id [-1 if no enemy is found].
 */
int Weapon::findNearestToBase(void)
{
   const char *s_fn="Weapon::findHighestEnergy";
 
   int id=-1;
	trace->event(s_fn,0,"enter");
	
	for (int i=0; i<MAX_MONSTERS; i++)
	{			
		if ((monsters[i]!=NULL) && (monsters[i]->getState()==stateEnemyMoving))
		{
			float distance= 
				sqrt( ( (monsters[i]->getX()-(x*32)) * 
							(monsters[i]->getX()-(x*32)) ) + 
					   ( (monsters[i]->getY()-(y*32)) * 
						  (monsters[i]->getY()-(y*32)) ) );
			
			if (distance<=range)
			{			  		
				id=i;
				trace->event(s_fn,0,"Monster [%d] in range", id);			
				break;
			}
		}
	}
	
	trace->event(s_fn,0,"leave [id=%d]", id);
	return id;
}

/**
 * find highest enery enemy in range 
 *
 * @return id [-1 if no enemy is found].
 */
int Weapon::findHighestEnergy(void)
{
   const char *s_fn="Weapon::findHighestEnergy";
 
   int id=-1;
	int energy=0;
	trace->event(s_fn,0,"enter");
	
	for (int i=0; i<MAX_MONSTERS; i++)
	{			
		if ((monsters[i]!=NULL) && (monsters[i]->getState()==stateEnemyMoving))
		{
			float distance= 
				sqrt( ( (monsters[i]->getX()-(x*32)) * 
							(monsters[i]->getX()-(x*32)) ) + 
					   ( (monsters[i]->getY()-(y*32)) * 
						  (monsters[i]->getY()-(y*32)) ) );
			
			if (distance<=range)
			{			  		
				if (energy < monsters[i]->getEnergy())
				{
					id=i;
					energy=monsters[i]->getEnergy();
					trace->event(s_fn,0,"Monster [%d] energy=%d in range", id, energy);
				}
			}
		}
	}
	
	trace->event(s_fn,0,"leave [id=%d]", id);
	return id;
}

/**
 * find fastest enemy in range 
 *
 * @return id [-1 if no enemy is found].
 */
int Weapon::findFastest(void)
{
   const char *s_fn="Weapon::findFasters";
 
   int id=-1;
	int step=0;
	trace->event(s_fn,0,"enter");
	
	for (int i=0; i<MAX_MONSTERS; i++)
	{			
		if ((monsters[i]!=NULL) && (monsters[i]->getState()==stateEnemyMoving))
		{
			float distance= 
				sqrt( ( (monsters[i]->getX()-(x*32)) * 
							(monsters[i]->getX()-(x*32)) ) + 
					   ( (monsters[i]->getY()-(y*32)) * 
						  (monsters[i]->getY()-(y*32)) ) );
			
			if (distance<=range)
			{			  		
				if (step < monsters[i]->getStep())
				{
					id=i;
					step=monsters[i]->getStep();
					trace->event(s_fn,0,"Monster [%d] step=%d in range", id, step);
				}
			}
		}
	}
	
	trace->event(s_fn,0,"leave [id=%d]", id);
	return id;
}

/**
 * find enemy in range depending on weapon type 
 *
 * @return id [-1 if no enemy is found].
 */
int Weapon::findMonster(void)
{
   int id=-1;
	
	const char *s_fn="Weapon::findMonster";
	trace->event(s_fn,0,"enter");
	
	switch (fireMode)
	{
		case FIRE_MODE_NEAREST_TO_BASE:
					id=findNearestToBase();
					break;
	
		case FIRE_MODE_HIGHEST_ENERGY:
					id=findHighestEnergy();
					break;
	
		case FIRE_MODE_FASTEST:
					id=findFastest();
					break;
	}
	
	trace->event(s_fn,0,"leave [id=%d]", id);
	return id;
}

/**
 * Play fire sound 
 */
void Weapon::playFireSound(void)
{
	const char *s_fn="Weapon::playFireSound";
	trace->event(s_fn,0,"enter");
	
	switch(type)
	{
		case 0: 	// Gun
					sound->effect(SOUND_GUN);	
					break;
			
		case 1: 	// Rifle
					sound->effect(SOUND_RIFLE);	
					break;
								
		case 2: 	// Cannon
					sound->effect(SOUND_CANON);	
					break;
					
		case 3: 	// Missile
					sound->effect(SOUND_MISSLE);	
					break;
								
		case 4: 	// Laser
					sound->effect(SOUND_LASER);	
					break;
								
		default: // Nuck
					sound->effect(SOUND_LASER);	
					break;
	}
	trace->event(s_fn,0,"leave");
}

/**
 * Calculate angle between weapon and enemies 
 * and selected correct weapon sprite frame.
 *
 * @param id	The id of the enemy 
 *
 * @return angle between weapon and enemy.
 */
int Weapon::calculateAngle(int id)
{
	const char *s_fn="Weapon::calculateAngle";

	trace->event(s_fn,0,"enter [%d]", id);
	if (monsters[id]!=NULL)
	{
		int x1= (x*32)+16;
		int y1= (y*32)+16;
		trace->event(s_fn,0,"Weapon x=%d y=%d", x1, y1);
		int x2= monsters[id]->getX()+16;
		int y2= monsters[id]->getY()+16;
		trace->event(s_fn,0,"Enemy x=%d y=%d", x2, y2);
		
		double angle1 = atan2((y2 - y1),(x2 - x1));
		int angle2 = round(( angle1 * 180.0 ) / M_PI);
		if (angle2<0) angle2=360+angle2;
		angle2=360-angle2;
		trace->event(s_fn,0,"Angle=%d", angle2);
	
		if  ( ((angle2>350) && (angle2<=360)) ||
			   ((angle2>0) && (angle2<=12)) ) 
		{
			angle=4; 
		} 
		else if ((angle2>12) && (angle2<=34))
		{
			angle=5; 
		}
		else if ((angle2>34) && (angle2<=56))
		{
			angle=6;
		}
		else if ((angle2>56) && (angle2<=78))
		{
			angle=7;
		}
		else if ((angle2>78) && (angle2<=100))
		{
			angle=8;
		}
		else if ((angle2>100) && (angle2<=122))
		{
			angle=9;
		}
		else if ((angle2>122) && (angle2<=144))
		{
			angle=10;
		}
		else if ((angle2>144) && (angle2<=166))
		{
			angle=11;
		}
		else if ((angle2>166) && (angle2<=188))
		{
			angle=12;
		}
		else if ((angle2>188) && (angle2<=210))
		{
			angle=13;
		}
		else if ((angle2>210) && (angle2<=232))
		{
			angle=14;
		}
		else if ((angle2>232) && (angle2<=254))
		{
			angle=15;
		}
		else if ((angle2>254) && (angle2<=276))
		{
			angle=0;
		}
		else if ((angle2>276) && (angle2<=298))
		{
			angle=1;
		}
		else if ((angle2>298) && (angle2<=320))
		{
			angle=2;
		}
		else if ((angle2>320) && (angle2<=350))
		{
			angle=3;
		}
	}
	trace->event(s_fn,0,"leave [angle=%d]", angle);
	return angle;
}

/**
 * Get weapon sprite frame 
 *
 * @return weapon sprite start frame
 */
int Weapon::getFrame()
{	
	if (image->h==32) 
	{
		// No animation sprite available, return direct;
		return 0;
	}
		
	// Frame sequence available
	if (frameDelay>3)
	{
		if (fireDelay>0)
		{
			// Fire sprite sequece 
			switch (game.frameCounter)
			{
				case 0:  // prepare fire sprite
							frame=angle+(16*1);
							game.frameCounter++;
							break;
					  
				case 1:  // fire 1 sprite
							frame=angle+(16*2);
							game.frameCounter++;
							break;
						
				case 2:  // fire 2 sprite
							frame=angle+(16*3);
							game.frameCounter++;
							break;
							
				case 3:  // idle sprite
							frame=angle;
							break;
			}
		}
		else
		{
			frame=angle;
		}
		frameDelay=0;
	}
	else
	{
		frameDelay++;
	}
	return frame;
}

// ------------------------------
// public methods
// ------------------------------

/**
 * draw weapon on screen
 */
void Weapon::draw()
{
	// Draw weapon range circle
	if (selected)
	{	
		GRRLIB_Circle((x*32)+16, (y*32)+16, range, IMAGE_COLOR3, 1);
	}
	
	// Draw fire trail 
	if (--fireDelay>0)
	{
		GRRLIB_Line( (x*32)+16, (y*32)+16, monsterX+16, monsterY+16, GRRLIB_LIGHTRED);								
	}
	
	// Draw Weapon on screen
	GRRLIB_DrawTile(  (x*32), (y*32), image, 0, 1, 1, IMAGE_COLOR, getFrame());
					
	// Draw reload time bar
	float proc = ((rate-delay) / rate) * 18.0;
	GRRLIB_Rectangle((x*32)+5, (y*32)+28, 20, 4, GRRLIB_BLACK, 0);
	GRRLIB_Rectangle((x*32)+6, (y*32)+29, proc, 2, GRRLIB_RED, 1);
}

/** 
 * Move (fire) weapon 
 */			
void Weapon::move(void)
{
   const char *s_fn="Weapon::move";
	
	if (delay>0) 
	{
		delay--;
	}
	else
	{
		// fire weapon, if enemy in range
		int id=findMonster();
		
		if (id!=-1)
		{					
			// Target enemy found
			calculateAngle(id);
			
			// Store enemy position for fired effect!
			monsterX=monsters[id]->getX();
			monsterY=monsters[id]->getY();
			fireDelay=15;		
			game.frameCounter=0;
			
			// Play fire sound
			playFireSound();
								
			int energy=monsters[id]->getEnergy();
			if (energy<=power)
			{
				// Receive score and cash for shooting the monster
				game.score+=energy;
				game.cash+=energy;
		
				// Monster is dead
				trace->event(s_fn,0,"Monster %d is dying!", monsters[id]->getIndex());				
				monsters[id]->setState(stateEnemyDying);
				sound->effect(SOUND_DEAD);	
			}
			else
			{
				monsters[id]->setEnergy(energy-power);
			
				// Receive score and cash for shooting the monster
				game.score+=power;
				game.cash+=power;
			}
					
			// Reset delay counter;
			delay=rate;
		}
	}
}

/** 
 * upgrade power of weapon
 */
void Weapon::upgradePower(void)
{
	const char *s_fn="Weapon::upgradePower";
	trace->event(s_fn,0,"enter");
	
	if ((game.cash>=powerPrice) && (power<maxPower))
	{
		power+=powerStep;
		trace->event(s_fn,0,"Weapon %d upgrade power to %d",index, power);
		game.cash-=powerPrice;
		totalPrice+=powerPrice;
		powerPrice=powerPrice*2;					
		sound->effect(SOUND_UPGRADE);
	}
	
	trace->event(s_fn,0,"leave");
}

/** 
 * upgrade range of weapon
 */
void Weapon::upgradeRange(void)
{
	const char *s_fn="Weapon::upgradeRange";
	trace->event(s_fn,0,"enter");
	
	if ((game.cash>=rangePrice) && (range<maxRange))
	{
		range+=rangeStep;
		trace->event(s_fn,0,"Weapon %d upgrade range to %d",index, range);
		game.cash-=rangePrice;
		totalPrice+=rangePrice;
		rangePrice=rangePrice*2;
		sound->effect(SOUND_UPGRADE);
	}
	
	trace->event(s_fn,0,"leave");
}

/** 
 * upgrade rate of weapon
 */
void Weapon::upgradeRate(void)
{
	const char *s_fn="Weapon::upgradeRate";
	trace->event(s_fn,0,"enter");
	
	if ((game.cash>=ratePrice) && (rate>maxRate))
	{
		rate-=(rateStep*AVERAGE_FPS);
		trace->event(s_fn,0,"Weapon %d upgrade rate to %d",index, rate);
		game.cash-=ratePrice;
		totalPrice+=ratePrice;
		ratePrice=ratePrice*2;

		// Update weapon reload delay sequence, if needed!
		if (delay>rate)
		{
			delay=rate;
		}
		
		sound->effect(SOUND_UPGRADE);
	}
		
	trace->event(s_fn,0,"leave");
}

/** 
 * check if weapon is selected by WiiMote pointer
 *
 * @param x1 	The x location of pointer.
 * @param y1	The y location of pointer.
 *
 * @return weapon selected!
 */
bool Weapon::onSelect(int x1, int y1)
{   
	const char *s_fn="Weapon::onSelect";
	if ( 	(x1>=(x*32)) && 
			(x1<=((x*32)+32)) && 
			(y1>=(y*32)) && 
			(y1<=((y*32)+32)) )
	{      	 	
		trace->event(s_fn,0,"Weapon %d selected", index);
		
		// Click
		sound->effect(SOUND_CLICK);	
		return true;
	}
	return false;
}

// ------------------------------
// Setters 
// ------------------------------

/**
 * Set weapon x grid position
 *
 * @param x1	The x grid position
 */
void Weapon::setX(int x1)
{
	const char *s_fn="Weapon::setX";
	trace->event(s_fn,0,"%d",x1);
   
	x = x1;
}

/**
 * Set weapon y grid position
 *
 * @param y1	The y grid position
 */
void Weapon::setY(int y1)
{
   const char *s_fn="Weapon::setY";
   trace->event(s_fn,0,"%d",y1);
  
   y = y1;
}
				
/**
 * Set weapon image
 *
 * @param image1	The image 
 */
void Weapon::setImage(GRRLIB_texImg *image1)
{   
   image = image1;
}

/**
 * Set weapon power
 *
 * @param power1	The power
 */
void Weapon::setPower(int power1)
{
   const char *s_fn="Weapon::setPower";
   trace->event(s_fn,0,"%d",power1);
   
   power=power1;
}

/**
 * Set weapon range
 *
 * @param range1	The range
 */
void Weapon::setRange(int range1)
{
   const char *s_fn="Weapon::setRange";
   trace->event(s_fn,0,"%d",range1);
   
   range=range1;
}

/**
 * Set weapon rate
 *
 * @param rate1	The rate
 */
void Weapon::setRate(int rate1)
{
   const char *s_fn="Weapon::setRate";
   trace->event(s_fn,0,"%d",rate1);
   
   rate=rate1*AVERAGE_FPS;
   delay=rate;
}

/**
 * Set weapon maximum power
 *
 * @param maxPower1	The maximum power
 */
void Weapon::setMaxPower(int maxPower1)
{
   const char *s_fn="Weapon::setmaxPower";
   trace->event(s_fn,0,"%d",maxPower1);
   
   maxPower=maxPower1;
}

/**
 * Set weapon maximum range
 *
 * @param maxRange1	The maximum range
 */
void Weapon::setMaxRange(int maxRange1)
{
   const char *s_fn="Weapon::setMaxRange";
   trace->event(s_fn,0,"%d",maxRange1); 
   
   maxRange=maxRange1;
}

/**
 * Set weapon maximum rate
 *
 * @param maxRate1	The maximum rate
 */
void Weapon::setMaxRate(int maxRate1)
{
   const char *s_fn="Weapon::setMaxRate";
   trace->event(s_fn,0,"%d",maxRate1);
   
   maxRate=maxRate1*AVERAGE_FPS;
}

/**
 * Set weapon power price
 *
 * @param price	The power price.
 */
void Weapon::setPowerPrice(int price)
{
   const char *s_fn="Weapon::setPowerPrice";
   trace->event(s_fn,0,"%d",price);
   
   powerPrice=price;
}

/**
 * Set weapon range price
 *
 * @param price	The range price.
 */
void Weapon::setRangePrice(int price)
{
	const char *s_fn="Weapon::setRangePrice";
	trace->event(s_fn,0,"%d",price);
   
	rangePrice=price;
}

/**
 * Set weapon rate price
 *
 * @param price	The rate price.
 */
void Weapon::setRatePrice(int price)
{
	const char *s_fn="Weapon::setRatePrice";
	trace->event(s_fn,0,"%d",price);
	
	ratePrice=price;
}

/**
 * Set weapon index
 *
 * @param index1	The unique index
 */
void Weapon::setIndex(int index1)
{
	const char *s_fn="Weapon::setIndex";
	trace->event(s_fn,0,"%d",index1);
	
	index=index1;
}

/**
 * Set weapon selected
 *
 * @param selected1	True weapon seleced (show range), false not selected
 */
void Weapon::setSelected(bool selected1)
{
	selected=selected1;
}

/**
 * Set weapon type
 *
 * @param type1	The weapon type.
 */
void Weapon::setType(int type1)
{
	type=type1;
}

/**
 * Set weapon power step size
 *
 * @param step1	The weapon power step size.
 */
void Weapon::setPowerStep(int step1)
{
	powerStep=step1;
}

/**
 * Set weapon range step size
 *
 * @param step1	The weapon range step size.
 */
void Weapon::setRangeStep(int step1)
{
	rangeStep=step1;
}

/**
 * Set weapon rate step size
 *
 * @param step1	The weapon rate step size.
 */
void Weapon::setRateStep(int step1)
{
	rateStep=step1;
}

/**
 * Set weapon name
 *
 * @param name1	The weapon name
 * @param ...		Optional parameters
 */
void Weapon::setName(const char *name1, ...)
{
	char buf[MAX_LEN];
	memset(buf,0x00,sizeof(buf));
	
	// Expend event string
	va_list list;
	va_start(list, name1 );
	vsprintf(buf, name1, list);
		
	strcpy(name,buf);
}

/**
 * Set weapon total price. This information is needed for the sale action.
 *
 * @param totalPrice1	The weapon total price
 */
void Weapon::setTotalPrice(int totalPrice1)
{
	totalPrice=totalPrice1;
}

/**
 * Set weapon fire mode.
 *
 * @param mode		The weapon fire mode. 
 */
void Weapon::setFireMode(int mode)
{
	fireMode=mode;
}

// ------------------------------
// Getters 
// ------------------------------

/** 
 * Get X grid position
 *
 * @return x grid position.
 */
int Weapon::getX(void)
{
	return x;
}

/** 
 * Get Y grid position
 *
 * @return y grid position.
 */
int Weapon::getY(void)
{
	return y;
}

/** 
 * Get current upgrade power price
 *
 * @return current power price.
 */
int Weapon::getPowerPrice(void)
{
	return powerPrice;
}

/** 
 * Get current upgrade range price
 *
 * @return current range price.
 */
int Weapon::getRangePrice(void)
{
	return rangePrice;
}

/** 
 * Get current upgrade rate price
 *
 * @return current rate price.
 */
int Weapon::getRatePrice(void)
{
	return ratePrice;
}

/** 
 * Get weapon name
 *
 * @return weapon name.
 */
const char *Weapon::getName(void)
{
	return name;
}

/**
 * Is power ungradeble?
 *
 * @return true or false
 */
bool Weapon::isPowerUpgradeble(void)
{
	return power<maxPower;
}

/**
 * Is range ungradeble?
 *
 * @return true or false
 */
bool Weapon::isRangeUpgradeble(void)
{
	return range<maxRange;
}

/**
 * Is rate ungradeble?
 *
 * @return true or false
 */
bool Weapon::isRateUpgradeble(void)
{
	return rate>maxRate;
}

/**
 * Get current power
 *
 * @return power level
 */
int Weapon::getPower(void)
{
	return power;
}

/**
 * Get current range
 *
 * @return range level
 */
int Weapon::getRange(void)
{
	return range;
}

/**
 * Get current rate
 *
 * @return rate level
 */
int Weapon::getRate(void)
{
	return (rate/AVERAGE_FPS);
}

/**
 * Get maximum power
 *
 * @return maximum power level
 */
int Weapon::getMaxPower(void)
{
	return maxPower;
}

/**
 * Get maximum range
 *
 * @return maximum range level
 */
int Weapon::getMaxRange(void)
{
	return maxRange;
}

/**
 * Get maximum rate
 *
 * @return maximum rate level
 */
int Weapon::getMaxRate(void)
{
	return (maxRate/AVERAGE_FPS);
}

/**
 * Get total price
 *
 * @return total price
 */
int Weapon::getTotalPrice(void)
{
	return totalPrice;
}

/**
 * Get fire mode
 *
 * @return fire mode 
 */
int Weapon::getFireMode(void)
{
	return fireMode;
}
	
// ------------------------------
// The end
// ------------------------------