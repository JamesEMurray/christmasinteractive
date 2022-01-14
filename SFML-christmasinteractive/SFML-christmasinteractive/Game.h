/// <summary>
/// author JamesEMurray
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

enum class colourMode { black, yellow, red };

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	void moveSprite(); //Moves the text across the screen
	void checkCollision(); //Checks if char collide with colour words, (triggers screen change)
	void changeColour();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Sprite m_yellowOptionS; //text used for first yellow menu option
	sf::Texture m_yellowOptionT; //texture for yellow text
	sf::Sprite m_redOptionS; //text used for second menu option red
	sf::Texture m_redOptionT; //textture for red text
	sf::Sprite m_mainCharS; // sprite used for main character
	sf::Texture m_mainCharT; // texture used for main character
	bool m_exitGame; // control exiting game
	bool m_switchColourY = false;
	bool m_switchColourR = false;

	float move = 10.0;
	float previous = 40.0;
	float priorY = 120.0;
	float priorR = 480.0;
	float postJump = 380.0f - (20 * move);

	colourMode m_colour = colourMode::black;
};

#endif // !GAME_HPP

