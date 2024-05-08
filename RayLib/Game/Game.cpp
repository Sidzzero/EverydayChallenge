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
	pipe1.GenerateRandomGap(SCREEN_WIDTH+300);
	pipe1.StartMoving();
	pipe2.StopMoving();
}


void Game::Update()
{

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
		   ptrCurrentPipe->GenerateRandomGap(SCREEN_WIDTH+25);
		   auto temp = ptrCurrentPipe;
		   ptrCurrentPipe = ptrNextPipe;
		   ptrNextPipe = temp;
		   isCrossed = false;
	   }

	   player.Update();
	}
	//GAME OVER THINGS
	
	if (player.pos.y> 900 
		 ||
		(player.pos.x+50 >= ptrCurrentPipe->posTop.x-100 && player.pos.x+50<= (ptrCurrentPipe->posTop.x) &&
		player.pos.y<ptrCurrentPipe->posTop.y) ||
		(player.pos.x + 50 >= ptrCurrentPipe->posBot.x && player.pos.x + 50 <= (ptrCurrentPipe->posBot.x +100) &&
			player.pos.y >= ptrCurrentPipe->posBot.y)
		
		)
	
	{
		
		isPLaying = false;
		ptrCurrentPipe->isMoving = false;
		ptrNextPipe->isMoving = false;
		isGameOver = true;
	}

	if (isCrossed == false && player.pos.x+10> ptrCurrentPipe->posTop.x)
	{
		player.iScore++;
		isCrossed = true;
	}



	if (IsKeyPressed(KEY_P) && isPLaying == false)
	{
		isPLaying = true;
		isGameOver = false;
		player.Reset();
		pipe1.StartMoving();
		pipe1.GenerateRandomGap(SCREEN_WIDTH + 300);
		pipe2.StopMoving();
		ptrCurrentPipe = &pipe1;
		ptrNextPipe = &pipe2;
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
	if (isGameOver)
	{
		DrawText("GAME OVER !!", SCREEN_WIDTH * 0.09f, SCREEN_HEIGHT * 0.45f, 100, RED);
		DrawText("Press 'P' to Fly Again !", SCREEN_WIDTH * 0.16f, SCREEN_HEIGHT *0.54f, 50, DARKPURPLE);
		
	}

	//Debugger
	DrawCircle(pipe1.posTop.x - 100, pipe1.posTop.y, 5, BLUE);
	DrawCircle(pipe1.posTop.x, pipe1.posTop.y, 5, RED);

	DrawCircle(pipe2.posTop.x, pipe2.posTop.y, 5, RED);
	DrawCircle(pipe2.posTop.x-100, pipe2.posTop.y, 5, BLUE);

	DrawCircle(pipe1.posBot.x, pipe1.posBot.y, 5, BLUE);
	DrawCircle(pipe1.posBot.x+100, pipe1.posBot.y, 5,  RED);
	DrawCircle(pipe2.posBot.x, pipe2.posBot.y, 5, BLUE);
	DrawCircle(pipe2.posBot.x + 100, pipe2.posBot.y, 5,  RED);


	DrawCircle(player.pos.x, player.pos.y, 10, GREEN);
	DrawCircle(player.pos.x+50,player.pos.y, 10, DARKGREEN);

	DrawCircle(player.pos.x, player.pos.y+50, 10, PURPLE);
	DrawCircle(player.pos.x + 50, player.pos.y+50, 10, DARKPURPLE);
}

void Game::Shutdown()
{
	player.Cleanup();
}
