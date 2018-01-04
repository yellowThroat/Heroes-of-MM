#include "stdafx.h"
#include "battle.h"

battle::battle()
{
	_showGrid = true;
	_changeScene = false;

}
battle::~battle() {}

HRESULT battle::init(int x)
{
	_changeScene = false;
	_battleNum = x;
	_attribute = false;
	_changeScene = false;
	_button = BAB_NULL;
	_buttonConfig = BAC_NULL;
	for (int i = 0; i < MAXGRIDX; i++)
	{
		for (int j = 0; j < MAXGRIDY; j++)
		{
			ZeroMemory(&_battleArr[i][j], sizeof(tagGridInfo));

			_battleArr[i][j].arrX = i;
			_battleArr[i][j].arrY = j;
			_battleArr[i][j].ground = 127 + 42 * j;
			_battleArr[i][j].destY = 87 + 42 * j;
			if (j % 2)
			{
				_battleArr[i][j].center = 80 + 44 * i;
				_battleArr[i][j].destX = 59 + 44 * i;

			}
			else
			{
				_battleArr[i][j].center = 102 + 44 * i;
				_battleArr[i][j].destX = 81 + 44 * i;
			}
			_battleArr[i][j].closed = false;
		}
	}

	switch (_battleNum)
	{
	case 0:
		//_obstacle = RND->getInt(2);

		_obstacle = 0;
	break;
	case 1:
		
	break;
	}


	setObstacle();

	return S_OK;
}

void battle::release(void)
{

}

void battle::update(void)
{
	_vPath = getPath(2, 3, getMouseArr().x, getMouseArr().y);



	activeButton();
}

void battle::render(void)
{
	battleDraw();
	buttonDraw();
}

void battle::buttonDraw(void)
{
	switch (_button)
	{
	case BAB_NULL:
		break;
	case BAB_CONFIG:
		IMAGEMANAGER->findImage("battle_window_config")->render(getMemDC(), 159, 54);
		IMAGEMANAGER->findImage("battle_window_config_shadow")->alphaRender(getMemDC(), 159, 54, 150);

		if (!_showGrid) IMAGEMANAGER->findImage("battle_off")->render(getMemDC(), 184, 110);

		IMAGEMANAGER->findImage("battle_load")->frameRender(getMemDC(), 183, 472);
		IMAGEMANAGER->findImage("battle_re")->frameRender(getMemDC(), 294, 472);
		IMAGEMANAGER->findImage("battle_main")->frameRender(getMemDC(), 405, 472);
		IMAGEMANAGER->findImage("battle_return")->frameRender(getMemDC(), 516, 472);
		IMAGEMANAGER->findImage("battle_default")->frameRender(getMemDC(), 516, 413);


		break;
	case BAB_RUN:
		break;
	case BAB_SPELL:
		break;
	case BAB_WAIT:
		break;
	case BAB_DEF:
		break;
	case BAB_END:
		break;
	}

}

void battle::battleDraw()
{


	if (!_battleNum)
	{
		IMAGEMANAGER->findImage("battle_green")->render(getMemDC());

		if(_obstacle == 0)
		IMAGEMANAGER->findImage("hill")->render(getMemDC(), 134, 268);
		else if (_obstacle == 1)
		{
			IMAGEMANAGER->findImage("pond")->render(getMemDC(), 301, 337);

			IMAGEMANAGER->findImage("log")->render(getMemDC(), 301, 171);
		}

	}
	else
	{
		IMAGEMANAGER->findImage("battle_lava")->render(getMemDC());
	}
	if (_showGrid)
	{
		IMAGEMANAGER->findImage("grid_set")->render(getMemDC());
	}

	for (int i = 0; i < MAXGRIDX; i++)
	{
		for (int j = 0; j < MAXGRIDY; j++)
		{
			char tmp[256];
			sprintf(tmp, "(%d,%d)", i, j);


			//IMAGEMANAGER->findImage("grid")->alphaRender(getMemDC(),
			//	_battleArr[i][j].destX, _battleArr[i][j].destY, 50);

			HFONT font = CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("µ¸¿òÃ¼"));
			HFONT oldfont = (HFONT)SelectObject(getMemDC(), font);
			SelectObject(getMemDC(), font);

			SetTextColor(getMemDC(), RGB(255, 255, 255));

			TextOut(getMemDC(), _battleArr[i][j].center - strlen(tmp)*3 , _battleArr[i][j].ground - 24, tmp, strlen(tmp));
			SelectObject(getMemDC(), oldfont);
			DeleteObject(font);
			SetTextColor(getMemDC(), RGB(0, 0, 0));
		}
	}


	if (_attribute)
	{
		for (int i = 0; i < MAXGRIDX; i++)
		{
			for (int j = 0; j < MAXGRIDY; j++)
			{
				
				if(_battleArr[i][j].closed)
				IMAGEMANAGER->findImage("grid_closed")->render(getMemDC(),
					_battleArr[i][j].destX, _battleArr[i][j].destY);


			}
		}
	}


	IMAGEMANAGER->findImage("battle_ui")->render(getMemDC(), 0, 556);
	IMAGEMANAGER->findImage("battle_config")->frameRender(getMemDC(), 3, 559);
	IMAGEMANAGER->findImage("battle_run")->frameRender(getMemDC(), 105, 559);
	IMAGEMANAGER->findImage("battle_spell")->frameRender(getMemDC(), 645, 559);
	IMAGEMANAGER->findImage("battle_wait")->frameRender(getMemDC(), 696, 559);
	IMAGEMANAGER->findImage("battle_def")->frameRender(getMemDC(), 747, 559);



	//==============  T E S T ========================
	numberDraw(getMemDC(), getMouseArr().x, WINSIZEX / 2 - 14, 10);
	numberDraw(getMemDC(), getMouseArr().y, WINSIZEX / 2 + 14, 10);

	if (getMouseArr().x >= 0 && getMouseArr().x < MAXGRIDX &&
		getMouseArr().y >= 0 && getMouseArr().y < MAXGRIDY)
	{
		IMAGEMANAGER->findImage("grid")->render(getMemDC(),
			_battleArr[getMouseArr().x][getMouseArr().y].destX,
			_battleArr[getMouseArr().x][getMouseArr().y].destY);
	}

	for (int i = 0; i < _vPath.size(); i++)
	{
		Rectangle(getMemDC(),
			_battleArr[_vPath[i].x][_vPath[i].y].center - 10,
			_battleArr[_vPath[i].x][_vPath[i].y].destY + 20,
			_battleArr[_vPath[i].x][_vPath[i].y].center + 10,
			_battleArr[_vPath[i].x][_vPath[i].y].destY + 40);
	}

}

POINT battle::getMouseArr(void)
{
	POINT point;
	point.x = -1;
	point.y = -1;
	for (int i = 0; i < MAXGRIDX; i++)
	{
		for (int j = 0; j < MAXGRIDY; j++)
		{
			if (PtInRect(&RectMake(_battleArr[i][j].destX, _battleArr[i][j].destY, 43, 50), _ptMouse))
			{
				point.x = i;
				point.y = j;

				if (_ptMouse.y < _battleArr[i][j].destY + 10)
				{
					if (_ptMouse.x < _battleArr[i][j].destX + 19)
					{
						if (_battleArr[i][j].destY + 10 - _ptMouse.y >
							10.0f / 19.0f*(_ptMouse.x - _battleArr[i][j].destX))
						{
							if (j % 2 == 1) point.x--;
							point.y--;
						}



					}
					else if (_ptMouse.x >= _battleArr[i][j].destX + 24)
					{
						if (_battleArr[i][j].destY + 10 - _ptMouse.y >
							10.0f / 19.0f*(_battleArr[i][j].destX + 43 - _ptMouse.x))
						{
							if (j % 2 == 0) point.x++;
							point.y--;
						}

					}



				}
				else if(_ptMouse.y >= _battleArr[i][j].destY + 40)
				{
					if (_ptMouse.x < _battleArr[i][j].destX + 19)
					{
						if (10 -(_battleArr[i][j].destY + 50 - _ptMouse.y) >
							10.0f / 19.0f*(_ptMouse.x - _battleArr[i][j].destX))
						{
							if (j % 2 == 1) point.x--;
							point.y++;
						}



					}
					else if (_ptMouse.x >= _battleArr[i][j].destX + 24)
					{
						if (10 -(_battleArr[i][j].destY + 50 - _ptMouse.y) >
							10.0f / 19.0f*(_battleArr[i][j].destX + 43 - _ptMouse.x))
						{
							if (j % 2 == 0) point.x++;
							point.y++;
						}

					}

				}



			}
		}
	}
	return point;
}

void battle::joinCreature(tagCreature creature)
{
	tagCreature tmp = creature;
	tmp.arrNum = _vCreature.size();

	tagBattleCreature tmp0;
	
	
	_vCreature.push_back(tmp);
}

void battle::setObstacle(void)
{
	if (_battleNum == 0 && _obstacle == 0)
	{
		for (int i = 4; i < 12; i++)
		{
			_battleArr[i][5].closed = true;

		}
		_battleArr[11][4].closed = true;
		_battleArr[2][6].closed = true;
		_battleArr[3][6].closed = true;
		_battleArr[2][7].closed = true;		
	}
	else if (_battleNum == 0 && _obstacle == 1)
	{
		for (int i = 5; i < 10; i++)
		{
			_battleArr[i][6].closed = true;

		}
		for (int i = 6; i < 10; i++)
		{
			_battleArr[i][7].closed = true;
		}
		_battleArr[5][2].closed = true;
		_battleArr[6][2].closed = true;
	}

}

void battle::inputBattle(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_HOME))
	{
		if (!_attribute) _attribute = true;
		else _attribute = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		////====================== T E S T ==============================
		//if (getMouseArr().x >= 0 && getMouseArr().x < MAXGRIDX &&
		//	getMouseArr().y >= 0 && getMouseArr().y < MAXGRIDY)
		//{
		//	_vPath = getPath(7, 5, getMouseArr().x, getMouseArr().y);
		//	printf("");
		//}

		//=============================================================

		if (_button == BAB_NULL)
		{
			if (PtInRect(&RectMake(3, 559, 50, 38), _ptMouse))
			{
				IMAGEMANAGER->findImage("battle_config")->setFrameX(1);
			}
			if (PtInRect(&RectMake(105, 559, 50, 38), _ptMouse))
			{
				IMAGEMANAGER->findImage("battle_run")->setFrameX(1);
			}
			if (PtInRect(&RectMake(645, 559, 50, 38), _ptMouse))
			{
				IMAGEMANAGER->findImage("battle_spell")->setFrameX(1);
			}
			if (PtInRect(&RectMake(696, 559, 50, 38), _ptMouse))
			{
				IMAGEMANAGER->findImage("battle_wait")->setFrameX(1);
			}
			if (PtInRect(&RectMake(747, 559, 50, 38), _ptMouse))
			{
				IMAGEMANAGER->findImage("battle_def")->setFrameX(1);
			}

		}
		else
		{
			switch (_button)
			{
			case BAB_NULL:
				break;
			case BAB_CONFIG:
			{
				if (PtInRect(&RectMake(184, 110, 30, 22), _ptMouse))
				{
					if (!_showGrid) _showGrid = true;
					else _showGrid = false;
				}
				
				if (_buttonConfig == BAC_NULL)
				{
					if (IMAGEMANAGER->findImage("battle_load")->getFrameX() == 0 &&
						PtInRect(&RectMake(183, 472, 100, 48), _ptMouse))
					{
						IMAGEMANAGER->findImage("battle_load")->setFrameX(1);
					}
					if (IMAGEMANAGER->findImage("battle_re")->getFrameX() == 0 &&
						PtInRect(&RectMake(297, 472, 100, 48), _ptMouse))
					{
						IMAGEMANAGER->findImage("battle_re")->setFrameX(1);
					}
					if (IMAGEMANAGER->findImage("battle_main")->getFrameX() == 0 &&
						PtInRect(&RectMake(405, 472, 100, 48), _ptMouse))
					{
						IMAGEMANAGER->findImage("battle_main")->setFrameX(1);
					}
					if (IMAGEMANAGER->findImage("battle_return")->getFrameX() == 0 &&
						PtInRect(&RectMake(516, 472, 100, 48), _ptMouse))
					{
						IMAGEMANAGER->findImage("battle_return")->setFrameX(1);
					}
					if (IMAGEMANAGER->findImage("battle_default")->getFrameX() == 0 &&
						PtInRect(&RectMake(516, 413, 100, 48), _ptMouse))
					{
						IMAGEMANAGER->findImage("battle_default")->setFrameX(1);
					}


				}

			}
			break;
			case BAB_RUN:
				break;
			case BAB_SPELL:
				break;
			case BAB_WAIT:
				break;
			case BAB_DEF:
				break;
			}
		}


	}

	if(KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (IMAGEMANAGER->findImage("battle_config")->getFrameX() == 1 &&
			PtInRect(&RectMake(3, 559, 50, 38), _ptMouse))
		{
			_button = BAB_CONFIG;
		}

		if (IMAGEMANAGER->findImage("battle_run")->getFrameX() == 1 &&
			PtInRect(&RectMake(105, 559, 50, 38), _ptMouse))
		{
			_button = BAB_RUN;

		}
		if (IMAGEMANAGER->findImage("battle_spell")->getFrameX() == 1 &&
			PtInRect(&RectMake(645, 559, 50, 38), _ptMouse))
		{
			_button = BAB_SPELL;

		}
		if (IMAGEMANAGER->findImage("battle_wait")->getFrameX() == 1 &&
			PtInRect(&RectMake(696, 559, 50, 38), _ptMouse))
		{
			_button = BAB_WAIT;

		}
		if (IMAGEMANAGER->findImage("battle_def")->getFrameX() == 1 &&
			PtInRect(&RectMake(747, 559, 50, 38), _ptMouse))
		{
			_button = BAB_DEF;

		}

		if (_button == BAB_CONFIG)
		{
			if (IMAGEMANAGER->findImage("battle_load")->getFrameX() == 1 &&
				PtInRect(&RectMake(183, 472, 100, 48), _ptMouse))
			{
			}
			if (IMAGEMANAGER->findImage("battle_re")->getFrameX() == 1 &&
				PtInRect(&RectMake(297, 472, 100, 48), _ptMouse))
			{
			}
			if (IMAGEMANAGER->findImage("battle_main")->getFrameX() == 1 &&
				PtInRect(&RectMake(405, 472, 100, 48), _ptMouse))
			{
				_changeScene = true;
			}
			if (IMAGEMANAGER->findImage("battle_return")->getFrameX() == 1 &&
				PtInRect(&RectMake(516, 472, 100, 48), _ptMouse))
			{
				_button = BAB_NULL;
			}
			if (IMAGEMANAGER->findImage("battle_default")->getFrameX() == 1 &&
				PtInRect(&RectMake(516, 413, 100, 48), _ptMouse))
			{
			}

		}
		////============= config button =======================
		IMAGEMANAGER->findImage("battle_load")->setFrameX(0);
		IMAGEMANAGER->findImage("battle_re")->setFrameX(0);
		IMAGEMANAGER->findImage("battle_main")->setFrameX(0);
		IMAGEMANAGER->findImage("battle_return")->setFrameX(0);
		IMAGEMANAGER->findImage("battle_default")->setFrameX(0);
		////===================================================
		//============= main button =========================
		IMAGEMANAGER->findImage("battle_config")->setFrameX(0);
		IMAGEMANAGER->findImage("battle_run")->setFrameX(0);
		IMAGEMANAGER->findImage("battle_spell")->setFrameX(0);
		IMAGEMANAGER->findImage("battle_wait")->setFrameX(0);
		IMAGEMANAGER->findImage("battle_def")->setFrameX(0);
		//===================================================
	}


}

void battle::activeButton(void)
{
	switch (_button)
	{
	case BAB_NULL: 
		break;
	case BAB_CONFIG:
		break;
	case BAB_RUN: _button = BAB_NULL;
		break;
	case BAB_SPELL: _button = BAB_NULL;
		break;
	case BAB_WAIT: _button = BAB_NULL;
		break;
	case BAB_DEF: _button = BAB_NULL;
		break;
	case BAB_END:
		break;
	}
}