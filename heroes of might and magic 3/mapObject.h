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


class mapObject : public gameNode
{
private:
	typedef vector<tagMapObject> vObject;
	typedef vector<tagMapObject>::iterator vObjectIter;

	vObject _vObject;
	vObjectIter _viObject;

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



	//============== L O A D ================
	void loadObject(void);

	//============== G E T T E R ==============
	vObject getObject() { return _vObject; }
	vObjectIter getObjectIter() { return _viObject; }

	mapObject();
	~mapObject();

};