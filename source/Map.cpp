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
#include "Map.h"

int maxLine;
char data[15][20];

extern Trace trace;

// ------------------------------
// Constructor
// ------------------------------

Map::Map()
{
	const char *s_fn="Map::Map";
	trace.event(s_fn,0,"enter");
   
	trace.event(s_fn,0,"leave [void]");  
}
	
// ------------------------------
// Destructor
// ------------------------------

Map::~Map()
{
	const char *s_fn="Map::~Map";
	trace.event(s_fn,0,"enter");

	trace.event(s_fn,0,"leave [void]");  
}

// ------------------------------
// Others
// ------------------------------

void initMap(const char* filename)
{
   const char *s_fn="Map::initMap";
   trace.event(s_fn,0,"enter");
   
   FILE *fp;
   mxml_node_t *tree =NULL;
   mxml_node_t *group;   
   const char  *pointer;

   maxLine=0;
   
   /*Load our xml file! */
   fp = fopen(filename, "r");
   if (fp!=NULL)
   {   
      tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
      fclose(fp);
   }
    
   // Read Map Lines
   for (group = mxmlFindElement(tree, tree, "line", NULL, NULL, MXML_DESCEND);
        group != NULL;
        group = mxmlFindElement(group, tree, "line", NULL, NULL, MXML_DESCEND))
   {		  
      pointer=mxmlElementGetAttr(group,"id");
	  if (pointer!=NULL) strcpy(data[maxLine],pointer); 
	  	  
      pointer=mxmlElementGetAttr(group,"data");
      if (pointer!=NULL) strcpy(data[maxLine],pointer);  
	  
	  maxLine++;
   }
   
   mxmlDelete(group);
   mxmlDelete(tree);
   trace.event(s_fn,0,"leave [void]");
}

void Map::draw(void)
{

}

boolean Map::onLoad(void)
{
	const char *s_fn="Map::onLoad";
	trace.event(s_fn,0,"enter");
	
	initMap(MAP1_FILENAME);
	
	trace.event(s_fn,0,"leave [true]");  
	return true;
}
			
// ------------------------------
// Getters and Setters
// ------------------------------

void Map::setLevel(int level1)
{
	const char *s_fn="Map::setLevel";
	trace.event(s_fn,0,"enter");
	
   if ((level>=0) && (level<=MAX_LEVEL))
   {
      level = level1;
   }
   
   trace.event(s_fn,0,"leave [void]");  
}

// ------------------------------
// The End
// ------------------------------