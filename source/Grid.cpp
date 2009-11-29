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

#include <stdio.h>
#include <stdlib.h>
#include <mxml.h>

#include "General.h"
#include "GRRLIB.h"
#include "Trace.h"
#include "Grid.h"

int maxLines;
int maxLocations;

char gridData[16][20];

typedef struct 
{
	int x;
	int y;
}
location;

location locationList[320];

extern Trace trace;

// ------------------------------
// Constructor
// ------------------------------

Grid::Grid()
{
	const char *s_fn="Grid::Grid";
	trace.event(s_fn,0,"enter");
  
	trace.event(s_fn,0,"leave [void]");  
}
	
// ------------------------------
// Destructor
// ------------------------------

Grid::~Grid()
{
	const char *s_fn="Grid::~Grid";
	trace.event(s_fn,0,"enter");

	trace.event(s_fn,0,"leave [void]");  
}

// ------------------------------
// Others
// ------------------------------

void parseGrid(void)
{
	const char *s_fn="Grid::parseGrid";
	trace.event(s_fn,0,"enter");
   
	int x,y;
	char temp[16][20];
	boolean ready=false;
	maxLocations=0;
   
	// Make copy of grid data
	for (y=0;y<16;y++)
	{
		for (x=0;x<20;x++)
		{
			temp[y][x]=gridData[y][x];
		}
	}
   
	// Find start position
	for (y=0;y<16;y++)
	{
		for (x=0;x<20;x++)
		{
			if (temp[y][x]=='*')
			{
				locationList[maxLocations].x=x;
				locationList[maxLocations].y=y;
				maxLocations++;
				temp[y][x]='0';
				break;
			}
		}
	}
	
	// Find all other positions
	while (!ready)
	{
		ready=true;
		x=locationList[maxLocations-1].x;
		y=locationList[maxLocations-1].y;
		
		if (temp[y-1][x]!='0')
		{
			locationList[maxLocations].x=x;
			locationList[maxLocations].y=y;
			maxLocations++;
			temp[y][x]='0';
			ready=false;
		}
		else if (temp[y+1][x]!='0')
		{
			locationList[maxLocations].x=x;
			locationList[maxLocations].y=y;
			maxLocations++;
			temp[y][x]='0';
			ready=false;
		}
		else if (temp[y][x+1]!='0')
		{
			locationList[maxLocations].x=x;
			locationList[maxLocations].y=y;
			maxLocations++;
			temp[y][x]='0';
			ready=false;
		}
		else if (temp[y][x-1]!='0')
		{
			locationList[maxLocations].x=x;
			locationList[maxLocations].y=y;
			maxLocations++;
			temp[y][x]='0';
			ready=false;
		}
	}
	
	trace.event(s_fn,0,"leave [maxLocations=%d]",maxLocations);
}

void initGrid(const char* filename)
{
   const char *s_fn="Grid::initGrid";
   trace.event(s_fn,0,"enter");
   
   FILE *fp;
   mxml_node_t *tree =NULL;
   mxml_node_t *group;   
   const char  *pointer;

   maxLines=0;
   
   /*Load our xml file! */
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
   trace.event(s_fn,0,"leave [void]");
}

void Grid::draw(void)
{
   int x;
   int y;
   
   for (y=0; y<16; y++)
   {	
		for (x=0; x<20; x++)
		{
			switch (gridData[y][x])
			{
				case '0': 
					GRRLIB_DrawImg( x*32, y*32, image5, 0, 1.0, 1.0, IMAGE_COLOR );
					break;
	
				case '1':
					GRRLIB_DrawImg( x*32, y*32, image1, 0, 1.0, 1.0, IMAGE_COLOR );
					break;				
					
				case '2':
					GRRLIB_DrawImg( x*32, y*32, image2, 0, 1.0, 1.0, IMAGE_COLOR );
					break;	
					
				case '3':
					GRRLIB_DrawImg( x*32, y*32, image3, 0, 1.0, 1.0, IMAGE_COLOR );
					break;	
					
				case '4':
					GRRLIB_DrawImg( x*32, y*32, image4, 0, 1.0, 1.0, IMAGE_COLOR );
					break;	
			}
		}
	}
}

void Grid::render(void)
{
	const char *s_fn="Grid::render";
	trace.event(s_fn,0,"enter");
   
    initGrid(GRID1_FILENAME);
	parseGrid();
	
	trace.event(s_fn,0,"leave [void]");  
}
			
// ------------------------------
// Getters and Setters
// ------------------------------


void Grid::setImage1(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImage1";
   trace.event(s_fn,0,"enter");
   
   image1 = image;
   
   trace.event(s_fn,0,"leave [void]");
}

void Grid::setImage2(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImage1";
   trace.event(s_fn,0,"enter");
   
   image2 = image;
   
   trace.event(s_fn,0,"leave [void]");
}

void Grid::setImage3(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImage1";
   trace.event(s_fn,0,"enter");
   
   image3 = image;
   
   trace.event(s_fn,0,"leave [void]");
}

void Grid::setImage4(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImage4";
   trace.event(s_fn,0,"enter");
   
   image4 = image;
   
   trace.event(s_fn,0,"leave [void]");
}

void Grid::setImage5(GRRLIB_texImg *image)
{
   const char *s_fn="Pointer::setImage5";
   trace.event(s_fn,0,"enter");
   
   image5 = image;
   
   trace.event(s_fn,0,"leave [void]");
}

void Grid::setLevel(int level1)
{
	const char *s_fn="Grid::setLevel";
	trace.event(s_fn,0,"enter [level=%d]",level1);
	
   if ((level>=0) && (level<=MAX_LEVEL))
   {
      level = level1;
   }
   
   trace.event(s_fn,0,"leave [void]");  
}

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