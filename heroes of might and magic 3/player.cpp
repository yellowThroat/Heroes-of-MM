#include "stdafx.h"
#include "player.h"

player::player() {}
player::~player() {}

HRESULT player::init(int myNum)
{
	_myNum = myNum;
	_myTurn = false;

	tagHero tmp;
	tmp.field = IMAGEMANAGER->findImage("hero_castle");
	tmp.fieldShadow = IMAGEMANAGER->findImage("hero_castle_shadow");
	tmp.flag = IMAGEMANAGER->findImage("hero_flag");
	tmp.indexX = 0;
	tmp.indexY = 0;
	tmp.myNum = 0;
	tmp.angle = 0;
	addHero(PointMake(10,10),tmp);


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
}

void player::render(void)
{
	for (_viHero = _vHero.begin(); _viHero != _vHero.end(); ++_viHero)
	{
		(*_viHero)->render();
	}


}

void player::addHero(POINT point,tagHero heroInfo)
{
	hero* he;
	he = new hero;
	he->init(point, heroInfo);

	_vHero.push_back(he);

}
