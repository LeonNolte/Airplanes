/// <summary>
/// Leon Nolte
/// 24 January 2022
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
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Airplanes" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
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
		if (sf::Event::MouseButtonPressed == newEvent.type)	// user klicked with mouse
		{
			processMouseKlicks(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type) // user released mouse button
		{
			processMouseReleases(newEvent);
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
}

/// <summary>
/// deals with mouse button presses from user
/// </summary>
/// <param name="t_event"> mouse button press event </param>
void Game::processMouseKlicks(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.key.code)
	{
		m_newVelocityOrigin = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
	}
}

/// <summary>
/// deals with mouse button releases
/// </summary>
/// <param name="t_event"> mouse button release release event </param>
void Game::processMouseReleases(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.key.code)
	{
		m_newVelocityEnd = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
		m_currentVelocity = (m_newVelocityEnd - m_newVelocityOrigin) / 80.0f; // sets new plane velocity
		setFlightAngle();
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	movePlane();

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_planeOneSprite);
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
	if (!m_planesTexture.loadFromFile("ASSETS\\IMAGES\\PLANES.png"))
	{
		std::cout << "Error: Planes texture could not be loaded";
	}

	m_planeOneSprite.setTexture(m_planesTexture);
	m_planeOneSprite.setTextureRect(sf::IntRect(362, 115, 87, 69));
	m_planeOneSprite.setOrigin(43.5f, 34.5f);
	m_planeOneSprite.setPosition(sf::Vector2f(50.0f, 30.0f));
	setFlightAngle();
}

/// <summary>
/// moves plane at basic set speed and detects window boundaries
/// </summary>
void Game::movePlane()
{
	m_planesPosition += m_currentVelocity;
	m_planeOneSprite.setPosition(m_planesPosition);

	if (m_planesPosition.x <= 0.0f)
	{
		m_planesPosition.x = 0.0f;
	}

	else if (m_planesPosition.x >= 800.0f)
	{
		m_planesPosition.x = 800.0f;
	}

	if (m_planesPosition.y <= 0.0f)
	{
		m_planesPosition.y = 0.0f;
	}

	else if (m_planesPosition.y >= 600.0f)
	{
		m_planesPosition.y = 600.0f;
	}
}

/// <summary>
/// rotates sprite to fit plane trajectory
/// </summary>
void Game::setFlightAngle()
{
	m_flightAngleRadians = std::atan2(m_currentVelocity.y, m_currentVelocity.x);	// calculates angle in radians
	m_flightAngle = 180.0f * m_flightAngleRadians / M_PI;	// translates radians into degrees

	m_planeOneSprite.setRotation(m_flightAngle + 90.0f);	// +90 degrees since original asset points upward
}
