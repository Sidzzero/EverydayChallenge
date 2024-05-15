#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(Texture2D a_texture, Rectangle a_rectangles[], int a_numberOfFrames, float a_fps)
{
	texture = a_texture;
	for (int i=0;i<a_numberOfFrames;i++)
	{
		rectangles.push_back(a_rectangles[i]);
	}
	numberOfFrames = a_numberOfFrames;
	fps = a_fps;
}

SpriteAnimation::~SpriteAnimation()
{
	UnloadTexture(texture);
}

void SpriteAnimation::Draw(float currentTime,Rectangle &destination, Vector2 orgin, float rotation, Color color)
{
	int temp_iCurrentFrame =(int) (currentTime * fps) % numberOfFrames;
	DrawTexturePro(texture, rectangles[temp_iCurrentFrame], destination, orgin, rotation, color);
}
void SpriteAnimation::DrawIndex(int frameIndex, Rectangle &destination, Vector2 orgin, float rotation, Color color)
{
	DrawTexturePro(texture, rectangles[frameIndex], destination, orgin,rotation,color);
}