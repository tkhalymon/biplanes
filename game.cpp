#include "game.h"
#include "bullet.h"
#include <GL/glut.h>


Game::Game()
{
	plane1 = new Plane(RED);
	plane2 = new Plane(BLUE);
}

Game::~Game()
{
	//delete(plane1);
	//delete(plane2);
}

void Game::advance()
{
	int winY = glutGet(GLUT_WINDOW_HEIGHT);
	plane1->advance(1);
	plane2->advance(1);
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].advance(1);
		if (bullets[i].ttl < 0)
		{
			bullets.erase(bullets.begin() + i);
		}
		if (bullets[i].y > winY || bullets[i].y < 0)
		{
			bullets.erase(bullets.begin() + i);
		}
		if (plane1->place.Distance(Decart(bullets[i].x, bullets[i].y))<21)
		{
			plane1->health -= bullets[i].ttl / 150; // can be anything
			if (plane1->health <= 0) plane1->broken();
			// if (--plane1->health==0) plane1->broken();
			bullets.erase(bullets.begin() + i);	
			// expl.add(bullets[i].x, bullets[i].y, BulletExpl);
		}
		if (plane2->place.Distance(Decart(bullets[i].x, bullets[i].y))<21)
		{
			plane2->health -= (bullets[i].ttl + 100) / 150; // can be anything
			if (plane2->health <= 0) plane2->broken();
			// if (--plane2->health==0) plane2->broken();
			bullets.erase(bullets.begin() + i);
		}

	}
}

void Game::redraw()
{
	drawGround();
	plane1->drawHealthBar();
	plane2->drawHealthBar();
	plane1->draw();
	plane2->draw();
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].draw();
	}
}


void Game::sendControls(bool kb[], bool kb_special[])
{
	for (int i = 0; i < 256; i++)
	{
		if (kb[i])
		{
			int key = i;
			switch (key)
			{
			case 'w':
				plane2->accelerate();
				break;
			case 's':
				plane2->slowdown();
				break;
			case 'a':
				plane2->rotate_left();
				break;
			case 'd':
				plane2->rotate_right();
				break;
			case 'q':
				if (!plane2->reloading()) bullets.insert(bullets.end(), plane2->fire());
				break;
			}
		}

		if (kb_special[i])
		{
			int key = i;
			switch (key)
			{
			case GLUT_KEY_UP:
				plane1->accelerate();
				break;
			case GLUT_KEY_DOWN:
				plane1->slowdown();
				break;
			case GLUT_KEY_LEFT:
				plane1->rotate_left();
				break;
			case GLUT_KEY_RIGHT:
				plane1->rotate_right();
				break;
			case GLUT_KEY_END:
				if(!plane1->reloading()) bullets.insert(bullets.end(), plane1->fire());
			}

		}
	}
}