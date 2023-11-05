#pragma once
#define PI 3.14159265
#include <math.h>
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>


class Arena
{
public:
	//double stretchFactor;

	Arena(double pHEIGHT, double pWIDTH); // Konstruktor, bekommt globale Variablen

	int XInSegment(int X); //Rückgabe des Standpunkts in der Breite vom Bildschirm 
	int YOfArenaCurve(double X); //Erstellung der Parabel je nach X-Position und Rückgabe des Y-Wertes
	double SlopeOfArenaCurve(double X); //Rückgabe der Steigung der Parabel
	int RotationOfArenaCurve(double X); //Warum Rotation, wenn ich eine Steigung habe?
	void draw();

private:
	double WIDTH;
	double HEIGHT;
};
