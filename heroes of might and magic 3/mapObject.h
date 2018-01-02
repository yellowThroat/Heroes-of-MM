#pragma once
#include "gameNode.h"

struct tagMapObject
{
	image* img;
	image* shadowImg;
	MINE mine;
	EVENT ev;
	POINT point;
	int player;
	int enterX, enterY;
	int indexX, indexY;
	int imgX, imgY;
	int type;
	bool visit;
};

//========== type ==============//
//								//
//		0 : mine				//
//		1 : event				//
//		2 : resources			//
//		3 : artifact			//
//		4 : castle creature		//
//		5 : dungeon creature	//
//								//
//==============================//

struct tagObject
{
	int type;						// 무슨 종류 인가
	int sub;						// 그 중 어떤 물건인가
	int x;							// x 좌표
	int y;							// y 좌표
	int possesion;					// 가지고 있는 자원량 
	int player;						// 어느 플레이어거 상태인가
	bool active;					// 이번 주 활성화된적 있는가
	vector<int> visitor;			// 방문한적 있는 영웅들 모음
};

class zOrder;

class mapObject : public gameNode
{
private:
	zOrder * _zOrder;

private:
	typedef vector<tagMapObject> vObject;
	typedef vector<tagMapObject>::iterator vObjectIter;

	vObject _vObject;
	vObjectIter _viObject;

	vector<tagObject> _vOb;
	

private:
	tagSaveInfo _mapSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _roadSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _buildSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _vBuildSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _vLootSaveInfo[MAXTILE][MAXTILE];

private:
	int _count;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void draw(void);

	//=================================
	bool checkObject(int x, int y);

	//============== L O A D ================
	void loadObject(void);
	void addLoot(int x, int y, int kind);

	//============== G E T T E R ==============
	tagObject getvOb(int x, int y);
	vObject getObject() { return _vObject; }
	vObjectIter getObjectIter() { return _viObject; }

	//============== S E T T E R ===============
	void setOb(int x, int y, tagObject ob);

	//============ ADDRESS LINK ===============
	void setzOrderAddressLink(zOrder* zor) { _zOrder = zor; }

	mapObject();
	~mapObject();

};