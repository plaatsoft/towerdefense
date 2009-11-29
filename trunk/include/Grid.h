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

#ifndef GRID_H
#define GRID_H

#include "GRRLIB.h"

class Grid
{
  private:
    int level;
	GRRLIB_texImg *image1;
	GRRLIB_texImg *image2;
	GRRLIB_texImg *image3;
	GRRLIB_texImg *image4;
	GRRLIB_texImg *image5;
	
  public:
	// Constructor & Destructor
  	Grid();
 	~Grid();

	// Other
	void draw(void);
	void render(void);
	
	// Setters
	void setImage1(GRRLIB_texImg *image);
	void setImage2(GRRLIB_texImg *image);
	void setImage3(GRRLIB_texImg *image);
	void setImage4(GRRLIB_texImg *image);
	void setImage5(GRRLIB_texImg *image);
	void setLevel(int level);
	
	// Getters
	int getLocationX(int pos);
	int getLocationY(int pos);
	int getMaxLocations(void);
};

#endif
