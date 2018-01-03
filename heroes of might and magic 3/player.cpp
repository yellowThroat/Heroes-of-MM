#include "stdafx.h"
#include "player.h"
#include "playMap.h"
#include "gameScene.h"
#include "zOrder.h"



player::player() {}
player::~player() {}

HRESULT player::init(int myNum)
{
	_myNum = myNum;
	_myTurn = true;
	_cityScene = false;
	_autoCamera = false;
	_window = false;
	_creatureinfo = false;
	_enemyInfo = -1;
	_currentHero = 0;
	_currentCamp = 0;
	_count = 0;
	_currentCreature = -1;
	_destination = { 0,0 };
	_enemyCor = { 0,0 };
	/*
	tagHero tmp;
	tmp.field = IMAGEMANAGER->findImage("hero_castle");
	tmp.fieldShadow = IMAGEMANAGER->findImage("hero_castle_shadow");
	tmp.flag = IMAGEMANAGER->findImage("hero_flag");
	tmp.myNum = 0;
	tmp.angle = 0;
	tmp.kind = 0;
	*/
	addHero(PointMake(5,5),CommonHero(NAME_CHRISTIAN));
	addHero(PointMake(8, 8), CommonHero(NAME_SEPHINE));
	addHero(PointMake(10, 10), CommonHero(NAME_ADELAIDE));
	ZeroMemory(&_myProperty, sizeof(myProperty));
	ZeroMemory(&_myBuilding, sizeof(myBuilding));


	//_myProperty.gold = 123456;
	//_myProperty.gem = 36;
	//_myProperty.wood = 356;
	//_myProperty.iron = 785;
	//_myProperty.crystal = 99;
	//_myProperty.mercury = 123;
	//_myProperty.sulfur = 1234;
	

	setMyInfo();


	return S_OK;
}

void player::release(void)
{

}

void player::update(void)
{
	if (_cityScene)
	{
		cityUpdate();
	}
	else
	{
		fieldUpdate();


	}

	if (_creatureinfo) setFrame();

}

void player::fieldUpdate(void)
{
	for ( _viHero = _vHero.begin(); _viHero != _vHero.end(); ++_viHero)
	{
		(*_viHero)->update();
	}
	camera();

}

void player::cityUpdate(void)
{

}

void player::render(void)
{
	if (_cityScene)
	{
		//================= ���� �� ��
		cityScene();
	}

	else
	{
		//================= �ʵ� �� ��
		fieldScene();
	}

	
}

void player::fieldScene(void)
{
	for (_viHero = _vHero.begin(); _viHero != _vHero.end(); ++_viHero)
	{
		(*_viHero)->render();
	}

	if (_enemyInfo != -1) enemyInfoDraw();

}

void player::setMyInfo(void)
{
	for (int i = 0; i < _gs->getvCamp().size(); i++)
	{
		if (_gs->getvCamp()[i]->getPlayerNum() == 0)
		{
			_myBuilding.camp++;
		}
	}
}

void player::enemyInfoDraw(void)
{
	char tmp[256];
	int indexX;
	int indexY;
	int possesion;

	if (_ob->checkObject(_enemyCor.x, _enemyCor.y))
	{
		possesion = _ob->getvOb(_enemyCor.x, _enemyCor.y).possesion;
		

		if (_ob->getvOb(_enemyCor.x, _enemyCor.y).type == 4) indexY = 0;
		else if (_ob->getvOb(_enemyCor.x, _enemyCor.y).type == 5) indexY = 2;

		if (_ob->getvOb(_enemyCor.x, _enemyCor.y).sub % 2 == 1) indexY++;

		indexX = _ob->getvOb(_enemyCor.x, _enemyCor.y).sub / 2;

		IMAGEMANAGER->findImage("creature_portrait")->frameRender(getMemDC(), 355, 186, indexX, indexY);

		IMAGEMANAGER->findImage("window_unit")->render(getMemDC(), 256, 160);
		IMAGEMANAGER->findImage("window_unit_shadow")->alphaRender(getMemDC(), 256, 160, 150);

		HFONT font = CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));
		HFONT oldfont = (HFONT)SelectObject(getMemDC(), font);
		SelectObject(getMemDC(), font);
		if (possesion <= 5) sprintf(tmp, "����� %s", _enemyName);
		else if (possesion <= 15) sprintf(tmp, "������ %s", _enemyName);
		else if (possesion <= 35) sprintf(tmp, "������ %s", _enemyName);
		else if (possesion <= 85) sprintf(tmp, "�ټ��� %s", _enemyName);
		else if (possesion <= 150) sprintf(tmp, "�� ������ %s", _enemyName);
		else if (possesion > 150) sprintf(tmp, "%s ����", _enemyName);

		SetTextColor(getMemDC(), RGB(255, 255, 255));

		TextOut(getMemDC(), 387 - strlen(tmp) / 2 * 7, 264, tmp, strlen(tmp));
		


		SetTextColor(getMemDC(), RGB(0, 0, 0));
		SelectObject(getMemDC(), oldfont);
		DeleteObject(font);

	}





}

void player::heroInfoDraw(void)
{
	IMAGEMANAGER->findImage("window_heroinfo")->render(getMemDC(), 64, 8);
	IMAGEMANAGER->findImage("window_heroinfo_shadow")->alphaRender(getMemDC(), 64, 8, 150);

	
	for (int i = 0; i < _vHero.size(); i++)
	{
		//=========== ��� ������ �ʻ�ȭ 676 95
		_vHero[i]->getHeroInfo().portraitSmall->frameRender(getMemDC(),
			676, 95 + _vHero[i]->getMyNum() * 54,
			_vHero[i]->getHeroInfo().indexX,
			_vHero[i]->getHeroInfo().indexY);						// �� ������ �ʻ�ȭ �׷���

		IMAGEMANAGER->findImage("select_hero")->render(getMemDC(),		// ���� ���õ� ���� ǥ��
			675, 95 + _currentHero * 54);
	}
		
	tagHero hero;
	hero = _vHero[_currentHero]->getHeroInfo();

	hero.portraitLarge->frameRender(getMemDC(), 83, 26,
		hero.indexX, hero.indexY);								//�ʻ�ȭ 

	numberDraw(getMemDC(), hero.str, 113, 168);					// ��������
	numberDraw(getMemDC(), hero.def, 183, 168);
	numberDraw(getMemDC(), hero.spell, 253, 168);
	numberDraw(getMemDC(), hero.intel, 323, 168);

	numberDraw(getMemDC(), _vHero[_currentHero]->getExp(), 132, 262);
	numberDraw(getMemDC(), _vHero[_currentHero]->getMana(), 276, 262);
	numberDraw(getMemDC(), _vHero[_currentHero]->getMaxMana(), 314, 262);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), 299, 260, "/", 1);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	
	
	HFONT font = CreateFont(24, 0, 0, 0, 50, false, false, false,
		HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));
	HFONT oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(248, 228, 144));
	SelectObject(getMemDC(), font);

	TextOut(getMemDC(), 254 - strlen(hero.name) / 2 * 16, 39, hero.name, strlen(hero.name));

	SetTextColor(getMemDC(), RGB(0, 0, 0));
	DeleteObject(font);
	SelectObject(getMemDC(), oldfont);
	
	font = CreateFont(15, 0, 0, 0, 50, false, false, false,
		HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SelectObject(getMemDC(), font);
	
	char tmp[256];
	sprintf(tmp, "%d", hero.level);

	TextOut(getMemDC(), 215, 64, tmp, strlen(tmp));							// ���� ��ġ

	TextOut(getMemDC(), 232, 64, "����", 4);									// '����'

	TextOut(getMemDC(), 266, 64, hero.jobName, strlen(hero.jobName));		// ���� �̸�

	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);


	//79 - 492  ũ���� �ʻ�ȭ �׷��ֱ� quantity 37 - 53

	for (int j = 0; j < _vHero[_currentHero]->getCreature().size(); j++)
	{
		_vHero[_currentHero]->getCreature()[j].portrait->frameRender(getMemDC(),
			79 + _vHero[_currentHero]->getCreature()[j].position * 66, 492,
			_vHero[_currentHero]->getCreature()[j].tier,
			_vHero[_currentHero]->getCreature()[j].kind *2 +
			_vHero[_currentHero]->getCreature()[j].level);		// �ʻ�ȭ �׸���

		numberDraw(getMemDC(), _vHero[_currentHero]->getCreature()[j].quantity,	// �װ� �������
			136 - (int)log10(_vHero[_currentHero]->getCreature()[j].quantity*10)*7
			+ _vHero[_currentHero]->getCreature()[j].position * 66, 545);
	}

	if (_currentCreature != -1)
	{
		IMAGEMANAGER->findImage("select_creature")->render(getMemDC(), 78 + _currentCreature*66, 491);
	}

	if (_creatureinfo)
	{
		tagCreature tmp;
		tagHero tmpHero;
		tmpHero = _vHero[_currentHero]->getHeroInfo();

		for (int i = 0; i < _vHero[_currentHero]->getCreature().size(); i++)
		{
			if (_vHero[_currentHero]->getCreature()[i].position == _currentCreature)
			{
				tmp = _vHero[_currentHero]->getCreature()[i];
			}
		}

		switch (tmp.kind)
		{
		case 0:
			IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(), 139, 67);
			break;

		case 1:
			IMAGEMANAGER->findImage("dungeon_fort_back")->render(getMemDC(), 139, 67);
			break;
		}


		for (int i = 0; i < _vHero[_currentHero]->getCreature().size(); i++)
		{
			if (_vHero[_currentHero]->getCreature()[i].position == _currentCreature)
			{
				_vHero[_currentHero]->getCreature()[i].imgShadow[_vHero[_currentHero]->getCreature()[i].state]->alphaFrameRender(getMemDC(),
					189 - _vHero[_currentHero]->getCreature()[i].startX,
					189 - _vHero[_currentHero]->getCreature()[i].startY, 150);

				_vHero[_currentHero]->getCreature()[i].img[_vHero[_currentHero]->getCreature()[i].state]->frameRender(getMemDC(),
					189 - _vHero[_currentHero]->getCreature()[i].startX,
					189 - _vHero[_currentHero]->getCreature()[i].startY);




			}



			//if (_vHero[_currentHero]->getCreature()[i].position == _currentCreature)
			//{
			//	_vHero[_currentHero]->getCreature()[i].imgShadow[_vHero[_currentHero]->getCreature()[i].state]->alphaFrameRender(getMemDC(),
			//		189 - _vHero[_currentHero]->getCreature()[i].img[_vHero[_currentHero]->getCreature()[i].state]->getFrameWidth() / 2,
			//		127 - _vHero[_currentHero]->getCreature()[i].img[_vHero[_currentHero]->getCreature()[i].state]->getFrameHeight() / 2, 150);
			//
			//	_vHero[_currentHero]->getCreature()[i].img[_vHero[_currentHero]->getCreature()[i].state]->frameRender(getMemDC(),
			//		189 - _vHero[_currentHero]->getCreature()[i].img[_vHero[_currentHero]->getCreature()[i].state]->getFrameWidth() / 2,
			//		127 - _vHero[_currentHero]->getCreature()[i].img[_vHero[_currentHero]->getCreature()[i].state]->getFrameHeight() / 2);
			//
			//
			//
			//
			//}
		}

		IMAGEMANAGER->findImage("window_creatureinfo")->render(getMemDC(), 119, 21);
		IMAGEMANAGER->findImage("window_creatureinfo_shadow")->alphaRender(getMemDC(), 119, 21, 150);

		//268 42
		HFONT font = CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));
		HFONT oldfont = (HFONT)SelectObject(getMemDC(), font);

		SelectObject(getMemDC(), font);

		SetTextColor(getMemDC(), RGB(248, 228, 144));

		TextOut(getMemDC(), 268 - strlen(tmp.name)/2 * 16, 42, tmp.name, strlen(tmp.name));
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		//345 71
		char tmpChar[256];
		sprintf(tmpChar, "%d (%d)", tmp.atk, tmp.atk + tmpHero.str);

		TextOut(getMemDC(), 392 - strlen(tmpChar)*7, 70, tmpChar, strlen(tmpChar));

		sprintf(tmpChar, "%d (%d)", tmp.def, tmp.def + tmpHero.def);

		TextOut(getMemDC(), 392 - strlen(tmpChar) * 7, 88, tmpChar, strlen(tmpChar));

		sprintf(tmpChar, "%d - %d", tmp.minDmg, tmp.maxDmg);

		TextOut(getMemDC(), 392 - strlen(tmpChar) * 7, 125, tmpChar, strlen(tmpChar));

		sprintf(tmpChar, "%d", tmp.hp);

		TextOut(getMemDC(), 392 - strlen(tmpChar) * 7, 145, tmpChar, strlen(tmpChar));

		sprintf(tmpChar, "%d", tmp.speed);

		TextOut(getMemDC(), 392 - strlen(tmpChar) * 7, 183, tmpChar, strlen(tmpChar));

		sprintf(tmpChar, "%d", tmp.quantity);

		TextOut(getMemDC(), 238 - strlen(tmpChar) * 7, 185, tmpChar, strlen(tmpChar));


		DeleteObject(font);
		SelectObject(getMemDC(), oldfont);

		SetTextColor(getMemDC(), RGB(0, 0, 0));

	}
	
}

void player::setFrame(void)
{
	tagCreature tmp;

	for (int i = 0; i < _vHero[_currentHero]->getCreature().size(); i++)
	{
		if (_vHero[_currentHero]->getCreature()[i].position == _currentCreature)
		{
			tmp = _vHero[_currentHero]->getCreature()[i];
			break;
		}
	}

	if (!_count)
	{
		if (tmp.img[tmp.state]->getFrameX() >= tmp.img[tmp.state]->getMaxFrameX())
		{
			tmp.img[tmp.state]->setFrameX(-1);
			tmp.imgShadow[tmp.state]->setFrameX(-1);

			tmp.state = (CREATURESTATE)(tmp.state + 1);

			if (tmp.state >= STATE_SWITCH) tmp.state = STATE_DOWN;
		}


		tmp.img[tmp.state]->setFrameX(tmp.img[tmp.state]->getFrameX() + 1);
		tmp.imgShadow[tmp.state]->setFrameX(tmp.imgShadow[tmp.state]->getFrameX() + 1);

		_count = 6;

	}
	else _count--;
	

	for (int i = 0; i < _vHero[_currentHero]->getCreature().size(); i++)
	{
		if (_vHero[_currentHero]->getCreature()[i].position == _currentCreature)
		{
			_vHero[_currentHero]->setCreature(tmp, i);
			break;
		}

	}
}

void player::cityScene(void)
{
	
	
}

void player::enterCity(void)
{
}

void player::camera(void)
{
	_mouseArr.x = (_ptMouse.x + DATABASE->getPlayCameraX()) / TILESIZE;
	_mouseArr.y = (_ptMouse.y + DATABASE->getPlayCameraY()) / TILESIZE;

	for ( _viHero = _vHero.begin(); _viHero != _vHero.end(); ++_viHero)
	{
		if (_autoCamera)
		{
			if ((*_viHero)->getGoOn())
			{
				float x;
				float y;
				x = ((*_viHero)->getHeroX() - 12 * TILESIZE);
				y = ((*_viHero)->getHeroY() - 9 * TILESIZE);
		
				_pm->setCameraX(x);
				_pm->setCameraY(y);
				//DATABASE->setPlayCameraX(x);
				//DATABASE->setPlayCameraY(y);
				
		
			}
		}

		if ((*_viHero)->getMoveEnd())
		{
			float x;
			float y;
			x = ((*_viHero)->getHeroPoint().x - 12)*TILESIZE;
			y = ((*_viHero)->getHeroPoint().y - 9)*TILESIZE;

			_pm->setCameraX(x);
			_pm->setCameraY(y);
			_autoCamera = false;
			
			(*_viHero)->setMoveEnd(false);

		}

		

	}
}

void player::activeObject(void)
{
	for (int i = 0; i < _vHero.size(); i++)
	{
		
		if (_ob->checkObject(_vHero[i]->getHeroDest().x, _vHero[i]->getHeroDest().y) &&
			_pm->getTileInfo(_vHero[i]->getHeroDest().x, _vHero[i]->getHeroDest().y).loot &&
			_vHero[i]->getGoOn())
		{
			int x = _vHero[i]->getHeroDest().x;
			int y = _vHero[i]->getHeroDest().y;

			switch (_ob->getvOb(x, y).type)
			{
			case 2:
			{
				switch (_ob->getvOb(x, y).sub)
				{
				case 0:
				{
					_myProperty.gold += RND->getFromIntTo(500, 1000);
					int ran = RND->getInt(4);
					if (!ran) _myProperty.gem += RND->getFromFloatTo(5, 7);
					if (ran == 1) _myProperty.crystal += RND->getFromIntTo(5, 7);
					if (ran == 2) _myProperty.sulfur += RND->getFromIntTo(5, 7);
					if (ran == 3) _myProperty.mercury += RND->getFromIntTo(5, 7);

				}

				break;
				case 1:

				break;
				case 2:
					_myProperty.crystal += RND->getFromIntTo(3, 4);
				break;
				case 3:
					_myProperty.gem += RND->getFromIntTo(3, 4);

				break;
				case 4:
					_myProperty.gold += RND->getFromIntTo(1000, 1500);

				break;
				case 5:
					_myProperty.mercury += RND->getFromIntTo(3, 4);

				break;
				case 6:
					_myProperty.iron += RND->getFromIntTo(3, 4);

				break;
				case 7:
					_myProperty.sulfur += RND->getFromIntTo(3, 4);

				break;
				case 8:
					_myProperty.wood += RND->getFromIntTo(3, 4);

				break;
				}
				_zOrder->deleteRender(x, y);
				_pm->setClosed(x, y, false);
				_pm->setLoot(x,y, false);
				_ob->deleteOb(x, y);

			}
			break;
			case 3:

			break;
			case 4:

			break;
			case 5:

			break;
			}


		}
	}
}

void player::weekGo(void)
{
	for (int i = 0; i < _gs->getvCamp().size(); i++)
	{
		_gs->getvCamp()[i]->weekGo();
	}
}

void player::dayGo(void)
{
	for (int i = 0; i < _vHero.size(); i++)
	{
		_vHero[i]->dayGo();
	}
	_myProperty.crystal += _myBuilding.crystal;
	_myProperty.gem += _myBuilding.gem;
	_myProperty.iron += _myBuilding.iron;
	_myProperty.mercury += _myBuilding.mercury;
	_myProperty.sulfur += _myBuilding.sulfur;
	_myProperty.wood += _myBuilding.wood;
	
	int gold;
	gold = _myBuilding.gold * 1000;
	for (int i = 0; i < _gs->getvCamp().size(); i++)
	{
		_gs->getvCamp()[i]->dayGo();
		if (_gs->getvCamp()[i]->getNum() == 0)
		{
			switch (_gs->getvCamp()[i]->getHall())
			{
			case 0:
				break;

			case 1:
				gold += 500;
				break;

			case 2:
				gold += 1000;
				break;

			case 3:
				gold += 2000;
				break;
			case 4:
				gold += 4000;
				break;
			}
		}
	}
	_myProperty.gold += gold;
}

void player::addHero(POINT point,tagHero heroInfo)
{
	hero* he;

	he = new hero;
	he->setPlayerAddressLink(this);
	he->setPlayMapAddressLink(_pm);
	he->init(point, heroInfo);
	he->setMynum(_vHero.size());
	_pm->setClosed(point.x, point.y, true);


	//=============== z order�� ���� ===================
	tagRender render;
	ZeroMemory(&render, sizeof(tagRender));
	
	render.img = heroInfo.field;
	render.shadowImg = heroInfo.fieldShadow;
	render.flag = heroInfo.flag;
	render.destX = (point.x - 1) * TILESIZE;
	render.destY = (point.y - 1) * TILESIZE;
	render.sourX = render.img->getFrameX();
	render.sourY = render.img->getFrameY();
	render.sizeX = 0;
	render.sizeY = 2* TILESIZE;
	render.identity = he->getMyNum();
	render.kind = 10;

	_zOrder->addRender(render);


	_vHero.push_back(he);

}

void player::inputCity(void)
{

	//
	// ���� ���ܵ�����
	//
	// ����ؾ��� �ڵ��.....
	//
	// �ϴ� �����ִ°��� �� ����
	//
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//==================== C I T Y   S C E N E =====================
		//============== ķ�� ����!
		for (int i = 0; i < _gs->getvCamp().size(); i++)
		{

			//==========���� ���� �ִ� ���� �Ӿ�?
			if (_currentCamp == _gs->getvCamp()[i]->getNum())
			{
				//========= �ٸ� ���� �ִ� â ����?
				if (!_gs->getvCamp()[i]->getWindow())
				{

					switch (_gs->getvCamp()[i]->getCityInfo().camp)
					{
					case CAMP_CASTLE:
						if (getMenuC())
						{
							//========== â�� ���Ȱ� ���� ��â�� �̰ž�!
							_gs->getvCamp()[i]->setWindow(true);
							_gs->getvCamp()[i]->setWindowNum(getPixelC());



						}

						break;
					case CAMP_DUNGEON:
						if (getMenuD())
						{
							//========== â�� ���Ȱ� ���� ��â�� �̰ž�!
							_gs->getvCamp()[i]->setWindow(true);
							_gs->getvCamp()[i]->setWindowNum(getPixelD());


						}

						break;
					}
					//==========�� ��� ������?

					//============= ������ ������ ===========
					if (PtInRect(&RectMake(744, 544, 48, 30), _ptMouse))
					{
						_cityScene = false;
						setProperty(_gs->getvCamp()[i]->getProperty());
					}

				}
				//=============â�� ���� �־�?
				else
				{
					switch (_gs->getvCamp()[i]->getCityInfo().camp)
					{
					case CAMP_CASTLE:
						switch (_gs->getvCamp()[i]->getWindowNum())
						{
							//=========== Ȧ�� ��������
						case 0:
							if (!_gs->getvCamp()[i]->getContents())
							{
								if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
								{
									_gs->getvCamp()[i]->setWindow(false);
								}

								for (int j = 0; j < 16; j++)
								{
									if (PtInRect(&RectMake(
										_gs->getvCamp()[i]->getStructure(j).x,
										_gs->getvCamp()[i]->getStructure(j).y,
										150, 70), _ptMouse))
									{
										_gs->getvCamp()[i]->setSaveStructure(j);
										_gs->getvCamp()[i]->setContents(true);
									}

								}



							}
							else
							{
								if (PtInRect(&RectMake(492, 486, 64, 30), _ptMouse))
								{
									_gs->getvCamp()[i]->setContents(false);
								}




							}
							break;

							//=========== ��ä�� �������� 
						case 1:

							//=========== â ����
							if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
							{
								_gs->getvCamp()[i]->setWindow(false);
							}




							break;
						
						
						case 8:



							break;

						default:
							_gs->getvCamp()[i]->setWindow(false);

							break;

						}


						break;
					case CAMP_DUNGEON:
						switch (_gs->getvCamp()[i]->getWindowNum())
						{
							//=========== Ȧ�� ��������
						case 0:
							if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
							{
								_gs->getvCamp()[i]->setWindow(false);
							}
							break;

							//=========== ��ä�� �������� 
						case 1:




							//=========== â ����
							if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
							{
								_gs->getvCamp()[i]->setWindow(false);
							}

							break;

						}
					default:
						_gs->getvCamp()[i]->setWindow(false);

						break;


						break;
					}
				}











			}
		}



	}
}

void player::inputField(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_ob->checkObject(_mouseArr.x, _mouseArr.y) &&
			_ob->getvOb(_mouseArr.x, _mouseArr.y).type >= 4 &&
			_enemyInfo == -1)
		{
			sprintf(_enemyName,"%s", CommonCreature(
				_ob->getvOb(_mouseArr.x, _mouseArr.y).type - 4,
				_ob->getvOb(_mouseArr.x, _mouseArr.y).sub / 2,
				_ob->getvOb(_mouseArr.x, _mouseArr.y).sub % 2).name);
			_enemyCor.x = _mouseArr.x;
			_enemyCor.y = _mouseArr.y;
			_enemyInfo = _ob->getvOb(_mouseArr.x, _mouseArr.y).sub;
		}
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_enemyInfo = -1;
	}



	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//====================  F I E L D   S C E N E =====================
		if (!_window)
		{
			for (int i = 0; i < _vHero.size(); i++)
			{
				if (_vHero[i]->getMyNum() == _currentHero && !_vHero[i]->getGoOn() &&
					(_mouseArr.x != _vHero[i]->getHeroDest().x ||
						_mouseArr.y != _vHero[i]->getHeroDest().y))
				{
					_vHero[i]->setPath(_pm->getPath(_vHero[i]->getHeroPoint().x,
						_vHero[i]->getHeroPoint().y,
						_mouseArr.x, _mouseArr.y));

					if (_vHero[i]->getPath().size())
					{
						POINT tmp;
						tmp.x = _vHero[i]->getPath()[_vHero[i]->getPath().size() - 1].x;
						tmp.y = _vHero[i]->getPath()[_vHero[i]->getPath().size() - 1].y;

						_vHero[i]->setHeroDest(tmp);

					}
					if (_vHero[i]->getPath().size() < 20)
					{
						DATABASE->setMoveSpeed(4);
					}
					else if (_vHero[i]->getPath().size() >= 20 && _vHero[i]->getPath().size() < 40)
					{
						DATABASE->setMoveSpeed(10);

					}
					else
					{
						DATABASE->setMoveSpeed(15);

					}
					_vHero[i]->setPreviousPath(_vHero[i]->getHeroPoint());

				}

				else  if (
					_mouseArr.x == _vHero[i]->getHeroDest().x	&&
					_mouseArr.y == _vHero[i]->getHeroDest().y	&&
					!_vHero[i]->getGoOn()						&&
					_currentHero == _vHero[i]->getMyNum()		&&
					_vHero[i]->getPath().size()					&& 
					!(_pm->getClosed(_mouseArr.x, _mouseArr.y)	&& !_pm->getTileInfo(_mouseArr.x,_mouseArr.y).loot)	&&
					_vHero[i]->getNeedAp() <= _vHero[i]->getAP())
				{
					_vHero[i]->setGoOn(true);
					if (_pm->getTileInfo(_mouseArr.x, _mouseArr.y).loot)
					{
						if (_vHero[i]->getPath().size() == 1 )
						{
							activeObject();
							_vHero[i]->setGoOn(false);
							_vHero[i]->clearDraw();
						}
							_vHero[i]->deletePath(_vHero[i]->getPath().size() - 1);
					}
					//if (!_autoCamera) _autoCamera = true;
					//_pm->setClosed(_vHero[i]->getHeroPoint().x, _vHero[i]->getHeroPoint().y, false);
					if (_vHero[i]->getInCamp() != -1)										// ķ���� �ִ� ���̶��
					{
						_gs->getvCamp()[_vHero[i]->getInCamp()]->setHero(false);	// �־��� ���� ���� �����ٰ� �˷���
						//_vHero[i]->setInCamp(-1);									// ķ�� ���Ӵٰ� �ʱ�ȭ ���ְ�

					}


				}

			}
		}
		if(_window)
		{
			if (!_creatureinfo)		// ũ���� ����â �ȿ�������
			{
				for (int i = 0; i < 7; i++) // ũ���ĸ� ��������
				{
					bool end = false;
					if (PtInRect(&RectMake(79 + 66*i, 492, 58, 64), _ptMouse))
					{
						vector<tagCreature> tmpCreature;
						tmpCreature = _vHero[_currentHero]->getCreature();

						if (_currentCreature == -1) //���� ũ���İ� ���ٸ�
						{
							//========= �� �ڸ��� ũ���İ� �ִ��� ���� Ȯ���ϰ�
							for (int j = 0; j < tmpCreature.size(); j++)
							{
								if (tmpCreature[j].position == i) //�� �ڸ��� ũ���İ� �ִٸ�
								{
									_currentCreature = i;
									end = true;
								}
							}
						}
						else //=================== ���� ���õ� ũ���İ� �ִٸ�
						{
							if (_currentCreature == i) //============== �� ���� �ڸ��� �����ٸ�
							{
								_creatureinfo = true; //=============== ũ���� ����â�� ����
								end = true;
							}
							else //============= �ٸ� �ڸ��� �����ٸ�
							{
								int tmp0 = 0;
								int tmp1 = 8;
								for (int j = 0; j < tmpCreature.size(); j++)
								{
									if (tmpCreature[j].position == _currentCreature)
									{
										tmp0 = j;
									}
									if (tmpCreature[j].position == i)
									{
										tmp1 = j;
									}
								}

								if (tmp1 < tmpCreature.size() &&
									tmpCreature[tmp0].kind == tmpCreature[tmp1].kind &&
									tmpCreature[tmp0].tier == tmpCreature[tmp1].tier &&
									tmpCreature[tmp0].level == tmpCreature[tmp1].level)
								{
									tmpCreature[tmp1].quantity += tmpCreature[tmp0].quantity;
									tmpCreature.erase(tmpCreature.begin() + tmp0);
									_vHero[_currentHero]->setCreature(tmpCreature);
								}
								else
								{
									for (int j = 0; j < tmpCreature.size(); j++) 
									{
										if (tmpCreature[j].position == _currentCreature) // ���� ���õ� ũ���ĸ� ��� �ٸ����� ������
										{
											tmpCreature[j].position = -1;
										}
										if (tmpCreature[j].position == i) // �� �ڸ��� �ִ��� ���� ���õ� ������ ������
										{
											tmpCreature[j].position = _currentCreature;
										}
										if (tmpCreature[j].position == -1) //�� ���� ���´� ũ���� �����Ѱ����� ����
										{
											tmpCreature[j].position = i;
										}
										// �׸��� �װ� �ٽ� �Է�����
										_vHero[_currentHero]->setCreature(tmpCreature);
									}
								}
								_currentCreature = -1;
								end = true;
							}
						}
						if (end) break;
					}
				}





				// ===================== ���� ���°�
				for (int i = 0; i < 8; i++)
				{
					if (PtInRect(&RectMake(675, 95 + 54 * i, 46, 30),_ptMouse))
					{
						if(i < _vHero.size())
						_currentHero = i;
						_currentCreature = -1;
					}
				}

				//====================== ����â �ݱ�

				if (PtInRect(&RectMake(674, 523, 52, 36), _ptMouse))
				{
					_currentCreature = -1;
					_window = false;
				}

			}
			else				//=====================ũ���� ���� â ���� ����
			{






				//============== ũ���� ����â �ݰ� ���� ũ���� �ʱ�ȭ
				if (PtInRect(&RectMake(335, 258, 64, 30),_ptMouse))
				{
					_creatureinfo = false;
					_currentCreature = -1;
				}
			}

		}


	}
}
