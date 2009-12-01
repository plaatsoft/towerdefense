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

#include "GRRLIB.h"

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
	int step;
	
  public:
  	Weapon();
 	~Weapon();

	void draw(void);	
	void properties(void);
	void move(void);
	
	void setX(int x);
	void setY(int y);
	void setAlfa(int alfa);
	void setAngle(int angle);
	void setImage(GRRLIB_texImg *image);
	void setStep(int step);
};

#endif

