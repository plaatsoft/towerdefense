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

#ifndef BASE_H
#define BASE_H

#include "grrlib.h"

class Base
{
  private:
	int x;
	int y;	
	GRRLIB_texImg *image;
	int height;
	int width;
	
  public:
	// Constructor & Destructor
  	Base();
 	~Base();

	// Other
	void draw(void);
	
	// Setters
	void setX(int x);
	void setY(int y);
	void setImage(GRRLIB_texImg *image);
	
	// Getters
	int getX(void);
	int getY(void);
};

#endif
