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

	vDraw _vDraw;				// ��ο� ���� �׷��ٶ� �� ����
	vPath _vPath;				// ������ ��θ� �д� ����
	vCreature _vCreature;		// ������ �ִ� ũ���ĵ�

private:
	tagHero _myHero;			// ������ ���� ������
	
	POINT _pointArr;			// ���� ��ǥ �迭
	POINT _destination;			// ���� ������

private:
	float _x;					// ������ ���� ��ǥ
	float _y;					// ��
	bool _goOn;					// �̵� ������
	bool _moveEnd;				// �̵� ���� Ÿ�̹��� �˸��� ����
	bool _isInCamp;				// ķ�� ������ ������
	int _myNum;					// ���� �ѹ�
	int _player;				// ����÷��̾� ��������
	int _currentActionPoint;	// ���� �ൿ��
	int _maxActionPoint;		// �ִ� �ൿ��
	int _currentMana;			// ���� �ֹ���
	int _maxMana;				// �ִ� �ֹ���

	
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