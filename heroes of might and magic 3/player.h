#pragma once
#include "gameNode.h"
#include "hero.h"



class playMap;
class gameScene;
class zOrder;
class mapObject;
class battle;

class player : public gameNode
{
private:
	playMap* _pm;
	gameScene* _gs;
	zOrder* _zOrder;
	mapObject* _ob;
	battle* _battle;

private:
	typedef vector<hero*> vHero;
	typedef vector<hero*>::iterator vHeroIter;

	typedef vector<POINT> vPath;

	vHero _vHero;
	vHeroIter _viHero;

	vPath _vPath;

private:
	myProperty _myProperty;			// 플레이어가 가진 재산
	myBuilding _myBuilding;			// 플레이어가 가진 건물수
	POINT _mouseArr;
	POINT _destination;
	POINT _enemyCor;				// 적 정보 보기

private:
	char _enemyName[256];			// 적 이름 보기
	bool _myTurn;					// 플레이어 차례인가
	bool _battleScene;				// 전투중인가?
	bool _cityScene;				// 도시안에 들어갔을때
	bool _autoCamera;				// 영웅이동중 카메라 쫓아가기
	bool _window;					// 메뉴창을 열었을때 클릭 방지를 위해 
	bool _creatureinfo;				// 크리쳐 정보창을 킴
	int _enemyInfo;					// 적 정보창을 띄우는용 -1 이면 false
	int _myNum;						// 플레이어 값
	int _currentHero;				// 현재 조정중인 영웅
	int _currentCamp;				// 현재 보고있는 마을
	int _currentCreature;
	int _count;						// 인덱스 돌리는용
	int _saveCorX;					// 좌표 저장용
	int _saveCorY;

public:

	HRESULT init(int myNum);
	void release(void);
	void update(void);
	void render(void);
	

	//=============== U P D A T E ============
	void fieldUpdate(void);
	void cityUpdate(void);


	//================ D R A W ===========
	void cityScene(void);
	void fieldScene(void);
	void heroInfoDraw(void);
	void enemyInfoDraw(void);

	
	//================ S E T T I N G =========
	void setBattle(void);
	void setMyInfo(void);
	void inputCity(void);
	void inputField(void);
	void camera(void);
	void setFrame(void);
	void weekGo(void);
	void dayGo(void);
	void activeObject(void);

	//================ E N T E R ===========
	void enterCity(void);



	//=========== H E R O ============
	void addHero(POINT point, tagHero heroInfo);




	//=========== G E T T E R ===============
	int getNum() { return _myNum; }
	int getCurrentCamp() { return _currentCamp; }
	int getCurrentHero() { return _currentHero; }
	bool getTurn() { return _myTurn; }
	bool getScene() { return _cityScene; }
	bool getAutoCamera() { return _autoCamera; }
	bool getWindow() { return _window; }
	bool getBattleScene() { return _battleScene; }
	vHero getHero() { return _vHero; }
	vPath getPath() { return _vPath; }
	myProperty getProperty() { return _myProperty; }
	myBuilding getBuilding() { return _myBuilding; }

	//=========== S E T T E R ===============
	void setScene(bool scene) { _cityScene = scene; }
	void setCurrentCamp(int camp) { _currentCamp = camp; }
	void setCurrentHero(int hero) { _currentHero = hero; }
	void setAutoCamera(bool autocamera) { _autoCamera = autocamera; }
	void setProperty(myProperty pro) { _myProperty = pro; }
	void setBuilding(myBuilding build) { _myBuilding = build; }
	void setWindow(bool window) { _window = window; }
	void setBattleScene(bool scene) { _battleScene = scene; }

	//=========== ADDRESS LINK===============
	void setPlayMapAddressLink(playMap* pm) { _pm = pm; }
	void setGameSceneAddressLink(gameScene* gs) { _gs = gs; }
	void setzOrderAddressLink(zOrder* zor) { _zOrder = zor; }
	void setMapObjectAddressLink(mapObject* mo) { _ob= mo; }
	void setBattletAddressLink(battle* battle) { _battle= battle; }


	player();
	~player();
};