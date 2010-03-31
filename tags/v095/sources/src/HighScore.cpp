/** 
 *  @file 
 *  @brief The file contain the HighScore class methodes
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
 
#include <mxml.h>
#include <time.h>

#include "General.h"
#include "HighScore.h"
#include "Trace.h"

extern Trace *trace;

// ------------------------------
// Constructor 
// ------------------------------

/**
 * Constructor
 * Init all properties with default values.
 */
HighScore::HighScore()
{
	const char *s_fn="HighScore::HighScore";
	trace->event(s_fn,0,"enter");
   
	for(int i=0; i<MAX_LOCAL_HIGHSCORE; i++)
	{
		scores[i].localTime=0;
		scores[i].wave=0;
		scores[i].map=0;
		scores[i].score=0;
		memset(scores[i].name,0x00,MAX_LEN);
	} 
	
	trace->event(s_fn,0,"leave [void]");  
}

// ------------------------------
// Destructor
// ------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
HighScore::~HighScore()
{
	const char *s_fn="HighScore::~HighScore";
	trace->event(s_fn,0,"enter");
  
   trace->event(s_fn,0,"HighScore destroyed");
	
	trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Others
// ------------------------------

/**
 * load highscore xml file form sdcard.
 *
 * @param filename   The filename of the setting file.
 */
void HighScore::load(const char *filename)
{
	const char *s_fn="HighScore::load";
    trace->event(s_fn,0,"enter");
	
	int i;
	FILE *fp;
	mxml_node_t *tree=NULL;
	mxml_node_t *data=NULL;
	const char *tmp;
	char temp[MAX_LEN];

	maxdata=0;
   
	/*Load our xml file! */
	fp = fopen(filename, "r");
   
	if (fp!=NULL)
	{
		tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
		fclose(fp);

		for(i=0; i<MAX_LOCAL_HIGHSCORE; i++)
		{
			sprintf(temp, "entry%d", i);
			data = mxmlFindElement(tree, tree, temp, NULL, NULL, MXML_DESCEND);
  
			tmp=mxmlElementGetAttr(data,"score"); 
			if (tmp!=NULL) 
			{
				scores[maxdata].score=atoi(tmp); 
			}
			else 
			{
				scores[maxdata].score=0;
			}
		
			tmp=mxmlElementGetAttr(data,"localTime");   
			if (tmp!=NULL) 
			{
				scores[maxdata].localTime=atoi(tmp); 
			}
			else 
			{
				scores[maxdata].localTime=0;
			}
				
			tmp=mxmlElementGetAttr(data,"wave"); 
			if (tmp!=NULL) 
			{
				scores[maxdata].wave=atoi(tmp); 
			}
			else 
			{
				scores[maxdata].wave=0;
			}
		
		   tmp=mxmlElementGetAttr(data,"map"); 
			if (tmp!=NULL) 
			{
				scores[maxdata].map=atoi(tmp); 
			}
			else 
			{
				scores[maxdata].map=0;
			}
			
			tmp=mxmlElementGetAttr(data,"name"); 
			if (tmp!=NULL) 
			{
				strcpy(scores[maxdata].name,tmp); 
			}
			else 
			{
				strcpy(scores[maxdata].name,"");
			}
		
			// Entry is valid (Keep the information)
			if (scores[maxdata].score>0)
			{
				trace->event(s_fn,0,"load highscore [id=%d|score=%d|localTime=%d|wave=%d|map=%d|name=%s]"
					,maxdata, 
					scores[maxdata].score, 
					scores[maxdata].localTime,
					scores[maxdata].wave, 
					scores[maxdata].map, 
					scores[maxdata].name );
					
				maxdata++;		
			}
		} 
   }
   
   mxmlDelete(data);
   mxmlDelete(tree);
   
   trace->event(s_fn,0,"leave [void]");
}

/**
 * save highscore to xml file.
 *
 * @param filename   The filename of the setting file.
 */
void HighScore::save( const char *filename)
{
	const char *s_fn="HighScore::save";
	trace->event(s_fn,0,"enter");
	
	int i;
	mxml_node_t *xml;
	mxml_node_t *group;
	mxml_node_t *data;   
	char tmp[MAX_LEN];
      
	xml = mxmlNewXML("1.0");
	group = mxmlNewElement(xml, "TowerDefense");
   
	for(i=0; i<MAX_LOCAL_HIGHSCORE; i++)
	{
		trace->event(s_fn,0,"save highscore [id=%d|score=%d|localTime=%d|wave=%d|map=%d|name=%s]"
					,i, 
					scores[i].score, 
					scores[i].localTime,
					scores[i].wave, 
					scores[i].map, 
					scores[i].name );
					
		sprintf(tmp, "entry%d", i);
        data = mxmlNewElement(group, tmp);
  
	   sprintf(tmp, "%d", (int) scores[i].localTime);
      mxmlElementSetAttr(data, "localTime", tmp);
	  
	   sprintf(tmp, "%d", scores[i].score);
	   mxmlElementSetAttr(data, "score", tmp);

		sprintf(tmp, "%d", scores[i].wave);
	   mxmlElementSetAttr(data, "wave", tmp);
		 
		sprintf(tmp, "%d", scores[i].map);
	   mxmlElementSetAttr(data, "map", tmp);
		
	   mxmlElementSetAttr(data, "name", scores[i].name); 
	}
  
	/* now lets save the xml file to a file! */
	FILE *fp;
	fp = fopen(filename, "w");

	mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);
   
	/*Time to clean up!*/
	fclose(fp);
	
	
	mxmlDelete(data);
	mxmlDelete(group);
	mxmlDelete(xml);
   
	trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Setters
// ------------------------------

/**
 * Insert new score on the ready place in the list.
 *
 * @param name   The players name.
 * @param wave   The wave level.
 * @param map    The map id.
 * @param score  The score.
 */
void HighScore::setScore(const char *name, int wave, int map, int score)
{
	const char *s_fn="HighScore::setScore";
	trace->event(s_fn,0,"enter [name=%s|wave=%d|map=%d|score=%d)", name, wave, map, score);
	
	int marker=-1;
	
	// Find score position
	for(int i=0; i<MAX_LOCAL_HIGHSCORE; i++)
	{
		if (score>=scores[i].score)
		{
			marker=i;
			break;
		}
	}
	
	// No highscore
	if (marker==-1) return;
	
	// Move all entry on step down.
	for (int i=(MAX_LOCAL_HIGHSCORE-2); i>=marker; i--)
	{
		int offset=i+1;
		scores[offset].score = scores[i].score;
		scores[offset].wave = scores[i].wave;
		scores[offset].map = scores[i].map;
		scores[offset].localTime = scores[i].localTime;
		strcpy(scores[offset].name,scores[i].name);
	}
	
	// Insert now entry.
	scores[marker].score=score;
	scores[marker].wave=wave;
	scores[marker].map=map;
	scores[marker].localTime=time(NULL);
	strcpy(scores[marker].name,name);
	
	trace->event(s_fn,0,"leave [void]");
}


// ------------------------------
// Getters
// ------------------------------

/**
 * Get the name of highscore entry X
 *
 * @param index   The range index [0..99]
 *
 * @return The name of the player
 */
char* HighScore::getName(int index)
{
   return scores[index].name;
}

/**
 * Get the date of highscore entry X
 *
 * @param index   The range index [0..99]
 *
 * @return The entry date
 */
time_t* HighScore::getDate(int index)
{
	return &scores[index].localTime;
}

/**
 * Get the score of highscore entry X
 *
 * @param index   The range index [0..99]
 *
 * @return The score of the selected entry
 */
int HighScore::getScore(int index)
{
	return scores[index].score;
}

/**
 * Get the wave of highscore entry X
 *
 * @param index   The range index [0..99]
 *
 * @return The wave id of the selected entry
 */
int HighScore::getWave(int index)
{
	return scores[index].wave;
}

/**
 * Get the map id of highscore entry X
 *
 * @param index    The range index [0..99]
 *
 * @return The map id of the selected entry
 */
int HighScore::getMap(int index)
{
	return scores[index].map;
}

/**
 * Get the amount of score entries in the highscore array
 *
 * @return amount. The amount of score entries
 */
int HighScore::getAmount(void)
{
	int amount=0;
	for (int i=0; i<MAX_LOCAL_HIGHSCORE; i++)
	{
		if (scores[i].score!=0) amount++;
	}
	return amount;
}

// ------------------------------
// The End
// ------------------------------