#include "stdafx.h"
#include "player.h"
#include "playMap.h"
#include "gameScene.h"



player::player() {}
player::~player() {}

HRESULT player::init(int myNum)
{
	_myNum = myNum;
	_myTurn = true;
	_cityScene = false;
	_autoCamera = false;
	_currentHero = 0;
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
	addHero(PointMake(8, 8), CommonHero(NAME_TIRIS));
	addHero(PointMake(10, 10), CommonHero(NAME_DAMACON));
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
				DATABASE->setPlayCameraX(x);
				DATABASE->setPlayCameraY(y);
				
		
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

	_vHero.push_back(he);

}

void player::inputCity(void)
{
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
		for (int i = 0; i < _vHero.size(); i++)
		{
			if (_vHero[i]->getMyNum() == _currentHero && !_vHero[i]->getGoOn()&&
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
				else if(_vHero[i]->getPath().size() >=20 && _vHero[i]->getPath().size() <40)
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
				_vHero[i]->getPath().size() && !_pm->getClosed(_mouseArr.x,_mouseArr.y))
			{
				_vHero[i]->setGoOn(true);
				_vHero[i]->setInCamp(false);
				if (!_autoCamera) _autoCamera = true;
				_pm->setClosed(_vHero[i]->getHeroPoint().x, _vHero[i]->getHeroPoint().y, false);

			
			}

		}		

		


	}
}
