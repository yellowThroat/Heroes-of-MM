#pragma once
#include "singletonBase.h"

class dataBase : public singletonBase<dataBase>
{
private:
	int _saveNum;
	int _moveSpeed;
	int _bgmVolume;
	int _effectVolume;
	float _playCameraX;
	float _playCameraY;
	string _saveFileName;
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
	void setBgmVolume(int volume) { _bgmVolume = volume; }
	void setEffectVolume(int volume) { _effectVolume = volume; }
	//========= G E T T E R ==========
	int getSaveNum() { return _saveNum; }
	int getMoveSpeed() { return _moveSpeed; }
	int getBgmVolume() { return _bgmVolume; }
	int getEffectVolume() { return _effectVolume; }
	float getPlayCameraX() { return _playCameraX; }
	float getPlayCameraY() { return _playCameraY; }
	string getSaveName() { return _saveFileName; }
	SAVE getFileList() { return _saveFile[_saveNum]; }

	
	dataBase();
	~dataBase();

};