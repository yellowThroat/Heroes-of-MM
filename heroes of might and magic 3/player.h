#pragma once
#include "gameNode.h"
#include "hero.h"

typedef struct tagProperty
{
	int gold;
	int crystal;
	int wood;
	int iron;
	int sulfur;
	int mercury;
	int gem;	
	tagProperty()
	{
		gold			= 0;
		crystal			= 0;
		wood			= 0;
		iron			= 0;
		sulfur			= 0;
		mercury			= 0;
		gem				= 0;
	}

}myProperty;

typedef struct tagMyBuilding
{
	int camp;
	int gold;
	int crystal;
	int wood;
	int iron;
	int sulfur;
	int mercury;
	int gem;
	tagMyBuilding()
	{
		camp			= 1;
		gold			= 0;
		crystal			= 0;
		wood			= 0;
		iron			= 0;
		sulfur			= 0;
		mercury			= 0;
		gem				= 0;
	}
}myBuilding;


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
	myProperty _myProperty;
	myBuilding _myBuilding;
	POINT _mouseArr;
	POINT _destination;

private:
	bool _readyMove;
	bool _myTurn;
	bool _cityScene;
	bool _autoCamera;
	int _myNum;
	int _currentHero;
	int _currentCamp;


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
	bool getTurn() { return _myTurn; }
	int getNum() { return _myNum; }
	int getCurrentCamp() { return _currentCamp; }
	vPath getPath() { return _vPath; }
	bool getScene() { return _cityScene; }
	vHero getHero() { return _vHero; }
	bool getAutoCamera() { return _autoCamera; }

	//=========== S E T T E R ===============
	void setScene(bool scene) { _cityScene = scene; }
	void setCurrentCamp(int camp) { _currentCamp = camp; }
	void setAutoCamera(bool autocamera) { _autoCamera = autocamera; }
	//=========== ADDRESS LINK===============
	void setPlayMapAddressLink(playMap* pm) { _pm = pm; }
	void setGameSceneAddressLink(gameScene* gs) { _gs = gs; }



	player();
	~player();
};