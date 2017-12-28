#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <algorithm>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "iniDataManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "txtData.h"
#include "collision.h"
#include "infoHomm.h"
#include "dataBase.h"
#include "heroInfo.h"

using namespace std;
using namespace IOTA_UTIL;
using namespace HOMM_HERO;

//===============================================
// ## ������ ���� ������ ## 2017.07. 28 ##
//===============================================

#define WINNAME (LPTSTR)(TEXT("Iota Team"))
#define WINSTARTX 50
#define WINSTARTY 10
#define WINSIZEX 1100
#define WINSIZEY 600 
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define INIDATA iniDataManager::getSingleton()
#define DATABASE dataBase::getSingleton()

//==================================
// ## ��ũ�� �Լ� ## 17.08.07 ##
//==================================

#define SAFE_DELETE(p)  {if(p) {delete(p); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}

//===================================
// ## ���� ���� ## 17.08.07 ##
//===================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

extern BOOL _leftButtonDown;