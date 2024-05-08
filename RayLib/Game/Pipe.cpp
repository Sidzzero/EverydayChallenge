#include "Pipe.h"

Pipe::Pipe()
{
	Image img= LoadImage("assets\\sprites\\pipe-green.png");
	texPipeTop = LoadTextureFromImage(img);

	UnloadImage(img);
	
	GenerateRandomGap(SCREEN_WIDTH);
}

void Pipe::Draw()
{
	//	//DrawTextureEx(texPipe, Vector2{ 100,yTop }, 180, PLAYER_SCALE, RAYWHITE);//L-100  - top
	//DrawTextureEx(texPipe, Vector2{ 0,yBot }, 0, PLAYER_SCALE, RAYWHITE);//500 L-700 bottom
	DrawTextureEx(texPipeTop, posTop, 180, PLAYER_SCALE, RAYWHITE);//L-100  - top
	DrawTextureEx(texPipeTop, posBot, 0, PLAYER_SCALE, RAYWHITE);//500 L-700 bottom
}

void Pipe::Update()
{
	if (isMoving == false)
	{
		return;
	}
	posTop.x -= 180.0f * GetFrameTime();
	posBot.x -= 180.0f * GetFrameTime();
}

void Pipe::Cleanup()
{

}

void Pipe::Reset()
{

}

void Pipe::GenerateRandomGap(float a_xPos)
{
	posTop.x = a_xPos;
	posBot.x = a_xPos-104;

	posTop.y = GetRandomValue(100, 700);
	posBot.y = GetRandomValue(posTop.y + 500, 500);
	
}

void Pipe::StartMoving()
{
	isMoving = true;
	GenerateRandomGap(SCREEN_WIDTH);
}

void Pipe::StopMoving()
{
	isMoving = false;
	GenerateRandomGap(SCREEN_WIDTH*5);
}
