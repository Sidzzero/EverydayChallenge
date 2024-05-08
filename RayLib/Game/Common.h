#pragma once
#include "raylib.h"
#include "raymath.h"
#include <deque>
#include <vector>
#include <string>
#include <iostream>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = (512 * 2);

constexpr float PLAYER_SCALE = 2.0f;

class Object
{
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Cleanup() = 0;
	virtual void Reset()= 0;

};
