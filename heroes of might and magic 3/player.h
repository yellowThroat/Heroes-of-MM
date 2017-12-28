#pragma once
#include "gameNode.h"
#include "hero.h"



class playMap;
class gameScene;


class player : public gameNode
{
private:
	playMap* _pm;
	gameScene* _gs;

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

private:
	bool _myTurn;
	bool _cityScene;
	bool _autoCamera;
	int _myNum;						// 플레이어 값
	int _currentHero;				// 현재 조정중인 영웅
	int _currentCamp;				// 현재 보고있는 마을


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

	
	//================ S E T T I N G =========
	void inputCity(void);
	void inputField(void);
	void camera(void);

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
	//=========== ADDRESS LINK===============
	void setPlayMapAddressLink(playMap* pm) { _pm = pm; }
	void setGameSceneAddressLink(gameScene* gs) { _gs = gs; }



	player();
	~player();
};