#pragma once
#include "gameNode.h"


class mainMenu : public gameNode
{
private:

private:
	RECT _mapTool;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	
	
	void imageInit(void);


	//===============  A D D R E S S   L I N K ===================

	mainMenu();
	~mainMenu();


};