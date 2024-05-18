#include "Grid.h"



void Grid::Initialize()
{
	numRows = 11;
	numCols = COLUMN;
	cellSize = CELL_SIZE;
	blockColors = GetBlockColors();
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grids[i][j] = 0;
		}

	}
}

void Grid::Draw()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			DrawRectangle(i*CELL_SIZE+10+OFFSET_X, j * CELL_SIZE+10 + OFFSET_Y, cellSize-1, cellSize-1, blockColors[grids[i][j]]);
		}

	}
}

Grid::Grid()
{
	std::cout <<"construct!\n";
}


