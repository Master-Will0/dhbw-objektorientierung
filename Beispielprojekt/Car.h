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
	Car(string fileprename, Arena* pArena, int pPositionX, int pPositionY, int pWIDTH, int pFRAMERATE); // Kontruktor mit Festlegung des Pixels vom Bild (unten links) und Spiegelung des Bildes  

	void draw();
	void move();

	int getCenterX();	// Rückgabe des Mittelpunkt des Objekts in X - Richtung
	int getCenterY();	// Rückgabe des Mittelpunkt des Objekts in Y - Richtung
	int getEndX(); //Rückgabe Eckpunkt des Bildes in X-Richtung
	int getEndY(); //Rückgabe Eckpunkt des Bildes in Y-Richtung

	void jump(Gosu::Button);//sprung nach oben nach Tastendruck
	void accelerate(Gosu::Button btnLeft, Gosu::Button btnRight); //bremsen und beschleunigen, je nach Tastendruck

	
	bool carOverCurve(); //Rückgabe, ob das Auto über der Kurve ist


private:

	double velocityX = 0;
	double velocityY = 0;
	double velocity = 0; //gesamt Betrag der Geschwindigkeit
	int positionX = 0;
	int positionY = 0;
	int rotation = 0; //in degree
	bool mirrored = false;
	const Gosu::Image* image;
	const Gosu::Image* image_mirrored;
	const int ACCELERATION = 1000;  //fürs Abbremsen und Beschleunigen
	const int GRAVITY = 3000; //Gravitation
	const double FRICTION = 0.995;//Reibungsfaktor

	double WIDTH;
	int FRAMERATE;
	Arena *arena;

	void directedVelocity(); //Berechnung der gerichteten Gechwindigkeit auf der Bahn
	void freefallVelocity();// Berechnung der Geschwindigkeit im Freien Fall

	void movement();//umwandeln der Geschwindigkeits Werte in Bewegung
	void mirror(); //Verändern der Variable mirrored, je nach dem ob das Bild gespiegelt ist

};

	
	
	

	

	

