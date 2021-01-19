#include "stdafx.h"
#include "tankScene.h"


tankScene::tankScene()
{
}


tankScene::~tankScene()
{
}

HRESULT tankScene::init()
{
	_tankMap = new tankMap;
	_tankMap->init();

	_tank = new tank;
	_tank->init();
	_tank->setTankMapMemoryAddressLink(_tankMap);

	return S_OK;
}

void tankScene::release()
{
}

void tankScene::update()
{
	_tank->update();
}

void tankScene::render()
{
	_tankMap->render();
	_tank->render();
}
