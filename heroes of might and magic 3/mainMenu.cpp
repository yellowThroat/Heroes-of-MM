#include "stdafx.h"
#include "mainMenu.h"

mainMenu::mainMenu() {}
mainMenu::~mainMenu() {}

HRESULT	mainMenu::init(void)
{
	//============================= I N I T ============================
	imageInit();


	//==================================================================
	_mapTool = RectMakeCenter(641, 300, 68, 72);
	
	return S_OK;
}

void mainMenu::release(void)
{

}

void mainMenu::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_mapTool, _ptMouse))
		{
			SCENEMANAGER->changeScene("mapTool");
		}
	}
}

void mainMenu::render(void)
{

	draw();
}

void mainMenu::draw(void)
{
	IMAGEMANAGER->findImage("mainBackground")->render(getMemDC());
	IMAGEMANAGER->findImage("mainBackgroundSecond")->render(getMemDC(), 800, 0);
	IMAGEMANAGER->findImage("button_maptool")->render(getMemDC(), _mapTool.left, _mapTool.top);
	IMAGEMANAGER->findImage("font_maptool")->render(getMemDC(), _mapTool.left - 50, _mapTool.top + 15);
}

void mainMenu::imageInit(void)
{
	IMAGEMANAGER->addImage("mainBackground", "image/ui/mainMenuBackGround.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mainBackgroundSecond", "image/ui/mainMenuSecond.bmp", 300, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("font_maptool", "image/font/font_mapTool.bmp", 175, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_maptool", "image/ui/maptoolButton.bmp",68, 72, true, RGB(255, 0, 255));
}