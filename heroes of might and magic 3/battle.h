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
	int arrX;					// 배열 좌표 x
	int arrY;					// 배열 좌표 y
	int destX;					// 실제 시작 좌표 x
	int destY;					// 실제 시작 좌표 y
	int ground;					// 땅 좌표
	int center;					// 중점
	bool closed;				// 이동 가능?
	bool unit;					// 이미 누가 있는가?
	bool range;					// 이동 범위에 있는가?
	bool attack;				// 공격 범위에 있는가?
	
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

	float x, y;				// ==== 좌표 
	float angle;			// ==== 각도
	
	int arrX, arrY;			// ==== 배열 좌표
	int target;				// ==== 어떤놈을 가리키느냐
	int arrNum;

	int sourX;				// ==== 프레임 x
	int sourY;				// ==== 프레임 y
	int count;				// ==== 프레임 돌리는용
	int attackTarget;		// ==== 누구 때림?

	bool counter;			// ==== 반격했늬?
	bool isRight;			// 어디 보고 있늬?
	bool player;			// 플레이어냐 아니냐
	bool turn;

	bool operator<(const tagBattleCreature&v) const {
		return (y< v.y);
	}

};


class battle : public gameNode
{
private:

private:
	tagGridInfo _battleArr[MAXGRIDX][MAXGRIDY];		// 전장 좌표
	vector<tagHexaFind> _openlist;					// 헥사 a스타 
	vector<tagHexaFind> _closelist;					// 헥사 a스타
	vector<POINT> _vPath;							// 사용할 경로
	vector<tagBattleCreature> _vBattle;				// 좌표, 등에 사용
	vector<tagCreature> _vCreature;					// 전투에 참여하는 얘들 
private:
	BATTLEBUTTON _button;
	BATTLECONFIG _buttonConfig;
	BATTLECURSOR _cursor;

private:
	int _battleNum;									// 어떤 전장에서 싸우나
	int _obstacle;									// 어떤 장애물을 깔까
	int _currentCreature;							// 현재 턴인 크리쳐는 무엇인가?
	bool _showGrid;									// 그리드 보여줌?
	bool _attribute;								// closed grid 보여줌?
	bool _changeScene;								// 신 바꾸는용
	bool _move;										// 이동 중
	bool _attack;									// 때리러 가는 중
	bool _cursorInGrid;								// 마우스가 격자 안에 있는가?
	bool _turn;										// 이번턴이 끝났는가?
	bool _youWin;									// 이겻늬??
	bool _youLose;									// 졌늬?
	float _angle;									// 마우스 근접공격 앵글
	
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
	void setArrNum(void);							// 두 벡터간 상호간의 통신을 위해
	void setCondition(void);						// 크리쳐의 위치가 어디 배열인지
	void creatureMove(void);						// 현재 크리쳐를 이동 시켜보자
	void setTurn(void);								// 턴이 돌아가는것
	void frameCycle(void);
	POINT getMouseArr(void);
	POINT getArr(POINT xy);
	int isAnybody(int x, int y);					// 누가 거기에 있는지 없는지
	int isAnybody(int x, int y, bool arrNum);		// 누가 거기에 있는지 없는지 배열 넘버
	bool canGo(int destX, int destY, int x,int size);						// 그 방향으로 갈수 있늬?

	//========== HEXA A STAR =============
	bool alreadyClosed(int x, int y);
	bool alreadyOpend(int x, int y);
	int getValueH(int x, int y, int destX,int destY);
	vector<POINT> getPath(int x, int y, int destX, int destY, bool fly);	// 찾은 경로


	//============ G E T T E R ===========
	bool getChangeScene() { return _changeScene; }
	bool getWin() { return _youWin; }
	bool getLose() { return _youLose; }


	battle();
	~battle();
};