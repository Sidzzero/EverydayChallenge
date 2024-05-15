#pragma once
#include "Common.h"
class SpriteAnimation
{
public:
	Texture2D texture;
	std::vector<Rectangle> rectangles;
	int numberOfFrames = 0;
	float fps;

	SpriteAnimation(Texture2D texture, Rectangle  a_rectangles[], int a_numberOfFrames, float a_fps);
	~SpriteAnimation();
	 
	void Draw(float currentTime, Rectangle &destination,Vector2 orgin, float rotation, Color color);
	void DrawIndex(int frameIndex, Rectangle &destination, Vector2 orgin, float rotation, Color color);


};

