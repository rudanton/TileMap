#include "stdafx.h"
#include "tankMap.h"

tankMap::tankMap()
{
}


tankMap::~tankMap()
{
}

HRESULT tankMap::init()
{
	IMAGEMANAGER->addFrameImage("mapTiles", "maptiles.bmp", 0, 0, 640, 288, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	load();

	return S_OK;
}

void tankMap::release()
{
}

void tankMap::update()
{
}

void tankMap::render()
{
	IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(),
				_tiles[i][j].rc.left,
				_tiles[i][j].rc.top,
				_tiles[i][j].terrainFrameX,
				_tiles[i][j].terrainFrameY);
		}
	}

	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			//������Ʈ �Ӽ��� NONE�̸� �������� �׸�������(continue)
			if (_tiles[i][j].obj == OBJ_NONE) continue;

			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(),
				_tiles[i][j].rc.left, 
				_tiles[i][j].rc.top,
				_tiles[i][j].objFrameX, 
				_tiles[i][j].objFrameY);
		}
	}



}

void tankMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("saveMap1.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	//1. Ÿ�ϸ��� �ҷ��ö� � Ÿ�� �Ǵ� ������Ʈ��
	//��Ʈ�ʵ带 ���ؼ� �Ӽ�(?) ���� �־���Ѵ�.
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; j++)
		{
			if (_tiles[i][j].terrain == TR_WATER) _attribute[i][j] |= ATTR_UNMOVE;
			if (_tiles[i][j].obj == OBJ_BLOCK1) _attribute[i][j] |= ATTR_UNMOVE;
			if (_tiles[i][j].obj == OBJ_BLOCK3) _attribute[i][j] |= ATTR_UNMOVE;
			if (_tiles[i][j].obj == OBJ_BLOCKS) _attribute[i][j] |= ATTR_UNMOVE;

		}
	}


	CloseHandle(file);

}
