#ifndef _PLANE_H_
#define _PLANE_H_
#include <vector>
#include "utils.h"

enum ExplosionType { BulletExpl, PlaneExpl };
class Explosions
{
public:
	Explosions() {};
	~Explosions() {};

	void add(double x, double y, ExplosionType type)
	{
		Explosion l;
		l.x = x;
		l.y = y;
		if (type == BulletExpl)
		{
			l.ttl = 50;
		}
		else // plane
		{
			l.ttl = 500;
		}
		expl.push_back(l);
	}
	void draw()
	{
		for (std::vector<Explosion>::iterator i = expl.begin(); i != expl.end(); ++i)
		{
			if (i->ttl > 0)
			{
				glColor4d(1.0, 1.0, 0.0, 0.5);
				glBegin(GL_POLYGON);
				for (double j = 0; j < 2 * PI; j += PI / 20)
				{
					glVertex2d(i->x + cos(j) * sqrt(i->ttl), i->y + sin(j) * sqrt(i->ttl));	
				}
				glEnd();
				i->ttl -= 20;
			}
			else
			{
				expl.erase(i);
				i--;
			}
		}
	}
	struct Explosion
	{
		double x;
		double y;
		int ttl;
	};
	std::vector<Explosion> expl;
};

class Plane
{
private:
	class Angle
	{
	public:
		Angle();
		~Angle();

		void rotateLeft(void);
		void rotateRight(void);
		void advance(Decart speed);
		double alpha;

	private:
		double speed;
		double accel;
	};

public:
	// Physics
	void countAccel();
	void stabilize();
	Angle angle;
	Decart accel;
	Decart speed;
	double forsage;
	static double gravity;
	static double maxForsage;

	//Color of the plane
	Color color;

	//For selfdrawing
	static void useTexture();
	static PNGTextures texture;

	//Reload timer
	int reload;

	void drawVectors();

	void drawTail();

	//Creates an airplane of specified color
	Plane(Color color);

	//Draw airplane at current position and angle on the screen
	void draw();
	/* Controls of airplane.*/

	//Change angle (rotate counterclockwise);
	void rotate_left();

	//Change angle (rotate clockwise);
	void rotate_right();

	//Increase speed
	void accelerate();

	//Decrease speed
	void slowdown();

	//Make a shot and return a bullet object
	Bullet fire();

	//Simulate time change
	void advance(double time);

	//Checks if reloading
	bool reloading();

	void broken();

	void drawHealthBar();

	double health;

	//Defines where CENTER of the plane is
	Decart place;

	int deathNum;

	Explosions expl;
};

#endif