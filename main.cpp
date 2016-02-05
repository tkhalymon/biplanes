#include <GL/glut.h>
#include <iostream>
#include "utils.h"
#include "game.h"

Game *game;
bool Pause;

bool kb[256];
bool kb_special[256];

void display();
void timer(int);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void specialKeyboardUp(int key, int x, int y);

void glut_initialisation(int argc, char *argv[])
{
	glutInit(&argc, argv);
	int scrSizeX = glutGet(GLUT_SCREEN_WIDTH);
	int scrSizeY = glutGet(GLUT_SCREEN_HEIGHT);
	// std::cout << scrSizeY << " / " << scrSizeX << " = " << scrSizeY / (double)scrSizeX << "\n";
	glutInitWindowSize(scrSizeX, scrSizeY);
	glutCreateWindow("Biplanes version 1.3");
	glLoadIdentity();
	glOrtho(0, scrSizeX, 0, scrSizeY, - 1, 1);
	// gluPerspective(75, (double)scrSizeX / (double)scrSizeY, 1.0, 700);
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glutSetKeyRepeat(0);
	glutTimerFunc(50, timer, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialUpFunc(specialKeyboardUp);
	glMatrixMode(GL_MODELVIEW);
	glutSetCursor(GLUT_CURSOR_NONE);
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutFullScreen();
}


int main(int argc, char *argv[])
{
	glut_initialisation(argc, argv);
	game = new Game;
	glutMainLoop();
	delete game;
	return 0;
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH);
	glPushMatrix();
	if (!Pause)
	{	
		game->sendControls(kb, kb_special);
		game->advance();
	}
	game->redraw();
	glPopMatrix();
	glDisable(GL_DEPTH);
	glutSwapBuffers();
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

void keyboard (unsigned char key, int x, int y)
{
	kb[key] = true;
	if (key == 32) Pause = !Pause;
}

void keyboardUp(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);
	kb[key] = false;
}

void specialKeyboard(int key, int x, int y)
{
	kb_special[key] = true;
}

void specialKeyboardUp(int key, int x, int y)
{
	kb_special[key] = false;
}
