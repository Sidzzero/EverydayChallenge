#pragma once 
//LAZY TO RENAmE
#include "Common.h"
#include "Grid.h"

typedef enum State{Playing, MainMenu, Setting};




class GAme
{
public:
	State currentState = State::Playing;
	int iScore = 0;
	

	void Start();
	void Draw();
	void Update();
	void Shutdown();
private:
	//Grid grid;
	void OnPlayingState();

};




