// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"
#include <raymath.h>
#include <vector>


struct Shape
{
public:
    std::vector<Vector2> vertices;
    float radius = 10.0f;
    Color col;
    bool bDrawLine = false;
    void Draw()
    {
        for (int i=0;i<vertices.size();i++)
        {
            DrawCircleV(vertices[i], radius, col);
            if (i>=1 && bDrawLine)
            {
                DrawLineV(vertices[i], vertices[i-1],RAYWHITE);
            }
        }
        if(bDrawLine)
        DrawLineV(vertices[vertices.size()-1], vertices[0], ORANGE);
    }

    void UpdatePos(int index,Vector2 newPos)
    {
        if (index <0 || vertices.empty() || index>=vertices.size())
        {
            return;
        }
        vertices[index] = newPos;
    }

    void AddVertice(Vector2 newVertex)
    {
        vertices.push_back(newVertex);
    }
};

struct RigidBod2
{
public:
    Vector2 pos = Vector2{400 , 0};
    Vector2 accel = Vector2{0,9.8f};
    Vector2 velocity = Vector2{0,0};
    void Update(float currentFrameDelta)
    {
         auto tempAccel = Vector2{ accel.x * currentFrameDelta,accel.y * currentFrameDelta };
        velocity = Vector2Add(velocity, tempAccel);
         auto tempVector = Vector2{ velocity.x * currentFrameDelta,velocity.y * currentFrameDelta };
         pos = Vector2Add(pos, tempVector);
    }
};
class World
{
public:
    Shape mouseShap;
    Shape boxShape;
    RigidBod2 boxRigid;
    
    World()
    {
        mouseShap.AddVertice(Vector2{0,0});

        boxShape.AddVertice(Vector2{ 100,100 });
        boxShape.AddVertice(Vector2{ 100,200 });
        boxShape.AddVertice(Vector2{ 200,200 });
        boxShape.AddVertice(Vector2{ 200,100 });
        boxShape.col = DARKBLUE;
        boxShape.bDrawLine = true;
    }
    void Draw() 
    {
        mouseShap.Draw();
        boxShape.Draw();
        DrawCircleV(boxRigid.pos, 30, BROWN);
        
    }
    void Update()
    {
        m_currentFrame = GetFrameTime();
        m_currentMousePos = GetMousePosition();
        mouseShap.UpdatePos(0, m_currentMousePos);
        boxRigid.Update(m_currentFrame);


    }
private:
    float m_currentFrame = 0;
    Vector2 m_currentMousePos = {0,0};
};


int main(void)
{
    InitWindow(800, 450, "Simulation PLayground- powered by Raylib");
    World world;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        
        world.Update();
        world.Draw();

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
