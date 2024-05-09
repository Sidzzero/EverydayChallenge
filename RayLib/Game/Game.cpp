// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common.h"
#include <unordered_set>
#include <utility> // for std::pair
#include <random>


Vector2 GetGridPosition(Vector2 a_mousePos)
{
    Vector2 result = { -5,-5 };
    //starting offset to offset + grid+col

    //Out of Grid location
    if (a_mousePos.x< START_POINT ||
        a_mousePos.y<START_POINT ||
        a_mousePos.x>START_POINT + GRID_SIZE * COLUMN ||
        a_mousePos.y>START_POINT + GRID_SIZE * ROW)
    {
        return Vector2{ -1,-1 };
    }
    result.x = floor(  (a_mousePos.x / (GRID_SIZE * COLUMN)) / (1.0f / COLUMN) );
    result.y = floor(a_mousePos.y / (GRID_SIZE * ROW) / (1.0f / ROW));

    return result;
}

std::string VectorToString(Vector2 a_Vector)
{
    return std::string{ std::to_string(a_Vector.x) + ":" + std::to_string(a_Vector.y) };
}


Color BOMB = RED;
Color UNOPENED = BLUE;
Color CLOSE_TO_BOMB = ORANGE;
Color OPEN = YELLOW;



struct Cell
{
public:
    Color col = Color{BLUE};
    bool isBomb = false;
    int iNumberOfNearBombs = 0;
    void SetAsBomb()
    {
        iNumberOfNearBombs = 0;
        isBomb = true;
        col = UNOPENED;
    }
    void Reset()
    {
        iNumberOfNearBombs = 0;
        col = UNOPENED;
        isBomb = false;
    }
};

bool IsPressedABomb(Cell (&grid)[ROW][ROW], int x, int y)
{
    return grid[x][y].isBomb;
}

void CheckNeightbourForBombAndUpdate(Cell(&grid)[ROW][ROW], int x, int y)
{
    if (x<0 || y<0 || x>=ROW || y>=ROW)
    {
        return;
    }
    if (ColorIsEqual( grid[x][y].col , CLOSE_TO_BOMB)  ||
        ColorIsEqual(grid[x][y].col, BOMB)||
        ColorIsEqual(grid[x][y].col, OPEN))
    {    
        return;
   }
    grid[x][y].col = OPEN;
    if (x - 1 >= 0 && y - 1 >= 0)
    {
        //grid[x - 1][y - 1].col = OPEN;
        if (grid[x - 1][y - 1].isBomb)
        {
            grid[x - 1][y - 1].col = BOMB;
            grid[x][y].iNumberOfNearBombs++;
        }
       // else
       // CheckNeightbourForBombAndUpdate(grid, x-1,y-1);
    }
    if (y - 1 >= 0)
    {
       // grid[x][y - 1].col = OPEN;
        if (grid[x][y - 1].isBomb)
        {
            grid[x][y - 1].col = BOMB;
            grid[x][y].iNumberOfNearBombs++;
        }
       // else
       // CheckNeightbourForBombAndUpdate(grid, x , y - 1);
    }
    if (x + 1 < ROW && y - 1 >= 0)
    {
       // grid[x + 1][y - 1].col = OPEN;
        if (grid[x + 1][y - 1].isBomb)
        {
            grid[x + 1][y - 1].col = BOMB;
            grid[x][y].iNumberOfNearBombs++;
        }
       // else
       // CheckNeightbourForBombAndUpdate(grid, x+1, y - 1);
    }
    if (x - 1 >= 0)
    {
      //  grid[x - 1][y].col = OPEN;
        if (grid[x - 1][y].isBomb)
        {
            grid[x - 1][y].col = BOMB;
            grid[x][y].iNumberOfNearBombs++;
        }
       // else
       // CheckNeightbourForBombAndUpdate(grid, x - 1, y );
    }
    if (x + 1 < ROW)
    {
      //  grid[x + 1][y].col = OPEN;
        if (grid[x + 1][y].isBomb)
        {
            grid[x + 1][y].col = BOMB;
            grid[x][y].iNumberOfNearBombs++;
        }
        //else
       // CheckNeightbourForBombAndUpdate(grid, x + 1, y);
    }
    if (x - 1 >= 0 && y + 1 < ROW)
    {
       // grid[x - 1][y + 1].col = OPEN;
        if (grid[x - 1][y + 1].isBomb)
        {
            grid[x - 1][y + 1].col = BOMB;
            grid[x][y].iNumberOfNearBombs++;
        }
       // else
      //  CheckNeightbourForBombAndUpdate(grid, x - 1, y+1);
    }
    if (y + 1 < ROW)
    {
       // grid[x][y + 1].col = OPEN;
        if (grid[x][y + 1].isBomb)
        {
            grid[x][y + 1].col = BOMB;
            grid[x][y].iNumberOfNearBombs++;
        }
        //else
      //  CheckNeightbourForBombAndUpdate(grid, x , y + 1);
    }
    if (x + 1 < ROW && y + 1 < ROW)
    {
       // grid[x + 1][y + 1].col = OPEN;
        if (grid[x + 1][y + 1].isBomb)
        {
            grid[x + 1][y + 1].col = BOMB;
            grid[x][y].iNumberOfNearBombs++;
        }
        //else
      //  CheckNeightbourForBombAndUpdate(grid, x+1, y + 1);
    }
    if (grid[x][y].iNumberOfNearBombs>0)
    {
        grid[x][y].col = CLOSE_TO_BOMB;
    }
    else
    {
        CheckNeightbourForBombAndUpdate(grid, x - 1, y - 1);
        CheckNeightbourForBombAndUpdate(grid, x, y - 1);
        CheckNeightbourForBombAndUpdate(grid, x + 1, y - 1);
        CheckNeightbourForBombAndUpdate(grid, x + 1, y);
        CheckNeightbourForBombAndUpdate(grid, x - 1, y + 1);
        CheckNeightbourForBombAndUpdate(grid, x, y + 1);
        CheckNeightbourForBombAndUpdate(grid, x + 1, y + 1);
    }

  
}

void SelectNEighbours(Cell(&grid)[ROW][ROW], int x, int y)
{
    if(x-1>=0 && y-1>=0)
    grid[x - 1][y - 1].col = OPEN;

    if(y-1>=0)
    grid[x ][y - 1].col = OPEN;

    if(x+1<ROW && y-1>=0)
    grid[x+1 ][y-1 ].col = OPEN;

    if (x - 1 >= 0)
    grid[x - 1][y].col = OPEN;

    if (x + 1 < ROW)
    grid[x + 1][y].col = OPEN;

    if (x - 1 >= 0 && y+1<ROW)
    grid[x - 1][y + 1].col = OPEN;

    if ( y + 1 < ROW)
    grid[x][y + 1].col = OPEN;

    if (x+1<ROW &&y + 1 < ROW)
    grid[x+1][y+1].col = OPEN;
}
void UpdateGrid(Cell(&grid)[ROW][ROW] ,int x, int y, std::unordered_set<std::pair<int, int>> & visitedSet)
{
    if (x<0 || y<0 || x>=ROW || y>=ROW)
    {
        return;
    }
  
    int temp_NeightbourBomb = 0;
    if (x-1 >0 && y-1>0)//Exisitngs
    {
        if (grid[x][x].isBomb)
        {
            temp_NeightbourBomb++;
        }
    }
    if (x> 0 && y - 1 > 0)//Exisitngs
    {
        if (grid[x][x].isBomb)
        {
            temp_NeightbourBomb++;
        }
    }
    if (x - 1 > 0 && y  > 0)//Exisitngs
    {
        if (grid[x][x].isBomb)
        {
            temp_NeightbourBomb++;
        }
    }

}

class Game
{
public:
    bool isGameOver = false;
    bool isCheat = false;
    float Timer = 0;
    Cell grid[ROW][COLUMN];
    //std::unordered_set<std::pair<int, int>> visited;

    Game()
    {
    }

    void Startup()
    {

      //  grid[0][1].SetAsBomb();
      //  grid[2][2].SetAsBomb();
      //  grid[1][1].SetAsBomb();
      //  grid[2][3].SetAsBomb();
        GenerateRandomBombCell();
    }
    void Reset()
    {
        isGameOver = false;
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                grid[i][j].isBomb = false;
                grid[i][j].col = UNOPENED;
                grid[i][j].iNumberOfNearBombs = 0;
            }
        }
        GenerateRandomBombCell();
        isCheat = false;
        Timer = 0;
    }

    void GenerateRandomBombCell()
    {
        //TODO: I GOOGLE THIS AND WROTE NO IDEA HOW IT WORKS
        std::vector<std::pair<int, int>> pairs;
        auto numPairs = GetRandomValue(0, ROW * ROW - ROW * ROW * 0.5);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, ROW - 1);

        for (int i = 0; i < numPairs; ++i) {
            int x = dis(gen);
            int y = dis(gen);
            pairs.push_back(std::make_pair(x, y));
        }

        for (int i=0;i<pairs.size();i++)
        {
            grid[pairs[i].first][pairs[i].second].SetAsBomb();
        }

            
    }
    void Update()
    {
        if (isGameOver == false)
        {
            Timer += 1.0f * GetFrameTime();
        }
        mousePos = GetMousePosition();

        if (IsKeyPressed(KEY_R) && isGameOver)
        {
            Reset();
        }
        if (IsKeyPressed(KEY_C)   )
        {
            isCheat = !isCheat;
        }
        //debug
        if (IsMouseButtonPressed(0))
        {
            auto tempGridPos = GetGridPosition(mousePos);
            if (tempGridPos.x != -1 && tempGridPos.y != -1)
            {
               // grid[(int)tempGridPos.y - 1][(int)tempGridPos.x - 1].col = ORANGE;
            }
           // SelectNEighbours(grid, (int)tempGridPos.y - 1, (int)tempGridPos.x - 1);

           // CheckNeightbourForBombAndUpdate(grid, (int)tempGridPos.y - 1, (int)tempGridPos.x - 1);
           
            if (IsPressedABomb(grid, (int)tempGridPos.y -1, (int)tempGridPos.x- 1))
            {
                std::cout<<"BOMB CHECK TRUEEEE"<< std::endl;
               // grid[(int)tempGridPos.y - 1][(int)tempGridPos.x - 1].col = BOMB;
                 isGameOver = true;
                 isCheat = true;
            }
            else
            {
                std::cout << "BOMB CHECK FALSE" << std::endl;

                CheckNeightbourForBombAndUpdate(grid, (int)tempGridPos.y - 1, (int)tempGridPos.x - 1);
                
            }

        }
    }
    std::string tmpstrTime;
    void Draw()
    {
        DrawGrid();
        if (isGameOver)
        {
            DrawText("GAME OVER", GetScreenWidth() *0.25f, GetScreenHeight() * 0.85f, 100, RED);
        }

        tmpstrTime = "Time:" + std::to_string((int)Timer);
        DrawText(tmpstrTime.c_str(), GetScreenWidth() * 0.15f, 0, 40, DARKPURPLE);
        //debug
        strMousePos = std::to_string(mousePos.x) + "," + std::to_string(mousePos.y);;
        DrawCircleV(mousePos, 10, YELLOW);
        DrawText(("MousePos:" + VectorToString(mousePos)).c_str(), 0, GetScreenHeight()*0.1, 20, BLACK);
        auto temp = GetGridPosition(mousePos);
        temp.x -= 1;
        temp.y -= 1;
        DrawText(("GRID_POS:" + VectorToString(temp)).c_str(), 0, GetScreenHeight() * 0.15, 20, BLACK);

     
    }
    void Shutdown()
    {

    }
private:

    std::string strMousePos;
    Vector2 mousePos = Vector2{0,0};

    void DrawGrid()
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                //DrawRectangle(0,0,GRID_SIZE,GRID_SIZE,RED);
                //reverting here
                float xPos = START_POINT + (float)j * GRID_SIZE;
                float yPos = START_POINT + (float)i * GRID_SIZE;
                
                Color actualCol = grid[i][j].col;
                if (isCheat == false && grid[i][j].isBomb)
                {
                    grid[i][j].col = UNOPENED;
                }
                else if ( (isGameOver||isCheat == true) && grid[i][j].isBomb )
                {
                    grid[i][j].col = BOMB;
                }
                    
                DrawRectangleRounded(
                    Rectangle{ xPos,
                    yPos,
                    GRID_SIZE,
                    GRID_SIZE }, 0.5f, 6, grid[i][j].col);
                if (grid[i][j].isBomb && isCheat)
                {
                   // DrawText("BOMBXXXXXX", xPos +GRID_SIZE/3,yPos + GRID_SIZE / 2, 15, RED);
                    DrawText("Bomb", xPos+10,yPos+25,30, BLACK);
                }
                else
                {
                    auto temp = std::to_string(grid[i][j].iNumberOfNearBombs);
                    DrawText(temp.c_str(), xPos + GRID_SIZE / 3, yPos + GRID_SIZE / 2, 15, DARKBROWN);
                }
            }
        }
    }

};



int main(void)
{
   // InitWindow(SCREEN_WIDTH, SCREEN_WIDTH, "RL_Minesweeper - powered by RAYLIB");
    InitWindow(GRID_SIZE*ROW + GRID_SIZE*4, GRID_SIZE * ROW+ GRID_SIZE*4, "RL_Minesweeper - powered by RAYLIB");
    InitAudioDevice();
    Game mineSweeper;
    mineSweeper.Startup();


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        mineSweeper.Update();
        mineSweeper.Draw();
        EndDrawing();
    }
    mineSweeper.Shutdown();
    CloseWindow();

    return 0;
}


