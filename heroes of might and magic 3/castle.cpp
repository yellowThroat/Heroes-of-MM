#include "stdafx.h"
#include "castle.h"

castle::castle() {}
castle::~castle() {}

HRESULT castle::init()
{

	return S_OK;
}

void castle::release()
{

}

void castle::update(void)
{
	camp::update();
}

void castle::render(void)
{
	camp::render();

}
