#pragma once
#include "gameNode.h"

class player;

class zOrder : public gameNode
{
private:
	player* _player;

private:
	typedef vector<tagRender> vRender;
		
	vRender _vRender;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addRender(tagRender render);

	void setPlayerAddressLink(player* pl) { _player = pl; }


	zOrder();
	~zOrder();
};