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

//Trace trace;

int maxLine;
char data[15][20];

// ------------------------------
// Constructor
// ------------------------------

Map::Map()
{

}
	
// ------------------------------
// Destructor
// ------------------------------

Map::~Map()
{
  
}

// ------------------------------
// Others
// ------------------------------

void initMap(char* filename)
{
   char *s_fn="initMap";
   //trace.event(s_fn,0,"enter");
   
   FILE *fp;
   mxml_node_t *tree;
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
   //trace.event(s_fn,0,"leave [void]");
}

void Map::draw(void)
{

}

boolean Map::onLoad(void)
{
	initMap(MAP1_FILENAME);
}
			
// ------------------------------
// Getters and Setters
// ------------------------------

void Map::setLevel(int level1)
{
   if ((level>=0) && (level<=MAX_LEVEL))
   {
      level = level1;
   }
}

// ------------------------------
// The End
// ------------------------------