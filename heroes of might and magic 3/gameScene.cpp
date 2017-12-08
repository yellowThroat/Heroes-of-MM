#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()  
{
	SOUNDMANAGER->play("¹è°æ", 1.0f);
	return S_OK;
}
void gameScene::release()  
{

}
void gameScene::update()   
{

}
void gameScene::render()   
{
	IMAGEMANAGER->findImage("·ÑÇù°î0")->render(getMemDC());
}

