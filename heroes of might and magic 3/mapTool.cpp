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


	_categoryNum = CATE_NULL;
	_mapX = _mapY = 0;
	_inputDelayX = _inputDelayY = 0;
	_mouseArr.x = 0;
	_mouseArr.y = 0;
	_saveX = _saveY = 0;
	_saveAreaX = _saveAreaY = 0;
	_smallNum = 0;
	_brushNum = 0;
	_tileNum = 0;
	_roadNum = 0;
	_eraseNum = 0;
	_page = 0;
	_boxLength = 128;
	_clickUI = false;
	_area = false;
	_foldMini= false;
	_erase = false;
	//============== R E C T   M A K E =====================
	_miniMap = RectMake(836, WINSIZEY - 226, 216, 216);
	_miniView = RectMake(_miniMap.left, _miniMap.top, 72, 54);
	_largeCategory = RectMake(808, 108, 242, 32);
	_smallCategory = RectMake(808, 150, 242, 32);
	_contents = RectMake(830, 192, 256, 288);
	return S_OK;
}

void mapTool::release(void)
{

}

void mapTool::update(void)
{
	//================= T I M E R ================================
	if (_inputDelayX) _inputDelayX--;
	if (_inputDelayY) _inputDelayY--;




	//================= F U N C T I O N ==========================
	setCor();
	keyControl();
	cameraMove();
	setButton();
	minimapMove();


}

void mapTool::render(void)
{

	//====================== CORDINATE =========================
	for (int i = 0; i < MAXTILE; i++)
	{

		sprintf(_cor, "%d", i);

		Rectangle(getMemDC(), _corX[i].left, _corX[i].top, _corX[i].right, _corX[i].bottom);
		Rectangle(getMemDC(), _corY[i].left, _corY[i].top, _corY[i].right, _corY[i].bottom);

		
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

	SelectObject(getMemDC(), oldbrush);
	DeleteObject(brush);

	//================ MOUSE POINT NUMBER ================================

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	
	if (_mouseArr.x < 10)
		TextOut(getMemDC(), 32 + (_mouseArr.x - (int)_mapX/TILESIZE)*TILESIZE , 2, _msCorX, strlen(_msCorX));
	else
		TextOut(getMemDC(), 28 + (_mouseArr.x - (int)_mapX / TILESIZE)*TILESIZE , 2, _msCorX, strlen(_msCorX));
	
	if (_mouseArr.y < 10  )
		TextOut(getMemDC(), 5, 25 + (_mouseArr.y - (int)_mapY/TILESIZE)*TILESIZE  , _msCorY, strlen(_msCorY));
	else
		TextOut(getMemDC(), 2, 25 + (_mouseArr.y - (int)_mapY / TILESIZE)*TILESIZE , _msCorY, strlen(_msCorY));

	SetTextColor(getMemDC(), RGB(0, 0, 0));


	//================= T I L E   D R A W ============================


	tileDraw();


	//================= R O A D   D R A W =========================


	roadDraw();

	//=============== S E L E C T   R E C T ==========================
	selectDraw();

	//=============== U I ==================
	IMAGEMANAGER->findImage("mapToolUI")->render(getMemDC());
	IMAGEMANAGER->findImage("mapToolMark")->render(getMemDC());
	
	buttonDraw();

	//=============== M I N I   M A P====================
	miniDraw();

}

void mapTool::selectDraw(void)
{
	if (_categoryNum == CATE_TILE)
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
	else if (_categoryNum == CATE_ROAD)
	{
		switch (_roadNum)
		{
		case 0:
			IMAGEMANAGER->findImage("select")->render(getMemDC(),
				20 + (_ptMouse.x - 20) / TILESIZE * TILESIZE, 20 + (_ptMouse.y - 20) / TILESIZE*TILESIZE);
		break;
		case 10:
			if (_eraseNum == 0)
				IMAGEMANAGER->findImage("select")->render(getMemDC(),
					20 + (_ptMouse.x - 20) / TILESIZE * TILESIZE,
					20 + (_ptMouse.y - 20) / TILESIZE*TILESIZE);
			if (_eraseNum == 1)
			{
				IMAGEMANAGER->findImage("select2")->render(getMemDC(),
					20 + (_mouseArr.x - 1)*TILESIZE - _mapX,
					20 + (_mouseArr.y - 1)*TILESIZE - _mapY);

			}
			

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
		if (_miniMap.top == WINSIZEY - 226 && _categoryNum != CATE_NULL)
		{
			IMAGEMANAGER->findImage("left")->frameRender(getMemDC(), 903, 335);
			IMAGEMANAGER->findImage("right")->frameRender(getMemDC(), 964, 335);

		}
	}
	else
	{
		IMAGEMANAGER->findImage("up")->frameRender(getMemDC(), _miniMap.left - 30, WINSIZEY - 40);

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
			if (_roadArr[i][j].road != ROAD_END &&
				i - _mapX / TILESIZE >= 0 && 
				j - _mapY / TILESIZE >= 0)
				_roadArr[i][j].img->frameRender(getMemDC(),
					20 + _roadArr[i][j].destX * TILESIZE - _mapX,
					30 + _roadArr[i][j].destY * TILESIZE - _mapY,
					_roadArr[i][j].sourX, _roadArr[i][j].sourY);
		}
	}
}

void mapTool::buttonDraw(void)
{
	IMAGEMANAGER->findImage("tileButton")->frameRender(getMemDC(), _largeCategory.left, _largeCategory.top);
	IMAGEMANAGER->findImage("roadButton")->frameRender(getMemDC(), _largeCategory.left +42, _largeCategory.top);

	switch (_categoryNum)
	{
	case CATE_NULL:
		break;
	case CATE_TILE:

		IMAGEMANAGER->findImage("button_green")->frameRender(getMemDC(), _smallCategory.left, _smallCategory.top);

		IMAGEMANAGER->findImage("button_water")->frameRender(getMemDC(), _smallCategory.left + 42, _smallCategory.top);

		IMAGEMANAGER->findImage("button_volcano")->frameRender(getMemDC(), _smallCategory.left + 84, _smallCategory.top);

		IMAGEMANAGER->findImage("size1")->frameRender(getMemDC(), _smallCategory.left, _smallCategory.bottom + 10);

		IMAGEMANAGER->findImage("size2")->frameRender(getMemDC(), _smallCategory.left , _smallCategory.bottom + 36);

		IMAGEMANAGER->findImage("sizeF")->frameRender(getMemDC(), _smallCategory.left , _smallCategory.bottom + 62);

		switch (_tileNum)
		{
		case 0:
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
		case 1:
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
		case 2:
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
		break;
	case CATE_ROAD:
		IMAGEMANAGER->findImage("button_normal")->frameRender(getMemDC(), _smallCategory.left, _smallCategory.top);

		IMAGEMANAGER->findImage("erase")->frameRender(getMemDC(), _smallCategory.right - 32, _smallCategory.top);

		if(!_erase) 
			IMAGEMANAGER->findImage("size1")->frameRender(getMemDC(), _smallCategory.left, _smallCategory.bottom + 10);



		switch (_roadNum)
		{
		case 0:
			IMAGEMANAGER->findImage("button_road_normal")->render(getMemDC(),
				_contents.left, _contents.top);
		break;
		case 1:
		break;
		case 10:
			IMAGEMANAGER->findImage("button_brush_size")->render(getMemDC(),
				_contents.left, _contents.top);
			break;
		}
		break;
	case CATE_OBSTACLE:
		break;
	case CATE_UNIT:
		break;
	case CATE_RESOURCE:
		break;
	case CATE_OBJ:
		break;
	case CATE_END:
		break;
	default:
		break;
	}

	if (!_erase)
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
	else
	{
		{
			IMAGEMANAGER->findImage("push")->render(getMemDC(),
				_contents.left + _eraseNum * TILESIZE,
				_contents.top ); 
		}
	}



}

void mapTool::setButton(void)
{

	if (_categoryNum == CATE_TILE) IMAGEMANAGER->findImage("tileButton")->setFrameX(0);
	else IMAGEMANAGER->findImage("tileButton")->setFrameX(1);
	
	if (_categoryNum == CATE_ROAD) IMAGEMANAGER->findImage("roadButton")->setFrameX(0);
	else IMAGEMANAGER->findImage("roadButton")->setFrameX(1);

	if (_brushNum == 0) IMAGEMANAGER->findImage("size1")->setFrameX(0);
	else IMAGEMANAGER->findImage("size1")->setFrameX(1);

	if (_brushNum == 1) IMAGEMANAGER->findImage("size2")->setFrameX(0);
	else IMAGEMANAGER->findImage("size2")->setFrameX(1);

	if (_brushNum == 2) IMAGEMANAGER->findImage("sizeF")->setFrameX(0);
	else IMAGEMANAGER->findImage("sizeF")->setFrameX(1);

	if (_tileNum == 0) IMAGEMANAGER->findImage("button_green")->setFrameX(0);
	else IMAGEMANAGER->findImage("button_green")->setFrameX(1);

	if (_tileNum == 1) IMAGEMANAGER->findImage("button_water")->setFrameX(0);
	else IMAGEMANAGER->findImage("button_water")->setFrameX(1);

	if (_tileNum == 2) IMAGEMANAGER->findImage("button_volcano")->setFrameX(0);
	else IMAGEMANAGER->findImage("button_volcano")->setFrameX(1);

	if (_roadNum == 0) IMAGEMANAGER->findImage("button_normal")->setFrameX(0);
	else IMAGEMANAGER->findImage("button_normal")->setFrameX(1);

	if (_erase) IMAGEMANAGER->findImage("erase")->setFrameX(0);
	else IMAGEMANAGER->findImage("erase")->setFrameX(1);


	if (_categoryNum == CATE_TILE)
	{
		IMAGEMANAGER->findImage("button_terrain_green")->setFrameY(_page);
		IMAGEMANAGER->findImage("button_terrain_water")->setFrameY(_page);
		IMAGEMANAGER->findImage("button_terrain_volcano")->setFrameY(_page);
		
	}

	if (!_foldMini) _contents.bottom = _contents.top + 128;
	else _contents.bottom = _contents.top + 288;

	
	//==================== E R A S E ==========================
	if (_roadNum == 10) _erase = true;
	else _erase = false;
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
	if (_boxLength > 288) _boxLength = 288;


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
	switch (_categoryNum)
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
			_roadArr[arrX][arrY].img = NULL;
			_roadArr[arrX][arrY].isChanged = false;
			_roadArr[arrX][arrY].road = ROAD_END;


			setRoad(arrX - 1, arrY, _roadArr[arrX - 1][arrY].road);
			setRoad(arrX, arrY - 1, _roadArr[arrX ][arrY-1].road);
			setRoad(arrX + 1, arrY, _roadArr[arrX + 1][arrY].road);
			setRoad(arrX, arrY + 1, _roadArr[arrX ][arrY+1].road);

		}

		break;
	case CATE_OBSTACLE:
		break;
	case CATE_UNIT:
		break;
	case CATE_RESOURCE:
		break;
	case CATE_OBJ:
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

		_roadArr[arrX][arrY].img = IMAGEMANAGER->findImage("road_normal");
		_roadArr[arrX][arrY].sourX = 0;
		_roadArr[arrX][arrY].sourY = 3;
		_roadArr[arrX][arrY].road = currentRoad;


		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if(_roadArr[arrX + i][arrY + j].road == ROAD_NORMAL ||
					_roadArr[arrX + i][arrY + j].road == ROAD_VOLCANO)
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

void mapTool::setTile(int arrX, int arrY, TILE tile)
{
	TILE currentTile = tile;


	if (!_mapArr[arrX][arrY].isChanged)
	{
		int direction = 0;

		//========= 바꼈으면 좀 이따 다시 돌아오면 바꾸도록
		if (_brushNum != 2)_mapArr[arrX][arrY].isChanged = true;

		//========== 같은 종류에서 랜덤으로 깔기
		int ranNum;
		int ranNum2;

		ranNum = RND->getInt(4);
		ranNum2 = RND->getInt(20);

		//===== 1/20 확률로 잔디 파기
		if(ranNum2) _mapArr[arrX][arrY].sourX = ranNum;
		else _mapArr[arrX][arrY].sourX = 4 + ranNum;		
		
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
				if (_mapArr[arrX + i][arrY + j].tile != (TILE)_tileNum)
				{
					switch (i)
					{
					case -1:
						switch (j)
						{
						case -1: direction += LEFTTOP;
						break;
						case 0: direction += LEFTMIDDLE;
						break;
						case 1: direction += LEFTBOTTOM;
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
						case -1: direction += RIGHTTOP;
						break;
						case 0: direction += RIGHTMIDDLE;
						break;
						case 1: direction += RIGHTBOTTOM;
						break;
						}
					break;
					}
				}
			}
		}
		
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

		//========= 옆 타일 정비
		if (_mapArr[arrX - 1][arrY].tile != (TILE)_tileNum)
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
		if (_mapArr[arrX + 1][arrY].tile != (TILE)_tileNum)
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
		if (_mapArr[arrX][arrY - 1].tile != (TILE)_tileNum)
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
		if (_mapArr[arrX][arrY + 1].tile != (TILE)_tileNum)
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

void mapTool::setCor(void)
{
	if (_ptMouse.x < 788)
	{
		_mouseArr.x = ((_ptMouse.x - 20) / TILESIZE) + (int)_mapX / TILESIZE;
		_mouseArr.y = ((_ptMouse.y - 20) / TILESIZE) + (int)_mapY / TILESIZE;
	}
	
	sprintf(_msCorX, "%d", _mouseArr.x );
	sprintf(_msCorY, "%d", _mouseArr.y );

	if (_mouseArr.x != _saveX || _mouseArr.y != _saveY)
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (_saveX - i >= 0 && _saveY - j >= 0)
				{
					switch (_categoryNum)
					{
					case CATE_NULL:
						break;
					case CATE_TILE:
						_mapArr[_saveX + i][_saveY + j].isChanged = false;
						break;
					case CATE_ROAD:
						_roadArr[_saveX + i][_saveY + j].isChanged = false;
						break;
					case CATE_OBSTACLE:
						break;
					case CATE_UNIT:
						break;
					case CATE_RESOURCE:
						break;
					case CATE_OBJ:
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

void mapTool::keyControl(void)
{
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

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_saveX = _mouseArr.x;
		_saveY = _mouseArr.y;

		//============== DRAW TILE=====================
		if (PtInRect(&RectMake(0, 0, 788, WINSIZEY), _ptMouse) && !_clickUI && _brushNum != 2)
		{
			if (_categoryNum == CATE_TILE)
			{
				if (_brushNum == 255)
				{
					_mapArr[_mouseArr.x][_mouseArr.y].sourX = _saveIndex.x;
					_mapArr[_mouseArr.x][_mouseArr.y].sourY = _saveIndex.y;
					_mapArr[_mouseArr.x][_mouseArr.y].tile = (TILE)_tileNum;
					
					switch (_tileNum)
					{
					case 0:
						_mapArr[_mouseArr.x][_mouseArr.y].miniX = 0;
						_mapArr[_mouseArr.x][_mouseArr.y].miniY = 0;
						_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_GREEN;
						_mapArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("terrain_green");
					break;
					case 1:
						_mapArr[_mouseArr.x][_mouseArr.y].miniX = 1;
						_mapArr[_mouseArr.x][_mouseArr.y].miniY = 0;
						_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_WATER;
						_mapArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("terrain_water");
					break;
					case 2:
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
					_mapArr[_mouseArr.x ][_mouseArr.y ].sourX = 0;
					_mapArr[_mouseArr.x ][_mouseArr.y ].sourY = 0;
						switch (_tileNum)
						{
						case 0:
							_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_GREEN;
							_mapArr[_mouseArr.x][_mouseArr.y].img =
								IMAGEMANAGER->findImage("terrain_green");
						break;
						case 1:
							_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_WATER;
							_mapArr[_mouseArr.x][_mouseArr.y].img =
								IMAGEMANAGER->findImage("terrain_water");

						break;
						case 2:
							_mapArr[_mouseArr.x][_mouseArr.y].tile = TILE_VOLCANO;
							_mapArr[_mouseArr.x][_mouseArr.y].img =
								IMAGEMANAGER->findImage("terrain_volcano");
							break;
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
							_mapArr[_mouseArr.x -i][_mouseArr.y -j].sourX = 0;
							_mapArr[_mouseArr.x -i][_mouseArr.y -j].sourY = 0;
							switch (_tileNum)
							{
							case 0:
								_mapArr[_mouseArr.x - i][_mouseArr.y - j].tile = TILE_GREEN;
								_mapArr[_mouseArr.x - i][_mouseArr.y - j].img =
									IMAGEMANAGER->findImage("terrain_green");
								break;
							case 1:
								_mapArr[_mouseArr.x - i][_mouseArr.y - j].tile = TILE_WATER;
								_mapArr[_mouseArr.x - i][_mouseArr.y - j].img =
									IMAGEMANAGER->findImage("terrain_water");

								break;
							case 2:
								_mapArr[_mouseArr.x - i][_mouseArr.y - j].tile = TILE_VOLCANO;
								_mapArr[_mouseArr.x - i][_mouseArr.y - j].img =
									IMAGEMANAGER->findImage("terrain_volcano");
								break;
							}
							point.x = _mouseArr.x -i;
							point.y = _mouseArr.y - j;
							_vSaveCor.push_back(point);

						}
					}
				}
			}
			else if (_categoryNum == CATE_ROAD)
			{
				if (_brushNum == 0 && !_erase)
				{
					setRoad(_mouseArr.x, _mouseArr.y, (ROAD)_roadNum);

					for (int i = -1; i < 2; i++)
					{
						for (int j = -1; j < 2; j++)
						{
							if (!(i == 0 && j == 0) && _roadArr[_mouseArr.x + i][_mouseArr.y + j].road == (TILE)_roadNum)
								setRoad(_mouseArr.x + i, _mouseArr.y + j, (ROAD)_roadNum);
						}
					}
				}
				else if (_brushNum == 255 && !_erase)
				{
					_roadArr[_mouseArr.x][_mouseArr.y].road = (ROAD)_roadNum;
					switch (_roadNum)
					{
					case 0:
						_roadArr[_mouseArr.x][_mouseArr.y].img = IMAGEMANAGER->findImage("road_normal");
						_roadArr[_mouseArr.x][_mouseArr.y].sourX = _saveIndex.x;
						_roadArr[_mouseArr.x][_mouseArr.y].sourY = _saveIndex.y;
						_roadArr[_mouseArr.x][_mouseArr.y].isChanged = true;
					break;
					case 1:
					break;
					case 2:
					break;
						
					}
				}
				else if (_erase)
				{
					switch (_eraseNum)
					{
					case 0:
						deleteAll(_mouseArr.x, _mouseArr.y);
						break;
					case 1:
						for (int i = 0; i < 2; i++)
						{
							for (int j = 0; j < 2; j++)
							{
								deleteAll(_mouseArr.x -i,_mouseArr.y - j);
							}
						}
						break;
					case 2:
						break;

					}


				}
			}


		}


		//============== PREVENT OVERAP BETWEEN UI AND TILE==============
		if (_ptMouse.x > 788) _clickUI = true;

		//================= MINI MAP CONTROL=================
		if(!_foldMini)
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
			_erase = false;
			if (_ptMouse.x < _largeCategory.left + 32) _categoryNum = CATE_TILE;
			else if (_ptMouse.x >= _largeCategory.left + 42 && _ptMouse.x < _largeCategory.left + 74) _categoryNum = CATE_ROAD;
			else if (_ptMouse.x >= _largeCategory.left + 84 && _ptMouse.x < _largeCategory.left + 116) _categoryNum = CATE_OBSTACLE;
			else if (_ptMouse.x >= _largeCategory.left + 126 && _ptMouse.x <_largeCategory.left + 158) _categoryNum = CATE_UNIT;
			else if (_ptMouse.x >= _largeCategory.left + 168 && _ptMouse.x <_largeCategory.left + 200) _categoryNum = CATE_RESOURCE;
			else if (_ptMouse.x >= _largeCategory.left + 210 && _ptMouse.y <_largeCategory.left + 242) _categoryNum = CATE_OBJ;
		}

		//================== SMALL CATEGORY SELECT =======================
		if (PtInRect(&_smallCategory, _ptMouse))
		{
			_page = 0;
			_erase = false;
			switch (_categoryNum)
			{
			case CATE_NULL:
				break;
			case CATE_TILE:

				if (_ptMouse.x < _smallCategory.left + 32) _tileNum = 0;
				else if (_ptMouse.x >= _smallCategory.left + 42 && _ptMouse.x < _smallCategory.left + 74) _tileNum = 1;
				else if (_ptMouse.x >= _smallCategory.left + 84 && _ptMouse.x < _smallCategory.left + 116) _tileNum = 2;
				break;
			case CATE_ROAD:
				if (_ptMouse.x < _smallCategory.left + 32) _roadNum = 0;
				else if (_ptMouse.x >= _smallCategory.left + 42 && _ptMouse.x < _smallCategory.left + 74);
				else if (_ptMouse.x >= _smallCategory.left + 84 && _ptMouse.x < _smallCategory.left + 116) ;
				else if (_ptMouse.x >= _smallCategory.right - 32 && _ptMouse.x < _smallCategory.right) _roadNum = 10;

				break;
			case CATE_OBSTACLE:
				break;
			case CATE_UNIT:
				break;
			case CATE_RESOURCE:
				break;
			case CATE_OBJ:
				break;
			case CATE_END:
				break;
			default:
				break;
			}
		}


		//================== C O N T E N T S ======================

		//================== B R U S H ============================
		if ((_categoryNum == CATE_TILE || _categoryNum == CATE_ROAD) && PtInRect(&RectMake(
			_smallCategory.left, _smallCategory.bottom + 10, 16, 16), _ptMouse))
		{
			_brushNum = 0;
		}
		else if (_categoryNum == CATE_TILE && PtInRect(&RectMake(
			_smallCategory.left, _smallCategory.bottom + 36, 16, 16), _ptMouse))
		{
			_brushNum = 1;
		}
		else if (_categoryNum == CATE_TILE && PtInRect(&RectMake(
			_smallCategory.left, _smallCategory.bottom + 62, 16, 16), _ptMouse))
		{
			_brushNum = 2;
		}


		if (_brushNum == 2 && !_clickUI && !_area)
		{
			_area = true;
			_saveAreaX = _mouseArr.x;
			_saveAreaY = _mouseArr.y;
		}

		if (_brushNum != 255)
		{
			_saveIndex.x = 15;
			_saveIndex.y = 15;
		}

		if (_erase && _eraseNum == 2 &&!_clickUI && !_area && _ptMouse.x < 788)
		{
			_area = true;
			_saveAreaX = _mouseArr.x;
			_saveAreaY = _mouseArr.y;
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

		//================ C O N T E N T S   B O X ====================
		if (PtInRect(&_contents, _ptMouse) )
		{
			
			if (!_foldMini && _ptMouse.y <= _contents.top + 128 )
			{
				_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE;
				_saveIndex.y = _page * 4 +(_ptMouse.y - _contents.top) / TILESIZE;

			}
			else if (_foldMini)
			{
				_saveIndex.x = (_ptMouse.x - _contents.left) / TILESIZE;
				_saveIndex.y = (_ptMouse.y - _contents.top) / TILESIZE;
			}

			_brushNum = 255;

			if (_erase)
			{
				if(_saveIndex.y == 0 && _saveIndex.x <=2) _eraseNum = _saveIndex.x;

			}
		}

		

	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_clickUI = false;


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
			if(_mouseArr.x != _saveAreaX && _mouseArr.y != _saveAreaY)
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
			_mapArr[_viSaveCor->x][_viSaveCor->y].tile = (TILE)_tileNum;
		}

		for (_viSaveCor = _vSaveCor.begin(); _viSaveCor != _vSaveCor.end(); ++_viSaveCor)
		{
			setTile(_viSaveCor->x, _viSaveCor->y, (TILE)_tileNum);
		}

		for (_viSaveCor = _vSaveCor.begin(); _viSaveCor != _vSaveCor.end(); ++_viSaveCor)
		{
			_mapArr[_viSaveCor->x][_viSaveCor->y].isChanged = false;
		}


		_vSaveCor.clear();

		//===================== 범위형 지우기 ===================
		if (_area && _categoryNum == CATE_ROAD && _erase && _eraseNum == 2)
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


		//=================== P U L L   A R R O W ================
		if (!_foldMini)
		{
			if (IMAGEMANAGER->findImage("down")->getFrameX() == 1)
			{
				IMAGEMANAGER->findImage("down")->setFrameX(0);
				if(PtInRect(&RectMake(_miniMap.left - 30, WINSIZEY - 40, 21, 21), _ptMouse))
				_foldMini = true;

			}
		}
		if (_foldMini)
		{
			if (IMAGEMANAGER->findImage("up")->getFrameX() == 1)
			{
				IMAGEMANAGER->findImage("up")->setFrameX(0);
				if(PtInRect(&RectMake(_miniMap.left - 30, WINSIZEY - 40, 21, 21), _ptMouse))
				_foldMini = false;

			}
		}

		if (IMAGEMANAGER->findImage("left")->getFrameX() == 1)
		{
			IMAGEMANAGER->findImage("left")->setFrameX(0);
			if (PtInRect(&RectMake(903, 335, 21, 21), _ptMouse))
			{
				_page--;
				if (_page < 0) _page = 0;
			
			}
		}
		
		if (IMAGEMANAGER->findImage("right")->getFrameX() == 1)
		{
			IMAGEMANAGER->findImage("right")->setFrameX(0);
			if (PtInRect(&RectMake(964, 335, 21, 21), _ptMouse))
			{
				_page++;

				int maxPage = 0;;
				switch (_categoryNum)
				{
				case CATE_TILE:
					maxPage = 3;
					break;
				case CATE_ROAD:
					maxPage = 1;
					break;
				}
				if (_page > maxPage-1) _page = maxPage -1;

			}
		}
	}
}

void mapTool::loadImg(void)
{
	//================ T E R R A I N ==========================
	IMAGEMANAGER->addFrameImage("terrain", "image/mapTool/terrain_idle.bmp", 32, 32,1,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_green", "image/mapTool/terrain_green.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_water", "image/mapTool/terrain_water.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_volcano", "image/mapTool/terrain_volcano.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));

	//================ R O A D =================================
	IMAGEMANAGER->addFrameImage("road_normal", "image/mapTool/road_normal.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));


	//================ M I N I   M A P =====================
	IMAGEMANAGER->addImage("miniView72", "image/mapTool/miniView72.bmp", 72, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("miniView36", "image/mapTool/miniView36.bmp", 144, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap", "image/mapTool/miniRECT.bmp", 220, 220, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniTerrain72", "image/mapTool/miniTerrain72.bmp", 15, 15, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniTerrain36", "image/mapTool/miniTerrain36.bmp", 30, 30, 5, 5, true, RGB(255, 0, 255));

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
	
	//====================================== U I 
	IMAGEMANAGER->addFrameImage("up", "image/mapTool/arrow_up.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down", "image/mapTool/arrow_down.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("left", "image/mapTool/arrow_left.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("right", "image/mapTool/arrow_right.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("size1", "image/mapTool/size_1.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("size2", "image/mapTool/size_2.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sizeF", "image/mapTool/size_flexible.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("erase", "image/mapTool/erase.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_brush_size", "image/mapTool/buttonBrushSize.bmp", 96, 32, true, RGB(255, 0, 255));
}