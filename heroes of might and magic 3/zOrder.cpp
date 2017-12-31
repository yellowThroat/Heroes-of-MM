#include "stdafx.h"
#include "zOrder.h"
#include "player.h"

zOrder::zOrder() {}
zOrder::~zOrder() {}

HRESULT zOrder::init(void)
{

	return S_OK;
}

void zOrder::release(void)
{

}

void zOrder::update(void)
{
	for (int j = 0; j < _player->getHero().size(); j++)
	{ 
		if(_player->getHero()[j]->getGoOn() )
		for (int i = 0; i < _vRender.size(); i++)
		{
			if (_vRender[i].kind)
			{
				if (_vRender[i].identity == _player->getHero()[j]->getMyNum())
				{
					_vRender[i].destX = _player->getHero()[j]->getHeroX() - 32;
					_vRender[i].destY = _player->getHero()[j]->getHeroY() - 32;
					_vRender[i].sourX = _player->getHero()[j]->getHeroInfo().field->getFrameX();
					_vRender[i].sourY = _player->getHero()[j]->getHeroInfo().field->getFrameY();

					break;
				}
			}
		}
	}
	//
	sort(_vRender.begin(), _vRender.end());

}

void zOrder::render(void)
{

	for (int i = 0; i < _vRender.size(); i++)
	{
		if (_vRender[i].destX - DATABASE->getPlayCameraX() >= MINCAMERA	 * TILESIZE &&
			_vRender[i].destX - DATABASE->getPlayCameraX() <= MAXCAMERAX * TILESIZE &&
			_vRender[i].destY - DATABASE->getPlayCameraY() >= MINCAMERA	 * TILESIZE	&&
			_vRender[i].destY - DATABASE->getPlayCameraY() <= MAXCAMERAY * TILESIZE)
		{
			if (_vRender[i].identity == 255)
			{
				_vRender[i].img->frameRender(getMemDC(),
					_vRender[i].destX- DATABASE->getPlayCameraX(),
					_vRender[i].destY- DATABASE->getPlayCameraY(),
					_vRender[i].sourX, 
					_vRender[i].sourY);

				if(_vRender[i].shadowImg!=NULL)
					_vRender[i].shadowImg->alphaFrameRender(getMemDC(),
						_vRender[i].destX - DATABASE->getPlayCameraX(),
						_vRender[i].destY - DATABASE->getPlayCameraY(),
						_vRender[i].sourX,
						_vRender[i].sourY, SHADOWALPHA);

			}
			else
			{
				_vRender[i].img->frameRender(getMemDC(),
					_vRender[i].destX - DATABASE->getPlayCameraX(),
					_vRender[i].destY - DATABASE->getPlayCameraY());

				if (_vRender[i].shadowImg != NULL)
					_vRender[i].shadowImg->alphaFrameRender(getMemDC(),
						_vRender[i].destX - DATABASE->getPlayCameraX(),
						_vRender[i].destY - DATABASE->getPlayCameraY(), SHADOWALPHA);

				if (_vRender[i].flag != NULL)
					_vRender[i].flag->frameRender(getMemDC(),
						_vRender[i].destX - DATABASE->getPlayCameraX(),
						_vRender[i].destY - DATABASE->getPlayCameraY(),
						0,
						_vRender[i].sourY);

			}

		}



	}
}

void zOrder::addRender(tagRender render)
{

	_vRender.push_back(render);
}