#pragma once
#include "gameNode.h"

class battle : public gameNode
{
private:


public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	battle();
	~battle();
};