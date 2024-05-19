#pragma once 
//LAZY TO RENAmE
#include "Common.h"
#include "Grid.h"

typedef enum State{Playing, MainMenu, Setting};




class GAme
{
public:
	State currentState = State::Playing;
	~GAme();
	

	void Start();
	void Draw();
	void Update();
	void Shutdown();
	int GetCurrentGridScore();
	void DrawNextUI(float a_x, float a_y);

private:
	Grid grid;
	Music fxBgMusic;
	void OnPlayingState();


};




