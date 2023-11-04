#pragma once

#include <stdio.h>
#include <string.h>
#include<string>
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <cmath>
#include "Arena.h"

#define PI 3.14159265

using namespace std;

class Car {

public:
	Car(string fileprename, Arena arena, int positionX, int positionY, double pWIDTH, int pFRAMERATE); // Kontruktor mit Festlegung des Pixels vom Bild (unten links) und Spiegelung des Bildes  

	int getCenterX();	// R�ckgabe des Mittelpunkt des Objekts in X - Richtung
	int getCenterY();	// R�ckgabe des Mittelpunkt des Objekts in Y - Richtung
	int getEndX(); //R�ckgabe Eckpunkt des Bildes in X-Richtung
	int getEndY(); //R�ckgabe Eckpunkt des Bildes in Y-Richtung

	void draw();
	void move();
	
	void accelerate(Gosu::Button btnLeft, Gosu::Button btnRight); //bremsen und beschleunigen, je nach Tastendruck

	bool getMirrored(); //R�ckgabe, ob das Bild gespiegelt ist

	void setRotation(int rotation); //Setzen Rotation des Bildes
	int getRotation(); //R�ckgabe Rotation des Bildes
	
	bool carOverCurve(); //Wof�r steht caic?; R�ckgabe, ob das Auto �ber der Curve ist
	void gravity();

	void directedVelocity();
	void freeVelocity();

	void movement();
	void isMirrored(); //Ver�ndern der Variable mirrored, je nach dem ob das Bild gespiegelt ist


private:

	double velocityX = 0;
	double velocityY = 0;
	double velocity = 0; //gesamt Betrag der Geschwindigkeit
	double gravityY = 0;
	int positionX = 0;
	int positionY = 0;
	int rotation = 0; //in degree
	bool mirrored = false;
	bool IsCarOverCurve = true;
	const Gosu::Image image;
	const Gosu::Image image_mirrored;
	const int ACCELERATION = 1000;  //f�rs Abbremsen und Beschleunigen
	const int GRAVITY = 1;
	const double FRICTION = 0.995;

	double WIDTH;
	int FRAMERATE;
	Arena arena;

};

	
	
	

	

	


