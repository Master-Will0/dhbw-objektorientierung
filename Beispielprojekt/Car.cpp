#include "Car.h"

Car::Car(string fileprename, Arena* pArena, int pPositionX, int pPositionY, int pWIDTH, int pFRAMERATE)
{
	arena = pArena;
	WIDTH = pWIDTH;
	FRAMERATE = pFRAMERATE;
	image = new Gosu::Image(fileprename + ".png");
	image_mirrored = new Gosu::Image(fileprename + "_mirrored.png");

	positionX = pPositionX;// -image.width() / 2;		Festlegung X ud Y für Bild vom Auto
	positionY = pPositionY - image->height();

	if (positionX > (WIDTH / 2))	//spiegeln des Bildes ab rechter Hälfte des Bildschirms?
	{
		mirrored = true;	
	}
}

int Car::getCenterX() //Rückgabe Mittelpunkt des Bildes in X-Richtung
{
	return this->positionX + image->width() / 2;
}
int Car::getCenterY() //Rückgabe Mittelpunkt des Bildes in Y-Richtung
{
	return this->positionY + image->height() / 2;
}
int Car::getEndX() //Rückgabe Eckpunkt des Bildes in X-Richtung
{
	return this->positionX + image->width();
}
int Car::getEndY() //Rückgabe Eckpunkt des Bildes in Y-Richtung
{
	return this->positionY + image->height();
}

void Car::draw() 
{
	image->draw(200,200,1);
	
	
	if (mirrored) //wenn das gespiegelte Bild auftaucht
	{
		image_mirrored->draw_rot(this->positionX, this->positionY - image->height() * (1 + sin(-1 * rotation * PI / 180)), 0, -1 * rotation, 0, 0);
		////////////////////////////////
		Gosu::Graphics::draw_rect(this->positionX, this->positionY - image->height() * (1 + sin(-1 * rotation * PI / 180)), image->width(), image->height(), Gosu::Color::BLACK, 0); //schwarzer Block in Bildgröße
		Gosu::Graphics::draw_rect(this->positionX, this->positionY - image->height(), image->width(), 5, Gosu::Color::GREEN, 0); //grüner Balken über schwarzem Block
		image->draw(0, 0, 0, 0, 0); //?
	}
	else 
	{
		image->draw_rot(this->positionX, this->positionY - image->height() * (1 + sin(-1 * rotation * PI / 180)), 0, -1 * rotation, 0, 0);  // Rotation Bild nach Parabel
		
		Gosu::Graphics::draw_rect(this->positionX, this->positionY - image->height() * (1 + sin(-1 * rotation * PI / 180)), image->width(), image->height(), Gosu::Color::BLACK, 0);
		Gosu::Graphics::draw_rect(this->positionX, this->positionY - image->height(), image->width(), 5, Gosu::Color::GREEN, 0);
		image_mirrored->draw(0, 0, 0, 0, 0);
	}
}

void Car::move() 
{
	IsCarOverCurve = carOverCurve();
	this->gravity();

	if (!IsCarOverCurve) //Auto unter der Kurve
	{
		this->directedVelocity(); //gerichtete Gechwindigkeit
	}
	else 
	{
		this->freeVelocity(); //freie Geschwindigkeit
	}
	this->isMirrored();
	this->movement();
}

void Car::accelerate(Gosu::Button btnLeft, Gosu::Button btnRight) 
{
	if (Gosu::Input::down(btnLeft)) //linke Richtung
	{
		if (!carOverCurve()) //nur wenn das Auto unter der Kurve ist?
		{
			this->velocity -= (double)ACCELERATION / FRAMERATE; //bremsen?
		}
	}
	if (Gosu::Input::down(btnRight)) //rechte Richtung
	{
		if (!carOverCurve()) 
		{
			this->velocity += (double)ACCELERATION / FRAMERATE; //beschleunigen?
		}
	}
}

bool Car::getMirrored() //Rückgabe, ob das Bild gespiegelt ist
{
	return this->mirrored;
}
void Car::setRotation(int rotation) //Rotation festlegen
{
	
	this->rotation = rotation;
}
int Car::getRotation() //Rückgabe der Rotation vom Bild
{
	return this->rotation;
}

bool Car::carOverCurve() // caic for top middle of car
{ 
	if (this->positionY < arena->YOfArenaCurve(this->getCenterX())) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

void Car::gravity() //wie ist die Schwerkraft gemeint? also welchen Einfluss hat sie
{
	this->gravityY += (double)GRAVITY / FRAMERATE;
}
void Car::directedVelocity()
{
	this->rotation = arena->RotationOfArenaCurve(this->getCenterX());// !!!!!
	positionY = arena->YOfArenaCurve(getCenterX());

	velocity -= gravityY * sin(rotation * PI / 180);

	velocity *= FRICTION;

	velocityX = velocity * cos(rotation * PI / 180);
	velocityY = -1 * velocity * sin(rotation * PI / 180);
}
void Car::freeVelocity()
{
	velocityY += gravityY;
}
void Car::movement()
{
	static double counterX = 0;
	static double counterY = 0;
	counterX += velocityX / FRAMERATE;
	counterY += velocityY / FRAMERATE;
	
	if ((int)counterX) 
	{
		this->positionX += (int)counterX;
		counterX -= (int)counterX;
	}
	
	if ((int)counterY) 
	{
		this->positionY += (int)counterY;
		counterY -= (int)counterY;
	}
}
void Car::isMirrored() //herausfinden, ob Bild gespiegelt ist
{
	if (this->velocityX < 0) //wenn Auto nach rechts zeigt, aber v nach links geht, also negativ ist
	{ 
		this->mirrored = true;
	}
	else if (this->velocityX > 0) 
	{
		this->mirrored = false;
	}//kein weiteres else wieso dann if else?
}