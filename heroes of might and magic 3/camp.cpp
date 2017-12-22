#include "stdafx.h"
#include "camp.h"

camp::camp() {}
camp::~camp() {}


HRESULT camp::init(building info)
{
	//================================================
	// 건물 숫자가 0이면 지어지지 않은 상태			//
	// hall 은 1부터 시작 : 마을회관					//
	// 1 이상은 건물 레벨								//
	// 플레이어는 0이면 빈성 1이상 해당 플레이어에 소속	//
	//================================================
	ZeroMemory(&_buildingInfo, sizeof(tagBuildingInfo));

	_buildingInfo = info;
	buildingInit();

	_fieldPoint.x = _buildingInfo.destX + _buildingInfo.enterX;
	_fieldPoint.y = _buildingInfo.destY + _buildingInfo.enterY;

	_showWindow = false;

	switch (_buildingInfo.camp)
	{
	case CAMP_CASTLE:
		
	break;
	
	case CAMP_DUNGEON:
		
	break;

	}



	return S_OK;
}

void camp::release(void)
{

}

void camp::update(void)
{
	//=================== F U N C T I O N ===================
	buildingCondition();			// * 필요없나?
	cameraSetting();				// 플레이 카메라 정보 실시간 받기
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
	
	IMAGEMANAGER->findImage("city_UI")->render(getMemDC(), 0, 374);
	IMAGEMANAGER->findImage("mapToolUI")->render(getMemDC(), 800, 0);


	//============ 특수 건물 번호 ==============
	// 0 : 그리핀 성채
	// 1 : 조선소
	// 2 : 마구간
	// 3 : 등대
	// 4 : 검사협회

	IMAGEMANAGER->findImage("castle_back")->render(getMemDC());
	IMAGEMANAGER->findImage("castle_waterfall")->frameRender(getMemDC(),
		46, 119);
	IMAGEMANAGER->findImage("castle_stable")->frameRender(getMemDC(),
		384, 193, _special[2],IMAGEMANAGER->findImage("castle_stable")->getFrameY());
	IMAGEMANAGER->findImage("castle_storage")->frameRender(getMemDC(),
		488, 228, _market, IMAGEMANAGER->findImage("castle_storage")->getFrameY());
	IMAGEMANAGER->findImage("castle_market")->frameRender(getMemDC(),
		413, 264, _market, IMAGEMANAGER->findImage("castle_market")->getFrameY());
	IMAGEMANAGER->findImage("castle_guild")->frameRender(getMemDC(),
		704, 76, _guild, IMAGEMANAGER->findImage("castle_guild")->getFrameY());
	IMAGEMANAGER->findImage("castle_guild_ani")->frameRender(getMemDC(),
		704, 76, IMAGEMANAGER->findImage("castle_guild_ani")->getFrameX(),_guild);
	IMAGEMANAGER->findImage("castle_fort")->frameRender(getMemDC(),
		478, 37, _fort, IMAGEMANAGER->findImage("castle_fort")->getFrameY());
	IMAGEMANAGER->findImage("castle_barrack")->frameRender(getMemDC(),
		304, 65, _level[0], IMAGEMANAGER->findImage("castle_barrack")->getFrameY());
	IMAGEMANAGER->findImage("castle_archer")->frameRender(getMemDC(),
		360, 115, _level[1], IMAGEMANAGER->findImage("castle_archer")->getFrameY());
	IMAGEMANAGER->findImage("castle_tower")->frameRender(getMemDC(),
		81, 44, _level[2], _special[0] + IMAGEMANAGER->findImage("castle_tower")->getFrameY()*2);
	IMAGEMANAGER->findImage("castle_sword")->frameRender(getMemDC(),
		176, 85, _level[3], IMAGEMANAGER->findImage("castle_sword")->getFrameY());
	IMAGEMANAGER->findImage("castle_abbey")->frameRender(getMemDC(),
		563, 173, _level[4], IMAGEMANAGER->findImage("castle_abbey")->getFrameY());
	IMAGEMANAGER->findImage("castle_ground")->frameRender(getMemDC(),
		160, 190, _level[5], IMAGEMANAGER->findImage("castle_ground")->getFrameY());
	IMAGEMANAGER->findImage("castle_ground_ani")->frameRender(getMemDC(),
		160, 190, IMAGEMANAGER->findImage("castle_ground_ani")->getFrameX(), _level[5]);
	IMAGEMANAGER->findImage("castle_hall")->frameRender(getMemDC(),
		0, 154, _hall, IMAGEMANAGER->findImage("castle_hall")->getFrameY());
	IMAGEMANAGER->findImage("castle_hall_ani")->frameRender(getMemDC(),
		0, 154, IMAGEMANAGER->findImage("castle_hall_ani")->getFrameX(), _hall);
	IMAGEMANAGER->findImage("castle_pub")->frameRender(getMemDC(),
		0, 198, _pub, IMAGEMANAGER->findImage("castle_pub")->getFrameY());
	IMAGEMANAGER->findImage("castle_forge")->frameRender(getMemDC(),
		231, 255, _forge, IMAGEMANAGER->findImage("castle_forge")->getFrameY());
	IMAGEMANAGER->findImage("castle_door")->frameRender(getMemDC(),
		302, 1, _level[6], IMAGEMANAGER->findImage("castle_door")->getFrameY());

	if (_showWindow)
	{
		switch (_windowNum)
		{
			//============== 홀
		case 0:
			break;
			//============== 성채
		case 1:


			break;
		case 8:
			for (int i = 0; i < 6; i++)
			{
				IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(),
					168 + 394 * (i % 2), 25 + 133 * (i / 2));
			}
			IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(),
				364, 424);
			IMAGEMANAGER->findImage("window_castle_fort")->render(getMemDC());


			break;


		}
	}

}

void camp::dungeonDraw(void)
{
	IMAGEMANAGER->findImage("city_UI")->render(getMemDC(), 0, 374);
	IMAGEMANAGER->findImage("mapToolUI")->render(getMemDC(), 800, 0);

	// 0 : 버섯 고리
	// 1 : 아카데미
	// 2 : 마나 구름
	// 3 : 아티팩트 상인
	// 4 : 포탈
	IMAGEMANAGER->findImage("dungeon_back")->render(getMemDC());

	IMAGEMANAGER->findImage("dungeon_temple")->frameRender(getMemDC(),
		300, 29, _level[3],IMAGEMANAGER->findImage("dungeon_temple")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_maze")->frameRender(getMemDC(),
		519, 172, _level[4],IMAGEMANAGER->findImage("dungeon_maze")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_manCave")->frameRender(getMemDC(),
		270, 253, _level[5], IMAGEMANAGER->findImage("dungeon_manCave")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_draCave")->frameRender(getMemDC(),
		550, 0, _level[6],IMAGEMANAGER->findImage("dungeon_draCave")->getFrameY());
	
	IMAGEMANAGER->findImage("dungeon_draCave_ani")->frameRender(getMemDC(),
		550, 0, IMAGEMANAGER->findImage("dungeon_draCave_ani")->getFrameX(), _level[6]);

	IMAGEMANAGER->findImage("dungeon_academy")->frameRender(getMemDC(),
		311, 298, _special[0], IMAGEMANAGER->findImage("dungeon_academy")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_guild")->frameRender(getMemDC(),
		164, 15, _guild, IMAGEMANAGER->findImage("dungeon_guild")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_forge")->frameRender(getMemDC(),
		546, 250, _forge, IMAGEMANAGER->findImage("dungeon_forge")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_market")->frameRender(getMemDC(),
		590, 318, _market, IMAGEMANAGER->findImage("dungeon_market")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_storage")->frameRender(getMemDC(),
		624, 335l, _market, IMAGEMANAGER->findImage("dungeon_storage")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_artifact")->frameRender(getMemDC(),
		745, 297, _special[3], IMAGEMANAGER->findImage("dungeon_artifact")->getFrameY());

	if(!_special[4]) IMAGEMANAGER->findImage("dungeon_portal")->frameRender(getMemDC(),
		687, 177);

	IMAGEMANAGER->findImage("dungeon_cloud")->frameRender(getMemDC(),
		131, 26, IMAGEMANAGER->findImage("dungeon_cloud")->getFrameX(),
		_guild/5 + IMAGEMANAGER->findImage("dungeon_cloud")->getFrameY() * 2);

	IMAGEMANAGER->findImage("dungeon_pub")->frameRender(getMemDC(),
		211, 297, _pub, IMAGEMANAGER->findImage("dungeon_pub")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_hall")->frameRender(getMemDC(),
		0, 203, _hall, IMAGEMANAGER->findImage("dungeon_hall")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_fort")->frameRender(getMemDC(),
		363, 87, _fort, IMAGEMANAGER->findImage("dungeon_fort")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_pillar")->frameRender(getMemDC(),
		121, 256, IMAGEMANAGER->findImage("dungeon_pillar")->getFrameX()
		,_level[2] + IMAGEMANAGER->findImage("dungeon_pillar")->getFrameY()*2);

	IMAGEMANAGER->findImage("dungeon_farm")->frameRender(getMemDC(),
		0, 300, IMAGEMANAGER->findImage("dungeon_farm")->getFrameX(),
		_level[0] + IMAGEMANAGER->findImage("dungeon_farm")->getFrameY() * 4);

	IMAGEMANAGER->findImage("dungeon_nest")->frameRender(getMemDC(),
		0, 26 , _level[1], IMAGEMANAGER->findImage("dungeon_nest")->getFrameY());


	if (_showWindow)
	{
		switch (_windowNum)
		{
			//============== 홀
		case 0:
			break;
			//============== 성채
		case 1:
			for (int i = 0; i < 6; i++)
			{
				IMAGEMANAGER->findImage("dungeon_fort_back")->render(getMemDC(),
					168 + 394*(i%2), 25 + 133*(i/2));
			}
			IMAGEMANAGER->findImage("dungeon_fort_back")->render(getMemDC(),
				364, 424);
			IMAGEMANAGER->findImage("window_dungeon_fort")->render(getMemDC());
			

			break;

		}
	}

	 


}

void camp::setFrameCycle(void)
{
	frameCycle("castle_hall_ani", 12,true);
	frameCycle("castle_ground_ani", 12,true);
	frameCycle("castle_waterfall", 8);
	frameCycle("castle_guild_ani", 8);


	frameCycle("dungeon_farm", 8);
	frameCycle("dungeon_cloud", 8);
	frameCycle("dungeon_pillar", 8);
	frameCycle("dungeon_draCave_ani", 8);
	frameCycle("dungeon_portal", 8);

}

void camp::selectBox(void)
{
	if (_buildingInfo.camp == CAMP_CASTLE)
	{
		if (getPixelC(0)) IMAGEMANAGER->findImage("castle_hall")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_hall")->				setFrameY(0);	

		if (getPixelC(1)) IMAGEMANAGER->findImage("castle_pub")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_pub")->				setFrameY(0);

		if (getPixelC(2)) IMAGEMANAGER->findImage("castle_barrack")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_barrack")->			setFrameY(0);

		if (getPixelC(3)) IMAGEMANAGER->findImage("castle_archer")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_archer")->				setFrameY(0);

		if (getPixelC(4)) IMAGEMANAGER->findImage("castle_sword")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_sword")->				setFrameY(0);

		if (getPixelC(5)) IMAGEMANAGER->findImage("castle_tower")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_tower")->				setFrameY(0);

		if (getPixelC(6)) IMAGEMANAGER->findImage("castle_ground")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_ground")->				setFrameY(0);

		if (getPixelC(7)) IMAGEMANAGER->findImage("castle_door")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_door")->				setFrameY(0);

		if (getPixelC(8)) IMAGEMANAGER->findImage("castle_fort")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_fort")->				setFrameY(0);

		if (getPixelC(9)) IMAGEMANAGER->findImage("castle_abbey")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_abbey")->				setFrameY(0);

		if (getPixelC(10)) IMAGEMANAGER->findImage("castle_forge")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_forge")->				setFrameY(0);

		if (getPixelC(11)) IMAGEMANAGER->findImage("castle_stable")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_stable")->				setFrameY(0);

		if (getPixelC(12)) IMAGEMANAGER->findImage("castle_guild")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_guild")->				setFrameY(0);

		if (getPixelC(13)) IMAGEMANAGER->findImage("castle_market")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_market")->				setFrameY(0);

		if (getPixelC(14)) IMAGEMANAGER->findImage("castle_storage")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_storage")->			setFrameY(0);

	}
	else if (_buildingInfo.camp == CAMP_DUNGEON)
	{
		if (getPixelD(0)) IMAGEMANAGER->findImage("dungeon_hall")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_hall")->setFrameY(0);

		if (getPixelD(1)) IMAGEMANAGER->findImage("dungeon_fort")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_fort")->setFrameY(0);

		if (getPixelD(2)) IMAGEMANAGER->findImage("dungeon_farm")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_farm")->setFrameY(0);

		if (getPixelD(3)) IMAGEMANAGER->findImage("dungeon_nest")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_nest")->setFrameY(0);

		if (getPixelD(4)) IMAGEMANAGER->findImage("dungeon_pillar")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_pillar")->setFrameY(0);

		if (getPixelD(5)) IMAGEMANAGER->findImage("dungeon_temple")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_temple")->setFrameY(0);

		if (getPixelD(6)) IMAGEMANAGER->findImage("dungeon_maze")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_maze")->setFrameY(0);

		if (getPixelD(7)) IMAGEMANAGER->findImage("dungeon_manCave")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_manCave")->setFrameY(0);

		if (getPixelD(8)) IMAGEMANAGER->findImage("dungeon_draCave")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_draCave")->setFrameY(0);

		if (getPixelD(9)) IMAGEMANAGER->findImage("dungeon_pub")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_pub")->setFrameY(0);

		if (getPixelD(10)) IMAGEMANAGER->findImage("dungeon_academy")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_academy")->setFrameY(0);

		if (getPixelD(11)) IMAGEMANAGER->findImage("dungeon_cloud")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_cloud")->setFrameY(0);

		if (getPixelD(12)) IMAGEMANAGER->findImage("dungeon_guild")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_guild")->setFrameY(0);

		if (getPixelD(13)) IMAGEMANAGER->findImage("dungeon_market")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_market")->setFrameY(0);

		if (getPixelD(14)) IMAGEMANAGER->findImage("dungeon_storage")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_storage")->setFrameY(0);

		if (getPixelD(15)) IMAGEMANAGER->findImage("dungeon_artifact")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_artifact")->setFrameY(0);

		if (getPixelD(16)) IMAGEMANAGER->findImage("dungeon_portal")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_portal")->setFrameY(0);

		if (getPixelD(17)) IMAGEMANAGER->findImage("dungeon_forge")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_forge")->setFrameY(0);

	}




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
	//================== 필드 이미지 =====================

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