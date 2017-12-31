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
	_zOrder = new zOrder;

	//============= L O A D   I N F O ================
	loadMap();
	loadCamp();
	


	//============= I N I T I A L I Z E ============

	_fadeAlpha = 255;



	//============= ADDRESS LINK====================
	_ui->setPlayMapAddressLink(_pm);
	_ui->setgameSceneAddressLink(this);
	_ui->setPlayerAddressLink(_player);
	_player->setPlayMapAddressLink(_pm);
	_player->setGameSceneAddressLink(this);
	_player->setzOrderAddressLink(_zOrder);
	_pm->setzOrderAddressLink(_zOrder);
	_ob->setzOrderAddressLink(_zOrder);
	_zOrder->setPlayerAddressLink(_player);

	//============= C L A S S   I N I T ==================
	_pm->init();
	_ui->init();
	_ob->init();
	_player->init(0);
	_zOrder->init();

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
	
	enterCity();


	//================== INPUT KEY ==================

	//============= FIELD
	if (!_player->getScene())
	{
		if (_ptMouse.x >= 788 || _ui->getConfig())				// 필드 : UI	
		{
			if(!_player->getWindow())
			_ui->input();
		}
		else inputPlay();										// 필드 : 겜화면	STAY
		inputCommon();											// 필드 : 겜화면	KEY UP
		_player->inputField();									// 필드 : 겜화면 KEY DOWN

	}
	//============= CITY SCENE
	if (_player->getScene())
	{
		for (int i = 0; i < _vCamp.size(); i++)
		{
			if (_vCamp[i]->getNum() == _player->getCurrentCamp())
			{
				if(!_player->getWindow()) _vCamp[i]->inputCity();
				else _player->inputField();
			}
		}


		//_player->inputCity();									// 마을 : KEY DOWN

	}
	//============= BATTLE SCENE

	//========= C L A S S   U P D A T E=================
	
	for (int i = 0; i < _vCamp.size(); i++)
	{
		_vCamp[i]->update();
	}

	_zOrder->update();
	_pm->update();
	_ui->update();
	_ob->update();
	_player->update();
	
}

void gameScene::render(void)
{
	//============= C L A S S   R E N D E R ===============
	if (!_player->getScene())
	{
		//=============== 필드 밖 렌더
		_pm->render();									// z order 4 인방 장애물
		_ob->render();									// z order 4 인방 오브젝트
	

		for (int i = 0; i < _vCamp.size(); i++)
		{
			_vCamp[i]->render();						// z order 4 인방 캠프
		}

		_pm->attributeDraw();
		_player->render();								// z order 4 인방 영


		_zOrder->render();

		_ui->render();

		_player->getHero()[_player->getCurrentHero()]->uiDraw();
	}

	if (_player->getScene())
	{
		//================ 마을 안 렌더
		for (int i = 0; i < _vCamp.size(); i++)
		{
			if (_player->getCurrentCamp() == _vCamp[i]->getNum())
			{
				if (_vCamp[i]->getCityInfo().camp == CAMP_CASTLE)
				{
					_vCamp[i]->castleDraw();

				}
				else if (_vCamp[i]->getCityInfo().camp == CAMP_DUNGEON)
				{
					_vCamp[i]->dungeonDraw();
				}
				_vCamp[i]->selectBox();

			}
		}

		_player->render();

	}
	
	if (_player->getWindow()) _player->heroInfoDraw();

	if(_fadeAlpha >0)
	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), _fadeAlpha);
}

void gameScene::enterCity(void)
{
	for (int i = 0; i < _vCamp.size(); i++)
	{
		for (int j = 0; j < _player->getHero().size(); j++)
		{
			//========== 영웅이 캠프의 입구에 왔는지
			if (_player->getHero()[j]->getHeroPoint().x == _vCamp[i]->getFieldPoint().x &&
				_player->getHero()[j]->getHeroPoint().y == _vCamp[i]->getFieldPoint().y)
			{
				//=========== 영웅이 성에 있던 상태가 아닌지 이동 중인건 아닌지
				if (_player->getHero()[j]->getInCamp() == -1 && !_player->getHero()[j]->getGoOn())
				{
					//============ 그렇다면 이제 플레이어의 씬을 바꿔라
					//============ 그 성의 번호로 커런트 번호를 바꿔줘라
					//============ 영웅도 성안에 들어왔다고 해줘라
					_player->setScene(true);
					_player->setCurrentCamp(_vCamp[i]->getNum());
					_player->getHero()[j]->setInCamp(_vCamp[i]->getNum());
					_vCamp[i]->setProperty(_player->getProperty());				// 재산을 넘겨주고
					_vCamp[i]->setHeroAddressLink(_player->getHero()[j]);		// 들어간 영웅 넘겨주고
					_vCamp[i]->setHero(true);									// 영웅 들어갔다고 알려주고
				}
			}
		}
	}
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
				build.enterX = _vBuildSaveInfo[i][j].enterX;
				build.enterY = _vBuildSaveInfo[i][j].enterY;
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

				if (build.camp != CAMP_NULL)
				{
					//=============== z order를 위한 ===================
					tagRender render;
					ZeroMemory(&render, sizeof(tagRender));
					
					render.img = build.img;
					render.shadowImg = build.imgShadow;
					render.flag = NULL;
					render.destX = (build.destX - build.imgX) * TILESIZE;
					render.destY = (build.destY - build.imgY) * TILESIZE;
					render.sourX = build.sourX;
					render.sourY = build.sourY;
					render.sizeX = 5;
					render.sizeY = 6 * TILESIZE;
					render.identity = 255;
					render.kind = 0;
					_zOrder->addRender(render);



					addCamp(build);
				}
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

	camp->setPlayerAddressLink(_player);
	camp->setNum(_vCamp.size());
	camp->setzOrderAddressLink(_zOrder);



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
		//============= F I E L D   S C E N E ===============
		if (!_player->getScene())
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

				_pm->setCameraX(camera.x);
				_pm->setCameraY(camera.y);

			}
			
		}


	}	
}