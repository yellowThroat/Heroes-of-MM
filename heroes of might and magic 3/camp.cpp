#include "stdafx.h"
#include "camp.h"

camp::camp() {}
camp::~camp() {}


HRESULT camp::init(building info)
{
	//================================================
	// �ǹ� ���ڰ� 0�̸� �������� ���� ����			//
	// hall �� 1���� ���� : ����ȸ��					//
	// 1 �̻��� �ǹ� ����								//
	// �÷��̾�� 0�̸� �� 1�̻� �ش� �÷��̾ �Ҽ�	//
	//================================================
	
	_buildingInfo = info;
	buildingInit();

	_fieldPoint.x = _buildingInfo.destX + _buildingInfo.enterX;
	_fieldPoint.y = _buildingInfo.destY + _buildingInfo.enterY;


	return S_OK;
}

void camp::release(void)
{

}

void camp::update(void)
{
	//=================== F U N C T I O N ===================
	buildingCondition();			// * �ʿ����?
	cameraSetting();				// �÷��� ī�޶� ���� �ǽð� �ޱ�
	setFrameCycle();
	
}

void camp::render(void)
{
	fieldDraw();
}

void camp::fieldDraw(void)
{
	IMAGEMANAGER->findImage("enter")->render(getMemDC(),
		_fieldPoint.x * TILESIZE - DATABASE->getPlayCameraX(),
		_fieldPoint.y * TILESIZE - DATABASE->getPlayCameraY());


	if (_buildingInfo.destX - _buildingInfo.imgX - _cameraArr.x >= -8 &&
		_buildingInfo.destX + _buildingInfo.sizeX / 2 - _cameraArr.x <= 32 &&
		_buildingInfo.destY - _buildingInfo.imgY - _cameraArr.y >= -6 &&
		_buildingInfo.destY - _buildingInfo.sizeY / 2 - _cameraArr.y <= 24)
	{
		if (_fort <= 2)
		{
			_fieldImg->frameRender(getMemDC(),
				(_buildingInfo.destX - _buildingInfo.imgX)*TILESIZE - DATABASE->getPlayCameraX(),
				(_buildingInfo.destY - _buildingInfo.imgY)*TILESIZE - DATABASE->getPlayCameraY(),
				_fort, 0);

			_fieldShadowImg->alphaFrameRender(getMemDC(),
				(_buildingInfo.destX - _buildingInfo.imgX)*TILESIZE - DATABASE->getPlayCameraX(),
				(_buildingInfo.destY - _buildingInfo.imgY)*TILESIZE - DATABASE->getPlayCameraY(),
				_fort, 0,190);

		}

		else
		{
			_fieldImg->frameRender(getMemDC(),
				(_buildingInfo.destX - _buildingInfo.imgX)*TILESIZE - DATABASE->getPlayCameraX(),
				(_buildingInfo.destY - _buildingInfo.imgY)*TILESIZE - DATABASE->getPlayCameraY(),
				2, 0);
			_fieldShadowImg->alphaFrameRender(getMemDC(),
				(_buildingInfo.destX - _buildingInfo.imgX)*TILESIZE - DATABASE->getPlayCameraX(),
				(_buildingInfo.destY - _buildingInfo.imgY)*TILESIZE - DATABASE->getPlayCameraY(),
				2, 0,190);

		}
	}
	


}

void camp::castleDraw(void)
{
	//============ Ư�� �ǹ� ��ȣ ==============
	// 0 : �׸��� ��ä
	// 1 : ������
	// 2 : ������
	// 3 : ���
	// 4 : �˻���ȸ


	IMAGEMANAGER->findImage("castle_back")->render(getMemDC());
	IMAGEMANAGER->findImage("castle_fort")->frameRender(getMemDC(),
		478, 37,_fort,0);
	IMAGEMANAGER->findImage("castle_barrack")->frameRender(getMemDC(),
		304, 65, _level[0], 0);
	IMAGEMANAGER->findImage("castle_archer")->frameRender(getMemDC(),
		360, 115, _level[1], 0);
	IMAGEMANAGER->findImage("castle_tower")->frameRender(getMemDC(),
		81, 44, _level[2], _special[0]);
	IMAGEMANAGER->findImage("castle_sword")->frameRender(getMemDC(),
		176, 85, _level[3], 0);
	IMAGEMANAGER->findImage("castle_abbey")->frameRender(getMemDC(),
		563, 173, _level[4], 0);
	IMAGEMANAGER->findImage("castle_ground")->frameRender(getMemDC(),
		160, 190, _level[5], 0);
	IMAGEMANAGER->findImage("castle_ground_ani")->frameRender(getMemDC(),
		160, 190,IMAGEMANAGER->findImage("castle_ground_ani")->getFrameX(), _level[5]);
	IMAGEMANAGER->findImage("castle_hall")->frameRender(getMemDC(),
		0, 154, _hall, 0);
	IMAGEMANAGER->findImage("castle_hall_ani")->frameRender(getMemDC(),
		0, 154, IMAGEMANAGER->findImage("castle_hall_ani")->getFrameX(), _hall);
	IMAGEMANAGER->findImage("castle_door")->frameRender(getMemDC(),
		302, 1, _level[6], 0);


}

void camp::dungeonDraw(void)
{
	IMAGEMANAGER->findImage("dungeon_back")->render(getMemDC());

}

void camp::setFrameCycle(void)
{
	frameCycle("castle_hall_ani", 12,true);
	frameCycle("castle_ground_ani", 12,true);
}

void camp::buildingInit()
{
	_cityScene = false;
	strcpy(_name, _buildingInfo.campInfo.name);
	_camp				= _buildingInfo.camp;
	_hall				= _buildingInfo.campInfo.hall;
	_fort				= _buildingInfo.campInfo.fort;
	_pub				= _buildingInfo.campInfo.pub;
	_guild				= _buildingInfo.campInfo.guild;
	_market				= _buildingInfo.campInfo.market;
	_forge				= _buildingInfo.campInfo.forge;
	_player				= _buildingInfo.campInfo.player;
	for (int i = 0; i < 7; i++)
	{
		_level[i]		= _buildingInfo.campInfo.level[i];
	}
	for (int i = 0; i < 5; i++)
	{
		_special[i]		= _buildingInfo.campInfo.special[i];
	}
	//================== �ʵ� �̹��� =====================

	switch (_camp)
	{
	case CAMP_CASTLE:
		_fieldImg = IMAGEMANAGER->findImage("building_castle");
		_fieldShadowImg = IMAGEMANAGER->findImage("building_castle_shadow");
		break;
	case CAMP_DUNGEON:
		_fieldImg = IMAGEMANAGER->findImage("building_dungeon");
		_fieldShadowImg = IMAGEMANAGER->findImage("building_dungeon_shadow");
		break;
	}

	_fieldRect = RectMake(_buildingInfo.destX, _buildingInfo.destY,
		_buildingInfo.sizeX, _buildingInfo.sizeY);

}

void camp::buildingCondition(void)
{
	if (_hall > 4) _hall = 4;
	if (_fort > 4) _fort = 4;
	if (_pub > 1) _pub = 1;
	if (_market > 1) _market = 1;
	if (_forge > 1) _forge = 1;
	for (int i = 0; i < 7; i++)
	{
		if (_level[i] > 2) _level[i] = 2;
	}
	for (int i = 0; i < 5; i++)
	{
		if (_special[i] > 1) _special[i] = 1;
	}

	switch (_camp)
	{
	case CAMP_CASTLE:
		if (_guild > 4) _guild = 4;
		
		break;
	case CAMP_DUNGEON:
		if (_guild > 5) _guild = 5;
		break;
	}
}

void camp::cameraSetting(void)
{
	_cameraX = DATABASE->getPlayCameraX();
	_cameraY = DATABASE->getPlayCameraY();

	_cameraArr.x = _cameraX / TILESIZE;
	_cameraArr.y = _cameraY / TILESIZE;

}