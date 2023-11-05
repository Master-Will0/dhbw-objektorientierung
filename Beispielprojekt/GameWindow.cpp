#include "GameWindow.h"


GameWindow::GameWindow(int pWIDTH, int pHEIGHT, int pFRAMERATE) : Window(pWIDTH, pHEIGHT, pFRAMERATE)
{		
		set_caption("Gosu Tutorial mit Git");
		Gosu::Image Hintergrund("Hintergrund.png");
		WIDTH = pWIDTH;
		HEIGHT = pHEIGHT;
		FRAMERATE = pFRAMERATE;

		Arena arena(HEIGHT, WIDTH);

		Car redcar("auto_rot", arena, WIDTH / 3, HEIGHT - 150, WIDTH, FRAMERATE);
		Car bluecar("auto_blau", arena, WIDTH / 2, HEIGHT - 150, WIDTH, FRAMERATE);
}

void GameWindow::draw()
{
	Hintergrund.draw(0, 0, -100, double(WIDTH) / double(Hintergrund.width()), double(HEIGHT) / double(Hintergrund.height()));
	redcar.draw();
	bluecar.draw();
	arena.draw();
}


void GameWindow::update()
{
	redcar.move();
	redcar.accelerate(Gosu::Button::KB_LEFT, Gosu::Button::KB_RIGHT);

	bluecar.move();
	bluecar.accelerate(Gosu::Button::KB_A, Gosu::Button::KB_D);
}