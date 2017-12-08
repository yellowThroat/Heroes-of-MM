#pragma once
#include "gameNode.h"
#include <functional>


//�ݹ��Լ� �Լ�������
typedef void(*CALLBACK_FUNCTION)(void);

//<Functional>
//std::function
//std::move
//std::bind
//�Ϲ� ��� ����, ������� ���� �����ϰ� ��

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;		//��ư �̳�

	const char* _imageName;			//��ư �̹��� �̸�
	image* _image;					//��ư �̹���
	RECT _rc;
	float _x, _y;

	CALLBACK_FUNCTION _callbackFunction;

public:
	HRESULT init(const char* imageName, int x, int y,		
		CALLBACK_FUNCTION cbFunction);
	void release(void);
	void update(void);
	void render(void);


	button();
	~button();
};