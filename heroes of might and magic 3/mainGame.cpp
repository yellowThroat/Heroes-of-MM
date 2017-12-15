#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{

}

//초기화
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	_option = false;
	//============================
	SCENEMANAGER->addScene("mainMenu", new mainMenu);
	SCENEMANAGER->addScene("mapTool", new mapTool);

	SCENEMANAGER->changeScene("mapTool");


	//============== A D D R E S S   L I N K ===================
	
	

	return S_OK;
}
//메모리 해제
void mainGame::release(void)
{
	
}

//연산관련(타이머)
void mainGame::update(void)	
{
	gameNode::update();
	TIMEMANAGER->getElapsedTime();
	if (KEYMANAGER->isOnceKeyDown(VK_F10)) {
		switch (_option)
		{
		case true:
			_option = false;
			break;
		case false:
			_option = true;
			break;
		default:
			break;
		}
	}
	//=================================


	SCENEMANAGER->update();

}

//그려주는 함수
void mainGame::render(void)	
{
	//흰색 도화지 한 장 필요
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================
	SCENEMANAGER->render();


	//========================================================================
	if(_option)TIMEMANAGER->render(getMemDC());
	//백버퍼에 있는걸 HDC로 그려주는 역할
	this->getBackBuffer()->render(getHDC(), 0, 0);

}