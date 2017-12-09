#pragma once

#define INPUTDELAY 8

#include "gameNode.h"
#include "loading.h"

class mapTool : public gameNode
{
private:
	vector<POINT> _vSaveCor;
	vector<POINT>::iterator _viSaveCor;

private:
	loading* _loading;

private:
	tagTileInfo _mapArr[MAXTILE][MAXTILE];
	CATEGORY _categoryNum;
	POINT _mouseArr;
	POINT _saveIndex;
	RECT _corX[MAXTILE], _corY[MAXTILE];
	RECT _miniMap;
	RECT _miniView;
	RECT _largeCategory;
	RECT _smallCategory;
	RECT _contents;
private:
	float _mapX, _mapY;

	bool _clickUI;
	bool _area;
	bool _foldMini;

	char _cor[256];
	char _msCorX[256], _msCorY[256];
	char _temp[256];
	
	int _boxLength;
	int _inputDelayX, _inputDelayY;
	int _saveX, _saveY;
	int _saveAreaX, _saveAreaY;
	int _smallNum;
	int _brushNum;
	int _tileNum;
	int _page;
	


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void tileDraw(void);
	void miniDraw(void);
	void buttonDraw(void);
	void selectDraw(void);


	void setTile(int arrX, int arrY, TILE tile);
	void setCor(void);
	void keyControl(void);
	void cameraMove(void);
	void minimapMove(void);
	void setButton(void);
	
	void loadImg(void);



	mapTool();
	~mapTool();
};