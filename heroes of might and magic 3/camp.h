#pragma once
#include "gameNode.h"

struct tagStructure
{
	// ������ ����
	char name[256];
	int num;
	int level;
	image* img;

	//�ʿ� �ڿ�
	int gold;
	int wood;
	int iron;
	int crystal;
	int mercury;
	int sulfur;
	int gem;
};

class camp : public gameNode
{
private:


private:
	image* _fieldImg;
	image* _fieldShadowImg;
	image* _cityBackground;

	tagStructure _structure[18];// ����ü ����
	building _buildingInfo;		// ķ�� ����
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
	int _windowNum;				// �� ������?
	bool _cityScene;			// �ǹ� ������ ���Դ°�
	bool _showWindow;			// ���� ��������
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
	void structureInit();
	void buildingInit();
	void buildingCondition(void);
	void cameraSetting(void);
	void setCityScene(bool scene) { _cityScene = scene; }
	void setBuildingInfo(building info) { _buildingInfo = info; }
	void setFrameCycle(void);
	void selectBox(void);


	//========== G E T T E R =============
	building getCityInfo() { return _buildingInfo; }
	POINT getFieldPoint() { return _fieldPoint; }
	bool getCityScene() { return _cityScene; }
	bool getWindow() { return _showWindow; }
	int getNum() { return _campNum; }
	int getPlayerNum() { return _player; }
	int getWindowNum() { return _windowNum; }

	//========== S E T T E R =============
	void setNum(int num) { _campNum = num; }
	void setPlayer(int num) { _player = num; }
	void setWindow(bool show) { _showWindow = show; }
	void setWindowNum(int num) { _windowNum = num; }


	//========== ADDRESS LINK ============

	camp();
	~camp();
};