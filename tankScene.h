#pragma once
#include "gameNode.h"
#include "tank.h"
#include "tankMap.h"

class tankScene : public gameNode
{
private:
	tankMap* _tankMap;
	tank* _tank;

public:
	tankScene();
	~tankScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

