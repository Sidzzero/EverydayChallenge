#include "Grid.h"



void Grid::Initialize()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	blockColors = GetBlockColors();
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grids[i][j] = 0;
		}

	}

	blocks = { LBLock{}, JBLock {},IBLock{},OBLock{},SBLock{},TBLock{}, ZBLock{} };

	currentBLock = GetRandomBlock();
	nextBLock = GetRandomBlock();
	std::cout << "ROW:" << numRows << ",COL:" << numCols << "\n";

	/*
	for (int j = 0; j < numCols; j++)
	{
		grids[ROW - 1][j] = 1;
		grids[ROW - 2][j] = 4;
	}
	grids[ROW - 3][4] = 6;
	*/

}

void Grid::Draw()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			DrawRectangle(j * CELL_SIZE + 10 + OFFSET_X, i * CELL_SIZE + 10 + OFFSET_Y, cellSize - 1, cellSize - 1, blockColors[grids[i][j]]);
		}

	}

	currentBLock.Draw();
	if (bFull)
	{
		DrawRectangle(GetScreenWidth() / 9.f, GetScreenHeight() / 2,550,100,DARKBROWN);
		DrawText("Game Over", GetScreenWidth() / 8.0f, GetScreenHeight() / 2, 100, RED);
	}
}
int tempCurrentINdex = 0;
void Grid::Update()
{
	if (bFull)
	{
		return;
	}
	//Make the current block fall or accept movement
	//TESTING
	if (IsKeyPressed(KEY_G))
	{
		tempCurrentINdex++;
		tempCurrentINdex = tempCurrentINdex < blocks.size() ? tempCurrentINdex : 0;
		currentBLock = blocks[tempCurrentINdex];
	}

	if (IsKeyPressed(KEY_C))
	{
		ChecAndClearRows();
	}
	FallBlocks();
}

void Grid::MoveCurrentLeft()
{
	//currentBLock.x--;
	currentBLock.Move(-1, 0);
	if (CheckIfOutSide() == true || CheckCellNotFree() == true)
	{
		currentBLock.Move(1, 0);
	}
}


void Grid::MoveCurrentRight()
{
	//currentBLock.x++;
	currentBLock.Move(1, 0);
	if (CheckIfOutSide() == true || CheckCellNotFree() == true)
	{
		currentBLock.Move(-1, 0);
	}
}

void Grid::MoveCurrentDown()
{
	//currentBLock.y++;
	currentBLock.Move(0, 1);
	if (CheckIfOutSide() == true || CheckCellNotFree() == true)
	{
		currentBLock.Move(0, -1);
		LockInBlock();
	}
	else
	{
		iScore++;
	}

}

void Grid::RotatecwCurrent()
{
	currentBLock.rotation++;
	if (currentBLock.rotation >= currentBLock.rotationMap.size())//TODO: Make it like a clamp and move it to block logic?
	{
		currentBLock.rotation = 0;
	}
	if (CheckIfOutSide() || CheckCellNotFree() == true)
	{
		RotateccwCurrent();
	}
}

void Grid::RotateccwCurrent()
{
	currentBLock.rotation--;
	if (currentBLock.rotation < 0)
	{
		currentBLock.rotation = currentBLock.rotationMap.size() - 1;
	}
	if (CheckIfOutSide() || CheckCellNotFree() == true)
	{
		RotatecwCurrent();
	}
}

void Grid::FallBlocks()
{
	elaspedSinceLast += 1.0f * GetFrameTime();
	if (elaspedSinceLast > waitTime)
	{
		elaspedSinceLast = 0;
		MoveCurrentDown();
	}
}

bool Grid::CheckIfOutSide()
{
	auto CurrentBlocksPos = currentBLock.GetCurrentPositions();
	for (auto pos : CurrentBlocksPos)
	{
		if (pos.x < 0 || pos.y < 0 || pos.x >= numCols || pos.y >= numRows)
		{
			std::cout <<"OUTSIDE" << "\n";
			return true;
		}
	}

	return false;;
}

bool Grid::CheckCellNotFree()
{
	auto CurrentBlocksPos = currentBLock.GetCurrentPositions();
	for (auto pos : CurrentBlocksPos)
	{
		if (grids[pos.y][pos.x] != 0)
		{
			std::cout << "NOT FREE" << "\n";
			return true;
		}
	}
	return  false;
}

void Grid::LockInBlock()
{
	auto CurrentBlocksPos = currentBLock.GetCurrentPositions();
	for (auto pos : CurrentBlocksPos)
	{
		std::cout << pos.x << ":" << pos.y << "\n";
		grids[pos.y][pos.x] = currentBLock.id;
	}

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			std::cout << (grids[i][j]);
			std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout << "Before" << currentBLock.id << ":" << nextBLock.id << "\n";
	currentBLock = nextBLock;
	if (nextBLock.id != 0)
	{
		nextBLock = GetRandomBlock();//Simple random giver but maybe random list each time?
	}std::cout << "After" << currentBLock.id << ":" << nextBLock.id << "\n";
	ChecAndClearRows();
	if (CheckCellNotFree() == true)
	{
		bFull = true;
	}
	
}




Block Grid::GetRandomBlock()
{
	int temp_iRand = GetRandomValue(0, blocks.size() - 1);
	temp_iRand = 3;
	std::cout << "Random Block Generated with ID:!" << temp_iRand << "\n";
	return blocks[temp_iRand];
}

void Grid::ChecAndClearRows()
{
	int temp_CountClearedRows = 0;
	int temp_RowStartNotEmpty = -1;
	int i, j;
	for ( i = ROW - 1; i >= 0; i--)
	{
		temp_RowStartNotEmpty = i;
		bool bFoundEmpty = false;
		for ( j = 0; j < COLUMN; j++)
		{
			if (grids[i][j] == 0)
			{
				bFoundEmpty = true;
				break;
			}
		}
		if (bFoundEmpty == false)
		{
			for (int k = 0; k < COLUMN; k++)
			{
				grids[i][k] = 0;
			}
			temp_CountClearedRows++;
		}
		else
		{
			break;
		}
	}
	if (temp_CountClearedRows > 0)
	{
		ShiftAllRows(i,temp_CountClearedRows);
	}
}

void Grid::ShiftAllRows(int a_iRowStart , int a_Count)
{
	for (int i = a_iRowStart; i >= 0; i--)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			grids[i + a_Count][j] = grids[i][j];
			grids[i][j] = 0;
		}
		iScore += 100;
	}

}

void Grid::ClearRow(int a_iRow)
{
	for (int j = 0; j < COLUMN; j++)
	{
		grids[a_iRow][j] = 0;
	}
}

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	std::cout << "construct!\n";
}


