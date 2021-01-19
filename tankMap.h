#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tankMap : public gameNode
{
private:
	tagTile _tiles[TILEX][TILEY];

	//������ �Ӽ��� enum���� �ϸ� �����������
	//���� ��Ʈ�ʵ���� �Ἥ �Ҳ��̹Ƿ� �������� �ҰԿ�
	DWORD _attribute[TILEX][TILEY];

	int _pos[2][2];	//����� �ǹ̰� ���� ��������

public:
	tankMap();
	~tankMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	tagTile (*getTile())[TILEY] { return _tiles; }

		//2. �ش� �Ӽ��� �Ѱ��� getter�� ���� ��������
		//2���н�
	DWORD (*getAttribute())[TILEY] { return *&_attribute; }

	//int getPosFirst() { return _pos[0]; }
	//int getPosSecond() { return _pos[1]; }
};

