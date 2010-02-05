/** 
 *  @file 
 *  @brief The file contain the HighScore class
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

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

typedef struct
{
   time_t localTime;
   int    wave;
   int    score; 
	int    map;
   char   name[MAX_LEN];
}
Score;

class HighScore
{
  private:
	int maxdata;
	Score scores[MAX_LOCAL_HIGHSCORE];

  public:
  	// Constructor & Destructor
	HighScore();
 	~HighScore();
	
	// Other
	void load(const char *filename);
	void save( const char *filename);
	
	// Setters
	void setScore(const char *name, int wave, int map, int score);
	
	// Getters
	char *getName(int index);
	time_t *getDate(int index);
	int  getWave(int index);
	int  getScore(int index);
	int  getMap(int index);
	int  getAmount();
};

#endif
