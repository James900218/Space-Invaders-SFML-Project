#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include"Bullet.h"

using namespace std;

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	
public:

	int iPointBonus = 0;

	sf::FloatRect enemyBoundsBox;
	string imgDirector;

	Enemy(); //default constructor

	Enemy(string imgDirectory);

	void drawEnemy(sf::RenderWindow& window); //draw enemy to sfml window

	void setPosition(int posX, int posY); //initisalise alien spawn point

	int getPosX();

	int getPosY();

	void checkColl(Bullet bullet); //check bullet co-ordinates intersect self

	bool bCollision = false; //true when collided

	void acquireFile(); // re-sets enemy texture when drawing from vector

	void moveEnemy(char cDirection, float fMoveX); 

};

