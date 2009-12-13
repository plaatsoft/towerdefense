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

#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
  private:
    char firstChar;
	char secondChar;
	char thirdChar;
	int  musicVolume;
	int  effectVolume;
	
  public:
  	// Constructor & Destructor
	Settings();
 	~Settings();
	
	// Methodes
	void load(const char *filename);
	void save( const char *filename);
	
	// Setters
	void setFirstChar(char letter);
	void setSecondChar(char letter);
	void setThirdChar(char letter);
	void setMusicVolume(int volume);
	void setEffectVolume(int volume);

	// Getters
	char getFirstChar(void);
	char getSecondChar(void);
	char getThirdChar(void);
	int  getMusicVolume(void);
	int  getEffectVolume(void);
};

#endif
