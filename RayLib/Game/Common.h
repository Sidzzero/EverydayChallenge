#pragma once
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
        auto tempVector = Vector2{ velocity.x * currentFrameDelta / mass,velocity.y * currentFrameDelta / mass };
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
        for (int i = 0; i < vertices.size(); i++)
        {
            DrawCircleV(vertices[i], radius, col);
            if (i >= 1 && bDrawLine)
            {
                DrawLineV(vertices[i], vertices[i - 1], RAYWHITE);
            }
        }
        if (bDrawLine)
            DrawLineV(vertices[vertices.size() - 1], vertices[0], ORANGE);
    }

    void UpdatePos(int index, Vector2 newPos)
    {
        if (index < 0 || vertices.empty() || index >= vertices.size())
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

    std::vector<Vector2> GetAllVertice()
    {
        std::vector<Vector2> temp;
        for (int i = 0; i < vertices.size(); i++)
        {
            temp.push_back(vertices[i].pos);
        }
        return temp;
    }
};

Rectangle CreateBoundBox(std::vector<Vector2> polgygons)
{
    //find the min /max X and Y and create a box out of it bro
    float Xmin =INT_MAX, XMax = INT_MIN, Ymin = INT_MAX, Ymax= INT_MIN;
    for (int i=0;i< polgygons.size();i++)
    {
        Vector2 current = polgygons[i];
        if (Xmin>current.x)
        {
            Xmin = current.x;
        }
        if (Ymin > current.y)
        {
            Ymin = current.y;
        }
        if (XMax < current.x)
        {
            XMax = current.x;
        }
        if (Ymax < current.y)
        {
            Ymax = current.y;
        }
    }
    Rectangle result;
    result.x = Xmin;
    result.y = Ymin;
    result.width =  XMax-Xmin;
    result.height =  Ymax - Ymin;

    return result;

}

Vector2 ClosestPointOnBoundingBox(Vector2 point , std::vector<Vector2>& polygon)
{
    Vector2 closesPoint = { INT_MAX,INT_MAX };
    //Error of sigle point check and min 3 point a.k.a triangle
    Vector2 nextPoint = Vector2{ 0,0 };
    Vector2 currentPoint = Vector2{ 0,0 };
    for (int i=0;i<polygon.size();i+=2)
    {
        currentPoint = polygon[i];
        if (i==polygon.size()-1)//last point
        {
            nextPoint = polygon[0];
        }
        else
        {
            nextPoint = polygon[i + 1];
        }

    }
    return closesPoint;
}

class World
{
public:
    Shape mouseShap;
    //Shape boxShape;
    RigidBod2 ballRigid;

    ShapeWithRigid boxWithRigid;

    World()
    {
        mouseShap.AddVertice(Vector2{ 0,0 });

        boxWithRigid.AddVertice(Vector2{ 100,100 });
        boxWithRigid.AddVertice(Vector2{ 100,200 });
        boxWithRigid.AddVertice(Vector2{ 200,200 });
        boxWithRigid.AddVertice(Vector2{ 200,100 });
       // boxWithRigid.AddVertice(Vector2{ 200,30 });
        boxWithRigid.col = DARKBLUE;
        boxWithRigid.bDrawLine = true;

    }
    void Draw()
    {
        mouseShap.Draw();
        DrawCircleV(ballRigid.pos, 30, BROWN);

        boxWithRigid.Draw();

        auto tempBox = boxWithRigid.GetAllVertice();
        DrawRectangleLinesEx(CreateBoundBox(tempBox),1.0f, YELLOW);
        DrawCircleLinesV(ClosestPointOnBoundingBox(m_currentMousePos, tempBox), 10.0f, PURPLE);
        

    }
    void Update()
    {
        m_currentFrame = GetFrameTime();
        m_currentMousePos = GetMousePosition();
        mouseShap.UpdatePos(0, m_currentMousePos);
         
        ballRigid.Update(m_currentFrame);
       // boxWithRigid.Update(m_currentFrame);


    }
private:
    float m_currentFrame = 0;
    Vector2 m_currentMousePos = { 0,0 };
};