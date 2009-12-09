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

#ifndef WEAPON_H
#define WEAPON_H

#include "General.h"
#include "GRRLIB.h"
#include "Monster.h"
#include "Trace.h"  
#include "Pointer.h" 


class Weapon
{
  private:
	int x;
	int y;	
	int alfa;
	float size;
	int angle;
	int targetAngle;
	GRRLIB_texImg *image;
	int height;
	int width;
	int delay;
	
	boolean selected;
	
	int rate;
	int range;
	int power;
	
	int powerPrice;
	int rangePrice;
	int ratePrice;
	
	
  public:
  	Weapon();
 	~Weapon();

	// Methodes
	void draw();
	void fire(Monster *monsters[MAX_MONSTERS]);
	void move(void);
	int  upgrade(int type);
	bool onSelect(int x1, int y1);
	
	// Setters
	void setX(int x);
	void setY(int y);
	void setImage(GRRLIB_texImg *image);

	void setPower(int power);	
	void setRange(int range);
	void setRate(int rate);
	
	void setPowerPrice(int price);
    void setRangePrice(int price);
    void setRatePrice(int price);
	
	// Getters
	int getPowerPrice(void);
	int getRangePrice(void);
	int getRatePrice(void);
};

#endif

