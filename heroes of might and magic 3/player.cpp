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
	_currentHero = 0;
	_currentCreature = -1;
	_destination = { 0,0 };
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


	_myProperty.gold = 123456;
	_myProperty.gem = 36;
	_myProperty.wood = 356;
	_myProperty.iron = 785;
	_myProperty.crystal = 99;
	_myProperty.mercury = 123;
	_myProperty.sulfur = 1234;
	




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

		//sort(_vHero.begin(), _vHero.end(), hero::comp);
	}

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
		//================= 마을 안 신
		cityScene();
	}

	else
	{
		//================= 필드 밖 신
		fieldScene();
	}

	
}

void player::fieldScene(void)
{
	for (_viHero = _vHero.begin(); _viHero != _vHero.end(); ++_viHero)
	{
		(*_viHero)->render();
	}

}

void player::heroInfoDraw(void)
{
	IMAGEMANAGER->findImage("window_heroinfo")->render(getMemDC(), 64, 8);
	IMAGEMANAGER->findImage("window_heroinfo_shadow")->alphaRender(getMemDC(), 64, 8, 150);

	
	for (int i = 0; i < _vHero.size(); i++)
	{
		//=========== 모든 영웅의 초상화 676 95
		_vHero[i]->getHeroInfo().portraitSmall->frameRender(getMemDC(),
			676, 95 + _vHero[i]->getMyNum()*54,
			_vHero[i]->getHeroInfo().indexX,
			_vHero[i]->getHeroInfo().indexY);						// 각 영웅의 초상화 그려줌

		IMAGEMANAGER->findImage("select_hero")->render(getMemDC(),		// 현재 선택된 영웅 표시
			675, 95 + _currentHero * 54);

		
		if (_vHero[i]->getMyNum() == _currentHero) //현재 선택된 영웅 그리는것
		{
			tagHero hero;
			hero = _vHero[i]->getHeroInfo();

			hero.portraitLarge->frameRender(getMemDC(), 83, 26,
				hero.indexX, hero.indexY);								//초상화 

			numberDraw(getMemDC(), hero.str, 113, 168);					// 힘민지지
			numberDraw(getMemDC(), hero.def, 183, 168);
			numberDraw(getMemDC(), hero.wiz, 253, 168);
			numberDraw(getMemDC(), hero.inte, 323, 168);

			numberDraw(getMemDC(), _vHero[i]->getExp(), 132, 262);
			numberDraw(getMemDC(), _vHero[i]->getMana(), 276, 262);
			numberDraw(getMemDC(), _vHero[i]->getMaxMana(), 314, 262);

			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 299, 260, "/", 1);
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			
			
			HFONT font = CreateFont(24, 0, 0, 0, 50, false, false, false,
				HANGUL_CHARSET, 0, 0, 0, 0, TEXT("돋움체"));
			HFONT oldfont = (HFONT)SelectObject(getMemDC(), font);
			SetTextColor(getMemDC(), RGB(248, 228, 144));
			SelectObject(getMemDC(), font);

			TextOut(getMemDC(), 254 - strlen(hero.name) / 2 * 16, 39, hero.name, strlen(hero.name));

			SetTextColor(getMemDC(), RGB(0, 0, 0));
			DeleteObject(font);
			SelectObject(getMemDC(), oldfont);
			
			font = CreateFont(15, 0, 0, 0, 50, false, false, false,
				HANGUL_CHARSET, 0, 0, 0, 0, TEXT("돋움체"));
			oldfont = (HFONT)SelectObject(getMemDC(), font);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			SelectObject(getMemDC(), font);
			
			char tmp[256];
			sprintf(tmp, "%d", hero.level);

			TextOut(getMemDC(), 215, 64, tmp, strlen(tmp));							// 레벨 수치

			TextOut(getMemDC(), 232, 64, "레벨", 4);									// '레벨'

			TextOut(getMemDC(), 266, 64, hero.jobName, strlen(hero.jobName));		// 직업 이름

			SetTextColor(getMemDC(), RGB(0, 0, 0));
			SelectObject(getMemDC(), oldfont);
			DeleteObject(font);


			//79 - 492  크리쳐 초상화 그려주기 quantity 37 - 53

			for (int j = 0; j < _vHero[i]->getCreature().size(); j++)
			{
				_vHero[i]->getCreature()[j].portrait->frameRender(getMemDC(),
					79 + _vHero[i]->getCreature()[j].position * 66, 492,
					_vHero[i]->getCreature()[j].tier,
					_vHero[i]->getCreature()[j].kind *2 +
					_vHero[i]->getCreature()[j].level);		// 초상화 그리고

				numberDraw(getMemDC(), _vHero[i]->getCreature()[j].quantity,	// 그게 몇마리인지
					126 + _vHero[i]->getCreature()[j].position * 66, 545);		
			}


		}


		if (_currentCreature != -1)
		{
			IMAGEMANAGER->findImage("select_creature")->render(getMemDC(), 78 + _currentCreature*66, 491);
		}


		
	}

	if (_creatureinfo)
	{
		IMAGEMANAGER->findImage("window_creatureinfo")->render(getMemDC(), 127, 72);
		IMAGEMANAGER->findImage("window_creatureinfo_shadow")->alphaRender(getMemDC(), 127, 72, 150);







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

void player::addHero(POINT point,tagHero heroInfo)
{
	hero* he;

	he = new hero;
	he->setPlayerAddressLink(this);
	he->setPlayMapAddressLink(_pm);
	he->init(point, heroInfo);
	he->setMynum(_vHero.size());
	_pm->setClosed(point.x, point.y, true);


	//=============== z order를 위한 ===================
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
	render.kind = 1;

	_zOrder->addRender(render);


	_vHero.push_back(he);

}

void player::inputCity(void)
{

	//
	// 아직 남겨뒀지만
	//
	// 폐기해야할 코드들.....
	//
	// 일단 쓰고있는곳은 다 없앰
	//
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//==================== C I T Y   S C E N E =====================
		//============== 캠프 뒤져!
		for (int i = 0; i < _gs->getvCamp().size(); i++)
		{

			//==========지금 보고 있는 성이 머야?
			if (_currentCamp == _gs->getvCamp()[i]->getNum())
			{
				//========= 다른 열려 있는 창 없지?
				if (!_gs->getvCamp()[i]->getWindow())
				{

					switch (_gs->getvCamp()[i]->getCityInfo().camp)
					{
					case CAMP_CASTLE:
						if (getMenuC())
						{
							//========== 창은 열렸고 내가 연창은 이거야!
							_gs->getvCamp()[i]->setWindow(true);
							_gs->getvCamp()[i]->setWindowNum(getPixelC());



						}

						break;
					case CAMP_DUNGEON:
						if (getMenuD())
						{
							//========== 창은 열렸고 내가 연창은 이거야!
							_gs->getvCamp()[i]->setWindow(true);
							_gs->getvCamp()[i]->setWindowNum(getPixelD());


						}

						break;
					}
					//==========자 어딜 눌렀니?

					//============= 성에서 나가자 ===========
					if (PtInRect(&RectMake(744, 544, 48, 30), _ptMouse))
					{
						_cityScene = false;
						setProperty(_gs->getvCamp()[i]->getProperty());
					}

				}
				//=============창이 열려 있어?
				else
				{
					switch (_gs->getvCamp()[i]->getCityInfo().camp)
					{
					case CAMP_CASTLE:
						switch (_gs->getvCamp()[i]->getWindowNum())
						{
							//=========== 홀을 눌렀을때
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

							//=========== 성채를 눌렀을때 
						case 1:

							//=========== 창 닫자
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
							//=========== 홀을 눌렀을때
						case 0:
							if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
							{
								_gs->getvCamp()[i]->setWindow(false);
							}
							break;

							//=========== 성채를 눌렀을때 
						case 1:




							//=========== 창 닫자
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

				}

				else  if (_mouseArr.x == _vHero[i]->getHeroDest().x &&
					_mouseArr.y == _vHero[i]->getHeroDest().y &&
					!_vHero[i]->getGoOn() && _currentHero == _vHero[i]->getMyNum() &&
					_vHero[i]->getPath().size() && !_pm->getClosed(_mouseArr.x, _mouseArr.y))
				{
					_vHero[i]->setGoOn(true);
					_vHero[i]->setInCamp(false);
					if (!_autoCamera) _autoCamera = true;
					_pm->setClosed(_vHero[i]->getHeroPoint().x, _vHero[i]->getHeroPoint().y, false);


				}

			}
		}
		if(_window)
		{

			if (!_creatureinfo)		// 크리쳐 정보창 안열려잇음
			{
				for (int i = 0; i < 7; i++) // 이제 눌러보자
				{
					
					for (int i = 0; i < _vHero[_currentHero]->getCreature().size(); i++) // 현재 영웅의 크리쳐 정보를 가져오고
					{
						// 79 492
						if (PtInRect(&RectMake(79 + 66 * i, 492, 58, 64), _ptMouse))	// 각 렉트 창을 눌럿을때
						{
							if (_currentCreature == -1)	// 지금 선택된게 없다면
							{
								


							}
							else
							{
								if (_currentCreature != i)
								{
									for (int j = 0; j < _vHero[_currentHero]->getCreature().size(); j++)
									{
										if (_vHero[_currentHero]->getCreature()[j].position == _currentCreature)
										{
											_vHero[_currentHero]->getCreature()[j].position = i;
										}


									}

								}
								else
								{
									_creatureinfo = true;
									_currentCreature = -1;

								}
							}

							
						}


					}
				}






				for (int i = 0; i < 8; i++)
				{
					if (PtInRect(&RectMake(675, 95 + 54 * i, 46, 30),_ptMouse))
					{
						if(i < _vHero.size())
						_currentHero = i;
					}
				}


				if (PtInRect(&RectMake(674, 523, 52, 36), _ptMouse))
				{
					_window = false;
				}

			}
			else
			{
				if (PtInRect(&RectMake(343, 309, 64, 30),_ptMouse))
				{
					_creatureinfo = false;
					_currentCreature = -1;
				}
			}

		}


	}
}
