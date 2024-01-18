#include "Block.h"
#include "..\include\Block.h"

Block::Block(string imgDirectory)
{
	if (!texture.loadFromFile(imgDirectory))
	{
		cout << "Error" << endl;
	}
	sprite.setTexture(texture);
}

void Block::drawBlock(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Block::setPosition(int posX, int posY)
{
	sprite.setPosition(posX, posY);
}

void Block::checkColl(Bullet bullet, Enemy enemy)
{
	if (bullet.getRight() > sprite.getPosition().x &&
		bullet.getTop() < sprite.getPosition().y + sprite.getGlobalBounds().height
		&& bullet.getBottom() > sprite.getPosition().y && bullet.getLeft() < sprite.getPosition().x + sprite.getGlobalBounds().width)
	{
		bCollision = true;
		iBlockHeatlh--;

		if (iBlockHeatlh == 0)
		{
			sprite.setPosition(500, -4278);

		}

	}
	else if (enemy.getPosX() > sprite.getPosition().x &&
		enemy.getPosY() > sprite.getPosition().y)
	{
		iBlockHeatlh--;
		if (iBlockHeatlh == 0)
		{
			sprite.setPosition(500, -4278);
		}
	}
}

void Block::acquireFile()
{
	sprite.setTexture(texture);
	if (iBlockHeatlh ==2)
	{
		texture2.loadFromFile(".\\assets\\images\\OkBlock.png");
		sprite.setTexture(texture2);
	}
	else if (iBlockHeatlh <= 1)
		{
			texture3.loadFromFile(".\\assets\\images\\WeakBlock.png");
			sprite.setTexture(texture3);
		}
}

void Block::setScale(int iScaleFactor)
{
	sprite.setScale(sprite.getScale().x * 3, sprite.getScale().y * 3);
}
