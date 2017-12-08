#pragma once
#include "gameNode.h"

class mainMenu : public gameNode
{
private:
	RECT _mapTool;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	
	
	void imageInit(void);


	mainMenu();
	~mainMenu();


};