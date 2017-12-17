#pragma once
#include "gameNode.h"

class playMap;

enum GAMEBUTTON
{
	GB_SUMMARY,
	GB_SPELL,
	GB_CONFIG,
	GB_HERO,
	GB_TURN,
	GB_GOON,
	GB_NULL
};

enum CONBUTTON
{
	CONFIG_LOAD,
	CONFIG_SAVE,
	CONFIG_RE,
	CONFIG_MAIN,
	CONFIG_QUIT,
	CONFIG_RETURN,
	CONFIG_NULL
};

class ui : public gameNode
{
private:
	playMap* _pm;

private:
	RECT _miniMapRect;
	RECT _summaryRect;
	RECT _spellRect;
	RECT _configRect;
	RECT _heroRect;
	RECT _turnRect;
	RECT _goOnRect;
	RECT _windowConfig;
	RECT _conRect[6];

	GAMEBUTTON _gb;
	CONBUTTON _cb;

private:
	bool _mainButton;				// ����ȭ�� �� ��ư �����°�
	bool _miniMapMove;				// �̴ϸ� �̵� ���ΰ�
	bool _config;					// ȯ�漳�� â�� ���ȴ°�
	bool _conButton;				// ȯ�漳�� â���� ��ư�� �����°�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//=============== D R A W ==============
	void draw(void);

	//=============== S E T T I N G ===========
	void input(void);
	void setButton(void);

	//=============== G E T T E R ===============
	RECT getMiniMapRect() { return _miniMapRect; }
	bool getMiniMapMove() { return _miniMapMove; }
	bool getConfig() { return _config; }


	//=============== S E T T E R ===============
	void setMiniMapMove(bool move) { _miniMapMove = move; }


	//=============== ADRESS LINK===========
	void setPlayMapAddressLink(playMap* mp) { _pm = mp; }




	ui();
	~ui();

};