/** 
 *  @file 
 *  @brief The file contain the Sound class
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

#ifndef SOUND_H
#define SOUND_H

#include <gcmodplay.h> 
#include <asndlib.h>

enum
{
	SOUND_GUN=0,
	SOUND_RIFLE=1,
	SOUND_CANON=2,
	SOUND_MISSLE=3,
	SOUND_LASER=4,	
	
	SOUND_CLICK=5,
	SOUND_DEAD=6,
	SOUND_UPGRADE=7,
	SOUND_START=8,
	SOUND_FINISH=9,
	SOUND_LAUNCH=10
};
				
class Sound
{
  private:
	MODPlay snd1;	
	int musicVolume;
	int effectVolume;
	int musicTrack;
	
  public:
  	// Constructor & Destructor
	Sound();
 	~Sound();

	// Methodes
	void play(void);
	void effect(int type);

	// Setters	
	void setMusicVolume(int volume);
	void setEffectVolume(int volume);
	void setMusicTrack(int track);
		
	// Getters
	int getMusicVolume(void);
	int getEffectVolume(void);
	int getMusicTrack(void);
};

#endif
