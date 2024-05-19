// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common.h"
#include "SpriteAnimation.h"
#include "GAme.h"
int main(void)
{
    InitWindow(20*CELL_SIZE + CELL_SIZE + 55, 
        10*CELL_SIZE + CELL_SIZE+400, 
        "Tetris Game- powered by RAYLIB");

    Image knightImg = LoadImage("assets/images/Knight_Idle.png");
    Image knightRunImg = LoadImage("assets/images/Knight_Run.png");

    Texture2D temp = LoadTextureFromImage(knightImg);
    
    Rectangle rectanglesTemp[] = 
    {
        {0,0 ,589,709},
        {589,0 ,589,709},
        {589 * 2,0 ,589,709},
        {589 * 3,0 ,589,709},
        {589 * 4,0 ,589,709},
        {589 * 5,0 ,589,709},
        {589 * 6,0 ,589,709},
        {589 * 8,0 ,589,709},
        {589 * 9,0 ,589,709},
        {589 *10,0 ,589,709},

    };
    SpriteAnimation knightSprite(temp, rectanglesTemp, 10, 15);
    temp = LoadTextureFromImage(knightRunImg);
    SpriteAnimation knightRunningSprite(temp, rectanglesTemp, 10, 15);
    auto tempKnightRect = Rectangle{ 0,80,512,709 };
    auto tempKnightRunRect = Rectangle{ 520,80,512,709 };

    InitAudioDevice();
    
   
    SetTargetFPS(60);
    GAme tetris;
    tetris.Start();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),DARKPURPLE);
        DrawRectangle(GetScreenWidth() * 0.65, 0, GetScreenHeight() * 0.65, GetScreenHeight(), DARKBLUE);

        DrawRectangle(GetScreenWidth() * 0.68, GetScreenHeight() * .10,
                     GetScreenWidth()*.45 * 0.65, GetScreenHeight()*0.15, BLUE);

        DrawText("SCORE", GetScreenWidth() * 0.76, GetScreenHeight() * .11, 25, YELLOW);
        DrawText(std::to_string(tetris.GetCurrentGridScore()).c_str(), GetScreenWidth() * 0.75, GetScreenHeight() * .15, 55, DARKGRAY);


    
        DrawRectangle(GetScreenWidth() * 0.68,
            GetScreenHeight() * .40,
            GetScreenWidth() * .45 * 0.65,
            GetScreenHeight() * 0.30,
            DARKGRAY);
        DrawText("Next Block:", GetScreenWidth() * 0.72,
            GetScreenHeight() * .42,
            25, YELLOW);
        tetris.DrawNextUI(GetScreenWidth() * 0.68, GetScreenHeight() * .40 + 10);

       
        tetris.Update();
        tetris.Draw();

        EndDrawing();
    }
    CloseAudioDevice();
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


