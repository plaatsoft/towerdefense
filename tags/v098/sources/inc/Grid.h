/** 
 *  @file 
 *  @brief The file contain the Grid class
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

#ifndef GRID_H
#define GRID_H

#include "grrlib.h"

typedef struct 
{
	int x;						/**< x 	The x position */
	int y;						/**< y 	The y position */
}
location;

/**
 * Grid class
 * @param locationList 		The monster walk pad arry .
 * @param gridData 			The raw grid data array.
 * @param gridBuild			The build data array.
 * @param maxLocations		The location steps in grid.
 * @param baseX				The baseX location in the grid.
 * @param baseY				The baseY location in the grid.
 * @param index				The index number of this grid.
 * @param imageRoad1			The image of road1 element.
 * @param imageRoad2			The image of road2 element.
 * @param imageRoad3			The image of road3 element.
 * @param imageRoad4			The image of road4 element.
 * @param imageRoad5			The image of road5 element.
 * @param imageBase			The image of Base element.
 * @param imageGeneral1		The image of roadGeneral1 (Bridge) element.
 * @param imageGeneral2		The image of roadGeneral2 (Water) element.
 */
 
class Grid
{
  private:
	location locationList[MAX_GRID_Y*MAX_GRID_X];
	char gridData[MAX_GRID_Y][MAX_GRID_X];	
	char gridBuild[MAX_GRID_Y][MAX_GRID_X];
	int maxLocations;
	int baseX;
	int baseY;
   int index;
	
	GRRLIB_texImg *imageRoad1;
	GRRLIB_texImg *imageRoad2;
	GRRLIB_texImg *imageRoad3;
	GRRLIB_texImg *imageRoad4;
	GRRLIB_texImg *imageRoad5;
	GRRLIB_texImg *imageBase;
	GRRLIB_texImg *imageGeneral1;
	GRRLIB_texImg *imageGeneral2;
	
	void parseGrid(void);
	bool loadGrid(const char* filename);
	GRRLIB_texImg * loadImage(const char *filename);
	
  public:
	// Constructor & Destructor
  	Grid();
 	~Grid();

	// Other
	void draw(int xOffset, int yOffset, float size);
	void create(const char* directory);
	void initBuild(void);
	
	// Setters
	void setBuild(int x, int y);
	void setUnBuild(int x, int y);
	void setIndex(int index);
	
	// Getters
	bool isBuild(int x, int y);
	int getLocationX(int pos);
	int getLocationY(int pos);
	int getMaxLocations(void);
};

#endif
