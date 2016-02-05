#include <GL/glut.h>
#include <math.h>
#include <vector>
#include "lodepng.h"
#include "utils.h"
#include "bullet.h"
#include "plane.h"
// PNGTextures texture;

Polar projectate(Decart vect, double angle)
{
	Polar temp = vect.toPolar();
	temp.radius *= cos(temp.angle - angle);
	temp.angle = angle;
	return temp;
}

void PNGTextures::load(const char *fileName)
{
	std::vector<unsigned char> image;
	unsigned error = lodepng::decode(image, this->width, this->height, fileName);
	if (error != 0) glutDestroyWindow(1);
	glGenTextures(1, this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
}

void Plane::useTexture()
{
	texture.use();
}

void PNGTextures::use(void)
{
	glBindTexture(GL_TEXTURE_2D, this->texture[0]);
}

Polar::Polar(double _angle, double _radius)
{
	this->angle = _angle;
	this->radius = _radius;
}

Polar Decart::toPolar()
{
	double angle;
	double power = Distance();
	if (y > 0) angle = acos(x / Distance());
	else angle = 2 * PI - acos(x / Distance());
	return Polar(angle, power);
}

Decart::Decart(double _x, double _y)
{
	this->x = _x;
	this->y = _y;
}

double Decart::Distance()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

double Decart::Distance(Decart other)
{
	return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
}

double Decart::Angle()
{
	if (y > 0) return acos(x / Distance());
	else return 2 * PI - acos(x / Distance());
}

Decart Polar::toDecart()
{
	if (angle < PI)
		return Decart(cos(angle) * radius, sin(angle) * radius);
	else
		return Decart(cos(angle) * radius, sin(angle) * radius);
}

void drawGround()
{
	int winWidth = glutGet(GLUT_WINDOW_WIDTH);
	glBegin(GL_POLYGON);
	glColor3d(0.0, 0.0, 0.0);
	glVertex2d(0, 0);
	glVertex2d(winWidth, 0);
	glColor3d(0.2, 0.2, 0.2);
	glVertex2d(winWidth, 85);
	glVertex2d(0, 85);
	glEnd();
}
