#include "stdafx.h"
#include "ui.h"
#include "playMap.h"
#include "player.h"
#include "gameScene.h"

ui::ui(){}
ui::~ui(){}

HRESULT ui::init(void)
{

	_miniMapMove = false;
	_mainButton = false;
	_config = false;
	_conButton = false;
	_day = 1;
	_week = 1;
	_month = 1;
	_gb = GB_NULL;
	_firstHero = 0;
	//================  R E C T   M A K E ===============
	_miniMapRect = RectMake(817, 24, 140, 144);
	_summaryRect = RectMake(863, 193, 32, 32);
	_spellRect = RectMake(895, 257, 32, 32);
	_configRect = RectMake(895, 289, 32, 32);
	_heroRect = RectMake(863, 321, 64, 32);
	_turnRect = RectMake(863, 353, 64, 32);
	_goOnRect = RectMake(863, 257, 32, 32);
	_windowConfig = RectMake(200, 30, 480, 486);
	for (int i = 0; i < 6; i++)
	{
		_conRect[i] = RectMake(_windowConfig.left + 246 + 111 * (i % 2),
			_windowConfig.top + 298 + 59 * (i / 2),100,48);
	}

	return S_OK;
}

void ui::release(void)
{

}

void ui::update(void)
{
	setButton();
}

void ui::render(void)
{
	draw();
}

void ui::draw(void)
{
	char tmp[10];
	IMAGEMANAGER->findImage(itoa(DATABASE->getSaveNum(),tmp,10))->render(getMemDC(),817,24);

	IMAGEMANAGER->findImage("gameMiniview")->render(getMemDC(),
		_miniMapRect.left + _pm->getCameraArr().x * 2,
		_miniMapRect.top + _pm->getCameraArr().y * 2);

	IMAGEMANAGER->findImage("gameUI")->render(getMemDC());
	
	numberDraw(getMemDC(), _player->getProperty().wood, 45, 582);
	numberDraw(getMemDC(), _player->getProperty().mercury, 156, 582);
	numberDraw(getMemDC(), _player->getProperty().iron, 265, 582);
	numberDraw(getMemDC(), _player->getProperty().sulfur, 376, 582);
	numberDraw(getMemDC(), _player->getProperty().crystal, 487, 582);
	numberDraw(getMemDC(), _player->getProperty().gem, 600, 582);
	numberDraw(getMemDC(), _player->getProperty().gold, 716, 582);
	numberDraw(getMemDC(), _month, 858, 579);
	numberDraw(getMemDC(), _week, 895, 579);
	numberDraw(getMemDC(), _day, 932, 579);
	
	for (int i = _firstHero; i < _firstHero + 5; i++)
	{
		if (i >= _player->getHero().size()) break;

		int ap = _player->getHero()[i]->getAP();
		int mana = _player->getHero()[i]->getMana();

		_player->getHero()[i]->getHeroInfo().portraitSmall->frameRender(getMemDC(),
			804, 211 + 32 * i,
			_player->getHero()[i]->getHeroInfo().indexX,
			_player->getHero()[i]->getHeroInfo().indexY);

		//=== 마나통 최대는 100 행동력통 최대는 2200
		IMAGEMANAGER->findImage("bar_ap")->render(getMemDC(), 798,
			211 + 32 * i + (2200 - ap)*0.01363,
			0, (2200 - ap)*0.01363, 6, 30 - (2200 - ap)*0.01363);

		IMAGEMANAGER->findImage("bar_mana")->render(getMemDC(), 851,
			211 + 32 * i + (100 - mana)*0.3,
			0, (100 - mana)*0.3, 6, 30 - (100- mana)*0.3);




	}

	IMAGEMANAGER->findImage("select_hero")->render(getMemDC(),
		803, 210 + (_player->getCurrentHero() - _firstHero) * 32);


	if (_mainButton)
	{
		switch (_gb)
		{
		case GB_SUMMARY:
		 IMAGEMANAGER->findImage("gamebutton_summary")->render(getMemDC(),
			_summaryRect.left, _summaryRect.top);
		break;
		
		case GB_SPELL:
		 IMAGEMANAGER->findImage("gamebutton_spell")->render(getMemDC(),
		_spellRect.left, _spellRect.top);
		break;
		
		case GB_CONFIG:
		 IMAGEMANAGER->findImage("gamebutton_config")->render(getMemDC(),
		_configRect.left, _configRect.top);
		break;
		
		case GB_HERO:
		 IMAGEMANAGER->findImage("gamebutton_hero")->render(getMemDC(),
		_heroRect.left, _heroRect.top);
		break;
		
		case GB_TURN:
		 IMAGEMANAGER->findImage("gamebutton_turn")->render(getMemDC(),
		_turnRect.left, _turnRect.top);
		break;

		case GB_GOON:
		IMAGEMANAGER->findImage("gamebutton_goon")->render(getMemDC(),
			_goOnRect.left, _goOnRect.top);
		break;		

		case GB_NULL:
		break;
		}
	}

	if (_config)
	{
		IMAGEMANAGER->findImage("window_config")->render(getMemDC(), _windowConfig.left, _windowConfig.top);
		


		if (_conButton)
		{
			switch (_cb)
			{
			case CONFIG_LOAD:
				IMAGEMANAGER->findImage("gamebutton_load")->render(getMemDC(),
					_conRect[0].left, _conRect[0].top);
				break;
			case CONFIG_SAVE: 
				IMAGEMANAGER->findImage("gamebutton_save")->render(getMemDC(),
					_conRect[1].left, _conRect[1].top);
				break;
			case CONFIG_RE:
				IMAGEMANAGER->findImage("gamebutton_re")->render(getMemDC(),
					_conRect[2].left, _conRect[2].top);
				break;
			case CONFIG_MAIN:
				IMAGEMANAGER->findImage("gamebutton_main")->render(getMemDC(),
					_conRect[3].left, _conRect[3].top);
				break;
			case CONFIG_QUIT:
				IMAGEMANAGER->findImage("gamebutton_quit")->render(getMemDC(),
					_conRect[4].left, _conRect[4].top);
				break;
			case CONFIG_RETURN:
				IMAGEMANAGER->findImage("gamebutton_return")->render(getMemDC(),
					_conRect[5].left, _conRect[5].top);
				break;
			case CONFIG_NULL:
				break;
			}

		}
	}







}

void ui::setButton(void)
{
	for (int i = 0; i < 6; i++)
	{
		if (!PtInRect(&_conRect[i], _ptMouse) && _cb == (CONBUTTON)i)
		{
			_conButton = false;
		}
	}

	switch (_gb)
	{
	case GB_SUMMARY:
	if (!PtInRect(&_summaryRect, _ptMouse))
	{
		_mainButton = false;
	}
		break;
	case GB_SPELL:
		if (!PtInRect(&_spellRect, _ptMouse))
	{
		_mainButton = false;
	}
	break;
	case GB_CONFIG:
		if (!PtInRect(&_configRect, _ptMouse))
	{
		_mainButton = false;
	}
	break;
	case GB_HERO:
		if (!PtInRect(&_heroRect, _ptMouse))
	{
		_mainButton = false;
	}
	break;
	case GB_TURN:
		if (!PtInRect(&_turnRect, _ptMouse))
	{
		_mainButton = false;
	}
	break;
	case GB_GOON:
	if (!PtInRect(&_goOnRect, _ptMouse))
	{
		_mainButton = false;
	}
	break;

	case GB_NULL:
		break;
	}
}

void ui::input(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		
		//===================== F I E L D   S C E N E ==============
		if (!_player->getScene())
		{
			if (PtInRect(&_miniMapRect, _ptMouse) || _miniMapMove)
			{
				if (!_config)
				{
					_miniMapMove = true;
					POINT camera;
					camera.x = (_ptMouse.x - 12 * 2 - _miniMapRect.left) / 2 * TILESIZE;
					camera.y = (_ptMouse.y - 9 * 2 - _miniMapRect.top) / 2 * TILESIZE;

					if (camera.x <= -8 * TILESIZE) camera.x = -8 * TILESIZE;
					if (camera.y <= -6 * TILESIZE) camera.y = -6 * TILESIZE;
					if (camera.x >= 56 * TILESIZE) camera.x = 56 * TILESIZE;
					if (camera.y >= 60 * TILESIZE) camera.y = 60 * TILESIZE;

					_pm->setCameraX(camera.x);
					_pm->setCameraY(camera.y);

					_player->setAutoCamera(false);

				}
			}





		}



	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_player->getScene() && !_player->getWindow())
		{
			//=============== F I E L D   S C E N E
			if (_config && PtInRect(&_windowConfig, _ptMouse))
			{
				for (int i = 0; i < 6; i++)
				{
					if (PtInRect(&_conRect[i], _ptMouse))
					{
						_cb = (CONBUTTON)i;
						_conButton = true;
					}
				}
			}

			//======================= 
			if (!_config)
			{
				if (PtInRect(&_summaryRect, _ptMouse))
				{
					_gb = GB_SUMMARY;
					_mainButton = true;
				}
				if (PtInRect(&_spellRect, _ptMouse))
				{
					_gb = GB_SPELL;
					_mainButton = true;
				}
				if (PtInRect(&_configRect, _ptMouse))
				{
					_gb = GB_CONFIG;
					_mainButton = true;
				}
				if (PtInRect(&_heroRect, _ptMouse))
				{
					_gb = GB_HERO;
					_mainButton = true;
				}
				if (PtInRect(&_turnRect, _ptMouse))
				{
					_gb = GB_TURN;
					_mainButton = true;
				}
				if (PtInRect(&_goOnRect, _ptMouse))
				{
					_gb = GB_GOON;
					_mainButton = true;
				}
			}

			//================ 영웅 선택할때

			for (int i = 0; i < 5; i++)
			{
				if (PtInRect(&RectMake(804, 211 + i*32, 46, 30), _ptMouse))
				{
					if (i + _firstHero < _player->getHero().size())
					{
						if (i + _firstHero != _player->getCurrentHero())
						{
							_player->setCurrentHero(i + _firstHero);
					
							for (int j = 0; j < _player->getHero().size(); j++)
							{
								if (i + _firstHero == _player->getHero()[j]->getMyNum())
								{
									POINT point;
									point.x = _player->getHero()[j]->getHeroPoint().x;
									point.y = _player->getHero()[j]->getHeroPoint().y;

									_pm->setCameraX((point.x - 12) * TILESIZE);
									_pm->setCameraY((point.y - 9) * TILESIZE);

									_player->setAutoCamera(false);
								}
							}
						}
						else
						{
							_player->setWindow(true);
						}




					}
				}
			}


		}
		

	}


	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_mainButton && !_config)
		{
			switch (_gb)
			{
			case GB_SUMMARY:
				break;
			case GB_SPELL:
				break;
			case GB_CONFIG: _config = true;
				break;
			case GB_HERO:
				int tmp;
				tmp = _player->getCurrentHero() +1;
				if (_player->getHero().size() <= tmp) tmp = 0;
				_player->setCurrentHero(tmp);

				POINT point;
				point.x = _player->getHero()[_player->getCurrentHero()]->getHeroPoint().x;
				point.y = _player->getHero()[_player->getCurrentHero()]->getHeroPoint().y;

				_pm->setCameraX((point.x - 12) * TILESIZE);
				_pm->setCameraY((point.y - 9) * TILESIZE);


				break;
			case GB_TURN: 

				if (_day < 7)
				{
					_day++;
					_player->dayGo();
				}
				else
				{
					_day = 1;

					if (_week < 4)	_week++;
					else
					{
						_week = 1;
						_month++;
					}
					_player->dayGo();
					_player->weekGo();
				}

				break;
			case GB_GOON:
				if (_player->getHero()[_player->getCurrentHero()]->getPath().size())
				{
					_player->getHero()[_player->getCurrentHero()]->setGoOn(true);
					_gs->getvCamp()[_player->getHero()[_player->getCurrentHero()]->getInCamp()]->setHero(false);
				}

				break;
			case GB_NULL:
				break;
			}

		}

		if (_config && _conButton)
		{
			switch (_cb)
			{
			case CONFIG_LOAD:
				break;
			case CONFIG_SAVE:
				break;
			case CONFIG_RE:
				break;
			case CONFIG_MAIN: SCENEMANAGER->changeScene("mainMenu");
				break;
			case CONFIG_QUIT: PostQuitMessage(0);
				break;
			case CONFIG_RETURN: _config = false;
				break;
			case CONFIG_NULL:
				break;
			}

			_conButton = false;

		}

		_miniMapMove = false;
		_mainButton = false;


	}
}