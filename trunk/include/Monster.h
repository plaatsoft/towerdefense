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

#ifndef MONSTER_H
#define MONSTER_H

#include "GRRLIB.h"

class Monster
{
  private:

	int x;
	int targetX;
	int y;	
	int targetY;
	int alfa;
	int energy;
	float size;
	GRRLIB_texImg *image;
	int height;
	int width;
	int step;
	int delay;
	int pos;
	int index;
	boolean visible;
	
  public:
	// Constructor & Destructor
  	Monster();
 	~Monster();

	// Methodes
	void draw(void);
	void text(void);
	bool move(void);
	bool hit(int hit);
	
	// Setters
	void setImage(GRRLIB_texImg *image);	
	void setStep(int step);
	void setDelay(int delay);
	void setEnergy(int energy);
	void setIndex(int index);
		
	// Getters
	int getX(void);
	int getY(void);
	int getAlfa(void);
	float getSize(void);
	int getStep(void);
};

#endif
