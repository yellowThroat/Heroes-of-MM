#pragma once
#include "singletonBase.h"

class dataBase : public singletonBase<dataBase>
{
private:
	int _saveNum;



public:

	HRESULT init(void);
	void release(void);


	//========= S E T T E R =========
	void setSaveNum(int saveNum) { _saveNum = saveNum; }

	//========= G E T T E R ==========
	int getSaveNum() { return _saveNum; }

	dataBase();
	~dataBase();

};