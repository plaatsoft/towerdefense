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

#ifndef MONSTERSPECS_H
#define MONSTERSPECS_H

#include "GRRLIB.h" 

class MonsterSpecs
{
  private:
  
   // Classic emenies images
	GRRLIB_texImg *monster1;
	GRRLIB_texImg *monster2;
	GRRLIB_texImg *monster3;
	GRRLIB_texImg *monster4;
	GRRLIB_texImg *monster5;  
	GRRLIB_texImg *monster6;
	GRRLIB_texImg *monster7;
	GRRLIB_texImg *monster8;
	GRRLIB_texImg *monster9;
	GRRLIB_texImg *monster10;
	GRRLIB_texImg *monster11;
	GRRLIB_texImg *monster12;
	GRRLIB_texImg *monster13;
	GRRLIB_texImg *monster14;
	GRRLIB_texImg *monster15;
	GRRLIB_texImg *monster16;
	GRRLIB_texImg *monster17;
	GRRLIB_texImg *monster18;
	GRRLIB_texImg *monster19;
	GRRLIB_texImg *monster20;
	GRRLIB_texImg *monster21;
	GRRLIB_texImg *monster22;
	GRRLIB_texImg *monster23;
	GRRLIB_texImg *monster24;
	GRRLIB_texImg *monster25;
	
	// Animated images.
	GRRLIB_texImg *monster1a;
	GRRLIB_texImg *monster2a;
	GRRLIB_texImg *monster3a;
	GRRLIB_texImg *monster4a;
	GRRLIB_texImg *monster5a;
	GRRLIB_texImg *monster6a;
	GRRLIB_texImg *monster7a;
	GRRLIB_texImg *monster8a;
	GRRLIB_texImg *monster9a;
	GRRLIB_texImg *monster10a;
	GRRLIB_texImg *monster11a;
	GRRLIB_texImg *monster12a;
	GRRLIB_texImg *monster13a;
	GRRLIB_texImg *monster14a;
	GRRLIB_texImg *monster15a;
	GRRLIB_texImg *monster16a;
	GRRLIB_texImg *monster17a;
	GRRLIB_texImg *monster18a;
	GRRLIB_texImg *monster19a;
	GRRLIB_texImg *monster20a;
	GRRLIB_texImg *monster21a;
	
  public:
  	// Constructor & Destructor
	MonsterSpecs();
 	~MonsterSpecs();
		
	// Getters
	GRRLIB_texImg * getImage(int type);
	int getEnergy(int type);
};

#endif




