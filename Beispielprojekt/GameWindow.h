#pragma once

#include<Gosu/Window.hpp>
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include "Arena.h"
#include "Car.h"

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image* hintergrund;

	GameWindow(int pWIDTH, int pHEIGHT, int pFRAMERATE);

	void draw() override;
	void update() override;

private:
	int WIDTH;
	int HEIGHT;
	int FRAMERATE;

	Arena* arena;
	Car* redcar;
	Car* bluecar;
};

