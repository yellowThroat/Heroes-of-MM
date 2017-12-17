#include "stdafx.h"
#include "playMap.h"

playMap::playMap() {}
playMap::~playMap() {}

HRESULT playMap::init()
{
	
	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			ZeroMemory(&_map[i][j], sizeof(tagTileInfo));
			_map[i][j].destX = i;
			_map[i][j].destY = j;
			_map[i][j].img = IMAGEMANAGER->findImage("terrain_green");
			_map[i][j].sourX = 0;
		}
	}

	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			ZeroMemory(&_road[i][j], sizeof(tagRoadInfo));
			_road[i][j].road = ROAD_END;
			_road[i][j].img = NULL;
			_road[i][j].destX = i;
			_road[i][j].destY = j;
		}
	}
	
	loadFileList();
	loadMap(DATABASE->getSaveNum());

	_camera.x = 0;
	_camera.y = 0;

	_cameraArr.x = 0;
	_cameraArr.y = 0;

	_buildAttribute = false;


	return S_OK;
}

void playMap::release(void)
{

}

void playMap::update(void)
{
	sort(_vBuild.begin(), _vBuild.end());

	//============== F U N C T I O N ===============
	cameraMove();
	inputCommon();
}

void playMap::render(void)
{


	tileDraw();

	roadDraw();

	obstacleDraw();

	attributeDraw();

}

void playMap::tileDraw(void)
{
	IMAGEMANAGER->findImage("game_background")->loopRender(getMemDC(),
		&RectMake(0, 0, 788, 600), _camera.x, _camera.y);
	IMAGEMANAGER->findImage("edge_left")->render(getMemDC(),
		-32 - _camera.x, -32 - _camera.y);
	IMAGEMANAGER->findImage("edge_right")->render(getMemDC(),
		2304 - _camera.x, -32 - _camera.y);
	IMAGEMANAGER->findImage("edge_top")->render(getMemDC(),
		-32 - _camera.x, -32 - _camera.y);
	IMAGEMANAGER->findImage("edge_bottom")->render(getMemDC(),
		-32 - _camera.x, 2304 - _camera.y);

	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			if(i - _cameraArr.x >= MINCAMERA && i - _cameraArr.x < MAXCAMERAX &&
				j - _cameraArr.y >=MINCAMERA && j - _cameraArr.y < MAXCAMERAY)
			_map[i][j].img->frameRender(getMemDC(),
				(_map[i][j].destX - _cameraArr.x) * TILESIZE,
				(_map[i][j].destY- _cameraArr.y) * TILESIZE,
				_map[i][j].sourX, _map[i][j].sourY);
		}
	}
	

}

void playMap::roadDraw(void)
{
	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			if (i - _cameraArr.x >= MINCAMERA && i - _cameraArr.x < MAXCAMERAX &&
				j - _cameraArr.y >= MINCAMERA && j - _cameraArr.y < MAXCAMERAY)
			{
				if(_road[i][j].img != NULL)
				_road[i][j].img->frameRender(getMemDC(),
					(_road[i][j].destX - _cameraArr.x) * TILESIZE,
					(_road[i][j].destY - _cameraArr.y) * TILESIZE,
					_road[i][j].sourX, _road[i][j].sourY);

			}

		}
	}
}

void playMap::obstacleDraw(void)
{
	for (_viBuild = _vBuild.begin(); _viBuild != _vBuild.end(); ++_viBuild)
	{
		if (_viBuild->destX - _cameraArr.x > MINCAMERA && _viBuild->destX - _cameraArr.x < MAXCAMERAX &&
			_viBuild->destY - _cameraArr.y > MINCAMERA && _viBuild->destY - _cameraArr.y < MAXCAMERAY)
		{
			_viBuild->img->frameRender(getMemDC(),
				(_viBuild->destX - _viBuild->imgX) * TILESIZE - _camera.x,
				(_viBuild->destY - _viBuild->imgY) * TILESIZE - _camera.y,
				_viBuild->sourX, _viBuild->sourY);

			if (_viBuild->imgShadow != NULL)
				_viBuild->imgShadow->alphaFrameRender(getMemDC(),
					(_viBuild->destX - _viBuild->imgX) * TILESIZE - _camera.x,
					(_viBuild->destY - _viBuild->imgY) * TILESIZE - _camera.y,
					_viBuild->sourX, _viBuild->sourY, SHADOWALPHA);

		}

	}
}

void playMap::attributeDraw(void)
{
	if (_buildAttribute)
	{
		for (int i = 0; i < MAXTILE; i++)
		{
			for (int j = 0; j < MAXTILE; j++)
			{
				if (i - _cameraArr.x >= 0 && i - _cameraArr.x < 24 &&
					j - _cameraArr.y >= 0 && j - _cameraArr.y < 18)
				{
					if (_map[i][j].isClosed)
						IMAGEMANAGER->findImage("closed")->render(getMemDC(),
							i*TILESIZE - _camera.x, j*TILESIZE - _camera.y);
					if (_map[i][j].entrance)
						IMAGEMANAGER->findImage("enter")->render(getMemDC(),
							i*TILESIZE - _camera.x, j*TILESIZE - _camera.y);

				}

			}
		}
		for (int i = 0; i < 24; i++)
		{
			MoveToEx(getMemDC(), (i + 1)*TILESIZE, 0, NULL);
			LineTo(getMemDC(),(i + 1)*TILESIZE, WINSIZEY);
		}
		for (int i = 0; i < 18; i++)
		{
			MoveToEx(getMemDC(), 0,(i + 1)*TILESIZE, NULL);
			LineTo(getMemDC(), 788,(i + 1)*TILESIZE);
		}

	}

}

void playMap::cameraMove(void)
{
	_cameraArr.x = _camera.x / TILESIZE;
	_cameraArr.y = _camera.y / TILESIZE;

	DATABASE->setPlayCamera(_camera);


}

void playMap::loadFileList(void)
{

	HANDLE file;
	DWORD read;

	file = CreateFile("map/saveFileList.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _saveFile, sizeof(SAVE)*MAXSAVE, &read, NULL);

	CloseHandle(file);

}

void playMap::inputCommon(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_cameraArr.x > -12) _camera.x -= TILESIZE;		
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_cameraArr.x < 59) _camera.x += TILESIZE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_cameraArr.y < 62) _camera.y += TILESIZE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_cameraArr.y > -9) _camera.y -= TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		switch (_buildAttribute)
		{
		case TRUE: _buildAttribute = false;
			break;
		case FALSE: _buildAttribute = true;
			break;
		}
	}

}

void playMap::loadMap(int saveNum)
{
	HANDLE file;
	DWORD read;

	/*
	string tmp = TEXT("map/");
	string tmp1 = _saveFile[saveNum].fileName;

	
	for (int i = 0; i < tmp1.size(); i++)
	{
		tmp.push_back(tmp1.at(i));
	}

	tmp.push_back('.');
	tmp.push_back('m');
	tmp.push_back('a');
	tmp.push_back('p');
	*/

	file = CreateFile(DATABASE->getSaveName().c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _mapSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);
	ReadFile(file, _roadSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);
	ReadFile(file, _buildSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);
	ReadFile(file, _vBuildSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);

	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			//===================== load terrain =================
			switch (_mapSaveInfo[i][j].type)
			{
			case TILE_GREEN:
				_map[i][j].img = IMAGEMANAGER->findImage("terrain_green");
				_map[i][j].tile = TILE_GREEN;

				break;

			case TILE_WATER:
				_map[i][j].img = IMAGEMANAGER->findImage("terrain_water");
				_map[i][j].tile = TILE_WATER;
				break;

			case TILE_VOLCANO:
				_map[i][j].img = IMAGEMANAGER->findImage("terrain_volcano");
				_map[i][j].tile = TILE_VOLCANO;
				break;
			}
			_map[i][j].miniX = _mapSaveInfo[i][j].miniX;
			_map[i][j].miniY = _mapSaveInfo[i][j].miniY;
			_map[i][j].sourX = _mapSaveInfo[i][j].sourX;
			_map[i][j].sourY = _mapSaveInfo[i][j].sourY;


			//====================== load road ========================
			switch (_roadSaveInfo[i][j].type)
			{
			case 1:
				_road[i][j].img = IMAGEMANAGER->findImage("road_normal");
				_road[i][j].road = ROAD_NORMAL;
				break;
			case 2:
				_road[i][j].img = IMAGEMANAGER->findImage("road_rock");
				_road[i][j].road = ROAD_ROCK;

				break;
			case 3:
				_road[i][j].img = IMAGEMANAGER->findImage("road_river");
				_road[i][j].road = ROAD_RIVER;

				break;
			}
			_road[i][j].sourX = _roadSaveInfo[i][j].sourX;
			_road[i][j].sourY = _roadSaveInfo[i][j].sourY;

			//====================== load build ========================
			_map[i][j].isClosed = _buildSaveInfo[i][j].closed;
			_map[i][j].entrance = _buildSaveInfo[i][j].enter;

			if (_vBuildSaveInfo[i][j].type >= 2000)
			{
				building build;
				ZeroMemory(&build, sizeof(building));
				build.camp = CAMP_NULL;
				build.mine = MINE_NULL;
				build.ev = EV_NULL;
				build.destX = i;
				build.destY = j;
				build.sourX = _vBuildSaveInfo[i][j].sourX;
				build.sourY = _vBuildSaveInfo[i][j].sourY;
				build.sizeX = _vBuildSaveInfo[i][j].sizeX;
				build.sizeY = _vBuildSaveInfo[i][j].sizeY;
				build.miniX = _vBuildSaveInfo[i][j].miniX;
				build.imgX = _vBuildSaveInfo[i][j].imgX;
				build.imgY = _vBuildSaveInfo[i][j].imgY;

				switch (_vBuildSaveInfo[i][j].type % 10)
				{
				case 1:
					build.img = IMAGEMANAGER->findImage("obstacle_1x1");
					build.imgShadow = IMAGEMANAGER->findImage("obstacle_1x1_shadow");
					break;

				case 2:
					build.img = IMAGEMANAGER->findImage("obstacle_2x2");
					build.imgShadow = IMAGEMANAGER->findImage("obstacle_2x2_shadow");
					break;

				case 3:
					build.img = IMAGEMANAGER->findImage("obstacle_4x4");
					build.imgShadow = IMAGEMANAGER->findImage("obstacle_4x4_shadow");
					break;

				case 4:
					build.img = IMAGEMANAGER->findImage("obstacle_6x4");
					build.imgShadow = IMAGEMANAGER->findImage("obstacle_6x4_shadow");
					break;

				}
				_vBuild.push_back(build);
			}

		}
	}



	CloseHandle(file);
}