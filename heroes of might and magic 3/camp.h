#pragma once
#include "gameNode.h"

class playMap;

class camp : public gameNode
{
private:
	playMap* _pm;

private:
	image* _fieldImg;
	image* _fieldShadowImg;
	image* _cityBackground;

	building _buildingInfo;		// 건물 정보
	POINT _camera;				// 카메라 정보
	POINT _cameraArr;
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
	bool _cityScene;			// 건물 안으로 들어왔는가

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

	//========== G E T T E R =============
	bool getCityScene() { return _cityScene; }

	//========== ADDRESS LINK ============
	void setAddressLinkFromPlayMap(playMap* pm) { _pm = pm; }

	camp();
	~camp();
};