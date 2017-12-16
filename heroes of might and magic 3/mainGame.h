#pragma once
#include "gameNode.h"
#include "mainMenu.h"
#include "mapTool.h"
#include "gameScene.h"

class mainGame : public gameNode
{
private:
	bool _option;

public:
	virtual HRESULT init(void);	
	virtual void release(void);	
	virtual void update(void);	
	virtual void render(void);	

	
	mainGame();
	~mainGame();
};

