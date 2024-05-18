#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "raylib.h"

const int  ROW = 20;
const int COLUMN = 20;
const int CELL_SIZE = 30;
const float OFFSET_X = 50; const float OFFSET_Y = 25;
const float WAIT_TIME = 0.25f;

struct Position
{
public :
	int x;
	int y;
};

