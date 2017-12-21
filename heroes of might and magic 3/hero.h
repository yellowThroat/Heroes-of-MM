#pragma once
#include "gameNode.h"

struct tagPathDraw
{
	POINT point;
	int indexX;
	int indexY;
};

class hero : public gameNode
{
private:
	typedef vector<POINT> vPath;
	typedef vector<tagPathDraw> vDraw;


	vDraw _vDraw;
	vPath _vPath;

private:
	tagHero _myHero;
	
	POINT _pointArr;
	POINT _destination;

private:
	float _x;
	float _y;
	bool _myTurn;
	bool _goOn;
	bool _moveEnd;
	bool _isInCamp;
	int _myNum;
	
	
public:

	HRESULT init(POINT point, tagHero hero);
	void release(void);
	void update(void);
	void render(void);

	//========== D R A W =========
	void fieldDraw(void);
	void pathDraw(void);

	//========== S E T ============
	void setAngle(void);
	void setCordinate(void);
	void heroMove(void);
	int getDirection(int x, int y);

	//============= G E T T E R  ============
	vPath getPath() { return _vPath; }
	tagHero getHeroInfo() { return _myHero; }
	POINT getHeroPoint() { return _pointArr; }
	float getHeroX() { return _x; }
	float getHeroY() { return _y; }
	int getMyNum() { return _myNum; }
	bool getGoOn() { return _goOn; }
	bool getMoveEnd() { return _moveEnd; }
	bool getInCamp() { return _isInCamp; }
	//============= S E T T E R =============
	void setHeroInfo(tagHero heroInfo) { _myHero = heroInfo; }
	void setPath(vPath path);
	void setMynum(int num) { _myNum = num; }
	void setGoOn(bool go) { _goOn = go; }
	void setMoveEnd(bool end) { _moveEnd = end; }
	void setInCamp(bool camp) { _isInCamp = camp; }
	hero();
	~hero();
};