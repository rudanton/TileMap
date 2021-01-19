#pragma once
#include "gameNode.h"
#include "tankMap.h"

enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_UP,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_DOWN
};

class tank : public gameNode
{
private:
	tankMap* _tankMap;
	image* _image;
	float _x, _y;
	float _speed;
	RECT _rc;
	TANKDIRECTION _direction;
	BOOL _move;

	float _width, _height;
	int _tileX, _tileY;
	int _tileIndex[2][2];

	int _frameX, _frameY;

public:
	tank();
	~tank();

	HRESULT init();
	void release();
	void update();
	void render();

	void tankMove();
	void setTankPosition();

	void setTankMapMemoryAddressLink(tankMap* tm) { _tankMap = tm; }
};

