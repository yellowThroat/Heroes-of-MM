#pragma once
#include "gameNode.h"


class hero : public gameNode
{
private:
	tagHero _myHero;
	
	POINT _pointArr;
	POINT _destination;

private:
	float _x;
	float _y;

	
	
public:

	HRESULT init(POINT point, tagHero hero);
	void release(void);
	void update(void);
	void render(void);

	//========== D R A W =========
	void fieldDraw(void);


	//========== S E T ============
	void setAngle(void);
	void setCordinate(void);
	void heroMove(void);

	//============= G E T T E R  ============
	tagHero getHeroInfo() { return _myHero; }


	//============= S E T T E R =============
	void setHeroInfo(tagHero heroInfo) { _myHero = heroInfo; }

	hero();
	~hero();
};