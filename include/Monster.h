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
	float size;
	GRRLIB_texImg *image;
	int height;
	int width;
	bool xDirection;
	bool yDirection;
	int step;
	int delay;
	int pos;
	boolean visible;
	
  public:
  	Monster();
 	~Monster();

	void setImage(GRRLIB_texImg *image);	
	void setStep(int step);
	void setDelay(int delay);
	
	int getX(void);
	int getY(void);
	int getAlfa(void);
	float getSize(void);
	int getStep(void);
	
	void properties(void);
	void draw(void);
	void move(void);
};

#endif
