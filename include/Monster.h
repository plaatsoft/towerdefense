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
 
	// Current x position
	int x;
	
	// Target x position
	int targetX;
	
	// Current x position
	int y;	
	
	// Target x position
	int targetY;
	
	// Alfa image color
	int alfa;
	
	// Monster energy label
	int energy;
	
	// Monster siz
	float size;
	
	// Monster Sprite
	GRRLIB_texImg *image;
	
	// Monster height (default 32)
	int height;
	
	// Monster width (default 32)
	int width;
	
	// Monster step (pixels per movement)
	int step;
	
	// Monster start delay (how much cycles to wait before entering the grid)
	int startDelay;
	
	// Monster grid position
	int pos;
	
	// Monster is visible on grid
	boolean visible;
	
  public:
	// Constructor & Destructor
  	Monster();
 	~Monster();

	// Methodes
	void draw(void);
	void text(void);
	void move(void);
	
	// Setters
	void setImage(GRRLIB_texImg *image);	
	void setStep(int step);
	void setStartDelay(int delay);
	void setEnergy(int energy);
	bool setHit(int hit);
	
	// Getters
	int getX(void);
	int getY(void);
	int getAlfa(void);
	float getSize(void);
	int getStep(void);
};

#endif
