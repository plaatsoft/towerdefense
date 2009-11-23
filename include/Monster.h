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

#ifndef ENEMY_H
#define ENEMY_H

#include "GRRLIB.h"

class Monster
{
  private:
	int x;
	int y;	
	int alfa;
	float size;
	int angle;
	int targetAngle;
	GRRLIB_texImg image;
	int height;
	int width;
	bool xDirection;
	bool yDirection;
	int step;
	
  public:
  	Monster();
	Monster(int x,int y, int height, int width, float size, int angle, int alfa, GRRLIB_texImg image );
 	~Monster();
	
	void setX(int x);
	void setY(int y);
	void setAlfa(int alfa);
	void setSize(float size);
	void setAngle(int angle);
	void setWidth(int width);
	void setHeight(int height);
	void setStep(int step);
	void setImage(GRRLIB_texImg image1);
	
	int getX(void);
	int getY(void);
	int getAlfa(void);
	float getSize(void);
	int getAngle(void);
	int getWidth(void);
	int getHeight(void);
	int getStep(void);
	
	void properties(void);
	void draw(void);
	void move(void);
};

#endif
