#pragma once
#include "raylib.h"
#include "raymath.h"
#include <deque>
#include <vector>
#include <string>

class Object
{
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Cleanup() = 0;
	virtual void Reset()= 0;

};
