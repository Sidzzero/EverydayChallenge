#include "Ship.h"
#include <string>


void Ship::Update()
{
	auto timeElasped = GetFrameTime();
	
	if (IsKeyDown(KEY_UP))
	{
			acel.y -= 100.0f;
	}
	else
	{
		if(acel.y<0)
		acel.y += 40 ;
		else
			acel.y = 0.0f; // Ensure it resets properly
	}



	if(IsKeyDown(KEY_LEFT))
	{
		angle -= 5 * timeElasped;
		
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		angle += 5 * timeElasped;
	}
	

	velocity.x = -cos(DEG2RAD * angle)* acel.y * timeElasped;
	velocity.y = -sin(DEG2RAD * angle)* acel.y * timeElasped;
	DrawText(std::to_string(velocity.x).c_str(), 10, 10, 5, WHITE);
	DrawText( std::to_string(velocity.y).c_str(), 10, 20, 5, WHITE);
	//velocity.x += acel.x * timeElasped;
	//velocity.y += acel.y * timeElasped;

	pos.x += velocity.x * timeElasped;
	pos.y += velocity.y * timeElasped;

	for (auto& shipPos : points)
	{
		shipPos.x += velocity.x * timeElasped;
		shipPos.y += velocity.y * timeElasped;
	}
}

std::vector<Vector2> transformed;
void Ship::Draw()
{
	DrawCircleGradient(pos.x, pos.y, 25, GREEN, RED);
	//DrawCircleV(pos, 25, GREEN);
	//DrawTriangle(points[0],points[1],points[2],RAYWHITE);
	//DrawLineV(points[0], points[1], RAYWHITE);
	//DrawLineV(points[1], points[2], RAYWHITE);
	//DrawLineV(points[2], points[0],RAYWHITE);

	DrawPoly(pos, 3, 25, angle, RAYWHITE);
	Vector2 endpoint = Vector2Scale(Vector2{ 1,0 }, 50);
	endpoint = Vector2Add(pos, endpoint);
	endpoint = Vector2Rotate (Vector2Subtract(endpoint,pos),angle );
	endpoint = Vector2Add(pos, endpoint);
	DrawLineEx(pos, endpoint, 5, RED);


}


void Ship::Cleanup()
{
}
