#pragma once
#include "Window.h"

#include <string>
class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

private:
	void Move();
	Window m_window;

	sf::Texture m_mushTexture;
	sf::Sprite m_mushSprite;
	sf::Vector2f m_increment{0.4f,0.4f};

};

