#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>

#include"PlayerShip.h"
#include"Enemy.h"
#include"Bullet.h"
#include"Block.h"


using namespace std;

int main()
{



	// initialising game variables and window~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Space Invaders", sf::Style::Default);
	window.setPosition(sf::Vector2i(400, 100));
	window.setFramerateLimit(60);

	// initilizing variables
	int PlayerLives = 3;
	int maxNumEnemies = 10;
	unsigned int uiPoints = 0;
	bool bBulletColl = false;
	bool bBulletCollPlayer = false;
	bool bBlockColl = false;
	bool bAlienMoveR = true;
	bool bAlienMoveL = false;
	bool bRedAlienBool = false;
	bool bSwitchMusic = false;
	float iAlienMovesSpeed = 1.f;
	int iSpriteWidth = 45;
	int iWaveCounter = 0;
	const int iNumOfFrames = 2;
	int iCurrentFrame;
	const int iNumOfBlocks = 3;
	const float iDifficultyRamp = 0.2f;

	// points marker for when to spawn red invader in seconds
	int aiRedAlienSpawn[10];
	for (int i = 0; i < 10; i++)
	{
		aiRedAlienSpawn[i] = 30 + (30 * i);
	}

	string asSubHeaderString[3];
	asSubHeaderString[0] = "Mercury";
	asSubHeaderString[1] = "Mars";
	asSubHeaderString[2] = "Invader Homeworld";


	//initializing a random seed, this ensures the Srand function wont return a similar set of random values each time.
	srand(static_cast<unsigned int>(time(0)));
	int iRandNum;
	iRandNum = rand() % 10;

	PlayerShip Player1(".\\assets\\images\\Ship.png");
	sf::FloatRect ShipBoundingbox = Player1.pSprite.getGlobalBounds();
	Player1.setPosition(500.f, 750.f);

	vector<PlayerShip> PlayerLivesVec;
	for (int i = 0; i < PlayerLives; i++)
	{
		PlayerShip PlayerlivesIcon(".\\assets\\images\\Ship.png");
		PlayerlivesIcon.setPosition(800.f + (i * 75), 10.f);
		PlayerlivesIcon.pSprite.setScale(PlayerlivesIcon.pSprite.getScale().x / 2.0f, PlayerlivesIcon.pSprite.getScale().y / 2.0f); 
		PlayerLivesVec.push_back(PlayerlivesIcon);
	}

	//vectors holding invaders
	vector<Enemy> AlienShipVec;
	vector<Enemy> AlienshipRedVec;

	//vectors holding bullets
	vector<Bullet> bulletvec;
	bool isFiring = false;
	bool isDown = false;

	vector<Bullet> AlienBulletVec;
	bool AlienIsFiring = false;

	//vectors holding blocks
	vector<Block> BlockVec;
	for (int i = 0; i < iNumOfBlocks; i++)
	{
		Block block(".\\assets\\images\\FullBlock.png");
		block.setPosition(175 + (i * 300),650);
		block.setScale(4);
		BlockVec.push_back(block);
	}

	// clocks used in window loop for repeated functions such as switching booleans related to other objects
	sf::Clock ShipFireClock;
	sf::Clock AlienFireClock;
	sf::Clock RedInvaderClock;
 	
	// game boundries
	sf::RectangleShape leftWall;
	leftWall.setSize(sf::Vector2f(5,800));
	leftWall.setPosition(0,0);
	leftWall.setFillColor(sf::Color::Blue);
	sf::FloatRect leftWallBoundingBox = leftWall.getGlobalBounds();

	sf::RectangleShape RightWall;
	RightWall.setSize(sf::Vector2f(5, 800));
	RightWall.setPosition(995, 0);
	RightWall.setFillColor(sf::Color::Blue);
	sf::FloatRect rightWallBoundingBox = RightWall.getGlobalBounds();

	sf::RectangleShape ceiling;
	ceiling.setSize(sf::Vector2f(1000, 5));
	ceiling.setPosition(0,0);
	ceiling.setFillColor(sf::Color::Blue);
	sf::FloatRect ceilingBoundingBox = ceiling.getGlobalBounds();

	//load font
	sf::Font SIFont;
	if (!SIFont.loadFromFile(".\\assets\\fonts\\unifont.ttf")) return 0;

	//score text
	sf::Text scoreCounter;
	scoreCounter.setFont(SIFont);
	scoreCounter.setString("000");
	scoreCounter.setCharacterSize(24);
	scoreCounter.setPosition(10,10);
	scoreCounter.setFillColor(sf::Color::White);

	//Header text
	sf::Text headerText;
	headerText.setFont(SIFont);
	headerText.setCharacterSize(24);
	headerText.setPosition(475,10);
	headerText.setFillColor(sf::Color::White);

	sf::Text SubHeaderText;
	SubHeaderText.setFont(SIFont);
	SubHeaderText.setString(asSubHeaderString[0]);
	SubHeaderText.setCharacterSize(24);
	SubHeaderText.setPosition(475,30);
	SubHeaderText.setFillColor(sf::Color::White);

	// load sounds
	sf::SoundBuffer P1ShootBuffer;
	if (!P1ShootBuffer.loadFromFile(".\\assets\\sounds\\ShipBullet.wav")) return 0;
	sf::SoundBuffer AlienShootBuffer;
	if (!AlienShootBuffer.loadFromFile(".\\assets\\sounds\\InvaderBullet.wav")) return 0;
	sf::SoundBuffer AlienDeathbuffer;
	if (!AlienDeathbuffer.loadFromFile(".\\assets\\sounds\\InvaderHit.wav")) return 0;
	sf::SoundBuffer PlayerDeathBuffer;
	if (!PlayerDeathBuffer.loadFromFile(".\\assets\\sounds\\ShipHit.wav")) return 0;
	
	//sounds initialize buffers and settings
	sf::Sound PlayerShootSFX;
	PlayerShootSFX.setBuffer(P1ShootBuffer);
	sf::Sound AlienShootSFX;
	AlienShootSFX.setBuffer(AlienShootBuffer);
	sf::Sound AlienDestroy;
	AlienDestroy.setBuffer(AlienDeathbuffer);
	sf::Sound PlayerShipDestroy;
	PlayerShipDestroy.setBuffer(PlayerDeathBuffer);

	sf::Sound Music;
	sf::SoundBuffer musicBuffer[3];
	if (!musicBuffer[0].loadFromFile(".\\assets\\sounds\\03_Mercury.wav")) return 0;
	if (!musicBuffer[1].loadFromFile(".\\assets\\sounds\\06_Mars.wav")) return 0;
	if (!musicBuffer[2].loadFromFile(".\\assets\\sounds\\12_Invader Homeworld.wav")) return 0;

	Music.setBuffer(musicBuffer[0]);
	Music.setVolume(50);
	Music.play();
	Music.setLoop(true);




	// main window loop~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (AlienShipVec.empty() == true)
			{
				AlienShipVec.clear();
				iWaveCounter++;
				headerText.setString(to_string(iWaveCounter));
				bSwitchMusic = true;

				for (int i = 0; i < maxNumEnemies; i++)
				{
					Enemy alienshipnew1(".\\assets\\images\\InvaderA1.png");
					alienshipnew1.setPosition(800 - (i * 75), 300);
					AlienShipVec.push_back(alienshipnew1);
					cout << "sprites loaded:" << AlienShipVec.size() + 1 << endl;
				}

				for (int i = 0; i < maxNumEnemies; i++)
				{
					Enemy alienshipnew2(".\\assets\\images\\InvaderB1.png");
					alienshipnew2.setPosition(800 - (i * 75), 200);
					AlienShipVec.push_back(alienshipnew2);
					cout << "sprites loaded:" << AlienShipVec.size() + 1 << endl;
				}


				for (int i = 0; i < maxNumEnemies; i++)
				{
					Enemy alienshipnew3(".\\assets\\images\\InvaderC1.png");
					alienshipnew3.setPosition(800 - (i * 75), 100);
					AlienShipVec.push_back(alienshipnew3);
					cout << "sprites loaded:" << AlienShipVec.size() + 1 << endl;
				}
			}

			if (bRedAlienBool == true)
			{
				
				for (int i = 0; i < 1; i++)
				{
						Enemy alienShipRed(".\\assets\\images\\RedInvader.png");
						alienShipRed.setPosition(0, 100);
						AlienshipRedVec.push_back(alienShipRed);
						bRedAlienBool = false;
				}
				
			}

			// player inputs
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				Player1.movePlayer('a', 15.0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				Player1.movePlayer('d', 15.0);
			}

			if (isDown == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					isFiring = true;
					isDown = true;

				}
				
			}

			// moves the ship to the right with equal force to ships movespeed if touching the left wall
			if (Player1.pSprite.getGlobalBounds().intersects(leftWall.getGlobalBounds()))
			{
				cout << "ship is intersecting left wall" << endl;
				Player1.pSprite.move(15, 0); 
			}

			// moves ship to the left with equal force to ship move speed if touching the right wall
			if (Player1.pSprite.getGlobalBounds().intersects(RightWall.getGlobalBounds()))
			{
				cout << "ship is intersecting right wall" << endl;
				Player1.pSprite.move(-15, 0); 
			}

			// changes the "isDown" boolean every 1.5 seconds, allowing the laser to be fired, this stops the laser from being rapidly fired
			if (ShipFireClock.getElapsedTime().asSeconds() >= 1.5)
			{ 
				isDown = false;
				ShipFireClock.restart();
				cout << "laser has reset" << endl;
			}

			//developer cheat for testing
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				cout << "cheat enabled" << endl;
				for (int i = 0; i < AlienShipVec.size(); i++)
				{
					AlienShipVec.erase(AlienShipVec.begin() + i);
				}
			}*/

		}




		// Update Window~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		window.clear(sf::Color::Black);	

		if (RedInvaderClock.getElapsedTime().asSeconds() > 30)
		{
			if (AlienshipRedVec.empty())
			{
				bRedAlienBool = true;
			}
		}

		if (iWaveCounter == 2)
		{
			if (bSwitchMusic == true)
			{
				cout << "this function works" << endl;
				Music.setBuffer(musicBuffer[1]);
				Music.play();
			}
			SubHeaderText.setString(asSubHeaderString[1]);
			bSwitchMusic = false;
		}
		else if(iWaveCounter == 3)
		{
			if (bSwitchMusic == true)
			{
				Music.setBuffer(musicBuffer[2]);
				Music.play();
			}
			SubHeaderText.setString(asSubHeaderString[2]);
			bSwitchMusic = false;
		}

		if (iWaveCounter > 3)
		{
			SubHeaderText.setString("You Win! Go for a high Score!");
		}

        //check ship collision
		for (int i = 0; i < AlienBulletVec.size(); i++)
		{
			Player1.checkColl(AlienBulletVec[i]);
		
		}

		if (Player1.getY() > 1000)
		{
			if (!PlayerLivesVec.empty())
			{
				PlayerLivesVec.pop_back();
				bBulletCollPlayer = true;
			}

			PlayerShipDestroy.play();
			Player1.setPosition(500.f, 750.f);
			cout << PlayerLivesVec.size() << ": lives remaining" << endl;

		}
		
		// checking for alien collision
		for (int i = 0; i < bulletvec.size(); i++)
		{
			// only checks if bullet is on the same height as the invaders to reduce constant memory usage
			if (bulletvec[i].getTop() < AlienShipVec.front().getPosY())
			{
				for (int j = 0; j < AlienShipVec.size(); j++)
				{
					AlienShipVec[j].checkColl(bulletvec[i]);

					if (AlienShipVec[j].bCollision == true)
					{
						bBulletColl = true;

						AlienShipVec[j].bCollision = false;
					}
					
				}
						
			}
		}

		//checking for red Invader collisions
		if (!AlienshipRedVec.empty())
		{
			for (int i = 0; i < bulletvec.size(); i++)
			{
				for (int j = 0; j < AlienshipRedVec.size(); j++)
				{
					AlienshipRedVec[j].checkColl(bulletvec[i]);

					// erasing invader
					if (AlienshipRedVec[j].bCollision == true)
					{
						bBulletColl = true;
						AlienshipRedVec[j].bCollision = false;
						RedInvaderClock.restart();
						AlienshipRedVec.erase(AlienshipRedVec.begin() + j);
						AlienDestroy.play();
						uiPoints = (uiPoints + 20);
					}
				}
			}
			
		}

		//checking for block collision
		for (int i = 0; i < AlienBulletVec.size(); i++)
		{
			for (int j = 0; j < BlockVec.size(); j++)
			{
				BlockVec[j].checkColl(AlienBulletVec[i], AlienShipVec.front());
				BlockVec[j].acquireFile();
				if (BlockVec[j].bCollision == true)
				{
					cout << "bullet erased" << endl;
					bBlockColl = true;
					BlockVec[j].bCollision = false;
				}
			}
		}
			
		//setting the bullet position to the ships X and Y co-ordinates (+27 to align laser with center of ship)
		if (isFiring == true)
		{
			Bullet newBullet(".\\assets\\images\\Bullet.png");
			newBullet.setPosition(sf::Vector2f(Player1.getX() + 27, Player1.getY()));
			bulletvec.push_back(newBullet);
			PlayerShootSFX.play();
			isFiring = false;


		}

		// creating bullet for alien fire, returns a random integer to choose an object from the vector to fire from
		if (AlienIsFiring == true)
		{
			if (AlienShipVec.size() > 10)
			{
				
				Bullet newBullet(".\\assets\\images\\Bullet.png");
				newBullet.setPosition(sf::Vector2f(AlienShipVec[iRandNum].getPosX(), AlienShipVec[iRandNum].getPosY())); //fix it , fatal error when 10 or less enemies remain
				AlienBulletVec.push_back(newBullet);
				AlienShootSFX.play();
				iRandNum = rand() % 10;
				AlienIsFiring = false;
			}
		}  

		

		

		// erasing aliens, moves alien up away from window area and safely erases from the vector
		for (int i = 0; i < AlienShipVec.size(); i++)
		{
			if (AlienShipVec[i].getPosY() < 0)
			{
				uiPoints++;
				scoreCounter.setString(to_string(uiPoints));
				cout << "Alien has been destroyed!" << endl;

				AlienShipVec.erase(AlienShipVec.begin() + i);
				AlienShipVec.shrink_to_fit();
				AlienDestroy.play();
				

			}

		}

		// erasing collided bullet
		if (bBulletColl == true)
		{
			for (int i = 0; i < bulletvec.size(); i++)
			{
				bulletvec.erase(bulletvec.begin() + i);
			}
			bBulletColl = false;
		}
		else if (bBulletCollPlayer == true)
		{
			for (int i = 0; i < AlienBulletVec.size(); i++)
			{
				AlienBulletVec.erase(AlienBulletVec.begin() + i);
			}
			bBulletCollPlayer = false;
		}
		else if (bBlockColl == true)
		{
			for (int i = 0; i < AlienBulletVec.size(); i++)
			{
				AlienBulletVec.erase(AlienBulletVec.begin() + i);
			}
			bBlockColl = false;
		}

		//drawing each bullet to window and setting trajectory through fire() function 
		for (int i = 0; i < bulletvec.size(); i++)
		{
			bulletvec[i].draw(window);
			bulletvec[i].fire(-10);

			// erase bullet from vector if it goes off screen
			for (int j = 0; j < bulletvec.size(); j++)
			{
				if (bulletvec[j].getRight() > ceiling.getPosition().x &&
					bulletvec[j].getTop() < ceiling.getPosition().y + ceiling.getGlobalBounds().height
					&& bulletvec[j].getBottom() > ceiling.getPosition().y)
				{
					bulletvec.erase(bulletvec.begin() + i);
					cout << "bullet erased" << endl;
				}

			}
		}

		if (AlienFireClock.getElapsedTime().asSeconds() >= 3 - (iDifficultyRamp * iWaveCounter))
		{
			AlienIsFiring = true;
			AlienFireClock.restart();
			cout << "Aliens fire" << endl;

		}

		for (int i = 0; i < AlienBulletVec.size(); i++)
		{
			AlienBulletVec[i].draw(window);
			AlienBulletVec[i].fire(5);

			for (int j = 0; j < AlienBulletVec.size(); j++)
			{
				if (AlienBulletVec[j].getBottom() > 800)
				{
					AlienBulletVec.erase(AlienBulletVec.begin() + i);
					cout << "Alien bullet erased" << endl;
				}
			}
		}

		// moving aliens

		if (AlienShipVec.size() > 20)
		{
			iAlienMovesSpeed = 0.5f + (iDifficultyRamp * iWaveCounter);
		}
		else if (AlienShipVec.size() <= 20 && AlienShipVec.size() > 10)
		{
			iAlienMovesSpeed = 1.5f + (iDifficultyRamp * iWaveCounter);
		}
		else if (AlienShipVec.size() <= 10 && AlienShipVec.size() > 1)
		{
			iAlienMovesSpeed = 2.5f + (iDifficultyRamp * iWaveCounter);
		}
		else if (AlienShipVec.size() <= 1)
		{
			iAlienMovesSpeed = 6.f + (iDifficultyRamp * iWaveCounter);
		}

		for (int i = 0; i < AlienShipVec.size(); i++)
		{
			if (AlienShipVec[i].getPosX() + iSpriteWidth >= RightWall.getPosition().x)
			{
				bAlienMoveR = false;
				bAlienMoveL = true;
				cout << "aliens move left" << endl;
				for (int i = 0; i < AlienShipVec.size(); i++)
				{
					AlienShipVec[i].moveEnemy('D', 0.f);
				}
			}
			else if (AlienShipVec[i].getPosX() <= leftWall.getPosition().x)
			{
				bAlienMoveL = false;
				bAlienMoveR = true;
				cout << "aliens move right" << endl;
				for (int i = 0; i < AlienShipVec.size(); i++)
				{
					AlienShipVec[i].moveEnemy('D', 0.f);
				}
			}
		}

		if (bAlienMoveR == true)
		{
			for (int i = 0; i < AlienShipVec.size(); i++)
			{
				AlienShipVec[i].moveEnemy('R', iAlienMovesSpeed);
			}
		}
		else if (bAlienMoveL == true)
		{
			for (int i = 0; i < AlienShipVec.size(); i++)
			{
				AlienShipVec[i].moveEnemy('L', iAlienMovesSpeed);
			}
		}

		for (int i = 0; i < AlienshipRedVec.size(); i++)
		{
			AlienshipRedVec[i].moveEnemy('R', 1.f);
		}

		for (int i = 0; i < AlienShipVec.size(); i++)
		{
			if (AlienShipVec[i].getPosY() >= 750)
			{
				if (!PlayerLivesVec.empty())
				{
					PlayerLivesVec.pop_back();
					cout << PlayerLivesVec.size() << ": lives remaining" << endl;
				}

				AlienShipVec.erase(AlienShipVec.begin() + i);
			}
		}

		for (int i = 0; i < AlienshipRedVec.size(); i++)
		{
			if (AlienshipRedVec[i].getPosX() > 1000)
			{
				bRedAlienBool = false;
				RedInvaderClock.restart();
				AlienshipRedVec.erase(AlienshipRedVec.begin() + i);
			}
		}

		if (PlayerLivesVec.empty())
		{
			window.close();
		}

		// drawing sprites

		for (auto i = 0; i < AlienShipVec.size(); i++)
		{
			AlienShipVec[i].acquireFile();
			AlienShipVec[i].drawEnemy(window);
		}

		for (int i = 0; i < PlayerLivesVec.size(); i++)
		{
			PlayerLivesVec[i].acquireFile();
			PlayerLivesVec[i].drawPlayer(window);
		}

		for (int i = 0; i < BlockVec.size(); i++)
		{
			BlockVec[i].acquireFile();
			BlockVec[i].drawBlock(window);
		}

		for (int i = 0; i < AlienshipRedVec.size(); i++)
		{
			AlienshipRedVec[i].acquireFile();
			AlienshipRedVec[i].drawEnemy(window);
		}

		Player1.drawPlayer(window);
		window.draw(leftWall);
		window.draw(RightWall);
		window.draw(ceiling);
		window.draw(scoreCounter);
		window.draw(headerText);
		window.draw(SubHeaderText);

		window.display();

	}

	


	return 0;
}

