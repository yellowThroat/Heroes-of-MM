#include "stdafx.h"
#include "utils.h"


namespace IOTA_UTIL
{
	//거리 가져오는 함수
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//각도 가져오는 함수
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}


	//각도 가져오는 함수 0 ~ 2PI
	float getAngle(float x, float y)
	{
		float angle;
		if (y > 0) 	angle = atan2f(y, x);		
		else angle = PI2 + atan2f(y, x);		
		return angle;
	}

	//숫자 적는 매크로
	void NumberMacro(HDC hdc, int num, int x, int y, int su)
	{
		int a, b, c, d;
		a = num / 1000;
		b = (num % 1000) / 100;
		c = (num % 100) / 10;
		d = num % 10;
		char tmp[256];
		if (su == 4) {
			IMAGEMANAGER->findImage(itoa(a, tmp, 10))->render(hdc, x, y);
			IMAGEMANAGER->findImage(itoa(b, tmp, 10))->render(hdc, x + IMAGEMANAGER->findImage("0")->getWidth(), y);
			IMAGEMANAGER->findImage(itoa(c, tmp, 10))->render(hdc, x + IMAGEMANAGER->findImage("0")->getWidth() * 2, y);
			IMAGEMANAGER->findImage(itoa(d, tmp, 10))->render(hdc, x + IMAGEMANAGER->findImage("0")->getWidth() * 3, y);
		}
		if (su == 3) {
			IMAGEMANAGER->findImage(itoa(b, tmp, 10))->render(hdc, x, y);
			IMAGEMANAGER->findImage(itoa(c, tmp, 10))->render(hdc, x + IMAGEMANAGER->findImage("0")->getWidth(), y);
			IMAGEMANAGER->findImage(itoa(d, tmp, 10))->render(hdc, x + IMAGEMANAGER->findImage("0")->getWidth() * 2, y);
		}
		if (su == 2) {
			IMAGEMANAGER->findImage(itoa(c, tmp, 10))->render(hdc, x, y);
			IMAGEMANAGER->findImage(itoa(d, tmp, 10))->render(hdc, x + IMAGEMANAGER->findImage("0")->getWidth(), y);
		}
		if (su == 1) IMAGEMANAGER->findImage(itoa(d, tmp, 10))->render(hdc, x, y);
	}

	void frameRotation(image* img, int division, float angle, bool frameX, bool clockwise)
	{
		float _divisionAngle;
		int frame;
		float _angle;

		_divisionAngle = PI / division;

		_angle = angle + _divisionAngle;
		if (_angle >= PI2) _angle -= PI2;
		if (_angle <= 0) _angle += PI2;

		frame = int(_angle / (2.0f* _divisionAngle));

		if (clockwise)
		{
			if (frameX)	img->setFrameX(frame);		
			else img->setFrameY(frame);
		}
		else
		{
			if (frame)
			{
				if (frameX) img->setFrameX(division-frame);
				else img->setFrameY(division-frame);

			}
			else
			{
				img->setFrameX(0);
				img->setFrameY(0);
			}
		}
	}


	// int 형 올림
	int getRise(int x)
	{
		int a = x/2 +1; 
		
		return a;
	}

	/*
	폰트 
		CreateFont(
	40,						//문자폭
	0,						//문자 넓이
	40,						//문자 기울기(실제로 문자가 각도로 기움)
	0,						//문자 방향
	600,					//문자 굵기(폰트 크기)
	0,						//bool 문자 기울기
	0,						//bool 문자 밑줄
	0,						//bool 문자 취소선(나무위키에 많음)
	HANGUL_CHARSET,			//문자 셋팅
	0,						//출력 정확도
	0,						//클리핑 정확도
	0,						//출력의 퀄리티
	0,						//자간
	TEXT("궁서체"));			//폰트

	사용법

	//font1 = CreateFont(100, 0, 0, 0, 300, false, false, false,
	//	HANGUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림"));
	//
	//oldFont = (HFONT)SelectObject(getMemDC(), font1);
	//sprintf(str, "치킨먹구싶다");
	//TextOut(getMemDC(), 10, 100, str, strlen(str));
	//DeleteObject(font1);

	*/

}