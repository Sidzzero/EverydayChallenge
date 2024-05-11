#pragma once
#include <iostream>
#include "raylib.h"
#include <raymath.h>
#include <vector>
#include <string>



struct Ray2D
{
public:
    Ray2D(Vector2 a_pos, Vector2 a_dir)
    {
        pos = a_pos;
        dir = a_dir;
    }
    Vector2 pos;
    Vector2 dir;

    Vector2 GetPointAtT(float t)
    {
        Vector2 result;
        auto scaledDir = Vector2{ dir.x * t,dir.y * t };
        result = Vector2Add(pos,scaledDir);
        return result;
    }

    bool GetIntersectionWithSegement(Vector2 &a, Vector2 &b,float currentT,Vector2 &closedPoint)
    {
        float distanceAB = Vector2Distance(a,b);
        if (distanceAB<=0.000001f)
        {
            return false;
        }
        auto ScaleDir = GetPointAtT(currentT);

        float topN = (ScaleDir.x - a.x) * (b.x - a.x) + (ScaleDir.y - a.y) * (b.y - a.y);
        float u = topN / distanceAB;
       // DrawLineV( Vector2Add(  pos, Vector2{0,25} ),
          //  Vector2Add(  ScaleDir, Vector2{ 0,25 }),
         //   BROWN);


        if (u>=0 && u<=1.0f)
        {
            closedPoint = Vector2Add(this->pos, Vector2Scale(this->dir,u));
            return true;
        }

        return false;
    }

};
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

Vector2 ClosestPointOnBoundingBox(Vector2 point , Rectangle rectBox,std::vector<Vector2> vertices,bool &a_Result)
{
    Vector2 closesPoint = { INT_MAX,INT_MAX };
    //Error of sigle point check and min 3 point a.k.a triangle
    Vector2 nextPoint = Vector2{ 0,0 };
    Vector2 currentPoint = Vector2{ 0,0 };
    Vector2 redPoint = Vector2{ rectBox.x + rectBox.width + 10.0f,rectBox.y + rectBox.height / 2};
    DrawCircleV(redPoint,4.0f,RED);
    float bluepointDist = Vector2Distance(redPoint, point);
    Vector2 rayDirect = Vector2{1,0};

    
    float pointNearRightBBDistance = Vector2Distance
    (
        Vector2{ rectBox .x + rectBox.width/2 , rectBox.y + rectBox.height},
        redPoint
    );

    //std::cout <<"bluepointDist" << bluepointDist << "\n";
    DrawText( std::to_string(pointNearRightBBDistance).c_str(), point.x, point.y+30, 10, WHITE);
    float distMouseToRightBBDotted = 0;
    distMouseToRightBBDotted = Vector2DotProduct
    (
        Vector2Subtract(redPoint,point)     ,
        Vector2{1,0}
    );

    Ray2D ray2D = Ray2D
    { 
        point,rayDirect
    };
    auto tttt = Vector2Scale(Vector2{ 1,0 }, pointNearRightBBDistance);
    DrawLineV(Vector2Add(point, Vector2{0,40}), 
        Vector2Add( Vector2Add(point, tttt), Vector2{ 0,40 })
        ,
        YELLOW);

    tttt = Vector2Scale(Vector2{ 1,0 }, distMouseToRightBBDotted);
    DrawLineV(point, Vector2Add(point, tttt), BLUE);
    bool isColliding = false;
    int iCount = 0;//keep track of overall collision
    Vector2 currentSliceA = Vector2{ 0,0 };
    Vector2 currentSliceB = Vector2{0,0};
    for (int i=0;i<vertices.size();i+=2)
    {
        currentSliceA = vertices[i];
        if (i == vertices.size()-1)//last point
        {
            currentSliceB = vertices[0];
        }
        else
        {
            currentSliceB = vertices[i + 1];
        }
        if (ray2D.GetIntersectionWithSegement(currentSliceA, currentSliceB, distMouseToRightBBDotted, closesPoint))
        {
            iCount++;
        }

    }
    if (iCount%2==0)
    {
        a_Result = false;
    }
    else
    {
        a_Result = true;
    }
    std::cout << " INterestcCount:" << iCount <<": closesPoint:" <<closesPoint.x<<"::"<<closesPoint.y<< std::endl;
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

        auto tempVertices = boxWithRigid.GetAllVertice();
        auto  tempBox = CreateBoundBox(tempVertices);
        DrawRectangleLinesEx(tempBox,1.0f, YELLOW);
        bool Colide = false;
        auto tempCCollid = ClosestPointOnBoundingBox(m_currentMousePos, tempBox, tempVertices, Colide);
        if (Colide)
        {
            DrawCircleLinesV(tempCCollid, 30.0f, GREEN);
        }
        else
        {
            DrawCircleLinesV(m_currentMousePos, 30.0f, RED);
        }
        
        

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