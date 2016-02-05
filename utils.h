#ifndef _UTILS_H_
#define _UTILS_H_
#include <GL/glut.h>
#include <math.h>
#include "lodepng.h"
#include "bullet.h"

#define PI acos(- 1)

class Decart;
class Polar;

Polar projectate(Decart vect, double angle);

class PNGTextures
{
public:
	unsigned int texture[1];
	unsigned width;
	unsigned height;
	PNGTextures() {};
	void load(const char *fileName);
	~PNGTextures() {};
	void use(void);
};

enum Color {RED, BLUE};


class Decart
{
public:
	Decart() {};
	Decart(double x, double y);
	~Decart() {};

	Polar toPolar();
	double Distance();
	double Distance(Decart other);
	double Angle();
	
	double x;
	double y;
};

class Polar
{
public:
	Polar() {};
	Polar(double angle, double power);
	~Polar() {};

	Decart toDecart();
	double angle;
	double radius;
};

void drawGround();

#endif
