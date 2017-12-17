#pragma once
#include "camp.h"

class dungeon : public camp
{
private:

public :

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	dungeon();
	~dungeon();



};