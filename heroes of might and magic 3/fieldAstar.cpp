#include "stdafx.h"
#include "playMap.h"

vector<POINT> playMap::getPath(int x, int y, int destX, int destY)
{
	vector<POINT> shortestPath;
	POINT point;
	tagPathFind currentNode;
	tagPathFind findNode;

	ZeroMemory(&currentNode, sizeof(tagPathFind));

	//======= 벡터 설겆이 ==========
	_openlist.clear();
	_closelist.clear();

	
	currentNode.nodeX = x;
	currentNode.nodeY = y;
	currentNode.parentX = x;
	currentNode.parentY = y;
	currentNode.g = 0;
	
	_openlist.push_back(currentNode);

	

	//========== 끝까지 갈때까지 반복해야 하는데..........
	//========= openlist 뒤져서 목표지점인게 있기전까진 반복
	while(true)
	{
		sort(_openlist.begin(), _openlist.end());

		//============ 선택된건 클로즈에 넣고
		ZeroMemory(&currentNode, sizeof(tagPathFind));
		currentNode.nodeX = _openlist[0].nodeX;
		currentNode.nodeY = _openlist[0].nodeY;
		currentNode.g = _openlist[0].g;

		_openlist.erase(_openlist.begin());
		_closelist.push_back(currentNode);

		//====== 그 주변이 열려 있다면 오픈에 넣고 parentX Y 설정 =======
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{

				//=========== 이미 오픈리스트에 있다면 변경된 g값으로 f 계산
				if (alreadyOpend(currentNode.nodeX + i, currentNode.nodeY + j))
				{
					if(_openlist[openlistNum(currentNode.nodeX+ i,
						currentNode.nodeY + j)].g)
					 
						
				}
				//=========== 현재 노드의 주변이 열려 있는지 조건문

				if (!_map[currentNode.nodeX + i][currentNode.nodeY + j].isClosed &&
					!isClosed(currentNode.nodeX + i, currentNode.nodeY + j) &&
					!alreadyOpend(currentNode.nodeX + i, currentNode.nodeY +j))
				{
					ZeroMemory(&findNode, sizeof(tagPathFind));
					findNode.nodeX = currentNode.nodeX + i;
					findNode.nodeY = currentNode.nodeY + j;
					findNode.parentX = currentNode.nodeX;
					findNode.parentY = currentNode.nodeY;
					findNode.g = currentNode.g;

					//=======넣기 전에 FGH값 계산을 하고 =========
					if (i == 0 || j == 0)
					{
						findNode.g += 10;
					}
					else findNode.g += 14;

					if (abs(destX - findNode.nodeX) >= abs(destY - findNode.nodeY))
					{
						int diagonal = abs(destY - findNode.nodeY);
						int vertical = abs(destX - findNode.nodeX) - diagonal;

						findNode.h = diagonal * 14 + vertical * 10;
					}
					else
					{
						int diagonal = abs(destX - findNode.nodeX);
						int vertical = abs(destY - findNode.nodeY) - diagonal;
						findNode.h = diagonal * 14 + vertical * 10;
					}
					findNode.f = findNode.g + findNode.h;

					_openlist.push_back(findNode);
				}
			}
		}


		for (auto i : _openlist)
		{
			if (i.nodeX == destX && i.nodeY == destY)
			{


				break;
			}
		}


	}


}

bool playMap::isClosed(int x, int y)
{
	for (auto i : _closelist)
	{
		if (i.nodeX == x && i.nodeY == y)
		{
			return true;
		}
	}

	return false;
}

bool playMap::alreadyOpend(int x, int y)
{
	for (auto i : _openlist)
	{
		if (i.nodeX == x && i.nodeY == y)
		{
			return true;
		}
	}

	return false;

}

int playMap::openlistNum(int x, int y)
{
	for (int i = 0; i < _openlist.size(); i++)
	{
		if (_openlist[i].nodeX == x && _openlist[i].nodeY == y)
		{
			return i;
		}
	}


	return 0;
}