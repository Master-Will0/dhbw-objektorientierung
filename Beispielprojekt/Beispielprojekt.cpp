#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <cmath>
using namespace std;

const int WIDTH = Gosu::screen_width();
const int HEIGHT = Gosu::screen_height();

//infos: unter Rahmen: 105px;

int XInSegment(int X) {//0 for left, 1 for middle, 2 for right
	if (X < WIDTH / 4) { return 0; }
	else if (X > WIDTH * 3 / 4) { return 2; }
	else { return 1; }
}
int YOfCurve(double X) {
	switch (XInSegment(X)) {
	case 0://			105 nach oben       skalierung Parabel							verschiebung Parabel
		return HEIGHT - (105 +	((double)HEIGHT / 2 / pow((double)WIDTH / 4, 2))	* pow(X - (double)WIDTH / 4, 2));
	case 1:
		return HEIGHT - 105;
	case 2:
		return HEIGHT - (105 +	((double)HEIGHT / 2 / pow((double)WIDTH / 4, 2))	* pow(X - (double)WIDTH * 3 / 4, 2));
	}
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
	const int GRAVITY = 150;

	bool carOverCurve() {
		if (this->getEndY() < YOfCurve(this->getEndY())) {
			return 1;
		}
		else { return 0; }
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
		this->positionX = positionX - image.width() / 2;
		this->positionY = positionY - image.height();
		if (this->positionX > WIDTH / 2) {
			this->mirrored = true;
		}
	};


	void draw() {
		if (mirrored) {
			image_mirrored.draw(this->positionX, this->positionY);
			image.draw(0,0,0,0,0);
		} else{
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
			counterY -= (int)counterY;
		}
		if (this->velocityX < 0 ) { //wenn Auto nach rechts zeigt, aber v nach links geht, also negativ ist
			this->mirrored = true;
		}
		else if (this->velocityX > 0) {
			this->mirrored = false;
		}
		if (this->carOverCurve()) {
			this->velocityY += GRAVITY / 60;
		}
		if (!this->carOverCurve() && this->velocityY > 0) {
			this->velocityY = 0;
		}
	}
	void accelerate(int directionFactor = 1) {
		this->velocityX += ACCELERATION * cos(this->rotation) / 60 * directionFactor;
		this->velocityY -= ACCELERATION * sin(this->rotation) /60 * directionFactor;
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
		Redcar("Car_red", WIDTH/1.5, HEIGHT - 150),
		Bluecar("Car_blue", WIDTH/2.5, HEIGHT - 150)
	{
		set_caption("Gosu Tutorial mit Git");
	}

	
	void draw() override
	{
		Hintergrund.draw(0, 0, -100, double(WIDTH) / double(Hintergrund.width()), double(HEIGHT) / double(Hintergrund.height()));
		Redcar.draw();
		Bluecar.draw();
		for (int x = 0; x < WIDTH; x++) {
			Gosu::Graphics::draw_rect(x, YOfCurve(x), 5, 5, Gosu::Color::BLACK, 0);
		}
	}

	
	void update() override
	{
		Redcar.move();
		if (Gosu::Input::down(Gosu::Button::KB_RIGHT)) {
			Redcar.accelerate();
		}
		if (Gosu::Input::down(Gosu::Button::KB_LEFT)) {
			Redcar.accelerate(-1);
		}

		Bluecar.move();
		if (Gosu::Input::down(Gosu::Button::KB_D)) {
			Bluecar.accelerate();
		}
		if (Gosu::Input::down(Gosu::Button::KB_A)) {
			Bluecar.accelerate(-1);
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