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

#ifndef WEAPONSPECS_H
#define WEAPONSPECS_H

#include "GRRLIB.h" 

class WeaponSpecs
{
  private:

	GRRLIB_texImg *weapon1;
	GRRLIB_texImg *weapon2;
	GRRLIB_texImg *weapon3;
	GRRLIB_texImg *weapon4;
	GRRLIB_texImg *weapon5;
	GRRLIB_texImg *weapon6;

	GRRLIB_texImg *weapon1a;
	GRRLIB_texImg *weapon2a;
	GRRLIB_texImg *weapon3a;
	GRRLIB_texImg *weapon4a;
	GRRLIB_texImg *weapon5a;
	GRRLIB_texImg *weapon6a;
	
	// Weapon build counter;
	int gunCounter;
	int rifleCounter;
	int canonCounter;
	int missleCounter;
	int laserCounter;
	int nukeCounter;
	
  public:
  	// Constructor & Destructor
	WeaponSpecs();
 	~WeaponSpecs();
	
	// Other
	void resetCounter(void);
		
	// Getters
	
	// Return Weapon Image (16x4 animation of 32x32 pixels)
	GRRLIB_texImg * getImage(int type);
	
	// Return Weapon Image (32x32 pixels) per Type		
	GRRLIB_texImg * getImageSpecial(int type);

	const char *getName(int type);
	int getPrice(int type);
	int getUpgradePrice(int type);
	
	int getMinPower(int type);
	int getMinRange(int type);
	int getMinRate(int type);
	
	int getMaxPower(int type);
	int getMaxRange(int type);
	int getMaxRate(int type);
	
	int getStepPower(int type);
	int getStepRange(int type);
	int getStepRate(int type);
	
	int getCounter(int type);
};

#endif



