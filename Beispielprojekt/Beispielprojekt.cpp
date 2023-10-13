#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <cmath>
using namespace std;

const int WIDTH = Gosu::screen_width();
const int HEIGHT = Gosu::screen_height();

//infos: unter Rahmen: 105px;


int YofCurve(double X) {
	switch (carInSegment(X)) {
	case 0:// 105 nach oben       skalierung Parabel							verschiebung Parabel
		return 105 +	((double)HEIGHT / 2 * pow((double)WIDTH / 4, 2))	* pow(X - (double)WIDTH / 4, 2);
	case 1:
		return 105;
	case 2:
		return 105 +	((double)HEIGHT / 2 * pow((double)WIDTH / 4, 2))	* pow(X - (double)WIDTH * 3 / 4, 2);
	}
}
int carInSegment(int X) {//0 for left, 1 for middle, 2 for right
	if (X < WIDTH / 4) { return 0; }
	else if (X > WIDTH * 3 / 4) { return 2; }
	else { return 1; }
}

class Car {
	double velocityX = 0;
	double velocityY = 0;
	int positionX = 0;
	int positionY = 0;
	int rotation = 0; //in degree
	bool mirrored = false;
	const Gosu::Image image;
	const Gosu::Image image_mirrored;
	const int ACCELERATION = 100;
	const int GRAVITY = 100;

	bool carOverCurve() {
		if (this->getEndX() > YofCurve(this->getEndX())) {
			return 1;
		}
		else return 0;
	}

	int getCenterX() {
		return this->positionX + this->image.width() / 2;
	}
	int getCenterY() {
		return this->positionY + this->image.height() / 2;
	}
	int getEndX() {
		return this->positionX + this->image.width();
	}
	int getEndY() {
		return this->positionY + this->image.height();
	}
public:
	Car(string fileprename, int positionX, int positionY) :
		image(fileprename + ".png"), image_mirrored(fileprename + "_mirrored.png")
	{ 
		this->positionX = positionX;
		this->positionY = positionY - image.height() - 105;
	};


	void draw() {
		if (mirrored) {
			cout << "mirrored!!!" << endl;
			image_mirrored.draw(this->positionX, this->positionY);
			image.draw(0,0,0,0,0);
		} else{
			cout << "not" << endl;
			image.draw(this->positionX, this->positionY);
			image_mirrored.draw(0, 0, 0, 0, 0);
		}
	}

	double counterX = 0;
	double counterY = 0;
	void move() {
		counterX += this->velocityX / 60;
		counterY += this->velocityY / 60;
		if ((int)counterX) {
			this->positionX += (int)counterX;
			counterX -= (int)counterX;
		}
		if ((int)counterY) {
			this->positionY += (int)counterY;
			counterY += (int)counterY;
		}
		if (this->velocityX < 0 ) { //wenn Auto nach rechts zeigt, aber v nach links geht, also negativ ist
			this->mirrored = true;
		}
		else {
			this->mirrored = false;
		}
	}
	void accelerate() {
		this->velocityX += ACCELERATION * cos(this->rotation) / 60;
		this->velocityY -= ACCELERATION * sin(this->rotation) /60;
		// if(Z over curve){this->velocityY += GRAVITY/60;}
		cout << "acc call" << this->velocityX << endl;
	}
	bool getMirrored() {
		return this->mirrored;
	}
	void setRotation(int rotation) {
		this->rotation = rotation;
	}
	int getRotation() {
		return this->rotation;
	}
};
class GameWindow : public Gosu::Window
{
public:

	Gosu::Image Hintergrund;
	Car Redcar;
	Car Bluecar;

	GameWindow(): 
		Window (WIDTH, HEIGHT),
		Hintergrund ("Hintergrund.png"),
		Redcar("Car_red", WIDTH/1.75, HEIGHT),
		Bluecar("Car_blue", WIDTH/2.25, HEIGHT)
	{
		set_caption("Gosu Tutorial mit Git");
	}

	
	void draw() override
	{
		Hintergrund.draw(0, 0, -100, double(WIDTH) / double(Hintergrund.width()), double(HEIGHT) / double(Hintergrund.height()));
		Redcar.draw();
		Bluecar.draw();
		
		/*
		graphics().draw_line(
			0, Gosu::available_height(), Gosu::Color::RED,
			200, 100, Gosu::Color::GREEN,
			0.0
		);*/
	}

	
	void update() override
	{
		Redcar.move();
		if (Gosu::Input::down(Gosu::Button::KB_LEFT)) {
			Redcar.accelerate(-100);
		}
		if (Gosu::Input::down(Gosu::Button::KB_RIGHT)) {
			Redcar.accelerate(100);
		}

		Bluecar.move();
		if (Gosu::Input::down(Gosu::Button::KB_A)) {
			Bluecar.accelerate(-100);
		}
		if (Gosu::Input::down(Gosu::Button::KB_D)) {
			Bluecar.accelerate(100);
		}
	}
};

// C++ Hauptprogramm
int main()
{
	cout << "Window-sizing: " << WIDTH << " x " << HEIGHT << endl;
	GameWindow window;
	window.show();
	return 1;
}