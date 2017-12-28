#pragma once
#include "gameNode.h"

struct tagPathDraw
{
	POINT point;
	int indexX;
	int indexY;
};

class player;
class playMap;

class hero : public gameNode
{
private:
	player* _pl;
	playMap* _pm;

private:
	typedef vector<POINT> vPath;
	typedef vector<tagPathDraw> vDraw;
	typedef vector<tagCreature> vCreature;

	vDraw _vDraw;				// 경로에 방향 그려줄때 쓸 벡터
	vPath _vPath;				// 실제로 경로를 읽는 벡터
	vCreature _vCreature;		// 가지고 있는 크리쳐들

private:
	tagHero _myHero;			// 영웅의 각종 정보들
	
	POINT _pointArr;			// 영웅 좌표 배열
	POINT _destination;			// 아직 보류중

private:
	float _x;					// 영웅의 중점 좌표
	float _y;					// 상동
	bool _goOn;					// 이동 중인지
	bool _moveEnd;				// 이동 끝난 타이밍을 알리기 위해
	bool _isInCamp;				// 캠프 안으로 들어갔는지
	int _myNum;					// 영웅 넘버
	int _player;				// 어느플레이어 영웅인지
	int _currentActionPoint;	// 현재 행동력
	int _maxActionPoint;		// 최대 행동력
	int _currentMana;			// 현재 주문력
	int _maxMana;				// 최대 주문력

	
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
	tagHero getHeroInfo() { return _myHero; }
	POINT getHeroPoint() { return _pointArr; }
	POINT getHeroDest() { return _destination; }
	vPath getPath() { return _vPath; }
	float getHeroX() { return _x; }
	float getHeroY() { return _y; }
	int getMyNum() { return _myNum; }
	bool getGoOn() { return _goOn; }
	bool getMoveEnd() { return _moveEnd; }
	bool getInCamp() { return _isInCamp; }
	//============= S E T T E R =============
	void setHeroDest(POINT point) { _destination = point; }
	void setHeroInfo(tagHero heroInfo) { _myHero = heroInfo; }
	void setPath(vPath path);
	void setMynum(int num) { _myNum = num; }
	void setGoOn(bool go) { _goOn = go; }
	void setMoveEnd(bool end) { _moveEnd = end; }
	void setInCamp(bool camp) { _isInCamp = camp; }

	//============= ADDRESS LINK ===============
	void setPlayerAddressLink(player* pl) { _pl = pl; }
	void setPlayMapAddressLink(playMap* pm) { _pm = pm; }

	hero();
	~hero();
};