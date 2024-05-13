#pragma once
#include <iostream>
#include "raylib.h"
#include <raymath.h>
#include <vector>
#include <string>
bool GetClosestPointOnRay(Vector2 a, Vector2 b, Vector2 point, float& u);
bool IsPointOnLine(Vector2 a, Vector2 b, Vector2 point);
Vector2 GetPointOnTwoVector(Vector2 a, Vector2 b, float t);
bool findIntersectionBetweenSegements(const Vector2& A, const Vector2& B, const Vector2& V1, const Vector2& V2, Vector2& intersection);
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

		DrawLineEx(pointMass[i].pos, pointMass[temp_iNextIndex].pos, 5.0f, BLUE);
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
	   ( Vector2{rect.x+rect.width+25.0f,rect.y}, 
		tempMousePos);
	float dotMouseCorner = Vector2DotProduct(rectCornerToMouse, Vector2{ 1.0f,0 });
	Vector2 adjustedMouseToCornerPointEnd = Vector2Add
	(tempMousePos,
		Vector2Scale(Vector2{ 1.0f,0 }, dotMouseCorner)
	);
	DrawLineV(tempMousePos, adjustedMouseToCornerPointEnd, YELLOW);//Mouse Cutter RAY

	DrawLineV(Vector2{ rect.x + rect.width + 25.0f,rect.y },
		Vector2Add(Vector2{ rect.x + rect.width + 25.0f,rect.y+5.0f },
		Vector2Scale(Vector2{0,1},500)),
		YELLOW);//CUT LINE HORIZONTAL
	int countForPoints = 0;
	int countForSide = 0;
	float v = -1;
	Vector2 intersectionPoint = Vector2{ 0,0 };
	for (int i = 0; i < pointMass.size(); i++)
     //for (int i = 2; i <= 2; i++)
	{
		DrawText((std::to_string(i)).c_str(),
			pointMass[i].pos.x + 15,
			pointMass[i].pos.y,
			20,
			YELLOW);
		int temp_iNextIndex = i + 1;
		if (i == pointMass.size() - 1)
		{
			temp_iNextIndex = 0;
		}
		float u = -500;
		
		if (findIntersectionBetweenSegements
		(pointMass[i].pos,
		pointMass[temp_iNextIndex].pos,
			tempMousePos,
			adjustedMouseToCornerPointEnd, intersectionPoint)
			)
		{
			countForSide++;
		}
		DrawCircleLinesV(intersectionPoint, 15, WHITE);
		DrawText( (std::to_string(i)+"<->"+ std::to_string(temp_iNextIndex)).c_str(), 
			intersectionPoint.x + 25,
			intersectionPoint.y, 
			20,
			WHITE);
		
	}
	if (countForSide%2==0)
	{
		DrawText("OUTSIDE of Polygon", GetScreenWidth() * 0.30f, GetScreenHeight() * 0.80f, 50, RED);
	}
	else
	{
		DrawText("INSIDE of Polygon",GetScreenWidth()*0.30f, GetScreenHeight() * 0.80f, 50, GREEN);

	}
	// std::cout << "countForPoints:" << countForPoints << ",countForSide" << countForSide << "," << v << std::endl;
	 std::cout <<",countForSide" << countForSide<<","<< intersectionPoint.x<<"," << intersectionPoint.y<< std::endl;
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

bool IsPointOnLine(Vector2 a, Vector2 b, Vector2 point)
{
	float aTOPoint = Vector2Distance(a, point);
	float pointTOB = Vector2Distance(point, b);
	float atoB = Vector2Distance(a,b);

	float TotalWithPoint = aTOPoint + pointTOB;
	std::string temp_text = "atoB:" + std::to_string(atoB);
	temp_text = temp_text.substr(0, temp_text.find(".") + 3);

	std::string temp_text1 = "aTOPoint:" + std::to_string(aTOPoint);
	temp_text1 = temp_text1.substr(0, temp_text1.find(".") + 3);
	std::string temp_text2 = "pointTOB:" + std::to_string(pointTOB);
	temp_text2 = temp_text2.substr(0, temp_text2.find(".") + 3);

	DrawText(temp_text.c_str(), GetMousePosition().x, GetMousePosition().y + 25, 25, GREEN);
	DrawText(temp_text1.c_str(), GetMousePosition().x, GetMousePosition().y + 50, 25, GREEN);
	DrawText(temp_text2.c_str(), GetMousePosition().x, GetMousePosition().y + 75, 25, GREEN);

	DrawLineV(a, point, BROWN);
	DrawCircleLinesV(a, 25, DARKBROWN);
	DrawCircleLinesV(b, 25, DARKBROWN);
	DrawCircleV(point, 25, BROWN);
	
	if ( abs(atoB - TotalWithPoint) >=0.0f && abs(atoB - TotalWithPoint)<=0.001f)
	{
		return true;
	}
	return false;
}

Vector2 GetPointOnTwoVector(Vector2 a, Vector2 b, float t)
{
	Vector2 sub = Vector2Subtract(b,a);
	Vector2 Scale = Vector2Scale(sub, t);
	Vector2 endPoint = Vector2Add(a, Scale);
	return endPoint;

}

/// <summary>
/// Finds Segements intersection
/// </summary>
bool findIntersectionBetweenSegements(const Vector2& A, const Vector2& B, const Vector2& V1, const Vector2& V2, Vector2& intersection)
{
	DrawCircleLinesV(A, 15, WHITE);
	DrawCircleLinesV(B, 15, WHITE);
	DrawCircleLinesV(V1, 15, WHITE);
	DrawCircleLinesV(V2,15,WHITE);
	// Calculate the components of vectors B - A and V2 - V1
	double dx1 = B.x - A.x;
	double dy1 = B.y - A.y;
	double dx2 = V2.x - V1.x;
	double dy2 = V2.y - V1.y;

	// Calculate the determinant
	double determinant = (-dx1 * dy2) + (dy1 * dx2);

	// Check if the line segments are parallel
	if (determinant == 0) {
		// Line segments are parallel or collinear, no intersection
		intersection = Vector2{ 10, 10+B.y }; // Return some default value to indicate no intersection
	
		return false;
	}

	// Calculate the values of t and u
	double t = ((V1.y - A.y) * dx2 - (V1.x - A.x) * dy2) / determinant;
	double u = -((V1.y - A.y) * -dx1 + (V1.x - A.x) * dy1) / determinant;

	// Check if both t and u are within the range [0, 1]
	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
		// Calculate the intersection point
		 ;
		intersection.x = A.x + t * dx1;
		intersection.y = A.y + t * dy1;
		intersection = intersection;
		//DrawText(std::to_string(i).c_str(), intersectionPoint.x + 25, intersectionPoint.y, 20, WHITE);
		DrawText(std::to_string(t).c_str(), intersection.x + 35, intersection.y+25, 20, GREEN);
		DrawText(std::to_string(u).c_str(), intersection.x + 35, intersection.y+55, 20, GREEN);
	
		return true;
	}
	else {
		// No intersection within the line segments
		intersection = Vector2{ 10,10 + B.y }; // Return some default value to indicate no intersection
		 ;
		intersection.x = A.x + t * dx1;
		intersection.y = A.y + t * dy1;
		intersection = intersection;
		DrawText(std::to_string(t).c_str(), intersection.x + 35, intersection.y+25, 25, RED);
		DrawText(std::to_string(u).c_str(), intersection.x + 35, intersection.y+55, 25, RED);
		return false;
	}
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
	cubespoint.push_back(Vector2{ 300,300 });
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
