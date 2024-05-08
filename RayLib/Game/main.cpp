// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "raylib.h"
#include "Common.h"
#include "Game.h"


int main(void)
{   
 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Zlappy Bird - powered by Raylib");
   
    InitAudioDevice();
    Game ZlappyBird(SCREEN_WIDTH, SCREEN_HEIGHT);
    ZlappyBird.StartUp();
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GREEN);
        ZlappyBird.Update();
        ZlappyBird.Draw();
        // DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
        EndDrawing();
    }
    ZlappyBird.Shutdown();
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
