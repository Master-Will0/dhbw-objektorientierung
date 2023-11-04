#include "Arena.h"

//Arena::		

Arena::Arena(double pHEIGHT, double pWIDTH) {
	WIDTH = pWIDTH;
	HEIGHT = pHEIGHT;
}

int Arena::XInSegment(int X) //Rückgabe 0 für links, 1 für mitte, 2 für rechts zum Ermittlen des Standpunkts
{
	if (X < WIDTH / 4) { return 0; } //linker Bildschirm
	else if (X > WIDTH * 3 / 4) { return 2; } //rechter Bildschirm
	else { return 1; } //Mitte des Bildschirms
}

int Arena::YOfArenaCurve(double X) //Erstellung der Parabel je nach X-Position
{
	switch (XInSegment(X)) //105 Verschiebung nach oben, wegen der Plattform; strechtFactor als Skalierung der Parabel; Abzug der Bildschirmbreite für die Verschiebung der Parabel
	{
	case 0:
		return HEIGHT - (105 + stretchFactor * pow(X - (double)WIDTH / 4, 2)); //warum Verschiebung nach links?
	case 1:
		return HEIGHT - 105;
	case 2:
		return HEIGHT - (105 + stretchFactor * pow(X - (double)WIDTH * 3 / 4, 2));
	}
}

double Arena::SlopeOfArenaCurve(double X) 
{
	stretchFactor = (double)HEIGHT / 2 / pow((double)WIDTH / 4, 2); // idk why, same definition again; Wieso generell diese Berechnung?
	switch (XInSegment(X)) 
	{
	case 0:
		return stretchFactor * 2 * (X - (double)WIDTH / 4);
	case 1:
		return 0;
	case 2:
		return stretchFactor * 2 * (X - (double)WIDTH * 3 / 4);
	}
}

int Arena::RotationOfArenaCurve(double X) 
{
	return atan(this->SlopeOfArenaCurve(X)) * 180 / PI;
}

void Arena::draw() 
{
	for (int x = 0; x < WIDTH; x++) 
	{
		Gosu::Graphics::draw_rect(x, this->YOfArenaCurve(x), 5, 5, Gosu::Color::BLACK, 0);
	}
	/*for (int x = 0; x < WIDTH; x++) {
		for (int y = this->YOfArenaCurve(x); y < HEIGHT; y++) {
			Gosu::Graphics::draw_rect(x, y, 1, 1, Gosu::Color::BLACK, 0);
		}
	}*/
}

