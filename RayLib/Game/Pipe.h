#pragma once
#include "Common.h"
class Pipe :Object
{
public :
	Vector2 posTop;
	Vector2 posBot;
	Texture texPipeTop;
	bool isMoving = false;

	Pipe();

	void Draw();
	void Update();
	void Cleanup();
	void Reset();

	void GenerateRandomGap(float a_startPos);
	void StartMoving();
	void StopMoving();
};

