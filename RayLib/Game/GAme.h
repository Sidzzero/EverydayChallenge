#pragma once 
//LAZY TO RENAmE
#include "Common.h"
#include "Grid.h"

typedef enum State{Playing, MainMenu, Setting};




class GAme
{
public:
	State currentState = State::Playing;
	
	

	void Start();
	void Draw();
	void Update();
	void Shutdown();
	int GetCurrentGridScore();
private:
	Grid grid;
	void OnPlayingState();

};




