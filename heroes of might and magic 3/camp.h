#pragma once
#include "gameNode.h"

struct tagStructure
{
	// ������ ����
	TCHAR name[256];				// �̸�
	TCHAR explantion[256];		// �ǹ� ����
	TCHAR needBuild[256];		// ���� �ǹ�
	int num;					// ���° ĭ�� �ִ°��̴�.
	int level;					// �̰� �� �Ӿ�	
	image* img;					// �ǹ� ����
	image* checkImg;
	int x, y;					// �׸� ��ġ
	int index;					// �Ǽ� ���� ����
	bool needResources;			// �ڿ� ����
	bool needBuilding;			// ��ũƮ�� �ʿ�
	//�ʿ� �ڿ�
	int gold;
	int wood;
	int iron;
	int crystal;
	int mercury;
	int sulfur;
	int gem;
};

struct tagUnitSample
{
	CREATURESTATE state;
	image* img[STATE_END];
	image* shadowImg[STATE_END];
	int x;
	int y;
	
};

struct tagRecruit
{	
	char unit[256];				// ���� �̸�
	char building[256];			// �ǹ� �̸�
	int output;					// �� ���귮
	int remain;					// ���� �� �ִ� ���¼�
	int x, y;					// Ȧ �����ÿ� ��ǥ
	int num;					// ���° ĭ����
	
	int gold;					// �ʿ��� �ڿ���
	int wood;
	int iron;
	int sulfur;
	int mercury;
	int crystal;
	int gem;
	
};

class player;

class camp : public gameNode
{
private:
	player* _play;

private:
	image* _fieldImg;
	image* _fieldShadowImg;
	image* _cityBackground;

	tagUnitSample _unitSample[14];	// ���� ����
	tagStructure _structure[18];	// ����ü ����
	tagRecruit _recruit[7];		// ���� ���� ����
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
	int _levelGrowth[7];		// ũ���� ����
	int _special[5];			// Ư�� �ǹ�
	int _campNum;				// �� �ѹ�
	int _windowNum;				// �� ������?
	bool _cityScene;			// �ǹ� ������ ���Դ°�
	bool _showWindow;			// ���� ��������
	bool _contents;				// ������ �����
	bool _beBuilt;				// �̹��� �ǹ� �̹� ������
	float _cameraX;				// ī�޶� X
	float _cameraY;				// ī�޶� Y
	myProperty _property;		// �÷��̾� �ڿ�
	tagStructure _saveStructure;// ���� �ǹ� ( Ȧ���� )
	tagRecruit _saveRecruit;	// ���� ���� ( ��ä���� )
	


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
	void inputCity();
	void structureInit();
	void unitSampleInit();
	void buildingInit();
	void recruitInit();
	void buildingCondition(void);
	void cameraSetting(void);
	void setCityScene(bool scene) { _cityScene = scene; }
	void setBuildingInfo(building info) { _buildingInfo = info; }
	void setFrameCycle(void);
	void selectBox(void);
	void changeState(image* img, int delay);


	//========== G E T T E R =============
	tagStructure getStructure(int num) { return _structure[num]; }
	myProperty getProperty() { return _property; }
	building getCityInfo() { return _buildingInfo; }
	POINT getFieldPoint() { return _fieldPoint; }
	bool getCityScene() { return _cityScene; }
	bool getWindow() { return _showWindow; }
	bool getContents() { return _contents; }
	int getNum() { return _campNum; }
	int getPlayerNum() { return _player; }
	int getWindowNum() { return _windowNum; }
	//========== S E T T E R =============
	void setNum(int num) { _campNum = num; }
	void setPlayer(int num) { _player = num; }
	void setWindow(bool show) { _showWindow = show; }
	void setWindowNum(int num) { _windowNum = num; }
	void setProperty(myProperty pro) { _property = pro; }
	void setContents(bool contents) { _contents = contents; }
	void setSaveStructure(int stru) { _saveStructure = _structure[stru]; }

	//========== ADDRESS LINK ============

	void setPlayerAddressLink(player* player) { _play = player; }

	camp();
	~camp();
};