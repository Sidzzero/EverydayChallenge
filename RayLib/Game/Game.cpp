#include "GAme.h"

void GAme::Start()
{
	grid.Initialize();
}

void GAme::Draw()
{
	grid.Draw();
	DrawText("TETRIS CLONE: Coded by SIDZ", GetScreenWidth() * 0.07f, GetScreenHeight() * 0.01f, 25, GREEN);
}

void GAme::Update()
{
	auto currentKeyPressed = GetKeyPressed();
	if (grid.bFull == false)
	{
		if (currentKeyPressed == KEY_LEFT)
		{
			grid.MoveCurrentLeft();
		}
		else if (currentKeyPressed == KEY_RIGHT)
		{
			grid.MoveCurrentRight();
		}
		else if (currentKeyPressed == KEY_UP)
		{
			grid.RotatecwCurrent();
		}
		else if (currentKeyPressed == KEY_DOWN)
		{
			//grid.RotateccwCurrent();
			grid.MoveCurrentDown();
		}
	}
	else
	{
	  //GAME OVER THINGS>>>
	}
	if (currentKeyPressed == KEY_R)
	{
		grid.Initialize();
	}
	grid.Update();
}
void GAme::OnPlayingState()
{

}

void GAme::Shutdown()
{
}

int GAme::GetCurrentGridScore()
{
	return grid.iScore;
}

void GAme::DrawNextUI(float a_x, float a_y)
{
	grid.nextBLock.DrawAt(a_x,a_y);
}
