#pragma once
#include "gameNode.h"

#define	MAXGRIDX 15
#define MAXGRIDY 11

struct tagHexaFind
{
	int f;
	int g;
	int h;
	int nodeX, nodeY;
	int parentX, parentY;

	bool operator<(const tagHexaFind &v) const {
		return (f  < v.f);
	}
};

struct tagGridInfo
{
	int arrX;					// �迭 ��ǥ x
	int arrY;					// �迭 ��ǥ y
	int destX;					// ���� ���� ��ǥ x
	int destY;					// ���� ���� ��ǥ y
	int ground;					// �� ��ǥ
	int center;					// ����
	bool closed;				// �̵� ����?
	bool unit;					// �̹� ���� �ִ°�?
	bool range;					// �̵� ������ �ִ°�?
	bool attack;				// ���� ������ �ִ°�?
	
};

enum BATTLEBUTTON
{
	BAB_NULL = -1, 
	BAB_CONFIG,
	BAB_RUN,
	BAB_SPELL,
	BAB_WAIT,
	BAB_DEF,
	BAB_END
};

enum BATTLECONFIG
{
	BAC_NULL = -1,
	BAC_LOAD,
	BAC_RE,
	BAC_MAIN,
	BAC_RETURN,
	BAC_DEFAULT,
	BAC_END
};

enum BATTLECURSOR
{
	CUR_IDLE,
	CUR_MOVE,
	CUR_ATKMELEE,
	CUR_ATKRANGE,
	CUR_END
};

struct tagBattleCreature
{

	float x, y;				// ==== ��ǥ 
	float angle;			// ==== ����
	
	int arrX, arrY;			// ==== �迭 ��ǥ
	int target;				// ==== ����� ����Ű����
	int arrNum;

	int sourX;				// ==== ������ x
	int sourY;				// ==== ������ y
	int count;				// ==== ������ �����¿�
	int attackTarget;		// ==== ���� ����?

	bool counter;			// ==== �ݰ��ߴ�?
	bool isRight;			// ��� ���� �ִ�?
	bool player;			// �÷��̾�� �ƴϳ�
	bool turn;

	bool operator<(const tagBattleCreature&v) const {
		return (y< v.y);
	}

};


class battle : public gameNode
{
private:

private:
	tagGridInfo _battleArr[MAXGRIDX][MAXGRIDY];		// ���� ��ǥ
	vector<tagHexaFind> _openlist;					// ��� a��Ÿ 
	vector<tagHexaFind> _closelist;					// ��� a��Ÿ
	vector<POINT> _vPath;							// ����� ���
	vector<tagBattleCreature> _vBattle;				// ��ǥ, � ���
	vector<tagCreature> _vCreature;					// ������ �����ϴ� ��� 
private:
	BATTLEBUTTON _button;
	BATTLECONFIG _buttonConfig;
	BATTLECURSOR _cursor;

private:
	int _battleNum;									// � ���忡�� �ο쳪
	int _obstacle;									// � ��ֹ��� ���
	int _currentCreature;							// ���� ���� ũ���Ĵ� �����ΰ�?
	bool _showGrid;									// �׸��� ������?
	bool _attribute;								// closed grid ������?
	bool _changeScene;								// �� �ٲٴ¿�
	bool _move;										// �̵� ��
	bool _attack;									// ������ ���� ��
	bool _cursorInGrid;								// ���콺�� ���� �ȿ� �ִ°�?
	bool _turn;										// �̹����� �����°�?
	bool _youWin;									// �̰��??
	bool _youLose;									// ����?
	float _angle;									// ���콺 �������� �ޱ�
	
public:
	HRESULT init(int x);
	void release(void);
	void update(void);
	void render(void);

	//============  D R A W =============
	void battleDraw(void);
	void buttonDraw(void);
	void creatureDraw(void);

	//============ U P D A T E ==========
	void endBattle(void);
	void enemyAction(void);
	void cursorChange(void);
	void setObstacle(void);
	void inputBattle(void);
	void activeButton(void);
	void joinCreature(tagCreature creature);
	void joinCreature(tagObject object);
	void setArrNum(void);							// �� ���Ͱ� ��ȣ���� ����� ����
	void setCondition(void);						// ũ������ ��ġ�� ��� �迭����
	void creatureMove(void);						// ���� ũ���ĸ� �̵� ���Ѻ���
	void setTurn(void);								// ���� ���ư��°�
	void frameCycle(void);
	POINT getMouseArr(void);
	POINT getArr(POINT xy);
	int isAnybody(int x, int y);					// ���� �ű⿡ �ִ��� ������
	int isAnybody(int x, int y, bool arrNum);		// ���� �ű⿡ �ִ��� ������ �迭 �ѹ�
	bool canGo(int destX, int destY, int x,int size);						// �� �������� ���� �ִ�?

	//========== HEXA A STAR =============
	bool alreadyClosed(int x, int y);
	bool alreadyOpend(int x, int y);
	int getValueH(int x, int y, int destX,int destY);
	vector<POINT> getPath(int x, int y, int destX, int destY, bool fly);	// ã�� ���


	//============ G E T T E R ===========
	bool getChangeScene() { return _changeScene; }
	bool getWin() { return _youWin; }
	bool getLose() { return _youLose; }


	battle();
	~battle();
};