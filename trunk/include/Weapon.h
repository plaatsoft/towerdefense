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

#ifndef WEAPON_H
#define WEAPON_H

#include "General.h"
#include "GRRLIB.h"
#include "Monster.h"
#include "Trace.h"  
#include "Pointer.h" 

enum
{
   FIRE_MODE_NEAREST_TO_BASE=0,
   FIRE_MODE_HIGHEST_ENERGY=1, 
	FIRE_MODE_FASTEST=2
};

class Weapon
{
  private:
	int   x;
	int   y;	
	float size;
	int   angle;
	int   targetAngle;
	
	GRRLIB_texImg *image;
	float delay;
	int   index;
	int   type;
	char  name[MAX_LEN];
   int   totalPrice;
	
	int fireDelay;
	int fireMode;
	
	int monsterX;
	int monsterY;
	
	bool selected;
	
	float rate;
	int range;
	int power;

   int maxPower;
   int maxRange;   
   int maxRate;
	
	int powerPrice;
	int rangePrice;
	int ratePrice;
	
	int powerStep;
	int rangeStep;
	int rateStep;

	int frame;
	int frameDelay;
	
	// private methodes
	int findNearestToBase(void);
	int findNearestToWeapon(void);
	int findHighestEnergy(void);
	int findFasters(void);
	int findMonster(void);
	
	void playFireSound(void);
	int  getFrame(void);
	int  calculateAngle(int id);
	
  public:
  	// Constructor & Destructor
	Weapon();
 	~Weapon();

	// public methodes
	void draw(void);
	void fire(void);
	void move(void);
	bool onSelect(int x, int y);
	
	int  upgradePower(void);
	int  upgradeRange(void);
	int  upgradeRate(void);
	
	// Setters
	void setX(int x);
	void setY(int y);
	void setImage(GRRLIB_texImg *image);
	void setSelected(bool selected);
	void setIndex(int index);
	void setType(int type);
	void setName(const char *name, ...);
	void setFireMode(int mode);
	
	void setPower(int power);	
	void setRange(int range);
	void setRate(int rate);
	
	void setMaxPower(int maxPower);	
	void setMaxRange(int maxRange);
	void setMaxRate(int maxRate);
	
	void setPowerPrice(int price);
   void setRangePrice(int price);
   void setRatePrice(int price);
	
	void setPowerStep(int step);
   void setRangeStep(int step);
   void setRateStep(int step);
	
	void setTotalPrice(int totalPrice);

	// Getters
	
	int getX(void);
	int getY(void);
	
	const char *getName(void);
	int getTotalPrice(void);
	int getFireMode(void);
	
	int getPowerPrice(void);
	int getRangePrice(void);
	int getRatePrice(void);
	
	int getPower(void);	
	int getRange(void);
	int getRate(void);
	
	int getMaxPower(void);	
	int getMaxRange(void);
	int getMaxRate(void);
	
	bool isPowerUpgradeble(void);
	bool isRangeUpgradeble(void);
	bool isRateUpgradeble(void);
};

#endif

