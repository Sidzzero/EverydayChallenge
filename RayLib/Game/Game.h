#pragma once
#include "Common.h"
#include "Player.h"
#include "Pipe.h"
class Game 
{
public:

	bool isPLaying = true;
	bool isGameOver = false;

	bool isCrossed = false;
	Player player;

	Pipe pipe1;
	Pipe pipe2;

	Pipe* ptrCurrentPipe;
	Pipe* ptrNextPipe;
	Texture texBG;
	Texture texGameOver;
	Texture texGround;

	Sound fxFly;
	Sound fxPass;
	Sound fxHit;
	Sound fxDie;


	float yTop = 100;
	float yBot = 700;
	float fGroundScroll = 0;
	float fSkyScroll = 0;

	Game(int screenWidth, int screenHeight);// :player(playerCreated);
	void StartUp();
	void Update();
	void Draw();
	void Shutdown();

	void GameOver();

	

};

