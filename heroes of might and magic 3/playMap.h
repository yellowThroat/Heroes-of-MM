#pragma once
#include "gameNode.h"



class playMap : public gameNode
{
private:
	vector<building> _vBuild;
	vector<building>::iterator _viBuild;

private:
	tagTileInfo _map[MAXTILE][MAXTILE];
	tagRoadInfo _road[MAXTILE][MAXTILE];

	tagSaveInfo _mapSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _roadSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _buildSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _vBuildSaveInfo[MAXTILE][MAXTILE];

	SAVE _saveFile[MAXSAVE];

private:
	POINT _camera;
	POINT _cameraArr;

private:
	bool _buildAttribute;
		
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//============ D R A W =============
	void tileDraw(void);
	void roadDraw(void);
	void obstacleDraw(void);
	void attributeDraw(void);

	//============ S E T T I N G =============
	void cameraMove();
	void inputCommon();

	//============ L O A D ==============
	void loadMap(int saveNum);
	void loadFileList(void);

	//============ G E T T E R ================
	POINT getCamera() { return _camera; }
	POINT getCameraArr() { return _cameraArr; }

	//============ S E T T E R ================
	void setCamera(POINT camera) { _camera = camera; }


	//============ ADDRESS LINK ===============

	playMap();
	~playMap();
};