#pragma once
#include "Common.h"
class Player :Object
{
public:
	int iScore = 0;
	Vector2 pos;
	Vector2 accel = Vector2{0,1};
	float speed = 10;
	Texture tex;

	 
	 Player( Vector2 pos,const char *ImagePath);
	 void Draw() ;
	 void Update() ;
	 void Cleanup() ;
	 void Reset() ;

	
};

