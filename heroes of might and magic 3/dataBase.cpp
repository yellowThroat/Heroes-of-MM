#include "stdafx.h"
#include "dataBase.h"

dataBase::dataBase() {}
dataBase::~dataBase() {}

HRESULT	dataBase::init()
{

	_saveNum = 0;
	_playCamera.x = _playCamera.y = 0;
	loadFileList();
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

}