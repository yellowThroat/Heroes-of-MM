#pragma once

#define INPUTDELAY 8

#include "gameNode.h"

class mapTool : public gameNode
{
private:
	vector<POINT> _vSaveCor;
	vector<POINT>::iterator _viSaveCor;
	
	vector<building> _vBuild;
	vector<building>::iterator _viBuild;

private:

private:
	tagTileInfo _mapArr[MAXTILE][MAXTILE];
	tagRoadInfo _roadArr[MAXTILE][MAXTILE];
	tagBuildingInfo _buildArr[MAXTILE][MAXTILE];

	tagRemember _remember;
	FIRST _categoryLarge;
	SECOND _categorySmall;
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

	bool _buildAttribute;
	bool _area;
	bool _foldMini;
	bool _move;

	char _cor[256];
	char _msCorX[256], _msCorY[256];
	char _temp[256];
	
	int _boxLength;
	int _inputDelayX, _inputDelayY;
	int _saveX, _saveY;
	int _saveAreaX, _saveAreaY;
	int _brushNum;
	int _page;
	


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	//=============== D R A W ===============
	void tileDraw(void);			// TILE
	void miniDraw(void);			// MINIMAP
	void buttonDraw(void);			// BUTTON
	void selectDraw(void);			// SELECT CURSOR
	void buildingDraw(void);		// BUILDING
	void roadDraw(void);			// ROAD
	void attributeDraw(void);		// ATTRIBUTE
	void cordinateDraw(void);		// CORDINATE

	//=============== S E T T I N G ========
	void setCor(void);
	void cameraMove(void);
	void setButton(void);
	void minimapMove(void);
	void loadImg(void);
	void inputOnMap(void);
	void inputOnUI(void);
	void inputCommon(void);



	//=============== C O N T E N T S ===============
	void setTile(int arrX, int arrY, TILE tile);
	void setRoad(int arrX, int arrY, ROAD road);
	void deleteAll(int arrX, int arrY);
	void addBuilding(int arrX, int arrY, CAMP camp);
	void addBuilding(int arrX, int arrY, MINE mine);
	void addBuilding(int arrX, int arrY, EVENT ev);







	mapTool();
	~mapTool();
};