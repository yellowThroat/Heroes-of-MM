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

struct tagBattleCreature
{

	float x, y;				// ==== ��ǥ 
	int arrX, arrY;			// ==== �迭 ��ǥ
	int target;				// ==== ����� ����Ű����
	int num;				// ==== ����Ű�³��� �迭��ȣ
	
	bool isRight;			// ��� ���� �ִ�?
	bool player;			// �÷��̾�� �ƴϳ�

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

private:
	int _battleNum;									// � ���忡�� �ο쳪
	int _obstacle;									// � ��ֹ��� ���
	bool _showGrid;									// �׸��� ������?
	bool _attribute;								// closed grid ������?
	bool _changeScene;								// �� �ٲٴ¿�
public:
	HRESULT init(int x);
	void release(void);
	void update(void);
	void render(void);

	//============  D R A W =============
	void battleDraw(void);
	void buttonDraw(void);


	//============ U P D A T E ==========
	void setObstacle(void);
	void inputBattle(void);
	void activeButton(void);
	void joinCreature(tagCreature creature);
	POINT getMouseArr(void);

	//========== HEXA A STAR =============
	bool alreadyClosed(int x, int y);
	bool alreadyOpend(int x, int y);
	int getValueH(int x, int y, int destX,int destY);
	vector<POINT> getPath(int x, int y, int destX, int destY);	// ã�� ���


	//============ G E T T E R ===========
	bool getChangeScene() { return _changeScene; }

	battle();
	~battle();
};