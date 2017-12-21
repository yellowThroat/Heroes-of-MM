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
	_readyMove = false;
	_cityScene = false;
	_autoCamera = false;
	_currentHero = 0;
	_destination = { 0,0 };
	tagHero tmp;
	tmp.field = IMAGEMANAGER->findImage("hero_castle");
	tmp.fieldShadow = IMAGEMANAGER->findImage("hero_castle_shadow");
	tmp.flag = IMAGEMANAGER->findImage("hero_flag");
	tmp.indexX = 0;
	tmp.indexY = 0;
	tmp.myNum = 0;
	tmp.angle = 0;
	addHero(PointMake(5,5),tmp);


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
	he->init(point, heroInfo);
	he->setMynum(_vHero.size());
	

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

					//==========자 어딜 눌렀니?
					if (getPixelD(1))
					{
						//========== 창은 열렸고 내가 연창은 이거야!
						_gs->getvCamp()[i]->setWindow(true);
						_gs->getvCamp()[i]->setWindowNum(1);
					}

					//============= 성에서 나가자 ===========
					if (PtInRect(&RectMake(744, 544, 48, 30), _ptMouse))
					{
						_cityScene = false;
					}

				}
				//=============창이 열려 있어?
				else
				{
					switch (_gs->getvCamp()[i]->getWindowNum())
					{
						//=========== 홀을 눌렀을때
					case 0:
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
				(_mouseArr.x != _destination.x || _mouseArr.y != _destination.y)&& !_readyMove)
			{
				_vHero[i]->setPath(_pm->getPath(_vHero[i]->getHeroPoint().x,
					_vHero[i]->getHeroPoint().y,
					_mouseArr.x, _mouseArr.y));
				if (_vHero[i]->getPath().size())
				{
					_destination.x = _vHero[i]->getPath()[_vHero[i]->getPath().size() - 1].x;
					_destination.y = _vHero[i]->getPath()[_vHero[i]->getPath().size() - 1].y;

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

				//_readyMove = true;
			}

			else  if (_mouseArr.x == _destination.x &&
				_mouseArr.y == _destination.y && !_vHero[i]->getGoOn() &&
				_vHero[i]->getPath().size())
			{
				_vHero[i]->setGoOn(true);
				_vHero[i]->setInCamp(false);
				if (!_autoCamera) _autoCamera = true;
			
			}

		}		

		


	}
}
