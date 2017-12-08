#pragma once

#include "gameNode.h"

class mapTool : public gameNode
{
private:
	tagTileInfo _mapArr[MAXTILE][MAXTILE];


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	mapTool();
	~mapTool();
};