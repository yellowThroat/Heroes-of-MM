#include "stdafx.h"
#include "ui.h"
#include "playMap.h"


ui::ui(){}
ui::~ui(){}

HRESULT ui::init(void)
{

	_miniMapMove = false;
	_mainButton = false;
	_config = false;
	_conButton = false;
	_gb = GB_NULL;
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

				_pm->setCamera(camera);

			}
		}


	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
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
				break;
			case GB_TURN:
				break;
			case GB_GOON:
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