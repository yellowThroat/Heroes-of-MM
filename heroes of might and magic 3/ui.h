#pragma once
#include "gameNode.h"

class playMap;

class ui : public gameNode
{
private:
	playMap* _pm;

private:
	RECT _miniMapRect;

private:
	bool _miniMapMove;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//=============== D R A W ==============
	void draw(void);

	//=============== S E T T I N G ===========
	void input(void);

	//=============== G E T T E R ===============
	RECT getMiniMapRect() { return _miniMapRect; }
	bool getMiniMapMove() { return _miniMapMove; }
	


	//=============== S E T T E R ===============
	void setMiniMapMove(bool move) { _miniMapMove = move; }


	//=============== ADRESS LINK===========
	void setPlayMapAddressLink(playMap* mp) { _pm = mp; }




	ui();
	~ui();

};