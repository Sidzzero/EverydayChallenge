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
	DrawTextureEx(tex, pos, 0, PLAYER_SCALE, RAYWHITE);
	DrawText(std::string{ std::to_string(iScore)}.c_str(), SCREEN_WIDTH / 2, 0, 100, YELLOW);
}

 void Player::Update()
 {
	 if (GetKeyPressed() == KEY_SPACE)
	 {
		 velocity = Vector2{0,-UpForce };
	 }
	 velocity = Vector2Add(velocity, Vector2{ accel.x * GetFrameTime(), accel.y * GetFrameTime() });
	 pos = Vector2Add(pos, Vector2{ velocity.x * GetFrameTime(), velocity.y * GetFrameTime() });
	 std::cout << velocity.y <<std::endl;
 }

 void Player::Reset()
 {
	 pos = Vector2{ 180,400 };
	  accel = Vector2{ 0,1500 };
	  velocity = Vector2{ 0,400 };
	  UpForce = 600;
	  iScore = 0;
 }
 void Player::Cleanup()
 {
	 UnloadTexture(tex);
 }