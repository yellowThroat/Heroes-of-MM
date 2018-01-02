#pragma once
#include "gameNode.h"

struct tagPathFind
{
	int f;
	int g;
	int h;
	int nodeX, nodeY;
	int parentX, parentY;
	int road;
	int direction;;
	bool operator<(const tagPathFind &v) const {
		return (f  < v.f );
	}
};

struct tagPathFindSecond
{
	int f;
	int g;
	int h;
	int nodeX, nodeY;
	int parentX, parentY;
	int road;
	int direction;
	bool operator<(const tagPathFindSecond &v) const {
		return (h < v.h);
	}
};

class zOrder;

class playMap : public gameNode
{
private:
	zOrder * _zOrder;

private:
	vector<building> _vBuild;
	vector<building>::iterator _viBuild;

	vector<tagPathFind> _openlist;
	vector<tagPathFindSecond> _closelist;


private:
	tagTileInfo _map[MAXTILE][MAXTILE];
	tagRoadInfo _road[MAXTILE][MAXTILE];

	tagSaveInfo _mapSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _roadSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _buildSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _vBuildSaveInfo[MAXTILE][MAXTILE];

	SAVE _saveFile[MAXSAVE];

private:
	float _cameraX;
	float _cameraY;
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
	bool alreadyClosed(int x, int y);
	
	//============ G E T T E R ================
	tagRoadInfo getRoadInfo(int x, int y) { return _road[x][y]; }
	float getCameraX() { return _cameraX; }
	float getCameraY() { return _cameraY; }
	POINT getCameraArr() { return _cameraArr; }
	bool getClosed(int x, int y) { return _map[x][y].isClosed; }
	bool getAttribute() { return _buildAttribute; }
	//============ S E T T E R ================
	void setCameraX(float x) { _cameraX = x; }
	void setCameraY(float y) { _cameraY = y; }
	void setClosed(int x, int y, bool closed) { _map[x][y].isClosed = closed; }

	//============ ADDRESS LINK ===============
	void setzOrderAddressLink(zOrder* zor) { _zOrder = zor; }

	playMap();
	~playMap();
};