#pragma once
#include "gameNode.h"

class playMap;
class gameScene;
class player;

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
	gameScene* _gs;
	player* _player;

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
	bool _mainButton;				// 게임화면 중 버튼 눌렀는가
	bool _miniMapMove;				// 미니맵 이동 중인가
	bool _config;					// 환경설정 창이 열렸는가
	bool _conButton;				// 환경설정 창에서 버튼을 눌렀는가
	int _firstHero;					// 초상화 나타낼 첫번재 영웅은 누규?
	int _firstCamp;					// 첫번째 진영은 엉듸?
	int _month;						// 시간 - 달
	int _week;						// 시간 - 주
	int _day;						// 시간 - 일
	float _bgmVolume;					// 브금 소리 조절
	float _effectVolume;				// 효과음 소리 조절

	bool _changeScene;				// 체인지 신
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
	void bgmVolumeControl();
	void effectVolumeControl();

	//=============== G E T T E R ===============
	RECT getMiniMapRect() { return _miniMapRect; }
	bool getMiniMapMove() { return _miniMapMove; }
	bool getConfig() { return _config; }
	bool getChangeScene() { return _changeScene; }

	//=============== S E T T E R ===============
	void setMiniMapMove(bool move) { _miniMapMove = move; }


	//=============== ADRESS LINK===========
	void setPlayMapAddressLink(playMap* mp) { _pm = mp; }
	void setgameSceneAddressLink(gameScene* gs) { _gs = gs; }
	void setPlayerAddressLink(player* player) { _player= player; }




	ui();
	~ui();

};