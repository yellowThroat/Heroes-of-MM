#pragma once
#include "hero.h"

class knight : public hero
{
private:

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	knight();
	~knight();

};