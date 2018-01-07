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
	myProperty _myProperty;			// �÷��̾ ���� ���
	myBuilding _myBuilding;			// �÷��̾ ���� �ǹ���
	POINT _mouseArr;
	POINT _destination;
	POINT _enemyCor;				// �� ���� ����

private:
	char _enemyName[256];			// �� �̸� ����
	bool _myTurn;					// �÷��̾� �����ΰ�
	bool _battleScene;				// �������ΰ�?
	bool _cityScene;				// ���þȿ� ������
	bool _autoCamera;				// �����̵��� ī�޶� �Ѿư���
	bool _window;					// �޴�â�� �������� Ŭ�� ������ ���� 
	bool _creatureinfo;				// ũ���� ����â�� Ŵ
	int _enemyInfo;					// �� ����â�� ���¿� -1 �̸� false
	int _myNum;						// �÷��̾� ��
	int _currentHero;				// ���� �������� ����
	int _currentCamp;				// ���� �����ִ� ����
	int _currentCreature;
	int _count;						// �ε��� �����¿�
	int _saveCorX;					// ��ǥ �����
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