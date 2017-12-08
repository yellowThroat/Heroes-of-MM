#include "stdafx.h"
#include "button.h"

button::button() {}
button::~button() {}


HRESULT button::init(const char* imageName, int x, int y,	
	CALLBACK_FUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;


	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void button::release()
{

}

void button::update()
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;
}

void button::render(void)
{
	switch (_direction)
	{
	case BUTTONDIRECTION_NULL: case BUTTONDIRECTION_UP:
		_image->frameRender(getMemDC(), _rc.left, _rc.top,0,0);
		break;
	case BUTTONDIRECTION_DOWN:
		_image->frameRender(getMemDC(), _rc.left, _rc.top,0,1);
		break;
	}
}