#ifndef ENEMY_H
#define ENEMY_H

#include "GRRLIB.h"

class Enemy
{
  private:
	int x;
	int y;	
	int alfa;
	float size;
	int angle;
	int targetAngle;
	GRRLIB_texImg image;
	int height;
	int width;
	bool xDirection;
	bool yDirection;
	int step;
	
  public:
  	Enemy();
	Enemy(int x,int y, int height, int width, float size, int angle, int alfa, GRRLIB_texImg image );
 	~Enemy();
	
	void setX(int x);
	void setY(int y);
	void setAlfa(int alfa);
	void setSize(float size);
	void setAngle(int angle);
	void setImage(char *image);
    void setWidth(int width);
	void setHeight(int height);
	void setStep(int step);
	
	int getX(void);
	int getY(void);
	int getAlfa(void);
	float getSize(void);
	int getAngle(void);
	GRRLIB_texImg getImage(void);
	int getWidth(void);
	int getHeight(void);
	int getStep(void);
	
	void properties(void);
	void draw(void);
	void move(void);
};

#endif
