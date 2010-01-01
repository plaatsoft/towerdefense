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

#ifndef POINTER_H
#define POINTER_H

#include <wiiuse/wpad.h>

#include "GRRLIB.h"

class Pointer
{
  private:
	int  x;
	int  y;	
	int  angle;
	int  index;	
	int  xOffset;
	int  yOffset;
	int  rumble;
	int  color;
	ir_t ir;
	GRRLIB_texImg *image;
	bool selected1;
	bool selected2;
	bool selectedA;	
	bool selectedB;	
  
	void saveSettingFile(const char* filename);	
	void buttonScroll(int x,int y );
	void buttonPlus(int index);
	void buttonMinus(int index);
	void buttonA(int x, int y);
	void buttonExit(int index);
	void button1x(void);
	void button2y(void);
	char getLetter(char letter, bool up);
	
  public:
  	// Constructor & Destructor
	Pointer();
 	~Pointer();

	// Other
	void draw(void);
	void action(void);

	// Setters
	void setIndex(int index);
	void setX(int x);
	void setY(int y);
	void setAngle(int angle);
	void setImage(GRRLIB_texImg *image);
	void setRumble(int rumble);
	void setColor(int color);
	
	// Getters
	int getX(void);
	int getY(void);
	int getXOffset(void);
	int getYOffset(void);
};

#endif
