#include "stdafx.h"
#include "hero.h"

hero::hero() {}
hero::~hero() {}

HRESULT hero::init(POINT point, tagHero hero)
{
	_pointArr = point;
	_myHero = hero;
	_x = _pointArr.x * TILESIZE;
	_y = _pointArr.y * TILESIZE;

	return S_OK;
}

void hero::release(void)
{

}

void hero::update(void)
{
	setAngle();
	setCordinate();

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD9))
	{
		//_myHero.angle +=0.1;
		frameCycle(_myHero.field, 6);

		if (_myHero.angle > PI2) _myHero.angle = 0;
		_x += 3;
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD7))
	{
		//_myHero.angle -= 0.1;
		frameCycle(_myHero.field, 8);
		if (_myHero.angle < 0) _myHero.angle = PI2;
		_x -= 3;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

	}

}

void hero::render(void)
{
	fieldDraw();
}

void hero::fieldDraw(void)
{
	//============= 필드 위 모습
	_myHero.field->frameRender(getMemDC(),
		_x - DATABASE->getPlayCamera().x,
		_y - DATABASE->getPlayCamera().y);
		

	//============= 필드 위 그림자
	_myHero.fieldShadow->alphaFrameRender(getMemDC(),
		_x - DATABASE->getPlayCamera().x,
		_y - DATABASE->getPlayCamera().y,SHADOWALPHA);

	//============= 필드 위 플래그
	_myHero.flag->frameRender(getMemDC(),
		_x - DATABASE->getPlayCamera().x,
		_y - DATABASE->getPlayCamera().y,
		_myHero.myNum, _myHero.field->getFrameY());

	/*
	//============= 필드 위 모습
	_myHero.field->frameRender(getMemDC(),
		_x - DATABASE->getPlayCamera().x,
		_y - DATABASE->getPlayCamera().y,
		_myHero.indexX, _myHero.field->getFrameY());
	*/

	
}

void hero::heroMove(void)
{
	if (_x != _destination.x * TILESIZE || _y != _destination.y * TILESIZE)
	{

	}
}

void hero::setCordinate(void)
{
	_pointArr.x = _x / TILESIZE;
	_pointArr.y = _y / TILESIZE;
}

void hero::setAngle(void)
{

	frameRotation(_myHero.field, 8, _myHero.angle, false, true);
}

