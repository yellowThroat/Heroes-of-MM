#pragma once
#include "gameNode.h"
#include "playMap.h"
#include "ui.h"
#include "castle.h"
#include "dungeon.h"
#include "mapObject.h"
#include "player.h"

class gameScene : public gameNode
{
private:
	mapObject*		_ob;
	playMap*		_pm;
	player*			_player;
	ui*				_ui;


private:
	typedef vector<camp*> vCamp;
	typedef vector<camp*>::iterator vCampIter;

	vCamp _vCamp;
	vCampIter _viCamp;
	building test;

private:
	tagSaveInfo _mapSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _roadSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _buildSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _vBuildSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _vLootSaveInfo[MAXTILE][MAXTILE];


private:

	int _fadeAlpha;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//=========== E N T E R   C I T Y ==========
	void enterCity(void);

	//=========== L O A D   M A P ==========
	void loadMap();
	void loadCamp();
	//void clearCamp();

	//=========== O B J E C T ==============
	void addCamp(tagBuildingInfo info);

	//=========== S E T T I N G =============
	void inputCommon(void);
	void inputPlay(void);

	//=========== G E T T E R ===============
	vCamp getvCamp() { return _vCamp; }


	gameScene();
	~gameScene();

};