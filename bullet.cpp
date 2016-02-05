#include <GL/glut.h>
#include <iostream>
#include "bullet.h"
#include "math.h"
Bullet::Bullet(double x, double y, double angle, double power)
{
	ttl = 70 + rand() % 30;
	this->speedX = cos(angle) * power;
	this->speedY = sin(angle) * power;
	this->x = x;
	this->y = y;
}

void Bullet::draw()
{
	// glBegin(GL_QUADS);
	// 	glColor3d(0.0, 0.0, 0.0);
	// 	glVertex2d(x - 2, y - 2);
	// 	glVertex2d(x + 2, y - 2);
	// 	glVertex2d(x + 2, y + 2);
	// 	glVertex2d(x - 2, y + 2);
	// glEnd();
	glBegin(GL_LINES);
		glColor4d(0.0, 0.0, 0.0, 1.0);
		glVertex2d(x, y);
		glColor4d(0.0, 0.0, 0.0, 0.0);
		glVertex2d(x - speedX, y - speedY);
	glEnd();
}

void Bullet::advance(double time)
{
	speedY -= 0.02;
	x += speedX;
	y += speedY;
	ttl--;
	if (x < 0) x += glutGet(GLUT_WINDOW_WIDTH);
	if (x > glutGet(GLUT_WINDOW_WIDTH)) x -= glutGet(GLUT_WINDOW_WIDTH);
}

Bullet::~Bullet(){}