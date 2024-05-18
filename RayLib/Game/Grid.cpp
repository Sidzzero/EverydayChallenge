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
	std::cout <<"ROW:" << numRows << ",COL:" << numCols<<"\n";
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

	currentBLock.Draw();
}
int tempCurrentINdex = 0;
void Grid::Update()
{
	//Make the current block fall or accept movement
	//TESTING
	if (IsKeyPressed(KEY_G))
	{
		tempCurrentINdex++;
		tempCurrentINdex = tempCurrentINdex < blocks.size() ? tempCurrentINdex:0;
		currentBLock = blocks[tempCurrentINdex];
	}
	FallBlocks();
}

void Grid::MoveCurrentLeft()
{
	//currentBLock.x--;
	currentBLock.Move(-1, 0);
	if (CheckIfOutSide() == true)
	{
		currentBLock.Move(1, 0);
	}
}


void Grid::MoveCurrentRight()
{
	//currentBLock.x++;
	currentBLock.Move(1, 0);
	if (CheckIfOutSide() == true)
	{
		currentBLock.Move(-1, 0);
	}
}

void Grid::MoveCurrentDown()
{
	//currentBLock.y++;
	currentBLock.Move(0, 1);
	if (CheckIfOutSide() == true)
	{
		currentBLock.Move(0, -1);
		LockInBlock();
	}

}

void Grid::RotatecwCurrent()
{
	currentBLock.rotation++;
	if (currentBLock.rotation >= currentBLock.rotationMap.size())//TODO: Make it like a clamp and move it to block logic?
	{
		currentBLock.rotation = 0;
	}
	 if (CheckIfOutSide())
	{
		RotateccwCurrent();
	}
}

void Grid::RotateccwCurrent()
{
	currentBLock.rotation--;
	if (currentBLock.rotation<0)
	{
		currentBLock.rotation = currentBLock.rotationMap.size()-1;
	}
	 if (CheckIfOutSide())
	{
		RotatecwCurrent();
	}
}

void Grid::FallBlocks()
{
	elaspedSinceLast += 1.0f * GetFrameTime();
	if (elaspedSinceLast>waitTime)
	{
		elaspedSinceLast = 0;
		MoveCurrentDown();
    }
}

bool Grid::CheckIfOutSide()
{
	auto CurrentBlocksPos = currentBLock.GetCurrentPositions();
	for (auto pos:CurrentBlocksPos)
	{
		if (pos.x<0 || pos.y<0 || pos.x>=numRows || pos.y>=numCols)
		{
			return true;
		}
	}

	return false;;
}

void Grid::LockInBlock()
{
	auto CurrentBlocksPos = currentBLock.GetCurrentPositions();
	for (auto pos : CurrentBlocksPos)
	{
		std::cout<<pos.x<<":" <<pos.y<< "\n";
		grids[pos.x][pos.y] = currentBLock.id;
	}

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			std::cout << grids[i][j];
			std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout <<"Before" << currentBLock.id << ":" << nextBLock.id << "\n";
	currentBLock = nextBLock;
	nextBLock = GetRandomBlock();//Simple random giver but maybe random list each time?
	std::cout <<"After" << currentBLock.id << ":" << nextBLock.id << "\n";
}

Block Grid::GetRandomBlock()
{
	int temp_iRand = GetRandomValue(0, blocks.size() - 1);
	std::cout << "Random Block Generated with ID:!"<< temp_iRand <<"\n";
	return blocks[temp_iRand];
}

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	std::cout <<"construct!\n";
}


