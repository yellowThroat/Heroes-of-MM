#pragma once
#include "gameNode.h"


class camp : public gameNode
{
private:


private:
	image* _fieldImg;
	image* _fieldShadowImg;
	image* _cityBackground;

	building _buildingInfo;		// 건물 정보
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
	bool _cityScene;			// 건물 안으로 들어왔는가
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
	void buildingInit();
	void buildingCondition(void);
	void cameraSetting(void);
	void setCityScene(bool scene) { _cityScene = scene; }
	void setBuildingInfo(building info) { _buildingInfo = info; }
	void setFrameCycle(void);

	//========== G E T T E R =============
	bool getCityScene() { return _cityScene; }
	building getCityInfo() { return _buildingInfo; }
	int getNum() { return _campNum; }
	int getPlayerNum() { return _player; }
	POINT getFieldPoint() { return _fieldPoint; }

	//========== S E T T E R =============
	void setNum(int num) { _campNum = num; }
	void setPlayer(int num) { _player = num; }

	//========== ADDRESS LINK ============

	camp();
	~camp();
};