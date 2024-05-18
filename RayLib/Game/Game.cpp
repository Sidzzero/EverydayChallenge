#include "GAme.h"

void GAme::Start()
{
	grid.Initialize();
}

void GAme::Draw()
{
	grid.Draw();
}

void GAme::Update()
{
	auto currentKeyPressed = GetKeyPressed();
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
		grid.RotateccwCurrent();
	}
}
void GAme::OnPlayingState()
{

}

void GAme::Shutdown()
{
}
