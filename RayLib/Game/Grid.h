#pragma once
#include "Common.h"
#include "BlockColor.h"

class Grid
{
public :
	int grids[20][10];//Holds the color 
	void Initialize();
	void Draw();
	Grid();

private:
	int numRows = 1;
	int numCols = 1;
	int cellSize ;
	std::vector<Color> blockColors;

};

