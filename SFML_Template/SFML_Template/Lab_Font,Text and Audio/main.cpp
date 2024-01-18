#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

using namespace std;

int main()
{
	bool bSoundFX = true;
	bool bSpatialFx = false;
	bool bMusic = false;

	unsigned int uiTickingClock = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Drawing Window");

	sf::Clock timer;
	
	sf::Font digitalFont;
	if (!digitalFont.loadFromFile(".\\assets\\fonts\\DIGITALDREAMFATSKEW.TTF")) return 0;

	sf::Font germanFont;
	if (!germanFont.loadFromFile(".\\assets\\fonts\\din1451alt.TTF")) return 0;

	sf::Text Title;
	Title.setFont(digitalFont);
	Title.setString("Cool Video Game");
	Title.setCharacterSize(32);
	Title.setPosition(200, 30);
	Title.setFillColor(sf::Color::Green);

	sf::Text PlayTimer;
	PlayTimer.setFont(germanFont);
	PlayTimer.setString(to_string(uiTickingClock));
	PlayTimer.setCharacterSize(24);
	PlayTimer.setPosition(30, 30);
	PlayTimer.setFillColor(sf::Color::Green);

	sf::RectangleShape myRectB;
	myRectB.setSize(sf::Vector2f(150.f, 175.0f));
	myRectB.setPosition(200, 400);
	myRectB.setOrigin(myRectB.getSize().x / 2.0f, myRectB.getSize().y / 2.0f);
	myRectB.setFillColor(sf::Color::Blue);

	sf::SoundBuffer blopBuffer;
	if (!bSpatialFx)
	{
		if (!blopBuffer.loadFromFile(".\\assets\\audio\\beep.flac")) return 0;
	}
	else
	{
		if (!blopBuffer.loadFromFile(".\\assets\\audio\\beepMono.ogg")) return 0;
	}

	sf::Sound blopSound;
	blopSound.setBuffer(blopBuffer);

	if (!bSpatialFx)
	{
		blopSound.setRelativeToListener(true);
		blopSound.setMinDistance(500.f);
		blopSound.setAttenuation(0.000001f);
	}

	sf::Listener::setPosition(50.f, 0.f, 50.f);
	sf::Listener::setDirection(1.f, 0.f, 1.f);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				myRectB.move(0.f, -1.f);
				if (bSpatialFx) blopSound.setPosition(myRectB.getPosition().x, 0.f, myRectB.getPosition().y);
				if (bSoundFX) blopSound.play();
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				myRectB.move(0.f, 1.f);
				if (bSpatialFx) blopSound.setPosition(myRectB.getPosition().x, 0.f, myRectB.getPosition().y);
				if (bSoundFX) blopSound.play();
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				myRectB.move(-1.f, 0.f);
				if (bSpatialFx) blopSound.setPosition(myRectB.getPosition().x, 0.f, myRectB.getPosition().y);
				if (bSoundFX) blopSound.play();
			}
			if (event.key.code == sf::Keyboard::Right) 
			{
				myRectB.move(1.f, 0.f);				
				if (bSpatialFx) blopSound.setPosition(myRectB.getPosition().x, 0.f, myRectB.getPosition().y);
				if (bSoundFX) blopSound.play();
			}
			if (event.key.code == sf::Keyboard::Tab && !event.key.shift) myRectB.rotate(5.0f); 
			if (event.key.code == sf::Keyboard::Tab && event.key.shift) myRectB.rotate(-5.0f); 
		}

		sf::Time elapsedTime = timer.getElapsedTime();
		if (elapsedTime.asSeconds() > 1)
		{
			uiTickingClock++;
			timer.restart();
		}

		window.clear(sf::Color::Black);

		window.draw(Title);
		window.draw(PlayTimer);
		window.draw(myRectB);
		
		window.display();
	}

	return 0;
}