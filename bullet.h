#ifndef _BULLET_H_
#define _BULLET_H_
#include "utils.h"

class Bullet
{
public:
	Bullet(double x, double y, double angle, double power);
	~Bullet();
	double speedX;
	double speedY;
	double x;
	double y;

	double ttl;

	void draw();
	void advance(double);

};


#endif