#pragma once
#include "gameNode.h"

struct tagStructure
{
	// 구조물 정보
	char name[256];
	int num;
	int level;
	image* img;

	//필요 자원
	int gold;
	int wood;
	int iron;
	int crystal;
	int mercury;
	int sulfur;
	int gem;
};

struct tagUnitSample
{
	CREATURESTATE state;
	image* img[STATE_END];
	image* shadowImg[STATE_END];
	int x;
	int y;
	
};

class camp : public gameNode
{
private:


private:
	image* _fieldImg;
	image* _fieldShadowImg;
	image* _cityBackground;

	tagUnitSample _unitSample[14];
	tagStructure _structure;	// 구조체 정보
	building _buildingInfo;		// 캠프 정보
	POINT _cameraArr;			// 카메라 배열
	POINT _fieldPoint;			// 필드 좌표
	RECT _fieldRect;			// 필드 렉트
	CAMP _camp;					// 종류 
	
	
private:
	char _name[256];			// 성 이름
	int _player;				// 어느 플레이어것인가
	int _hall;					// 회관
	int _fort;					// 요새
	int _pub;					// 선술집
	int _guild;					// 마법길드
	int _market;				// 시장
	int _forge;					// 대장간
	int _level[7];				// 티어 건물
	int _special[5];			// 특수 건물
	int _campNum;				// 성 넘버
	int _windowNum;				// 멀 눌렀니?
	bool _cityScene;			// 건물 안으로 들어왔는가
	bool _showWindow;			// 무언갈 눌렀을때
	float _cameraX;				// 카메라 X
	float _cameraY;				// 카메라 Y



public:

	virtual HRESULT	init(building info);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//============ D R A W ===============
	void fieldDraw(void);
	void castleDraw(void);
	void dungeonDraw(void);

	//========== S E T T I N G ===========
	void structureInit();
	void unitSampleInit();
	void buildingInit();
	void buildingCondition(void);
	void cameraSetting(void);
	void setCityScene(bool scene) { _cityScene = scene; }
	void setBuildingInfo(building info) { _buildingInfo = info; }
	void setFrameCycle(void);
	void selectBox(void);
	void changeState(image* img, int delay);


	//========== G E T T E R =============
	building getCityInfo() { return _buildingInfo; }
	POINT getFieldPoint() { return _fieldPoint; }
	bool getCityScene() { return _cityScene; }
	bool getWindow() { return _showWindow; }
	int getNum() { return _campNum; }
	int getPlayerNum() { return _player; }
	int getWindowNum() { return _windowNum; }

	//========== S E T T E R =============
	void setNum(int num) { _campNum = num; }
	void setPlayer(int num) { _player = num; }
	void setWindow(bool show) { _showWindow = show; }
	void setWindowNum(int num) { _windowNum = num; }


	//========== ADDRESS LINK ============

	camp();
	~camp();
};