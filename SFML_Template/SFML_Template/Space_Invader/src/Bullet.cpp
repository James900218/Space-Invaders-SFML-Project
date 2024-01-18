#include "Bullet.h"

Bullet::Bullet(string imgDirectory)
{
	if (!texture.loadFromFile(imgDirectory))
	{
		cout << "Error" << endl;
	}
	bullet.setTexture(texture);
}

void Bullet::fire(int speed)
{
	bullet.move(0, speed);
}

void Bullet::draw(sf::RenderWindow& window)
{

	window.draw(bullet);
}

void Bullet::setPosition(sf::Vector2f newPos)
{
	bullet.setPosition(newPos);
}

void Bullet::getGlobalBounds()
{
	bullet.getGlobalBounds();
}

int Bullet::getRight()
{
	return bullet.getPosition().x + bullet.getGlobalBounds().width;
}

int Bullet::getLeft()
{
	return bullet.getPosition().x;
}

int Bullet::getTop()
{
	return bullet.getPosition().y;
}

int Bullet::getBottom()
{
	return bullet.getPosition().y + bullet.getGlobalBounds().height;
}






