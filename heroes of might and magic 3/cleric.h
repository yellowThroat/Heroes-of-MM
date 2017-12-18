#pragma once
#include "hero.h"

class cleric : public hero
{
private:

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	cleric();
	~cleric();
};