#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{

}

//�ʱ�ȭ
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	_option = false;
	//============================
	SCENEMANAGER->addScene("mainMenu", new mainMenu);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("gameScene", new gameScene);

	SCENEMANAGER->changeScene("mainMenu");
	ShowCursor(false);

	//============== A D D R E S S   L I N K ===================
	IMAGEMANAGER->addImage("mouse_idle", "image/ui/mouse/mouse_idle.bmp", 10, 18, true, RGB(255, 0, 255));

	

	return S_OK;
}
//�޸� ����
void mainGame::release(void)
{
	
}

//�������(Ÿ�̸�)
void mainGame::update(void)	
{
	gameNode::update();
	TIMEMANAGER->getElapsedTime();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0)) {
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

//�׷��ִ� �Լ�
void mainGame::render(void)	
{
	//��� ��ȭ�� �� �� �ʿ�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//==============================================================
	SCENEMANAGER->render();
	IMAGEMANAGER->findImage("mouse_idle")->render(getMemDC(), _ptMouse.x, _ptMouse.y);

	//========================================================================
	if(_option)TIMEMANAGER->render(getMemDC());
	//����ۿ� �ִ°� HDC�� �׷��ִ� ����
	this->getBackBuffer()->render(getHDC(), 0, 0);

}