#pragma once
#include "image.h"

#define PI 3.141592654f
#define PI2 PI * 2

#define PI4 float(PI/4.0f)
#define PI8 float(PI/8.0f)
#define PI16 float(PI/16.0f)
#define PI32 float(PI/32.0f)
#define PI64 float(PI/64.0f)
#define PI128 float(PI/128.0f)

#define FLOAT_TO_INT(f1) static_cast<int>(f1)
#define FLOAT_EPSILON 0.001f //�Ǽ��� ���� ���� ����

namespace IOTA_UTIL
{
	//�Ÿ� �������� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	//���� �������� �Լ�
	float getAngle(float x1, float y1, float x2, float y2);

	//���� �������� �Լ� 2
	float getAngle(float x, float y);

	//���� ���� �Լ�
	void NumberMacro(HDC hdc, int num, int x, int y, int su);	

	//�̹��� ȸ�� ������
	void frameRotation(image* img, int division, float angle, bool frameX, bool clockwise);

}