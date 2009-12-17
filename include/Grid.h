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
	GRRLIB_texImg *image1;
	GRRLIB_texImg *image2;
	GRRLIB_texImg *image3;
	GRRLIB_texImg *image4;
	GRRLIB_texImg *image5;
	GRRLIB_texImg *imageBase;
	GRRLIB_texImg *imageWater;
	GRRLIB_texImg *imageBridge;

	
	void parseGrid(void);
	void loadGrid(const char* filename);
	
  public:
	// Constructor & Destructor
  	Grid();
 	~Grid();

	// Other
	void draw(int xOffset, int yOffset, int size);
	void text(void);
	void create(const char* filename);

	// Setters
	void setImageRoad1(GRRLIB_texImg *image);
	void setImageRoad2(GRRLIB_texImg *image);
	void setImageRoad3(GRRLIB_texImg *image);
	void setImageRoad4(GRRLIB_texImg *image);
	void setImageRoad5(GRRLIB_texImg *image);
	void setImageBase(GRRLIB_texImg *image);	
	void setImageWater(GRRLIB_texImg *image);
	void setImageBridge(GRRLIB_texImg *image);
	void setIndex(int index);
	
	// Getters
	int getLocationX(int pos);
	int getLocationY(int pos);
	int getMaxLocations(void);
};

#endif
