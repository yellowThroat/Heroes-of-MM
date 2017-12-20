#pragma once
#include "singletonBase.h"

class dataBase : public singletonBase<dataBase>
{
private:
	int _saveNum;
	int _moveSpeed;
	string _saveFileName;
	float _playCameraX;
	float _playCameraY;
	tagSaveInfo _vBuildSaveInfo[MAXTILE][MAXTILE];
	SAVE _saveFile[MAXSAVE];
	image* _miniMap;

public:

	HRESULT init(void);
	void release(void);
	void loadFileList(void);

	//========= S E T T E R =========
	void setSaveNum(int saveNum) { _saveNum = saveNum; }
	void setSaveName(string saveName);
	void setPlayCameraX(float x) { _playCameraX = x; }
	void setPlayCameraY(float y) { _playCameraY = y; }
	void setVBuildSaveInfo(tagSaveInfo save);
	void setMoveSpeed(int speed) { _moveSpeed = speed; }
	//========= G E T T E R ==========
	int getSaveNum() { return _saveNum; }
	int getMoveSpeed() { return _moveSpeed; }
	string getSaveName() { return _saveFileName; }
	float getPlayCameraX() { return _playCameraX; }
	float getPlayCameraY() { return _playCameraY; }
	SAVE getFileList() { return _saveFile[_saveNum]; }
	
	dataBase();
	~dataBase();

};