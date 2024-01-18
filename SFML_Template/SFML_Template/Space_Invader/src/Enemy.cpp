#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(string imgDirectory)
{
	if (!texture.loadFromFile(imgDirectory))
	{
		cout << "Error" << endl;
	}
	sprite.setTexture(texture);

	imgDirectory = imgDirector;
}

void Enemy::drawEnemy(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Enemy::setPosition(int posX, int posY)
{
	sprite.setPosition(posX, posY);
}

int Enemy::getPosX()
{
	return sprite.getPosition().x;
}

int Enemy::getPosY()
{
	return sprite.getPosition().y;
}

void Enemy::checkColl(Bullet bullet)
{
	if (bullet.getRight() > sprite.getPosition().x &&
		bullet.getTop() < sprite.getPosition().y + sprite.getGlobalBounds().height
		&& bullet.getBottom() > sprite.getPosition().y && bullet.getLeft() < sprite.getPosition().x + sprite.getGlobalBounds().width)
	{

		sprite.setPosition(500, -4278);
		bCollision = true;

	}
}

void Enemy::acquireFile()
{
	sprite.setTexture(texture);
}

void Enemy::moveEnemy(char cDirection, float fMoveX)
{
	if (cDirection == 'L')
	{
		sprite.move(-fMoveX, 0.f);

	}
	else if (cDirection == 'R')
	{
		sprite.move(fMoveX, 0.f);

	}
	else if (cDirection == 'D')
	{
		sprite.move(0.f, 15.f);
	}



}





