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
	if (isPLaying)
	{
	   player.Update();
	}
	
	if (player.pos.y> 900)
	{
		isPLaying = false;
		player.Reset();
	}
	if (GetKeyPressed()==KEY_SPACE)
	{
		isPLaying = true;
	
	}
}

void Game::Draw()
{
	player.Draw();
}

void Game::Shutdown()
{
	player.Cleanup();
}
