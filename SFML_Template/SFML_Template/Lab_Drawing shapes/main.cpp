#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
	sf::RenderWindow Window(sf::VideoMode(800, 300), "SFML is working!!!");

	Window.setPosition(sf::Vector2i(100, 100));
	Window.setFramerateLimit(60);
	Window.setSize(sf::Vector2u(800, 300));

	sf::RectangleShape myRectangle;
	myRectangle.setSize(sf::Vector2f(200.f, 120.f));
	myRectangle.setOrigin(myRectangle.getSize().x / 1.5f, myRectangle.getSize().y / 1.5f);
	myRectangle.setPosition(200, 250);
	myRectangle.setFillColor(sf::Color::Blue);
	myRectangle.setOutlineColor(sf::Color::Magenta);
	myRectangle.setOutlineThickness(10.f);

	sf::RectangleShape myRectangleB;
	myRectangleB.setSize(sf::Vector2f(200.f, 120.f));
	myRectangleB.setOrigin(myRectangleB.getSize().x / 1.5f, myRectangleB.getSize().y / 1.5f);
	myRectangleB.setPosition(500, 200);
	myRectangleB.setFillColor(sf::Color::Red);
	myRectangleB.setOutlineColor(sf::Color::Black);
	myRectangleB.setOutlineThickness(10.f);

	sf::FloatRect myRectangleBoundsBox = myRectangle.getGlobalBounds();
	sf::Vector2f location(15.f, 400.f);
	sf::FloatRect myRectangleBBoundsBox = myRectangleB.getGlobalBounds();
	bool isIn = myRectangleBoundsBox.contains(location);

	/*sf::CircleShape myCircle;
	myCircle.setRadius(45.0f);
	myCircle.setOrigin(45.0f, 45.0f);
	myCircle.setPosition(320.0f, 120.0f);
	myCircle.setPointCount(50);
	myCircle.setFillColor(sf::Color::Red);
	myCircle.setOutlineColor(sf::Color::Green);
	myCircle.setOutlineThickness(10.0f);*/

	
	//sf::FloatRect myCircleBoundsBox = myCircle.getLocalBounds();

	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Window.close();
			}

			if (event.key.code == sf::Keyboard::Up) myRectangle.move(0.f, -10.f);
			if (event.key.code == sf::Keyboard::Down) myRectangle.move(0.f, 10.f);
			if (event.key.code == sf::Keyboard::Left) myRectangle.move(-10.f, 0.f);
			if (event.key.code == sf::Keyboard::Right) myRectangle.move(10.f, 0.f);
			if (event.key.code == sf::Keyboard::Tab && !event.key.shift) myRectangle.rotate(5.0f);
			if (event.key.code == sf::Keyboard::Tab && event.key.shift) myRectangle.rotate(-5.0f);

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f clickLocation(event.mouseButton.x, event.mouseButton.y);

					if (myRectangleBoundsBox.contains(clickLocation))
					{
						if (myRectangle.getFillColor() == sf::Color::Blue)
						{
							myRectangle.setFillColor(sf::Color::Red);
						}
						else
						{
							myRectangle.setFillColor(sf::Color::Blue);
						}
					}
				}
			}
			//Check for collisions
			sf::FloatRect rectABoundingBox = myRectangle.getGlobalBounds();
			sf::Vector2f location(15.f, 400.f);
			bool isIn = myRectangleBoundsBox.contains(location);

			sf::FloatRect rectBBoundingBox = myRectangleB.getGlobalBounds();

			if (myRectangleBoundsBox.intersects(myRectangleBBoundsBox))
			{
				cout << "A and B bound boxes intersect." << endl;
			}
			else
			{
				cout << "A and B bound boxes do not intersect." << endl;
			}

			//if (isIn == true)        //myRectangleBoundsBox.intersects(myRectangleBBoundsBox))
			//{
			//	cout << "A and B bounds boxes are intersecting" << endl;                                                                                                                                                                                                         
			//}
			//else
			//{
			//	cout << "A and B bounds boxes are not intersecting" << endl;
			//}

		}

		Window.clear(sf::Color::White);

		Window.draw(myRectangle);
		Window.draw(myRectangleB);
		//Window.draw(myCircle);

		Window.display();

	}
	return 0;
}