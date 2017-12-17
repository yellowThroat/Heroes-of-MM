#pragma once
#include "gameNode.h"

class hero : public gameNode
{

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	hero();
	~hero();
};