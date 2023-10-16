#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <cmath>
#define PI 3.14159265
using namespace std;

const int WIDTH = Gosu::screen_width();
const int HEIGHT = Gosu::screen_height();

//infos: unter Rahmen: 105px;
struct Arena {
	double stretchFactor = (double)HEIGHT / 2 / pow((double)WIDTH / 4,2);
	int XInSegment(int X) {//0 for left, 1 for middle, 2 for right
		if (X < WIDTH / 4) { return 0; }
		else if (X > WIDTH * 3 / 4) { return 2; }
		else { return 1; }
	}
	int YOfArenaCurve(double X) {
		switch (XInSegment(X)) {
		case 0://			105 nach oben       skalierung Parabel							verschiebung Parabel
			return HEIGHT - (105 + stretchFactor * pow(X - (double)WIDTH / 4, 2));
		case 1:
			return HEIGHT - 105;
		case 2:
			return HEIGHT - (105 + stretchFactor * pow(X - (double)WIDTH * 3 / 4, 2));
		}
	}
	int SlopeOfArenaCurve(double X) {
		switch (XInSegment(X)) {
		case 0:
			return stretchFactor * 2 * (X - (double)WIDTH / 4);
		case 1:
			return 0;
		case 2:
			return stretchFactor * 2 * (X - (double)WIDTH * 3 / 4);
		}
	}
	int RotationOfArenaCurve(double X) {
		return atan(this->SlopeOfArenaCurve(X)) * 180 / PI;
	}
	void draw() {
		for (int x = 0; x < WIDTH; x++) {
			Gosu::Graphics::draw_rect(x, this->YOfArenaCurve(x), 5, 5, Gosu::Color::BLACK, 0);
		}
		/*for (int x = 0; x < WIDTH; x++) {
			for (int y = this->YOfArenaCurve(x); y < HEIGHT; y++) {
				Gosu::Graphics::draw_rect(x, y, 1, 1, Gosu::Color::BLACK, 0);
			}
		}*/
	}
};


class Car {
	double velocityX = 0;
	double velocityY = 0;
	double velocity = 0; //gesamt Betrag
	double gravityY = 0;
	int positionX = 0;
	int positionY = 0;
	int rotation = 0; //in degree
	bool mirrored = false;
	const Gosu::Image image;
	const Gosu::Image image_mirrored;
	const int ACCELERATION = 100;
	const int GRAVITY = 150;
	Arena arena;

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
	bool carOverCurve() {
		if (this->getEndY() < arena.YOfArenaCurve(this->getCenterX())) {
			return 1;
		}
		else { 
			return 0; 
		}
	}
	void gravity(){
		if (this->carOverCurve()) {
			this->gravityY += GRAVITY / 60;
		}
		else{
			this->gravityY = 0;
		}
	}
	void rotatedVelocity() {
		this->rotation = arena.RotationOfArenaCurve(this->getCenterX());
		this->velocityX = this->velocity * cos(this->rotation);
		this->velocityY = this->velocity * sin(this->rotation);
	}
	void movement() {
		static double counterX = 0;
		static double counterY = 0;
		counterX += this->velocityX / 60;
		counterY += (gravityY + velocityY) / 60;
		if ((int)counterX) {
			this->positionX += (int)counterX;
			counterX -= (int)counterX;
		}
		if ((int)counterY) {
			this->positionY += (int)counterY;
			counterY -= (int)counterY;
		}
	}
	void isMirrored() {
		if (this->velocityX < 0) { //wenn Auto nach rechts zeigt, aber v nach links geht, also negativ ist
			this->mirrored = true;
		}
		else if (this->velocityX > 0) {
			this->mirrored = false;
		}
	}
	

public:
	Car(string fileprename, Arena arena, int positionX, int positionY) :
		image(fileprename + ".png"), image_mirrored(fileprename + "_mirrored.png"),
		arena(arena)
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

	void move() {
		this->rotatedVelocity();
		this->gravity();
		this->isMirrored();
		this->movement();
	}
	void accelerate(Gosu::Button btnLeft, Gosu::Button btnRight) {
		if (Gosu::Input::down(btnLeft)) {
			this->velocity += ACCELERATION / 60 * -1;
		}
		if (Gosu::Input::down(btnRight)) {
			this->velocity += ACCELERATION / 60;
		}
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
	Arena arena;

	GameWindow(): 
		Window (WIDTH, HEIGHT),
		Hintergrund ("Hintergrund.png"),
		Redcar("Car_red", arena, WIDTH/1.5, HEIGHT - 150),
		Bluecar("Car_blue", arena, WIDTH/2.5, HEIGHT - 150)
	{
		set_caption("Gosu Tutorial mit Git");
	}

	
	void draw() override
	{
		Hintergrund.draw(0, 0, -100, double(WIDTH) / double(Hintergrund.width()), double(HEIGHT) / double(Hintergrund.height()));
		Redcar.draw();
		Bluecar.draw();
		arena.draw();
	}

	
	void update() override
	{
		Redcar.move();
		Redcar.accelerate(Gosu::Button::KB_LEFT, Gosu::Button::KB_RIGHT);
		
		Bluecar.move();
		Bluecar.accelerate(Gosu::Button::KB_A, Gosu::Button::KB_D);
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