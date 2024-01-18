#pragma once

#include<iostream>
using namespace std;
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include"PlayerShip.h"

class Bullet
{
private:
	sf::Sprite bullet;
	sf::Texture texture;
	
public:

	Bullet(string imgDirectory); //constructor

	void fire(int speed); // move bullet

	void draw(sf::RenderWindow& window); // draw bullet to sfml window

	void setPosition(sf::Vector2f newPos); // set spawn position

	void getGlobalBounds();

	// get all sides of bullet sprite
	int getRight();
	int getLeft();
	int getTop();
	int getBottom();


};

