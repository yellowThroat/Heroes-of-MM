#include "stdafx.h"
#include "dataBase.h"

dataBase::dataBase() {}
dataBase::~dataBase() {}

HRESULT	dataBase::init()
{
	_miniMap = new image;
	_saveNum = 0;
	_playCameraX = _playCameraY = 0;
	//loadFileList();
	_moveSpeed = 4;
	return S_OK;
}

void dataBase::release(void)
{

}

void dataBase::setSaveName(string saveName)
{
	string tmp;
	tmp = TEXT("map/");

	for (int i = 0; i < saveName.length(); i++)
	{
		tmp.push_back(saveName.at(i));
	}

	tmp.push_back('.');
	tmp.push_back('m');
	tmp.push_back('a');
	tmp.push_back('p');

	_saveFileName = tmp;
	
	tmp.clear();

	tmp = TEXT("map/");
	for (int i = 0; i < saveName.length(); i++)
	{
		tmp.push_back(saveName.at(i));
	}

	tmp.push_back('.');
	tmp.push_back('b');
	tmp.push_back('m');
	tmp.push_back('p');
	


	

	IMAGEMANAGER->addImage("play_miniMap", tmp.c_str(), 144, 144,true,RGB(255,0,255));
}


void dataBase::setVBuildSaveInfo(tagSaveInfo save)
{

}

void dataBase::loadFileList(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("map/saveFileList.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _saveFile, sizeof(SAVE)*MAXSAVE, &read, NULL);

	CloseHandle(file);
	
	for (int i = 0; i < MAXSAVE; i++)
	{
		string tmp;
		tmp = TEXT("map/");

		for (int j = 0; j < _saveFile[i].fileName.size(); j++)
		{
			tmp.push_back(_saveFile[i].fileName.at(j));
		}

		tmp.push_back('.');
		tmp.push_back('b');
		tmp.push_back('m');
		tmp.push_back('p');

	

		
		char tmp1[10];
		IMAGEMANAGER->addImage(itoa(i, tmp1, 10), tmp.c_str(), 144, 144, true, RGB(255, 0, 255));
		int a = 0;
	}

}