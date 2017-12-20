#include "stdafx.h"
#include "player.h"
#include "playMap.h"


player::player() {}
player::~player() {}

HRESULT player::init(int myNum)
{
	_myNum = myNum;
	_myTurn = true;
	_readyMove = false;
	_cityScene = false;
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
		cityScene();
	}

	else
	{
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
	IMAGEMANAGER->findImage("city_UI")->render(getMemDC(), 0, 374);
	IMAGEMANAGER->findImage("mapToolUI")->render(getMemDC(), 800, 0);
	
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
		if ((*_viHero)->getGoOn())
		{
			float x;
			float y;
			x = ((*_viHero)->getHeroX() - 12*TILESIZE);
			y = ((*_viHero)->getHeroY() - 9*TILESIZE);
			
			_pm->setCameraX(x);
			_pm->setCameraY(y);
			
		}

		if ((*_viHero)->setMoveEnd())
		{
			float x;
			float y;
			x = ((*_viHero)->getHeroPoint().x - 12)*TILESIZE;
			y = ((*_viHero)->getHeroPoint().y - 9)*TILESIZE;

			_pm->setCameraX(x);
			_pm->setCameraY(y);

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

void player::inputGame(void)
{
	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_cityScene)
		{
			//====================  F I E L D   S C E N E =====================
			for (int i = 0; i < _vHero.size(); i++)
			{
				if (_vHero[i]->getMyNum() == _currentHero && !_vHero[i]->getGoOn()&&
					(_mouseArr.x != _destination.x || _mouseArr.y != _destination.y)&& !_readyMove)
				{
					_vHero[i]->setPath(_pm->getPath(
						_vHero[i]->getHeroPoint().x,
						_vHero[i]->getHeroPoint().y,
						_mouseArr.x, _mouseArr.y));
					_destination.x = _mouseArr.x;
					_destination.y = _mouseArr.y;
					//_readyMove = true;
				}

				else  if (_mouseArr.x == _destination.x &&
					_mouseArr.y == _destination.y && !_vHero[i]->getGoOn() &&
					_vHero[i]->getPath().size())
				{
					_vHero[i]->setGoOn(true);
				
				}

			}		

		}
		else
		{
			//==================== C I T Y   S C E N E ======================

		}


	}
}
