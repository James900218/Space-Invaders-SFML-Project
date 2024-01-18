#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Animated Sprites");

	sf::Clock timer;

	bool bSuccess;

	sf::Vector2f trafficLightsSize(84, 250);
	sf::Texture trafficLightTex;
	sf::Sprite trafficLightsSprite;
	bSuccess = trafficLightTex.loadFromFile(".\\assets\\textures\\lights.png");

	if (!bSuccess)
	{
		exit(1);
	}

	static const int iNumFrames = 4;
	int iCurrentFrame = 0;
	sf::IntRect trafficLightrect[iNumFrames];
	trafficLightrect[0] = sf::IntRect(0, 0, 84, 249);
	trafficLightrect[1] = sf::IntRect(83, 0, 84, 249);
	trafficLightrect[2] = sf::IntRect(166, 0, 84, 249);
	trafficLightrect[3] = sf::IntRect(249, 0, 84, 249);

	trafficLightsSprite.setScale(trafficLightsSize.x / trafficLightTex.getSize().x * 4.0f, trafficLightsSize.y / trafficLightTex.getSize().y);
	trafficLightsSprite.setOrigin(trafficLightsSize.x / 2.f / trafficLightsSprite.getScale().x, trafficLightsSize.y / 2.f / trafficLightsSprite.getScale().y);
	trafficLightsSprite.setPosition(675, 300);
	trafficLightsSprite.setTexture(trafficLightTex);
	trafficLightsSprite.setTextureRect(trafficLightrect[iCurrentFrame]);

	sf::Vector2f explosionSize(334, 320);
	sf::Texture explosionTex;
	sf::Sprite explosionSprite;
	bSuccess = explosionTex.loadFromFile(".\\assets\\textures\\explosion.png");

	if (!bSuccess)
	{
		exit(1);
	}

	bool bExplosionActive = false;

	int iCurrentFrame2 = 0;
	static const int iNumFrames2 = 24;
	const sf::Vector2i sheetDims(6, 4);
	sf::IntRect explosionRects[iNumFrames2];

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			explosionRects[i + j * 6] = sf::IntRect(i * explosionSize.x, j * explosionSize.y, explosionSize.x, explosionSize.y);
		}
	}

	explosionSprite.setScale(explosionSize.x / explosionTex.getSize().x * sheetDims.x, explosionSize.y / explosionTex.getSize().y * sheetDims.y);
	explosionSprite.setOrigin(explosionSize.x / 2.f / explosionSprite.getScale().x, explosionSize.y / 2.f / explosionSprite.getScale().y);
	explosionSprite.setTexture(explosionTex);
	explosionSprite.setTextureRect(explosionRects[iCurrentFrame2]);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				iCurrentFrame++;
				if (iCurrentFrame >= iNumFrames) iCurrentFrame = 0;
				trafficLightsSprite.setTextureRect(trafficLightrect[iCurrentFrame]);
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				explosionSprite.setPosition(event.mouseButton.x, event.mouseButton.y);
				iCurrentFrame2 = 0;
				bExplosionActive = true;
			}

					
		}

		sf::Time elapsedTime = timer.getElapsedTime();
		if (elapsedTime.asSeconds() > 1.0 / 24.0)
		{
			if (bExplosionActive)
			{
				iCurrentFrame2++;
				if (iCurrentFrame2 > iNumFrames2)
				{
					iCurrentFrame2 = 0;
					bExplosionActive = false;
				}
				explosionSprite.setTextureRect(explosionRects[iCurrentFrame2]);
			
			}
			timer.restart();
		}

		window.clear(sf::Color::White);
		window.draw(trafficLightsSprite);

		if (bExplosionActive)
		{
			window.draw(explosionSprite);
		}

		window.display();
		
	}

	return 0;


}