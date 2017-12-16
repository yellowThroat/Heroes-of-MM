#include "stdafx.h"
#include "ui.h"
#include "playMap.h"


ui::ui(){}
ui::~ui(){}

HRESULT ui::init(void)
{

	_miniMapMove = false;


	//================  R E C T   M A K E ===============
	_miniMapRect = RectMake(817, 24, 140, 144);

	return S_OK;
}

void ui::release(void)
{

}

void ui::update(void)
{

}

void ui::render(void)
{
	draw();
}

void ui::draw(void)
{
	IMAGEMANAGER->findImage("gameMiniview")->render(getMemDC(),
		_miniMapRect.left + _pm->getCameraArr().x * 2,
		_miniMapRect.top + _pm->getCameraArr().y * 2);

	IMAGEMANAGER->findImage("gameUI")->render(getMemDC());

}

void ui::input(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_miniMapRect, _ptMouse) || _miniMapMove)
		{
			_miniMapMove = true;
			POINT camera;
			camera.x = (_ptMouse.x - 12 * 2 - _miniMapRect.left) / 2 * TILESIZE;
			camera.y = (_ptMouse.y - 9 * 2 - _miniMapRect.top) / 2 * TILESIZE;

			if (camera.x <= -8 * TILESIZE) camera.x = -8 * TILESIZE;
			if (camera.y <= -6 * TILESIZE) camera.y = -6 * TILESIZE;
			if (camera.x >= 56 * TILESIZE) camera.x = 56 * TILESIZE;
			if (camera.y >= 60 * TILESIZE) camera.y = 60 * TILESIZE;

			_pm->setCamera(camera);

		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_miniMapMove = false;
	}
}