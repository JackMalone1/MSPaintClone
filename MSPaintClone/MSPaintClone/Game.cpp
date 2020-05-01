#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U}, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
	m_window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(m_window);
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
	ImGui::SFML::Shutdown();
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

		processEvents(); // at least 60 fps
		ImGui::SFML::Update(m_window, clock.restart());
		update(timePerFrame);
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
		ImGui::SFML::ProcessEvent(newEvent);
		if (sf::Event::Closed == newEvent.type) // window message
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
	ImGui::SetNextWindowFocus();
	ImGui::Begin("Sample window"); // begin window
	if (ImGui::ColorPicker3("background colour",color))
	{
		// this code gets called if color value changes, so
		// the background color is upgraded automatically!
		bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
		bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
		bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
	}

	// Window title text edit
	ImGui::InputText("Window title", windowTitle, 255);

	if (ImGui::Button("Update window title")) {
		// this code gets if user clicks on the button
		// yes, you could have written if(ImGui::InputText(...))
		// but I do this to show how buttons work :)
		m_window.setTitle(windowTitle);
	}
	
	ImGui::End(); // end window
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	m_window.clear(bgColor);
	ImGui::SFML::Render(m_window);
	m_window.display();

}
