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

	SCENEMANAGER->changeScene("mapTool");


	//============== A D D R E S S   L I N K ===================
	
	

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

//�׷��ִ� �Լ�
void mainGame::render(void)	
{
	//��� ��ȭ�� �� �� �ʿ�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================
	SCENEMANAGER->render();


	//========================================================================
	if(_option)TIMEMANAGER->render(getMemDC());
	//����ۿ� �ִ°� HDC�� �׷��ִ� ����
	this->getBackBuffer()->render(getHDC(), 0, 0);

}