#include "stdafx.h"
#include "gameScene.h"

gameScene::gameScene() {}
gameScene::~gameScene(){}

HRESULT gameScene::init(void)
{
	_vCamp.clear();
	//============= A L L O C A T I O N ===================
	_pm = new playMap;						// 플레이 하는 맵
	_ui = new ui;							// 플레이시 ui
	_ob = new mapObject;					// 플레이시 나올 맵 오브젝트
	_player = new player;

	//============= L O A D   I N F O ================
	loadMap();
	loadCamp();
	
	


	//============= I N I T I A L I Z E ============

	_fadeAlpha = 255;



	//============= ADDRESS LINK====================
	_ui->setPlayMapAddressLink(_pm);
	_ui->setgameSceneAddressLink(this);

	//============= C L A S S   I N I T ==================
	_pm->init();
	_ui->init();
	_ob->init();
	_player->init(0);

	//=============== T E S T ==================




	return S_OK;
}

void gameScene::release(void)
{

}

void gameScene::update(void)
{

	if(_fadeAlpha >0) _fadeAlpha -= 3;
	if (_fadeAlpha < 0) _fadeAlpha = 0;
	

	//=========== F U N C T I O N =================
	
	if (_ptMouse.x >= 788 || _ui->getConfig()) _ui->input();
	else inputPlay();
	inputCommon();


	//========= C L A S S   U P D A T E=================
	
	for (int i = 0; i < _vCamp.size(); i++)
	{
		_vCamp[i]->update();
	}

	_pm->update();
	_ui->update();
	_ob->update();
	_player->update();
	
}

void gameScene::render(void)
{
	//============= C L A S S   R E N D E R ===============
	_pm->render();
	_ob->render();
	
	_pm->attributeDraw();
	for (int i = 0; i < _vCamp.size(); i++)
	{
		_vCamp[i]->render();
	}

	_player->render();

	_ui->render();


	if(_fadeAlpha >0)
	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), _fadeAlpha);
}

void gameScene::loadMap(void)
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
}

void gameScene::loadCamp(void)
{
	for (int i = 0; i < MAXTILE; i++)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			if ((_vBuildSaveInfo[i][j].type & ELEMENTCAMP) == ELEMENTCAMP)
			{
				building build;
				ZeroMemory(&build, sizeof(building));
				build.camp = (CAMP)((_vBuildSaveInfo[i][j].type^ELEMENTCAMP) % 10);
				build.mine = MINE_NULL;
				build.ev = EV_NULL;
				build.destX = i;
				build.destY = j;
				build.sourX = _vBuildSaveInfo[i][j].sourX;
				build.sourY = _vBuildSaveInfo[i][j].sourY;
				build.sizeX = _vBuildSaveInfo[i][j].sizeX;
				build.sizeY = _vBuildSaveInfo[i][j].sizeY;
				build.imgX = _vBuildSaveInfo[i][j].imgX;
				build.imgY = _vBuildSaveInfo[i][j].imgY;
				build.miniX = _vBuildSaveInfo[i][j].miniX;
				build.campInfo = _vBuildSaveInfo[i][j].campInfo;

				switch ((_vBuildSaveInfo[i][j].type^ELEMENTCAMP) % 10)
				{
				case 0:
					build.img = IMAGEMANAGER->findImage("building_castle");
					build.imgShadow = IMAGEMANAGER->findImage("building_castle_shadow");
					break;
				case 1:
					build.img = IMAGEMANAGER->findImage("building_dungeon");
					build.imgShadow = IMAGEMANAGER->findImage("building_dungeon_shadow");
					break;
				}

				if(build.camp != CAMP_NULL) addCamp(build);
			}
		}
	}



}

void gameScene::addCamp(tagBuildingInfo info)
{
	camp* camp;


	switch (info.camp)
	{
	case CAMP_CASTLE:
		camp = new castle;
		break;
	case CAMP_DUNGEON:
		camp = new dungeon;

		break;
	}

	camp->init(info);

	_vCamp.push_back(camp);

}

void gameScene::inputCommon(void)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_ui->getMiniMapMove())
		{
			_ui->setMiniMapMove(false);
		}
	}
}

void gameScene::inputPlay(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&(_ui->getMiniMapRect()), _ptMouse) || _ui->getMiniMapMove())
		{
			POINT camera;
			camera.x = (_ptMouse.x - 12 * 2 - _ui->getMiniMapRect().left) / 2 * TILESIZE;
			camera.y = (_ptMouse.y - 9 * 2 - _ui->getMiniMapRect().top) / 2 * TILESIZE;

			if (camera.x <= -8 * TILESIZE) camera.x = -8 * TILESIZE;
			if (camera.y <= -6 * TILESIZE) camera.y = -6 * TILESIZE;
			if (camera.x >= 56 * TILESIZE) camera.x = 56 * TILESIZE;
			if (camera.y >= 60 * TILESIZE) camera.y = 60 * TILESIZE;

			_pm->setCamera(camera);
		}

	}
	
}