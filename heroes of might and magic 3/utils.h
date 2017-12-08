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
#define FLOAT_EPSILON 0.001f //실수의 가장 작은 단위

namespace IOTA_UTIL
{
	//거리 가져오는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	//각도 가져오는 함수
	float getAngle(float x1, float y1, float x2, float y2);

	//각도 가져오는 함수 2
	float getAngle(float x, float y);

	//숫자 적는 함수
	void NumberMacro(HDC hdc, int num, int x, int y, int su);	

	//이미지 회전 프레임
	void frameRotation(image* img, int division, float angle, bool frameX, bool clockwise);

}