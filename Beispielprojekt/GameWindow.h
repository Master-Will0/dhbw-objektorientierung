#pragma once

#include<Gosu/Window.hpp>
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include "Arena.h"
#include "Car.h"

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image Hintergrund;

	GameWindow(int pWIDTH, int pHEIGHT, int pFRAMERATE);

	void draw() override;
	void update() override;
	Arena arena;

private:
	int WIDTH;
	int HEIGHT;
	int FRAMERATE;


	Car redcar;
	Car bluecar;
};

