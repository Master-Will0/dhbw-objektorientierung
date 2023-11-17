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
	int RotationOfArenaCurve(double X); //Rückgabe der Steigung der Parabel in Grad
	void draw();

private:
	double WIDTH;
	double HEIGHT;
	double stretchFactor; //Streckfaktor a der Arena-Parabel
};


//extern Arena arena;
