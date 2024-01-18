#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include"Bullet.h"

using namespace std;

class PlayerShip 
{

public:
	sf::Texture pTexture;
	sf::Sprite pSprite;


	PlayerShip(); //default constructor

	PlayerShip(string imgDirectory);
	
	void drawPlayer(sf::RenderWindow& window); // draw player to sfml window

	void movePlayer(char cDirection, float fMovementSpeed); // input function for player movement

	void setPosition(float fXPos, float fYPos);  //initialise player spawn point

	int getX();

	int getY();

	void acquireFile(); // re-set the texture file when drawing from vector

	void checkColl(class Bullet bullet); //check alien-bullet co-ordinates intersects self
}; 

