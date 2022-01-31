/// <summary>
/// Leon Nolte
/// 24 January 2022
/// </summary>

#ifndef GAME_HPP
#define GAME_HPP

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>

#include <SFML/Graphics.hpp>

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
	void processMouseKlicks(sf::Event t_event);
	void processMouseReleases(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	void movePlane();
	void setFlightAngle();

	const float M_PI = 3.1416f;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	sf::Sprite m_planeOneSprite;	// first plane sprite
	sf::Texture m_planesTexture;	// texture used for planes
	sf::Vector2f m_planesPosition{200.0f, 200.0f};	// center point of plane
	sf::Vector2f m_currentVelocity{ -1.0f, -1.0f};	// current velocity of plane
	sf::Vector2f m_newVelocityOrigin;
	sf::Vector2f m_newVelocityEnd;

	float m_flightAngleRadians = 0.0f;
	float m_flightAngle = 0.0f;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

