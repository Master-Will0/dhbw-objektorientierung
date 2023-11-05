#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <cmath>

#include "GameWindow.h"

#define PI 3.14159265
using namespace std;

const int WIDTH = Gosu::screen_width();
const int HEIGHT = Gosu::screen_height();
const int FRAMERATE = 60;




//infos: unter Rahmen: 105px; sometimes you need to add a couple of spaces at the accelerate function to work properly. idc why




// C++ Hauptprogramm
int main()
{
	cout << "Window-sizing: " << WIDTH << " x " << HEIGHT << endl;
	GameWindow window(WIDTH, HEIGHT, FRAMERATE);

	window.show();
	return 1;
}




// Rotation is not perfect and gravity when on the parabola needs to be added