/** 
 *  @file 
 *  @brief The file contain the Button class
 *  @author wplaat
 *
 *  Copyright (C) 2008-2010 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "grrlib.h"

/**
 * Button class
 * @param x The x-coordinate of the button.
 * @param y The y-coordinate of the button.
 * @param imageNormal image for not no focus situation.
 * @param imageFocus image for focus situation.
 * @param y The y-coordinate of the button.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param label The label name of the button.
 * @param focus The indication that the button is in focus of WiiMote pointer.
 * @param rumble The rumble array contain a countdown timer for each WiiMote.
 * @param index The index contain a unique number for debugging.
 */
class Button
{
  private:
	int x;							
	int y;	
	GRRLIB_texImg *imageNormal;
	GRRLIB_texImg *imageFocus;
	int height;
	int width;
	char label[100];
	bool focus;
	u32 color;
	bool rumble[MAX_POINTERS];
	int index;
	
  public:
	// Constructor & Destructor
  	Button();
 	~Button();

	// Other
	void draw();
	void text(int offset);
	bool onSelect(int pointerX, int pointerY, bool sound);
	
	// Setters
	void setX(int x);
	void setY(int y);
	void setLabel(const char *label);
	void setImageNormal(GRRLIB_texImg *imageNormal);
	void setImageFocus(GRRLIB_texImg *imageFocus);
	void setColor(u32 color);
	void setIndex(int index);
	
	// Getters
	int getX(void);
	int getY(void);
};

#endif