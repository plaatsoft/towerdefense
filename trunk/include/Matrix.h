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

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
  private:
	int wave;
	int level;
	int waveDelay;
	int enemyDelay;
	int minStep;
	int stepFactor;
	int enemiesInWave;
	
	void calculateMatrix(void);

  public:
  	// Constructor & Destructor
	Matrix();
 	~Matrix();
		
	// Getters
	int getEnemyAmount( void );
	int getEnemyStep( void );
	int getEnemyDelay( void );
	int getStartCash( void );
	int getWaveDelay( void );

	// Setters
	void setWave(int wave);
	void setLevel( int level );
};


#endif