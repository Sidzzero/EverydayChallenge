// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common.h"


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
    result.x = floor((a_mousePos.x / (GRID_SIZE * COLUMN)) / (1.0f / COLUMN));
    result.y = floor(a_mousePos.y / (GRID_SIZE * ROW) / (1.0f / ROW));

    return result;
}

std::string VectorToString(Vector2 a_Vector)
{
    return std::string{ std::to_string(a_Vector.x) + ":" + std::to_string(a_Vector.y) };
}

struct Cell
{
public:
    Color col = Color{BLUE};
    bool isBomb = false;
};

class Game
{
public:
    float Timer = 0;
    Cell grid[ROW][COLUMN];

    Game()
    {
    }

    void Startup()
    {
    }
    void Reset()
    {

    }
    void Update()
    {
        mousePos = GetMousePosition();

        //debug
        if (IsMouseButtonPressed(0))
        {
            auto tempGridPos = GetGridPosition(mousePos);
            if (tempGridPos.x != -1 && tempGridPos.y != -1)
            {
                grid[(int)tempGridPos.y - 1][(int)tempGridPos.x - 1].col = RED;
            }
        }
    }
    void Draw()
    {
        DrawGrid();
        //debug
        strMousePos = std::to_string(mousePos.x) + "," + std::to_string(mousePos.y);;
        DrawCircleV(mousePos, 10, YELLOW);
        DrawText(("MousePos:" + VectorToString(mousePos)).c_str(), 0, 300, 20, BLACK);
        DrawText(("GRID_POS:" + VectorToString(GetGridPosition(mousePos))).c_str(), 0, 400, 20, BLACK);
    }
    void Shutdown()
    {

    }
private:

    std::string strMousePos;
    Vector2 mousePos;

    void DrawGrid()
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                //DrawRectangle(0,0,GRID_SIZE,GRID_SIZE,RED);

                DrawRectangleRounded(
                    Rectangle{ START_POINT + (float)j * GRID_SIZE,
                    START_POINT + (float)i * GRID_SIZE,
                    GRID_SIZE,
                    GRID_SIZE }, 0.5f, 6, grid[i][j].col);
            }
        }
    }

};



int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_WIDTH, "RL_Minesweeper - powered by RAYLIB");
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


