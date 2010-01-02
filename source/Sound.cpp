/*  
**  Created by wplaat (www.plaatsoft.nl)
**
**  Copyright (C) 2009-2010
**  =======================
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

#include "General.h"
#include "GRRLIB.h"
#include "Settings.h"
#include "Sound.h"
#include "Trace.h"

#include "canon_pcm.h"
#include "click_pcm.h"
#include "death_pcm.h"
#include "gun_pcm.h"
#include "laser_pcm.h"
#include "rifle_pcm.h"
#include "rocket_pcm.h"
#include "upgrade_pcm.h"
#include "start_pcm.h"
#include "finish_pcm.h"
#include "lanch_pcm.h"

#include "track1_mod.h"
#include "track2_mod.h"
#include "track3_mod.h"
#include "track4_mod.h"
#include "track5_mod.h"
#include "track6_mod.h"
#include "track7_mod.h"
#include "track8_mod.h"
#include "track9_mod.h"

extern 	Trace *trace;

// ------------------------------
// Constructor 
// ------------------------------

Sound::Sound()
{
   const char *s_fn="Sound::Sound";
   trace->event(s_fn,0,"enter");
   
   musicVolume = 5;
   effectVolume = 9;
   musicTrack = 1;
	
   // Init Sound engine	
   SND_Init(INIT_RATE_48000); 
   SND_Pause(0);
   
   trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Destructor
// ------------------------------

Sound::~Sound()
{
  const char *s_fn="Sound::~Sound";
  trace->event(s_fn,0,"enter");
  
  trace->event(s_fn,0,"Sound destroyed");
		
  // Stop music
  MODPlay_Stop(&snd1);
   
  trace->event(s_fn,0,"leave [void]");
}

// ------------------------------
// Others
// ------------------------------
 
void Sound::play(void)
{
	const char *s_fn="Sound::play";
	trace->event(s_fn,0,"enter");
   
	MODPlay_Init(&snd1);
	MODPlay_Stop(&snd1);
	MODPlay_Pause(&snd1,false);
 
    // Restart music track after finished
    snd1.manual_polling=false;
   
    switch (musicTrack)
    {
       case 1 : MODPlay_SetMOD(&snd1, track1_mod);
		 	    MODPlay_Start(&snd1);	
		 	    break;	
			   
       case 2 : MODPlay_SetMOD(&snd1, track2_mod);
			    MODPlay_Start(&snd1);	
			    break;
			   
       case 3 : MODPlay_SetMOD(&snd1, track3_mod);
			    MODPlay_Start(&snd1);	
			    break;
			   
       case 4 : MODPlay_SetMOD(&snd1, track4_mod);
			    MODPlay_Start(&snd1);	
			    break;
			   
       case 5 : MODPlay_SetMOD(&snd1, track5_mod);
		 	    MODPlay_Start(&snd1);	
			    break;	
		   
	   case 6 : MODPlay_SetMOD(&snd1, track6_mod);
			    MODPlay_Start(&snd1);	
			    break;	
			   
	   case 7 : MODPlay_SetMOD(&snd1, track7_mod);
			    MODPlay_Start(&snd1);	
			    break;	
			   
	   case 8 : MODPlay_SetMOD(&snd1, track8_mod);
			    MODPlay_Start(&snd1);	
			    break;	
			   
	   case 9 : MODPlay_SetMOD(&snd1, track9_mod);
			    MODPlay_Start(&snd1);	
			    break;
    } 
    MODPlay_SetVolume( &snd1, musicVolume*MUSIC_MULTIPLER,musicVolume*MUSIC_MULTIPLER); 
    
	trace->event(s_fn,0,"leave [void]");
}
	
void Sound::effect(int type)
{
	switch(type)
	{
		// Gun
		case SOUND_GUN:
            SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) gun_pcm, gun_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	
			
		// Rifle
		case SOUND_RIFLE:
            SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) rifle_pcm, rifle_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	
			
		// Canon
		case SOUND_CANON:
           SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (u8 *) canon_pcm, canon_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
			break;
		
		// Missle
		case SOUND_MISSLE:
            SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) rocket_pcm, rocket_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	
			
		// Laser
		case SOUND_LASER:
           SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) laser_pcm, laser_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	
			

			
		// Click
		case SOUND_CLICK:
			SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (u8 *) click_pcm, click_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);				   
			break;

		// Dead
		case SOUND_DEAD:
            SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) death_pcm, death_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	

		// Upgrade
		case SOUND_UPGRADE:
            SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) upgrade_pcm, upgrade_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	
			
		// Start
		case SOUND_START:
            SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) start_pcm, start_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	

		// Finish
		case SOUND_FINISH:
            SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) finish_pcm, finish_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	
			
		// Launch
		case SOUND_LAUNCH:
            SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) lanch_pcm, lanch_pcm_size, 
				effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);
 	        break;	
			
	}
}

// ------------------------------
// Setters
// ------------------------------


void Sound::setMusicVolume(int volume)
{
	const char *s_fn="Sound::setMusicVolume";
	trace->event(s_fn,0,"%d",volume);
	
	if ((volume>=0) && (volume<=MAX_SOUND_VOLUME))
	{
		musicVolume=volume;
		MODPlay_SetVolume( &snd1, musicVolume*MUSIC_MULTIPLER,musicVolume*MUSIC_MULTIPLER);
	}
}


void Sound::setEffectVolume(int volume)
{	
	const char *s_fn="Sound::setEffectVolume";
	trace->event(s_fn,0,"%d",volume);
	
	if ((volume>=0) && (volume<=MAX_SOUND_VOLUME))
	{
		effectVolume=volume;
	}
}


void Sound::setMusicTrack(int track)
{
	const char *s_fn="Sound::setMusicTrack";
	trace->event(s_fn,0,"%d",track);
	
	if (track<1) 
	{
		musicTrack=MAX_MUSIC_TRACK;
		play();
	}
	else 
	{
		if (track>MAX_MUSIC_TRACK)
		{
			musicTrack=1;
			play();
		}
		else
		{
			musicTrack=track;
			play();
		}
	}
}
	
// ------------------------------
// Getters
// ------------------------------

int Sound::getMusicVolume()
{
	return musicVolume;
}

int Sound::getEffectVolume()
{
	return effectVolume;
}

int Sound::getMusicTrack()
{
	return musicTrack;
}

// ------------------------------
// The End
// ------------------------------

