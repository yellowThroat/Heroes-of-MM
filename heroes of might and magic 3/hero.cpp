#include "stdafx.h"
#include "hero.h"
#include "player.h"


hero::hero() {}
hero::~hero() {}

HRESULT hero::init(POINT point, tagHero hero)
{
	_pointArr = point;
	_myHero = hero;
	_x = _pointArr.x * TILESIZE;
	_y = _pointArr.y * TILESIZE;
	_myTurn = false;
	_goOn = false;

	return S_OK;
}

void hero::release(void)
{

}

void hero::update(void)
{
	setAngle();
	setCordinate();
	heroMove();
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD9))
	{
		//_myHero.angle +=0.1;
		frameCycle(_myHero.field, 4);

		if (_myHero.angle > PI2) _myHero.angle = 0;
		_x += 3;
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD7))
	{
		//_myHero.angle -= 0.1;
		frameCycle(_myHero.field, 4);
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
	pathDraw();

}

void hero::pathDraw(void)
{
	
	for (int i = 0; i < _vPath.size(); i++)
	{
		Rectangle(getMemDC(),
			_vPath[i].x * TILESIZE - DATABASE->getPlayCamera().x + 8,
			_vPath[i].y * TILESIZE - DATABASE->getPlayCamera().y + 8,
			_vPath[i].x * TILESIZE - DATABASE->getPlayCamera().x + 24,
			_vPath[i].y * TILESIZE - DATABASE->getPlayCamera().y + 24);
	}
	
	
	//============== 중간점
	for (int i = 0; i < _vDraw.size(); i++)
	{

		if (_vDraw.size() > 1 && i != _vDraw.size() - 1 && i != 0)
			IMAGEMANAGER->findImage("path")->frameRender(getMemDC(),
				(_vDraw[i].point.x )*TILESIZE - DATABASE->getPlayCamera().x,
				(_vDraw[i].point.y )*TILESIZE - DATABASE->getPlayCamera().y,
				_vDraw[i].indexX, _vDraw[i].indexY);
	}

	
	//============== 도착점
	if (_vPath.size() >= 1) IMAGEMANAGER->findImage("path")->frameRender(getMemDC(),
		_vPath[_vPath.size() - 1].x *TILESIZE - DATABASE->getPlayCamera().x, 
		_vPath[_vPath.size() - 1].y *TILESIZE - DATABASE->getPlayCamera().y,0,0);


}

void hero::fieldDraw(void)
{
	//============= 필드 위 모습
	_myHero.field->frameRender(getMemDC(),
		(_x - 32)  - DATABASE->getPlayCamera().x,
		(_y - 32)  - DATABASE->getPlayCamera().y);
		

	//============= 필드 위 그림자
	_myHero.fieldShadow->alphaFrameRender(getMemDC(),
		(_x - 32)  - DATABASE->getPlayCamera().x,
		(_y - 32)  - DATABASE->getPlayCamera().y,SHADOWALPHA);

	//============= 필드 위 플래그
	_myHero.flag->frameRender(getMemDC(),
		(_x - 32)  - DATABASE->getPlayCamera().x,
		(_y - 32)  - DATABASE->getPlayCamera().y,
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
	if (_goOn)
	{
		frameCycle(_myHero.field, 5);
		frameCycle(_myHero.fieldShadow, 5);
		frameRotation(_myHero.field, 8, _myHero.angle, false, true);
		frameRotation(_myHero.fieldShadow, 8, _myHero.angle, false, true);
		frameRotation(_myHero.flag, 8, _myHero.angle, false, true);
	

		_myHero.angle = atan2f(_vPath[0].y*TILESIZE +16 - (_y+16),
			_vPath[0].x*TILESIZE + 16 - (_x+16));

		

		if (checkPointInRect(RectMakeCenter(
			TILESIZE*_vPath[0].x +16, TILESIZE*_vPath[0].y+16, 16, 16), _x + 16, _y+16))
		{
			_x = _vPath[0].x * TILESIZE;
			_y = _vPath[0].y * TILESIZE;
			_vPath.erase(_vPath.begin());
			if (!_vPath.size()) _goOn = false;

		}
		else
		{
			_x += DATABASE->getMoveSpeed()*cosf(_myHero.angle);
			_y += DATABASE->getMoveSpeed()*sinf(_myHero.angle);
		}
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

void hero::setPath(vPath path)
{
	 _vPath = path; 
	 _vPath.erase(_vPath.begin()); 
	 _vDraw.clear();

	 for (int i = 0; i < _vPath.size()-2; i++)
	 {
		 if (i == 0) continue;
		 
		 tagPathDraw p;
		 ZeroMemory(&p, sizeof(tagPathDraw));
		 p.point.x  = _vPath[i].x;
		 p.point.y = _vPath[i].y;

		 int previous = 0;
		 int next =0;
		
		 int tmp0, tmp1;
		 tmp0 = _vPath[i].x - _vPath[i-1].x;
		 tmp1 = _vPath[i].y - _vPath[i-1].y;

		 switch (tmp0)
		 {
		 case -1:
			 switch (tmp1)
			 {
			 case -1: previous = 1;
				 break;
			 case 0: previous = 2;
				 break;
			 case 1: previous = 3;
				 break;
			 }
			 break;
		 case 0:
			 switch (tmp1)
			 {
			 case -1: previous = 4;
				 break;
			 case 0:
				 break;
			 case 1:previous = 5;
				 break;
			 }
			 break;
		 case 1:
			 switch (tmp1)
			 {
			 case -1:previous = 6;
				 break;
			 case 0:previous = 7;
				 break;
			 case 1:previous = 8;
				 break;
			 }
			 break;
		 }
	
		 tmp0 = _vPath[i+1].x - _vPath[i].x;
		 tmp1 = _vPath[i+1].y - _vPath[i].y;

		 switch (tmp0)
		 {
		 case -1:
			 switch (tmp1)
			 {
			 case -1: previous = 1;
				 break;
			 case 0: previous = 2;
				 break;
			 case 1: previous = 3;
				 break;
			 }
			 break;
		 case 0:
			 switch (tmp1)
			 {
			 case -1: previous = 4;
				 break;
			 case 0:
				 break;
			 case 1:previous = 5;
				 break;
			 }
			 break;
		 case 1:
			 switch (tmp1)
			 {
			 case -1:previous = 6;
				 break;
			 case 0:previous = 7;
				 break;
			 case 1:previous = 8;
				 break;
			 }
			 break;
		 }


		 if (previous == 1)
		 {
			 p.indexY = 7;
			 if (next == 8) p.indexX = 0;
			 if (next == 5) p.indexX = 1;
			 if (next == 7) p.indexX = 2;
		 }
		 if (previous == 2)
		 {
			 p.indexY = 1;
			 if (next == 7) p.indexX = 0;
			 if (next == 6) p.indexX = 1;
			 if (next == 8) p.indexX = 2;
		 }
		 if (previous == 3)
		 {
			 p.indexY = 5;
			 if (next == 6) p.indexX = 0;
			 if (next == 4) p.indexX = 1;
			 if (next == 7) p.indexX = 2;
		 }
		 if (previous == 4)
		 {
			 p.indexY = 4;
			 if (next == 5) p.indexX = 0;
			 if (next == 8) p.indexX = 1;
			 if (next == 3) p.indexX = 2;
		 }
		 if (previous == 5)
		 {
			 p.indexY = 3;
			 if (next == 4) p.indexX = 0;
			 if (next == 6) p.indexX = 1;
			 if (next == 1) p.indexX = 2;
		 }
		 if (previous == 6)
		 {
			 p.indexY = 8;
			 if (next == 3) p.indexX =0 ;
			 if (next == 5) p.indexX =1 ;
			 if (next == 2) p.indexX =2 ;
		 }
		 if (previous == 7)
		 {
			 p.indexY = 2;
			 if (next == 2) p.indexX =0 ;
			 if (next == 1) p.indexX =1 ;
			 if (next == 3) p.indexX = 2;

		 }
		 if (previous == 8)
		 {
			 p.indexY = 6;
			 if (next == 1) p.indexX =0 ;
			 if (next == 4) p.indexX =1 ;
			 if (next == 2) p.indexX =2 ;

		 }

		 _vDraw.insert(_vDraw.begin(), p);





	 }

	 


}