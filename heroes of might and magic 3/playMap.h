#pragma once
#include "gameNode.h"

struct tagPathFind
{
	int f;
	int g;
	int h;
	int nodeX, nodeY;
	int parentX, parentY;
	bool operator<(const tagPathFind &v) const {
		return (f < v.f);
	}
};

class playMap : public gameNode
{
private:
	vector<building> _vBuild;
	vector<building>::iterator _viBuild;

	vector<tagPathFind> _openlist;
	vector<tagPathFind> _closelist;

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
	//============ A S T A R ==================
	vector<POINT> getPath(int x, int y, int destX, int destY);	// 최단 경로 포인트
	bool isClosed(int x, int y);								// 클로즈에 있는지 확인
	bool alreadyOpend(int x, int y);
	int openlistNum(int x, int y);

	//============ G E T T E R ================
	POINT getCamera() { return _camera; }
	POINT getCameraArr() { return _cameraArr; }

	//============ S E T T E R ================
	void setCamera(POINT camera) { _camera = camera; }


	//============ ADDRESS LINK ===============

	playMap();
	~playMap();
};