#include "stdafx.h"
#include "mapObject.h"

mapObject::mapObject() {}
mapObject::~mapObject() {}

HRESULT mapObject::init(void)
{

	loadObject();

	_count = 0;
	return S_OK;
}

void mapObject::release(void)
{

}

void mapObject::update(void)
{
	_count++;

	for ( _viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		
		if ((int)(TIMEMANAGER->getWorldTime()/TIMEMANAGER->getElapsedTime())%8 ==0 && 
			((_viObject->type & ELEMENTMINE)== ELEMENTMINE||
			(_viObject->type & ELEMENTEVENT)== ELEMENTEVENT))
		{
			
			_viObject->indexX++;
			if (_viObject->indexX >= 8)
			{
				_viObject->indexX = 0;
			}
		}

	}
}

void mapObject::render(void)
{
	for ( _viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		_viObject->img->frameRender(getMemDC(),
			(_viObject->point.x - _viObject->imgX)*TILESIZE - DATABASE->getPlayCameraX(),
			(_viObject->point.y - _viObject->imgY)*TILESIZE - DATABASE->getPlayCameraY(),
			_viObject->indexX, _viObject->indexY);
		
		if(_viObject->shadowImg != NULL)
		_viObject->shadowImg->alphaFrameRender(getMemDC(),
			(_viObject->point.x - _viObject->imgX)*TILESIZE - DATABASE->getPlayCameraX(),
			(_viObject->point.y - _viObject->imgY)*TILESIZE - DATABASE->getPlayCameraY(),
			_viObject->indexX, _viObject->indexY, SHADOWALPHA);
			

	}

}

void mapObject::draw(void)
{

}


void mapObject::loadObject(void)
{
	HANDLE file;
	DWORD read;



	file = CreateFile(DATABASE->getSaveName().c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _mapSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);
	ReadFile(file, _roadSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);
	ReadFile(file, _buildSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);
	ReadFile(file, _vBuildSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);
	ReadFile(file, _vLootSaveInfo, sizeof(tagSaveInfo)*MAXTILE*MAXTILE, &read, NULL);

	CloseHandle(file);

	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			if ((_vBuildSaveInfo[i][j].type&ELEMENTMINE) == ELEMENTMINE )
			{
				tagMapObject object;
				ZeroMemory(&object, sizeof(tagMapObject));

				object.img = IMAGEMANAGER->findImage("game_mine");
				object.shadowImg = IMAGEMANAGER->findImage("game_mine_shadow");
				object.mine = (MINE)((_vBuildSaveInfo[i][j].type^ELEMENTMINE) % 10);
				object.point.x =i;
				object.point.y = j;
				object.indexX = 0;
				object.indexY = (_vBuildSaveInfo[i][j].type^ELEMENTMINE) % 10;
				object.visit = false;
				object.enterX = _vBuildSaveInfo[i][j].enterX;
				object.enterY = _vBuildSaveInfo[i][j].enterY;
				object.imgX = _vBuildSaveInfo[i][j].imgX;
				object.imgY = _vBuildSaveInfo[i][j].imgY;
				object.type = _vBuildSaveInfo[i][j].type;

				_vObject.push_back(object);
			}
			else if ((_vBuildSaveInfo[i][j].type & ELEMENTEVENT) == ELEMENTEVENT)
			{
				tagMapObject object;
				ZeroMemory(&object, sizeof(tagMapObject));

				object.img = IMAGEMANAGER->findImage("game_ev");
				object.shadowImg = IMAGEMANAGER->findImage("game_ev_shadow");
				object.ev = (EVENT)((_vBuildSaveInfo[i][j].type^ELEMENTEVENT) % 10);
				object.point.x = i;
				object.point.y = j;
				object.indexX = 0;
				object.indexY = (_vBuildSaveInfo[i][j].type^ELEMENTEVENT) % 10;
				object.visit = false;
				object.enterX = _vBuildSaveInfo[i][j].enterX;
				object.enterY = _vBuildSaveInfo[i][j].enterY;
				object.imgX = _vBuildSaveInfo[i][j].imgX;
				object.imgY = _vBuildSaveInfo[i][j].imgY;
				object.type = _vBuildSaveInfo[i][j].type;

				_vObject.push_back(object);

			}

			if ((_vLootSaveInfo[i][j].type & ELEMENTRESOURCE) == ELEMENTRESOURCE)
			{
				tagMapObject object;
				ZeroMemory(&object, sizeof(tagMapObject));

				object.img = IMAGEMANAGER->findImage("resources");
				object.shadowImg = IMAGEMANAGER->findImage("resources_shadow");
				object.point.x = i;
				object.point.y = j;
				object.indexX = _vLootSaveInfo[i][j].sourX;
				object.indexY = _vLootSaveInfo[i][j].sourY;
				object.visit = false;
				object.enterX = i;
				object.enterY = j;
				object.imgX = _vLootSaveInfo[i][j].imgX;
				object.imgY = _vLootSaveInfo[i][j].imgY;
				object.type = _vLootSaveInfo[i][j].type;
				_vObject.push_back(object);

			}
			else if ((_vLootSaveInfo[i][j].type & ELEMENTARTIFACT) == ELEMENTARTIFACT )
			{
				tagMapObject object;
				ZeroMemory(&object, sizeof(tagMapObject));

				object.point.x = i;
				object.point.y = j;
				object.indexX = _vLootSaveInfo[i][j].sourX;
				object.indexY = _vLootSaveInfo[i][j].sourY;
				object.visit = false;
				object.enterX = i;
				object.enterY = j;
				object.imgX = _vLootSaveInfo[i][j].imgX;
				object.imgY = _vLootSaveInfo[i][j].imgY;
				object.type = _vLootSaveInfo[i][j].type;
				switch ((_vLootSaveInfo[i][j].type ^ ELEMENTARTIFACT) /10)
				{
				case 1:
					object.img = IMAGEMANAGER->findImage("artifact_weapon");
					object.shadowImg = IMAGEMANAGER->findImage("artifact_weapon_shadow");
				break;
				case 2:
					object.img = IMAGEMANAGER->findImage("artifact_armor");
					object.shadowImg = IMAGEMANAGER->findImage("artifact_armor_shadow");
					break;
				case 3:
					object.img = IMAGEMANAGER->findImage("artifact_helmet");
					object.shadowImg = IMAGEMANAGER->findImage("artifact_helmet_shadow");
					break;
				case 4:
					object.img = IMAGEMANAGER->findImage("artifact_shield");
					object.shadowImg = IMAGEMANAGER->findImage("artifact_sheild_shadow");
					break;
				case 5:
					object.img = IMAGEMANAGER->findImage("artifact_acc");
					object.shadowImg = IMAGEMANAGER->findImage("artifact_acc_shadow");
					break;

				}



				_vObject.push_back(object);

			}
			else if ((_vLootSaveInfo[i][j].type & ELEMENTCASTLE) == ELEMENTCASTLE )
			{
				tagMapObject object;
				ZeroMemory(&object, sizeof(tagMapObject));

				object.point.x = i;
				object.point.y = j;
				object.indexX = _vLootSaveInfo[i][j].sourX;
				object.indexY = _vLootSaveInfo[i][j].sourY;
				object.visit = false;
				object.enterX = i;
				object.enterY = j;
				object.imgX = _vLootSaveInfo[i][j].imgX;
				object.imgY = _vLootSaveInfo[i][j].imgY;
				object.type = _vLootSaveInfo[i][j].type;
				object.img = IMAGEMANAGER->findImage("unit_castle");
				object.shadowImg = IMAGEMANAGER->findImage("unit_castle_shadow");



				_vObject.push_back(object);

			}
			else if((_vLootSaveInfo[i][j].type & ELEMENTDUNGEON) == ELEMENTDUNGEON)
			{
				tagMapObject object;
				ZeroMemory(&object, sizeof(tagMapObject));

				object.point.x = i;
				object.point.y = j;
				object.indexX = _vLootSaveInfo[i][j].sourX;
				object.indexY = _vLootSaveInfo[i][j].sourY;
				object.visit = false;
				object.enterX = i;
				object.enterY = j;
				object.imgX = _vLootSaveInfo[i][j].imgX;
				object.imgY = _vLootSaveInfo[i][j].imgY;
				object.type = _vLootSaveInfo[i][j].type;
				object.img = IMAGEMANAGER->findImage("unit_dungeon");
				object.shadowImg = IMAGEMANAGER->findImage("unit_dungeon_shadow");



				_vObject.push_back(object);


			}

		}
	}

}