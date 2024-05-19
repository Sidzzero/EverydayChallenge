#include "GAme.h"

GAme::~GAme()
{
	
}

void GAme::Start()
{
	grid.Initialize();
	
	fxBgMusic = LoadMusicStream("assets/sound/music.mp3");

	PlayMusicStream(fxBgMusic);
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
		UpdateMusicStream(fxBgMusic);
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
		StopMusicStream(fxBgMusic);
	}
	if (currentKeyPressed == KEY_R)
	{
		grid.Initialize();
		PlayMusicStream(fxBgMusic);
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
	grid.nextBLock.DrawAt(a_x,a_y,-grid.nextBLock.x, -grid.nextBLock.y);
}
