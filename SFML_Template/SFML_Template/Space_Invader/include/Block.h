#pragma once
#include<iostream>
using namespace std;
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>

#include"Bullet.h"
#include"Enemy.h"

class Block
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture texture2;
	sf::Texture texture3;

public:

	int iBlockHeatlh = 3;
	bool bCollision = false;

	Block(string imgDirectory); //constructor

	void drawBlock(sf::RenderWindow& window); //draw to sfml window

	void setPosition(int posX, int posY); // set spawn position

	void checkColl(Bullet bullet, Enemy enemy); // check bullet co-ordinates intersect self

	void acquireFile(); // re-sets the texture if block is damaged

	void setScale(int iScaleFactor); //change block scale

	

};

