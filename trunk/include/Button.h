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

#ifndef BUTTON_H
#define BUTTON_H

#include "GRRLIB.h"

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
	
  public:
	// Constructor & Destructor
  	Button();
 	~Button();

	// Other
	void draw();
	void text();
	bool onSelect(int pointerX, int pointerY);
	
	// Setters
	void setX(int x);
	void setY(int y);
	void setLabel(const char *label);
	void setImageNormal(GRRLIB_texImg *imageNormal);
	void setImageFocus(GRRLIB_texImg *imageFocus);
};

#endif