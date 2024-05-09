// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common.h"

Vector2 GetGridPosition(Vector2 a_mousePos)
{
    Vector2 result={-5,-5};
    //starting offset to offset + grid+col

    //Out of Grid location
    if (a_mousePos.x< START_POINT || 
        a_mousePos.y<START_POINT ||
        a_mousePos.x>START_POINT+GRID_SIZE*COLUMN ||
        a_mousePos.y>START_POINT+GRID_SIZE*ROW)
    {
        return Vector2{-1,-1};
    }
    result.x = floor((a_mousePos.x / ( GRID_SIZE * COLUMN) )/(1.0f/COLUMN));
    result.y = floor(a_mousePos.y / (GRID_SIZE * ROW) / (1.0f/ROW)) ;

    return result;
}

std::string VectorToString(Vector2 a_Vector)
{
    return std::string{ std::to_string(a_Vector.x)+":"+ std::to_string(a_Vector.y) };
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_WIDTH, "RL_Minesweeper - powered by RAYLIB");
    std::string strMousePos;
    Vector2 mousePos;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        mousePos = GetMousePosition();

       
        for (int i=0;i<ROW;i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                //DrawRectangle(0,0,GRID_SIZE,GRID_SIZE,RED);
                DrawRectangleRounded(
                    Rectangle{START_POINT +(float)j*GRID_SIZE,
                    START_POINT + (float)i*GRID_SIZE,
                    GRID_SIZE,
                    GRID_SIZE}, 0.5f, 6, RED);
            }
        }
        strMousePos = std::to_string(mousePos.x) + "," + std::to_string(mousePos.y);;
        DrawCircleV(mousePos, 10, BLUE);
        DrawText(("MousePos:" + VectorToString(mousePos)).c_str(), 0, 300, 20, BLACK);
        DrawText(("GRID_POS:" + VectorToString(GetGridPosition(mousePos))).c_str(), 0, 400, 20, BLACK);
       
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
