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
	for ( _viHero = _vHero.begin(); _viHero != _vHero.end(); ++_viHero)
	{
		(*_viHero)->update();
	}
	camera();
}

void player::render(void)
{
	for (_viHero = _vHero.begin(); _viHero != _vHero.end(); ++_viHero)
	{
		(*_viHero)->render();
	}


}

void player::camera(void)
{
	_mouseArr.x = (_ptMouse.x + DATABASE->getPlayCamera().x) / TILESIZE;
	_mouseArr.y = (_ptMouse.y + DATABASE->getPlayCamera().y) / TILESIZE;
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
				_mouseArr.y == _destination.y && !_vHero[i]->getGoOn())
			{
				_vHero[i]->setGoOn(true);
				//_readyMove = false;
			}

		}		
	}
}
