#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

using namespace std;

bool loadTexture(sf::Texture& tex, sf::Sprite& sprite, string sFileName, sf::Vector2f& size)
{
	bool bSuccess;
	bSuccess = tex.loadFromFile(".\\assets\\textures\\" + sFileName);
	if (!bSuccess)
	{
		return false;
	}

	sprite.setScale(size.x / tex.getSize().x, size.y / tex.getSize().y);
	sprite.setOrigin(size.x / 2.f / sprite.getScale().x, size.y / 2.f / sprite.getScale().y);
	sprite.setTexture(tex);
	return true;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Drawing Window");

	sf::Texture tileTex;
	if (!tileTex.loadFromFile(".\\assets\\textures\\tile.png")) return 0;
	tileTex.setRepeated(true);

	sf::Sprite floor;
	floor.setTexture(tileTex);
	floor.setTextureRect(sf::IntRect(0, 0, 800, 100));
	floor.setPosition(0,500);

	float beachBallRadius = 30.f;
	sf::Vector2f beachBallSize(beachBallRadius * 2.f, beachBallRadius * 2.f);
	sf::Texture beachBallTex;
	sf::Sprite beachBall;
	loadTexture(beachBallTex, beachBall, "beachball.png", beachBallSize);
	beachBall.setPosition(375, 150);

	sf::Texture stone;
	if (!stone.loadFromFile(".\\assets\\textures\\stone.png")) return 0;

	sf::Vector2f block1Size(200, 50);
	sf::Sprite block1;
	block1.setScale(block1Size.x / stone.getSize().x, block1Size.y / stone.getSize().y);
	block1.setOrigin(block1Size.x / 2.f / block1.getScale().x, block1Size.y / 2.f / block1.getScale().y);
	block1.setPosition(300, 400);
	block1.setRotation(20.f);
	block1.setTexture(stone);

	sf::Vector2f block2Size(100, 100);
	sf::Sprite block2;
	block2.setScale(block2Size.x / stone.getSize().x, block2Size.y / stone.getSize().y);
	block2.setOrigin(block2Size.x / 2.f / block2.getScale().x, block2Size.y / 2.f / block1.getScale().y);
	block2.setPosition(100, 300);
	block2.setColor(sf::Color::Magenta);
	block2.setTexture(stone);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.key.code == sf::Keyboard::Up) block1.move(0.f, -10.f);
			if (event.key.code == sf::Keyboard::Down) block1.move(0.f, 10.f);
			if (event.key.code == sf::Keyboard::Left) block1.move(-10.f, 0.f);
			if (event.key.code == sf::Keyboard::Right) block1.move(10.f, 0.f);
			if (event.key.code == sf::Keyboard::Tab && !event.key.shift) block1.rotate(5.0f);
			if (event.key.code == sf::Keyboard::Tab && event.key.shift) block1.rotate(-5.0f);

			if (event.key.code == sf::Keyboard::W) block2.move(0.f, -10.f);
			if (event.key.code == sf::Keyboard::S) block2.move(0.f, 10.f);
			if (event.key.code == sf::Keyboard::A) block2.move(-10.f, 0.f);
			if (event.key.code == sf::Keyboard::D) block2.move(10.f, 0.f);
			if (event.key.code == sf::Keyboard::Tab && !event.key.shift) block2.rotate(5.0f);
			if (event.key.code == sf::Keyboard::Tab && event.key.shift) block2.rotate(-5.0f);
		}

		window.clear(sf::Color(150, 150, 150));

		window.draw(floor);
		window.draw(block1);
		window.draw(block2);

		window.display();
	}

	return 0;
}