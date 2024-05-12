#pragma once
#include <iostream>
#include "raylib.h"
#include <raymath.h>
#include <vector>
#include <string>

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
	std::vector<PointMass> vertices;
	void Draw();
	void Update(float frameDelta);
};

void Polygon::Draw()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		int temp_iNextIndex = i + 1;
		if (i==vertices.size()-1)
		{
			temp_iNextIndex = 0;
		}

		DrawLineEx(vertices[i].pos, vertices[temp_iNextIndex].pos, 5.0f, WHITE);
	}
}

void Polygon::Update(float frameDelta)
{
	for (int i=0;i<vertices.size();i++)
	{
		auto tempAccel = Vector2Scale(vertices[i].accel, frameDelta);
		vertices[i].velocity = Vector2Add(vertices[i].velocity, tempAccel);
		auto NewVector = Vector2Scale(vertices[i].velocity,frameDelta/ vertices[i].mass);
		vertices[i].pos = Vector2Add(vertices[i].pos,NewVector);
	}
}
//END------Polygon--------------------
//PHYSIC WORLD--------------------
class PhysicWorld
{
public:
	Polygon polygon;
	
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
		polygon.vertices.push_back(temp);
	}

}
void PhysicWorld::Update()
{
	auto temp = GetFrameTime();
	polygon.Update(temp);
}
void PhysicWorld::Draw()
{
	polygon.Draw();
}
// END-------PHYSIC WORLD--------------------
