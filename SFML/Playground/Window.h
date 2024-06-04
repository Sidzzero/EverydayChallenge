#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Window
{
public:
	Window();
	Window(const std::string& a_title, const sf::Vector2u* a_size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullScreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullScreen();

	void Draw(sf::Drawable & a_drawable);

private:
	void Setup(const std::string& a_title, const sf::Vector2u* a_size);
	void Destroy();
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullScreen;



};

