#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
	sf::RenderWindow Window(sf::VideoMode(800, 300), "SFML is working!!!");

	Window.setPosition(sf::Vector2i(100, 100));
	Window.setFramerateLimit(60);
	Window.setSize(sf::Vector2u(800, 300));

	sf::Clock timer;
	int iCounter = 0;

	bool bIsUpPressed = false;
	bool bisDownPressed = false;


	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Window.close();
			}

			if (event.key.code == sf::Keyboard::W) cout << "The W key was pressed" << endl;
			if (event.key.code == sf::Keyboard::A) cout << "The A key was pressed" << endl;
			if (event.key.code == sf::Keyboard::S) cout << "The S key was pressed" << endl;
			if (event.key.code == sf::Keyboard::D) cout << "The D key was pressed" << endl;
			if (event.key.code == sf::Keyboard::Space) cout << "The Spacebar key was pressed" << endl;
			if (event.mouseButton.button == sf::Mouse::Left) cout << "The LMB was pressed" << endl;
			if (event.mouseButton.button == sf::Mouse::Right) cout << "The RMB was pressed" << endl;


			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up) bIsUpPressed = true;
				if (event.key.code == sf::Keyboard::Down) bisDownPressed = true;

			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up) bIsUpPressed = false;
				if (event.key.code == sf::Keyboard::Down) bisDownPressed = false;

			}

			if (bIsUpPressed)
			{
				if (bisDownPressed)
				{
					cout << "Up and Down are both pressed" << endl;
				}
				else
				{
					cout << "Up is pressed" << endl;
				}
			}
			else
			{
				if (bisDownPressed)
				{
					cout << "Down is pressed" << endl;
				}
			}

			sf::Time elapsedTime = timer.getElapsedTime();

			if (elapsedTime.asSeconds() > 1.0f)
			{
				cout << iCounter << endl;
				iCounter++;
				if (iCounter == 100) iCounter = 0;

				timer.restart();
			}
		}

		

	}
	return 0;
}