#include "stdafx.h"
#include "battle.h"
#include "player.h"

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
	_move = false;
	_cursorInGrid = false;
	_attack = false;
	_turn = false;
	_youWin = false;
	_youLose = false;

	_button = BAB_NULL;
	_buttonConfig = BAC_NULL;
	_cursor = CUR_IDLE;
	_angle = 0;



	for (int i = 0; i < MAXGRIDX; i++)
	{
		for (int j = 0; j < MAXGRIDY; j++)
		{
			ZeroMemory(&_battleArr[i][j], sizeof(tagGridInfo));

			_battleArr[i][j].arrX = i;
			_battleArr[i][j].arrY = j;
			_battleArr[i][j].ground = 127 + 42 * j;
			_battleArr[i][j].destY = 87 + 42 * j;
			_battleArr[i][j].range = false;
			_battleArr[i][j].attack = false;
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
		_obstacle = RND->getInt(2);

		_obstacle = 0;
	break;
	case 1:
		
	break;
	}


	setObstacle();
	sort(_vCreature.begin(), _vCreature.end());
	sort(_vBattle.begin(), _vBattle.end());

	if (_vBattle.size())
	{
		_vBattle[0].turn = true;
		_currentCreature = _vCreature.size();
		setArrNum();
		setTurn();


		//setTurn();

	}
	return S_OK;
}

void battle::release(void)
{

}

void battle::update(void)
{
	////============== T E S T ==================
	//_vPath = getPath(
	//	 _vBattle[_vCreature[_currentCreature].arrNum].arrX,
	//	 _vBattle[_vCreature[_currentCreature].arrNum].arrY,
	//	getMouseArr().x, getMouseArr().y,
	//	_vCreature[_currentCreature].fly);
	////==========================================

	sort(_vBattle.begin(), _vBattle.end());
	setArrNum();
	
	activeButton();
	setCondition();
	frameCycle();
	creatureMove();
	cursorChange();
	enemyAction();
	endBattle();
}

void battle::render(void)
{
	IMAGEMANAGER->findImage("mainBackgroundSecond")->render(getMemDC(),800,0);

	battleDraw();
	creatureDraw();
	buttonDraw();

	switch (_cursor)
	{
	case CUR_IDLE:
		IMAGEMANAGER->findImage("mouse_idle")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
		break;
	case CUR_MOVE:
		IMAGEMANAGER->findImage("battle_cursor_move")->frameRender(getMemDC(), _ptMouse.x - 32, _ptMouse.y - 32);

		break;
	case CUR_ATKMELEE:
		IMAGEMANAGER->findImage("battle_cursor_melee")->frameRender(getMemDC(), _ptMouse.x - 32, _ptMouse.y - 32);

		break;
	case CUR_ATKRANGE:
		IMAGEMANAGER->findImage("battle_cursor_range")->frameRender(getMemDC(), _ptMouse.x - 32, _ptMouse.y - 32);

		break;

	}
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

	//if (!_turn)
	//{
		for (int j = 0; j < MAXGRIDX; j++)
		{
			for (int k = 0; k < MAXGRIDY; k++)
			{

				if (_battleArr[j][k].range)
					IMAGEMANAGER->findImage("grid")->alphaRender(getMemDC(),
						_battleArr[j][k].destX,
						_battleArr[j][k].destY, 150);
				if (!_battleArr[j][k].range && _battleArr[j][k].attack)
					IMAGEMANAGER->findImage("grid_purple")->alphaRender(getMemDC(),
						_battleArr[j][k].destX,
						_battleArr[j][k].destY, 50);

			}
		}
	//}

	for (int i = 0; i < _vCreature.size(); i++)
	{
		IMAGEMANAGER->findImage("grid")->alphaRender(getMemDC(),
			_battleArr[_vBattle[_vCreature[i].arrNum].arrX][_vBattle[_vCreature[i].arrNum].arrY].destX,
			_battleArr[_vBattle[_vCreature[i].arrNum].arrX][_vBattle[_vCreature[i].arrNum].arrY].destY, 150);
		if (_vCreature[i].size == 2)
			IMAGEMANAGER->findImage("grid")->alphaRender(getMemDC(),
				_battleArr[_vBattle[_vCreature[i].arrNum].arrX - 1][_vBattle[_vCreature[i].arrNum].arrY].destX,
				_battleArr[_vBattle[_vCreature[i].arrNum].arrX - 1][_vBattle[_vCreature[i].arrNum].arrY].destY, 150);

	}



	
	if (_attribute)
	{
		HFONT font = CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("돋움체"));
		HFONT oldfont = (HFONT)SelectObject(getMemDC(), font);
		SelectObject(getMemDC(), font);
		
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		for (int i = 0; i < MAXGRIDX; i++)
		{
			for (int j = 0; j < MAXGRIDY; j++)
			{
				char tmp[256];
				sprintf_s(tmp, "(%d,%d)", i, j);	
		
				TextOut(getMemDC(), _battleArr[i][j].center - strlen(tmp)*3 , _battleArr[i][j].ground - 24, tmp, strlen(tmp));
			}
		}

		SelectObject(getMemDC(), oldfont);
		DeleteObject(font);
		SetTextColor(getMemDC(), RGB(0, 0, 0));

	}


	if (_attribute)
	{
		for (int i = 0; i < MAXGRIDX; i++)
		{
			for (int j = 0; j < MAXGRIDY; j++)
			{
				
				if(_battleArr[i][j].closed || _battleArr[i][j].unit)
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

void battle::creatureDraw(void)
{

	for (int i = 0; i < _vBattle.size(); i++)
	{
		int tmp = _vBattle[i].arrNum;

		//if (_vBattle[i].turn && !_move)
		//{
		//	for (int j = 0; j < MAXGRIDX; j++)
		//	{
		//		for (int k = 0; k < MAXGRIDY; k++)
		//		{
		//	
		//			if (_battleArr[j][k].range)
		//				IMAGEMANAGER->findImage("grid")->alphaRender(getMemDC(),
		//					_battleArr[j][k].destX,
		//					_battleArr[j][k].destY, 150);
		//			if (!_battleArr[j][k].range && _battleArr[j][k].attack)
		//				IMAGEMANAGER->findImage("grid_red")->alphaRender(getMemDC(),
		//					_battleArr[j][k].destX,
		//					_battleArr[j][k].destY, 100);
		//	
		//		}
		//	}
		//}





		//	IMAGEMANAGER->findImage("grid")->alphaRender(getMemDC(),
		//		_battleArr[_vBattle[i].arrX][_vBattle[i].arrY].destX,
		//		_battleArr[_vBattle[i].arrX][_vBattle[i].arrY].destY, 150);
		//	if (_vCreature[i].size == 2)
		//		IMAGEMANAGER->findImage("grid")->alphaRender(getMemDC(),
		//			_battleArr[_vBattle[i].arrX-1][_vBattle[i].arrY].destX,
		//			_battleArr[_vBattle[i].arrX-1][_vBattle[i].arrY].destY, 150);

		

		if(_vCreature[tmp].size == 1)
		{
			if (_vBattle[i].isRight)
			{
				_vCreature[tmp].img[_vCreature[tmp].state]->frameRender(getMemDC(),
					_vBattle[i].x - _vCreature[tmp].startX, _vBattle[i].y - _vCreature[tmp].startY,
					 _vBattle[i].sourX,  _vBattle[i].sourY);

				_vCreature[tmp].imgShadow[_vCreature[tmp].state]->alphaFrameRender(getMemDC(),
					_vBattle[i].x - _vCreature[tmp].startX, _vBattle[i].y - _vCreature[tmp].startY,
					 _vBattle[i].sourX,  _vBattle[i].sourY,150);

			}
			else if (!_vBattle[i].isRight)
			{
				_vCreature[tmp].img[_vCreature[tmp].state]->frameRender(getMemDC(),
					_vBattle[i].x - (_vCreature[tmp].img[_vCreature[tmp].state]->getFrameWidth() - _vCreature[tmp].startX),
					_vBattle[i].y - _vCreature[tmp].startY,
					_vBattle[i].sourX, _vBattle[i].sourY);

				_vCreature[tmp].imgShadow[_vCreature[tmp].state]->alphaFrameRender(getMemDC(),
					_vBattle[i].x - (_vCreature[tmp].img[_vCreature[tmp].state]->getFrameWidth() - _vCreature[tmp].startX),
					_vBattle[i].y - _vCreature[tmp].startY,
					_vBattle[i].sourX, _vBattle[i].sourY, 150);


			}

		}
		else if (_vCreature[tmp].size == 2)
		{
			if (_vBattle[i].isRight)
			{
				_vCreature[tmp].img[_vCreature[tmp].state]->frameRender(getMemDC(),
					_vBattle[i].x - 21 - _vCreature[tmp].startX, _vBattle[i].y - _vCreature[tmp].startY,
					_vBattle[i].sourX, _vBattle[i].sourY);

				_vCreature[tmp].imgShadow[_vCreature[tmp].state]->alphaFrameRender(getMemDC(),
					_vBattle[i].x - 21 - _vCreature[tmp].startX, _vBattle[i].y - _vCreature[tmp].startY,
					_vBattle[i].sourX, _vBattle[i].sourY, 150);


			}
			else if (!_vBattle[i].isRight)
			{
				_vCreature[tmp].img[_vCreature[tmp].state]->frameRender(getMemDC(),
					_vBattle[i].x - 21 -(_vCreature[tmp].img[_vCreature[tmp].state]->getFrameWidth() - _vCreature[tmp].startX),
					_vBattle[i].y - _vCreature[tmp].startY,
					_vBattle[i].sourX, _vBattle[i].sourY);

				_vCreature[tmp].imgShadow[_vCreature[tmp].state]->alphaFrameRender(getMemDC(),
					_vBattle[i].x - 21 -(_vCreature[tmp].img[_vCreature[tmp].state]->getFrameWidth() - _vCreature[tmp].startX),
					_vBattle[i].y - _vCreature[tmp].startY,
					_vBattle[i].sourX, _vBattle[i].sourY, 150);


			}
		}

		
		

		if (!_vCreature[tmp].isDead)
		{
			IMAGEMANAGER->findImage("battle_quantity")->render(getMemDC(), _vBattle[i].x + 11, _vBattle[i].y);
			numberDraw(getMemDC(), _vCreature[tmp].quantity, _vBattle[i].x + 26 - su(_vCreature[tmp].quantity)/2*7, _vBattle[i].y + 1 );

		}


		//_vCreature[tmp].img[_vCreature[tmp].state]->frameRender(getMemDC(),
		//	0,0);

	}
	



}

void battle::enemyAction(void)
{
	if (!_vBattle[_vCreature[_currentCreature].arrNum].player && !_turn)
	{
		//setTurn();
		//_turn = false;
		int shortest = 50;												// 언놈이 제일 가까이 있나
		int current = _vCreature[_currentCreature].arrNum;				// 현재 크리쳐 
		int target = -1;												// 때리러 갈놈 지정
		int destX;														// 이동 목표지점 X
		int destY;														// 이동 목표지점 Y

		//=========== 먼저 공격 범위에 누가 있는지? 누가 젤 가까운지
		for (int i = 0; i < _vBattle.size(); i++)
		{
			//setArrNum();

			if (_vBattle[i].player && _battleArr[_vBattle[i].arrX][_vBattle[i].arrY].attack && !_vCreature[_vBattle[i].arrNum].isDead)
			{
				if (shortest > getPath(_vBattle[current].arrX, _vBattle[current].arrY, 
					_vBattle[i].arrX, _vBattle[i].arrY,_vCreature[_currentCreature].fly).size())
				{
					shortest = getPath(_vBattle[current].arrX, _vBattle[current].arrY,
						_vBattle[i].arrX, _vBattle[i].arrY, _vCreature[_currentCreature].fly).size();

					target = _vBattle[i].arrNum;

					_vBattle[current].attackTarget = _vBattle[i].target;
				}
			}
		}

		//=============== 공격 범위에 누군가가 있다면?
		if (target != -1)
		{
			//=============== 바로 옆에 붙어 있다?  바로 고놈을 때려라==================
			if (getValueH(_vBattle[current].arrX, _vBattle[current].arrY, _vBattle[_vCreature[target].arrNum].arrX, _vBattle[_vCreature[target].arrNum].arrY) == 1)
			{
				_attack = true;
				_turn = true;
				attackSomeone(_currentCreature, target);

			}
			//=================== 좀 떨어져 있다면 이동후 때려야 할텐데..
			else
			{
				int shortestMove = 30;
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (!_battleArr[_vBattle[_vCreature[target].arrNum].arrX +i][_vBattle[_vCreature[target].arrNum].arrY + j].range) continue;

						if (i == 0 && j == 0) continue;

						if (_vBattle[target].arrY % 2 == 0)
						{
							if (i == -1 && j == -1) continue;
							if (i == -1 && j == 1) continue;
						}
						else
						{
							if (i == 1 && j == -1) continue;
							if (i == 1 && j == 1) continue;
						}

						if (shortestMove > getValueH(_vBattle[current].arrX, _vBattle[current].arrY,
							_vBattle[_vCreature[target].arrNum].arrX + i, _vBattle[_vCreature[target].arrNum].arrY + j))
						{
							shortestMove = getValueH(_vBattle[current].arrX, _vBattle[current].arrY,
								_vBattle[_vCreature[target].arrNum].arrX +i , _vBattle[_vCreature[target].arrNum].arrY + j);
							destX = _vBattle[_vCreature[target].arrNum].arrX + i;
							destY = _vBattle[_vCreature[target].arrNum].arrY + j;
						}
					}
				}

				_battleArr[_vBattle[current].arrX][_vBattle[current].arrY].unit = false;
				if(_vCreature[_currentCreature].size ==2) _battleArr[_vBattle[current].arrX-1][_vBattle[current].arrY].unit = false;

				_vPath = getPath(_vBattle[current].arrX, _vBattle[current].arrY, destX, destY, _vCreature[_currentCreature].fly);
				
				_attack = true;

				if (_vCreature[_currentCreature].size == 2)
				{
					
					if (!_battleArr[_vPath[_vPath.size() - 1].x - 1][_vPath[_vPath.size() - 1].y].range)
						_vPath[_vPath.size() - 1].x += 1;
				}



				while (_vPath.size())
				{
					if (!_battleArr[_vPath[_vPath.size() - 1].x][_vPath[_vPath.size() - 1].y].unit) break;
				
					_vPath.erase(_vPath.begin() + _vPath.size() - 1);
					_attack = false;
				
				}

				_move = true;
				_turn = true;
				_vCreature[_currentCreature].state = STATE_MOVE;

			}
		}
		
		//======================= 이동할 자리를 찾아보자 =================
		//======================= 먼저 누가 제일 가깝냐 ? ================
		//=============== target이 -1 인거는 공격범위에 아무도 없다는뜻 =====
		else if (target == -1)
		{
			int revise = 0;
			
			for (int i = 0; i < _vBattle.size(); i++)
			{
				if (_vBattle[i].player && !_vCreature[_vBattle[i].arrNum].isDead)
				{
					if (shortest > getPath(_vBattle[current].arrX, _vBattle[current].arrY,
						_vBattle[i].arrX, _vBattle[i].arrY, _vCreature[_currentCreature].fly).size())
					{
						shortest = getPath(_vBattle[current].arrX, _vBattle[current].arrY,
							_vBattle[i].arrX, _vBattle[i].arrY, _vCreature[_currentCreature].fly).size();
						target = _vBattle[i].arrNum;

					}
				}
			}

			if (target == -1) return;

			_vPath = getPath(_vBattle[current].arrX, _vBattle[current].arrY,
				_vBattle[_vCreature[target].arrNum].arrX, _vBattle[_vCreature[target].arrNum].arrY,
				_vCreature[_currentCreature].fly);

			int tmp = _vPath.size();

			for (int i = 0; i < tmp - _vCreature[_currentCreature].speed; i++)
			{
				_vPath.erase(_vPath.begin() + (_vPath.size() -1));
			}
			


			_battleArr[_vBattle[current].arrX][_vBattle[current].arrY].unit = false;
			if (_vCreature[_currentCreature].size == 2)
			{
				_battleArr[_vBattle[current].arrX - 1][_vBattle[current].arrY].unit = false;
				if (!_battleArr[_vPath[_vPath.size() - 1].x - 1][_vPath[_vPath.size() - 1].y].range)
					_vPath[_vPath.size() - 1].x += 1;
			}
			_vCreature[_currentCreature].state = STATE_MOVE;
			_move = true;
			_turn = true;

		}

	}
}

bool battle::canGo(int destX, int destY, int x, int size)
{
	switch (x)
	{
	case 0:

		if (size == 1)
		{
			if (destX + 1 >= MAXGRIDX) return false;
			if (destX + 1 < MAXGRIDX && _battleArr[destX + 1][destY].range) return true;
			else return false;

		}
		else
		{
			if (destX + 2 >= MAXGRIDX) return false;
			if (destX + 2 < MAXGRIDX && _battleArr[destX + 1][destY].range &&
				MAXGRIDX && _battleArr[destX + 2][destY].range) return true;
			else return false;

		}

	break;
	case 1:

		if (size == 1)
		{
			if (destY % 2 == 0)
			{
				if (destX + 1 >= MAXGRIDX || destY + 1 >= MAXGRIDY) return false;
				else
				{
					if (_battleArr[destX + 1][destY + 1].range) return true;
					else return false;
				}
			}
			else
			{
				if (destY + 1 >= MAXGRIDY) return false;
				else
				{
					if (_battleArr[destX][destY + 1].range) return true;
					else return false;
				}
			}


		}
		else
		{
			if (destY % 2 == 0)
			{
				if (destX + 1 >= MAXGRIDX || destY + 1 >= MAXGRIDY) return false;
				else
				{
					if (_battleArr[destX + 1][destY + 1].range &&
						(_battleArr[destX][destY +1].range || _battleArr[destX +2][destY +1].range)) return true;
					else return false;
				}
			}
			else
			{
				if (destY + 1 >= MAXGRIDY) return false;
				else
				{
					if (_battleArr[destX][destY + 1].range) return true;
					else return false;
				}
			}

		}


	break;
	case 2:

	break;
	case 3:

	break;
	case 4:

	break;
	case 5:

	break;
	}

	if (destY % 2 == 0)
	{
		if (size == 1)
		{

		}
		else
		{

		}
	}
	else
	{
		if (size == 1)
		{

		}
		else
		{

		}

	}
}

void battle::cursorChange(void)
{
	if (PtInRect(&RectMake(59, 87, 682, 470), _ptMouse) && _button == BAB_NULL)
	{
		_cursorInGrid = true;
		
	}
	else
	{
		_cursor = CUR_IDLE; 
		_cursorInGrid = false;
	}

	frameRotation(IMAGEMANAGER->findImage("battle_cursor_melee"), 6, _angle, true, true);

	if (_vBattle[_vCreature[_currentCreature].arrNum].player && _cursorInGrid)
	{
		if (!_vBattle[_vCreature[_currentCreature].arrNum].player	||
			!_battleArr[getMouseArr().x][getMouseArr().y].range)
		{
			_cursor = CUR_IDLE;
		}

		if (_battleArr[getMouseArr().x][getMouseArr().y].range)
		{
			_cursor = CUR_MOVE;
			if (_vCreature[_currentCreature].fly) IMAGEMANAGER->findImage("battle_cursor_move")->setFrameX(1);
			else IMAGEMANAGER->findImage("battle_cursor_move")->setFrameX(0);
		}

		for (int i = 0; i < _vBattle.size(); i++)
		{
			if (getMouseArr().x == _vBattle[i].arrX &&
				getMouseArr().y == _vBattle[i].arrY &&
				_battleArr[_vBattle[i].arrX][_vBattle[i].arrY].attack &&
				!_vBattle[i].player  && !_vCreature[_vBattle[i].arrNum].isDead)
			{
				_cursor = CUR_ATKMELEE;
				_angle = getAngle(_ptMouse.x - _vBattle[i].x  , _ptMouse.y - (_vBattle[i].y - 15));

				if (_angle >= 0 && _angle < PI / 3 - PI/6)
				{
					if (_vBattle[i].arrX + 1 == MAXGRIDX) _cursor = CUR_IDLE;
					if (_vBattle[i].arrX + 1 < MAXGRIDX &&
						!_battleArr[_vBattle[i].arrX + 1][_vBattle[i].arrY].range) _cursor = CUR_IDLE;
				}
				else if (_angle <= 2 * PI / 3 - PI / 6)
				{
					if (_vBattle[i].arrY % 2 == 0)
					{
						if (_vBattle[i].arrX + 1 == MAXGRIDX || _vBattle[i].arrY + 1 == MAXGRIDY) _cursor = CUR_IDLE;
						else
						{
							if (!_battleArr[_vBattle[i].arrX + 1][_vBattle[i].arrY + 1].range) _cursor = CUR_IDLE;
						}
					}
					else
					{
						if (_vBattle[i].arrY + 1 == MAXGRIDY) _cursor = CUR_IDLE;
						else
						{
							if (!_battleArr[_vBattle[i].arrX][_vBattle[i].arrY + 1].range) _cursor = CUR_IDLE;
						}

					}
				}
				else if (_angle <= 3 * PI / 3 - PI / 6)
				{
					if (_vBattle[i].arrY % 2 == 0)
					{
						if (_vBattle[i].arrY + 1 == MAXGRIDY) _cursor = CUR_IDLE;
						else
						{
							if (!_battleArr[_vBattle[i].arrX][_vBattle[i].arrY + 1].range) _cursor = CUR_IDLE;
						}
					}
					else
					{
						if (_vBattle[i].arrX - 1 < 0 || _vBattle[i].arrY + 1 == MAXGRIDY) _cursor = CUR_IDLE;
						else
						{
							if (!_battleArr[_vBattle[i].arrX -1][_vBattle[i].arrY + 1].range) _cursor = CUR_IDLE;
						}

					}

				}
				else if (_angle <= 4 * PI / 3 - PI / 6)
				{
					if (_vBattle[i].arrX - 1 < 0) _cursor = CUR_IDLE;
					if (_vBattle[i].arrX - 1 >= 0&&
						!_battleArr[_vBattle[i].arrX - 1][_vBattle[i].arrY].range) _cursor = CUR_IDLE;

				}
				else if (_angle <= 5 * PI / 3 - PI / 6)
				{
					if (_vBattle[i].arrY % 2 == 0)
					{
						if (_vBattle[i].arrY - 1 < 0) _cursor = CUR_IDLE;
						else
						{
							if (!_battleArr[_vBattle[i].arrX][_vBattle[i].arrY - 1].range) _cursor = CUR_IDLE;
						}
					}
					else
					{
						if (_vBattle[i].arrX - 1 < 0 || _vBattle[i].arrY - 1 < 0) _cursor = CUR_IDLE;
						else
						{
							if (!_battleArr[_vBattle[i].arrX - 1][_vBattle[i].arrY - 1].range) _cursor = CUR_IDLE;
						}

					}

				}
				else if (_angle <= 6 * PI / 3 - PI / 6)
				{
					if (_vBattle[i].arrY % 2 == 0)
					{
						if (_vBattle[i].arrX + 1 == MAXGRIDX || _vBattle[i].arrY - 1 < 0) _cursor = CUR_IDLE;
						else
						{
							if (!_battleArr[_vBattle[i].arrX + 1][_vBattle[i].arrY - 1].range) _cursor = CUR_IDLE;
						}
					}
					else
					{
						if (_vBattle[i].arrY - 1 < 0) _cursor = CUR_IDLE;
						else
						{
							if (!_battleArr[_vBattle[i].arrX][_vBattle[i].arrY - 1].range) _cursor = CUR_IDLE;
						}

					}

				}
				else
				{
					if (_vBattle[i].arrX + 1 == MAXGRIDX) _cursor = CUR_IDLE;
					if (_vBattle[i].arrX + 1 < MAXGRIDX &&
						!_battleArr[_vBattle[i].arrX + 1][_vBattle[i].arrY].range) _cursor = CUR_IDLE;
				}

				break;
			}
		}
	}
}

void battle::endBattle(void)
{
	int isAliveEnemy = 0;
	int isAlivePlayer = 0;



	for (int i = 0; i < _vCreature.size(); i++)
	{

		if (!_vCreature[i].isDead && !_vBattle[_vCreature[i].arrNum].player) isAliveEnemy++;
		if (!_vCreature[i].isDead && _vBattle[_vCreature[i].arrNum].player) isAlivePlayer++;

		if (isAliveEnemy == 0 && i == _vCreature.size() - 1)
		{
			//_vCreature.clear();
			//_vBattle.clear();
			_youWin = true;

		}
		else if (isAlivePlayer == 0 && i == _vCreature.size() - 1)
		{
			//_vCreature.clear();
			//_vBattle.clear();
			_youLose = true;
		}
	}

	if (_youLose || _youWin)
	{
		for (int i = 0; i < _vCreature.size();)
		{
			if (!_vBattle[_vCreature[i].arrNum].player || _vCreature[i].isDead)
			{
				_vCreature.erase(_vCreature.begin() + i);
				continue;
			}
			else i++;
		}
		for (int i = 0; i < _vCreature.size(); i++)
		{
			_vCreature[i].currentHp = _vCreature[i].hp;
			for (int j = 0; j < STATE_END; j++)
			{
				if(j != 6)
				_vCreature[i].img[j]->setFrameY(0);
			}
		}

		_player->getHero()[_player->getHeroNum()]->setCreature(_vCreature);
		_vCreature.clear();
		_vBattle.clear();

	}


	



}

void battle::creatureMove(void)
{

	if (_move && _vPath.size())
	{
		// _vBattle[_vCreature[_currentCreature].arrNum].angle =
		//	atan2f(_battleArr[_vPath[0].x][_vPath[0].y].ground -  _vBattle[_vCreature[_currentCreature].arrNum].y,
		//		_battleArr[_vPath[0].x][_vPath[0].y].center -  _vBattle[_vCreature[_currentCreature].arrNum].x);

		 _vBattle[_vCreature[_currentCreature].arrNum].angle =
			getAngle(_battleArr[_vPath[0].x][_vPath[0].y].center -  _vBattle[_vCreature[_currentCreature].arrNum].x,
				_battleArr[_vPath[0].x][_vPath[0].y].ground -  _vBattle[_vCreature[_currentCreature].arrNum].y);


		if ( _vBattle[_vCreature[_currentCreature].arrNum].angle >= PI/2 &&  _vBattle[_vCreature[_currentCreature].arrNum].angle < PI / 2 * 3)
		{
			 _vBattle[_vCreature[_currentCreature].arrNum].isRight = false;
		}
		else  _vBattle[_vCreature[_currentCreature].arrNum].isRight = true;

		if (PtInRect(&RectMake(
			_battleArr[_vPath[0].x][_vPath[0].y].center - 8,
			_battleArr[_vPath[0].x][_vPath[0].y].ground - 8, 16, 16),
			PointMake( _vBattle[_vCreature[_currentCreature].arrNum].x,  _vBattle[_vCreature[_currentCreature].arrNum].y)))
		{
			//============== 원하는 곳에 도착함 =================
			 _vBattle[_vCreature[_currentCreature].arrNum].x = _battleArr[_vPath[0].x][_vPath[0].y].center;
			 _vBattle[_vCreature[_currentCreature].arrNum].y = _battleArr[_vPath[0].x][_vPath[0].y].ground;

			 _vBattle[_vCreature[_currentCreature].arrNum].arrX = getArr(PointMake( _vBattle[_vCreature[_currentCreature].arrNum].x,  _vBattle[_vCreature[_currentCreature].arrNum].y)).x;
			 _vBattle[_vCreature[_currentCreature].arrNum].arrY = getArr(PointMake( _vBattle[_vCreature[_currentCreature].arrNum].x,  _vBattle[_vCreature[_currentCreature].arrNum].y)).y;


			_vPath.erase(_vPath.begin());

			if (!_vPath.size())
			{
				//_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX][_vBattle[_vCreature[_currentCreature].arrNum].arrY].closed = true;
				//
				//if (_vCreature[_currentCreature].size == 2)
				//{
				//	_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX -1][_vBattle[_vCreature[_currentCreature].arrNum].arrY].closed = true;
				//
				//}


				_move = false;
				//_vCreature[_currentCreature].state = STATE_IDLE;
				// _vBattle[_vCreature[_currentCreature].arrNum].sourX = 0;
				//_vBattle[_vCreature[_currentCreature].arrNum].isRight = true;

				 if (!_attack)
				 {
					 if(_vBattle[_vCreature[_currentCreature].arrNum].player)
					 _vBattle[_vCreature[_currentCreature].arrNum].isRight = true;

					 else _vBattle[_vCreature[_currentCreature].arrNum].isRight = false;

					 //_turn = false;
					 //setTurn();
				 }
				 else
				 {
					//setArrNum();
					//int target;
					//for (int i = 0; i < _vBattle.size(); i++)
					//{
					//	if (_vBattle[_vCreature[_currentCreature].arrNum].attackTarget == _vBattle[i].target)
					//	{
					//		target = _vBattle[i].arrNum;
					//		break;
					//	}
					//}
					//attackSomeone(_currentCreature, target);
				 }

			}

		}
		else
		{
			 _vBattle[_vCreature[_currentCreature].arrNum].x += _vCreature[_currentCreature].speed/3 * cosf( _vBattle[_vCreature[_currentCreature].arrNum].angle);
			 _vBattle[_vCreature[_currentCreature].arrNum].y += _vCreature[_currentCreature].speed/3 * sinf( _vBattle[_vCreature[_currentCreature].arrNum].angle);


		}

	}
	/*
	if (_attack && !_move && _vCreature[_currentCreature].state == STATE_IDLE)
	{
		setArrNum();
		int current = _vCreature[_currentCreature].arrNum;
		int target;
		for (int i = 0; i < _vBattle.size(); i++)
		{
			if (_vBattle[i].target == _vBattle[current].attackTarget)
			{
				target = i;
			}
		}

		if (_vBattle[current].arrY % 2 == 0)
		{
			if (_vBattle[current].arrX < _vBattle[target].arrX)
			{
				_vBattle[current].isRight = true;
				_vBattle[target].isRight = false;
			}
			else
			{
				_vBattle[current].isRight = false;
				_vBattle[target].isRight = true;
			}

		}
		else
		{
			if (_vBattle[current].arrX > _vBattle[target].arrX)
			{
				_vBattle[current].isRight = false;
				_vBattle[target].isRight = true;
			}
			else
			{
				_vBattle[current].isRight = true;
				_vBattle[target].isRight = false;
			}
		}

		if (_vBattle[current].arrY == _vBattle[target].arrY)
		{
			_vCreature[_currentCreature].state = STATE_FRONT;
		}
		else if (_vBattle[current].arrY > _vBattle[target].arrY)
		{
			_vCreature[_currentCreature].state = STATE_UP;
		}
		else if (_vBattle[current].arrY < _vBattle[target].arrY)
		{
			_vCreature[_currentCreature].state = STATE_DOWN;
		}
		_vBattle[current].sourX = 0;
	}
	*/
}

void battle::setArrNum(void)
{

	//============= arr 번호 조건 재 설정
	for (int i = 0; i < _vCreature.size(); i++)
	{

		for (int j = 0; j < _vBattle.size(); j++)
		{
			if (_vCreature[i].target == _vBattle[j].target)
			{
				_vCreature[i].arrNum = j;
				_vBattle[j].arrNum = i;
				break;

			}
		}
	}
}

void battle::setCondition(void)
{
	for (int i = 0; i < _vBattle.size(); i++)
	{
		_vBattle[i].arrX = getArr(PointMake(_vBattle[i].x, _vBattle[i].y)).x;
		_vBattle[i].arrY = getArr(PointMake(_vBattle[i].x, _vBattle[i].y)).y;

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

POINT battle::getArr(POINT xy)
{
	POINT point;
	point.x = -1;
	point.y = -1;
	for (int i = 0; i < MAXGRIDX; i++)
	{
		for (int j = 0; j < MAXGRIDY; j++)
		{
			if (PtInRect(&RectMake(_battleArr[i][j].destX, _battleArr[i][j].destY, 43, 50), xy))
			{
				point.x = i;
				point.y = j;

				if (xy.y < _battleArr[i][j].destY + 10)
				{
					if (xy.x < _battleArr[i][j].destX + 19)
					{
						if (_battleArr[i][j].destY + 10 - xy.y >
							10.0f / 19.0f*(xy.x - _battleArr[i][j].destX))
						{
							if (j % 2 == 1) point.x--;
							point.y--;
						}
					}
					else if (xy.x >= _battleArr[i][j].destX + 24)
					{
						if (_battleArr[i][j].destY + 10 - xy.y >
							10.0f / 19.0f*(_battleArr[i][j].destX + 43 - xy.x))
						{
							if (j % 2 == 0) point.x++;
							point.y--;
						}
					}
				}
				else if (xy.y >= _battleArr[i][j].destY + 40)
				{
					if (xy.x < _battleArr[i][j].destX + 19)
					{
						if (10 - (_battleArr[i][j].destY + 50 - xy.y) >
							10.0f / 19.0f*(xy.x - _battleArr[i][j].destX))
						{
							if (j % 2 == 1) point.x--;
							point.y++;
						}
					}
					else if (xy.x >= _battleArr[i][j].destX + 24)
					{
						if (10 - (_battleArr[i][j].destY + 50 - xy.y) >
							10.0f / 19.0f*(_battleArr[i][j].destX + 43 - xy.x))
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
	tmp.target = tmp.arrNum;

	tagBattleCreature tmp0;
	ZeroMemory(&tmp0, sizeof(tagBattleCreature));
	tmp0.arrX = creature.size - 1;
	tmp0.sourX = 0;
	tmp0.sourY = 0;
	tmp0.count = 0;
	tmp0.attackTarget = 0;
	if (tmp.position == 0) tmp0.arrY = 0;
	else if (tmp.position == 1) tmp0.arrY = 2;
	else if (tmp.position == 2) tmp0.arrY = 4;
	else if (tmp.position == 3) tmp0.arrY = 5;
	else if (tmp.position == 4) tmp0.arrY = 6;
	else if (tmp.position == 5) tmp0.arrY = 8;
	else if (tmp.position == 6) tmp0.arrY = 10;

	tmp0.x = _battleArr[tmp0.arrX][tmp0.arrY].center;
	tmp0.y = _battleArr[tmp0.arrX][tmp0.arrY].ground;

	tmp0.isRight = true;
	tmp0.target = tmp.arrNum;
	tmp0.player = true;
	tmp0.arrNum = tmp.arrNum;
	tmp0.angle = 0;
	tmp0.counter = false;

	
	_vCreature.push_back(tmp);
	_vBattle.push_back(tmp0);
}

void battle::joinCreature(tagObject object)
{
	int kind = object.type -4;
	int tier = object.sub / 2;
	int level = object.sub % 2;
	int rest = object.possesion % 5;
	for (int i = 0; i < 5; i++)
	{
		tagCreature tmp;
		tmp = CommonCreature(kind, tier, level);
		tmp.arrNum = 10 + i;
		tmp.target = 10 + i;
		if (i < rest) tmp.quantity = object.possesion / 5 + 1;
		else tmp.quantity = object.possesion / 5;
		

		tagBattleCreature tmp0;
		tmp0.arrX = MAXGRIDX - 1;
		tmp0.arrY = i * 2+1;
		tmp0.sourX = 0;
		tmp0.sourY = 0;
		tmp0.count = 0;
		tmp0.x = _battleArr[tmp0.arrX][tmp0.arrY].center;
		tmp0.y = _battleArr[tmp0.arrX][tmp0.arrY].ground;
		tmp0.attackTarget = 0;

		tmp0.isRight = false;
		tmp0.target = tmp.arrNum;
		tmp0.player = false;
		tmp0.arrNum = tmp.arrNum;
		tmp0.angle = 0;
		tmp0.counter = false;

		_vCreature.push_back(tmp);
		_vBattle.push_back(tmp0);

	}


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

void battle::frameCycle(void)
{
	if( _vBattle[_vCreature[_currentCreature].arrNum].count > 0)  _vBattle[_vCreature[_currentCreature].arrNum].count--;

	for (int i = 0; i < _vBattle.size(); i++)
	{
		if (!_turn)
		{
			if (_vBattle[i].player) _vBattle[i].isRight = true;
			else _vBattle[i].isRight = false;
		}
	}


	for (int i = 0; i < _vBattle.size(); i++)
	{
		if (_vBattle[i].isRight) _vBattle[i].sourY = 0;
		else _vBattle[i].sourY = 1;
	}


	if (! _vBattle[_vCreature[_currentCreature].arrNum].count)
	{
		int current = _vCreature[_currentCreature].arrNum;
		int target;
		for (int i = 0; i < _vBattle.size(); i++)
		{
			if (_vBattle[i].target == _vBattle[current].attackTarget)
			{
				target = i;
			}
		}

		if (_move)
		{
			if (_vPath.size() > 0)
			{
				if (_vCreature[_currentCreature].img[STATE_MOVE]->getMaxFrameX() -
					_vCreature[_currentCreature].moveEnd <=  _vBattle[_vCreature[_currentCreature].arrNum].sourX)
					 _vBattle[_vCreature[_currentCreature].arrNum].sourX = -1 + _vCreature[_currentCreature].moveStart;
			}
			 _vBattle[_vCreature[_currentCreature].arrNum].sourX++;
		}

		for (int i = 0; i < _vCreature.size(); i++)
		{
			if (!_move && _vCreature[i].state == STATE_MOVE )
			{
				if (_vCreature[i].moveEnd == 0)
				{
					_vCreature[i].state = STATE_IDLE;
					_vBattle[_vCreature[i].arrNum].sourX = -1;
					sort(_vBattle.begin(), _vBattle.end());
					if (!_attack)
					{
						setTurn();
						_turn = false;
					}
					else
					{
						setArrNum();
						int target;
						for (int j = 0; j < _vBattle.size(); j++)
						{
							if (_vBattle[_vCreature[i].arrNum].attackTarget == _vBattle[j].target)
							{
								target = _vBattle[j].arrNum;
								break;
							}
						}
						attackSomeone(i, target);

					}
					
					break;
				
				}



				if ( _vBattle[_vCreature[i].arrNum].sourX >= _vCreature[i].img[STATE_MOVE]->getMaxFrameX())
				{
					_vCreature[i].state = STATE_IDLE;
					 _vBattle[_vCreature[i].arrNum].sourX = -1;
					 sort(_vBattle.begin(), _vBattle.end());
					 if (!_attack)
					 {
						 _turn = false;

						 setTurn();
					 }
					 else
					 {
						 setArrNum();
						 int target;
						 for (int j = 0; j < _vBattle.size(); j++)
						 {
							 if (_vBattle[_vCreature[i].arrNum].attackTarget == _vBattle[j].target)
							 {
								 target = _vBattle[j].arrNum;
								 break;
							 }
						 }
						 attackSomeone(i, target);

					 }


				}
				_vBattle[_vCreature[i].arrNum].sourX++;

			}

		}
		/*
		if (_vCreature[_currentCreature].state == STATE_DOWN ||
			_vCreature[_currentCreature].state == STATE_FRONT ||
			_vCreature[_currentCreature].state == STATE_UP)
		{
			//if(_vCreature[_currentCreature].img[_vCreature[_currentCreature].state]->getMaxFrameX() )
			_vBattle[_vCreature[_currentCreature].arrNum].sourX++;

			if (_vBattle[_vCreature[_currentCreature].arrNum].sourX >=
				_vCreature[_currentCreature].img[_vCreature[_currentCreature].state]->getMaxFrameX())
			{
				_vCreature[_currentCreature].state = STATE_IDLE;
				_vBattle[current].sourX = 0;
				_attack = false;
			}

			if (_vBattle[_vCreature[_currentCreature].arrNum].sourX ==
				_vCreature[_currentCreature].img[_vCreature[_currentCreature].state]->getMaxFrameX()-1)
			{
				for (int i = 0; i < _vBattle.size(); i++)
				{
					if (_vBattle[i].target == _vBattle[_vCreature[_currentCreature].arrNum].attackTarget)
					{
						target = i;
					}
				}


				int dmg = RND->getFromIntTo(_vCreature[_currentCreature].minDmg, _vCreature[_currentCreature].maxDmg);
				int atk = _vCreature[_currentCreature].atk;
				int def = _vCreature[_vBattle[target].arrNum].def;
				int totalDmg = dmg * _vCreature[_currentCreature].quantity;
				int revise = atk - def;
				int hp = _vCreature[_vBattle[target].arrNum].currentHp;
				int totalHp = (_vCreature[_vBattle[target].arrNum].quantity-1) * _vCreature[_vBattle[target].arrNum].hp + hp;

				if (revise >= 60) revise = 60;
				if (revise <= -28) revise = -28;
				if (revise >= 0)
				{
					totalDmg = totalDmg * (1 + 0.05*revise);
				}
				else
				{
					totalDmg = totalDmg * (1 - 0.025*abs(revise));
				}


				if (totalDmg >= totalHp)
				{
					_vCreature[_vBattle[target].arrNum].state = STATE_DEAD;
				}
				else
				{
					totalHp -= totalDmg;
					_vCreature[_vBattle[target].arrNum].quantity = totalHp / _vCreature[_vBattle[target].arrNum].hp + 1;
					_vCreature[_vBattle[target].arrNum].currentHp = totalHp % _vCreature[_vBattle[target].arrNum].hp;

					if (_vCreature[_vBattle[target].arrNum].currentHp == 0)
					{
						_vCreature[_vBattle[target].arrNum].quantity -= 1;
						_vCreature[_vBattle[target].arrNum].currentHp = _vCreature[_vBattle[target].arrNum].hp;

					}

					_vCreature[_vBattle[target].arrNum].state = STATE_DAMAGED;
				}


			}


		}
		*/

		for (int i = 0; i < _vCreature.size(); i++)
		{
			

			if (_vCreature[i].state == STATE_DAMAGED)
			{
				_vBattle[_vCreature[i].arrNum].sourX++;

				if (_vBattle[_vCreature[i].arrNum].sourX >= _vCreature[i].img[STATE_DAMAGED]->getMaxFrameX())
				{
					int target;

					for (int j = 0; j < _vBattle.size(); j++)
					{
						if (_vBattle[_vCreature[i].arrNum].attackTarget == _vBattle[j].target)
						{
							target = _vBattle[j].arrNum;
						}
					}

					_vCreature[i].state = STATE_IDLE;
					_vBattle[_vCreature[i].arrNum].sourX = 0;
					
					if (_vBattle[_vCreature[i].arrNum].counter || i == _currentCreature)
					{
						_turn = false;
						_attack = false;
						setTurn();
					}
					else if(!_vBattle[_vCreature[i].arrNum].counter && i != _currentCreature)
					{
						attackSomeone(i, target);
						_vBattle[_vCreature[i].arrNum].counter = true;
					}
				}
			}

			else if (_vCreature[i].state == STATE_DEAD && !_vCreature[i].isDead)
			{
				if (_vBattle[_vCreature[i].arrNum].sourX < _vCreature[i].img[STATE_DEAD]->getMaxFrameX())
				{
					_vBattle[_vCreature[i].arrNum].sourX++;
				}
				if (_vBattle[_vCreature[i].arrNum].sourX == _vCreature[i].img[STATE_DEAD]->getMaxFrameX() &&
					!_vCreature[i].isDead)
				{
					_vCreature[i].isDead = true;
					_turn = false;
					_attack = false;
					setTurn();
				}

			}
			else if (_vCreature[i].state == STATE_FRONT || _vCreature[i].state == STATE_DOWN || _vCreature[i].state == STATE_UP)
			{
				
				_vBattle[_vCreature[i].arrNum].sourX++;

				if (_vBattle[_vCreature[i].arrNum].sourX >=
					_vCreature[i].img[_vCreature[i].state]->getMaxFrameX())
				{
					_vCreature[i].state = STATE_IDLE;
					_vBattle[_vCreature[i].arrNum].sourX = 0;
					
				}

				if (_vBattle[_vCreature[i].arrNum].sourX ==
					_vCreature[i].img[_vCreature[i].state]->getMaxFrameX() - 1)
				{
					int target;

					for (int j = 0; j < _vBattle.size(); j++)
					{
						if (_vBattle[_vCreature[i].arrNum].attackTarget == _vBattle[j].target)
						{
							target = _vBattle[j].arrNum;
							_vBattle[j].attackTarget = _vBattle[_vCreature[i].arrNum].target;

						}
					}

					int dmg = RND->getFromIntTo(_vCreature[i].minDmg, _vCreature[i].maxDmg);
					int atk = _vCreature[i].atk;
					int def = _vCreature[target].def;
					int totalDmg = dmg * _vCreature[i].quantity;
					int revise = atk - def;
					int hp = _vCreature[target].currentHp;
					int totalHp = (_vCreature[target].quantity - 1) * _vCreature[target].hp + hp;

					if (revise >= 60) revise = 60;
					if (revise <= -28) revise = -28;
					if (revise >= 0)
					{
						totalDmg = totalDmg * (1 + 0.05*revise);
					}
					else
					{
						totalDmg = totalDmg * (1 - 0.025*abs(revise));
					}


					if (totalDmg >= totalHp)
					{
						_vCreature[target].state = STATE_DEAD;
					}
					else
					{
						totalHp -= totalDmg;
						_vCreature[target].quantity = totalHp / _vCreature[target].hp + 1;
						_vCreature[target].currentHp = totalHp % _vCreature[target].hp;

						if (_vCreature[target].currentHp == 0)
						{
							_vCreature[target].quantity -= 1;
							_vCreature[target].currentHp = _vCreature[target].hp;

						}

						_vCreature[target].state = STATE_DAMAGED;

						//attackSomeone(target, i);
					}


					

					
				}
				else if (_vCreature[i].state == STATE_IDLE)
				{
					_vBattle[_vCreature[i].arrNum].sourX = 0;
				}

			}

		}

		//for (int i = 0; i < _vCreature.size(); i++)
		//{
		//
		//	if (_vCreature[i].state == STATE_DEAD)
		//	{
		//		for (int i = 0; i < _vBattle.size(); i++)
		//		{
		//			if (_vBattle[i].target == _vBattle[_vCreature[_currentCreature].arrNum].attackTarget)
		//			{
		//				target = i;
		//			}
		//		}
		//
		//
		//		
		//
		//		if (_vBattle[_vCreature[i].arrNum].sourX < _vCreature[i].img[STATE_DEAD]->getMaxFrameX())
		//		{
		//			_vBattle[_vCreature[i].arrNum].sourX++;
		//		}
		//		if (_vBattle[_vCreature[i].arrNum].sourX >= _vCreature[i].img[STATE_DEAD]->getMaxFrameX() &&
		//			!_vCreature[_vBattle[target].arrNum].isDead)
		//		{
		//			_vCreature[_vBattle[target].arrNum].isDead = true;
		//			_turn = false;
		//			setTurn();
		//		}
		//
		//	}
		//}


		 _vBattle[_vCreature[_currentCreature].arrNum].count = 6;
	}


}

void battle::attackSomeone(int x, int y)
{
	setArrNum();

	int attacker = _vCreature[x].arrNum;
	int victim = _vCreature[y].arrNum;


	if (_vBattle[attacker].arrY % 2 == 0)
	{
		if (_vBattle[attacker].arrX < _vBattle[victim].arrX)
		{
			_vBattle[attacker].isRight = true;
			_vBattle[victim].isRight = false;
		}
		else
		{
			_vBattle[attacker].isRight = false;
			_vBattle[victim].isRight = true;
		}

	}
	else
	{
		if (_vBattle[attacker].arrX > _vBattle[victim].arrX)
		{
			_vBattle[attacker].isRight = false;
			_vBattle[victim].isRight = true;
		}
		else
		{
			_vBattle[attacker].isRight = true;
			_vBattle[victim].isRight = false;
		}
	}

	

	if (_vBattle[attacker].arrY == _vBattle[victim].arrY)
	{
		_vCreature[x].state = STATE_FRONT;
	}
	else if (_vBattle[attacker].arrY > _vBattle[victim].arrY)
	{
		_vCreature[x].state = STATE_UP;
	}
	else if (_vBattle[attacker].arrY < _vBattle[victim].arrY)
	{
		_vCreature[x].state = STATE_DOWN;
	}
	_vBattle[attacker].sourX = 0;

}

void battle::setTurn(void)
{
	for (int i = 0; i < _vBattle.size(); i++)
	{
		//=========== 크리쳐 서잇는곳 다 유닛으로 바까줌
		_battleArr[_vBattle[i].arrX][_vBattle[i].arrY].unit = true;
		if (_vCreature[_vBattle[i].arrNum].size == 2)
		{
			_battleArr[_vBattle[i].arrX - 1][_vBattle[i].arrY].unit = true;
		
		}
		
	}
	

	if (_currentCreature < _vBattle.size())
	{
		//======== 그 다음턴 얘 설정
		_vBattle[_vCreature[_currentCreature].arrNum].turn = false;
	}

	while(true)
	{
		//========== 커런트 크리쳐 설정 
		_currentCreature--;

		if (_currentCreature < 0)
		{
			_currentCreature = _vCreature.size() - 1;
			for (int i = 0; i < _vBattle.size(); i++)
			{
				_vBattle[i].counter = false;
			}
		}

		if (!_vCreature[_currentCreature].isDead)
		{
			_vBattle[_vCreature[_currentCreature].arrNum].turn = true;
			break;
		}
	}

	for (int i = 0; i < MAXGRIDX; i++)
	{
		for (int j = 0; j < MAXGRIDY; j++)
		{
			//=========== 타일 초기화
			_battleArr[i][j].range = false;
			_battleArr[i][j].attack = false;
		}
	}

	for (int i = 0; i < MAXGRIDX; i++)
	{
		for (int j = 0; j < MAXGRIDY; j++)
		{
			//========== 이동 범위 설정
			int current = _vCreature[_currentCreature].arrNum;

			if (getValueH(_vBattle[current].arrX, _vBattle[current].arrY, i, j) <= _vCreature[_currentCreature].speed)
			{

				int size = getPath(_vBattle[_vCreature[_currentCreature].arrNum].arrX, _vBattle[_vCreature[_currentCreature].arrNum].arrY,
					i, j, _vCreature[_currentCreature].fly).size();

				if (size <= _vCreature[_currentCreature].speed && !_battleArr[i][j].closed)
				{
					if (!_battleArr[i][j].unit) _battleArr[i][j].range = true;
					if (i == _vBattle[current].arrX && j == _vBattle[current].arrY) _battleArr[i][j].range = true;

					if (_vCreature[_currentCreature].size == 2 && i == _vBattle[current].arrX -1&& j == _vBattle[current].arrY) _battleArr[i][j].range = true;

					//============ 사이즈 2 일때 내 바로 왼쪽 이동범위 여는거
					if (_vCreature[_currentCreature].size == 2 && _vBattle[_vCreature[_currentCreature].arrNum].arrX >= 2 &&
						!_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX - 2][_vBattle[_vCreature[_currentCreature].arrNum].arrY].closed)
					{
						_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX - 1][_vBattle[_vCreature[_currentCreature].arrNum].arrY].range = true;
					}

				}



			}



			//int size = getPath(_vBattle[_vCreature[_currentCreature].arrNum].arrX, _vBattle[_vCreature[_currentCreature].arrNum].arrY,
			//	i, j, _vCreature[_currentCreature].fly).size();
			//
			//if (size <= _vCreature[_currentCreature].speed && !_battleArr[i][j].closed )
			//{
			//	if(!_battleArr[i][j].unit) _battleArr[i][j].range = true;
			//	if (_vCreature[_currentCreature].size == 2 && _vBattle[_vCreature[_currentCreature].arrNum].arrX >= 2 && 
			//		!_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX -2][_vBattle[_vCreature[_currentCreature].arrNum].arrY].closed)
			//	{
			//		_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX - 1][_vBattle[_vCreature[_currentCreature].arrNum].arrY].range = true;
			//	}
			//
			//}



			//if (getPath( _vBattle[_vCreature[_currentCreature].arrNum].arrX,  _vBattle[_vCreature[_currentCreature].arrNum].arrY,
			//	i, j, _vCreature[_currentCreature].fly).() <=
			//	_vCreature[_currentCreature].speed &&
			//	!_battleArr[i][j].closed)
			//{
			//	_battleArr[i][j].range = true;		
			//	_battleArr[i][j].attack = true;
			//
			//	// 공격 범위 설정
			//	getPath
			//
			//
			//}
		}
	}
	if (_vCreature[_currentCreature].size == 2)
	{
		for (int i = 0; i < MAXGRIDX; i++)
		{
			for (int j = 0; j < MAXGRIDY; j++)
			{
				//======== 사이즈 2일때 1칸짜리 지우기
				if (_battleArr[i][j].range)
				{
					if (!_battleArr[i - 1][j].range && !_battleArr[i + 1][j].range)
					{
						_battleArr[i][j].range = false;
					}

					if (i == MAXGRIDX - 1 && !_battleArr[i-1][j].range)
					{
						_battleArr[i][j].range = false;
					}
				}
			}
		}
	}

	for (int i = 0; i < MAXGRIDX; i++)
	{
		for (int j = 0; j < MAXGRIDY; j++)
		{
			if (_battleArr[i][j].range)
			{
				_battleArr[i][j].attack = true;
	
				if (i - 1 >= 0 && !_battleArr[i - 1][j].closed) _battleArr[i - 1][j].attack = true;
				if (i + 1 < MAXGRIDX && !_battleArr[i + 1][j].closed) _battleArr[i + 1][j].attack = true;
				if (j - 1 >= 0)
				{
					if (!_battleArr[i][j - 1].closed)_battleArr[i][j - 1].attack = true;
					if (j % 2 == 0 && i + 1 < MAXGRIDX && !_battleArr[i + 1][j - 1].closed) _battleArr[i + 1][j - 1].attack = true;
					else if (j % 2 == 1 && i - 1 >= 0 && !_battleArr[i - 1][j - 1].closed) _battleArr[i - 1][j - 1].attack = true;
				}
				if (j + 1 < MAXGRIDY)
				{
					if (!_battleArr[i][j + 1].closed) _battleArr[i][j + 1].attack = true;
					if (j % 2 == 0 && i + 1 < MAXGRIDX && !_battleArr[i + 1][j + 1].closed) _battleArr[i + 1][j + 1].attack = true;
					else if (j % 2 == 1 && i - 1 >= 0 && !_battleArr[i - 1][j + 1].closed) _battleArr[i - 1][j + 1].attack = true;
				}
				
			}
		}
	}

	sort(_vBattle.begin(), _vBattle.end());


}

int battle::isAnybody(int x, int y)
{
	int tmp = -1;

	for (int i = 0; i < _vBattle.size(); i++)
	{
		if (_vBattle[i].arrX == x && _vBattle[i].arrY == y)
		{
			tmp = _vBattle[i].target;
			break;
		}
	}

	return tmp;
}

int battle::isAnybody(int x, int y, bool arrNum)
{
	if (true)
	{
		int tmp = -1;

		for (int i = 0; i < _vBattle.size(); i++)
		{
			if (_vBattle[i].arrX == x && _vBattle[i].arrY == y)
			{
				tmp = i;
				break;
			}
		}

		return tmp;

	}
	return false;
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


		//=============== C R E A T U R E   M O V E ======================
		for (int i = 0; i < MAXGRIDX; i++)
		{
			if (getMouseArr().x < 0 || getMouseArr().x >= MAXGRIDX ||
				getMouseArr().y < 0 || getMouseArr().y >= MAXGRIDY) break;

			for (int j = 0; j < MAXGRIDY; j++)
			{
				if (getMouseArr().x < 0 || getMouseArr().x >= MAXGRIDX ||
					getMouseArr().y < 0 || getMouseArr().y >= MAXGRIDY) break;


				//===================== 공격 할때 ======================
				if (_vBattle[_vCreature[_currentCreature].arrNum].player &&
					_battleArr[getMouseArr().x][getMouseArr().y].attack && !_move &&
					isAnybody(getMouseArr().x,getMouseArr().y) != -1 && 
					!_vBattle[isAnybody(getMouseArr().x, getMouseArr().y,true)].player &&
					_button == BAB_NULL && _cursor == CUR_ATKMELEE && !_turn )
				{
					_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX][_vBattle[_vCreature[_currentCreature].arrNum].arrY].unit = false;
					if (_vCreature[_currentCreature].size == 2)
					{
						_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX - 1][_vBattle[_vCreature[_currentCreature].arrNum].arrY].unit = false;
					}
					
					int tmp0 = 0;	// === X 좌표 보정용
					int tmp1 = 0;	// === Y 좌표 보정용
					int target;		// ==== 누구 때릴래
					_vBattle[_vCreature[_currentCreature].arrNum].attackTarget = isAnybody(getMouseArr().x, getMouseArr().y);

					for (int i = 0; i < _vBattle.size(); i++)
					{
						if (_vBattle[_vCreature[_currentCreature].arrNum].attackTarget == _vBattle[i].target)
						{
							target = _vBattle[i].arrNum;
						}
					}

					switch (IMAGEMANAGER->findImage("battle_cursor_melee")->getFrameX())
					{
					case 0: //============== 오른쪽에서 시계방향으로
						tmp0 = 1;
						tmp1 = 0;
						if (_vCreature[_currentCreature].size == 2) tmp0 = 2;
						break;
					case 1:
						tmp1 = 1;
						if(getMouseArr().y %2 == 0)tmp0 = 1;
						else tmp0 = 0;

						break;
					case 2:
						tmp1 = 1;
						if (getMouseArr().y % 2 == 0)tmp0 = 0;
						else tmp0 = -1;

						break;
					case 3:
						tmp0 = -1;
						tmp1 = 0;

						break;
					case 4:
						tmp1 = -1;
						if (getMouseArr().y % 2 == 0)tmp0 = 0;
						else tmp0 = -1;

						break;
					case 5:
						tmp1 = -1;
						if (getMouseArr().y % 2 == 0)tmp0 = 1;
						else tmp0 = 0;

						break;
					}
					

					_vPath.clear();
					_vPath = getPath(_vBattle[_vCreature[_currentCreature].arrNum].arrX,
						_vBattle[_vCreature[_currentCreature].arrNum].arrY,
						getMouseArr().x + tmp0, getMouseArr().y + tmp1, 
						_vCreature[_currentCreature].fly);

					if (_vPath.size() >= 1)
					{
						_vBattle[_vCreature[_currentCreature].arrNum].sourX = 0;
						_vBattle[_vCreature[_currentCreature].arrNum].sourY = 0;
						_vBattle[_vCreature[_currentCreature].arrNum].count = 0;
						_vCreature[_currentCreature].state = STATE_MOVE;
						_move = true;
					}
					else
					{
						attackSomeone(_currentCreature, target);
					}

					_attack = true;
					_turn = true;
				}

				//===================== 이동만 시킬때 ======================
				if (_vBattle[_vCreature[_currentCreature].arrNum].player &&
					_battleArr[getMouseArr().x][getMouseArr().y].range && !_move &&
					_button == BAB_NULL && _cursor == CUR_MOVE && !_turn &&(
					getMouseArr().x != _vBattle[_vCreature[_currentCreature].arrNum].arrX ||
					getMouseArr().y != _vBattle[_vCreature[_currentCreature].arrNum].arrY))
				{
					int revise = 0;
					_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX][_vBattle[_vCreature[_currentCreature].arrNum].arrY].unit = false;
					if (_vCreature[_currentCreature].size == 2)
					{
						if (!_battleArr[getMouseArr().x - 1][getMouseArr().y].range &&
							getMouseArr().x != _vBattle[_vCreature[_currentCreature].arrNum].arrX + 1 &&
							getMouseArr().y != _vBattle[_vCreature[_currentCreature].arrNum].arrY) revise = 1;
						_battleArr[_vBattle[_vCreature[_currentCreature].arrNum].arrX-1][_vBattle[_vCreature[_currentCreature].arrNum].arrY].unit = false;

					}




					_vPath.clear();
					_vPath = getPath(
						 _vBattle[_vCreature[_currentCreature].arrNum].arrX,
						 _vBattle[_vCreature[_currentCreature].arrNum].arrY,
						getMouseArr().x + revise, getMouseArr().y,
						_vCreature[_currentCreature].fly);

					//if (_vPath.size())
					//	_vPath.erase(_vPath.begin());

					 _vBattle[_vCreature[_currentCreature].arrNum].sourX = 0;
					 _vBattle[_vCreature[_currentCreature].arrNum].sourY = 0;
					 _vBattle[_vCreature[_currentCreature].arrNum].count = 0;
					_vCreature[_currentCreature].state = STATE_MOVE;

					_move = true;
					_turn = true;
				}




				//if ( _vBattle[_vCreature[_currentCreature].arrNum].player &&
				//	getValueH(
				//	 _vBattle[_vCreature[_currentCreature].arrNum].arrX,
				//	 _vBattle[_vCreature[_currentCreature].arrNum].arrY,
				//	getMouseArr().x, getMouseArr().y) <=
				//	_vCreature[_currentCreature].speed)
				//{
				//	_vPath.clear();
				//	_vPath = getPath(
				//	 _vBattle[_vCreature[_currentCreature].arrNum].arrX,
				//	 _vBattle[_vCreature[_currentCreature].arrNum].arrY,
				//	getMouseArr().x, getMouseArr().y,
				//	_vCreature[_currentCreature].fly);
				//
				//	if (_vPath.size())
				//	_vPath.erase(_vPath.begin());
				//
				//	_action = true;
				//}

			}
		}



		//============= M E N U ===========================
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