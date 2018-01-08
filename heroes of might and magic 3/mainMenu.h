#pragma once
#include "gameNode.h"


class mainMenu : public gameNode
{
private:
	
private:
	MMB _currentButton;
	SAVE _saveFile[MAXSAVE];

	RECT _mapTool;
	RECT _saveWindow0;
	RECT _saveWindow1;

private:
	bool _buttonActive;
	bool _newActive;
	bool _sceneChange;

	int _saveNum;
	int _fadeAlpha;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	//===============  D R A W =============
	void backgroundDraw(void);
	void buttonDraw(void);
	void windowDraw(void);
	



	//============= S E T T I N G ==========
	void imageInit(void);
	void soundInit(void);
	void buttonActive(void);
	void inputMenu(void);
	void windowMove(void);
	void sceneChange(void);

	//============= L O A D ========
	void loadFileList(void);
	void loadMap(string mapName);


	//============= G E T T E R ===================
	int getSaveNum() { return _saveNum; }


	//===============  A D D R E S S   L I N K ===================

	mainMenu();
	~mainMenu();


};