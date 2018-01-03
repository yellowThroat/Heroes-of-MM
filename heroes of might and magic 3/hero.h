#pragma once
#include "gameNode.h"

struct tagPathDraw
{
	POINT point;
	int indexX;
	int indexY;
	int action;
};

class player;
class playMap;
class zOrder;
class gameScene;

class hero : public gameNode
{
private:
	player* _pl;
	playMap* _pm;
	zOrder* _zOrder;

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
	POINT _destination;			// 최종 도착지
	POINT _previousPath;		// 이전 경로
	POINT _nextPath;			// 다음 경로

private:
	float _x;					// 영웅의 중점 좌표
	bool _goOn;					// 이동 중인지
	bool _moveEnd;				// 이동 끝난 타이밍을 알리기 위해
	int _isInCamp;				// 어느 캠프로 들어갔는지 아무데도 안갔다면 -1
	int _myNum;					// 영웅 넘버
	int _player;				// 어느플레이어 영웅인지
	int _currentActionPoint;	// 현재 행동력
	int _maxActionPoint;		// 최대 행동력
	int _needActionPoint;		// 이동시 필요 행동력
	int _totalActionPoint;		// 사용한 액션 포인트
	int _startActionPoint;		// 이동전 남은 행동력
	int _currentMana;			// 현재 주문력
	int _maxMana;				// 최대 주문력
	int _exp;					// 현재 경험치
	

	/*

	Speed			action Point
	3					1500
	4					1560
	5					1630
	6					1700
	7					1760
	8					1830
	9					1900
	10					1960
	11					2000
	
	*/


	
public:
	float _y;					// 상동

	HRESULT init(POINT point, tagHero hero);
	void release(void);
	void update(void);
	void render(void);

	//========== D R A W =========
	void fieldDraw(void);
	void pathDraw(void);
	void uiDraw(void);

	//========== S E T ============
	void deletePath(int arr);
	void clearDraw() { _vDraw.clear(); }
	void setAngle(void);
	void setCordinate(void);
	void heroMove(void);
	void weekGo(void);
	void dayGo(void);
	void addCreature(int kind, int tier, int level, int quantity);
	void addCreature(int kind, int tier, int level, int quantity, int position);
	void deleteCreature(int arr);
	void setActionPoint();
	int getDirection(int x, int y);


	static bool comp(const hero *t1, const hero *t2) {
		return (t1->_y < t2->_y);
	}

	//============= G E T T E R  ============
	vCreature getCreature() { return _vCreature; }
	tagHero getHeroInfo() { return _myHero; }
	POINT getHeroPoint() { return _pointArr; }
	POINT getHeroDest() { return _destination; }
	vPath getPath() { return _vPath; }
	float getHeroX() { return _x; }
	float getHeroY() { return _y; }
	int getMyNum() { return _myNum; }
	int getAP() { return _currentActionPoint; }
	int getNeedAp() { return _needActionPoint; }
	int getMaxAP() { return _maxActionPoint; }
	int getMana() { return _currentMana; }
	int getMaxMana() { return _maxMana; }
	int getExp() { return _exp; }
	int getInCamp() { return _isInCamp; }
	bool getGoOn() { return _goOn; }
	bool getMoveEnd() { return _moveEnd; }

	//============= S E T T E R =============
	void setCreature(vCreature creature) { _vCreature = creature; }
	void setCreature(tagCreature creature, int arr) { _vCreature[arr] = creature; }
	void setHeroDest(POINT point) { _destination = point; }
	void setHeroInfo(tagHero heroInfo) { _myHero = heroInfo; }
	void setPath(vPath path);
	void setPreviousPath(POINT point) { _previousPath = point; }
	void setMynum(int num) { _myNum = num; }
	void setGoOn(bool go);
	void setMoveEnd(bool end) { _moveEnd = end; }
	void setInCamp(int camp) { _isInCamp = camp; }
	void setAP(int ap) { _currentActionPoint = ap; }
	void setMana(int mana) { _currentMana = mana; }
	void setExp(int exp) { _exp = exp; }

	//============= ADDRESS LINK ===============
	void setPlayerAddressLink(player* pl) { _pl = pl; }
	void setPlayMapAddressLink(playMap* pm) { _pm = pm; }
	void setzOrderAddressLink(zOrder* zor) { _zOrder = zor; }

	hero();
	~hero();
};