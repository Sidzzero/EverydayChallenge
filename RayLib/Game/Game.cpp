#include "Game.h"

Game::Game(int screenWidth, int screenHeight):player(Player(Vector2{ 180,400 }, "assets\\sprites\\bluebird-downflap.png"))
{
	//player = Player( Vector2{ 50,50 }, "assets\sprites\bluebird-downflap.png" );
	Image img = LoadImage("assets\\sprites\\gameover.png");
	texGameOver = LoadTextureFromImage(img);
	UnloadImage(img);
	img = LoadImage("assets\\sprites\\background-day.png");
	texBG = LoadTextureFromImage(img);
	UnloadImage(img);
	img = LoadImage("assets\\sprites\\base.png");
	texGround = LoadTextureFromImage(img);
	UnloadImage(img);

	ptrCurrentPipe = &pipe1;
	ptrNextPipe    = &pipe2;

}

void Game::StartUp()
{
	pipe1.StartMoving();
	pipe2.StopMoving();
}


void Game::Update()
{

	if ( IsKeyPressed(KEY_R))
	{
		yTop = GetRandomValue(100, 600);
		yBot = GetRandomValue(yTop + 200, 700);
	}
	if (isPLaying)
	{

	   if (ptrCurrentPipe->posTop.x < SCREEN_WIDTH/2 && ptrNextPipe->isMoving == false)
	   {
		   ptrNextPipe->StartMoving();
	   }

	   pipe1.Update();
	   pipe2.Update();

	   if (ptrCurrentPipe->posTop.x<-10 && ptrCurrentPipe->isMoving == true)
	   {
		   ptrCurrentPipe->GenerateRandomGap(SCREEN_WIDTH);
		   auto temp = ptrCurrentPipe;
		   ptrCurrentPipe = ptrNextPipe;
		   ptrNextPipe = temp;
	   }

	   player.Update();
	}
	
	if (player.pos.y> 900)
	{
		//isPLaying = false;
		//player.Reset();
	}
	if (GetKeyPressed()==KEY_SPACE)
	{
		isPLaying = true;
	
	}
	
	
	
}

void Game::Draw()
{
	
	//DrawTextureEx(texBG, Vector2{ 0, 0 }, 0, 1, RAYWHITE);
	DrawTexturePro(texBG, Rectangle{ 0,0,288,512 }, 
		Rectangle{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT+100 },
		Vector2{0,100},
		0 ,
		RAYWHITE);



	//DrawTextureEx(texPipe, Vector2{ 100,yTop }, 180, PLAYER_SCALE, RAYWHITE);//L-100  - top
	//DrawTextureEx(texPipe, Vector2{ 0,yBot }, 0, PLAYER_SCALE, RAYWHITE);//500 L-700 bottom
	pipe1.Draw();
	pipe2.Draw();
	DrawTexturePro(texGround, Rectangle{ 0,0,336,112 },
		Rectangle{ 0,0,SCREEN_WIDTH,112 + 100 },
		Vector2{ 0,-910 },
		0,
		RAYWHITE);
	player.Draw();
}

void Game::Shutdown()
{
	player.Cleanup();
}
