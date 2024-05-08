#include "Player.h"


Player::Player(Vector2 a_pos, const char* ImagePath)
{
	//Load Image
	//Image img = LoadImage("assets\sprites\bluebird-downflap.png");
	Image img = LoadImage(ImagePath);
	tex = LoadTextureFromImage(img);
	
	UnloadImage(img);
	pos = a_pos;

}

void Player::Draw()
{
	//DrawTexture(tex, pos.x, pos.y, RAYWHITE);
	DrawTextureEx(tex, pos, 0, 2.0f, RAYWHITE);
}

 void Player::Update()
 {

 }

 void Player::Reset()
 {
	 pos = Vector2{50,50};
	 accel = Vector2{ 0,1 };
	 speed = 10;
 }

 void Player::Cleanup()
 {
	 UnloadTexture(tex);
 }