#pragma once
#include "gameNode.h"

struct tagAStar
{
	int f;
	int g;
	int h;
	int x, y;
	int px, py;
	bool operator<(const tagAStar &v) const {
		return (f > v.f);
	}
};

class playMap : public gameNode
{
private:
	vector<building> _vBuild;
	vector<building>::iterator _viBuild;

	vector<tagAStar> _openlist;
	vector<tagAStar> _closelist;

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

	//============ A S T A R =============
	vector<tagTileInfo> aStar(POINT currentpoint, POINT goalPoint); //a* 실행함수
	void add_openlist(tagAStar v);									// openlist에 추가
	tagAStar pop_openlist();										// openlist에서 pop
	tagAStar pop_openlist(int x, int y);							// openlist에서 pop
	tagAStar search_openlist(int x, int y);							// openlist에서 탐색
	bool search_openlist_exsist(int x, int y);						// closelist에 있는지 여부 확인
	void add_closelist(tagAStar v);									// cliselist에 추가
	tagAStar pop_closelist(int x, int y);							// closelist에서 pop
	bool search_closelist_exsist(int x, int y);						// closelist에 있는지 여부 확인

	tagAStar calc_vertex(tagAStar v, tagAStar p, POINT goalPoint);	// FGH값 계산
	void add_eightway(tagAStar v, POINT goalPoint);					// 8방향 탐색 후 추가 
	bool check_goal();												// 목적지 탐색

	
	//============ G E T T E R ================
	POINT getCamera() { return _camera; }
	POINT getCameraArr() { return _cameraArr; }

	//============ S E T T E R ================
	void setCamera(POINT camera) { _camera = camera; }


	//============ ADDRESS LINK ===============

	playMap();
	~playMap();
};