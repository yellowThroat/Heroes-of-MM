#include "stdafx.h"
#include "gameScene.h"

gameScene::gameScene() {}
gameScene::~gameScene(){}

HRESULT gameScene::init(void)
{
	//============= A L L O C A T I O N ===================
	_pm = new playMap;
	_ui = new ui;





	//============= I N I T I A L I Z E ============

	_fadeAlpha = 255;




	//============= ADDRESS LINK====================
	_ui->setPlayMapAddressLink(_pm);


	//============= C L A S S   I N I T ==================
	_pm->init();
	_ui->init();

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
	
	if (_ptMouse.x >= 788) _ui->input();
	else inputPlay();
	inputCommon();


	//========= C L A S S   U P D A T E=================
	_pm->update();
	_ui->update();

	
	
}

void gameScene::render(void)
{
	//============= C L A S S   R E N D E R ===============
	_pm->render();
	_ui->render();

	if(_fadeAlpha >0)
	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), _fadeAlpha);
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