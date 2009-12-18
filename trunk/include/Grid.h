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

typedef struct
{
	int filename;
	bool road;
	int angle;
	GRRLIB_texImg *image;
}
GridMeta;

typedef struct 
{
	int x;
	int y;
}
location;

class Grid
{
  private:
	GridMeta gridMeta;
	location locationList[MAX_GRID_Y*MAX_GRID_X];
	char gridData[MAX_GRID_Y][MAX_GRID_X];
	int maxLines;
	int maxLocations;
	int baseX;
	int baseY;

    int index;
	GRRLIB_texImg *imageRoad1;
	GRRLIB_texImg *imageRoad2;
	GRRLIB_texImg *imageRoad3;
	GRRLIB_texImg *imageRoad4;
	GRRLIB_texImg *imageRoad5;
	GRRLIB_texImg *imageBridge;
	GRRLIB_texImg *imageBase;
	GRRLIB_texImg *imageGeneral1;
	GRRLIB_texImg *imageGeneral2;

	
	void parseGrid(void);
	void loadGrid(const char* filename);
	GRRLIB_texImg * loadImage(const char *filename);
	
  public:
	// Constructor & Destructor
  	Grid();
 	~Grid();

	// Other
	void draw(int xOffset, int yOffset, int size);
	void text(void);
	void create(const char* directory);

	// Setters
	void setIndex(int index);
	
	// Getters
	int getLocationX(int pos);
	int getLocationY(int pos);
	int getMaxLocations(void);
};

#endif
