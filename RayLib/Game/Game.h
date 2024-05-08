#pragma once
#include "Common.h"
#include "Player.h"
class Game 
{
public:

	bool isPLaying = true;
	Player player;
	Game(int screenWidth, int screenHeight);// :player(playerCreated);
	void StartUp();
	void Update();
	void Draw();
	void Shutdown();
};

