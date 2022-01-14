/// <summary>
/// @author JamesEMurray
/// @date 10/01/2022
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{

	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Right == t_event.key.code)
	{
		//When RightArrow pressed, move sprite right [Assigned Sprite: m_mainCharS]
		m_mainCharS.setPosition((previous + move), 380.0f);
		previous = previous + move;
	}
	if (sf::Keyboard::Left == t_event.key.code)
	{
		//When LeftArrow pressed, move sprite left [Assigned Sprite: m_mainCharS]
		m_mainCharS.setPosition((previous - move), 380.0f);
		previous = previous - move;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		//When Spacebar pressed, move sprite upwards [Assigned Sprite: m_mainCharS]
		m_mainCharS.setPosition(previous, postJump);
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	moveSprite();
	checkCollision();

	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	
	m_window.clear(sf::Color::Black);
	changeColour();
	m_window.draw(m_yellowOptionS);
	m_window.draw(m_redOptionS);
	m_window.draw(m_mainCharS);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{

	if (!m_mainCharT.loadFromFile("ASSETS\\IMAGES\\mainCharSprite.png"))
	{
		//error message
		std::cout << "Problem loading Main Character" << std::endl;
	}
	m_mainCharS.setTexture(m_mainCharT);
	m_mainCharS.setPosition(previous, 380.0f);

	if (!m_yellowOptionT.loadFromFile("ASSETS\\IMAGES\\Yellow.png"))
	{
		//error message
		std::cout << "Problem loading yellow text" << std::endl;
	}
	m_yellowOptionS.setTexture(m_yellowOptionT);
	m_yellowOptionS.setPosition(priorY, 120.0f);

	if (!m_redOptionT.loadFromFile("ASSETS\\IMAGES\\Red.png"))
	{
		//error message
		std::cout << "Problem loading red text" << std::endl;
	}
	m_redOptionS.setTexture(m_redOptionT);
	m_redOptionS.setPosition(priorR, 240.0f);
}

void Game::moveSprite()
{
	short count = 0;
	/*
	while (count <= 3200)
	{*/
	if (count <= 3200)
	{
		
		m_yellowOptionS.setPosition(priorY, 120.0f);
		priorY = priorY - 0.1f;

		m_redOptionS.setPosition(priorR, 240.0f);
		priorR = priorR - 0.1f;

		count++;
	}
	
}

void Game::checkCollision()
{
	if ( m_mainCharS.getGlobalBounds().intersects( m_yellowOptionS.getGlobalBounds()))
	{
		m_switchColourY = true; //For testing
		m_colour = colourMode::yellow;
	}

	if ( m_mainCharS.getGlobalBounds().intersects( m_redOptionS.getGlobalBounds()))
	{
		m_switchColourR = true; //For testing
		m_colour = colourMode::red;
	}
	
	if (m_switchColourY == true) //testing message
	{
		std::cout << "Y = true" << std::endl;
		m_switchColourY = false;
	}
	if (m_switchColourR == true) //testing message
	{
		std::cout << "R = true" << std::endl;
		m_switchColourR = false;
	}
}

void Game::changeColour()
{
	//to set screen colour when collison occurs
	switch (m_colour)
	{
	case colourMode::black:
		m_window.clear(sf::Color::Color(127, 127, 127, 255));
		break;
	case colourMode::yellow:
		m_window.clear(sf::Color::Yellow);
		break;
	case colourMode::red:
		m_window.clear(sf::Color::Red);
		break;
	}
}
