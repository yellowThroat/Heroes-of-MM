#pragma once
#include "gameNode.h"

class gameScene : public gameNode
{
private:

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

		

	gameScene();
	~gameScene();

};