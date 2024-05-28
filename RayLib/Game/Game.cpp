// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common.h"
#include "SpriteAnimation.h"
#include "MainGame.h"
#include <string>
int main(void)
{
    InitWindow(1024, 768, "raylib [core] example - basic window");

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

    MainGame asteroid;
    asteroid.Init();
    bool bEnableMousePos = true;
    std::string temp_strMousePos;
    Vector2 mosPos;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

       // DrawText("Congrats! You created your first window!", 80, 80, 40, GREEN);
        if (IsKeyPressed(KEY_KP_1))
        {
            bEnableMousePos = !bEnableMousePos;

        }
        if (bEnableMousePos)
        {
            mosPos = GetMousePosition();
            temp_strMousePos = std::to_string(mosPos.x)+':'+ std::to_string(mosPos.y);
            DrawText(temp_strMousePos.c_str(),GetScreenWidth()*0.75f,0, 30, GREEN);
        }
     //   knightSprite.Draw(GetTime(), tempKnightRect, Vector2{ 0,0 }, 0.0f, WHITE);
     //   knightRunningSprite.Draw(GetTime(), tempKnightRunRect, Vector2{ 0,0 }, 0.0f, WHITE);

        asteroid.Update();
        asteroid.Draw();
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
