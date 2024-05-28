#pragma once
#include "Common.h"
class Ship
{
public:
	int iHealth = 3;

	float speed = 25.0f;
	float angle = 0;
	Vector2 pos = Vector2{250,250};
	Vector2 velocity;
	Vector2 acel = Vector2{0,0.0f};

	void Update();
	void Draw();
	void Cleanup();

private:
	std::vector<Vector2> points
	{ 
		//TODO: Take in center and circle and build ship?
		Vector2{465,250},
		Vector2{475,200},
		Vector2{485,250},
	
	};

};

