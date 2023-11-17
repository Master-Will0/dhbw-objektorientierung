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
	
	if (mirrored) //wenn das gespiegelte Bild auftaucht
	{
		image_mirrored->draw_rot(this->positionX + 20, this->positionY - image->height() * (1 + sin(-1 * rotation * PI / 180) * cos(rotation * PI / 180)), 0, -1 * rotation, 0, 0);
		////////////////////////////////
		/*Gosu::Graphics::draw_rect(this->positionX, this->positionY - image->height() * (1 + sin(-1 * rotation * PI / 180)), image->width(), image->height(), Gosu::Color::BLACK, 0); //schwarzer Block in Bildgröße
		Gosu::Graphics::draw_rect(this->positionX, this->positionY - image->height(), image->width(), 5, Gosu::Color::GREEN, 0); //grüner Balken über schwarzem Block
		image->draw(0, 0, 0, 0, 0); //?*/
	}
	else 
	{
		image->draw_rot(this->positionX + 20, this->positionY - image->height() * (1 + sin(-1 * rotation * PI / 180) * cos(rotation * PI / 180)), 0, -1 * rotation, 0, 0);  // Rotation Bild nach Parabel
		
		/*Gosu::Graphics::draw_rect(this->positionX, this->positionY - image->height() * (1 + sin(-1 * rotation * PI / 180)), image->width(), image->height(), Gosu::Color::BLACK, 0);
		Gosu::Graphics::draw_rect(this->positionX, this->positionY - image->height(), image->width(), 5, Gosu::Color::GREEN, 0);
		image_mirrored->draw(0, 0, 0, 0, 0);*/
	}
}

void Car::move() 
{

	if (!carOverCurve()) //Auto auf der Kurve
	{
		this->rotation = arena->RotationOfArenaCurve(this->getCenterX());// rotation am Punkt der Autos ablesen
		this->positionY = arena->YOfArenaCurve(this->getCenterX());//falls Auto unter der Kurve sein sollte => auf die Kurve setzen

		velocity -= (double)GRAVITY / FRAMERATE * sin(rotation * PI / 180);//Hangabtriebskraft
		velocity *= FRICTION;//Reibung

		this->directedVelocity(); //Berechnung der gerichteten Gechwindigkeit auf der Bahn
	}
	else 
	{
		this->freefallVelocity(); // Berechnung der Geschwindigkeit im Freien Fall
	}
	this->mirror();//Bild je nach v-Richtung spiegeln
	this->movement();//umwandeln der Geschwindigkeits Werte in Bewegung
}

void Car::jump(Gosu::Button btnUP) {
	if (Gosu::Input::down(btnUP)) 
	{
		this->positionY -= 30 * cos(this->rotation * PI /180); //'Sprung nach oben im rechten Winkel zur Fahrbahn
		this->positionX -= 30 * sin(this->rotation * PI / 180);
	}
}

void Car::accelerate(Gosu::Button btnLeft, Gosu::Button btnRight) 
{
	if (Gosu::Input::down(btnLeft)) //linke Richtung
	{
		if (!carOverCurve()) //nur wenn das Auto unter der Kurve ist?
		{
			this->velocity -= (double)ACCELERATION / FRAMERATE; //Beschleunigung nach links
		}
	}
	if (Gosu::Input::down(btnRight)) //rechte Richtung
	{
		if (!carOverCurve()) 
		{
			this->velocity += (double)ACCELERATION / FRAMERATE; //Beschleunigung nach links
		}
	}
}

bool Car::carOverCurve() // Rückgabe, ob das Auto über der Kurve ist
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

void Car::directedVelocity()
{
	velocityX = velocity * cos(rotation * PI / 180);
	velocityY = -1 * velocity * sin(rotation * PI / 180);
}

void Car::freefallVelocity()
{
	velocityY += (double)GRAVITY / FRAMERATE;
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

void Car::mirror() //Bild je nach v-Richtung spiegeln
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