#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool(){}
mapTool::~mapTool(){}

HRESULT mapTool::init(void)
{


	//====================== A L L O C A T I O N ================


	//======================  F U N C T I O N =================
	loadImg();

	//============================================================
	for (int i = 0; i < MAXTILE; i++)
	{
		_corX[i] = RectMake(20 + i*TILESIZE, 0, TILESIZE, 20);
		_corY[i] = RectMake(0, 20 + i*TILESIZE, 20, TILESIZE);

		
	}

	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			ZeroMemory(&_mapArr[i][j], sizeof(tagTileInfo));
			_mapArr[i][j].tile = TILE_WATER;
			_mapArr[i][j].miniX = 1;
			_mapArr[i][j].miniY = 0;
			_mapArr[i][j].destX = i;
			_mapArr[i][j].destY = j;
			_mapArr[i][j].sourX = 0;
			_mapArr[i][j].sourY = 0;
			_mapArr[i][j].img = IMAGEMANAGER->findImage("terrain_water");
			_mapArr[i][j].miniImg = IMAGEMANAGER->findImage("miniTerrain72");
			_mapArr[i][j].isChanged = false;
		}
	}

	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			ZeroMemory(&_roadArr[i][j], sizeof(tagRoadInfo));
			_roadArr[i][j].road = ROAD_END;
			_roadArr[i][j].destX = i;
			_roadArr[i][j].destY = j;
			_roadArr[i][j].sourX = 0;
			_roadArr[i][j].sourY = 0;
			_roadArr[i][j].isChanged = false;
		}
	}

	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			ZeroMemory(&_buildArr[i][j], sizeof(tagBuildingInfo));

			_buildArr[i][j].camp = CAMP_NULL;
			_buildArr[i][j].mine = MINE_NULL;
			_buildArr[i][j].ev = EV_NULL;
			_buildArr[i][j].destX = i;
			_buildArr[i][j].destY = j;
			_buildArr[i][j].miniX = 0;
			_buildArr[i][j].sourX = 0;
			_buildArr[i][j].sourY = 0;
			_buildArr[i][j].sizeX = 0;
			_buildArr[i][j].sizeY = 0;
		}
	}

	ZeroMemory(&_remember, sizeof(tagRemember));
	_remember.camp = CAMP_NULL;
	_remember.mine = MINE_NULL;
	_remember.ev = EV_NULL;


	_categoryLarge = CATE_NULL;
	_categorySmall = SMC_NULL;
	_mapX = _mapY = 0;
	_inputDelayX = _inputDelayY = 0;
	_mouseArr.x = ((_ptMouse.x - 20) / TILESIZE) + (int)_mapX / TILESIZE;
	_mouseArr.y = ((_ptMouse.y - 20) / TILESIZE) + (int)_mapY / TILESIZE;
	_saveX = _saveY = 0;
	_saveAreaX = _saveAreaY = 0;
	_brushNum = 0;
	_page = 0;
	_boxLength = 128;
	_area = false;
	_foldMini= false;
	_move = false;
	_buildAttribute = false;

	//============== R E C T   M A K E =====================
	_miniMap = RectMake(836, WINSIZEY - 226, 216, 216);
	_miniView = RectMake(_miniMap.left, _miniMap.top, 72, 54);
	_largeCategory = RectMake(808, 108, 242, 32);
	_smallCategory = RectMake(808, 150, 242, 32);
	_contents = RectMake(830, 192, 256, 288);

	//=============  S E T T I N G ====================
	setCor();

	return S_OK;
}

void mapTool::release(void)
{

}

void mapTool::update(void)
{
	//================= A R R A Y =========================
	sort(_vBuild.begin(), _vBuild.end());
	sort(_vRoot.begin(), _vRoot.end());

	//================= T I M E R ================================
	if (_inputDelayX) _inputDelayX--;
	if (_inputDelayY) _inputDelayY--;



	//================= F U N C T I O N ==========================
	setCor();
	cameraMove();
	setButton();
	minimapMove();
	inputCommon();
	if (_ptMouse.x < 788) inputOnMap();
	else if(_ptMouse.x > 788 && !_move) inputOnUI();

}

void mapTool::render(void)
{
	//================= T I L E   D R A W ============================


	tileDraw();


	//================= R O A D   D R A W =========================


	roadDraw();

	//================= B U I L D I N G   D R A W ==================


	buildingDraw();
	rootingDraw();

	//=============== S E L E C T   R E C T ==========================
	if(_ptMouse.x < 788) selectDraw();

	//=============== U I ==================
	IMAGEMANAGER->findImage("mapToolUI")->render(getMemDC());
	IMAGEMANAGER->findImage("mapToolMark")->render(getMemDC());

	buttonDraw();

	//=============== M I N I   M A P====================
	miniDraw();

	//==================  A T T R I B U T E ==================
	
	attributeDraw();

	//====================== CORDINATE =========================

	cordinateDraw();


}

void mapTool::selectBox(int arrX, int arrY, int destX, int destY)
{
	IMAGEMANAGER->findImage("width")->render(getMemDC(),
		20 + arrX*TILESIZE - _mapX,
		20 + arrY*TILESIZE - _mapY,
		0,0,(destX- arrX+1)*TILESIZE, 2);
	IMAGEMANAGER->findImage("width")->render(getMemDC(),
		20 + arrX*TILESIZE - _mapX,
		18 + (destY+1)*TILESIZE - _mapY,
		0, 0, (destX - arrX+1)*TILESIZE, 2);
	IMAGEMANAGER->findImage("height")->render(getMemDC(),
		20 + arrX*TILESIZE - _mapX,
		20 + arrY*TILESIZE - _mapY,
		0, 0,2, (destY- arrY+1)*TILESIZE);
	IMAGEMANAGER->findImage("height")->render(getMemDC(),
		18 + (destX+1)*TILESIZE - _mapX,
		20 + arrY*TILESIZE - _mapY,
		0, 0, 2, (destY - arrY+1)*TILESIZE);
}

void mapTool::closedBox(int arrX, int arrY, int destX, int destY)
{
	for (int i = arrX; i <= destX; i++)
	{
		for (int j = arrY; j <= destY; j++)
		{
			if (_mapArr[i][j].tile == TILE_WATER ||	_buildArr[i][j].isClosed)
			{
				IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
					20 + i*TILESIZE - _mapX, 20 + j*TILESIZE - _mapY, 150);
			}
		}
	}
}

void mapTool::cordinateDraw(void)
{
	for (int i = 0; i < 24; i++)
	{
		Rectangle(getMemDC(), 20 + i*TILESIZE, 0, 20 + (i + 1)*TILESIZE, 20);
	}
	for (int i = 0; i < 18; i++)
	{
		Rectangle(getMemDC(), 0, 20 + i*TILESIZE, 20, 20 + (i + 1)*TILESIZE);

	}
	for (int i = 0; i < MAXTILE; i++)
	{

		sprintf(_cor, "%d", i);


		if (i < 10)
		{
			if (i - (int)_mapX / TILESIZE >= 0 && i - (int)_mapX / TILESIZE < 24)
				TextOut(getMemDC(), 32 + i*TILESIZE - _mapX, 2, _cor, strlen(_cor));
			if (i - (int)_mapY / TILESIZE >= 0 && i - (int)_mapY / TILESIZE < 18)
				TextOut(getMemDC(), 5, 25 + i*TILESIZE - _mapY, _cor, strlen(_cor));
		}

		else
		{
			if (i - (int)_mapX / TILESIZE >= 0 && i - (int)_mapX / TILESIZE < 24)
				TextOut(getMemDC(), 28 + i*TILESIZE - _mapX, 2, _cor, strlen(_cor));
			if (i - (int)_mapY / TILESIZE >= 0 && i - (int)_mapY / TILESIZE < 18)
				TextOut(getMemDC(), 2, 25 + i*TILESIZE - _mapY, _cor, strlen(_cor));
		}
	}

	//================ MOUSE POINT RECT ================================
	HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);

	if (_ptMouse.x <= 788)
	{
		Rectangle(getMemDC(),
			_corX[_mouseArr.x - (int)_mapX / TILESIZE].left,
			_corX[_mouseArr.x - (int)_mapX / TILESIZE].top,
			_corX[_mouseArr.x - (int)_mapX / TILESIZE].right,
			_corX[_mouseArr.x - (int)_mapX / TILESIZE].bottom);

		Rectangle(getMemDC(),
			_corY[_mouseArr.y - (int)_mapY / TILESIZE].left,
			_corY[_mouseArr.y - (int)_mapY / TILESIZE].top,
			_corY[_mouseArr.y - (int)_mapY / TILESIZE].right,
			_corY[_mouseArr.y - (int)_mapY / TILESIZE].bottom);
	}

	SelectObject(getMemDC(), oldbrush);
	DeleteObject(brush);

	//================ MOUSE POINT NUMBER ================================

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);

	if (_ptMouse.x <= 788)
	{
		if (_mouseArr.x < 10)
			TextOut(getMemDC(), 32 + (_mouseArr.x - (int)_mapX / TILESIZE)*TILESIZE, 2, _msCorX, strlen(_msCorX));
		else
			TextOut(getMemDC(), 28 + (_mouseArr.x - (int)_mapX / TILESIZE)*TILESIZE, 2, _msCorX, strlen(_msCorX));

		if (_mouseArr.y < 10)
			TextOut(getMemDC(), 5, 25 + (_mouseArr.y - (int)_mapY / TILESIZE)*TILESIZE, _msCorY, strlen(_msCorY));
		else
			TextOut(getMemDC(), 2, 25 + (_mouseArr.y - (int)_mapY / TILESIZE)*TILESIZE, _msCorY, strlen(_msCorY));

	}

	SetTextColor(getMemDC(), RGB(0, 0, 0));

}

void mapTool::attributeDraw(void)
{
	if (_buildAttribute)
	{
		for (int i = 0; i < MAXTILE; i++)
		{
			for (int j = 0; j < MAXTILE; j++)
			{
				if (_buildArr[i][j].isClosed)
					IMAGEMANAGER->findImage("closed")->render(getMemDC(),
						20 + i*TILESIZE - _mapX, 20 + j*TILESIZE - _mapY);
				if (_buildArr[i][j].enter)
					IMAGEMANAGER->findImage("enter")->render(getMemDC(),
						20 + i*TILESIZE - _mapX, 20 + j*TILESIZE - _mapY);
					
			}
		}
	}
}

void mapTool::selectDraw(void)
{
	if (_categoryLarge == CATE_TILE )
	{
		if (_brushNum == 0 || _brushNum ==255 )
			IMAGEMANAGER->findImage("select")->render(getMemDC(),
				20 + (_ptMouse.x - 20) / TILESIZE * TILESIZE,
				20 + (_ptMouse.y - 20) / TILESIZE*TILESIZE);
		if (_brushNum == 1)
			IMAGEMANAGER->findImage("select2")->render(getMemDC(),
				20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
				20 + (_mouseArr.y - 1)*TILESIZE - _mapY);
	}
	else if (_categoryLarge == CATE_ROAD )
	{
		switch (_categorySmall)
		{
		case SMC_ZERO:
			IMAGEMANAGER->findImage("select")->render(getMemDC(),
				20 + (_ptMouse.x - 20) / TILESIZE * TILESIZE,
				20 + (_ptMouse.y - 20) / TILESIZE*TILESIZE);
		break;
		case SMC_ONE:
			IMAGEMANAGER->findImage("select")->render(getMemDC(),
				20 + (_ptMouse.x - 20) / TILESIZE * TILESIZE,
				20 + (_ptMouse.y - 20) / TILESIZE*TILESIZE);
			break;
		case SMC_TWO:
			IMAGEMANAGER->findImage("select")->render(getMemDC(),
				20 + (_ptMouse.x - 20) / TILESIZE * TILESIZE,
				20 + (_ptMouse.y - 20) / TILESIZE*TILESIZE);
			break;
		case SMC_FOUR:
			if (_saveIndex.x == 0)
				IMAGEMANAGER->findImage("select")->render(getMemDC(),
					20 + (_ptMouse.x - 20) / TILESIZE * TILESIZE,
					20 + (_ptMouse.y - 20) / TILESIZE*TILESIZE);
			if (_saveIndex.x == 1)
			{
				IMAGEMANAGER->findImage("select2")->render(getMemDC(),
					20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 1)*TILESIZE - _mapY);

			}
			

		break;
		}
	}
	else if (_categoryLarge == CATE_BUILDING )
	{
		switch (_categorySmall)
		{
		case SMC_ZERO:
			switch (_saveIndex.x)
			{
			case 0:
				IMAGEMANAGER->findImage("point_castle")->render(getMemDC(),
					20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 3)*TILESIZE - _mapY);
				IMAGEMANAGER->findImage("building_castle_shadow")->alphaFrameRender(getMemDC(),
					20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 3)*TILESIZE - _mapY,1,0,SHADOWALPHA);

				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if(_mapArr[_mouseArr.x -2 +i][_mouseArr.y  +j].tile == TILE_WATER ||
							_buildArr[_mouseArr.x - 2 +i][_mouseArr.y +j].isClosed)
							IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
								20 + (_mouseArr.x - 2 + i)*TILESIZE - _mapX,
								20 + (_mouseArr.y  + j)*TILESIZE - _mapY,150);
					}
				}
				break;
			case 1:
				IMAGEMANAGER->findImage("point_dungeon")->render(getMemDC(),
					20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 3)*TILESIZE - _mapY);
				IMAGEMANAGER->findImage("building_dungeon_shadow")->alphaFrameRender(getMemDC(),
					20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 3)*TILESIZE - _mapY,1,0,SHADOWALPHA);

				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (_mapArr[_mouseArr.x - 2 + i][_mouseArr.y + j].tile == TILE_WATER ||
							_buildArr[_mouseArr.x - 2 + i][_mouseArr.y + j].isClosed)
							IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
								20 + (_mouseArr.x - 2 + i)*TILESIZE - _mapX,
								20 + (_mouseArr.y + j)*TILESIZE - _mapY, 150);
					}
				}

				break;
			}
		break;
		
		case SMC_ONE:
		{
			//====================== 테두리 그리기
			if(_saveIndex.x + _saveIndex.y*4 != 2 &&
				_saveIndex.x + _saveIndex.y * 4 != 5)
				IMAGEMANAGER->findImage("point_mine")->render(getMemDC(),
					20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 1)*TILESIZE - _mapY);

			if(_saveIndex.x + _saveIndex.y * 4 == 2)
				IMAGEMANAGER->findImage("point_wood")->render(getMemDC(),
					20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 2)*TILESIZE - _mapY);

			if(_saveIndex.x + _saveIndex.y * 4 == 5)
				IMAGEMANAGER->findImage("point_mercury")->render(getMemDC(),
					20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 2)*TILESIZE - _mapY);

			switch (_saveIndex.y)
			{
			case 0:
				switch (_saveIndex.x)
				{
				case 0:
					IMAGEMANAGER->findImage("mine_gold")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 1)*TILESIZE - _mapY);					
					break;
				case 1:
					IMAGEMANAGER->findImage("mine_crystal")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 1)*TILESIZE - _mapY);
					break;
				case 2:
					IMAGEMANAGER->findImage("mine_wood")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 2)*TILESIZE - _mapY);
					break;
				case 3:
					IMAGEMANAGER->findImage("mine_iron")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 1)*TILESIZE - _mapY);
					break;
				}
				break;
			case 1:
				switch (_saveIndex.x)
				{
				case 0:
					IMAGEMANAGER->findImage("mine_sulfur")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 1)*TILESIZE - _mapY);
					break;
				case 1:
					IMAGEMANAGER->findImage("mine_mercury")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 2)*TILESIZE - _mapY);
					break;
				case 2:
					IMAGEMANAGER->findImage("mine_gem")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 1)*TILESIZE - _mapY);
					break;
				case 3:
					break;
				}

				break;
			}

			//============ 3 * 2 사이즈 금지 구역 표시
			if ((_saveIndex.x + _saveIndex.y * 4) != 5 &&
				(_saveIndex.x + _saveIndex.y * 4) != 2 &&
				(_saveIndex.x + _saveIndex.y * 4) != 7 && 
				(_saveIndex.x + _saveIndex.y * 4) != 4)
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (_mapArr[_mouseArr.x - 1 + i][_mouseArr.y - 1 + j].tile == TILE_WATER ||
							_buildArr[_mouseArr.x - 1 + i][_mouseArr.y -1 + j].isClosed)
							IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
								20 + (_mouseArr.x - 1 + i)*TILESIZE - _mapX,
								20 + (_mouseArr.y - 1 + j)*TILESIZE - _mapY, 150);
					}
				}
			if ((_saveIndex.x + _saveIndex.y) * 4 == 4)
			{
				for (int i = 0; i < 3; i++)
				{
					if (_mapArr[_mouseArr.x - 1 + i][_mouseArr.y ].tile == TILE_WATER ||
						_buildArr[_mouseArr.x - 1 + i][_mouseArr.y ].isClosed)
						IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
							20 + (_mouseArr.x - 1 + i)*TILESIZE - _mapX,
							20 + (_mouseArr.y )*TILESIZE - _mapY, 150);

				}
			}


			//============== 3 * 3 사이즈 금지 구역 표시 
			if ((_saveIndex.x + _saveIndex.y * 4) == 5 )
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (_mapArr[_mouseArr.x - 1 + i][_mouseArr.y -1 +j].tile == TILE_WATER ||
							_buildArr[_mouseArr.x - 1 + i][_mouseArr.y -1 + j].isClosed)
							IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
								20 + (_mouseArr.x - 1 + i)*TILESIZE - _mapX,
								20 + (_mouseArr.y - 1 +j )*TILESIZE - _mapY, 150);

					}
				}
			//============== 4 * 2 사이즈 금지 구역 표시 
			if ((_saveIndex.x + _saveIndex.y * 4) == 2)
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (_mapArr[_mouseArr.x - 2 + i][_mouseArr.y - 1 + j].tile == TILE_WATER ||
							_buildArr[_mouseArr.x - 2 + i][_mouseArr.y -1 + j].isClosed)
							IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
								20 + (_mouseArr.x - 2 + i)*TILESIZE - _mapX,
								20 + (_mouseArr.y - 1 + j)*TILESIZE - _mapY, 150);
					}
				}



		}
		break;

		case SMC_TWO:
			if (_categorySmall == SMC_TWO)
			{


				char evName[256];
				int adjustX = 0;
				int adjustY = 0;
				int sizeX = 0;
				int sizeY = 0;
				switch (_saveIndex.y)
				{
				case 0:
					if (_page == 0 || _foldMini)
						switch (_saveIndex.x)
						{
						case 0:
							sprintf(evName, "ev_lvlup");
							adjustY = 1;
							adjustX = 0;
							sizeX = 1;
							sizeY = 1;
							break;
						case 1:
							sprintf(evName, "ev_physical");
							adjustY = 1;
							adjustX = 0;
							sizeX = 2;
							sizeY = 1;
							break;
						case 2: sprintf(evName, "ev_magical");
							adjustY = 0;
							adjustX = 0;
							sizeX = 1;
							sizeY = 1;
							break;
						case 3: sprintf(evName, "ev_skill");
							adjustY = 0;
							adjustX = -1;
							sizeX = 3;
							sizeY = 1;
							break;
						}
					else if (_page == 1 && !_foldMini)
						switch (_saveIndex.x)
						{
						case 0:	sprintf(evName, "ev_movement");
							adjustY = 0;
							adjustX = 0;
							sizeX = 2;
							sizeY = 1;
							break;
						case 1:	sprintf(evName, "ev_resource");
							adjustY = 0;
							adjustX = -1;
							sizeX = 3;
							sizeY = 2;
							break;
						}
					else sprintf(evName, "empty");
					break;
				case 1:
					if (_page == 0 || _foldMini)
						switch (_saveIndex.x)
						{
						case 0: sprintf(evName, "ev_magic");
							adjustY = 0;
							adjustX = 0;
							sizeX = 1;
							sizeY = 1;
							break;
						case 1: sprintf(evName, "ev_luck");
							adjustY = 0;
							adjustX = 0;
							sizeX = 2;
							sizeY = 1;
							break;
						case 2: sprintf(evName, "ev_morale");
							adjustY = 0;
							adjustX = 0;
							sizeX = 2;
							sizeY = 1;
							break;
						case 3: sprintf(evName, "ev_explore");
							adjustY = 1;
							adjustX = 0;
							sizeX = 1;
							sizeY = 1;
							break;
						}
					else sprintf(evName, "empty");

					break;
				case 2:
					if (_foldMini)
						switch (_saveIndex.x)
						{
						case 0: sprintf(evName, "ev_movement");
							adjustY = 0;
							adjustX = 0;
							sizeX = 2;
							sizeY = 1;
							break;
						case 1: sprintf(evName, "ev_resource");
							adjustY = 0;
							adjustX = -1;
							sizeX = 3;
							sizeY = 2;
							break;
						}
					else sprintf(evName, "empty");
					break;
				}

				if (!((_page == 0 || _foldMini) && (_saveIndex.x == 1 && _saveIndex.y == 1)))
					IMAGEMANAGER->findImage(evName)->frameRender(getMemDC(),
						20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 1)*TILESIZE - _mapY);
				else
					IMAGEMANAGER->findImage(evName)->frameRender(getMemDC(),
						20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
						20 + (_mouseArr.y)*TILESIZE - _mapY);

				for (int i = adjustX; i < adjustX + sizeX; i++)
				{
					for (int j = adjustY; j < adjustY + sizeY; j++)
					{
						if (_mapArr[_mouseArr.x + i][_mouseArr.y + j].tile == TILE_WATER ||
							_buildArr[_mouseArr.x + i][_mouseArr.y + j].isClosed)
						{
							IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
								20 + (_mouseArr.x + i)*TILESIZE - _mapX,
								20 + (_mouseArr.y + j)*TILESIZE - _mapY, 150);
						}

					}
				}
				selectBox(_mouseArr.x - IMAGEMANAGER->findImage(evName)->getFrameWidth() / 2/TILESIZE,
					_mouseArr.y - IMAGEMANAGER->findImage(evName)->getFrameHeight() / 2/TILESIZE,
					_mouseArr.x + maxRange(IMAGEMANAGER->findImage(evName)->getFrameWidth() / TILESIZE, 2),
					_mouseArr.y + maxRange(IMAGEMANAGER->findImage(evName)->getFrameHeight() / TILESIZE, 2));
			}
		break;

		case SMC_THREE:
		break;

		case SMC_FOUR:
		{
			if (_saveIndex.x == 0)
				IMAGEMANAGER->findImage("select")->render(getMemDC(),
					20 + (_mouseArr.x) *TILESIZE - _mapX,
					20 + (_mouseArr.y) *TILESIZE - _mapY);

			if (_saveIndex.x == 1)
			{
				IMAGEMANAGER->findImage("select2")->render(getMemDC(),
					20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 1)*TILESIZE - _mapY);
			}
		}

			break;
		case SMC_FIVE:
		{
			//==================== 오브 젝트 이동 셀렉 =================
			if (_move)
			{


				switch (_remember.type)
				{
				case 0:
					switch (_remember.camp)
					{
					case CAMP_CASTLE:
						IMAGEMANAGER->findImage("point_castle")->render(getMemDC(),
							20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
							20 + (_mouseArr.y - 3)*TILESIZE - _mapY);

						break;
					case CAMP_DUNGEON:
						IMAGEMANAGER->findImage("point_dungeon")->render(getMemDC(),
							20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
							20 + (_mouseArr.y - 3)*TILESIZE - _mapY);
						break;
						
					}
					break;
				case 1:
					_remember.img->frameRender(getMemDC(),
							20 + (_mouseArr.x - _remember.sizeX/2 - _remember.imgX)*TILESIZE - _mapX,
							20 + (_mouseArr.y - _remember.sizeY/2 - _remember.imgY)*TILESIZE - _mapY);
						
					selectBox(_mouseArr.x - (_remember.sizeX + _remember.imgX) / 2,
						_mouseArr.y - (_remember.sizeY + _remember.imgY) / 2,
						_mouseArr.x + maxRange(_remember.img->getFrameWidth()/TILESIZE,2),
						_mouseArr.y + maxRange(_remember.img->getFrameHeight()/TILESIZE,2));

						break;

				case 2:

						_remember.img->frameRender(getMemDC(),
							20 + (_mouseArr.x - (_remember.sizeX + _remember.imgX)/ 2)*TILESIZE - _mapX,
							20 + (_mouseArr.y - (_remember.sizeY + _remember.imgY)/2)*TILESIZE - _mapY);


					selectBox(_mouseArr.x - (_remember.sizeX + _remember.imgX) / 2,
						_mouseArr.y - (_remember.sizeY + _remember.imgY) / 2,
						_mouseArr.x + maxRange(_remember.img->getFrameWidth()/TILESIZE,2),
						_mouseArr.y + maxRange(_remember.img->getFrameHeight()/TILESIZE,2));


					break;
				}
				//============== 금지 구역 표시
				for (int i = _mouseArr.x - _remember.sizeX / 2; i < _mouseArr.x + getRise(_remember.sizeX, 2); i++)
				{
					for (int j = _mouseArr.y - _remember.sizeY / 2; j < _mouseArr.y + getRise(_remember.sizeY, 2); j++)
					{
						int adjustX = 0;
						int adjustY = 0;
						switch (_remember.ev)
						{
						case EV_LVUP:		adjustY = 1;
							break;
						case EV_PHYSICAL:	adjustX = 1; adjustY = 1;
							break;
						case EV_MAGICAL:	 
							break;
						case EV_SKILL:		
							break;
						case EV_MAGIC:		
							break;
						case EV_LUCK:		adjustX = 1;
							break;
						case EV_MORALE:		adjustX = 1; 
							break;
						case EV_EXPLORE:	adjustY = 1;
							break;
						case EV_MOVEMENT:	adjustX = 1;
							break;
						case EV_RESOURCE:	adjustY = 1;
							break;

						}
						if (_buildArr[i + adjustX][j + adjustY].isClosed ||
							_mapArr[i + adjustX][j+ adjustY].tile == TILE_WATER)
							IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
								20 + (i+adjustX)*TILESIZE - _mapX, 20 + (j+ adjustY)*TILESIZE - _mapY, 150);
					}
				}
			}

		}
		break;
	
		case SMC_NULL:
			break;

		}
	}
	else if (_categoryLarge == CATE_OBS)
	{
		switch (_categorySmall)
		{
		case SMC_ZERO:
		{
			//===================== 드로우 위치 
			IMAGEMANAGER->findImage("obstacle_1x1")->frameRender(getMemDC(),
				20 + _mouseArr.x * TILESIZE - _mapX,
				20 + _mouseArr.y * TILESIZE - _mapY, _saveIndex.x , _saveIndex.y);


			//===================== 설치 가능 여부 표시 
			if (_mapArr[_mouseArr.x][_mouseArr.y].tile == TILE_WATER )
			{
				IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
					20 + _mouseArr.x * TILESIZE - _mapX,
					20 + _mouseArr.y * TILESIZE - _mapY, 150);
			}
			//==================== 셀렉 박스
			selectBox(_mouseArr.x, _mouseArr.y, _mouseArr.x, _mouseArr.y);

		}
		break;

		case SMC_ONE:
		{
				//==================== 드로우 위치
			IMAGEMANAGER->findImage("obstacle_2x2")->frameRender(getMemDC(),
				20 + (_mouseArr.x - 1) * TILESIZE - _mapX,
				20 + (_mouseArr.y - 1) * TILESIZE - _mapY, _saveIndex.x , _saveIndex.y + _page*2);

			//==================== 설치 가능 여부
			if(_saveIndex.x ==3)
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					if (_mapArr[_mouseArr.x - i][_mouseArr.y - j].tile == TILE_WATER )
					{
						IMAGEMANAGER->findImage("closed")->render(getMemDC(),
							20 + (_mouseArr.x - i) * TILESIZE - _mapX,
							20 + (_mouseArr.y - j) * TILESIZE - _mapY);
					}
				}
			}
			else if (_mapArr[_mouseArr.x][_mouseArr.y].tile == TILE_WATER )
			{
				IMAGEMANAGER->findImage("closed")->render(getMemDC(),
					20 + _mouseArr.x * TILESIZE - _mapX,
					20 + _mouseArr.y * TILESIZE - _mapY);

			}

			//===================셀렉 박스
			selectBox(_mouseArr.x - 1, _mouseArr.y - 1, _mouseArr.x, _mouseArr.y);

	
		}
		break;

		case SMC_TWO:
			switch (_foldMini)
			{
			case TRUE:
				// 4 x 4 사이즈 드로우 위치
				if (_page < 2)
				{
					IMAGEMANAGER->findImage("obstacle_4x4")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 2)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 2)*TILESIZE - _mapY, _saveIndex.x, _saveIndex.y +  2*_page);
					//================ 설치 가능 여부
					for (int i = _mouseArr.x -1 ; i <= _mouseArr.x + 1; i++)
					{
						for (int j = _mouseArr.y -1 ; j <= _mouseArr.y + 1; j++)
						{
							if (_mapArr[i][j].tile == TILE_WATER )
							{
								IMAGEMANAGER->findImage("closed")->render(getMemDC(),
									20 + i*TILESIZE - _mapX, 20 + j*TILESIZE - _mapY);
							}
						}
					}
					//==============셀렉 박스
					selectBox(_mouseArr.x - 2, _mouseArr.y - 2, _mouseArr.x + 1, _mouseArr.y + 1);
				}
				// 6 x 4 사이즈 드로우 위치
				else
				{
					IMAGEMANAGER->findImage("obstacle_6x4")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 2)*TILESIZE - _mapY, 0, _saveIndex.y);
					for (int i = _mouseArr.x - 2; i <= _mouseArr.x + 2; i++)
					{
						for (int j = _mouseArr.y - 2; j <= _mouseArr.y + 1; j++)
						{
							if (_mapArr[i][j].tile == TILE_WATER)
							{
								IMAGEMANAGER->findImage("closed")->render(getMemDC(),
									20 + i*TILESIZE - _mapX, 20 + j*TILESIZE - _mapY);
							}
						}
					}
					//==================셀렉 박스
					selectBox(_mouseArr.x - 3, _mouseArr.y - 2, _mouseArr.x + 2, _mouseArr.y + 1);
				}

			break;
			case FALSE:
				// 4 x 4 사이즈 드로우 위치
				if (_page < 4)
				{
					IMAGEMANAGER->findImage("obstacle_4x4")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 2)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 2)*TILESIZE - _mapY, _saveIndex.x, _saveIndex.y + _page);
					for (int i = _mouseArr.x -1; i <= _mouseArr.x + 1; i++)
					{
						for (int j = _mouseArr.y -1; j <= _mouseArr.y + 1; j++)
						{
							if (_mapArr[i][j].tile == TILE_WATER )
							{
								IMAGEMANAGER->findImage("closed")->render(getMemDC(),
									20 + i*TILESIZE - _mapX, 20 + j*TILESIZE - _mapY);
							}
						}
					}
					//============셀렉 박스
					selectBox(_mouseArr.x - 2, _mouseArr.y - 2, _mouseArr.x + 1, _mouseArr.y + 1);

				}
				// 6 x 4 사이즈 드로우 위치
				else
				{
					IMAGEMANAGER->findImage("obstacle_6x4")->frameRender(getMemDC(),
						20 + (_mouseArr.x - 3)*TILESIZE - _mapX,
						20 + (_mouseArr.y - 2)*TILESIZE - _mapY, 0, _page-4);
					for (int i = _mouseArr.x - 2; i <= _mouseArr.x + 2; i++)
					{
						for (int j = _mouseArr.y - 2; j <= _mouseArr.y + 1; j++)
						{
							if (_mapArr[i][j].tile == TILE_WATER)
							{
								IMAGEMANAGER->findImage("closed")->render(getMemDC(),
									20 + i*TILESIZE - _mapX, 20 + j*TILESIZE - _mapY);
							}
						}
					}
					//===========셀렉 박스
					selectBox(_mouseArr.x - 3, _mouseArr.y - 2, _mouseArr.x + 2, _mouseArr.y + 1);

				}
			break;
			}
		break;

		case SMC_THREE:
		break;
	
		case SMC_FOUR:
		break;
		
		case SMC_FIVE:
		{
			if (_move)
			{
				//============= 이동 중인거 그림
				_remember.img->frameRender(getMemDC(),
					20 + (_mouseArr.x - _remember.sizeX / 2 - _remember.imgX) *TILESIZE - _mapX,
					20 + (_mouseArr.y - _remember.sizeY / 2 - _remember.imgY) * TILESIZE - _mapY,
					_remember.sourX, _remember.sourY);

				//============= 이동 중인거 셀렉
				selectBox(_mouseArr.x - _remember.sizeX/2 - _remember.imgX ,
					_mouseArr.y - _remember.sizeY/2 - _remember.imgY,
					_mouseArr.x - _remember.sizeX/2 + _remember.sizeX - 1,
					_mouseArr.y - _remember.sizeY/2 + _remember.sizeY - 1);

				//============= 이동 중인거 금지 구역
				for (int i = _mouseArr.x - _remember.sizeX/2; i < _mouseArr.x - _remember.sizeX/2 + _remember.sizeX; i++)
				{
					for (int j = _mouseArr.y - _remember.sizeY/2; j < _mouseArr.y - _remember.sizeY/2 + _remember.sizeY; j++)
					{
						if (_mapArr[i][j].tile == TILE_WATER)
						{
							IMAGEMANAGER->findImage("closed")->alphaRender(getMemDC(),
								20 + i*TILESIZE - _mapX, 20 + j*TILESIZE - _mapY, 150);
						}
					}

				}
			}
		}
			break;
		}
	}
	else if (_categoryLarge == CATE_ROOTING)
	{
		switch (_categorySmall)
		{
		case SMC_ZERO:
		{
			IMAGEMANAGER->findImage("resources")->frameRender(getMemDC(),
				20 + (_mouseArr.x -1) * TILESIZE - _mapX,
				20 + _mouseArr.y * TILESIZE - _mapY , _saveIndex.x, _saveIndex.y);
			//================= 셀렉 박스
			selectBox(_mouseArr.x - 1, _mouseArr.y , _mouseArr.x, _mouseArr.y);

			//================= 금지 구역
			closedBox(_mouseArr.x, _mouseArr.y, _mouseArr.x, _mouseArr.y);
		}
			break;
		
		case SMC_ONE:
			switch ( _saveIndex.y + _page * 2)
			{
			case 0:
				IMAGEMANAGER->findImage("artifact_weapon")->frameRender(getMemDC(),
					20 + (_mouseArr.x -1) * TILESIZE - _mapX,
					20 + (_mouseArr.y -1) * TILESIZE - _mapY, _saveIndex.x, 0);
			break;

			case 1:
				IMAGEMANAGER->findImage("artifact_armor")->frameRender(getMemDC(),
					20 + (_mouseArr.x - 1) * TILESIZE - _mapX,
					20 + (_mouseArr.y - 1) * TILESIZE - _mapY, _saveIndex.x, 0);
			break;

			case 2:
				IMAGEMANAGER->findImage("artifact_shield")->frameRender(getMemDC(),
					20 + (_mouseArr.x - 1) * TILESIZE - _mapX,
					20 + (_mouseArr.y - 1) * TILESIZE - _mapY, _saveIndex.x, 0);
			break;

			case 3:
				IMAGEMANAGER->findImage("artifact_helmet")->frameRender(getMemDC(),
					20 + (_mouseArr.x - 1) * TILESIZE - _mapX,
					20 + (_mouseArr.y - 1) * TILESIZE - _mapY, _saveIndex.x, 0);
			break;

			case 4:
				IMAGEMANAGER->findImage("artifact_acc")->frameRender(getMemDC(),
					20 + (_mouseArr.x - 1) * TILESIZE - _mapX,
					20 + (_mouseArr.y - 1) * TILESIZE - _mapY, _saveIndex.x, 0);
			break;
			}
			//================= 셀렉 박스
			selectBox(_mouseArr.x - 1, _mouseArr.y - 1, _mouseArr.x, _mouseArr.y);

			//================= 금지 박스
			closedBox(_mouseArr.x, _mouseArr.y, _mouseArr.x, _mouseArr.y);

			break;
		
		case SMC_TWO:
			break;
		
		case SMC_THREE:
			break;
		
		case SMC_FOUR:
			break;
		
		case SMC_FIVE:
			break;

		}
	}
	
	
	if (_area)
	{
		if (_mouseArr.x >= _saveAreaX)
		{
			if (_mouseArr.y >= _saveAreaY)
			{
				IMAGEMANAGER->findImage("width")->render(getMemDC(),
					20 + _saveAreaX * TILESIZE - _mapX, 20 + _saveAreaY * TILESIZE - _mapY,
					0, 0, (1 + _mouseArr.x - _saveAreaX)*TILESIZE, 2);
				IMAGEMANAGER->findImage("width")->render(getMemDC(),
					20 + _saveAreaX * TILESIZE - _mapX, 20 + (_mouseArr.y + 1) * TILESIZE - 2 - _mapY,
					0, 0, (1 + _mouseArr.x - _saveAreaX)*TILESIZE, 2);
				IMAGEMANAGER->findImage("height")->render(getMemDC(),
					20 + _saveAreaX * TILESIZE - _mapX, 20 + _saveAreaY * TILESIZE - _mapY,
					0, 0, 2, (1 + _mouseArr.y - _saveAreaY)*TILESIZE);
				IMAGEMANAGER->findImage("height")->render(getMemDC(),
					18 + (_mouseArr.x +1) * TILESIZE - _mapX, 20 + _saveAreaY* TILESIZE - _mapY,
					0, 0, 2, (1 + _mouseArr.y - _saveAreaY)*TILESIZE);

			}
			else
			{
				IMAGEMANAGER->findImage("width")->render(getMemDC(),
					20 + _saveAreaX * TILESIZE - _mapX, 20 + _mouseArr.y* TILESIZE - _mapY,
					0, 0, (1 + _mouseArr.x - _saveAreaX)*TILESIZE, 2);
				IMAGEMANAGER->findImage("width")->render(getMemDC(),
					20 + _saveAreaX * TILESIZE - _mapX, 18 + (_saveAreaY + 1) * TILESIZE  - _mapY,
					0, 0, (1 + _mouseArr.x - _saveAreaX)*TILESIZE, 2);
				IMAGEMANAGER->findImage("height")->render(getMemDC(),
					20 + _saveAreaX * TILESIZE - _mapX, 20 + _mouseArr.y* TILESIZE - _mapY,
					0, 0, 2, (1 + _saveAreaY - _mouseArr.y )*TILESIZE);
				IMAGEMANAGER->findImage("height")->render(getMemDC(),
					18 + (_mouseArr.x + 1) * TILESIZE - _mapX, 20 + _mouseArr.y* TILESIZE - _mapY,
					0, 0, 2, (1 + _saveAreaY - _mouseArr.y)*TILESIZE);

			}
		}
		else
		{
			if (_mouseArr.y >= _saveAreaY)
			{
				IMAGEMANAGER->findImage("width")->render(getMemDC(),
					20 + _mouseArr.x * TILESIZE - _mapX, 20 + _saveAreaY * TILESIZE - _mapY,
					0, 0, (1 + _saveAreaX - _mouseArr.x )*TILESIZE, 2);
				IMAGEMANAGER->findImage("width")->render(getMemDC(),
					20 + _mouseArr.x * TILESIZE - _mapX, 18 + (_mouseArr.y + 1) * TILESIZE  - _mapY,
					0, 0, (1 + _saveAreaX - _mouseArr.x )*TILESIZE, 2);
				IMAGEMANAGER->findImage("height")->render(getMemDC(),
					20 + _mouseArr.x * TILESIZE - _mapX, 20 + _saveAreaY * TILESIZE - _mapY,
					0, 0, 2, (1 + _mouseArr.y - _saveAreaY)*TILESIZE);
				IMAGEMANAGER->findImage("height")->render(getMemDC(),
					18 + (_saveAreaX + 1) * TILESIZE - _mapX, 20 + _saveAreaY* TILESIZE - _mapY,
					0, 0, 2, (1 + _mouseArr.y - _saveAreaY)*TILESIZE);

			}
			else
			{
				IMAGEMANAGER->findImage("width")->render(getMemDC(),
					20 + _mouseArr.x * TILESIZE - _mapX, 20 + _mouseArr.y* TILESIZE - _mapY,
					0, 0, (1 + _saveAreaX -_mouseArr.x )*TILESIZE, 2);
				IMAGEMANAGER->findImage("width")->render(getMemDC(),
					20 + _mouseArr.x * TILESIZE - _mapX, 18 + (_saveAreaY + 1) * TILESIZE - _mapY,
					0, 0, (1 + _saveAreaX - _mouseArr.x )*TILESIZE, 2);
				IMAGEMANAGER->findImage("height")->render(getMemDC(),
					20 + _mouseArr.x * TILESIZE - _mapX, 20 + _mouseArr.y* TILESIZE - _mapY,
					0, 0, 2, (1 + _saveAreaY - _mouseArr.y)*TILESIZE);
				IMAGEMANAGER->findImage("height")->render(getMemDC(),
					18 + (_saveAreaX + 1) * TILESIZE - _mapX, 20 + _mouseArr.y* TILESIZE - _mapY,
					0, 0, 2, (1 + _saveAreaY - _mouseArr.y)*TILESIZE);

			}
		}
	}



}

void mapTool::miniDraw(void)
{
	IMAGEMANAGER->findImage("minimap")->render(getMemDC(), _miniMap.left-2, _miniMap.top-2);

	if (!_foldMini)
	{
		IMAGEMANAGER->findImage("down")->frameRender(getMemDC(), _miniMap.left - 30, WINSIZEY - 40);
		if (_miniMap.top == WINSIZEY - 226 && _categoryLarge != CATE_NULL && _categorySmall != SMC_NULL)
		{
			IMAGEMANAGER->findImage("left")->frameRender(getMemDC(), 903, 335);
			IMAGEMANAGER->findImage("right")->frameRender(getMemDC(), 964, 335);

		}
	}
	else
	{
		IMAGEMANAGER->findImage("up")->frameRender(getMemDC(), _miniMap.left - 30, WINSIZEY - 40);
		if (_categoryLarge == CATE_OBS && _categorySmall == SMC_TWO && _miniMap.top > WINSIZEY-50)
		{
			IMAGEMANAGER->findImage("left")->frameRender(getMemDC(), 903, 463);
			IMAGEMANAGER->findImage("right")->frameRender(getMemDC(), 964, 463);

		}

	}

	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{

			if (MAXTILE == 72)
			{
				if(_mapArr[i][j].tile != TILE_WATER)
				IMAGEMANAGER->findImage("miniTerrain72")->frameRender(getMemDC(),
						_miniMap.left + i * MINISIZE, _miniMap.top + j * MINISIZE,
						_mapArr[i][j].miniX, _mapArr[i][j].miniY);

			}
			else
			{
				if (_mapArr[i][j].tile != TILE_WATER)
					IMAGEMANAGER->findImage("miniTerrain36")->frameRender(getMemDC(),
						_miniMap.left + i * MINISIZE, _miniMap.top + j * MINISIZE,
						_mapArr[i][j].miniX, _mapArr[i][j].miniY);

			}
		}
	}

	for ( _viBuild = _vBuild.begin(); _viBuild != _vBuild.end(); ++_viBuild)
	{
		if (_viBuild->camp != CAMP_NULL || _viBuild->mine != MINE_NULL || _viBuild->ev != EV_NULL)
		{
			if (MAXTILE == 72)
			{
				IMAGEMANAGER->findImage("miniBuilding72")->frameRender(getMemDC(),
					_miniMap.left + _viBuild->destX * MINISIZE,
					_miniMap.top + _viBuild->destY *MINISIZE,
					_viBuild->miniX, 0);
			}
			else
			{
				IMAGEMANAGER->findImage("miniBuilding36")->frameRender(getMemDC(),
					_miniMap.left + _viBuild->destX  * MINISIZE,
					_miniMap.top + _viBuild->destY *MINISIZE,
					_viBuild->miniX, 0);
			}
		}
		else
		{
			if (MAXTILE == 72)
			{
				IMAGEMANAGER->findImage("miniObstacle72")->alphaFrameRender(getMemDC(),
					_miniMap.left + _viBuild->destX * MINISIZE,
					_miniMap.top + _viBuild->destY * MINISIZE,
					_viBuild->miniX, 0, 150);
			}
			else
			{
				IMAGEMANAGER->findImage("miniObstacle36")->alphaFrameRender(getMemDC(),
					_miniMap.left + _viBuild->destX * MINISIZE,
					_miniMap.top + _viBuild->destY * MINISIZE,
					_viBuild->miniX, 0, 150);

			}
		}

	}

	if(MAXTILE == 72) IMAGEMANAGER->findImage("miniView72")->render(getMemDC(), _miniView.left, _miniView.top);
	else
	IMAGEMANAGER->findImage("miniView36")->render(getMemDC(), _miniView.left, _miniView.top);



}

void mapTool::tileDraw()
{
	//===================== T I L E =====================
	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			if (i - _mapX / TILESIZE >= 0 && j - _mapY / TILESIZE >= 0)
				_mapArr[i][j].img->frameRender(getMemDC(),
					20 + _mapArr[i][j].destX * TILESIZE - _mapX,
					20 + _mapArr[i][j].destY * TILESIZE - _mapY,
					_mapArr[i][j].sourX, _mapArr[i][j].sourY);

		}
	}

}

void mapTool::roadDraw(void)
{
	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			if (_roadArr[i][j].img != NULL && _roadArr[i][j].road != ROAD_END &&
				i - _mapX / TILESIZE >= 0 && 
				j - _mapY / TILESIZE >= 0)
				_roadArr[i][j].img->frameRender(getMemDC(),
					20 + _roadArr[i][j].destX * TILESIZE - _mapX,
					30 + _roadArr[i][j].destY * TILESIZE - _mapY,
					_roadArr[i][j].sourX, _roadArr[i][j].sourY);
		}
	}
}

void mapTool::buildingDraw(void)
{

	for ( _viBuild = _vBuild.begin(); _viBuild != _vBuild.end(); ++_viBuild)
	{
			_viBuild->img->frameRender(getMemDC(),
				20 + (_viBuild->destX - _viBuild->imgX) * TILESIZE- _mapX,
				20 + (_viBuild->destY - _viBuild->imgY) * TILESIZE- _mapY,
				_viBuild->sourX, _viBuild->sourY);

			if(_viBuild->mine != MINE_IRON)
			_viBuild->imgShadow->alphaFrameRender(getMemDC(),
				20 + (_viBuild->destX - _viBuild->imgX) * TILESIZE - _mapX,
				20 + (_viBuild->destY - _viBuild->imgY) * TILESIZE - _mapY,
				_viBuild->sourX, _viBuild->sourY, SHADOWALPHA);
		
	}
}

void mapTool::rootingDraw(void)
{
	for ( _viRoot = _vRoot.begin(); _viRoot != _vRoot.end(); ++_viRoot)
	{
		_viRoot->img->frameRender(getMemDC(),
			20 + (_viRoot->destX - _viRoot->imgX) * TILESIZE - _mapX,
			20 + (_viRoot->destY - _viRoot->imgY) * TILESIZE - _mapY,
			_viRoot->sourX, _viRoot->sourY);

		if(_viRoot->imgShadow != NULL)
		_viRoot->imgShadow->alphaFrameRender(getMemDC(),
			20 + (_viRoot->destX - _viRoot->imgX) * TILESIZE - _mapX,
			20 + (_viRoot->destY - _viRoot->imgY) * TILESIZE - _mapY,
			_viRoot->sourX, _viRoot->sourY, SHADOWALPHA);
	}
}

void mapTool::buttonDraw(void)
{
	IMAGEMANAGER->findImage("tileButton")->frameRender(getMemDC(), _largeCategory.left, _largeCategory.top);
	IMAGEMANAGER->findImage("roadButton")->frameRender(getMemDC(), _largeCategory.left +42, _largeCategory.top);
	IMAGEMANAGER->findImage("buildingButton")->frameRender(getMemDC(), _largeCategory.left + 84, _largeCategory.top);
	IMAGEMANAGER->findImage("button_obstacle")->frameRender(getMemDC(), _largeCategory.left + 126, _largeCategory.top);
	IMAGEMANAGER->findImage("button_rooting")->frameRender(getMemDC(), _largeCategory.left + 168, _largeCategory.top);

	switch (_categoryLarge)
	{
	case CATE_NULL:
	break;
	
	case CATE_TILE:
	{
		IMAGEMANAGER->findImage("button_green")->frameRender(getMemDC(), _smallCategory.left, _smallCategory.top);

		IMAGEMANAGER->findImage("button_water")->frameRender(getMemDC(), _smallCategory.left + 42, _smallCategory.top);

		IMAGEMANAGER->findImage("button_volcano")->frameRender(getMemDC(), _smallCategory.left + 84, _smallCategory.top);
	
		if (_categorySmall != SMC_NULL)
		{
			IMAGEMANAGER->findImage("size1")->frameRender(getMemDC(), _smallCategory.left, _smallCategory.bottom + 10);

			IMAGEMANAGER->findImage("size2")->frameRender(getMemDC(), _smallCategory.left , _smallCategory.bottom + 36);

			IMAGEMANAGER->findImage("sizeF")->frameRender(getMemDC(), _smallCategory.left , _smallCategory.bottom + 62);
		}

		switch (_categorySmall)
		{
		case SMC_ZERO:
			if (_miniMap.top <= WINSIZEY - 226)
			{
				IMAGEMANAGER->findImage("button_terrain_green")->frameRender(getMemDC(),
					_contents.left, _contents.top);

			}
			else
			{
				IMAGEMANAGER->findImage("button_terrain_green_large")->render(getMemDC(),
					_contents.left, _contents.top,0,0,256,_boxLength);

			}
		break;
		case SMC_ONE:
			if (_miniMap.top <= WINSIZEY - 226)
			{
				IMAGEMANAGER->findImage("button_terrain_water")->frameRender(getMemDC(),
					_contents.left, _contents.top);

			}
			else
			{
				IMAGEMANAGER->findImage("button_terrain_water_large")->render(getMemDC(),
					_contents.left, _contents.top, 0, 0, 256, _boxLength);

			}
			break;
		case SMC_TWO:
			if (_miniMap.top <= WINSIZEY - 226)
			{
				IMAGEMANAGER->findImage("button_terrain_volcano")->frameRender(getMemDC(),
					_contents.left, _contents.top);

			}
			else
			{
				IMAGEMANAGER->findImage("button_terrain_volcano_large")->render(getMemDC(),
					_contents.left, _contents.top, 0, 0, 256, _boxLength);

			}
			break;
		}

	}
	break;

	case CATE_ROAD:
	{
		IMAGEMANAGER->findImage("button_normal")->frameRender(getMemDC(), _smallCategory.left, _smallCategory.top);

		IMAGEMANAGER->findImage("button_rock")->frameRender(getMemDC(), _smallCategory.left + 42, _smallCategory.top);

		IMAGEMANAGER->findImage("button_river")->frameRender(getMemDC(), _smallCategory.left + 84, _smallCategory.top);

		IMAGEMANAGER->findImage("erase")->frameRender(getMemDC(), _smallCategory.right - 32, _smallCategory.top);

		if(_categorySmall != SMC_NULL && _categorySmall != SMC_FOUR) 
			IMAGEMANAGER->findImage("size1")->frameRender(getMemDC(), _smallCategory.left, _smallCategory.bottom + 10);



		switch (_categorySmall)
		{
		case SMC_ZERO:
			IMAGEMANAGER->findImage("button_road_normal")->render(getMemDC(),
				_contents.left, _contents.top);
		break;
		case SMC_ONE:
			IMAGEMANAGER->findImage("button_road_rock")->render(getMemDC(),
				_contents.left, _contents.top);
		break;
		case SMC_TWO:
			IMAGEMANAGER->findImage("button_road_river")->render(getMemDC(),
				_contents.left, _contents.top);
			break;
		case SMC_FOUR:
			IMAGEMANAGER->findImage("button_brush_size")->render(getMemDC(),
				_contents.left, _contents.top);
			break;
		}

	}
	break;
	
	case CATE_BUILDING:
	{
		IMAGEMANAGER->findImage("button_camp")->frameRender(getMemDC(),
			_smallCategory.left, _smallCategory.top);

		IMAGEMANAGER->findImage("button_mine")->frameRender(getMemDC(),
			_smallCategory.left + 42, _smallCategory.top);

		IMAGEMANAGER->findImage("button_ev")->frameRender(getMemDC(),
			_smallCategory.left + 84, _smallCategory.top);

		IMAGEMANAGER->findImage("erase")->frameRender(getMemDC(),
			 _smallCategory.right - 74, _smallCategory.top);

		IMAGEMANAGER->findImage("move")->frameRender(getMemDC(),
			_smallCategory.right - 32, _smallCategory.top);
	
		switch (_categorySmall)
		{
		case SMC_ZERO:
			IMAGEMANAGER->findImage("button_castle")->frameRender(getMemDC(),
				_contents.left - 10, _contents.top);
			IMAGEMANAGER->findImage("button_dungeon")->frameRender(getMemDC(),
				_contents.left + 118, _contents.top);
			break;
		case SMC_ONE:
				IMAGEMANAGER->findImage("button_gold")->frameRender(getMemDC(),
					_contents.left - 10, _contents.top);
				IMAGEMANAGER->findImage("button_crystal")->frameRender(getMemDC(),
					_contents.left + 54, _contents.top);
				IMAGEMANAGER->findImage("button_wood")->frameRender(getMemDC(),
					_contents.left + 118, _contents.top);
				IMAGEMANAGER->findImage("button_iron")->frameRender(getMemDC(),
					_contents.left + 182, _contents.top);
				IMAGEMANAGER->findImage("button_sulfur")->frameRender(getMemDC(),
					_contents.left - 10, _contents.top + 64);
				IMAGEMANAGER->findImage("button_mercury")->frameRender(getMemDC(),
					_contents.left + 54, _contents.top + 64);
				IMAGEMANAGER->findImage("button_gem")->frameRender(getMemDC(),
					_contents.left + 118, _contents.top + 64);
				break;
		case SMC_TWO:
				if (_page == 0 || _foldMini)
				{
					IMAGEMANAGER->findImage("button_lvlup")->frameRender(getMemDC(),
						_contents.left - 10, _contents.top);
					IMAGEMANAGER->findImage("button_physical")->frameRender(getMemDC(),
						_contents.left + 54, _contents.top);
					IMAGEMANAGER->findImage("button_magical")->frameRender(getMemDC(),
						_contents.left + 118, _contents.top);
					IMAGEMANAGER->findImage("button_skill")->frameRender(getMemDC(),
						_contents.left + 182, _contents.top);
					IMAGEMANAGER->findImage("button_magic")->frameRender(getMemDC(),
						_contents.left - 10, _contents.top + 64);
					IMAGEMANAGER->findImage("button_luck")->frameRender(getMemDC(),
						_contents.left + 54, _contents.top + 64);
					IMAGEMANAGER->findImage("button_morale")->frameRender(getMemDC(),
						_contents.left + 118, _contents.top + 64);
					IMAGEMANAGER->findImage("button_explore")->frameRender(getMemDC(),
						_contents.left + 182, _contents.top + 64);
				}
				else if(_page = 1 && !_foldMini)
				{
					IMAGEMANAGER->findImage("button_movement")->frameRender(getMemDC(),
						_contents.left - 10 , _contents.top );
					IMAGEMANAGER->findImage("button_resource")->frameRender(getMemDC(),
						_contents.left + 54, _contents.top );
				}
				if (_foldMini)
				{
					IMAGEMANAGER->findImage("button_movement")->frameRender(getMemDC(),
						_contents.left - 10, _contents.top + 128);
					IMAGEMANAGER->findImage("button_resource")->frameRender(getMemDC(),
						_contents.left + 54, _contents.top + 128);

				}
			break;
		case SMC_THREE:
			break;
		case SMC_FOUR:
			IMAGEMANAGER->findImage("button_brush_size")->render(getMemDC(),
				_contents.left, _contents.top);
			break;
		case SMC_FIVE:
			break;
		}

	}
	break;

	case CATE_OBS:
	{
		IMAGEMANAGER->findImage("button_1x1")->frameRender(getMemDC(),
			_smallCategory.left, _smallCategory.top);

		IMAGEMANAGER->findImage("button_2x2")->frameRender(getMemDC(),
			_smallCategory.left + 42, _smallCategory.top);

		IMAGEMANAGER->findImage("button_4x4")->frameRender(getMemDC(),
			_smallCategory.left + 84, _smallCategory.top);

		IMAGEMANAGER->findImage("button_A")->frameRender(getMemDC(),
			_smallCategory.left + 126, _smallCategory.top);

		IMAGEMANAGER->findImage("erase")->frameRender(getMemDC(),
			_smallCategory.right - 74, _smallCategory.top);

		IMAGEMANAGER->findImage("move")->frameRender(getMemDC(),
			_smallCategory.right - 32, _smallCategory.top);
	
		switch (_categorySmall)
		{
		case SMC_ZERO:
			IMAGEMANAGER->findImage("button_obstacle_1x1")->frameRender(getMemDC(),
				_contents.left, _contents.top);
			break;
		case SMC_ONE:
			if(!_foldMini)
			IMAGEMANAGER->findImage("button_obstacle_2x2")->frameRender(getMemDC(),
				_contents.left, _contents.top);

			if(_foldMini)
			IMAGEMANAGER->findImage("button_obstacle_2x2_large")->render(getMemDC(),
				_contents.left, _contents.top, 0, 0, 256, _boxLength);


				break;
		case SMC_TWO:

			//== 4x4 맵 열렸을때
			if (_miniMap.top <= WINSIZEY - 226 && _page < 4)
			{
				IMAGEMANAGER->findImage("button_obstacle_4x4")->frameRender(getMemDC(),
					_contents.left, _contents.top);

			}
			//== 44 맵 닫혔을때
			else if (_miniMap.top > WINSIZEY -226 && _page < 2)
			{
				IMAGEMANAGER->findImage("button_obstacle_4x4_large")->frameRender(getMemDC(),
					_contents.left, _contents.top);

			}

			//========= 64 맵 열렸을때
			if (_miniMap.top <= WINSIZEY - 226 && _page >3)
			{
					IMAGEMANAGER->findImage("button_obstacle_6x4")->frameRender(getMemDC(),
					_contents.left, _contents.top);
			}

			//===========64 맵 닫혔을때
			else if( _miniMap.top > WINSIZEY -226 && _page >1)
			{
				IMAGEMANAGER->findImage("button_obstacle_6x4_large")->render(getMemDC(),
					_contents.left, _contents.top);

			}

		
				break;
		case SMC_THREE:
				break;
		case SMC_FOUR:
			IMAGEMANAGER->findImage("button_brush_size")->render(getMemDC(),
				_contents.left, _contents.top);
			break;
		case SMC_FIVE:
				break;

		}

	}
	break;
	
	case CATE_ROOTING:
	{
		IMAGEMANAGER->findImage("button_resources")->frameRender(getMemDC(),
			_smallCategory.left, _smallCategory.top);
		
		IMAGEMANAGER->findImage("button_artifact")->frameRender(getMemDC(),
			_smallCategory.left + 42, _smallCategory.top);
		
		IMAGEMANAGER->findImage("erase")->frameRender(getMemDC(),
			_smallCategory.right - 74, _smallCategory.top);

		IMAGEMANAGER->findImage("move")->frameRender(getMemDC(),
			_smallCategory.right - 32, _smallCategory.top);

		switch (_categorySmall)
		{
		case SMC_ZERO:
			
			IMAGEMANAGER->findImage("button_rooting_resources")->render(getMemDC(),
			_contents.left, _contents.top);

		break;

		case SMC_ONE:

			IMAGEMANAGER->findImage("button_rooting_artifact")->frameRender(getMemDC(),
				_contents.left - 20, _contents.top, 0, _page);

		break;

		case SMC_TWO:
			break;

		case SMC_THREE:
			break;

		case SMC_FOUR:
		{
			IMAGEMANAGER->findImage("button_brush_size")->render(getMemDC(),
				_contents.left, _contents.top);
		}
		break;

		case SMC_FIVE:
			break;
		}

	}


	break;
	case CATE_UNIT:
		break;
	case CATE_END:
		break;
	default:
		break;
	}

	if (_categorySmall != SMC_FOUR && _categoryLarge != CATE_BUILDING &&
		_categorySmall != SMC_FIVE && _categoryLarge != CATE_ROOTING)
	{

		if (!(_categoryLarge == CATE_OBS && _categorySmall == SMC_ONE) &&
			!(_categoryLarge == CATE_OBS && _categorySmall == SMC_TWO) &&
			!(_categoryLarge == CATE_OBS && _categorySmall == SMC_THREE))
		{
			if (!_foldMini)
			{
				if(_saveIndex.y >= _page * 4  && _saveIndex.y <(_page+1)*4)
				IMAGEMANAGER->findImage("push")->render(getMemDC(),
					_contents.left + _saveIndex.x * TILESIZE,
					_contents.top + (_saveIndex.y - _page * 4) * TILESIZE);

			}
			else
			{
				IMAGEMANAGER->findImage("push")->render(getMemDC(),
					_contents.left + _saveIndex.x * TILESIZE,
					_contents.top + _saveIndex.y  * TILESIZE);

			}

		}

	}
	else if(_categorySmall == SMC_FOUR)
	{
		{
			IMAGEMANAGER->findImage("push")->render(getMemDC(),
				_contents.left + _saveIndex.x * TILESIZE,
				_contents.top ); 
		}
	}



}

void mapTool::setButton(void)
{
	/**/	
	//================= 항상 UI 에 보이는것 ====================
	if (_categoryLarge == CATE_TILE) IMAGEMANAGER->findImage("tileButton")->setFrameX(0);
	else IMAGEMANAGER->findImage("tileButton")->setFrameX(1);

	if (_categoryLarge == CATE_ROAD) IMAGEMANAGER->findImage("roadButton")->setFrameX(0);
	else IMAGEMANAGER->findImage("roadButton")->setFrameX(1);

	if (_categoryLarge == CATE_BUILDING) IMAGEMANAGER->findImage("buildingButton")->setFrameX(0);
	else IMAGEMANAGER->findImage("buildingButton")->setFrameX(1);

	if (_categoryLarge == CATE_OBS) IMAGEMANAGER->findImage("button_obstacle")->setFrameX(0);
	else IMAGEMANAGER->findImage("button_obstacle")->setFrameX(1);
	
	if (_categoryLarge == CATE_ROOTING) IMAGEMANAGER->findImage("button_rooting")->setFrameX(0);
	else IMAGEMANAGER->findImage("button_rooting")->setFrameX(1);

	//================ 브러쉬를 크기를 정할때 ==================
	if (_brushNum == 0) IMAGEMANAGER->findImage("size1")->setFrameX(0);
	else IMAGEMANAGER->findImage("size1")->setFrameX(1);

	if (_brushNum == 1) IMAGEMANAGER->findImage("size2")->setFrameX(0);
	else IMAGEMANAGER->findImage("size2")->setFrameX(1);

	if (_brushNum == 2) IMAGEMANAGER->findImage("sizeF")->setFrameX(0);
	else IMAGEMANAGER->findImage("sizeF")->setFrameX(1);


	//=============== 대분류에 따라 세팅 해줌=================
	switch (_categoryLarge)
	{
	case CATE_TILE:
	{
		if (_categorySmall == SMC_ZERO) IMAGEMANAGER->findImage("button_green")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_green")->setFrameX(1);

		if (_categorySmall == SMC_ONE) IMAGEMANAGER->findImage("button_water")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_water")->setFrameX(1);

		if (_categorySmall == SMC_TWO) IMAGEMANAGER->findImage("button_volcano")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_volcano")->setFrameX(1);

		IMAGEMANAGER->findImage("button_terrain_green")->setFrameY(_page);
		IMAGEMANAGER->findImage("button_terrain_water")->setFrameY(_page);
		IMAGEMANAGER->findImage("button_terrain_volcano")->setFrameY(_page);
	}
	break;
	
	case CATE_ROAD:
	{
		if (_categorySmall == SMC_ZERO) IMAGEMANAGER->findImage("button_normal")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_normal")->setFrameX(1);

		if (_categorySmall == SMC_ONE) IMAGEMANAGER->findImage("button_rock")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_rock")->setFrameX(1);

		if (_categorySmall == SMC_TWO) IMAGEMANAGER->findImage("button_river")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_river")->setFrameX(1);
	}
	break;
	
	case CATE_BUILDING:
	{
		if (_categorySmall == SMC_ZERO) IMAGEMANAGER->findImage("button_camp")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_camp")->setFrameX(1);
	
		if (_categorySmall == SMC_ONE) IMAGEMANAGER->findImage("button_mine")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_mine")->setFrameX(1);
		
		if (_categorySmall == SMC_TWO) IMAGEMANAGER->findImage("button_ev")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_ev")->setFrameX(1);

		if (_categorySmall == SMC_FIVE) IMAGEMANAGER->findImage("move")->setFrameX(0);
		else IMAGEMANAGER->findImage("move")->setFrameX(1);

		switch (_categorySmall)
		{
		case SMC_ZERO:
			if (_saveIndex.x == 0) IMAGEMANAGER->findImage("button_castle")->setFrameX(0);
			else IMAGEMANAGER->findImage("button_castle")->setFrameX(1);
		
			if (_saveIndex.x == 1) IMAGEMANAGER->findImage("button_dungeon")->setFrameX(0);
			else IMAGEMANAGER->findImage("button_dungeon")->setFrameX(1);

			break;
		case SMC_ONE:
				if (_saveIndex.x == 0 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_gold")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_gold")->setFrameX(1);
				
				if (_saveIndex.x == 1 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_crystal")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_crystal")->setFrameX(1);
				
				if (_saveIndex.x == 2 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_wood")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_wood")->setFrameX(1);
				
				if (_saveIndex.x == 3 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_iron")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_iron")->setFrameX(1);

				if (_saveIndex.x == 0 && _saveIndex.y == 1)
					IMAGEMANAGER->findImage("button_sulfur")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_sulfur")->setFrameX(1);
				
				if (_saveIndex.x == 1 && _saveIndex.y == 1)
					IMAGEMANAGER->findImage("button_mercury")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_mercury")->setFrameX(1);
				
				if (_saveIndex.x == 2 && _saveIndex.y == 1)
					IMAGEMANAGER->findImage("button_gem")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_gem")->setFrameX(1);

			break;
		case SMC_TWO:
			if (_page == 0 || _foldMini)
			{
				if (_saveIndex.x == 0 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_lvlup")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_lvlup")->setFrameX(1);

				if (_saveIndex.x == 1 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_physical")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_physical")->setFrameX(1);

				if (_saveIndex.x == 2 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_magical")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_magical")->setFrameX(1);

				if (_saveIndex.x == 3 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_skill")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_skill")->setFrameX(1);

				if (_saveIndex.x == 0 && _saveIndex.y == 1)
					IMAGEMANAGER->findImage("button_magic")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_magic")->setFrameX(1);

				if (_saveIndex.x == 1 && _saveIndex.y == 1)
					IMAGEMANAGER->findImage("button_luck")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_luck")->setFrameX(1);

				if (_saveIndex.x == 2 && _saveIndex.y == 1)
					IMAGEMANAGER->findImage("button_morale")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_morale")->setFrameX(1);

				if (_saveIndex.x == 3 && _saveIndex.y == 1)
					IMAGEMANAGER->findImage("button_explore")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_explore")->setFrameX(1);

				if (_saveIndex.x == 0 && _saveIndex.y == 2)
					IMAGEMANAGER->findImage("button_movement")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_movement")->setFrameX(1);

				if (_saveIndex.x == 1 && _saveIndex.y == 2)
					IMAGEMANAGER->findImage("button_resource")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_resource")->setFrameX(1);


			}

			if (_page == 1 && !_foldMini)
			{
				if (_saveIndex.x == 0 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_movement")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_movement")->setFrameX(1);

				if (_saveIndex.x == 1 && _saveIndex.y == 0)
					IMAGEMANAGER->findImage("button_resource")->setFrameX(0);
				else IMAGEMANAGER->findImage("button_resource")->setFrameX(1);

			}


			break;

		}

	}
	break;

	case CATE_OBS:
	{
		if (_categorySmall == SMC_ZERO) IMAGEMANAGER->findImage("button_1x1")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_1x1")->setFrameX(1);

		if (_categorySmall == SMC_ONE) IMAGEMANAGER->findImage("button_2x2")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_2x2")->setFrameX(1);

		if (_categorySmall == SMC_TWO) IMAGEMANAGER->findImage("button_4x4")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_4x4")->setFrameX(1);
		
		if (_categorySmall == SMC_THREE) IMAGEMANAGER->findImage("button_A")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_A")->setFrameX(1);

		if (_categorySmall == SMC_FIVE) IMAGEMANAGER->findImage("move")->setFrameX(0);
		else IMAGEMANAGER->findImage("move")->setFrameX(1);

		switch (_categorySmall)
		{
		case SMC_ZERO:
			break;
		case SMC_ONE:
			
			 IMAGEMANAGER->findImage("button_obstacle_2x2")->setFrameY(_page);
			break;
		case SMC_TWO:
			switch (_foldMini)
			{
			case TRUE:
				IMAGEMANAGER->findImage("button_obstacle_4x4_large")->setFrameY(_page);
				break;
			case FALSE:
				IMAGEMANAGER->findImage("button_obstacle_4x4")->setFrameY(_page);
			if(_page >= 4)IMAGEMANAGER->findImage("button_obstacle_6x4")->setFrameY(_page - 4);
			
				break;
			}
			break;
		case SMC_THREE:
				break;
		case SMC_FOUR:

			break;
		case SMC_FIVE:
			break;

		}

	}
	break;
		
	case CATE_ROOTING:
	{
		if (_categorySmall == SMC_ZERO) IMAGEMANAGER->findImage("button_resources")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_resources")->setFrameX(1);

		if (_categorySmall == SMC_ONE) IMAGEMANAGER->findImage("button_artifact")->setFrameX(0);
		else IMAGEMANAGER->findImage("button_artifact")->setFrameX(1);
		
		if (_categorySmall == SMC_FIVE) IMAGEMANAGER->findImage("move")->setFrameX(0);
		else IMAGEMANAGER->findImage("move")->setFrameX(1);
	}
	break;
	}


	//======================= ERASE 업 다운
	if (_categorySmall == SMC_FOUR) IMAGEMANAGER->findImage("erase")->setFrameX(0);
	else IMAGEMANAGER->findImage("erase")->setFrameX(1);


	//================= 미니맵 유무에 따른 컨텐츠 박스 크기 조절
	if (!_foldMini) _contents.bottom = _contents.top + 128;
	else _contents.bottom = _contents.top + 288;

	//====================== PUSH 버튼 치워버리기~!!
	if (_categorySmall == SMC_NULL)
	{
		_saveIndex.x = 15;
		_saveIndex.y = 15;
	}
	

}

void mapTool::cameraMove(void)
{
	_miniView = RectMake(_miniMap.left + _mapX / TILESIZE * MINISIZE,
		_miniMap.top + _mapY / TILESIZE * MINISIZE,
		24 * MINISIZE, 18 * MINISIZE );

	if (_ptMouse.x > WINSIZEX - 15 && _ptMouse.x < WINSIZEX)
	{
		if (!_inputDelayX)
		{
			_mapX += TILESIZE;
			_inputDelayX = INPUTDELAY;
		}
	}
	if (_ptMouse.x < 15)
	{
		if (!_inputDelayX)
		{
			_mapX -= TILESIZE;
			_inputDelayX = INPUTDELAY;
		}
	}
	if (_ptMouse.y < 15)
	{
		if (!_inputDelayY)
		{
			_mapY -= TILESIZE;
			_inputDelayY = INPUTDELAY;
		}
	}
	if (_ptMouse.y > WINSIZEY - 15 && _ptMouse.y < WINSIZEY)
	{
		if (!_inputDelayY)
		{
			_mapY += TILESIZE;
			_inputDelayY = INPUTDELAY;
		}
	}


	if (_mapX < 0) _mapX = 0;
	if (_mapX > TILESIZE * (MAXTILE - 24)) _mapX = TILESIZE *  (MAXTILE - 24);
	if (_mapY < 0) _mapY = 0;
	if (_mapY > TILESIZE *  (MAXTILE - 18)) _mapY = TILESIZE *  (MAXTILE - 18);

}

void mapTool::minimapMove(void)
{
	if (!_foldMini)
	{
		_miniMap.top -= 10;
		_miniMap.bottom -= 10;

		_boxLength -= 10;
	}
	else
	{
		_miniMap.top += 10;
		_miniMap.bottom += 10;
		
		_boxLength += 10;
	}

	if (_boxLength < 128) _boxLength = 128;
	if (_boxLength > 288 && _categoryLarge != CATE_OBS) _boxLength = 288;
	if (_boxLength > 256 && _categoryLarge == CATE_OBS) _boxLength = 256;


	if (_miniMap.top < WINSIZEY - 226)
	{
		_miniMap.top = WINSIZEY - 226;
		_miniMap.bottom = _miniMap.top + 216;
	}
	if (_miniMap.top > WINSIZEY )
	{
		_miniMap.top = WINSIZEY ;
		_miniMap.bottom = _miniMap.top - 216;
	}


}

void mapTool::deleteAll(int arrX, int arrY)
{
	switch (_categoryLarge)
	{
	case CATE_NULL:
		break;
	case CATE_TILE:
		break;
	case CATE_ROAD:
		if (_roadArr[arrX][arrY].road != ROAD_END)
		{
			_roadArr[arrX][arrY].sourX = 0;
			_roadArr[arrX][arrY].sourY = 0;
			_roadArr[arrX][arrY].road = ROAD_END;
			_roadArr[arrX][arrY].img = NULL;
			_roadArr[arrX][arrY].isChanged = false;


			setRoad(arrX - 1, arrY, _roadArr[arrX - 1][arrY].road);
			setRoad(arrX, arrY - 1, _roadArr[arrX ][arrY-1].road);
			setRoad(arrX + 1, arrY, _roadArr[arrX + 1][arrY].road);
			setRoad(arrX, arrY + 1, _roadArr[arrX ][arrY+1].road);

		}

		break;
	case CATE_BUILDING:
		for ( _viBuild = _vBuild.begin(); _viBuild != _vBuild.end(); )
		{
			if (_viBuild->destX <= arrX && _viBuild->destX + _viBuild->sizeX > arrX &&
				_viBuild->destY <= arrY && _viBuild->destY + _viBuild->sizeY > arrY)
			{
				for (int i = _viBuild->destX ; i < _viBuild->destX +_viBuild->sizeX; i++)
				{
					for (int j = _viBuild->destY; j < _viBuild->destY + _viBuild->sizeY; j++)
					{
						_buildArr[i][j].camp = CAMP_NULL;
						_buildArr[i][j].mine = MINE_NULL;
						_buildArr[i][j].ev = EV_NULL;
						_buildArr[i][j].isClosed = false;
					}
				}
				_buildArr[_viBuild->destX + _viBuild->enterX][_viBuild->destY + _viBuild->enterY].enter = false;

				_viBuild = _vBuild.erase(_viBuild);
				break;
			}
			else ++_viBuild;
		}
		break;
	case CATE_OBS:
		for (_viBuild = _vBuild.begin(); _viBuild != _vBuild.end(); )
		{
			if (_viBuild->destX <= arrX && _viBuild->destX + _viBuild->sizeX > arrX &&
				_viBuild->destY <= arrY && _viBuild->destY + _viBuild->sizeY > arrY)
			{
				for (int i = _viBuild->destX; i < _viBuild->destX + _viBuild->sizeX; i++)
				{
					for (int j = _viBuild->destY; j < _viBuild->destY + _viBuild->sizeY; j++)
					{
						_buildArr[i][j].camp = CAMP_NULL;
						_buildArr[i][j].mine = MINE_NULL;
						_buildArr[i][j].ev = EV_NULL;
						_buildArr[i][j].isClosed = false;
					}
				}
				_buildArr[_viBuild->destX + _viBuild->enterX][_viBuild->destY + _viBuild->enterY].enter = false;

				_viBuild = _vBuild.erase(_viBuild);
				break;
			}
			else ++_viBuild;
		}
		break;
	case CATE_UNIT:
		break;
	case CATE_ROOTING:
		break;
	case CATE_END:
		break;
	default:
		break;
	}
	
}

void mapTool::setRoad(int arrX, int arrY, ROAD road)
{
	ROAD currentRoad = road;


	if (!_roadArr[arrX][arrY].isChanged )
	{
		int direction = 0;

		_roadArr[arrX][arrY].isChanged = true;

		int ranNum;
		int ranNum2;

		ranNum = RND->getInt(2);
		ranNum2 = RND->getInt(4);

		switch (currentRoad)
		{
		case ROAD_NORMAL:
			_roadArr[arrX][arrY].img = IMAGEMANAGER->findImage("road_normal");
		break;
		case ROAD_ROCK:
			_roadArr[arrX][arrY].img = IMAGEMANAGER->findImage("road_rock");
		break;
		case ROAD_RIVER:
			_roadArr[arrX][arrY].img = IMAGEMANAGER->findImage("road_river");
			break;
		case ROAD_END:
		break;
		default:
			break;
		}

		_roadArr[arrX][arrY].sourX = 0;
		_roadArr[arrX][arrY].sourY = 3;
		_roadArr[arrX][arrY].road = currentRoad;


		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (_roadArr[arrX + i][arrY + j].road != ROAD_END &&  currentRoad == ROAD_RIVER)
				{
					switch (i)
					{
					case -1:
						switch (j)
						{
						case -1:
							break;
						case 0: direction += LEFTMIDDLE;
							break;
						case 1:
							break;
						}
						break;
					case 0:
						switch (j)
						{
						case -1: direction += MIDDLETOP;
							break;
						case 0:
							break;
						case 1: direction += MIDDLEBOTTOM;
							break;
						}
						break;
					case 1:
						switch (j)
						{
						case -1:
							break;
						case 0: direction += RIGHTMIDDLE;
							break;
						case 1:
							break;
						}
						break;
					}

				}
				if (currentRoad!=ROAD_RIVER &&
					_roadArr[arrX + i][arrY + j].road == ROAD_NORMAL ||
					_roadArr[arrX + i][arrY + j].road == ROAD_ROCK)
				switch (i)
				{
				case -1:
					switch (j)
					{
					case -1: 
						break;
					case 0: direction += LEFTMIDDLE;
						break;
					case 1: 
						break;
					}
					break;
				case 0:
					switch (j)
					{
					case -1: direction += MIDDLETOP;
						break;
					case 0:
						break;
					case 1: direction += MIDDLEBOTTOM;
						break;
					}
					break;
				case 1:
					switch (j)
					{
					case -1: 
						break;
					case 0: direction += RIGHTMIDDLE;
						break;
					case 1: 
						break;
					}
					break;
				}
			}
		}
		//============== 포 문 위치 헷갈린다 여기가 끝이다~ 
		

		switch (direction)
		{
		case LEFTMIDDLE+ MIDDLETOP:
			_roadArr[arrX][arrY].sourX = 4 + ranNum2;
			_roadArr[arrX][arrY].sourY = 1;
		break;
		case MIDDLETOP + RIGHTMIDDLE:
			_roadArr[arrX][arrY].sourX = ranNum2;
			_roadArr[arrX][arrY].sourY = 1;
		break;
		case RIGHTMIDDLE + MIDDLEBOTTOM:
			_roadArr[arrX][arrY].sourX = ranNum2;
			_roadArr[arrX][arrY].sourY = 0;
		break;
		case MIDDLEBOTTOM + LEFTMIDDLE:
			_roadArr[arrX][arrY].sourX = 4 + ranNum2;
			_roadArr[arrX][arrY].sourY = 0;
		break;
		case ALL - LEFTMIDDLE:
			_roadArr[arrX][arrY].sourX = 4 +  ranNum;
			_roadArr[arrX][arrY].sourY = 2;
		break;
		case ALL - MIDDLETOP:
			_roadArr[arrX][arrY].sourX = ranNum;
			_roadArr[arrX][arrY].sourY = 2;
		break;
		case ALL - RIGHTMIDDLE:
			_roadArr[arrX][arrY].sourX = 6 +ranNum;
			_roadArr[arrX][arrY].sourY = 2;
		break;
		case ALL - MIDDLEBOTTOM:
			_roadArr[arrX][arrY].sourX = 2+ ranNum;
			_roadArr[arrX][arrY].sourY = 2;
		break;
		case ALL:
			_roadArr[arrX][arrY].sourX = 4;
			_roadArr[arrX][arrY].sourY = 3;
		break;
		default:
		break;
		}

		if ((direction & LEFTMIDDLE) != LEFTMIDDLE &&
			(direction & RIGHTMIDDLE) != RIGHTMIDDLE)
		{
			_roadArr[arrX][arrY].sourX = ranNum;
			_roadArr[arrX][arrY].sourY = 3;
		}
		if ((direction & MIDDLETOP) != MIDDLETOP&&
			(direction & MIDDLEBOTTOM) != MIDDLEBOTTOM)
		{
			_roadArr[arrX][arrY].sourX = 2 + ranNum;
			_roadArr[arrX][arrY].sourY = 3;
		}


	}
	
}

void mapTool::addBuilding(int arrX, int arrY, CAMP camp)
{


	building build;
	ZeroMemory(&build, sizeof(building));

	build.mine = MINE_NULL;
	build.ev = EV_NULL;

	build.camp = camp;
	build.sizeX = 5;
	build.sizeY = 3;
	build.destX = arrX - 2;
	build.destY = arrY ;
	build.imgX = 1;
	build.imgY = 3;
	build.sourX = 1;
	build.sourY = 0;
	build.miniX = 0;
	build.enterX = 2;
	build.enterY = 2;


	switch (build.camp)
	{
	case CAMP_CASTLE:
		build.img = IMAGEMANAGER->findImage("building_castle");
		build.imgShadow = IMAGEMANAGER->findImage("building_castle_shadow");
		break;
	case CAMP_DUNGEON:
		build.img = IMAGEMANAGER->findImage("building_dungeon");
		build.imgShadow = IMAGEMANAGER->findImage("building_dungeon_shadow");
		break;
	}


	//================== 응 아니야 돌아가
	
	//================== 맵 타일 제한 넘어가면?
	if (build.destX<0 || build.destY <= 0 || build.destX >MAXTILE || build.destY > MAXTILE) return;
	
	//================== 타일이 물이거나 건물이 있다면?
	for (int i = build.destX; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY; j < build.destY + build.sizeY; j++)
		{
			if (_mapArr[i][j].tile == TILE_WATER ||
				_buildArr[i][j].isClosed) return;
		}
	}

	//================== 금지 구역 설정
	for (int i = build.destX ; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY ; j < build.destY + build.sizeY; j++)
		{
			_buildArr[i][j].camp = build.camp;
			_buildArr[i][j].isClosed = true;
		}
	}
	//================= 입구 설정
	_buildArr[build.destX + build.enterX][build.destY + build.enterY].enter = true;



	_vBuild.push_back(build);

}

void mapTool::addBuilding(int arrX, int arrY, MINE mine)
{
	building build;

	ZeroMemory(&build, sizeof(building));

	build.camp = CAMP_NULL;
	build.ev = EV_NULL;

	build.mine = mine;
	if (build.mine >= (int)MINE_NULL) return;
	build.sourX = 0;
	build.sourY = 0;
	build.miniX = 1;
	build.enterX = 1;
	build.enterY = 1;
	switch (build.mine)
	{
	case MINE_GOLD:
		build.img = IMAGEMANAGER->findImage("mine_gold");
		build.imgShadow = IMAGEMANAGER->findImage("mine_gold_shadow");
		build.sizeX = 3;
		build.sizeY = 2;
		build.imgX = 0;
		build.imgY = 0;
		build.destX = arrX - 1;
		build.destY = arrY - 1;
		build.enterX = 1;
		build.enterY = 1;
		break;
	case MINE_CRYSTAL:
		build.img = IMAGEMANAGER->findImage("mine_crystal");
		build.imgShadow = IMAGEMANAGER->findImage("mine_crystal_shadow");
		build.sizeX = 3;
		build.sizeY = 2;
		build.imgX = 0;
		build.imgY = 0;
		build.destX = arrX - 1;
		build.destY = arrY - 1;
		build.enterX = 1;
		build.enterY = 1;
		break;
	case MINE_WOOD:
		build.img = IMAGEMANAGER->findImage("mine_wood");
		build.imgShadow = IMAGEMANAGER->findImage("mine_wood_shadow");
		build.sizeX = 4;
		build.sizeY = 2;
		build.imgX = 1;
		build.imgY = 1;
		build.destX = arrX - 2;
		build.destY = arrY - 1;
		build.enterX = 2;
		build.enterY = 1;
		break;
	case MINE_IRON:
		build.img = IMAGEMANAGER->findImage("mine_iron");
		build.imgShadow = IMAGEMANAGER->findImage("empty");
		build.sizeX = 3;
		build.sizeY = 2;
		build.destX = arrX - 1;
		build.destY = arrY - 1;
		build.imgX = 0;
		build.imgY = 0;
		build.enterX = 1;
		build.enterY = 1;
		break;
	case MINE_SULFUR:
		build.img = IMAGEMANAGER->findImage("mine_sulfur");
		build.imgShadow = IMAGEMANAGER->findImage("mine_sulfur_shadow");
		build.sizeX = 3;
		build.sizeY = 1;
		build.destX = arrX - 1;
		build.destY = arrY;
		build.imgX = 0;
		build.imgY = 1;
		build.enterX = 1;
		build.enterY = 0;
		break;
	case MINE_MERCURY:
		build.img = IMAGEMANAGER->findImage("mine_mercury");
		build.imgShadow = IMAGEMANAGER->findImage("mine_mercury_shadow");
		build.sizeX = 3;
		build.sizeY = 2;
		build.enterX = 1;
		build.enterY = 1;
		build.imgX = 0;
		build.imgY = 1;
		build.destX = arrX - 1;
		build.destY = arrY - 1;
		break;
	case MINE_GEM:
		build.img = IMAGEMANAGER->findImage("mine_gem");
		build.imgShadow = IMAGEMANAGER->findImage("mine_gem_shadow");
		build.sizeX = 3;
		build.sizeY = 2;
		build.enterX = 1;
		build.enterY = 1;
		build.imgX = 0;
		build.imgY = 0;
		build.destX = arrX -1;
		build.destY = arrY -1;
		break;
	}


	//================== 응 아니야 돌아가

	//================== 맵 타일 제한 넘어가면?
	if (build.destX<0 || build.destY <= 0 || build.destX >MAXTILE || build.destY > MAXTILE) return;

	//================== 타일이 물이거나 건물이 있다면?
	for (int i = build.destX; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY; j < build.destY + build.sizeY; j++)
		{
			if (_mapArr[i][j].tile == TILE_WATER ||
				_buildArr[i][j].isClosed) return;
		}
	}


	//=============== 금지 구역 설정
	for (int i = build.destX ; i < build.destX + build.sizeX ; i++)
	{
		for (int j = build.destY ; j < build.destY + build.sizeY ; j++)
		{
			_buildArr[i][j].mine = build.mine;
			_buildArr[i][j].isClosed = true;
		}
	}

	//================ 입구 설정
	_buildArr[build.destX + build.enterX][build.destY + build.enterY].enter = true;

	_vBuild.push_back(build);
}

void mapTool::addBuilding(int arrX, int arrY, EVENT ev)
{
	building build;

	ZeroMemory(&build, sizeof(building));

	build.camp = CAMP_NULL;
	build.mine = MINE_NULL;

	build.ev = ev;
	build.sourX = 0;
	build.sourY = 0;
	build.miniX = 2;
	switch (build.ev)
	{
	case EV_LVUP:
		build.img =IMAGEMANAGER->findImage("ev_lvlup");
		build.imgShadow = IMAGEMANAGER->findImage("ev_lvlup_shadow");
		build.sizeX = 1;
		build.sizeY = 1;
		build.enterX = 0;
		build.enterY = 0;
		build.imgX = 1;
		build.imgY = 2;
		build.destX = arrX ;
		build.destY = arrY + 1;
		break;
	case EV_PHYSICAL:
		build.img = IMAGEMANAGER->findImage("ev_physical");
		build.imgShadow = IMAGEMANAGER->findImage("ev_physical_shadow");
		build.sizeX = 2;
		build.sizeY = 1;
		build.enterX = 1;
		build.enterY = 0;
		build.imgX = 1;
		build.imgY = 2;
		build.destX = arrX;
		build.destY = arrY + 1;
		break;
	case EV_MAGICAL:
		build.img = IMAGEMANAGER->findImage("ev_magical");
		build.imgShadow = IMAGEMANAGER->findImage("ev_magical_shadow");
		build.sizeX = 1;
		build.sizeY = 1;
		build.enterX = 0;
		build.enterY = 0;
		build.imgX = 1;
		build.imgY = 1;
		build.destX = arrX;
		build.destY = arrY;
		break;
	case EV_SKILL:
		build.img = IMAGEMANAGER->findImage("ev_skill");
		build.imgShadow = IMAGEMANAGER->findImage("ev_skill_shadow");
		build.sizeX = 3;
		build.sizeY = 1;
		build.enterX = 1;
		build.enterY = 0;
		build.imgX = 0;
		build.imgY = 1;
		build.destX = arrX - 1;
		build.destY = arrY;
		break;
	case EV_MAGIC:
		build.img = IMAGEMANAGER->findImage("ev_magic");
		build.imgShadow = IMAGEMANAGER->findImage("ev_magic_shadow");
		build.sizeX = 1;
		build.sizeY = 1;
		build.enterX = 0;
		build.enterY = 0;
		build.imgX = 1;
		build.imgY = 1;
		build.destX = arrX;
		build.destY = arrY;
		break;
	case EV_LUCK:
		build.img = IMAGEMANAGER->findImage("ev_luck");
		build.imgShadow = IMAGEMANAGER->findImage("ev_luck_shadow");
		build.sizeX = 2;
		build.sizeY = 1;
		build.enterX = 0;
		build.enterY = 0;
		build.imgX = 1;
		build.imgY = 0;
		build.destX = arrX ;
		build.destY = arrY;
		break;
	case EV_MORALE:
		build.img = IMAGEMANAGER->findImage("ev_morale");
		build.imgShadow = IMAGEMANAGER->findImage("ev_morale_shadow");
		build.sizeX = 2;
		build.sizeY = 1;
		build.enterX = 0;
		build.enterY = 0;
		build.imgX = 1;
		build.imgY = 1;
		build.destX = arrX ;
		build.destY = arrY;
		break;
	case EV_EXPLORE:
		build.img = IMAGEMANAGER->findImage("ev_explore");
		build.imgShadow = IMAGEMANAGER->findImage("ev_explore_shadow");
		build.sizeX = 1;
		build.sizeY = 1;
		build.enterX = 0;
		build.enterY = 0;
		build.imgX = 1;
		build.imgY = 2;
		build.destX = arrX;
		build.destY = arrY + 1;
		break;
	case EV_MOVEMENT:
		build.img = IMAGEMANAGER->findImage("ev_movement");
		build.imgShadow = IMAGEMANAGER->findImage("ev_movement_shadow");
		build.sizeX = 2;
		build.sizeY = 1;
		build.enterX = 0;
		build.enterY = 0;
		build.imgX = 1;
		build.imgY = 1;
		build.destX = arrX ;
		build.destY = arrY;
		break;
	case EV_RESOURCE:
		build.img = IMAGEMANAGER->findImage("ev_resource");
		build.imgShadow = IMAGEMANAGER->findImage("ev_resource_shadow");
		build.sizeX = 3;
		build.sizeY = 2;
		build.enterX = 2;
		build.enterY = 1;
		build.imgX = 0;
		build.imgY = 1;
		build.destX = arrX -1;
		build.destY = arrY;
		break;
	}


	//================== 응 아니야 돌아가

	//================== 맵 타일 제한 넘어가면?
	if (build.destX<0 || build.destY <= 0 || build.destX >MAXTILE || build.destY > MAXTILE) return;

	//================== 타일이 물이거나 건물이 있다면?
	for (int i = build.destX; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY; j < build.destY + build.sizeY; j++)
		{
			if (_mapArr[i][j].tile == TILE_WATER ||
				_buildArr[i][j].isClosed) return;
		}
	}



	//=============== 금지 구역 설정
	for (int i = build.destX; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY; j < build.destY + build.sizeY; j++)
		{
			_buildArr[i][j].mine = build.mine;
			_buildArr[i][j].isClosed = true;
		}
	}

	//================ 입구 설정
	_buildArr[build.destX + build.enterX][build.destY + build.enterY].enter = true;

	_vBuild.push_back(build);


}

void mapTool::addObstacle(int arrX, int arrY)
{
	building build;
	ZeroMemory(&build, sizeof(tagBuildingInfo));

	build.camp	= CAMP_NULL;
	build.mine	= MINE_NULL;
	build.ev	= EV_NULL;
	build.sourX = _saveIndex.x;
	build.sourY = _saveIndex.y;

	switch (_categorySmall)
	{
	case SMC_ZERO:
	{
		build.destX = arrX;
		build.destY = arrY;
		build.img = IMAGEMANAGER->findImage("obstacle_1x1");
		build.imgShadow = IMAGEMANAGER->findImage("obstacle_1x1_shadow");
		build.imgX = 0;
		build.imgY = 0;
		build.sizeX = 1;
		build.sizeY = 1;
		build.miniX = 0;
	}
	break;

	case SMC_ONE:
	{
		build.img = IMAGEMANAGER->findImage("obstacle_2x2");
		build.imgShadow = IMAGEMANAGER->findImage("obstacle_2x2_shadow");
		build.sourY = _saveIndex.y + 2 * _page;
		if (build.sourX == 3)
		{
			build.miniX = 1;
			build.imgX = 0;
			build.imgY = 0;
			build.sizeX = 2;
			build.sizeY = 2;

		}
		else
		{
			build.miniX = 0;
			build.imgX = 1;
			build.imgY = 1;
			build.sizeX = 1;
			build.sizeY = 1;
		}
		build.destX = arrX - build.sizeX / 2;
		build.destY = arrY - build.sizeY / 2;
	}
	break;

	case SMC_TWO:
	{
		build.miniX = 2;
		build.sourX = _saveIndex.x;
		if (_foldMini) build.sourY = _saveIndex.y + _page * 2;
		else build.sourY = _saveIndex.y + _page;

		switch (_foldMini)
		{
		case TRUE:
			if (_page < 2)
			{
				build.img = IMAGEMANAGER->findImage("obstacle_4x4");
				build.imgShadow = IMAGEMANAGER->findImage("obstacle_4x4_shadow");
				build.sizeX = 3;
				build.sizeY = 3;
				build.imgX = 1;
				build.imgY = 1;

			}
			else
			{
				build.img = IMAGEMANAGER->findImage("obstacle_6x4");
				build.imgShadow = IMAGEMANAGER->findImage("obstacle_6x4_shadow");
				build.sizeX = 5;
				build.sizeY = 4;
				build.imgX = 1;
				build.imgY = 0;
				build.sourX = 0;
				build.sourY = _saveIndex.y + _page - 2;
			}

			break;

		case FALSE:
			if (_page < 4)
			{
				build.img = IMAGEMANAGER->findImage("obstacle_4x4");
				build.imgShadow = IMAGEMANAGER->findImage("obstacle_4x4_shadow");
				build.sizeX = 3;
				build.sizeY = 3;
				build.imgX = 1;
				build.imgY = 1;

			}
			else
			{
				build.img = IMAGEMANAGER->findImage("obstacle_6x4");
				build.imgShadow = IMAGEMANAGER->findImage("obstacle_6x4_shadow");
				build.sizeX = 5;
				build.sizeY = 4;
				build.imgX = 1;
				build.imgY = 0;
				build.sourX = 0;
				build.sourY = _page - 4;

			}
			break;
		}

		build.destX = arrX - build.sizeX / 2;
		build.destY = arrY - build.sizeY / 2;
	}
	break;

	case SMC_THREE:
	{
		int ranNum0 = 0;
		int ranNum1 = 0;
		int ranIndexX = 0;
		int ranIndexY = 0;

		//=================== 박스 설정에 대한 초기화	==================
		int width = abs(_mouseArr.x - _saveAreaX);					//
		int height = abs(_mouseArr.y - _saveAreaY);					//
		int range = (width + 1) * (height + 1);						//
		int initX = 0;												//
		int initY = 0;												//
		int destX = 0;												//
		int destY = 0;												//
																	//
		if (_mouseArr.x >= _saveAreaX) initX = _saveAreaX;			//
		else initX = _mouseArr.x;									//
		if (_mouseArr.y >= _saveAreaY) initY = _saveAreaY;			//
		else initY = _mouseArr.y;									//
																	//
		destX = initX + width;										//
		destY = initY + height;										//
		//============================================================

		build.destX = arrX;
		build.destY = arrY;


		ranNum0 = RND->getInt(4);

		if (width == 0 || height == 0)
		{
			if(_mapArr[build.destX][build.destY].tile != TILE_WATER)
			build.img = IMAGEMANAGER->findImage("obstacle_1x1");
			build.imgShadow = IMAGEMANAGER->findImage("obstacle_1x1_shadow");
			build.imgX = 0;
			build.imgY = 0;
			build.sizeX = 1;
			build.sizeY = 1;
			build.miniX = 0;
			if (_mapArr[build.destX][build.destY].tile != TILE_VOLCANO)
			build.sourX = RND->getInt(7);
			else
			{
				build.sourX = RND->getFromIntTo(6,7);
			}
		build.sourY = RND->getInt(4);
		}
		else if ((width < 3 || height < 3) && build.destX != destX && build.destY != destY)
		{
			build.img = IMAGEMANAGER->findImage("obstacle_2x2");
			build.imgShadow = IMAGEMANAGER->findImage("obstacle_2x2_shadow");
			build.sourX = RND->getInt(4);
			build.sourY = RND->getInt(4);
			if (build.sourX == 3)
			{
				build.miniX = 1;
				build.imgX = 0;
				build.imgY = 0;
				build.sizeX = 2;
				build.sizeY = 2;

			}
			else
			{
				build.miniX = 0;
				build.imgX = 1;
				build.imgY = 1;
				build.sizeX = 1;
				build.sizeY = 1;
			}
		}
		else if (width>=3 && width<5 && height >= 3 )
		{
			if ((build.destX == initX || build.destX == initX + 2) &&
				!((build.destY - initY)%2) &&
				build.destX <= destX -2 && build.destY <=destY -2)
			{
				build.img = IMAGEMANAGER->findImage("obstacle_4x4");
				build.imgShadow = IMAGEMANAGER->findImage("obstacle_4x4_shadow");
				build.sizeX = 3;
				build.sizeY = 3;
				build.imgX = 1;
				build.imgY = 1;
				build.sourX = RND->getInt(2);
				build.sourY = RND->getInt(4);
				build.miniX = 2;
				if (build.sourY == 3) build.sourX = 0;
			}
			else return;
		}
		else if (width >= 5 && height >=3)
		{
			ranNum0 = RND->getInt(6);
			if (!ranNum0 && build.destX < destX - 3 && build.destY < destY - 2)
			{
				build.img = IMAGEMANAGER->findImage("obstacle_6x4");
				build.imgShadow = IMAGEMANAGER->findImage("obstacle_6x4_shadow");
				build.sizeX = 5;
				build.sizeY = 4;
				build.imgX = 1;
				build.imgY = 0;
				build.sourX = 0;
				build.miniX = 3;
				build.sourY = RND->getInt(2);
			}
			else if(ranNum0 ==1&& build.destX < destX-1 && build.destY < destY - 1)
			{
				build.img = IMAGEMANAGER->findImage("obstacle_4x4");
				build.imgShadow = IMAGEMANAGER->findImage("obstacle_4x4_shadow");
				build.sizeX = 3;
				build.sizeY = 3;
				build.imgX = 1;
				build.imgY = 1;
				build.miniX = 2;
				build.sourX = RND->getInt(2);
				build.sourY = RND->getInt(4);
				if (build.sourY == 3) build.sourX = 0;

			}
			else
			{
				if (_buildArr[build.destX][build.destY].isClosed) return;
				build.img = IMAGEMANAGER->findImage("obstacle_2x2");
				build.imgShadow = IMAGEMANAGER->findImage("obstacle_2x2_shadow");
				build.sourX = RND->getInt(4);
				build.sourY = RND->getInt(4);
				if (build.sourX == 3)
				{
					build.miniX = 1;
					build.imgX = 0;
					build.imgY = 0;
					build.sizeX = 2;
					build.sizeY = 2;

				}
				else
				{
					build.miniX = 0;
					build.imgX = 1;
					build.imgY = 1;
					build.sizeX = 1;
					build.sizeY = 1;
				}

			}
		}
		else return;
	}
	break;

	case SMC_FIVE:
	{
		build.img = _remember.img;
		build.imgShadow = _remember.imgShadow;
		build.sizeX = _remember.sizeX;
		build.sizeY = _remember.sizeY;
		build.imgX = _remember.imgX;
		build.imgY = _remember.imgY;
		build.miniX = _remember.miniX;
		build.sourX = _remember.sourX;
		build.sourY = _remember.sourY;
		build.destX = arrX - build.sizeX / 2;
		build.destY = arrY - build.sizeY / 2;
	}
		break;

	}

	//================== 응 아니야 돌아가

	//================== 맵 타일 제한 넘어가면?
	if (build.destX<0 || build.destY <= 0 || build.destX >MAXTILE || build.destY > MAXTILE) return;

	//================== 타일이 물이거나 건물이 있다면?
	for (int i = build.destX; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY; j < build.destY + build.sizeY; j++)
		{
			if (_mapArr[i][j].tile == TILE_WATER) return;
		}
	}



	//=============== 금지 구역 설정
	for (int i = build.destX; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY; j < build.destY + build.sizeY; j++)
		{
			_buildArr[i][j].mine = build.mine;
			_buildArr[i][j].isClosed = true;
		}
	}

	_vBuild.push_back(build);
}

void mapTool::addRooting(int arrX, int arrY)
{
	building build;
	
	ZeroMemory(&build, sizeof(building));

	build.camp = CAMP_NULL;
	build.mine = MINE_NULL;
	build.ev = EV_NULL;
	build.destX = arrX;
	build.destY = arrY;
	switch (_categorySmall)
	{
	case SMC_ZERO:
		build.img = IMAGEMANAGER->findImage("resources");
		build.imgShadow = IMAGEMANAGER->findImage("resources_shadow");
		build.imgX = 1;
		build.sizeX = 1;
		build.sizeY = 1;
		build.sourX = _saveIndex.x;
		build.sourY = _saveIndex.y;
		break;

	case SMC_ONE:
		switch (_saveIndex.y + _page*2)
		{
		case 0:
			build.img = IMAGEMANAGER->findImage("artifact_weapon");

		break;
		case 1:
			build.img = IMAGEMANAGER->findImage("artifact_armor");

		break;
		case 2:
			build.img = IMAGEMANAGER->findImage("artifact_shield");

		break;
		case 3:
			build.img = IMAGEMANAGER->findImage("artifact_helmet");

		break;
		case 4:
			build.img = IMAGEMANAGER->findImage("artifact_acc");

		break;
		}
		build.imgShadow = NULL;
		build.imgX = 1;
		build.imgY = 1;
		build.sizeX = 1;
		build.sizeY = 1;
		build.sourX = _saveIndex.x;
		build.sourY = 0;
		break;
	}


	//================== 응 아니야 돌아가

	//================== 맵 타일 제한 넘어가면?
	if (build.destX<0 || build.destY <= 0 || build.destX >MAXTILE || build.destY > MAXTILE) return;

	//================== 타일이 물이거나 건물이 있다면?
	for (int i = build.destX; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY; j < build.destY + build.sizeY; j++)
		{
			if (_mapArr[i][j].tile == TILE_WATER || _buildArr[i][j].isClosed) return;
		}
	}



	//=============== 금지 구역 설정
	for (int i = build.destX; i < build.destX + build.sizeX; i++)
	{
		for (int j = build.destY; j < build.destY + build.sizeY; j++)
		{
			_buildArr[i][j].mine = build.mine;
			_buildArr[i][j].isClosed = true;
		}
	}

	_vRoot.push_back(build);



}

void mapTool::setTile(int arrX, int arrY, TILE tile)
{
	TILE currentTile = tile;


	if (!_mapArr[arrX][arrY].isChanged)
	{
		int direction = 0;
		int directionS = 0;

		//========= 바꼈으면 좀 이따 다시 돌아오면 바꾸도록
		if (_brushNum != 2)_mapArr[arrX][arrY].isChanged = true;

		//========== 같은 종류에서 랜덤으로 깔기
		int ranNum;
		int ranNum2;

		ranNum = RND->getInt(4);
		ranNum2 = RND->getInt(20);

		////===== 1/20 확률로 잔디 파기
		//if(ranNum2) _mapArr[arrX][arrY].sourX = ranNum;
		//else _mapArr[arrX][arrY].sourX = 4 + ranNum;		
		
		//========= 현재 타일 깔기
		_mapArr[arrX][arrY].sourY = 0;
		switch (currentTile)
		{
		case TILE_NONE:
			break;
		case TILE_GREEN:
			_mapArr[arrX][arrY].miniX = 0;
			_mapArr[arrX][arrY].miniY = 0;
			_mapArr[arrX][arrY].tile = TILE_GREEN;
			_mapArr[arrX][arrY].img = IMAGEMANAGER->findImage("terrain_green");
			break;
		case TILE_WATER:
			_mapArr[arrX][arrY].miniX = 1;
			_mapArr[arrX][arrY].miniY = 0;
			_mapArr[arrX][arrY].tile = TILE_WATER;
			_mapArr[arrX][arrY].img = IMAGEMANAGER->findImage("terrain_water");
			break;
		case TILE_VOLCANO:
			_mapArr[arrX][arrY].miniX = 2;
			_mapArr[arrX][arrY].miniY = 0;
			_mapArr[arrX][arrY].tile = TILE_VOLCANO;
			_mapArr[arrX][arrY].img = IMAGEMANAGER->findImage("terrain_volcano");
			break;
		case TILE_END:
			break;
		default:
			break;
		}

		//========= 패턴 변화
		

		//============ 주변 ==================
		
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if(arrX + i >= 0 && arrX + i <MAXTILE && arrY + j >= 0 && arrY + j <MAXTILE)
					if (_mapArr[arrX + i][arrY + j].tile == (TILE)_categorySmall )
					{
						switch (i)
						{
						case -1:
							switch (j)
							{
							case -1: direction += LEFTTOP; directionS++;
								break;
							case 0: direction += LEFTMIDDLE; directionS++;
								break;
							case 1: direction += LEFTBOTTOM; directionS++;
								break;
							}
							break;
						case 0:
							switch (j)
							{
							case -1: direction += MIDDLETOP; directionS++;
								break;
							case 0:
								break;
							case 1: direction += MIDDLEBOTTOM; directionS++;
								break;
							}
							break;
						case 1:
							switch (j)
							{
							case -1: direction += RIGHTTOP; directionS++;
								break;
							case 0: direction += RIGHTMIDDLE; directionS++;
								break;
							case 1: direction += RIGHTBOTTOM; directionS++;
								break;
							}
							break;
						}
					}
					//if (_mapArr[arrX + i][arrY + j].tile != (TILE)_categorySmall )
					//{
					//	switch (i)
					//	{
					//	case -1:
					//		switch (j)
					//		{
					//		case -1: direction += LEFTTOP;
					//		break;
					//		case 0: direction += LEFTMIDDLE;
					//		break;
					//		case 1: direction += LEFTBOTTOM;
					//		break;
					//		}
					//	break;
					//	case 0:
					//		switch (j)
					//		{
					//		case -1: direction += MIDDLETOP;
					//		break;
					//		case 0:
					//		break;
					//		case 1: direction += MIDDLEBOTTOM;
					//		break;
					//		}
					//	break;
					//	case 1:
					//		switch (j)
					//		{
					//		case -1: direction += RIGHTTOP;
					//		break;
					//		case 0: direction += RIGHTMIDDLE;
					//		break;
					//		case 1: direction += RIGHTBOTTOM;
					//		break;
					//		}
					//	break;
					//	}
					//}
			}
		}





		//if (directionS >= 4)
		//{
		//	//===== 1/20 확률로 잔디 파기
		//	if (ranNum2) _mapArr[arrX][arrY].sourX = ranNum;
		//	else _mapArr[arrX][arrY].sourX = 4 + ranNum;
		//
		//	_mapArr[arrX][arrY].sourY = 0;
		//}
		//else if (directionS < 4 && directionS >= 2)
		//{
		//	_mapArr[arrX][arrY].sourX = 7;
		//	_mapArr[arrX][arrY].sourY = 8;
		//}
		
		_mapArr[arrX][arrY].sourX = 5;
		_mapArr[arrX][arrY].sourY = 8;

		if (~direction == LEFTTOP)
		{
			_mapArr[arrX][arrY].sourX = 4;
			_mapArr[arrX][arrY].sourY = 7;

		}
		if (~direction == RIGHTTOP)
		{
			_mapArr[arrX][arrY].sourX = 6;
			_mapArr[arrX][arrY].sourY = 7;

		}
		if (~direction == LEFTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = 2;
			_mapArr[arrX][arrY].sourY = 7;

		}
		if (~direction == LEFTTOP)
		{
			_mapArr[arrX][arrY].sourX = 1;
			_mapArr[arrX][arrY].sourY = 7;

		}
		if ((direction & RIGHT) == RIGHT &&
			(direction & MIDDLEBOTTOM) == MIDDLEBOTTOM &&
			(direction & MIDDLETOP) == MIDDLETOP)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 1;
		}
		if ((direction & LEFT) == LEFT &&
			(direction & MIDDLEBOTTOM) == MIDDLEBOTTOM &&
			(direction & MIDDLETOP) == MIDDLETOP)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 1;
		}
		if ((direction & UP) == UP &&
			(direction & LEFTMIDDLE) == LEFTMIDDLE&&
			(direction & RIGHTMIDDLE) == RIGHTMIDDLE)
		{
			
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 2;
		}
		if ((direction & DOWN) == DOWN &&
			(direction & LEFTMIDDLE) == LEFTMIDDLE &&
			(direction & RIGHTMIDDLE) == RIGHTMIDDLE)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 2;
		}	

		if ((direction & LEFTMIDDLE) != LEFTMIDDLE &&
			(direction & MIDDLETOP) != MIDDLETOP &&
			(direction & EDGE7) == EDGE7)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 3;

		}
		if ((direction & RIGHTMIDDLE) != RIGHTMIDDLE &&
			(direction & MIDDLETOP) != MIDDLETOP &&
			(direction & EDGE8) == EDGE8)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 3;
		}
		if ((direction & RIGHTMIDDLE) != RIGHTMIDDLE &&
			(direction & MIDDLEBOTTOM) != MIDDLEBOTTOM&&
			(direction & EDGE5) == EDGE5)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 4;
		}
		if ((direction & LEFTMIDDLE) != LEFTMIDDLE &&
			(direction & MIDDLEBOTTOM) != MIDDLEBOTTOM&&
			(direction & EDGE6) == EDGE6)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 4;
		}
		if (direction == ALLDIRECTION - RIGHTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 5;
		}
		if (direction == ALLDIRECTION - LEFTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 5;
		}
		if (direction == ALLDIRECTION - LEFTTOP)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 6;
		}
		if (direction == ALLDIRECTION - RIGHTTOP)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 6;
		}
		if (direction == ALLDIRECTION - LEFTTOP - RIGHTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = 6;
			_mapArr[arrX][arrY].sourY = 8;

		}
		if (direction == ALLDIRECTION - RIGHTTOP - LEFTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = 7;
			_mapArr[arrX][arrY].sourY = 8;

		}


		if (direction == ALLDIRECTION)
		{
			//===== 1/20 확률로 잔디 파기
			if (ranNum2) _mapArr[arrX][arrY].sourX = ranNum;
			else _mapArr[arrX][arrY].sourX = 4 + ranNum;

			_mapArr[arrX][arrY].sourY = 0;

		}

		/*
		if ((direction & EDGE1) == EDGE1)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 3;
		}
		if ((direction & EDGE2) == EDGE2)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 3;
		}
		if ((direction & EDGE3) == EDGE3)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 4;
		}
		if ((direction & EDGE4) == EDGE4)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 4;
		}
		if (direction == LEFT || direction == LEFT - LEFTTOP || direction == LEFT - LEFTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 1;
		}
		if (direction  == RIGHT || direction == RIGHT - RIGHTTOP || direction == RIGHT - RIGHTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 1;
		}
		if (direction  == UP || direction == UP - LEFTTOP || direction == UP - RIGHTTOP)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 2;
		}
		if (direction  == DOWN || direction == DOWN- LEFTBOTTOM|| direction == DOWN - RIGHTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 2;
		}
		if (direction == LEFTTOP)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 6;
		}
		if (direction == RIGHTTOP)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 6;
		}
		if (direction == LEFTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = 4 + ranNum;
			_mapArr[arrX][arrY].sourY = 5;
		}
		if (direction == RIGHTBOTTOM)
		{
			_mapArr[arrX][arrY].sourX = ranNum;
			_mapArr[arrX][arrY].sourY = 5;
		}

		*/
		//========= 옆 타일 정비
		if (arrX -1 >= 0 && arrX +1 < MAXTILE && arrY -1 >= 0 && arrY + 1 < MAXTILE)
		{
			//============= 왼 쪽 타 일 ============
			if (_mapArr[arrX - 1][arrY].tile != (TILE)_categorySmall)
			{
				if (_mapArr[arrX - 1][arrY].sourY == 0)
				{
					_mapArr[arrX - 1][arrY].sourX = 4 + ranNum;
					_mapArr[arrX - 1][arrY].sourY = 1;
				}
				if (_mapArr[arrX - 1][arrY].sourY == 2)
				{

					if (_mapArr[arrX - 1][arrY].sourX < 4)
					{
						_mapArr[arrX - 1][arrY].sourY = 3;
					}
					else
					{
						_mapArr[arrX - 1][arrY].sourY = 4;
					}
					_mapArr[arrX - 1][arrY].sourX = 4 + ranNum;

				}
			}
			//============= 오 른 쪽 타 일 ============
			if (_mapArr[arrX + 1][arrY].tile != (TILE)_categorySmall)
			{
				if (_mapArr[arrX + 1][arrY].sourY == 0)
				{
					_mapArr[arrX + 1][arrY].sourX = ranNum;
					_mapArr[arrX + 1][arrY].sourY = 1;
				}

				if (_mapArr[arrX + 1][arrY].sourY == 2)
				{
					if (_mapArr[arrX + 1][arrY].sourX < 4)
					{
						_mapArr[arrX + 1][arrY].sourY = 3;
					}
					else
					{
						_mapArr[arrX + 1][arrY].sourX = ranNum;
						_mapArr[arrX + 1][arrY].sourY = 4;
					}

				}

			}
			//============= 위 쪽 타 일 ============
			if (_mapArr[arrX][arrY - 1].tile != (TILE)_categorySmall)
			{
				if (_mapArr[arrX][arrY - 1].sourY == 0)
				{
					_mapArr[arrX][arrY - 1].sourX = 4 + ranNum;
					_mapArr[arrX][arrY - 1].sourY = 2;
				}
				else if (_mapArr[arrX][arrY - 1].sourY == 1)
				{
					_mapArr[arrX][arrY - 1].sourY = 4;
				}
			}
			//============= 아 래 쪽 타 일 ============
			if (_mapArr[arrX][arrY + 1].tile != (TILE)_categorySmall)
			{
				if (_mapArr[arrX][arrY + 1].sourY == 0)
				{
					_mapArr[arrX][arrY + 1].sourX = ranNum;
					_mapArr[arrX][arrY + 1].sourY = 2;
				}
				else if (_mapArr[arrX][arrY + 1].sourY == 1)
				{
					_mapArr[arrX][arrY + 1].sourY = 3;
				}
			}



		}
	}
}

void mapTool::setCor(void)
{

	_mouseArr.x = ((_ptMouse.x - 20) / TILESIZE) + (int)_mapX / TILESIZE;
	_mouseArr.y = ((_ptMouse.y - 20) / TILESIZE) + (int)_mapY / TILESIZE;
	
	sprintf(_msCorX, "%d", _mouseArr.x );
	sprintf(_msCorY, "%d", _mouseArr.y );
	
	if (_mouseArr.x != _saveX || _mouseArr.y != _saveY)
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (_saveX + i >= 0 && _saveY + j >= 0)
				{
					switch (_categoryLarge)
					{
					case CATE_NULL:
						break;
					case CATE_TILE:
						_mapArr[_saveX + i][_saveY + j].isChanged = false;
						break;
					case CATE_ROAD:
						_roadArr[_saveX + i][_saveY + j].isChanged = false;
						break;
					case CATE_BUILDING:
						break;
					case CATE_OBS:
						break;
					case CATE_UNIT:
						break;
					case CATE_ROOTING:
						break;
					case CATE_END:
						break;
					default:
						break;
					}
					
				}
			}
		}
	}
	

}

void mapTool::inputCommon(void)
{
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		_categoryLarge = CATE_TILE;
		_categorySmall = SMC_ZERO;
		_saveIndex.x = 0;
		_saveIndex.y = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		switch (_buildAttribute)
		{
		case TRUE:
			_buildAttribute = false;
			break;
		case FALSE:
			_buildAttribute = true;
			break;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (!_inputDelayX)
		{
			_mapX += 32;
			_inputDelayX = INPUTDELAY;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_inputDelayX)
		{
			_mapX -= 32;
			_inputDelayX = INPUTDELAY;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (!_inputDelayY)
		{
			_mapY -= 32;
			_inputDelayY = INPUTDELAY;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (!_inputDelayY)
		{
			_mapY += 32;
			_inputDelayY = INPUTDELAY;
		}
	}



	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{

		//=================== 마우스 움직일때 체인지 변수 변환 ============
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (_saveX - i >= 0 && _saveY - j >= 0)
				{
					_mapArr[_saveX - i][_saveY - j].isChanged = false;
				}

			}
		}
		for (int i = -1; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (_saveX - i >= 0 && _saveY - j >= 0)
				{
					_roadArr[_saveX + i][_saveY + j].isChanged = false;

				}

			}
		}
		//============================범위형 타일 깔기
		if (_area && _brushNum == 2)
		{
			_area = false;
			POINT point;
			if (_mouseArr.x != _saveAreaX && _mouseArr.y != _saveAreaY)
				for (int i = _saveAreaX; i != _mouseArr.x + (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX); )
				{
					for (int j = _saveAreaY; j != _mouseArr.y + (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY); )
					{
						point.x = i;
						point.y = j;

						_vSaveCor.push_back(point);



						j += (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY);
					}
					i += (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX);
				}
			else
			{
				if (_mouseArr.x == _saveAreaX && _mouseArr.y != _saveAreaY)
				{
					for (int i = _saveAreaY; i != _mouseArr.y + (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY); )
					{
						point.x = _mouseArr.x;
						point.y = i;

						_vSaveCor.push_back(point);



						i += (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY);
					}
				}
				else if (_mouseArr.y == _saveAreaY && _mouseArr.x != _saveAreaX)
				{
					for (int i = _saveAreaX; i != _mouseArr.x + (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX); )
					{
						point.x = i;
						point.y = _mouseArr.y;

						_vSaveCor.push_back(point);



						i += (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX);
					}

				}
				else
				{
					point.x = _mouseArr.x;
					point.y = _mouseArr.y;
					_vSaveCor.push_back(point);
				}
			}
		}
		

		for (_viSaveCor = _vSaveCor.begin(); _viSaveCor != _vSaveCor.end(); ++_viSaveCor)
		{
			_mapArr[_viSaveCor->x][_viSaveCor->y].tile = (TILE)_categorySmall;
		}

		for (_viSaveCor = _vSaveCor.begin(); _viSaveCor != _vSaveCor.end(); ++_viSaveCor)
		{
			setTile(_viSaveCor->x, _viSaveCor->y, (TILE)_categorySmall);
		}

		for (_viSaveCor = _vSaveCor.begin(); _viSaveCor != _vSaveCor.end(); ++_viSaveCor)
		{
			_mapArr[_viSaveCor->x][_viSaveCor->y].isChanged = false;
		}


		_vSaveCor.clear();

		//===================== 범위형 지우기 ===================
		if (_area  && _categorySmall == SMC_FOUR && _saveIndex.x == 2)
		{
			_area = false;

			if (_mouseArr.x != _saveAreaX && _mouseArr.y != _saveAreaY)
				for (int i = _saveAreaX; i != _mouseArr.x + (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX); )
				{
					for (int j = _saveAreaY; j != _mouseArr.y + (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY); )
					{

						deleteAll(i, j);
						j += (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY);
					}
					i += (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX);
				}
			else
			{
				if (_mouseArr.x == _saveAreaX && _mouseArr.y != _saveAreaY)
				{
					for (int i = _saveAreaY; i != _mouseArr.y + (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY); )
					{
						deleteAll(_mouseArr.x, i);



						i += (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY);
					}
				}
				else if (_mouseArr.y == _saveAreaY && _mouseArr.x != _saveAreaX)
				{
					for (int i = _saveAreaX; i != _mouseArr.x + (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX); )
					{
						deleteAll(i, _mouseArr.y);


						i += (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX);
					}

				}
				else
				{
					deleteAll(_mouseArr.x, _mouseArr.y);
				}
			}


		}

		//===================== 범위형 장애물 깔기
		if (_area && _categoryLarge == CATE_OBS && _categorySmall == SMC_THREE )
		{
			if (_mouseArr.x != _saveAreaX && _mouseArr.y != _saveAreaY)
				for (int i = _saveAreaX; i != _mouseArr.x + (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX); )
				{
					for (int j = _saveAreaY; j != _mouseArr.y + (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY); )
					{

						addObstacle(i, j);
						j += (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY);
					}
					i += (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX);
				}
			else
			{
				if (_mouseArr.x == _saveAreaX && _mouseArr.y != _saveAreaY)
				{
					for (int i = _saveAreaY; i != _mouseArr.y + (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY); )
					{
						addObstacle(_mouseArr.x, i);



						i += (_mouseArr.y - _saveAreaY) / abs(_mouseArr.y - _saveAreaY);
					}
				}
				else if (_mouseArr.y == _saveAreaY && _mouseArr.x != _saveAreaX)
				{
					for (int i = _saveAreaX; i != _mouseArr.x + (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX); )
					{
						addObstacle(i, _mouseArr.y);


						i += (_mouseArr.x - _saveAreaX) / abs(_mouseArr.x - _saveAreaX);
					}

				}
				else
				{
					addObstacle(_mouseArr.x, _mouseArr.y);
				}
			}
		}
	

		//================== 오브젝트 이동 뗄때======================
		
		//============ O B S T A C L E   M O V E =================
		if (_move && _categoryLarge == CATE_OBS && _ptMouse.x < 788)
		{
			bool overlap = false;
			int sizeX, sizeY;
			//금지 구역 이라면
			for (int i = _mouseArr.x - _remember.sizeX/2; i < _mouseArr.x - _remember.sizeX/2 + _remember.sizeX; i++)
			{
				for (int j = _mouseArr.y - _remember.sizeY/2; j < _mouseArr.y - _remember.sizeY/2 + _remember.sizeY; j++)
				{
					if (_mapArr[i][j].tile == TILE_WATER)
					{
						overlap = true;
						addObstacle(_remember.destX + _remember.sizeX/2,
							_remember.destY + _remember.sizeY/2);
					}
					if (overlap) break;
				}
				if (overlap) break;
			}

			if (!overlap)
			{
				addObstacle(_mouseArr.x, _mouseArr.y);
			}


			_move = false;
		}


		if (_move && _categoryLarge != CATE_OBS)
		{
			bool overlap = false;
			int sizeX, sizeY;
			//============== 금지 구역 이라면

			if (_ptMouse.x <= 788)
			{
				for (int i = _mouseArr.x - _remember.sizeX/2; i < _mouseArr.x + getRise(_remember.sizeX,2); i++)
				{
					for (int j = _mouseArr.y - _remember.sizeY/2; j < _mouseArr.y+ getRise(_remember.sizeY,2) ; j++)
					{
						if (_mapArr[i][j].tile == TILE_WATER) overlap = true;
						if (overlap) break;
					}
					if (overlap) break;
				}

				//=============== 이미 존재 한다면
				for (int i = _mouseArr.x - _remember.sizeX/2; i < _mouseArr.x + getRise(_remember.sizeX,2) ; i++)
				{
					for (int j = _mouseArr.y - _remember.sizeY/2; j < _mouseArr.y + getRise(_remember.sizeY,2); j++)
					{
						if (_buildArr[i][j].isClosed) overlap = true;

						if (overlap) break;
					}
					if (overlap) break;
				}
			}

			if (overlap)
			{
				switch (_remember.type)
				{
				case 0:
					addBuilding(_remember.destX + _remember.sizeX/2 ,
						_remember.destY + _remember.sizeY/2, _remember.camp);
					break;
				case 1:
					addBuilding(_remember.destX + _remember.sizeX/2,
							_remember.destY + _remember.sizeY/2, _remember.mine);
					break;
				case 2:
					addBuilding(_remember.destX - _remember.imgX ,
						_remember.destY - _remember.imgY, _remember.ev);
					break;
				}
			}
			
			//================ 그렇지 않다면
			if(!overlap)
			switch (_remember.type)
			{
			case 0:
				addBuilding(_mouseArr.x, _mouseArr.y, _remember.camp);
				break;
			case 1:
				addBuilding(_mouseArr.x, _mouseArr.y, _remember.mine);
				break;
			case 2:
				addBuilding(_mouseArr.x, _mouseArr.y, _remember.ev);
				break;
			}


			ZeroMemory(&_remember, sizeof(tagRemember));
			_remember.camp = CAMP_NULL;
			_remember.mine = MINE_NULL;
			_remember.ev = EV_NULL;
			_move = false;

		}
		

		//===================== 일단 지우자 ============
		_area = false;
		_move = false;
		//=================== P U L L   A R R O W ================
		if (!_foldMini)
		{
			if (IMAGEMANAGER->findImage("down")->getFrameX() == 1)
			{
				IMAGEMANAGER->findImage("down")->setFrameX(0);
				if (PtInRect(&RectMake(_miniMap.left - 30, WINSIZEY - 40, 21, 21), _ptMouse))
				{
					_page = 0;
					_foldMini = true;
				}

			}
		}
		if (_foldMini)
		{
			if (IMAGEMANAGER->findImage("up")->getFrameX() == 1)
			{
				IMAGEMANAGER->findImage("up")->setFrameX(0);
				if (PtInRect(&RectMake(_miniMap.left - 30, WINSIZEY - 40, 21, 21), _ptMouse))
				{
					_page = 0;
					_foldMini = false;
				}

			}
		}


		//===================== P A G E L E F T ============================
		if (IMAGEMANAGER->findImage("left")->getFrameX() == 1)
		{
			IMAGEMANAGER->findImage("left")->setFrameX(0);

			if (PtInRect(&RectMake(903, 463, 21, 21), _ptMouse))
			{
				if (_categoryLarge == CATE_OBS && _categorySmall == SMC_TWO&& _foldMini)
				{
					if (_page)
					{
						_saveIndex.x = 0;
						_saveIndex.y = 0;
					}
					_page--;
					if (_page < 0) _page = 0;
				}
			}

			
			if (PtInRect(&RectMake(903, 335, 21, 21), _ptMouse))
			{
				if (_page)
				{
					_saveIndex.x = 0;
					_saveIndex.y = 0;
				}
				_page--;
				if (_page < 0) _page = 0;

			}
		}

		//================= P A G E R I G H T ====================
		if (IMAGEMANAGER->findImage("right")->getFrameX() == 1)
		{
				int maxPage = 0;

			IMAGEMANAGER->findImage("right")->setFrameX(0);
			if (PtInRect(&RectMake(964, 463, 21, 21), _ptMouse))
			{
				if (_categoryLarge == CATE_OBS && _categorySmall == SMC_TWO && _foldMini)
				{
					maxPage = 3;

					if (_page != maxPage)
					{
						_saveIndex.x = 0;
						_saveIndex.y = 0;
					}
					_page++;

					if (_page > maxPage - 1) _page = maxPage - 1;

				}
			}

			if (PtInRect(&RectMake(964, 335, 21, 21), _ptMouse) && !_foldMini)
			{

				switch (_categoryLarge)
				{
				case CATE_TILE:
					maxPage = 3;
					break;
				case CATE_ROAD:
					maxPage = 1;
					break;
				case CATE_BUILDING:
					switch (_categorySmall)
					{
					case SMC_ZERO: maxPage = 1;
						break;
					case SMC_ONE: maxPage = 1;
						break;
					case SMC_TWO: maxPage = 2;
						break;
					case SMC_THREE:
						break;
					case SMC_FOUR:
						break;
					case SMC_FIVE:
						break;
					}
					break;
				case CATE_OBS:
					switch (_categorySmall)
					{
					case SMC_ZERO: maxPage = 1;
						break;
					case SMC_ONE: maxPage = 2;
						break;
					case SMC_TWO:  maxPage = 6;						
						break;
					case SMC_THREE: maxPage = 1;
						break;
					case SMC_FOUR: maxPage = 1;
						break;
					case SMC_FIVE: maxPage = 1;
						break;
					}
					break;

				case CATE_ROOTING:
					switch (_categorySmall)
					{
					case SMC_ZERO: maxPage = 1;
						break;
					case SMC_ONE: maxPage = 3;
						break;
					case SMC_TWO:  maxPage = 1;
						break;
					case SMC_THREE: maxPage = 1;
						break;
					case SMC_FOUR: maxPage = 1;
						break;
					case SMC_FIVE: maxPage = 1;
						break;

					}
					break;
				}
				if (_page != maxPage)
				{
					_saveIndex.x = 0;
					_saveIndex.y = 0;
				}
				_page++;

				if (_page > maxPage - 1) _page = maxPage - 1;

			}
		}

	}

}

void mapTool::inputOnMap(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _brushNum != 2)
	{
		if (_categoryLarge != CATE_OBS)
		{
			_saveX = _mouseArr.x;
			_saveY = _mouseArr.y;

		}

		//============== DRAW TILE=====================
		if (_categoryLarge == CATE_TILE && _categorySmall != SMC_NULL)
		{
			if (_brushNum == 255)
			{
				_mapArr[_mouseArr.x][_mouseArr.y].sourX = _saveIndex.x;
				_mapArr[_mouseArr.x][_mouseArr.y].sourY = _saveIndex.y;
				_mapArr[_mouseArr.x][_mouseArr.y].tile = (TILE)_categorySmall;

				switch (_categorySmall)
				{
				case SMC_ZERO:
					_mapArr[_mouseArr.x][_mouseArr.y].miniX = 0;
					_mapArr[_mouseArr.x][_mouseArr.y].miniY = 0;
					_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_GREEN;
					_mapArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("terrain_green");
					break;
				case SMC_ONE:
					_mapArr[_mouseArr.x][_mouseArr.y].miniX = 1;
					_mapArr[_mouseArr.x][_mouseArr.y].miniY = 0;
					_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_WATER;
					_mapArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("terrain_water");
					break;
				case SMC_TWO:
					_mapArr[_mouseArr.x][_mouseArr.y].miniX = 2;
					_mapArr[_mouseArr.x][_mouseArr.y].miniY = 0;
					_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_VOLCANO;
					_mapArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("terrain_volcano");

					break;
				}
			}
			if (_brushNum == 0)
			{
				POINT point;
				_mapArr[_mouseArr.x][_mouseArr.y].sourX = 0;
				_mapArr[_mouseArr.x][_mouseArr.y].sourY = 0;
				switch (_categorySmall)
				{
				case SMC_ZERO:
					_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_GREEN;
					_mapArr[_mouseArr.x][_mouseArr.y].img =
						IMAGEMANAGER->findImage("terrain_green");
					break;
				case SMC_ONE:
					_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_WATER;
					_mapArr[_mouseArr.x][_mouseArr.y].img =
						IMAGEMANAGER->findImage("terrain_water");

					break;
				case SMC_TWO:
					_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_VOLCANO;
					_mapArr[_mouseArr.x][_mouseArr.y].img =
						IMAGEMANAGER->findImage("terrain_volcano");
					break;
				}
				for (int i = _mouseArr.x -1; i <= _mouseArr.x + 1; i++)
				{
					for (int j = _mouseArr.y -1 ; j <= _mouseArr.y + 1; j++)
					{
						if (_mapArr[i][j].tile == (TILE)_categorySmall)
						{
							point.x = i;
							point.y = j;
							_vSaveCor.push_back(point);
						}
					}
				}
				point.x = _mouseArr.x;
				point.y = _mouseArr.y;
				_vSaveCor.push_back(point);



			}
			else if (_brushNum == 1)
			{

				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						POINT point;
						_mapArr[_mouseArr.x - i][_mouseArr.y - j].sourX = 0;
						_mapArr[_mouseArr.x - i][_mouseArr.y - j].sourY = 0;
						switch (_categorySmall)
						{
						case SMC_ZERO:
							_mapArr[_mouseArr.x - i][_mouseArr.y - j].tile = TILE_GREEN;
							_mapArr[_mouseArr.x - i][_mouseArr.y - j].img =
								IMAGEMANAGER->findImage("terrain_green");
							break;
						case SMC_ONE:
							_mapArr[_mouseArr.x - i][_mouseArr.y - j].tile = TILE_WATER;
							_mapArr[_mouseArr.x - i][_mouseArr.y - j].img =
								IMAGEMANAGER->findImage("terrain_water");

							break;
						case SMC_TWO:
							_mapArr[_mouseArr.x - i][_mouseArr.y - j].tile = TILE_VOLCANO;
							_mapArr[_mouseArr.x - i][_mouseArr.y - j].img =
								IMAGEMANAGER->findImage("terrain_volcano");
							break;
						}
						for (int i = _mouseArr.x - 2; i <= _mouseArr.x + 1; i++)
						{
							for (int j = _mouseArr.y - 2; j <= _mouseArr.y + 1; j++)
							{
								if (_mapArr[i][j].tile == (TILE)_categorySmall)
								{
									point.x = i;
									point.y = j;
									_vSaveCor.push_back(point);
								}
							}
						}

						point.x = _mouseArr.x - i;
						point.y = _mouseArr.y - j;
						_vSaveCor.push_back(point);

					}
				}
			}
		}

		else if (_categoryLarge == CATE_ROAD)
		{
			switch (_categorySmall)
			{
			case SMC_ZERO:
				break;
			case SMC_ONE:
				break;
			case SMC_TWO:
				break;
			case SMC_THREE:
				break;
			case SMC_FOUR:

				switch (_saveIndex.x)
				{
				case 0:
					deleteAll(_mouseArr.x, _mouseArr.y);
					break;
				case 1:
					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							deleteAll(_mouseArr.x - i, _mouseArr.y - j);
						}
					}
					break;
				case 2:
					break;

				}

				break;
			case SMC_FIVE:
				break;
			case SMC_NULL:
				break;
			}

			if (_brushNum == 0 && _categorySmall != SMC_FOUR)
			{
				setRoad(_mouseArr.x, _mouseArr.y, (ROAD)_categorySmall);

				for (int i = -1; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						if (!(i == 0 && j == 0) && _roadArr[_mouseArr.x + i][_mouseArr.y + j].road == (ROAD)_categorySmall)
							setRoad(_mouseArr.x + i, _mouseArr.y + j, (ROAD)_categorySmall);
					}
				}
			}
			else if (_brushNum == 255 )
			{
				_roadArr[_mouseArr.x][_mouseArr.y].road = (ROAD)_categorySmall;
				switch (_categorySmall)
				{
				case SMC_ZERO:
					_roadArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("road_normal");
					_roadArr[_mouseArr.x][_mouseArr.y].sourX = _saveIndex.x;
					_roadArr[_mouseArr.x][_mouseArr.y].sourY = _saveIndex.y;
					_roadArr[_mouseArr.x][_mouseArr.y].isChanged = true;
					break;
				case SMC_ONE:
					_roadArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("road_rock");
					_roadArr[_mouseArr.x][_mouseArr.y].sourX = _saveIndex.x;
					_roadArr[_mouseArr.x][_mouseArr.y].sourY = _saveIndex.y;
					_roadArr[_mouseArr.x][_mouseArr.y].isChanged = true;
					break;
				case SMC_TWO:
					_roadArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("road_river");
					_roadArr[_mouseArr.x][_mouseArr.y].sourX = _saveIndex.x;
					_roadArr[_mouseArr.x][_mouseArr.y].sourY = _saveIndex.y;
					_roadArr[_mouseArr.x][_mouseArr.y].isChanged = true;
					break;
				case SMC_FOUR:
					break;
				case SMC_FIVE:
					break;
				case SMC_NULL:
					break;
				}
			}
		}

		else if (_categoryLarge == CATE_BUILDING)
		{
			switch (_categorySmall)
			{
			case SMC_ZERO:
				break;
			case SMC_ONE:
				break;
			case SMC_TWO:
				break;
			case SMC_THREE:
				break;
			case SMC_FOUR:
				switch (_saveIndex.x)
				{
				case 0:
					deleteAll(_mouseArr.x, _mouseArr.y);
				break;
				case 1:
					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							deleteAll(_mouseArr.x - i, _mouseArr.y - j);
						}
					}
				break;
				case 2:
					break;
				}
			
				break;
			case SMC_FIVE:
				break;
			}
		}

		else if (_categoryLarge == CATE_OBS)
		{
			switch (_categorySmall)
			{
			case SMC_ZERO: 
				if (_mouseArr.x != _saveX || _mouseArr.y != _saveY)
				{
					addObstacle(_mouseArr.x, _mouseArr.y);
					_saveX = _mouseArr.x;
					_saveY = _mouseArr.y;
				}
				break;
			case SMC_ONE:
				if (_mouseArr.x != _saveX || _mouseArr.y != _saveY)
				{
					addObstacle(_mouseArr.x, _mouseArr.y);
					_saveX = _mouseArr.x;
					_saveY = _mouseArr.y;
				}
				break;
			case SMC_TWO:
				if (_mouseArr.x != _saveX || _mouseArr.y != _saveY)
				{
					addObstacle(_mouseArr.x, _mouseArr.y);
					_saveX = _mouseArr.x;
					_saveY = _mouseArr.y;
				}
				break;
			case SMC_THREE:
				break;
			case SMC_FOUR:
				switch (_saveIndex.x)
				{
				case 0:
					deleteAll(_mouseArr.x, _mouseArr.y);
					break;
				case 1:
					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							deleteAll(_mouseArr.x - i, _mouseArr.y - j);
						}
					}
					break;
				case 2:
					break;
				}
				break;
			case SMC_FIVE:
				break;
			}
		}
	
		else if (_categoryLarge == CATE_ROOTING)
		{

		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//================ Draw Object =====================
		switch (_categoryLarge)
		{
		case CATE_TILE:
			break;
		case CATE_ROAD:
			break;
		case CATE_BUILDING:
			switch (_categorySmall)
			{
			case SMC_ZERO:
				addBuilding(_mouseArr.x, _mouseArr.y, CAMP(_saveIndex.x));
				break;
			case SMC_ONE:
				addBuilding(_mouseArr.x, _mouseArr.y, MINE(_saveIndex.x + _saveIndex.y * 4));
				break;
			case SMC_TWO:
				if(_page == 0 && !_foldMini)
				addBuilding(_mouseArr.x, _mouseArr.y, EVENT(_saveIndex.x + _saveIndex.y * 4));
				else if(_page == 1 && !_foldMini)
				addBuilding(_mouseArr.x, _mouseArr.y, EVENT(8+ _saveIndex.x + _saveIndex.y * 4));
				else if(_foldMini)
				addBuilding(_mouseArr.x, _mouseArr.y, EVENT(_saveIndex.x + _saveIndex.y * 4));

				break;
			case SMC_THREE:
				break;
			case SMC_FOUR:
				break;
			case SMC_FIVE:

				//================= 오브젝트 이동 누를때============
				for ( _viBuild = _vBuild.begin(); _viBuild != _vBuild.end(); )
				{
					if (_viBuild->destX <= _mouseArr.x && _viBuild->destX + _viBuild->sizeX > _mouseArr.x &&
						_viBuild->destY <= _mouseArr.y && _viBuild->destY + _viBuild->sizeY > _mouseArr.y)
					{
						_move = true;

						if (_viBuild->camp != CAMP_NULL) _remember.type = 0;
						if (_viBuild->mine != MINE_NULL) _remember.type = 1;
						if (_viBuild->ev != EV_NULL) _remember.type = 2;
						
						switch (_remember.type)
						{
						case 0: _remember.camp = _viBuild->camp;
						break;
						case 1: _remember.mine = _viBuild->mine;
						break;
						case 2: _remember.ev = _viBuild->ev;
						break;
						}
						_remember.img = _viBuild->img;
						_remember.sizeX = _viBuild->sizeX;
						_remember.sizeY = _viBuild->sizeY;
						_remember.destX = _viBuild->destX;
						_remember.destY = _viBuild->destY;
						_remember.imgX = _viBuild->imgX;
						_remember.imgY = _viBuild->imgY;
						_remember.sourX = _viBuild->sourX;
						_remember.sourY = _viBuild->sourY;
						_remember.miniX = _viBuild->miniX;


						deleteAll(_mouseArr.x, _mouseArr.y);
						break;

					}
					else ++_viBuild;
				}
				break;
			}
			break;
		case CATE_OBS:
			switch (_categorySmall)
			{
			case SMC_ZERO:
				break;
			case SMC_ONE:
				break;
			case SMC_TWO:
				break;
			case SMC_THREE:
				_saveAreaX = _mouseArr.x;
				_saveAreaY = _mouseArr.y;
				_area = true;
				break;
			case SMC_FOUR:
				break;
			case SMC_FIVE:
			{
				//================= 오브젝트 이동 누를때============
				for (_viBuild = _vBuild.begin(); _viBuild != _vBuild.end(); )
				{
					if (_viBuild->destX <= _mouseArr.x && _viBuild->destX + _viBuild->sizeX > _mouseArr.x &&
						_viBuild->destY <= _mouseArr.y && _viBuild->destY + _viBuild->sizeY > _mouseArr.y)
					{
						_move = true;
						
						ZeroMemory(&_remember, sizeof(tagRemember));

						_remember.camp = CAMP_NULL;
						_remember.mine = MINE_NULL;
						_remember.ev = EV_NULL;

						_remember.img = _viBuild->img;
						_remember.imgShadow = _viBuild->imgShadow;
						_remember.sizeX = _viBuild->sizeX;
						_remember.sizeY = _viBuild->sizeY;
						_remember.destX = _viBuild->destX;
						_remember.destY = _viBuild->destY;
						_remember.imgX = _viBuild->imgX;
						_remember.imgY = _viBuild->imgY;
						_remember.sourX = _viBuild->sourX;
						_remember.sourY = _viBuild->sourY;




						deleteAll(_mouseArr.x, _mouseArr.y);
						break;

					}
					else ++_viBuild;
				}

			}
				break;
			}
		break;
		
		case CATE_ROOTING:
			switch (_categorySmall)
			{
			case SMC_ZERO:
				addRooting(_mouseArr.x, _mouseArr.y);
				break;
			case SMC_ONE:
				addRooting(_mouseArr.x, _mouseArr.y);
				break;
			case SMC_TWO:

				break;
			case SMC_THREE:

				break;
			case SMC_FOUR:

				break;
			case SMC_FIVE:

				break;
			}
		break;

		}



		//================= 범위 그리기 ==============
		if (_brushNum == 2  && !_area)
		{
			_area = true;
			_saveAreaX = _mouseArr.x;
			_saveAreaY = _mouseArr.y;
		}


		//================ 범위 지우기 ================
		if (_categorySmall == SMC_FOUR && _saveIndex.x == 2&& !_area)
		{
			_area = true;
			_saveAreaX = _mouseArr.x;
			_saveAreaY = _mouseArr.y;
		}

	}


}

void mapTool::inputOnUI(void)
{


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{

		//================= MINI MAP CONTROL=================

		if (!_foldMini)
			if (PtInRect(&_miniMap, _ptMouse))
			{
				_mapX = (_ptMouse.x - 12 * MINISIZE - _miniMap.left) / MINISIZE * TILESIZE;
				_mapY = (_ptMouse.y - 9 * MINISIZE - _miniMap.top) / MINISIZE * TILESIZE;

				if (_mapX < 0) _mapX = 0;
				if (_mapX > TILESIZE * (MAXTILE - 24)) _mapX = TILESIZE *  (MAXTILE - 24);
				if (_mapY < 0) _mapY = 0;
				if (_mapY > TILESIZE *  (MAXTILE - 18)) _mapY = TILESIZE *  (MAXTILE - 18);

			}



	}
	

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		
		
		//================= LARGE CATEGORY SELECT =====================
		if (PtInRect(&_largeCategory, _ptMouse))
		{
			_page = 0;
			_brushNum = 255;
			_categorySmall = SMC_NULL;
			if (_ptMouse.x < _largeCategory.left + 32) _categoryLarge = CATE_TILE;
			else if (_ptMouse.x >= _largeCategory.left + 42 && _ptMouse.x < _largeCategory.left + 74) _categoryLarge = CATE_ROAD;
			else if (_ptMouse.x >= _largeCategory.left + 84 && _ptMouse.x < _largeCategory.left + 116) _categoryLarge = CATE_BUILDING;
			else if (_ptMouse.x >= _largeCategory.left + 126 && _ptMouse.x <_largeCategory.left + 158) _categoryLarge = CATE_OBS;
			else if (_ptMouse.x >= _largeCategory.left + 168 && _ptMouse.x <_largeCategory.left + 200) _categoryLarge = CATE_ROOTING;
			else if (_ptMouse.x >= _largeCategory.left + 210 && _ptMouse.y <_largeCategory.left + 242) _categoryLarge = CATE_UNIT;
		}

		//================== SMALL CATEGORY SELECT =======================
		if (PtInRect(&_smallCategory, _ptMouse))
		{
			_page = 0;
			_saveIndex.x = 0;
			_saveIndex.y = 0;
			switch (_categoryLarge)
			{
			case CATE_NULL:
				break;
			case CATE_TILE:
			{
				if (_ptMouse.x < _smallCategory.left + 32) _categorySmall = SMC_ZERO;
				else if (_ptMouse.x >= _smallCategory.left + 42 && _ptMouse.x < _smallCategory.left + 74) _categorySmall = SMC_ONE;
				else if (_ptMouse.x >= _smallCategory.left + 84 && _ptMouse.x < _smallCategory.left + 116) _categorySmall = SMC_TWO;

			}
			break;
			
			case CATE_ROAD:
			{
				if (_ptMouse.x < _smallCategory.left + 32) _categorySmall = SMC_ZERO;
				else if (_ptMouse.x >= _smallCategory.left + 42 && _ptMouse.x < _smallCategory.left + 74) _categorySmall = SMC_ONE;
				else if (_ptMouse.x >= _smallCategory.left + 84 && _ptMouse.x < _smallCategory.left + 116) _categorySmall = SMC_TWO;
				else if (_ptMouse.x >= _smallCategory.right - 32 && _ptMouse.x < _smallCategory.right) _categorySmall = SMC_FOUR;

			}
			break;
			
			case CATE_BUILDING:
			{
				if (_ptMouse.x < _smallCategory.left + 32) _categorySmall = SMC_ZERO;
				else if (_ptMouse.x >= _smallCategory.left + 42 && _ptMouse.x < _smallCategory.left + 74) _categorySmall = SMC_ONE;
				else if (_ptMouse.x >= _smallCategory.left + 84 && _ptMouse.x < _smallCategory.left + 116) _categorySmall = SMC_TWO;
				else if (_ptMouse.x >= _smallCategory.right - 74 && _ptMouse.x < _smallCategory.right - 42) _categorySmall = SMC_FOUR;
				else if (_ptMouse.x >= _smallCategory.right - 32 && _ptMouse.x < _smallCategory.right) _categorySmall = SMC_FIVE;
			}
			break;

			case CATE_OBS:
			{
				if (_ptMouse.x < _smallCategory.left + 32) _categorySmall = SMC_ZERO;
				else if (_ptMouse.x >= _smallCategory.left + 42 && _ptMouse.x < _smallCategory.left + 74) _categorySmall = SMC_ONE;
				else if (_ptMouse.x >= _smallCategory.left + 84 && _ptMouse.x < _smallCategory.left + 116) _categorySmall = SMC_TWO;
				else if (_ptMouse.x >= _smallCategory.left + 126 && _ptMouse.x < _smallCategory.left + 158) _categorySmall = SMC_THREE;
				else if (_ptMouse.x >= _smallCategory.right - 74 && _ptMouse.x < _smallCategory.right - 42) _categorySmall = SMC_FOUR;
				else if (_ptMouse.x >= _smallCategory.right - 32 && _ptMouse.x < _smallCategory.right) _categorySmall = SMC_FIVE;
			}
			break;

			case CATE_ROOTING:
			{
				if (_ptMouse.x < _smallCategory.left + 32) _categorySmall = SMC_ZERO;
				else if (_ptMouse.x >= _smallCategory.left + 42 && _ptMouse.x < _smallCategory.left + 74) _categorySmall = SMC_ONE;
				else if (_ptMouse.x >= _smallCategory.right - 74 && _ptMouse.x < _smallCategory.right - 42) _categorySmall = SMC_FOUR;
				else if (_ptMouse.x >= _smallCategory.right - 32 && _ptMouse.x < _smallCategory.right) _categorySmall = SMC_FIVE;
			}
				break;

			case CATE_UNIT:
				break;
			case CATE_END:
				break;
			default:
				break;
			}
		}

		
		
		//================== C O N T E N T S ======================

		//================== B R U S H ============================
		if ((_categoryLarge == CATE_TILE || _categoryLarge == CATE_ROAD) &&
			_categorySmall != SMC_NULL &&  PtInRect(&RectMake(
				_smallCategory.left, _smallCategory.bottom + 10, 16, 16), _ptMouse))
		{
			_brushNum = 0;
		}
		else if (_categoryLarge == CATE_TILE && _categorySmall != SMC_NULL && PtInRect(&RectMake(
			_smallCategory.left, _smallCategory.bottom + 36, 16, 16), _ptMouse))
		{
			_brushNum = 1;
		}
		else if (_categoryLarge == CATE_TILE && _categorySmall != SMC_NULL && PtInRect(&RectMake(
			_smallCategory.left, _smallCategory.bottom + 62, 16, 16), _ptMouse))
		{
			_brushNum = 2;
		}



		//=============== 자동 그리기 아니면 인덱스 날려버리기
		if (_brushNum != 255)
		{
			_saveIndex.x = 15;
			_saveIndex.y = 15;
		}

		//================= P U S H   A R R O W ===================

		if (!_foldMini && PtInRect(&RectMake(_miniMap.left - 30, WINSIZEY - 40, 21, 21), _ptMouse))
		{
			IMAGEMANAGER->findImage("down")->setFrameX(1);
		}
		if (_foldMini && PtInRect(&RectMake(_miniMap.left - 30, WINSIZEY - 40, 21, 21), _ptMouse))
		{
			IMAGEMANAGER->findImage("up")->setFrameX(1);
		}
		if (PtInRect(&RectMake(903, 335, 21, 21), _ptMouse))
		{
			IMAGEMANAGER->findImage("left")->setFrameX(1);
		}
		if (PtInRect(&RectMake(964, 335, 21, 21), _ptMouse))
		{
			IMAGEMANAGER->findImage("right")->setFrameX(1);
		}

		if (PtInRect(&RectMake(964, 463, 21, 21), _ptMouse) && _foldMini)
		{
			IMAGEMANAGER->findImage("right")->setFrameX(1);
		}
		if (PtInRect(&RectMake(903, 463, 21, 21), _ptMouse) && _foldMini)
		{
			IMAGEMANAGER->findImage("left")->setFrameX(1);
		}


		//================ C O N T E N T S   B O X ====================
		//================ S E T T I N G   I N D E X =====================
		if (PtInRect(&RectMake(_contents.left - 10, _contents.top, 256, 288), _ptMouse))
		{
			if ((_categoryLarge == CATE_TILE || _categoryLarge == CATE_ROAD) && _ptMouse.x >= _contents.left)
			{
				if (!_foldMini && _ptMouse.y <= _contents.top + 128)
				{
					if (_page != 2)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE;
						_saveIndex.y = _page * 4 + (_ptMouse.y - _contents.top) / TILESIZE;
					}
					else if (_page == 2 && _ptMouse.y <= _contents.top + 32)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE;
						_saveIndex.y = _page * 4 + (_ptMouse.y - _contents.top) / TILESIZE;
					}


				}
				else if (_foldMini)
				{
					_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE;
					_saveIndex.y = (_ptMouse.y - _contents.top) / TILESIZE;
				}
			}
			if (_categoryLarge == CATE_BUILDING)
			{
				switch (_categorySmall)
				{
				case SMC_ZERO:

					if (!_foldMini && _ptMouse.y <= _contents.top + 128)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left + 10) / 128;
						_saveIndex.y = 0;

					}
					else if (_foldMini)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left + 10) / 128;
						_saveIndex.y = 0;
					}

					break;
				case SMC_ONE:
					if (_ptMouse.y <= _contents.top + 128)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left + 10) / 64;
						_saveIndex.y = (_ptMouse.y - _contents.top)/64 ;

					}

					break;
				case SMC_TWO:
					
					if (_ptMouse.y <= _contents.top + 128 && !_foldMini)
					{ 
						_saveIndex.x = (_ptMouse.x - _contents.left + 10) / 64;
						_saveIndex.y = (_ptMouse.y - _contents.top) / 64;

					}
					if (_ptMouse.y <= _contents.top + 192 && _foldMini)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left + 10) / 64;
						_saveIndex.y = (_ptMouse.y - _contents.top) / 64;
					}

					break;
				case SMC_THREE:
					break;
				case SMC_FOUR:

					if (_ptMouse.y <= _contents.top + 128)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE;
						_saveIndex.y = (_ptMouse.y - _contents.top) / TILESIZE;
					}

					break;
				case SMC_FIVE:
					break;
				case SMC_NULL:
					break;
				}
			}
			if (_categoryLarge == CATE_OBS)
			{
				switch (_categorySmall)
				{
				case SMC_ZERO:
				{
					if (_ptMouse.y < _contents.top + 128)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE;
						_saveIndex.y = (_ptMouse.y - _contents.top) / TILESIZE;
					}

				}
				break;
				
				case SMC_ONE:
				{
					switch (_foldMini)
					{
					case TRUE:
						if (_ptMouse.y < _contents.top + 256)
						{
							_saveIndex.x = (_ptMouse.x - _contents.left) / (TILESIZE*2);
							_saveIndex.y = (_ptMouse.y - _contents.top) / (TILESIZE*2);
						}
						break;
					case FALSE:
						if (_ptMouse.y < _contents.top + 128)
						{
							_saveIndex.x = (_ptMouse.x - _contents.left) / (TILESIZE*2);
							_saveIndex.y = (_ptMouse.y - _contents.top) / (TILESIZE*2);
						}
						break;
					}

				}
				break;
				
				case SMC_TWO:
				{
					switch (_foldMini)
					{
					case TRUE:
						if (_ptMouse.y < _contents.top + 256)
						{
							_saveIndex.x = (_ptMouse.x - _contents.left) / (TILESIZE * 4);
							_saveIndex.y = (_ptMouse.y - _contents.top) / (TILESIZE * 4);
						}

						break;
					case FALSE:
						if (_ptMouse.y < _contents.top + 128)
						{
							_saveIndex.x = (_ptMouse.x - _contents.left) / (TILESIZE * 4);
							_saveIndex.y = (_ptMouse.y - _contents.top) / (TILESIZE * 4);
						}
						break;
					}

				}
				break;
				
				case SMC_THREE:
				
				break;
				
				case SMC_FOUR:
					if (_ptMouse.y < _contents.top + 128)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE ;
						_saveIndex.y = (_ptMouse.y - _contents.top) / TILESIZE ;
					}
				break;

				case SMC_FIVE:
				break;
				}
			}
			if (_categoryLarge == CATE_ROOTING)
			{
				switch (_categorySmall)
				{
				case SMC_ZERO:

					if (_ptMouse.y < _contents.top + 128)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE/2;
						_saveIndex.y = (_ptMouse.y - _contents.top) / TILESIZE;
					}

					break;
				case SMC_ONE:
					if (_ptMouse.y < _contents.top + 128)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left + 10) / TILESIZE / 2;
						_saveIndex.y = (_ptMouse.y - _contents.top) / TILESIZE / 2;
					}

					break;
				case SMC_TWO:
					break;
				case SMC_THREE:
					break;
				case SMC_FOUR:
					if (_ptMouse.y < _contents.top + 128)
					{
						_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE;
						_saveIndex.y = (_ptMouse.y - _contents.top) / TILESIZE;
					}
					break;
				case SMC_FIVE:
					break;
				}
			}

			//================ 브러시 날리기
			if(!PtInRect(&_miniMap,_ptMouse) && _ptMouse.x >= _contents.left) _brushNum = 255;
			 

			//========= 지우개 일때 다른것 건들지 않기
			if (_categorySmall == SMC_FOUR)
			{
				if (_saveIndex.x > 2 || _saveIndex.y > 0)
				{
					_saveIndex.x = 15;
					_saveIndex.y = 15;
				}

			}
		}
		
	}
	

}

void mapTool::loadImg(void)
{
	//================ T E R R A I N ==========================
	IMAGEMANAGER->addFrameImage("terrain", "image/mapTool/terrain_idle.bmp", 32, 32,1,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_green", "image/mapTool/terrain_green.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_water", "image/mapTool/terrain_test.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_volcano", "image/mapTool/terrain_volcano.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));

	//================ R O A D =================================
	IMAGEMANAGER->addFrameImage("road_normal", "image/mapTool/road_normal.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("road_rock", "image/mapTool/road_rock.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("road_river", "image/mapTool/road_river.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));

	//================ B U I L D I N G =========================
	//============ C A M P 
	IMAGEMANAGER->addFrameImage("building_castle", "image/mapTool/camp_castle.bmp", 576, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("building_castle_shadow", "image/mapTool/camp_castle_shadow.bmp", 576, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("building_dungeon", "image/mapTool/camp_dungeon.bmp", 576, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("building_dungeon_shadow", "image/mapTool/camp_dungeon_shadow.bmp", 576, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("building_castle_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("building_dungeon_shadow")->AlphaInit();
	IMAGEMANAGER->addImage("point_castle", "image/mapTool/point_castle.bmp", 192, 192, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("point_dungeon", "image/mapTool/point_dungeon.bmp", 192, 192, true, RGB(255, 0, 255));

	//============ MINE
	IMAGEMANAGER->addFrameImage("mine_gold", "image/mapTool/mine/mine_gold.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_crystal", "image/mapTool/mine/mine_crystal.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_wood", "image/mapTool/mine/mine_wood.bmp", 160, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_iron", "image/mapTool/mine/mine_iron.bmp", 96, 64, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_sulfur", "image/mapTool/mine/mine_sulfur.bmp", 96, 64, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_mercury", "image/mapTool/mine/mine_mercury.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_gem", "image/mapTool/mine/mine_gem.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_gold_shadow", "image/mapTool/mine/mine_gold_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_crystal_shadow", "image/mapTool/mine/mine_crystal_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_wood_shadow", "image/mapTool/mine/mine_wood_shadow.bmp", 160, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_sulfur_shadow", "image/mapTool/mine/mine_sulfur_shadow.bmp", 96, 64, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_mercury_shadow", "image/mapTool/mine/mine_mercury_shadow.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_gem_shadow", "image/mapTool/mine/mine_gem_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("mine_gold_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_crystal_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_wood_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_sulfur_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_mercury_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_gem_shadow")->AlphaInit();
	IMAGEMANAGER->addImage("point_mine", "image/mapTool/point_mine.bmp", 96, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("point_wood", "image/mapTool/point_wood.bmp", 160, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("point_mercury", "image/mapTool/point_mercury.bmp", 96, 96, true, RGB(255, 0, 255));

	//============= E V E N T 
	IMAGEMANAGER->addFrameImage("ev_lvlup", "image/mapTool/ev/ev_lvlup.bmp", 96, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_physical", "image/mapTool/ev/ev_physical.bmp", 96, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_magical", "image/mapTool/ev/ev_magical.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_skill", "image/mapTool/ev/ev_skill.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_magic", "image/mapTool/ev/ev_magic.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_luck", "image/mapTool/ev/ev_luck.bmp", 768, 32, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_morale", "image/mapTool/ev/ev_morale.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_explore", "image/mapTool/ev/ev_explore.bmp", 64, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_movement", "image/mapTool/ev/ev_movement.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_resource", "image/mapTool/ev/ev_resource.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("ev_lvlup_shadow", "image/mapTool/ev/ev_lvlup_shadow.bmp", 96, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_physical_shadow", "image/mapTool/ev/ev_physical_shadow.bmp", 96, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_magical_shadow", "image/mapTool/ev/ev_magical_shadow.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_skill_shadow", "image/mapTool/ev/ev_skill_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_magic_shadow", "image/mapTool/ev/ev_magic_shadow.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_luck_shadow", "image/mapTool/ev/ev_luck_shadow.bmp", 768, 32, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_morale_shadow", "image/mapTool/ev/ev_morale_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_explore_shadow", "image/mapTool/ev/ev_explore_shadow.bmp", 64, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_movement_shadow", "image/mapTool/ev/ev_movement_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_resource_shadow", "image/mapTool/ev/ev_resource_shadow.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->findImage("ev_lvlup_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_physical_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_magical_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_skill_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_magic_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_luck_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_morale_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_explore_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_movement_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_resource_shadow")->AlphaInit();

	//================ O B S T A C L E =====================
	IMAGEMANAGER->addFrameImage("obstacle_1x1", "image/mapTool/1x1/1x1_obstacle.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_2x2", "image/mapTool/1x1/2x2_obstacle.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_4x4", "image/mapTool/1x1/4x4_obstacle.bmp", 256, 512, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_6x4", "image/mapTool/1x1/6x4_obstacle.bmp", 192, 256, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_1x1_shadow", "image/mapTool/1x1/1x1_obstacle_shadow.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_2x2_shadow", "image/mapTool/1x1/2x2_obstacle_shadow.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_4x4_shadow", "image/mapTool/1x1/4x4_obstacle_shadow.bmp", 256, 512, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_6x4_shadow", "image/mapTool/1x1/6x4_obstacle_shadow.bmp", 192, 256, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->findImage("obstacle_1x1_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("obstacle_2x2_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("obstacle_4x4_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("obstacle_6x4_shadow")->AlphaInit();

	//==================== R O O T I N G ====================
	IMAGEMANAGER->addFrameImage("resources", "image/mapTool/resource/resource.bmp", 192, 96, 3, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("resources_shadow", "image/mapTool/resource/resource_shadow.bmp", 192, 96, 3, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("resources_shadow")->AlphaInit();
	IMAGEMANAGER->addFrameImage("artifact_weapon", "image/mapTool/resource/artifact_weapon.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("artifact_shield", "image/mapTool/resource/artifact_shield.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("artifact_armor", "image/mapTool/resource/artifact_armor.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("artifact_helmet", "image/mapTool/resource/artifact_helmet.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("artifact_acc", "image/mapTool/resource/artifact_acc.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));

	//================ M I N I   M A P =====================
	IMAGEMANAGER->addImage("miniView72", "image/mapTool/miniView72.bmp", 72, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("miniView36", "image/mapTool/miniView36.bmp", 144, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap", "image/mapTool/miniRECT.bmp", 220, 220, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniTerrain72", "image/mapTool/miniTerrain72.bmp", 15, 15, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniTerrain36", "image/mapTool/miniTerrain36.bmp", 30, 30, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniBuilding72", "image/mapTool/miniBuilding72.bmp", 54, 18, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniBuilding36", "image/mapTool/miniBuilding36.bmp", 108, 36, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniObstacle72", "image/mapTool/1x1/miniObstacle72.bmp", 60, 15, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniObstacle36", "image/mapTool/1x1/miniObstacle36.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("miniObstacle72")->AlphaInit();
	IMAGEMANAGER->findImage("miniObstacle36")->AlphaInit();

	//================ U S E R   I N T E R F A C E =================
	IMAGEMANAGER->addImage("mapToolUI", "image/ui/mapToolUI.bmp", 312, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("mapToolUI")->setX(788);
	IMAGEMANAGER->addImage("mapToolMark", "image/ui/mapToolMark.bmp", 300, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("mapToolMark")->setX(796);
	IMAGEMANAGER->findImage("mapToolMark")->setY(2);

	//=============== C U R S O R =========================
	IMAGEMANAGER->addImage("select", "image/mapTool/selectRect.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("select2", "image/mapTool/selectRect2.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("width", "image/mapTool/line_width.bmp", 768, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("height", "image/mapTool/line_height.bmp", 2, 576, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("closed", "image/mapTool/closedArea.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("closed")->AlphaInit();
	IMAGEMANAGER->findImage("closed")->setAlphaSource(50);
	IMAGEMANAGER->addImage("enter", "image/mapTool/enter.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("enter")->AlphaInit();

	//=============== B U T T O N =========================
	//==================================== T I L E 
	IMAGEMANAGER->addFrameImage("tileButton", "image/mapTool/tileButton.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("roadButton", "image/mapTool/roadButton.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_green", "image/mapTool/button_green.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_water", "image/mapTool/button_water.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_volcano", "image/mapTool/button_volcano.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_terrain_green", "image/mapTool/button_terrain_green.bmp", 256, 384, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_terrain_water", "image/mapTool/button_terrain_water.bmp", 256, 384, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_terrain_volcano", "image/mapTool/button_terrain_volcano.bmp", 256, 384, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_terrain_green_large", "image/mapTool/button_terrain_green_L.bmp", 256, 288, true, RGB(255, 0, 255 ));
	IMAGEMANAGER->addImage("button_terrain_water_large", "image/mapTool/button_terrain_water_large.bmp", 256, 288, true, RGB(255, 0, 255 ));
	IMAGEMANAGER->addImage("button_terrain_volcano_large", "image/mapTool/button_terrain_volcano_large.bmp", 256, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("push", "image/mapTool/button_push.bmp", 32, 32, true, RGB(255, 0, 255));
	
	//==================================== R O A D 
	IMAGEMANAGER->addFrameImage("button_road_normal", "image/mapTool/button_road_normal.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_normal", "image/mapTool/button_normal.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_road_rock", "image/mapTool/button_road_rock.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_rock", "image/mapTool/button_rock.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_road_river", "image/mapTool/button_road_river.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_river", "image/mapTool/button_river.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

	//==================================== C A M P 
	IMAGEMANAGER->addFrameImage("button_castle", "image/mapTool/button_castle.bmp", 256, 128, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_dungeon", "image/mapTool/button_dungeon.bmp", 256, 128, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("buildingButton", "image/mapTool/buildingButton.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_camp", "image/mapTool/button_camp.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

	//==================================== M I N E
	IMAGEMANAGER->addFrameImage("button_mine", "image/mapTool/button_mine.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_gold","image/mapTool/button_gold.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_crystal","image/mapTool/button_crystal.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_wood","image/mapTool/button_wood.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_iron","image/mapTool/button_iron.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_sulfur","image/mapTool/button_sulfur.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_mercury","image/mapTool/button_mercury.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_gem","image/mapTool/button_gem.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	
	//==================================== E V E N T 
	IMAGEMANAGER->addFrameImage("button_ev", "image/mapTool/button_ev.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_lvlup", "image/mapTool/button_lvlup.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_physical", "image/mapTool/button_physical.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_magical", "image/mapTool/button_magical.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_skill", "image/mapTool/button_skill.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_magic", "image/mapTool/button_magic.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_luck", "image/mapTool/button_luck.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_morale", "image/mapTool/button_morale.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_explore", "image/mapTool/button_explore.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_movement", "image/mapTool/button_movement.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_resource", "image/mapTool/button_resource.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	
	//==================================== O B S T A C L E
	IMAGEMANAGER->addFrameImage("button_obstacle", "image/mapTool/1x1/button_obstacle.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_1x1", "image/mapTool/1x1/button_1x1.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_2x2", "image/mapTool/1x1/button_2x2.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_4x4", "image/mapTool/1x1/button_4x4.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_A", "image/mapTool/1x1/button_A.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_1x1", "image/mapTool/1x1/1x1_obstacle.bmp", 256, 128, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_2x2", "image/mapTool/1x1/2x2_obstacle.bmp", 256, 256, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_4x4", "image/mapTool/1x1/4x4_obstacle.bmp", 256, 512, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_6x4", "image/mapTool/1x1/6x4_obstacle.bmp", 192, 256, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_obstacle_2x2_large", "image/mapTool/1x1/2x2_obstacle.bmp", 256, 256, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_4x4_large", "image/mapTool/1x1/4x4_obstacle.bmp", 256, 512, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_obstacle_6x4_large", "image/mapTool/1x1/6x4_obstacle.bmp", 192, 256, true, RGB(255, 0, 255));

	//==================================== R E S O U R C E 
	IMAGEMANAGER->addFrameImage("button_rooting", "image/mapTool/resource/button_rooting.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_resources", "image/mapTool/resource/button_resource.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_artifact", "image/mapTool/resource/button_artifact.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_rooting_artifact", "image/mapTool/resource/button_rooting_artifact.bmp", 256, 384, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_rooting_resources", "image/mapTool/resource/button_rooting_resources.bmp", 192, 96, true, RGB(255, 0, 255));



	//====================================== U I 
	IMAGEMANAGER->addFrameImage("empty", "image/mapTool/empty.bmp", 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("emptyS", "image/mapTool/empty.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("up", "image/mapTool/arrow_up.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down", "image/mapTool/arrow_down.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("left", "image/mapTool/arrow_left.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("right", "image/mapTool/arrow_right.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("size1", "image/mapTool/size_1.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("size2", "image/mapTool/size_2.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sizeF", "image/mapTool/size_flexible.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("erase", "image/mapTool/erase.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_brush_size", "image/mapTool/buttonBrushSize.bmp", 96, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("move", "image/mapTool/moveIcon.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

}