#include "GameWindow.h"


GameWindow::GameWindow(int pWIDTH, int pHEIGHT, int pFRAMERATE) : Window(pWIDTH, pHEIGHT, pFRAMERATE)

//Car::Car(string fileprename, Arena* pArena, int pPositionX, int pPositionY, int pWIDTH, int pFRAMERATE)
{		
		set_caption("Gosu Tutorial mit Git");
		hintergrund = new Gosu::Image("Hintergrund.png");
		//Gosu::Image hintergrund("Hintergrund.png");
		WIDTH = pWIDTH;
		HEIGHT = pHEIGHT;
		FRAMERATE = pFRAMERATE;

		arena = new Arena(HEIGHT, WIDTH);

		redcar = new Car("Car_red", arena, (int)(WIDTH / 3), (int)(HEIGHT - 150), WIDTH, FRAMERATE);
		bluecar = new Car("Car_blue", arena, (int)(WIDTH / 2), (int)(HEIGHT - 150), WIDTH, FRAMERATE);
}

void GameWindow::draw()
{
	hintergrund->draw(0, 0, 0, double(WIDTH) / double(hintergrund->width()), double(HEIGHT) / double(hintergrund->height()));
	
	arena->draw();
	//Gosu::Graphics::draw_rect(200, 200, (WIDTH / 2), (HEIGHT / 2), Gosu::Color::RED, 1);
	//Gosu::Image bild("Car_red.png");
	//bild.draw(200, 200, 1, 1, 1);
	redcar->draw();
	bluecar->draw();
}


void GameWindow::update()
{
	redcar->move();
	redcar->accelerate(Gosu::Button::KB_LEFT, Gosu::Button::KB_RIGHT);

	bluecar->move();
	bluecar->accelerate(Gosu::Button::KB_A, Gosu::Button::KB_D);
}