#include "stdafx.h"
#include "dungeon.h"

dungeon::dungeon() {}
dungeon::~dungeon() {}

HRESULT dungeon::init()
{

	return S_OK;
}

void dungeon::release(void)
{

}

void dungeon::update(void)
{
	camp::update();
}

void dungeon::render(void)
{
	camp::render();
}