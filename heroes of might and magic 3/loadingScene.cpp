#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{

}

HRESULT loadingScene::init()   
{
	_loading = new loading;
	_loading->init();

	char image[256];

	for (int i = 0; i < 100; i++)
	{
		memset(image, 0, sizeof(image));
		sprintf(image, "·ÑÇù°î%d", i);
		_loading->loadImage(image, "image/·ÑÇù°î.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_loading->loadSound("¹è°æ", "sound/background.mp3", true, true);
	}


	return S_OK;
}
void loadingScene::release()   
{
	SAFE_DELETE(_loading);
}
void loadingScene::update()	   
{
	_loading->update();

	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("Çù°î¾À");
	}
}
void loadingScene::render()	   
{
	_loading->render();
}
