#pragma once
#include "gameNode.h"
#include <functional>


//콜백함수 함수포인터
typedef void(*CALLBACK_FUNCTION)(void);

//<Functional>
//std::function
//std::move
//std::bind
//일반 멤버 변수, 멤버변수 참조 가능하게 됨

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;		//버튼 이넘

	const char* _imageName;			//버튼 이미지 이름
	image* _image;					//버튼 이미지
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