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

	vector<building> _vLoot;
	vector<building>::iterator _viLoot;

private:
	tagTileInfo _mapArr[MAXTILE][MAXTILE];
	tagRoadInfo _roadArr[MAXTILE][MAXTILE];
	tagBuildingInfo _buildArr[MAXTILE][MAXTILE];

	tagSaveInfo _mapSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _roadSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _buildSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _vBuildSaveInfo[MAXTILE][MAXTILE];
	tagSaveInfo _vLootSaveInfo[MAXTILE][MAXTILE];

	SAVE _saveFile[MAXSAVE];

	tagRemember _remember;
	FIRST _categoryLarge;
	SECOND _categorySmall;
	SELECTMENU _selectMenu;
	CONFIRM _currentConfirm;

	string _tmp;
	POINT _mouseArr;
	POINT _cameraArr;
	POINT _saveIndex;
	RECT _corX[MAXTILE], _corY[MAXTILE];
	RECT _miniMap;
	RECT _miniView;
	RECT _largeCategory;
	RECT _smallCategory;
	RECT _contents;
	RECT _confirmBox;
	RECT _saveWindow;

private:
	float _mapX, _mapY;

	bool _buildAttribute;
	bool _area;
	bool _foldMini;
	bool _move;
	bool _confirm;
	bool _saveAndLoad;
	bool _changeName;

	char _cor[256];
	char _msCorX[256], _msCorY[256];
	char _temp[256];
	
	int _boxLength;
	int _menuLength;
	int _inputDelayX, _inputDelayY;
	int _saveX, _saveY;
	int _saveAreaX, _saveAreaY;
	int _brushNum;
	int _page;
	int _saveNum;
	


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
	void lootingDraw(void);			// ROOTING
	void roadDraw(void);			// ROAD
	void attributeDraw(void);		// ATTRIBUTE
	void cordinateDraw(void);		// CORDINATE
	void windowDraw(void);				// CONFIRM

	void selectBox(int arrX, int arrY,int destX, int destY); // SELECT BOX
	void closedBox(int arrX, int arrY, int destX, int destY);// CLOSED BOX 

	//=============== S E T T I N G ========
	void loadImg(void);				// Load Img
	void setCor(void);				// Cordinate
	void cameraMove(void);			// Camera
	void minimapMove(void);			// Mini Map
	void setButton(void);			// Button Setting
	void inputOnMap(void);			// Key input On Map
	void inputOnUI(void);			// Key input On UI
	void inputCommon(void);			// Common Key input
	void inputWindow(void);			// Key input On window
	void windowMove(void);

	//=============== M E N U ================
	void goMain(void);				// Main Menu
	void newMap(void);				// New Map
	void saveMap(void);				// save Map
	void loadMap(void);				// load Map
	void saveMap(string fileName);
	void loadMap(string fileName);
	void saveFileList(void);
	void loadFileList(void);		// load Save File


	//=============== C O N T E N T S =========================
	void setTile(int arrX, int arrY, TILE tile);		// DRAW TILE
	void setRoad(int arrX, int arrY, ROAD road);		// DRAW ROAD
	void addBuilding(int arrX, int arrY, CAMP camp);	// DRAW BUILDING
	void addBuilding(int arrX, int arrY, MINE mine);	// DRAW BUILDING
	void addBuilding(int arrX, int arrY, EVENT ev);		// DRAW BUILDING
	void addObstacle(int arrX, int arrY);				// DRAW OBSTACLE
	void addLooting(int arrX, int arrY);
	void addUnit(int arrX, int arrY);
	void deleteAll(int arrX, int arrY);					// ERASE BUILDING

	//=============== A D D R E S S   L I N K ==================





	mapTool();
	~mapTool();
};

//HRGN 폴리곤; 1. 점을 배치해줌 2. 점들간에 선을 그어줘 CreateRGN(폴리곤이름, 선을 넣어줌, 몇개인가? )
