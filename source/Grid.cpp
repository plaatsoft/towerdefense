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
**  Foundation, Inc., 5 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <stdlib.h>
#include <mxml.h>

#include "General.h"
#include "GRRLIB.h"
#include "Trace.h"
#include "Grid.h"

int maxLines;
int maxLocations;
int baseX=0;
int baseY=0;

typedef struct
{
	int filename;
	bool road;
	int angle;
	GRRLIB_texImg *image;
}
GridMeta;

GridMeta gridMeta;

char gridData[MAX_GRID_Y][MAX_GRID_X];

typedef struct 
{
	int x;
	int y;
}
location;

location locationList[MAX_GRID_Y*MAX_GRID_X];

extern Trace *trace;
extern Game  game; 

// ------------------------------
// Constructor
// ------------------------------

Grid::Grid()
{
	const char *s_fn="Grid::Grid";
	trace->event(s_fn,0,"enter");
  
	trace->event(s_fn,0,"leave [void]");  
}
	
// ------------------------------
// Destructor
// ------------------------------

Grid::~Grid()
{
	const char *s_fn="Grid::~Grid";
	trace->event(s_fn,0,"enter");

	trace->event(s_fn,0,"leave [void]");  
}

// ------------------------------
// Others
// ------------------------------

void Grid::parseGrid(void)
{
	const char *s_fn="Grid::parseGrid";
	trace->event(s_fn,0,"enter");
   
	int x,y;
	char temp[MAX_GRID_Y][MAX_GRID_X];
	boolean ready=false;
	maxLocations=0;
   
	// Make copy of grid data and store start position
	for (y=0;y<MAX_GRID_Y;y++)
	{
		for (x=0;x<MAX_GRID_X;x++)
		{
			if (gridData[y][x]=='~') 
			{
				// Replace water element with glass element
				// else monsters walk over water.
				temp[y][x]='0';
			}
			else 
			{
				// Store other grid data elements
				temp[y][x]=gridData[y][x];
			
				// Store start position	of grid
				if (temp[y][x]=='*')
				{
					locationList[maxLocations].x=x;
					locationList[maxLocations].y=y;
					maxLocations++;
					temp[y][x]='0';
				}
			}
		}
	}
   
	// Create walking plan for monsters
	while (!ready)
	{
		ready=true;
		x=locationList[maxLocations-1].x;
		y=locationList[maxLocations-1].y;
		
		if (temp[y][x+1]!='0')
		{
			locationList[maxLocations].x=(x+1);
			locationList[maxLocations].y=y;
			maxLocations++;
			if (temp[y][x+1]!='#') ready=false; else ready=true;
			if (temp[y][x+1]!='7') temp[y][x+1]='0';
		}
		else if (temp[y][x-1]!='0')
		{
			locationList[maxLocations].x=(x-1);
			locationList[maxLocations].y=y;
			maxLocations++;
			if (temp[y][x-1]!='#') ready=false; else ready=true;
			if (temp[y][x-1]!='7') temp[y][x-1]='0';
		}
		else if (temp[y+1][x]!='0')
		{
			locationList[maxLocations].x=x;
			locationList[maxLocations].y=(y+1);
			maxLocations++;
			if (temp[y+1][x]!='#') ready=false; else ready=true;
			if (temp[y+1][x]!='7') temp[y+1][x]='0';
		}
		else if (temp[y-1][x]!='0')
		{
			locationList[maxLocations].x=x;
			locationList[maxLocations].y=(y-1);
			maxLocations++;
			if (temp[y-1][x]!='#') ready=false; else ready=true;
			if (temp[y-1][x]!='7') temp[y-1][x]='0';
		}
	}
	
	trace->event(s_fn,0,"leave [maxLocations=%d]",maxLocations);
}

void Grid::loadGrid(const char* filename)
{
   const char *s_fn="Grid::initGrid";
   trace->event(s_fn,0,"enter [filename=%s]",filename);
   
   FILE *fp;
   mxml_node_t *tree =NULL;
   mxml_node_t *group;   
   const char  *pointer;

   maxLines=0;
   
   /* Load our xml file! */
   fp = fopen(filename, "r");
   if (fp!=NULL)
   {   
      tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
      fclose(fp);
   }
    
   // Read Grid Lines
   for (group = mxmlFindElement(tree, tree, "line", NULL, NULL, MXML_DESCEND);
        group != NULL;
        group = mxmlFindElement(group, tree, "line", NULL, NULL, MXML_DESCEND))
   {		 	  	  
      pointer=mxmlElementGetAttr(group,"data");
      if (pointer!=NULL) strcpy(gridData[maxLines],pointer);  
	  
	  maxLines++;
   }
   
   mxmlDelete(group);
   mxmlDelete(tree);
   trace->event(s_fn,0,"leave [maxLines=%d]",maxLines);
}

void Grid::draw(void)
{
   int x;
   int y;
   
   // Parse
   for (y=0; y<MAX_GRID_Y; y++)
   {	
		for (x=0; x<MAX_GRID_X; x++)
		{
			switch (gridData[y][x])
			{				
				case '*': 
				case '0': 
					// Draw Grass image
					GRRLIB_DrawImg( x*32, y*32, image5, 0, 1.0, 1.0, IMAGE_COLOR );
					break;
	
				case 205:
				case '1':
					// Draw basic road
					GRRLIB_DrawImg( (x*32)+32, y*32, image4, 90, 1.0, 1.0, IMAGE_COLOR );
					break;	

				case 186:
				case '2':
					// Draw basic road
					GRRLIB_DrawImg( (x*32), (y*32), image4, 0, 1.0, 1.0, IMAGE_COLOR );
					break;	
					
				case 188:	
				case '3':
					// Draw angle road
					GRRLIB_DrawImg( (x*32), (y*32), image3, 0, 1.0, 1.0, IMAGE_COLOR );
					break;	

				case 200:
				case '4':
					// Draw angle road
					GRRLIB_DrawImg( (x*32)+32, y*32, image3, 90, 1.0, 1.0, IMAGE_COLOR );
					break;	
					
				case 201:
				case '5':
					// Draw angle road
					GRRLIB_DrawImg( (x*32)+32, (y*32)+32, image3, 180, 1.0, 1.0, IMAGE_COLOR );
					break;	
				
				case 187:
				case '6':
					// Draw angle road
					GRRLIB_DrawImg( (x*32), (y*32)+32, image3, 270, 1.0, 1.0, IMAGE_COLOR );
					break;	
			
				case 206:
				case '7':
					// Draw Cross road
					GRRLIB_DrawImg( (x*32), (y*32), image2, 0, 1.0, 1.0, IMAGE_COLOR );
					break;	
			
				case 204:
				case '8':
					// Draw T-section road
					GRRLIB_DrawImg( (x*32), (y*32), image1, 0, 1.0, 1.0, IMAGE_COLOR );
					break;	

				case 203:
				case '9':
					// Draw T-section road
					GRRLIB_DrawImg( (x*32), (y*32), image1, 90, 1.0, 1.0, IMAGE_COLOR );
					break;

				case 185:
				case 'A':
					// Draw T-section road
					GRRLIB_DrawImg( (x*32), (y*32), image1, 180, 1.0, 1.0, IMAGE_COLOR );
					break;

				case 202:
				case 'B':
					// Draw T-section road
					GRRLIB_DrawImg( (x*32), (y*32), image1, 270, 1.0, 1.0, IMAGE_COLOR );
					break;
		
				case '~':
					// Draw water image 
					GRRLIB_DrawImg( (x*32), (y*32), imageWater, 0, 1.0, 1.0, IMAGE_COLOR );
					break;

				case '=':
					// Draw bridge image
					GRRLIB_DrawImg( (x*32), (y*32), imageBridge, 0, 1.0, 1.0, IMAGE_COLOR );
					break;

				case 'H':
					// Draw bridge image
					GRRLIB_DrawImg( (x*32)+32, (y*32), imageBridge, 90, 1.0, 1.0, IMAGE_COLOR );
					break;
					
				case '#':
					// Draw grass image
					GRRLIB_DrawImg( (x*32), (y*32), image5, 0, 1.0, 1.0, IMAGE_COLOR );
					
					// Store Base Position for later use!
					baseX=x;
					baseY=y;
					break;
			}
		}
		
	}
	
	// Workarround to set base image on correct place
	if (index==2) baseX+=1;


	// Draw remaining base energy bar
	int proc = (game.monsterInBase / MAX_MONSTER_IN_BASE ) * 60;
	GRRLIB_Rectangle((baseX*32)-16, (baseY*32)+71, 60, 4, GRRLIB_BLACK, 1);
	if (proc>60)
	{
		GRRLIB_Rectangle((baseX*32)-15, (baseY*32)+72, proc, 2, GRRLIB_GREEN, 1);
	}
	else if (proc>30)
	{
		GRRLIB_Rectangle((baseX*32)-15, (baseY*32)+72, proc, 2, GRRLIB_YELLOW, 1);
	}
	else 
	{	
		GRRLIB_Rectangle((baseX*32)-15, (baseY*32)+72, proc, 2, GRRLIB_RED, 1);
	}
		
	// Draw base
	GRRLIB_DrawImg( (baseX*32)-16, (baseY*32)+5, imageBase, 0, 1.0, 1.0, IMAGE_COLOR );
}

void Grid::text(void)
{
    char tmp[50];

	// Workarround to set base image on correct place
	if (index==2) baseX+=1;
	
    sprintf(tmp, "%d", game.monsterInBase);
	GRRLIB_Printf2((baseX*32)-16, (baseY*32)+16, tmp, 12, GRRLIB_WHITESMOKE); 
}
	
	
// Load grid map and parse it for monster movement.
void Grid::create(const char* filename)
{
	const char *s_fn="Grid::render";
	trace->event(s_fn,0,"enter [filename=%s]",filename);
   
    loadGrid(filename);
	parseGrid();
	
	trace->event(s_fn,0,"leave [void]");  
}
			
// ------------------------------
// Setters
// ------------------------------

void Grid::setImageRoad1(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImageRoad1";
   trace->event(s_fn,0,"data");
   
   image1 = image;
}

void Grid::setImageRoad2(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImageRoad2";
   trace->event(s_fn,0,"data");
   
   image2 = image;
}

void Grid::setImageRoad3(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImageRoad3";
   trace->event(s_fn,0,"data");
   
   image3 = image;
}

void Grid::setImageRoad4(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImageRoad4";
   trace->event(s_fn,0,"data");
   
   image4 = image;
}

void Grid::setImageRoad5(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImageRoad5";
   trace->event(s_fn,0,"data");
   
   image5 = image;
}

void Grid::setImageBase(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImageBase";
   trace->event(s_fn,0,"data");
   
   imageBase = image;
}

void Grid::setImageWater(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImageWater";
   trace->event(s_fn,0,"data");
   
   imageWater = image;
}

void Grid::setImageBridge(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImageBrige";
   trace->event(s_fn,0,"data");
   
   imageBridge = image;
}

void Grid::setIndex(int index1)
{
	const char *s_fn="Grid::setIndex";
	trace->event(s_fn,0,"%d",index1);
	
    index = index1;
}

// ------------------------------
// Getters
// ------------------------------

int Grid::getLocationX(int pos)
{
    if (pos<maxLocations)
	{
		return (locationList[pos].x*32);
	}
	return -1;
}

int Grid::getLocationY(int pos)
{
    if (pos<maxLocations)
	{
		return (locationList[pos].y*32);
	}
	return -1;
}


int Grid::getMaxLocations(void)
{
   return maxLocations;
}

// ------------------------------
// The End
// ------------------------------