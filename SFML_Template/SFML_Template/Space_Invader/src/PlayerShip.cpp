#include "PlayerShip.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

PlayerShip::PlayerShip()
{

}

PlayerShip::PlayerShip(string imgDirectory)
{
	if (!pTexture.loadFromFile(imgDirectory))
	{
		cout << "Error" << endl;
	}
	pSprite.setTexture(pTexture);
}

void PlayerShip::drawPlayer(sf::RenderWindow& window)
{
	window.draw(pSprite);

}

void PlayerShip::movePlayer(char cDirection, float fMovementSpeed)
{

	if (cDirection == 'a')
	{
		pSprite.move(-fMovementSpeed, 0.f);
	}
	else if(cDirection == 'd')
	{

		pSprite.move(fMovementSpeed, 0.f);
	}
	
}

void PlayerShip::setPosition(float fXPos, float fYPos)
{
	pSprite.setPosition(fXPos, fYPos); //500, 750

}

int PlayerShip::getX()
{
	return pSprite.getPosition().x;
}

int PlayerShip::getY()
{
	return pSprite.getPosition().y;
}

void PlayerShip::acquireFile()
{
	pSprite.setTexture(pTexture);
}

void PlayerShip::checkColl(class Bullet bullet)
{
	if (bullet.getRight() > pSprite.getPosition().x &&
		bullet.getTop() < pSprite.getPosition().y + pSprite.getGlobalBounds().height
		&& bullet.getBottom() > pSprite.getPosition().y && bullet.getLeft() < pSprite.getPosition().x + pSprite.getGlobalBounds().width)
	{
		pSprite.setPosition(495,2000);
		cout << "Ship has been hit!" << endl;
	}
}






