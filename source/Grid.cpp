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

extern Trace *trace;
extern Game  game; 

// ------------------------------
// Constructor
// ------------------------------

Grid::Grid()
{
	const char *s_fn="Grid::Grid";
	trace->event(s_fn,0,"enter");
  
   baseX=0;
	baseY=0;
	
	imageBase=NULL;
	imageRoad1=NULL;
	imageRoad2=NULL;
	imageRoad3=NULL;
	imageRoad4=NULL;
	imageRoad5=NULL;
	imageGeneral1=NULL;
	imageGeneral2=NULL;
	
	trace->event(s_fn,0,"leave [void]");  
}
	
// ------------------------------
// Destructor
// ------------------------------

Grid::~Grid()
{
	const char *s_fn="Grid::~Grid";
	trace->event(s_fn,0,"enter");

   trace->event(s_fn,0,"Grid [%d] destroyed", index);

   GRRLIB_FreeTexture(imageBase);
   GRRLIB_FreeTexture(imageRoad1);
   GRRLIB_FreeTexture(imageRoad2);
   GRRLIB_FreeTexture(imageRoad3);
   GRRLIB_FreeTexture(imageRoad4);
   GRRLIB_FreeTexture(imageRoad5);
	GRRLIB_FreeTexture(imageGeneral1);
   GRRLIB_FreeTexture(imageGeneral2);
	
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
				// Replace water element with grass element
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

GRRLIB_texImg * Grid::loadImage(const char *filename)
{
    const char *s_fn="Grid::loadImage";
    trace->event(s_fn,0,"enter [filename=%s]",filename);
   
	u8 data[MAX_BUFFER_SIZE];
	memset(data,0x00,MAX_BUFFER_SIZE);
   
	FILE *fp = fopen(filename, "r");
	if (fp!=NULL)
	{  
	    fread(&data, 1, MAX_BUFFER_SIZE, fp);
		fclose(fp);
		trace->event(s_fn,0,"leave [DATA]");
		return GRRLIB_LoadTexture( data );
	}  
	fclose(fp);
	trace->event(s_fn,0,"leave [NULL]");
	return NULL;
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
      if (pointer!=NULL) 
		{
			strcpy(gridData[maxLines],pointer); 
			strcpy(gridBuild[maxLines],pointer);  
		}
	  
		maxLines++;
   }
   
   mxmlDelete(group);
   mxmlDelete(tree);
   trace->event(s_fn,0,"leave [maxLines=%d]",maxLines);
}

void Grid::draw(int xOffset, int yOffset, float size)
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
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset, 
						imageGeneral1, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;
					
				case '~':
					// Draw water image 
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset, 
						imageGeneral2, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;
	
				case 205:
				case '1':
					// Draw basic road
					GRRLIB_DrawImg( 
						(x*(32/size))+(32/size)+xOffset, 
						(y*(32/size))+yOffset, 
						imageRoad4, 90, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;	

				case 186:
				case '2':
					// Draw basic road
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset, 
						imageRoad4, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;	
					
				case 188:	
				case '3':
					// Draw angle road
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset, 
						imageRoad3, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;	

				case 200:
				case '4':
					// Draw angle road
					GRRLIB_DrawImg( 
						(x*(32/size))+(32/size)+xOffset, 
						(y*(32/size))+yOffset, 
						imageRoad3, 90, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;	
					
				case 201:
				case '5':
					// Draw angle road
					GRRLIB_DrawImg( 
						(x*(32/size))+(32/size)+xOffset, 
						(y*(32/size))+(32/size)+yOffset,
						imageRoad3, 180, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;	
				
				case 187:
				case '6':
					// Draw angle road
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+(32/size)+yOffset, 
						imageRoad3, 270, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;	
			
				case 206:
				case '7':
					// Draw Cross road
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset, 
						imageRoad2, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;	
			
				case 204:
				case '8':
					// Draw T-section road
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset, 
						imageRoad1, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;	

				case 203:
				case '9':
					// Draw T-section road
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset, 
						imageRoad1, 90, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;

				case 185:
				case 'A':
					// Draw T-section road
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset,
						imageRoad1, 180, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;

				case 202:
				case 'B':
					// Draw T-section road
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset,
						(y*(32/size))+yOffset,
						imageRoad1, 270, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;
	
				case '=':
					// Draw bridge image
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset,
						imageRoad5, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;

				case 'H':
					// Draw bridge image
					GRRLIB_DrawImg( 
						(x*(32/size))+(32/size)+xOffset, 
						(y*(32/size))+yOffset, 
						imageRoad5, 90, (1.0/size), (1.0/size), IMAGE_COLOR );
					break;
					
				case '#':
					// Draw grass image
					GRRLIB_DrawImg( 
						(x*(32/size))+xOffset, 
						(y*(32/size))+yOffset, 
						imageGeneral1, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
					
					// Store Base Position for later use!
					baseX=x;
					baseY=y;
					break;
			}
		}
		
	}
	
	// Workarround to set base image on correct place
	if (index==1) baseX+=1;
	
	// Draw base
	GRRLIB_DrawImg( 
			(baseX*(32/size))-(16/size)+xOffset,
			(baseY*(32/size))+(5/size)+yOffset, 
			imageBase, 0, (1.0/size), (1.0/size), IMAGE_COLOR );
	
	// Draw remaining base energy bar
	if (size==1)
	{
		float proc = ( (MAX_MONSTER_IN_BASE-game.monsterInBase) / (float) MAX_MONSTER_IN_BASE ) * 21.0;
		GRRLIB_Rectangle((baseX*32)+2, (baseY*32)+71, 20, 4, GRRLIB_BLACK, 0);
		GRRLIB_Rectangle((baseX*32)+2, (baseY*32)+72, proc, 2, GRRLIB_GREEN, 1);
	}
}
	
// Load grid map and parse it for monster movement.
void Grid::create(const char* directory)
{
	const char *s_fn="Grid::render";
	trace->event(s_fn,0,"enter [directory=%s]",directory);
   
    char filename[MAX_LEN];
	sprintf(filename,"%s/map.xml",directory);
    loadGrid(filename);
	parseGrid();
	
	// Load images
	sprintf(filename,"%s/base.png",directory);
    imageBase=loadImage(filename);
	
	sprintf(filename,"%s/road1.png",directory);
    imageRoad1=loadImage(filename);

	sprintf(filename,"%s/road2.png",directory);
    imageRoad2=loadImage(filename);
	
	sprintf(filename,"%s/road3.png",directory);
    imageRoad3=loadImage(filename);
	
	sprintf(filename,"%s/road4.png",directory);
    imageRoad4=loadImage(filename);

	sprintf(filename,"%s/road5.png",directory);
    imageRoad5=loadImage(filename);
 
	sprintf(filename,"%s/general1.png",directory);
    imageGeneral1=loadImage(filename);

	sprintf(filename,"%s/general2.png",directory);
    imageGeneral2=loadImage(filename);
	
	trace->event(s_fn,0,"leave [void]");  
}
			
// ------------------------------
// Setters
// ------------------------------

void Grid::setIndex(int index1)
{
	const char *s_fn="Grid::setIndex";
	trace->event(s_fn,0,"%d",index1);
	
    index = index1;	
}

void Grid::setBuild(int x, int y)
{
	gridBuild[x][y]='F';
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

bool Grid::isBuild(int x, int y)
{
	return (gridBuild[x][y]!='0');
}

// ------------------------------
// The End
// ------------------------------