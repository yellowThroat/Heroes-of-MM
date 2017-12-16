#pragma once
#include "gameNode.h"
#include "playMap.h"
#include "ui.h"

class gameScene : public gameNode
{
private:
	playMap* _pm;
	ui* _ui;


private:

	int _fadeAlpha;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//=========== S E T T I N G =============
	void inputCommon(void);
	void inputPlay(void);

	gameScene();
	~gameScene();

};