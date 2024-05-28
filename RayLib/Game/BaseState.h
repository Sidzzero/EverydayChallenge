#pragma once
#include "Common.h"


class BaseState
{
public:
	BaseState();
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

};

