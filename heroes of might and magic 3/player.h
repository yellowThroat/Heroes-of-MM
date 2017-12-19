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

class player : public gameNode
{
private:
	playMap* _pm;

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
	int _myNum;
	int _currentHero;


public:

	HRESULT init(int myNum);
	void release(void);
	void update(void);
	void render(void);
	
	void inputGame(void);
	void camera(void);



	//=========== H E R O ============
	void addHero(POINT point, tagHero heroInfo);



	//=========== G E T T E R ===============
	bool getTurn() { return _myTurn; }
	int getNum() { return _myNum; }
	vPath getPath() { return _vPath; }

	//=========== ADDRESS LINK===============
	void setPlayMapAddressLink(playMap* pm) { _pm = pm; }



	player();
	~player();
};