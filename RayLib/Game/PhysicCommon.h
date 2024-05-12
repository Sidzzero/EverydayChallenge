#pragma once
#include <iostream>
#include "raylib.h"
#include <raymath.h>
#include <vector>
#include <string>
bool GetClosestPointOnRay(Vector2 a, Vector2 b, Vector2 point, float& u);
struct PointMass
{
public:
	Vector2 pos;
	Vector2 accel;
	Vector2 velocity;
	
	float mass = 1.0f;
	Color color = Color{ GREEN };

};

//Polygon--------------------
struct Polygon
{
public :
	std::vector<PointMass> pointMass;
	void Draw();
	void Update(float frameDelta);
	void CheckCollsion(PointMass a_pointMass);
	Rectangle CreateBoundBox();

};

void Polygon::Draw()
{
	for (int i = 0; i < pointMass.size(); i++)
	{
		int temp_iNextIndex = i + 1;
		if (i==pointMass.size()-1)
		{
			temp_iNextIndex = 0;
		}

		DrawLineEx(pointMass[i].pos, pointMass[temp_iNextIndex].pos, 5.0f, WHITE);
	}
}

void Polygon::Update(float frameDelta)
{
	return;
	for (int i=0;i<pointMass.size();i++)
	{
		auto tempAccel = Vector2Scale(pointMass[i].accel, frameDelta);
		pointMass[i].velocity = Vector2Add(pointMass[i].velocity, tempAccel);
		auto NewVector = Vector2Scale(pointMass[i].velocity,frameDelta/ pointMass[i].mass);
		pointMass[i].pos = Vector2Add(pointMass[i].pos,NewVector);
	}

}

void Polygon::CheckCollsion(PointMass a_pointMass)
{
	Rectangle rect = CreateBoundBox();

	auto tempMousePos = GetMousePosition();
	Vector2 rectCornerToMouse = Vector2Subtract
	   ( Vector2{rect.x+rect.width+15.0f,rect.y}, 
		tempMousePos);
	float dotMouseCorner = Vector2DotProduct(rectCornerToMouse, Vector2{ 1.0f,0 });
	Vector2 adjustedMouseToCornerPointEnd = Vector2Add
	(tempMousePos,
		Vector2Scale(Vector2{ 1.0f,0 }, dotMouseCorner)
	);
	DrawLineV(tempMousePos, adjustedMouseToCornerPointEnd, YELLOW);//Mouse Cutter RAY

	DrawLineV(Vector2{ rect.x + rect.width + 15.0f,rect.y },
		Vector2Add(Vector2{ rect.x + rect.width + 15.0f,rect.y+5.0f },
		Vector2Scale(Vector2{0,1},500)),
		YELLOW);//CUT LINE HORIZONTAL
	int count = 0;
	for (int i = 0; i < pointMass.size(); i++)
   //  for (int i = 1; i <= 1; i++)
	{
		int temp_iNextIndex = i + 1;
		if (i == pointMass.size() - 1)
		{
			temp_iNextIndex = 0;
		}
		float u = -500;
		//Check only with mouse ray
		if (GetClosestPointOnRay(tempMousePos, adjustedMouseToCornerPointEnd,pointMass[i].pos,u))
		{
			if(u>=0 && u<=0.99f)
			count++;
			
		}
		
	}
	std::cout << count << std::endl;
}
Rectangle Polygon::CreateBoundBox()
{
	std::vector<Vector2> points;
	for (int i=0;i< pointMass.size();i++)
	{
		points.push_back(pointMass[i].pos);
	}
	//find the min /max X and Y and create a box out of it bro
	float Xmin = INT_MAX, XMax = INT_MIN, Ymin = INT_MAX, Ymax = INT_MIN;
	for (int i = 0; i < points.size(); i++)
	{
		Vector2 current = points[i];
		if (Xmin > current.x)
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
	result.width = XMax - Xmin;
	result.height = Ymax - Ymin;

	return result;

}

bool GetClosestPointOnRay(Vector2 a, Vector2 b, Vector2 point,float &u)
{
	u = -5000;
	double dx1 = b.x - a.x;
	double dy1 = b.y - a.y;
	double dx2 = point.x - a.x;
	double dy2 = point.y - a.y;

	// Calculate the squared magnitude of vector B - A
	double magnitudeSquared = dx1 * dx1 + dy1 * dy1;
	if (magnitudeSquared == 0)
	{
		return false;
	}
	// Calculate the dot product (point - A) dot (B - A)
	double dotProduct = dx2 * dx1 + dy2 * dy1;

	u = dotProduct / magnitudeSquared;
	return true;
}
//END------Polygon--------------------
//PHYSIC WORLD--------------------
class PhysicWorld
{
public:
	Polygon polygon;
	PointMass mousePos;
	
	void Setup();
	void Draw();
	void Update();


};
void PhysicWorld::Setup()
{
	std::vector<Vector2> cubespoint;
	cubespoint.push_back(Vector2{ 100,100 });
	cubespoint.push_back(Vector2{ 500,100 });
	cubespoint.push_back(Vector2{ 500,500 });
	cubespoint.push_back(Vector2{ 100,500 });

	for (int i=0;i<cubespoint.size();i++)
	{
		PointMass temp;
		temp.pos = cubespoint[i];
		temp.accel = Vector2{ 0,9.8f };
		temp.velocity = Vector2{ 0,0 };
		polygon.pointMass.push_back(temp);
	}

}
void PhysicWorld::Update()
{
	mousePos.pos = GetMousePosition();
	auto temp = GetFrameTime();
	//polygon.Update(temp);// DISABLED THE MOPVEMENT
	polygon.CheckCollsion(mousePos);
}
void PhysicWorld::Draw()
{
	polygon.Draw();
	DrawCircleV(mousePos.pos, 10.0f, ORANGE);

}
// END-------PHYSIC WORLD--------------------
