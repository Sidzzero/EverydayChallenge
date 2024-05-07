// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"
#include<deque>
#include <raymath.h>
#include <iostream>

const int CELL_SIZE = 30;
const int CELL_COUNT = 25;

Color green = { 174,204,94,255 };
Color darkGreen = {43,50,22,255};

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}
class Snake
{
public:
    std::deque<Vector2> body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
    Vector2 direction = Vector2{ 0,0 };
    bool isGrowing = false;
    Snake()
    {
       body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
  
        direction = Vector2{ 1,0 };
    }
    ~Snake()
    {

    }
    void Update()
    {
        body.push_front(Vector2Add(body[0], direction));
        if (isGrowing == false)
        {
            body.pop_back();
         
        }
        else
        {
            isGrowing = false; //poping required
        }
      
    }
    void Draw()
    {
        for (int i=0;i<body.size();i++)
        {
         //   DrawRectangleRounded(body[i].x * CELL_SIZE, body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, darkGreen);
           // DrawRectangleRounded(Rectangle{ body[i].x * CELL_SIZE, body[i].y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE },0.5,6, darkGreen);
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{  x * CELL_SIZE, y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE };
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
            //DrawRectangle(body[i].x * CELL_SIZE, body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, darkGreen);
        }
    }
};

class Food
{
public :
    Vector2 position = {1,1};
    Food(std::deque<Vector2> snakeBody)
    {
        Image img = LoadImage("Graphics/food.png");
        tex = LoadTextureFromImage(img);
        SpawnAtRandomPosition(snakeBody);
        UnloadImage(img);
    }
    ~Food()
    {
        UnloadTexture(tex);
    }

    void Update()
    {

    }
    void Draw()
    {
        DrawTexture(tex,position.x * CELL_SIZE,position.y * CELL_SIZE,RAYWHITE);
        DrawRectangle(position.x * CELL_SIZE, position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RAYWHITE);
    }
    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, CELL_COUNT - 1);
        float y = GetRandomValue(0, CELL_COUNT - 1);
        return Vector2{ x, y };
    }
    Vector2  SpawnAtRandomPosition(std::deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateRandomCell();
        while (ElementInDeque(position, snakeBody))
        {
            position = GenerateRandomCell();
        }
        return position;
    }
private: 
    Texture tex;
};
class Game
{
public:
    bool isPlaying = false;
    int iScore = 0;
    Snake snake;
    Food food = { snake.body };
    Game()
    {
       
    }
    ~Game()
    {
        
    }
    void Start()
    {
        isPlaying = true;
        iScore = 0;
        food.SpawnAtRandomPosition(snake.body);
    }
    void Update()
    {
        float currentTime = GetFrameTime();
        food.Update();
        ElaspedWaitTime += currentTime;
        if (IsKeyPressed(KEY_UP) && snake.direction.y !=1 )
        {
            snake.direction = Vector2{ 0,-1 };
        }
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
        {
            snake.direction = Vector2{ 0,1 };
        }
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
        {
            snake.direction = Vector2{ -1,0 };
        }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
        {
            snake.direction = Vector2{ 1,0 };
        }
        if (ElaspedWaitTime> snakeMoveWait)
        {
         snake.Update();
         ElaspedWaitTime = 0;
         //Collison
//Snake and Wall

//Snake and Food
         CheckCollisionWithFood();
         //Snake and Self
        }


    }
    void Draw()
    {
        food.Draw();
        snake.Draw();
    }
    void ShutDown()
    {

    }
    void CheckCollisionWithFood()
    {
        std::cout<< snake.body[0].x<<"=="<<food.position.x<<"|||"<< snake.body[0].y<<"=="<<food.position.y<<std::endl;
        if (Vector2Equals(snake.body[0],food.position))
        {
            food.SpawnAtRandomPosition(snake.body);
            snake.isGrowing = true;
            std::cout << "CheckCollisionWithFood !";
        }
    }
private:
    float snakeMoveWait = 0.2f;
    float ElaspedWaitTime = 0;
};

int main(void)
{
    InitWindow(CELL_SIZE*CELL_COUNT, CELL_SIZE * CELL_COUNT, "RL_Snake-powered by Raylib");
    Game snakeGame;
    snakeGame.Start();
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(green);
        //DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
        snakeGame.Update();
        snakeGame.Draw();
        EndDrawing();
    }
    snakeGame.ShutDown();
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
