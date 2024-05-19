#pragma once
#include "Common.h"
#include "BlockColor.h"
#include "Block.h"

class Grid
{
public :
	int grids[20][10];//Holds the color 
	int iScore = 0;
	std::vector<Block> blocks;
	Block currentBLock;
	Block nextBLock;

	void Initialize();
	void Draw();
	void Update();
	void MoveCurrentLeft();
	void MoveCurrentRight();
	void MoveCurrentDown();
	void RotatecwCurrent();
	void RotateccwCurrent();
	void FallBlocks();
	bool CheckIfOutSide();
	bool CheckCellNotFree();
	void LockInBlock();
	Block GetRandomBlock();

	void ChecAndClearRows();
	Grid();

private:
	int numRows = 20;
	int numCols = 10;
	int cellSize = 30 ;
	float elaspedSinceLast = 0;
	float waitTime = WAIT_TIME;
	void ShiftAllRows(int a_iRowStart, int a_Count);
	void ClearRow(int a_iRow);
	std::vector<Color> blockColors;



};

