#pragma once
#include "Common.h"
#include "Player.h"
#include "Pipe.h"
class Game 
{
public:

	bool isPLaying = true;
	Player player;

	Pipe pipe1;
	Pipe pipe2;

	Pipe* ptrCurrentPipe;
	Pipe* ptrNextPipe;
	Texture texBG;
	Texture texGameOver;
	Texture texGround;


	float yTop = 100;
	float yBot = 700;

	Game(int screenWidth, int screenHeight);// :player(playerCreated);
	void StartUp();
	void Update();
	void Draw();
	void Shutdown();

	

};

