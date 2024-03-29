/** 
 *  @file 
 *  @brief The file contain the Settings class methodes
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
#include <ogc/conf.h>

#include "General.h"
#include "Settings.h"
#include "Trace.h"

extern Trace *trace;

// ------------------------------
// Constructor 
// ------------------------------

/**
 * Constructor
 * Init all properties with default values.
 */
Settings::Settings()
{
   const char *s_fn="Settings::Settings";
   trace->event(s_fn,0,"enter");
   
   char ValidNick[] = "AAAAAA"; // 6 characters + the trailing NULL (game limit)
   unsigned char NickName[22];  // Name stored on the Wii, size is 0x16 bytes
   CONF_GetNickName(NickName);
   char *UpperCaseNick = strupr((char *)NickName); // Convert to uppercase (game limit)
 
   unsigned char c, d;
   for(c=0, d=0; c<sizeof(ValidNick)-1 && d<sizeof(NickName)-1; d++) {
      if((UpperCaseNick[d] >= 0x41 && UpperCaseNick[d] <= 0x5A) ||
         (UpperCaseNick[d] >= 0x30 && UpperCaseNick[d] <= 0x39)) {
         // Accept only chars used in the font (uppercase letters + numbers)
         ValidNick[c++] = UpperCaseNick[d];
      }
   }

   firstChar=ValidNick[0];
   secondChar=ValidNick[1];
   thirdChar=ValidNick[2]; 
   fourthChar=ValidNick[3];
   fifthChar=ValidNick[4];
   sixthChar=ValidNick[5];
	
   musicVolume = 5;
   effectVolume = 9;
	classicSprites=false;
   	
   trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Destructor
// ------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
Settings::~Settings()
{
	const char *s_fn="Settings::~Settings";
	trace->event(s_fn,0,"enter");
  
    trace->event(s_fn,0,"Settings destroyed");
	
	trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Others
// ------------------------------
	
/**
 * Load settings of file
 *
 * @param filename	The filename including complete directory path.
 */
void Settings::load(const char *filename)
{
    const char *s_fn="Settings::load";
    trace->event(s_fn,0,"enter");
	
    int i;
    FILE *fp;
    mxml_node_t *tree=NULL;
    mxml_node_t *data=NULL;
    const char *value;
    char temp[MAX_LEN];
   
    /*Load our xml file! */
    fp = fopen(filename, "r");
    if (fp!=NULL)
    {
	    trace->event(s_fn,0,"Load [filename=%s]",filename);
		
		tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
		fclose(fp);

		for(i=0; i<MAX_SETTINGS; i++)
		{
			sprintf(temp, "entry%d", i);
			data = mxmlFindElement(tree, tree, temp, NULL, NULL, MXML_DESCEND);
  
			if (data!=NULL)
			{
				value=mxmlElementGetAttr(data,"value"); 
			
				switch (i)
				{
					case 0: 	firstChar=value[0];
								break;

					case 1: 	secondChar=value[0];
								break;

					case 2: 	thirdChar=value[0];
								break;
	
					case 3: 	musicVolume=atoi(value);
								break;
					   
					case 4: 	effectVolume=atoi(value);
								break;
							
					case 5: 	fourthChar=value[0];
								break;
							
					case 6: 	fifthChar=value[0];
								break;
							
					case 7: 	sixthChar=value[0];
								break;
								
					case 8: 	if (atoi(value)==0)
								{
									classicSprites=false;
								}
								else
								{
									classicSprites=true;
								}
								break;
				}							
				trace->event(s_fn,0,"Store [id=%d|value=%s]",i,value);
			}
		}
	}
	else
    {
		trace->event(s_fn,0,"Setting file not found, use default values!");
    }

	mxmlDelete(data);
	mxmlDelete(tree);
	trace->event(s_fn,0,"leave [void]");
}

/**
 * Save setting to file
 *
 * @param filename	The setting filename including complete directory path
 */
void Settings::save( const char *filename)
{
    const char *s_fn="Settings::save";
    trace->event(s_fn,0,"enter");
	
    int i;
    mxml_node_t *xml;
    mxml_node_t *group;
    mxml_node_t *data;   
    char temp[MAX_LEN];
      
    xml = mxmlNewXML("1.0");
   
    group = mxmlNewElement(xml, "TowerDefense");
   
    for(i=0; i<MAX_SETTINGS; i++)
    {
        sprintf(temp, "entry%d", i);
        data = mxmlNewElement(group, temp);
  
		switch (i)
		{
			case 0: sprintf(temp, "%c", firstChar);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
					
			case 1: sprintf(temp, "%c", secondChar);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
					
			case 2: sprintf(temp, "%c", thirdChar);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
					
			case 3: sprintf(temp, "%d", musicVolume);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
					
			case 4: sprintf(temp, "%d", effectVolume);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
					
			case 5: sprintf(temp, "%c", fourthChar);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
					
			case 6: sprintf(temp, "%c", fifthChar);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
					
			case 7: sprintf(temp, "%c", sixthChar);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
					
			case 8: sprintf(temp, "%d", classicSprites);
					mxmlElementSetAttr(data, "value", temp);			  
					break;
		}
    }
  
    /* now lets save the xml file to a file! */
    FILE *fp;
    fp = fopen(filename, "w");

    mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);
   
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
 * Set first character of player nickname.
 *
 * @param letter 	The character.
 */
void Settings::setFirstChar(char letter)
{
	const char *s_fn="Settings::setFirstChar";
    trace->event(s_fn,0,"%c",letter);
	
	firstChar=letter;
}

/**
 * Set second character of player nickname.
 *
 * @param letter 	The character.
 */
void Settings::setSecondChar(char letter)
{
	const char *s_fn="Settings::setSecondChar";
    trace->event(s_fn,0,"%c",letter);
	
	secondChar=letter;
}

/**
 * Set third character of player nickname.
 *
 * @param letter 	The character.
 */
void Settings::setThirdChar(char letter)
{
	const char *s_fn="Settings::setThirdChar";
    trace->event(s_fn,0,"enter [letter=%c]",letter);
	
	thirdChar=letter;
}

/**
 * Set fourth character of player nickname.
 *
 * @param letter 	The character.
 */
void Settings::setFourthChar(char letter)
{
	const char *s_fn="Settings::setFourthChar";
    trace->event(s_fn,0,"enter [letter=%c]",letter);
	
	fourthChar=letter;
}

/**
 * Set fifth character of player nickname.
 *
 * @param letter 	The character.
 */
void Settings::setFifthChar(char letter)
{
	const char *s_fn="Settings::setFifthChar";
    trace->event(s_fn,0,"enter [letter=%c]",letter);
	
	fifthChar=letter;
}

/**
 * Set sixth character of player nickname.
 *
 * @param letter 	The character.
 */
void Settings::setSixthChar(char letter)
{
	const char *s_fn="Settings::setSixthChar";
    trace->event(s_fn,0,"enter [letter=%c]",letter);
	
	sixthChar=letter;
}

/**
 * Set music volume.
 *
 * @param volume 	The music volume value [0..128].
 */
void Settings::setMusicVolume(int volume)
{
	const char *s_fn="Settings::setMusicVolume";
    trace->event(s_fn,0,"%d",volume);
	
	musicVolume=volume;
}

/**
 * Set effect volume.
 *
 * @param volume 	The effect volume value [0..128].
 */
void Settings::setEffectVolume(int volume)
{
	const char *s_fn="Settings::setEffectVolume";
   trace->event(s_fn,0,"%d", volume);
	
	effectVolume=volume;
}

/**
 * Set class sprite mode.
 *
 * @param enabled 	True, classic sprites. False, animated sprites.
 */
void Settings::setClassicSprites(bool enabled)
{
   const char *s_fn="Settings::setClassicSprites";
   trace->event(s_fn,0,"%d", enabled);
	
	classicSprites=enabled;
}
		
// ------------------------------
// Getters
// ------------------------------

/**
 * Get first character of player nickname.
 *
 * @return character
 */
char Settings::getFirstChar(void)
{
	return firstChar;
}

/**
 * Get second character of player nickname.
 *
 * @return character
 */
char Settings::getSecondChar(void)
{
	return secondChar;
}

/**
 * Get third character of player nickname.
 *
 * @return character
 */
char Settings::getThirdChar(void)
{
	return thirdChar;
};

/**
 * Get fourth character of player nickname.
 *
 * @return character
 */
char Settings::getFourthChar(void)
{
	return fourthChar;
};

/**
 * Get fifth character of player nickname.
 *
 * @return character
 */
char Settings::getFifthChar(void)
{
	return fifthChar;
};

/**
 * Get sixth character of player nickname.
 *
 * @return character
 */
char Settings::getSixthChar(void)
{
	return sixthChar;
};

/**
 * Get music volume
 *
 * @return volume [0..128]
 */
int Settings::getMusicVolume(void)
{
	return musicVolume;
}

/**
 * Get effect volume
 *
 * @return volume [0..128]
 */
int Settings::getEffectVolume(void)
{
	return effectVolume;
}

/**
 * Get classic sprite
 *
 * @return classic sprite mode [true | false]
 */
bool Settings::getClassicSprites(void)
{
	return classicSprites;	
}

// ------------------------------
// The End
// ------------------------------