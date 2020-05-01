#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

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


	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game
	char windowTitle[255] = "ImGui + SFML = <3";
	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

};

#endif // !GAME_HPP