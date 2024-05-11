// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"
#include <raymath.h>
#include <vector>
struct RigidBod2
{
public:
    Vector2 pos = Vector2{ 400 , 0 };
    Vector2 accel = Vector2{ 0,9.8f };
    Vector2 velocity = Vector2{ 0,0 };
    float mass = 1;
    void Update(float currentFrameDelta)
    {
        auto tempAccel = Vector2{ accel.x * currentFrameDelta,accel.y * currentFrameDelta };
        velocity = Vector2Add(velocity, tempAccel);
        auto tempVector = Vector2{ velocity.x * currentFrameDelta/ mass,velocity.y * currentFrameDelta/ mass };
        pos = Vector2Add(pos, tempVector);
    }

    void UpdatePos(Vector2 a_pos)
    {
        pos = a_pos;
    }
};

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
struct ShapeWithRigid
{
public:
    std::vector<RigidBod2> vertices;
    float radius = 10.0f;
    Color col;
    bool bDrawLine = false;
    void Draw()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            DrawCircleV(vertices[i].pos, radius, col);
            if (i >= 1 && bDrawLine)
            {
                DrawLineV(vertices[i].pos, vertices[i - 1].pos, RAYWHITE);
            }
        }
        if (bDrawLine)
            DrawLineV(vertices[vertices.size() - 1].pos, vertices[0].pos, ORANGE);
    }
    void Update(float currentFrameDelta)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            vertices[i].Update(currentFrameDelta);
        }
    }
    void AddVertexAtIndex(int index, Vector2 newPos)
    {
        if (index < 0 || vertices.empty() || index >= vertices.size())
        {
            return;
        }
        vertices[index].pos = newPos;
    }

    void AddVertice(Vector2 newVertex)
    {
        auto tempRigid = RigidBod2{};
        tempRigid.pos = newVertex;
        vertices.push_back(tempRigid);
    }
};

class World
{
public:
    Shape mouseShap;
    //Shape boxShape;
    RigidBod2 ballRigid;

    ShapeWithRigid boxWithRigid;
    
    World()
    {
        mouseShap.AddVertice(Vector2{0,0});

        boxWithRigid.AddVertice(Vector2{ 100,100 });
        boxWithRigid.AddVertice(Vector2{ 100,200 });
        boxWithRigid.AddVertice(Vector2{ 200,200 });
        boxWithRigid.AddVertice(Vector2{ 200,100 });
        boxWithRigid.col = DARKBLUE;
        boxWithRigid.bDrawLine = true;
      
    }
    void Draw() 
    {
        mouseShap.Draw();
        DrawCircleV(ballRigid.pos, 30, BROWN);

        boxWithRigid.Draw();
        
    }
    void Update()
    {
        m_currentFrame = GetFrameTime();
        m_currentMousePos = GetMousePosition();
        mouseShap.UpdatePos(0, m_currentMousePos);
        ballRigid.Update(m_currentFrame);
        boxWithRigid.Update(m_currentFrame);
       

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
