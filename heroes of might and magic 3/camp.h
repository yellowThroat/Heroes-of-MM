#pragma once
#include "gameNode.h"

struct tagStructure
{
	// 구조물 정보
	TCHAR name[256];				// 이름
	TCHAR explantion[256];		// 건물 설명
	TCHAR needBuild[256];		// 선행 건물
	int num;					// 몇번째 칸에 있는것이다.
	int level;					// 이건 또 머야	
	image* img;					// 건물 사진
	image* checkImg;
	int x, y;					// 그릴 위치
	int index;					// 건설 가능 여부
	bool needResources;			// 자원 부족
	bool needBuilding;			// 테크트리 필요
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

struct tagRecruit
{	
	char unit[256];				// 유닛 이름
	char building[256];			// 건물 이름
	int output;					// 주 생산량
	int remain;					// 뽑을 수 있는 병력수
	int x, y;					// 홀 렌더시에 좌표
	int num;					// 몇번째 칸인지
	
	int gold;					// 필요한 자원들
	int wood;
	int iron;
	int sulfur;
	int mercury;
	int crystal;
	int gem;
	
};

class player;

class camp : public gameNode
{
private:
	player* _play;

private:
	image* _fieldImg;
	image* _fieldShadowImg;
	image* _cityBackground;

	tagUnitSample _unitSample[14];	// 유닛 샘플
	tagStructure _structure[18];	// 구조체 정보
	tagRecruit _recruit[7];		// 유닛 생산 정보
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
	int _levelGrowth[7];		// 크리쳐 성장
	int _special[5];			// 특수 건물
	int _campNum;				// 성 넘버
	int _windowNum;				// 멀 눌렀니?
	bool _cityScene;			// 건물 안으로 들어왔는가
	bool _showWindow;			// 무언갈 눌렀을때
	bool _contents;				// 내용을 띄우자
	bool _beBuilt;				// 이번턴 건물 이미 지었나
	float _cameraX;				// 카메라 X
	float _cameraY;				// 카메라 Y
	myProperty _property;		// 플레이어 자원
	tagStructure _saveStructure;// 찍은 건물 ( 홀에서 )
	tagRecruit _saveRecruit;	// 찍은 유닛 ( 성채에서 )
	


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
	void inputCity();
	void structureInit();
	void unitSampleInit();
	void buildingInit();
	void recruitInit();
	void buildingCondition(void);
	void cameraSetting(void);
	void setCityScene(bool scene) { _cityScene = scene; }
	void setBuildingInfo(building info) { _buildingInfo = info; }
	void setFrameCycle(void);
	void selectBox(void);
	void changeState(image* img, int delay);


	//========== G E T T E R =============
	tagStructure getStructure(int num) { return _structure[num]; }
	myProperty getProperty() { return _property; }
	building getCityInfo() { return _buildingInfo; }
	POINT getFieldPoint() { return _fieldPoint; }
	bool getCityScene() { return _cityScene; }
	bool getWindow() { return _showWindow; }
	bool getContents() { return _contents; }
	int getNum() { return _campNum; }
	int getPlayerNum() { return _player; }
	int getWindowNum() { return _windowNum; }
	//========== S E T T E R =============
	void setNum(int num) { _campNum = num; }
	void setPlayer(int num) { _player = num; }
	void setWindow(bool show) { _showWindow = show; }
	void setWindowNum(int num) { _windowNum = num; }
	void setProperty(myProperty pro) { _property = pro; }
	void setContents(bool contents) { _contents = contents; }
	void setSaveStructure(int stru) { _saveStructure = _structure[stru]; }

	//========== ADDRESS LINK ============

	void setPlayerAddressLink(player* player) { _play = player; }

	camp();
	~camp();
};