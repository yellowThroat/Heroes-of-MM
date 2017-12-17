#pragma once
#include "camp.h"

class castle : public camp
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	castle();
	~castle();

};