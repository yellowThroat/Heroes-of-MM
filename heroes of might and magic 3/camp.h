#pragma once
#include "gameNode.h"

class playMap;

class camp : public gameNode
{
private:
	playMap* _pm;

private:
	image* _fieldImg;
	image* _fieldShadowImg;
	image* _cityBackground;

	building _buildingInfo;		// �ǹ� ����
	POINT _camera;				// ī�޶� ����
	POINT _cameraArr;
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
	bool _cityScene;			// �ǹ� ������ ���Դ°�

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

	//========== G E T T E R =============
	bool getCityScene() { return _cityScene; }

	//========== ADDRESS LINK ============
	void setAddressLinkFromPlayMap(playMap* pm) { _pm = pm; }

	camp();
	~camp();
};