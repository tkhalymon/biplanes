#ifndef _GAME_H_
#define _GAME_H_
#include "utils.h"
#include "bullet.h"
#include "plane.h"

class KeyboardState;
class Game
{

public:
	Game();
	virtual ~Game();


	void redraw();
	void advance();
	void sendControls(bool[256], bool[256]);

	Plane* plane1;
	Plane* plane2;
	std::vector<Bullet> bullets;
	Explosions expl;
};

#endif