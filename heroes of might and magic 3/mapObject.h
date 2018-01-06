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
	void deleteOb(int x, int y);

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