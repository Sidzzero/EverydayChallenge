#include "Game.h"

Game::Game(int screenWidth, int screenHeight):player(Player(Vector2{ 180,400 }, "assets\\sprites\\bluebird-downflap.png"))
{
	//player = Player( Vector2{ 50,50 }, "assets\sprites\bluebird-downflap.png" );
}

void Game::StartUp()
{
	
}

void Game::Update()
{
	player.Update();
}

void Game::Draw()
{
	player.Draw();
}

void Game::Shutdown()
{
	player.Cleanup();
}
