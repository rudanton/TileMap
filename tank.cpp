#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{
}

HRESULT tank::init()
{
	_direction = TANKDIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 0, 0, 256, 128, 8, 4, true, RGB(255, 0, 255));
	_speed = 100.0f;
	_width = _image->getFrameWidth() - 6;
	_height = _image->getFrameHeight() - 6;
	_move = true;
	return S_OK;
}

void tank::release()
{
}

void tank::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = TANKDIRECTION_LEFT;
		//tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = TANKDIRECTION_RIGHT;
		//tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = TANKDIRECTION_UP;
		//tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = TANKDIRECTION_DOWN;
		//tankMove();
	}
	tankMove();
	
}

void tank::render()
{
	Rectangle(getMemDC(), _rc);
	_image->frameRender(getMemDC(), _rc.left-3, _rc.top-3);

	char str[128];
	sprintf_s(str, "tile  : (%d, %d)", _tileX, _tileY);
	TextOut(getMemDC(), 10, 10, str, strlen(str));

	sprintf_s(str, "(%d, %d)", 
		_tankMap->getTile()[_tileY][_tileX].terrainFrameX,
		_tankMap->getTile()[_tileY][_tileX].terrainFrameY);
	TextOut(getMemDC(), 100, 10, str, strlen(str));

	sprintf_s(str, "(%d, %d)",
		_tankMap->getTile()[_tileY][_tileX].objFrameX,
		_tankMap->getTile()[_tileY][_tileX].objFrameY);
	TextOut(getMemDC(), 100, 30, str, strlen(str));


	sprintf_s(str, "인접타일 : (%d, %d) , (%d, %d)", _tileIndex[0][0], _tileIndex[0][1], _tileIndex[1][0], _tileIndex[1][1]);
	TextOut(getMemDC(), 10, 50, str, strlen(str));


	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			sprintf_s(str, "(%d,%d)", j, i);
			TextOut(getMemDC(), 
				WINSIZEX - (IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * 32,
				i * 32,
				str,strlen(str));
		}
	}
}


void tank::tankMove()
{
	RECT rcCollision;	//임의의 충돌판정용 렉트
	//int tileIndex[2];	//이동방향에 따라 타일속성 검출계산용(몇 바이 몇에 있다)
	//int tileX, tileY;	//실제 탱크가 어느 타일에 위치하는지 계산용(left, top 기준일때)

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;

	switch (_direction)
	{
		case TANKDIRECTION_LEFT:
			_image->setFrameX(0);
			_image->setFrameY(3);

			if(_move)_x -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _width, _height);

		break;
		case TANKDIRECTION_UP:
			_image->setFrameX(0);
			_image->setFrameY(0);

			if (_move)_y -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _width, _height);
		break;
		case TANKDIRECTION_RIGHT:
			_image->setFrameX(0);
			_image->setFrameY(2);

			if (_move)_x += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _width, _height);
		break;
		case TANKDIRECTION_DOWN:
			_image->setFrameX(0);
			_image->setFrameY(1);

			if(_move)_y += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _width, _height);
		break;
	}

	//3.여러분이 조금있다 과제를 하실땐 충돌판정용 렉트를 살짝 깍아주어야 합니다.

	//4. 내 탱크좌표가 몇 번째 타일 인덱스에 있는지 계산을 해주세요
	//ex) tileX = rcCollision.left / TILESIZE
	_tileX = rcCollision.left / TILESIZE;
	_tileY = rcCollision.top / TILESIZE;

	//5.여길 계산하시오 (하일라이뜨)
	switch (_direction)
	{
		case TANKDIRECTION_LEFT:
			if (rcCollision.top / TILESIZE != rcCollision.bottom / TILESIZE)
			{
				if (_tankMap->getTile()[_tileY][_tileX].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCKS) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCKS) _move = false;
				else _move = true;
			}
			else
			{
				if (_tankMap->getTile()[_tileY][_tileX].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCKS) _move = false;
				else _move = true;
			}

			_tileIndex[0][0] = _tileX-1;
			_tileIndex[0][1] = _tileY;
			_tileIndex[1][0] = _tileX-1;
			_tileIndex[1][1] = _tileY + 1;
			//ex) tileIndex[0] = 내 앞 타일
			//ex) tileIndex[1] = 내 앞 타일의 그 옆 타일
		break;
		case TANKDIRECTION_UP:
			if (rcCollision.left / TILESIZE != rcCollision.right / TILESIZE)
			{
				if (_tankMap->getTile()[_tileY][_tileX].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCKS) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCKS) _move = false;
				else _move = true;
			}
			else
			{
				if (_tankMap->getTile()[_tileY][_tileX].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCKS) _move = false;
				else _move = true;
			}

			_tileIndex[0][0] = _tileX;
			_tileIndex[0][1] = _tileY-1;
			_tileIndex[1][0] = _tileX + 1;
			_tileIndex[1][1] = _tileY - 1;
			//ex) tileIndex[0] = 내 앞 타일
			//ex) tileIndex[1] = 내 앞 타일의 그 옆 타일
		break;
		case TANKDIRECTION_RIGHT:
			if (rcCollision.top / TILESIZE != rcCollision.bottom / TILESIZE)
			{
				if (_tankMap->getTile()[_tileY][_tileX + 1].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCKS) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX + 1].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX + 1].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX + 1].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX + 1].obj == OBJ_BLOCKS) _move = false;
				else _move = true;
			}
			else
			{
				if (_tankMap->getTile()[_tileY][_tileX + 1].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY][_tileX + 1].obj == OBJ_BLOCKS) _move = false;
				else _move = true;
			}
			
			_tileIndex[0][0] = _tileX + 1;
			_tileIndex[0][1] = _tileY;
			_tileIndex[1][0] = _tileX + 1;
			_tileIndex[1][1] = _tileY + 1;
			//ex) tileIndex[0] = 내 앞 타일
			//ex) tileIndex[1] = 내 앞 타일의 그 옆 타일
		break;
		case TANKDIRECTION_DOWN:
			if (rcCollision.left / TILESIZE != rcCollision.right / TILESIZE)
			{
				if (_tankMap->getTile()[_tileY + 1][_tileX].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCKS) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX + 1].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX + 1].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX + 1].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX + 1].obj == OBJ_BLOCKS) _move = false;
				else _move = true;
			}
			else
			{
				if (_tankMap->getTile()[_tileY + 1][_tileX].terrain == TR_WATER) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCK1) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCK3) _move = false;
				else if (_tankMap->getTile()[_tileY + 1][_tileX].obj == OBJ_BLOCKS) _move = false;
				else _move = true;
			}
			

			_tileIndex[0][0] = _tileX;
			_tileIndex[0][1] = _tileY + 1;
			_tileIndex[1][0] = _tileX + 1;
			_tileIndex[1][1] = _tileY + 1;
			//ex) tileIndex[0] = 내 앞 타일
			//ex) tileIndex[1] = 내 앞 타일의 그 옆 타일
		break;
	}

	//if (_tankMap->getTile()[_tileY][_tileX].terrain == TR_WATER) _move = false;
	//if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK1) _move = false;
	//if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCK3) _move = false;
	//if (_tankMap->getTile()[_tileY][_tileX].obj == OBJ_BLOCKS) _move = false;
	//6. 예외처리도 해주세요
	//못가는 타일과 부딪혔다! 그럼 막아랏! 
	

	rcCollision = RectMakeCenter(_x, _y, _width, _height);

	_rc = rcCollision;
}

void tank::setTankPosition()
{
	//_rc = _tankMap->getTile()[_tankMap->getPosFirst()].rc;

	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;
}
