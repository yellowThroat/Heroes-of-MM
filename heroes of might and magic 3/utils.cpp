#include "stdafx.h"
#include "utils.h"


namespace IOTA_UTIL
{

	//�Ÿ� �������� �Լ�
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//���� �������� �Լ�
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


	//���� �������� �Լ� 0 ~ 2PI
	float getAngle(float x, float y)
	{
		float angle;
		if (y > 0) 	angle = atan2f(y, x);
		else angle = PI2 + atan2f(y, x);
		return angle;
	}

	//���� ���� ��ũ��
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


	//======= �ȼ� �� �������� 
	bool getPixelC(int x)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("castle_RGB")->getMemDC(), _ptMouse.x, _ptMouse.y);

		int a = GetRValue(color);
		int b = GetGValue(color);
		int c = GetBValue(color);

		if (a == x&& b == 100 &&  c == 100) return true;


		return false;
	}

	bool getMenuC()
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("castle_RGB")->getMemDC(), _ptMouse.x, _ptMouse.y);

		int a = GetRValue(color);
		int b = GetGValue(color);
		int c = GetBValue(color);

		if (b == 100 && c == 100) return true;


		return false;

	}

	int getPixelC(void)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("castle_RGB")->getMemDC(), _ptMouse.x, _ptMouse.y);

		int a = GetRValue(color);
		


		return a;
	}





	bool getPixelD(int x)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeon_RGB")->getMemDC(), _ptMouse.x, _ptMouse.y);

		int a = GetRValue(color);
		int b = GetGValue(color);
		int c = GetBValue(color);

		if (a == x && b == 100 && c == 100) return true;


		return false;
	}

	bool getMenuD()
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeon_RGB")->getMemDC(), _ptMouse.x, _ptMouse.y);

		int a = GetRValue(color);
		int b = GetGValue(color);
		int c = GetBValue(color);

		if (b == 100 && c == 100) return true;


		return false;

	}

	int getPixelD(void)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeon_RGB")->getMemDC(), _ptMouse.x, _ptMouse.y);

		int a = GetRValue(color);



		return a;
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
				if (frameX) img->setFrameX(division - frame);
				else img->setFrameY(division - frame);

			}
			else
			{
				img->setFrameX(0);
				img->setFrameY(0);
			}
		}
	}

	int getRise(int x, int division)
	{
		int a;
		a = x;

		if (a % division)
		{
			a = a / division + 1;
		}
		else a = a / division;

		return a;
	}
	

	//================ ���� ���ϴ¿�
	int maxRange(int x, int division)
	{
		int a;
		a = x;
		if (a%division)
		{
			a = a / division ;
		}
		else a = a / division - 1;
		return a;
	}

	/*
	��Ʈ
		CreateFont(
	40,						//������
	0,						//���� ����
	40,						//���� ����(������ ���ڰ� ������ ���)
	0,						//���� ����
	600,					//���� ����(��Ʈ ũ��)
	0,						//bool ���� ����
	0,						//bool ���� ����
	0,						//bool ���� ��Ҽ�(������Ű�� ����)
	HANGUL_CHARSET,			//���� ����
	0,						//��� ��Ȯ��
	0,						//Ŭ���� ��Ȯ��
	0,						//����� ����Ƽ
	0,						//�ڰ�
	TEXT("�ü�ü"));			//��Ʈ

	����

	//font1 = CreateFont(100, 0, 0, 0, 300, false, false, false,
	//	HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�޸ձ���"));
	//
	//oldFont = (HFONT)SelectObject(getMemDC(), font1);
	//sprintf(str, "ġŲ�Ա��ʹ�");
	//TextOut(getMemDC(), 10, 100, str, strlen(str));
	//DeleteObject(font1);

	*/

	void frameCycle(image* img, int delay)
	{
		if ((int)(TIMEMANAGER->getWorldTime() / TIMEMANAGER->getElapsedTime()) % delay == 0)
		{
			if (img->getFrameX() >= img->getMaxFrameX())
			{
				img->setFrameX(-1);
			}
			img->setFrameX(img->getFrameX() + 1);

		}
	}

	void frameCycle(string keyName, int delay)
	{
		if ((int)(TIMEMANAGER->getWorldTime() / TIMEMANAGER->getElapsedTime()) % delay == 0)
		{
			if (IMAGEMANAGER->findImage(keyName.c_str())->getFrameX() >= IMAGEMANAGER->findImage(keyName.c_str())->getMaxFrameX())
			{
				IMAGEMANAGER->findImage(keyName.c_str())->setFrameX(-1);
			}
			IMAGEMANAGER->findImage(keyName.c_str())->setFrameX(IMAGEMANAGER->findImage(keyName.c_str())->getFrameX() + 1);

		}

	}

	void frameCycle(string keyName, int delay, bool reverse)
	{
		if (reverse)
		{
			static bool tmp = false;

			if ((int)(TIMEMANAGER->getWorldTime() / TIMEMANAGER->getElapsedTime()) % delay == 0)
			{
				if (!tmp)
				{
						if (IMAGEMANAGER->findImage(keyName.c_str())->getFrameX() >= IMAGEMANAGER->findImage(keyName.c_str())->getMaxFrameX())
						{
							IMAGEMANAGER->findImage(keyName.c_str())->setFrameX(IMAGEMANAGER->findImage(keyName.c_str())->getMaxFrameX()-2);
							tmp = true;
						}
						IMAGEMANAGER->findImage(keyName.c_str())->setFrameX(IMAGEMANAGER->findImage(keyName.c_str())->getFrameX() + 1);

				}
				else
				{
						if (IMAGEMANAGER->findImage(keyName.c_str())->getFrameX() <=0)
						{
							IMAGEMANAGER->findImage(keyName.c_str())->setFrameX(2);

							tmp = false;
						}
						IMAGEMANAGER->findImage(keyName.c_str())->setFrameX(IMAGEMANAGER->findImage(keyName.c_str())->getFrameX() - 1);

				}

			}

		}
		else
		{
			if ((int)(TIMEMANAGER->getWorldTime() / TIMEMANAGER->getElapsedTime()) % delay == 0)
			{
				IMAGEMANAGER->findImage(keyName.c_str())->setFrameX(IMAGEMANAGER->findImage(keyName.c_str())->getFrameX() + 1);

				if (IMAGEMANAGER->findImage(keyName.c_str())->getFrameX() >= IMAGEMANAGER->findImage(keyName.c_str())->getMaxFrameX())
				{
					IMAGEMANAGER->findImage(keyName.c_str())->setFrameX(0);
				}
			}

		}

	}



}

