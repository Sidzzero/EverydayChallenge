// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"
#include <string>
#include <vector>
#include<ctime>

const int screenWidth = 500;
const int screenHeight = 600;


struct Player
{
    Rectangle rect;
    float velocity = 250.0f;
    int score = 0;
    float w = 75.0f;
    float h = 10.0f;
};

struct Ball
{
    Vector2 pos;
    Vector2 accel{1.0f,1.0f};//direction
    float velocity;
    float radius = 5.0f;
};

struct Brick
{
    Rectangle rect;
    Color color;
    float w = 50.0f, h = 20.0f;
};

Texture2D texBackGround;
Player player;
Ball ball;
std::vector<Brick> bricks;

Sound fxBRickHit[2];
Sound fxPaddleHit;

void GameStartup()
{
    //Load BG
    Image imgBackground = LoadImage("assets/background.png");
    texBackGround = LoadTextureFromImage(imgBackground);
    UnloadImage(imgBackground);;

    //Load player data
    player.rect = Rectangle{ 250.0f,540.0f, player.w,player.h };
    player.score = 0;

    //Load Ball
    ball.pos = Vector2{ 300,300 };
    ball.velocity = 300.0f;

    std::vector<Color> COLORS{RED, ORANGE, BROWN, PURPLE, PINK, MAGENTA,DARKGREEN,DARKGRAY};
    //load bricks
    Brick newBrick;
    for (int i=0;i<8;i++) //Width is 500  and wdith of brick is (50++++++50) 400/50 = 8
    {
        for (int j=0;j<8;j++)
        {
            newBrick.rect = Rectangle
            {
            float(40+ (i*55)),
            float (50 + (j*26)),
            newBrick.w,
            newBrick.h
            };
            newBrick.color = COLORS[rand()%COLORS.size()];
            bricks.push_back(newBrick);
        }

    }

    //SOUND
    fxBRickHit[0] = LoadSound("assets/brick-hit-1.wav");
    fxBRickHit[1] = LoadSound("assets/brick-hit-2.wav");
    fxPaddleHit = LoadSound("assets/paddle-hit-1.wav");
}

void GameUpdate()
{
    float frameTime = GetFrameTime();
    //Player Postion
    if (IsKeyDown(KEY_LEFT))
    {
        player.rect.x -= player.velocity * frameTime;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player.rect.x += player.velocity * frameTime;
    }

    //Ball
    ball.pos.x = ball.pos.x + (ball.velocity * ball.accel.x) * frameTime;
    ball.pos.y = ball.pos.y + (ball.velocity * ball.accel.y) * frameTime;


    //Check ball and wall
    Brick brick;
    for (int i=0;i<bricks.size();i++)
    {
        brick = bricks[i];
        if (CheckCollisionCircleRec(ball.pos, ball.radius,brick.rect))
        {
            ball.accel.y *= -1;
            bricks.erase(bricks.begin() + i);
            player.score+=10;
            PlaySound(fxBRickHit[rand()%2]);
            ball.velocity += (ball.velocity*0.7f * frameTime);
            break;
        }
    }

    //Ball collsion with wall
    if (ball.pos.x>screenWidth || ball.pos.x<10)
    {
        ball.accel.x *= -1;
    }
    if (ball.pos.y > screenHeight || ball.pos.y < 10)
    {
        ball.accel.y *= -1;
    }


    //ball and player
    if (CheckCollisionCircleRec(ball.pos,ball.radius,player.rect))
    {
        ball.accel.x *= -1;
        ball.accel.y *= -1;
        PlaySound(fxPaddleHit);

    }
    //Check if reach screen
    if (player.rect.x<0)
    {
        player.rect.x = 0;
    }
    if (player.rect.x > (screenWidth - player.rect.width))
    {
        player.rect.x = screenWidth - player.rect.width;
    }

}
void GameRender()
{
    //BG
    DrawTexture(texBackGround,0,0,RAYWHITE);

    //Bricks
    Brick brick;
    for (int i=0;i<bricks.size();i++)
    {
        brick = bricks[i];
        DrawRectangle(brick.rect.x , brick.rect.y,brick.w,brick.h,brick.color);
    }

    //BALL
    DrawCircle(ball.pos.x, ball.pos.y, ball.radius, RAYWHITE);

    //PLAYER
    DrawRectangle(player.rect.x, player.rect.y, player.w, player.h, YELLOW);

    //Draw Text
    std::string sScore = ("Score:" + std::to_string(player.score));
    DrawText(sScore.c_str(), 10, 10, 30, YELLOW);
}
void GameShutdown()
{
    UnloadSound(fxBRickHit[0]);
    UnloadSound(fxBRickHit[1]);
    UnloadSound(fxPaddleHit);
    UnloadTexture(texBackGround);
    CloseAudioDevice();
}


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Breakout :: powered byRaylib  !");
    InitAudioDevice();
    srand(time(NULL));
    SetTargetFPS(60);
    GameStartup();
    while (!WindowShouldClose())
    {
        GameUpdate();
        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawText("Welcome to Breakout", 0, 0, 20, YELLOW);
        GameRender();
       
        std::string fps = std::to_string(GetFPS());
        DrawText(fps.c_str(), screenWidth - 80, 0, 30, GREEN);
        EndDrawing();
    }
    GameShutdown();
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
