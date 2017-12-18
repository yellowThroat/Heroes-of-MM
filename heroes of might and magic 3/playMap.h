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
	vector<tagTileInfo> aStar(POINT currentpoint, POINT goalPoint); //a* �����Լ�
	void add_openlist(tagAStar v);									// openlist�� �߰�
	tagAStar pop_openlist();										// openlist���� pop
	tagAStar pop_openlist(int x, int y);							// openlist���� pop
	tagAStar search_openlist(int x, int y);							// openlist���� Ž��
	bool search_openlist_exsist(int x, int y);						// closelist�� �ִ��� ���� Ȯ��
	void add_closelist(tagAStar v);									// cliselist�� �߰�
	tagAStar pop_closelist(int x, int y);							// closelist���� pop
	bool search_closelist_exsist(int x, int y);						// closelist�� �ִ��� ���� Ȯ��

	tagAStar calc_vertex(tagAStar v, tagAStar p, POINT goalPoint);	// FGH�� ���
	void add_eightway(tagAStar v, POINT goalPoint);					// 8���� Ž�� �� �߰� 
	bool check_goal();												// ������ Ž��

	
	//============ G E T T E R ================
	POINT getCamera() { return _camera; }
	POINT getCameraArr() { return _cameraArr; }

	//============ S E T T E R ================
	void setCamera(POINT camera) { _camera = camera; }


	//============ ADDRESS LINK ===============

	playMap();
	~playMap();
};