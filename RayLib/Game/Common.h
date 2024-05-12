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

    bool GetIntersectionWithSegement(Vector2 &a, Vector2 &b,Vector2 &pointToTest,Vector2 &closedPoint)
    {
       
        float u = -1;
       
        double dx1 = b.x - a.x;
        double dy1 = b.y - a.y;
        double dx2 = pointToTest.x - a.x;
        double dy2 = pointToTest.y - a.y;

        // Calculate the dot product (point - A) dot (B - A)
        double dotProduct = dx2 * dx1 + dy2 * dy1;

        // Calculate the squared magnitude of vector B - A
        double magnitudeSquared = dx1 * dx1 + dy1 * dy1;
        u = dotProduct / magnitudeSquared;
        DrawText(std::to_string(u).c_str(), pos.x, pos.y + 60, 50, WHITE);
        if (u>=0 && u<=1.0f)
        {
           
            closedPoint = Vector2Add
            (a,
             Vector2Scale(Vector2Subtract(b, a), u));
            return true;
        }

        return false;
    }

};

bool IsPresentInBoundBox(Vector2 a, Vector2 b, std::vector<Vector2> &vertices)
{
    int iCount = 0;
   // Vector2 segement = Vector2Subtract(b,a);
    for (int i = 0; i < vertices.size(); i++)
   // for (int i=1;i<=1;i++)
    {
        float u = -1;

        double dx1 = b.x - a.x;
        double dy1 = b.y - a.y;
        double dx2 = vertices[i].x - a.x;
        double dy2 = vertices[i].y - a.y;

        // Calculate the squared magnitude of vector B - A
        double magnitudeSquared = dx1 * dx1 + dy1 * dy1;
        if (magnitudeSquared == 0)
        {
            return false;
        }
        // Calculate the dot product (point - A) dot (B - A)
        double dotProduct = dx2 * dx1 + dy2 * dy1;

        u = dotProduct / magnitudeSquared;
       auto temp = Vector2Add
        (a,Vector2Scale(Vector2Subtract(b, a), u));
       DrawCircleLinesV(temp,10,DARKGREEN);
        if (u<0 || u>1)
        {
            continue;
        }
        iCount++;
    }
    std::cout<<"iCount?" <<(iCount)<< std::endl;
    return (iCount > 0) && iCount % 2 != 0;
}

bool IsPresentInBoundBox2(Vector2 a, Vector2 b, std::vector<Vector2>& vertices)
{
    int iCount = 0;
    // Vector2 segement = Vector2Subtract(b,a);
    std::vector<std::pair<int,int>> segemetns;
    float u = -1;
    float dotABp2p1 = 0;
   // for (int i = 0; i < vertices.size(); i++)
        for (int i=2;i<=2;i++)
    {
 

        double dx1 = b.x - a.x;
        double dy1 = b.y - a.y;
        double dx2 = vertices[i].x - a.x;
        double dy2 = vertices[i].y - a.y;

        // Calculate the squared magnitude of vector B - A
        double magnitudeSquared = dx1 * dx1 + dy1 * dy1;
        if (magnitudeSquared == 0)
        {
            return false;
        }
        // Calculate the dot product (point - A) dot (B - A)
        double dotProduct = dx2 * dx1 + dy2 * dy1;

        u = dotProduct / magnitudeSquared;
        auto temp = Vector2Add
        (a, Vector2Scale(Vector2Subtract(b, a), u));
        DrawCircleLinesV(temp, 10, DARKGREEN);
     
        if (u < 0 || u>1)
        {
            continue;
        }
       
       Vector2 diffAB = Vector2Subtract(b,a);
       diffAB = Vector2Normalize(diffAB);
       Vector2 ABpoint = Vector2Add(a, Vector2Scale(diffAB, u));
       ABpoint = Vector2Scale(diffAB, u);
       int nextINdex = i + 1;
       if (i== vertices.size()-1)//last
       {
           nextINdex = 0;
       }
       Vector2 p2p1 = Vector2Subtract(vertices[nextINdex],vertices[i]);
        dotABp2p1 = Vector2DotProduct
       (
           Vector2Subtract(ABpoint,vertices[i]),
           p2p1
       );
       if (dotABp2p1>=0 && dotABp2p1<=1)
       {
           segemetns.push_back(std::pair<int,int>{i, nextINdex});
           iCount++;
       }
    
    }
    std::string result = std::string{ "" };
    std::string first = std::string{ "" };
    std::string second = std::string{""};
    
    for (int i=0;i<segemetns.size();i++)
    {
        first = std::to_string(segemetns[i].first);
        second = std::to_string(segemetns[i].second);
        result = result+ (first + "->" + second+",");
    }
    result = result + +",Size:"+std::to_string(segemetns.size())
        +",dotABp2p1:"
        +
        std::to_string( dotABp2p1)
    +
        ",U:"
        +
        std::to_string(u);
    std::cout << "iCount?" << (iCount) <<",Frames:" << result << std::endl;
    return (iCount > 0) && iCount % 2 != 0;
}
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
        auto tempVector = Vector2{ 
            velocity.x * currentFrameDelta / mass,
            velocity.y * currentFrameDelta / mass };
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
    Vector2 redPoint = Vector2{ rectBox.x + rectBox.width  + 30.0f  ,rectBox.y + rectBox.height / 2};
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
        point,Vector2{1,0}
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

    //Check first 
    auto tempCCollid = IsPresentInBoundBox2(point, Vector2Add(point, tttt), vertices);



    for (int i = 0; i < vertices.size(); i++)
   //  for (int i=1;i<=1;i++)
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
        if (i==1)
        {

         //   DrawLineEx(currentSliceA, currentSliceB, 5.0f, BLUE);
        }
       
       //if (ray2D.GetIntersectionWithSegement(currentSliceA, currentSliceB, point, closesPoint))
        Vector2 currentClosePoint = Vector2{ -11111,-11111 };
        if (ray2D.GetIntersectionWithSegement(currentSliceA, currentSliceB, point, currentClosePoint))
        {
            iCount++;
        }
        if (Vector2Equals(closesPoint,currentClosePoint)>0)
        {
            closesPoint = currentClosePoint;
        }

    }
    if (tempCCollid)
    {
       // a_Result = false;
        a_Result = true;
    }
    else
    {
        a_Result = false;
    }
   // std::cout << " IsInisde?:" << tempCCollid <<": closesPoint:" <<closesPoint.x<<"::"<<closesPoint.y<< std::endl;
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

        boxWithRigid.AddVertice(Vector2{ 100,100 });//0
        boxWithRigid.AddVertice(Vector2{ 100,200 });//1
        boxWithRigid.AddVertice(Vector2{ 200,200 });//2
        boxWithRigid.AddVertice(Vector2{ 200,100 });//3
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