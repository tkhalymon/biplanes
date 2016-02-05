#include "plane.h"
#include <stdio.h>

double Plane::gravity = 1.1;
double Plane::maxForsage = 1.5;
PNGTextures Plane::texture;

Plane::Angle::Angle()
{
	this->alpha = PI / 3;
}

Plane::Angle::~Angle()
{}

void Plane::Angle::rotateLeft()
{
	accel = 0.02;
}

void Plane::Angle::rotateRight()
{
	accel = - 0.02;
}

void Plane::Angle::advance(Decart planeSpeed)
{
	double alphaSpeed = projectate(planeSpeed, this->alpha).radius;
	if (alphaSpeed <= 0) alphaSpeed *= -1;
	speed += accel * (alphaSpeed + 5) / 3;
	alpha += speed * (alphaSpeed) / 4;
	accel = 0;
	speed = 0;
}

Plane::Plane(Color color)
{
	this->color = color;
	if (this->color == BLUE) texture.load("res/plane.png");
	broken();
	deathNum = 0;
}

void Plane::countAccel()
{
	accel = Decart(forsage * cos(angle.alpha), forsage * sin(angle.alpha));
	Polar speedAlpha = projectate(Decart(forsage * cos(angle.alpha), forsage * sin(angle.alpha)),
		angle.alpha);
	if (speedAlpha.radius > 0)
	{
		accel.x -= speed.x * 1 / 5;
		accel.y -= speed.y * 1 / 5;
		glBegin(GL_LINES);
			glVertex2d(0, 0);
			glVertex2d(10, 10);
		glEnd();
	}
	else
	{
		accel.x -= speed.x * 1 / 5;
		accel.y -= speed.y * 1 / 5;
	}
	stabilize();
	if (color == BLUE)
		accel.y -= gravity;
	else accel.y += gravity;
	accel.x /= 30;
	accel.y /= 30;
}

void Plane::stabilize()
{
	Polar dest = projectate(speed, angle.alpha + PI / 2);
	Polar alphaSpeed = projectate(speed, angle.alpha);
	glBegin(GL_LINES);
		glVertex2d(40, 20);
		glVertex2d(40 + alphaSpeed.radius * 100, 20);
	glEnd();
	if (alphaSpeed.radius < 0) dest.radius *= -1;
	accel.x -= dest.radius * cos(dest.angle) * alphaSpeed.radius * 1;
	accel.y -= dest.radius * sin(dest.angle) * alphaSpeed.radius * 1;
	if (speed.Distance() < 1.5)
	{
		if (color == BLUE)
			angle.alpha -= cos(angle.alpha) * (1.5 - speed.Distance()) / 50;
		else
			angle.alpha -= cos(angle.alpha + PI) * (1.5 - speed.Distance()) / 50;
	}
}

void Plane::accelerate()
{
	forsage += 0.01;
	if (forsage > maxForsage) forsage = maxForsage;
}

void Plane::slowdown()
{
	forsage -= 0.01;
	if (forsage < 0) forsage = 0;
}

void Plane::rotate_left()
{
	angle.rotateLeft();
}

void Plane::rotate_right()
{
	angle.rotateRight();
}

void Plane::advance(double time)
{
	if (reload != 0) reload --;
	Decart winSize = Decart(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	angle.advance(speed);
	if (angle.alpha > 2 * PI) angle.alpha -= 2 * PI;
	if (angle.alpha < 0) angle.alpha += 2 * PI;
	countAccel();
	speed.x += accel.x;
	speed.y += accel.y;
	if (color == BLUE)
	{
		place.x += speed.x;
		place.y += speed.y;
	}
	else
	{
		place.x -= speed.x;
		place.y -= speed.y;
	}

	if (place.x < 0) place.x += winSize.x;
	if (place.x > winSize.x) place.x -= winSize.x;
	if (place.y < 100) broken();
	if (place.y > winSize.y - 35) place.y = winSize.y - 35;
}

Bullet Plane::fire()
{
	reload = 10;
	double x = place.x;
	double y = place.y;
	double power = 5 + speed.Distance();
	double bullet_angle;

	switch (color)
	{
	case BLUE:
		x += cos(angle.alpha) * 40;
		y += sin(angle.alpha) * 21;
		bullet_angle = angle.alpha;
		break;
	case RED:
		x -= cos(angle.alpha) * 40;
		y -= sin(angle.alpha) * 21;
		bullet_angle = angle.alpha + PI;
		break;
	}

	Bullet b(x,y, bullet_angle, power + 2);

	return b;
}

void Plane::draw()
{
	// PNGTextures texture;
	
	double d, a;
	d = sqrt(pow(texture.width / 2, 2) + pow(texture.height / 2, 2));
	a = acos(texture.width / d / 2);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	useTexture();
	if (this->color == BLUE)
	{	
	glColor4d(0.1, 0.1, 1.0, 1);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0, 0.0);
		glVertex2d(place.x - cos(a - angle.alpha) * d, place.y + sin(a - angle.alpha) * d);
		glTexCoord2d(1.0, 0.0);
		glVertex2d(place.x + cos(a + angle.alpha) * d, place.y + sin(a + angle.alpha) * d);
		glTexCoord2d(1.0, 1.0);
		glVertex2d(place.x + cos(a - angle.alpha) * d, place.y - sin(a - angle.alpha) * d);
		glTexCoord2d(0.0, 1.0);
		glVertex2d(place.x - cos(a + angle.alpha) * d, place.y - sin(a + angle.alpha) * d);
	glEnd();
	}
	else
	{	
	glColor4d(1.0, 0.1, 0.1, 1);
	glBegin(GL_POLYGON);
		glTexCoord2d(1.0, 0.0);
		glVertex2d(place.x - cos(a - angle.alpha) * d, place.y + sin(a - angle.alpha) * d);
		glTexCoord2d(0.0, 0.0);
		glVertex2d(place.x + cos(a + angle.alpha) * d, place.y + sin(a + angle.alpha) * d);
		glTexCoord2d(0.0, 1.0);
		glVertex2d(place.x + cos(a - angle.alpha) * d, place.y - sin(a - angle.alpha) * d);
		glTexCoord2d(1.0, 1.0);
		glVertex2d(place.x - cos(a + angle.alpha) * d, place.y - sin(a + angle.alpha) * d);
	glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	
	expl.draw();
	glDisable(GL_BLEND);
}

bool Plane::reloading()
{
	return reload != 0;
}

void Plane::broken()
{
	if (health != 0)
	{
		expl.add(place.x, place.y, PlaneExpl);
	}
	health = 10;
	accel = Decart(0, 0);
	angle.alpha = 0.3;
	forsage = 0.7;
	reload = 0;
	speed = Decart(2, 0);
	
	switch (color)
	{
	case BLUE:
		place = Decart(50, 120);
		break;
	case RED:
		angle.alpha *= - 1;
		place = Decart(glutGet(GLUT_WINDOW_WIDTH) - 50, 120);
		break;
	}
	deathNum++;
}

void Plane::drawHealthBar()
{
	static int winWidth = glutGet(GLUT_WINDOW_WIDTH);
	static char buffer[10];
	static int i = 0;	
	switch(this->color)
	{
	case BLUE:
		glBegin(GL_LINE_LOOP);
			glColor3d(1.0, 1.0, 1.0);
			glVertex2d(50, 10);
			glVertex2d(350, 10);
			glVertex2d(350, 30);
			glVertex2d(50, 30);
		glEnd();
		glBegin(GL_QUADS);
			glColor3d(0.3, 0.3, 1.0);
			glVertex2d(50, 11);
			glVertex2d(50, 30);
			glVertex2d(50 + health * 30 - 1, 30);
			glVertex2d(50 + health * 30 - 1, 11);
		glEnd();
		glBegin(GL_QUADS);
			glColor3d(0.3, 0.3, 1.0);
			glVertex2d(50, 35);
			glVertex2d(50, 45);
			glVertex2d(50 + (forsage / maxForsage) * 300 - 1, 45);
			glVertex2d(50 + (forsage / maxForsage) * 300 - 1, 35);
		glEnd();
		glColor3d(1.0, 1.0, 1.0);
		glRasterPos2d(winWidth / 2 + 15, 10);
		snprintf(buffer, 10, "%d", deathNum);
		i = 0;
		while(buffer[i] != '\0')
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
			i++;
		}
		break;
	case RED:
		glBegin(GL_LINE_LOOP);
			glColor3d(1.0, 1.0, 1.0);
			glVertex2d(winWidth - 50, 10);
			glVertex2d(winWidth - 350, 10);
			glVertex2d(winWidth - 350, 30);
			glVertex2d(winWidth - 50, 30);
		glEnd();
		glBegin(GL_QUADS);
			glColor3d(1.0, 0.3, 0.3);
			glVertex2d(winWidth - 50 - 1, 11);
			glVertex2d(winWidth - 50 - 1, 30);
			glVertex2d(winWidth - 50 - health * 30, 30);
			glVertex2d(winWidth - 50 - health * 30, 11);
		glEnd();
		glBegin(GL_QUADS);
			glColor3d(1.0, 0.3, 0.3);
			glVertex2d(winWidth - 50 - 1, 35);
			glVertex2d(winWidth - 50 - 1, 45);
			glVertex2d(winWidth - 50 - (forsage / maxForsage) * 300, 45);
			glVertex2d(winWidth - 50 - (forsage / maxForsage) * 300, 35);
		glEnd();
		
		glColor3d(1.0, 1.0, 1.0);
		glRasterPos2d(winWidth / 2 - 15, 10);
		snprintf(buffer, 10, "%d", deathNum);
		i = 0;
		while(buffer[i] != '\0')
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
			i++;
		}
		break;
	}
	glColor3d(1, 1, 1);
	glRasterPos2d(winWidth / 2 + 3, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
}
