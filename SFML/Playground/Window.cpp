#include "Window.h"

Window::Window()
{
	Setup("Basic Window-Powered by SFML",sf::Vector2u(640,480));
}

Window::Window(const std::string& a_title, const sf::Vector2u& a_size)
{
	Setup(a_title, a_size);
}

Window::~Window()
{
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color::Black);
}



void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
		else if (event.type ==sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			ToggleFullScreen();
		}
	}

}
bool Window::IsDone()
{
	return m_isDone;
}

bool Window::IsFullScreen()
{
	return m_isFullScreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_windowSize;
}

void Window::ToggleFullScreen()
{
	m_isFullScreen = !m_isFullScreen;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable& a_drawable)
{
	m_window.draw(a_drawable);
}

void Window::Setup(const std::string& a_title, const sf::Vector2u& a_size)
{
	m_windowTitle = a_title;
	m_windowSize  = a_size;
	m_isFullScreen = false;
	m_isDone = false;
	Create();
}

void Window::Create()
{
	auto style = m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_window.create({ m_windowSize.x,m_windowSize.y,32 }, m_windowTitle, style);
}

void Window::Destroy()
{
	m_window.close();
}


