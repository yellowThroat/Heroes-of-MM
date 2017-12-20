#pragma once
#include "gameNode.h"


class camp : public gameNode
{
private:


private:
	image* _fieldImg;
	image* _fieldShadowImg;
	image* _cityBackground;

	building _buildingInfo;		// �ǹ� ����
	POINT _cameraArr;			// ī�޶� �迭
	POINT _fieldPoint;			// �ʵ� ��ǥ
	RECT _fieldRect;			// �ʵ� ��Ʈ
	CAMP _camp;					// ���� 
	
	
private:
	char _name[256];			// �� �̸�
	int _player;				// ��� �÷��̾���ΰ�
	int _hall;					// ȸ��
	int _fort;					// ���
	int _pub;					// ������
	int _guild;					// �������
	int _market;				// ����
	int _forge;					// ���尣
	int _level[7];				// Ƽ�� �ǹ�
	int _special[5];			// Ư�� �ǹ�
	int _campNum;				// �� �ѹ�
	bool _cityScene;			// �ǹ� ������ ���Դ°�
	float _cameraX;				// ī�޶� X
	float _cameraY;				// ī�޶� Y



public:

	virtual HRESULT	init(building info);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//============ D R A W ===============
	void fieldDraw(void);
	void castleDraw(void);
	void dungeonDraw(void);

	//========== S E T T I N G ===========
	void buildingInit();
	void buildingCondition(void);
	void cameraSetting(void);
	void setCityScene(bool scene) { _cityScene = scene; }
	void setBuildingInfo(building info) { _buildingInfo = info; }
	void setFrameCycle(void);

	//========== G E T T E R =============
	bool getCityScene() { return _cityScene; }
	building getCityInfo() { return _buildingInfo; }
	int getNum() { return _campNum; }
	int getPlayerNum() { return _player; }
	POINT getFieldPoint() { return _fieldPoint; }

	//========== S E T T E R =============
	void setNum(int num) { _campNum = num; }
	void setPlayer(int num) { _player = num; }

	//========== ADDRESS LINK ============

	camp();
	~camp();
};