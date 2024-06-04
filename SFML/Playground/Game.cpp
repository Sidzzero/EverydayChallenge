#include "Game.h"

Game::Game() :m_window("Chap2", sf::Vector2u{800,600})
{
    m_mushTexture.loadFromFile("cyclops_1.png");
    m_mushSprite.setTexture(m_mushTexture);
    m_increment = sf::Vector2f{ 4,4 };
}

Game::~Game()
{
}

void Game::HandleInput()
{
}

void Game::Update()
{
    m_window.Update();
    Move();
}

void Game::Render()
{
    m_window.BeginDraw();
    m_window.Draw(m_mushSprite);
    m_window.EndDraw();
}

Window* Game::GetWindow()
{
    return &m_window;
}

void Game::Move()
{
}
