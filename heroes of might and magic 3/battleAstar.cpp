#include "stdafx.h"
#include "battle.h"

vector<POINT> battle::getPath(int x, int y, int destX, int destY, bool fly)
{
	vector<POINT> shortestPath;
	bool findPath = false;
	bool end = false;
	POINT point;
	tagHexaFind currentNode;
	tagHexaFind findNode;

	ZeroMemory(&currentNode, sizeof(tagHexaFind));
	ZeroMemory(&findNode, sizeof(tagHexaFind));

	if (destX < 0 || destY < 0 || destX >= MAXGRIDX || destY >= MAXGRIDY) return shortestPath;

	if (_battleArr[destX][destY].closed) return shortestPath;

	_openlist.clear();
	_closelist.clear();
	shortestPath.clear();

	currentNode.nodeX = x;
	currentNode.nodeY = y;
	currentNode.parentX = x;
	currentNode.parentY = y;
	currentNode.g = 0;
	currentNode.h = getValueH(x, y, destX, destY);
	currentNode.f = currentNode.g + currentNode.h;

	_closelist.push_back(currentNode);


	while (true)
	{
		if (_openlist.size() != 0)
		{
			ZeroMemory(&currentNode, sizeof(tagHexaFind));
			currentNode.nodeX = _openlist[0].nodeX;
			currentNode.nodeY = _openlist[0].nodeY;
			currentNode.f = _openlist[0].f;
			currentNode.g = _openlist[0].g;
			currentNode.h = _openlist[0].h;
			currentNode.parentX = _openlist[0].parentX;
			currentNode.parentY = _openlist[0].parentY;

			_openlist.erase(_openlist.begin());

			_closelist.push_back(currentNode);
		}
		
		//for (int i = -1; i <= 1 ; i++)
		//{
		//	for (int j = -1; j <= 1; j++)
		//	{
		//		if (i == 0 && j == 0) continue;
		//
		//		if (currentNode.nodeX + i < 0 || currentNode.nodeX + i >= MAXGRIDX ||
		//			currentNode.nodeY + j < 0 || currentNode.nodeY + j >= MAXGRIDX) continue;
		//
		//		//if (currentNode.nodeY % 2 == 0)
		//		//{
		//		//	if (i == -1 && (j == -1 || j == 1)) continue;
		//		//}
		//		//else if (currentNode.nodeY % 2 == 1)
		//		//{
		//		//	if (i == 1 && (j == -1 || j == 1)) continue;
		//		//}
		//		//
		//		//if (_battleArr[currentNode.nodeX][currentNode.nodeY].closed) continue;
		//		
		//		if (alreadyClosed(currentNode.nodeX + i, currentNode.nodeY + j))
		//		{
		//			ZeroMemory(&findNode, sizeof(tagHexaFind));
		//
		//			for (int k = 0; k < _closelist.size(); k++)
		//			{
		//				if (_closelist[k].nodeX == currentNode.nodeX + i &&
		//					_closelist[k].nodeY == currentNode.nodeY + j)
		//				{
		//					findNode.nodeX = _closelist[k].nodeX;
		//					findNode.nodeY = _closelist[k].nodeY;
		//					findNode.f = _closelist[k].f;
		//					findNode.g = _closelist[k].g;
		//					findNode.h = _closelist[k].h;
		//					findNode.parentX = _closelist[k].parentX;
		//					findNode.parentY = _closelist[k].parentY;
		//					break;
		//				}
		//			}
		//
		//			if (findNode.g + 1 <= currentNode.g)
		//			{
		//				_closelist[_closelist.size() - 1].g = findNode.g + 1;
		//				_closelist[_closelist.size() - 1].f =
		//					_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
		//				_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
		//				_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
		//				
		//			}
		//
		//			currentNode.g = _closelist[_closelist.size() - 1].g;
		//			currentNode.f = _closelist[_closelist.size() - 1].f;
		//			currentNode.parentX = _closelist[_closelist.size() - 1].parentX;
		//			currentNode.parentY = _closelist[_closelist.size() - 1].parentY;
		//		}
		//	}
		//}

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0) continue;

				if (currentNode.nodeX + i < 0 || currentNode.nodeX + i >= MAXGRIDX ||
					currentNode.nodeY + j < 0 || currentNode.nodeY + j >= MAXGRIDX) continue;

				if (currentNode.nodeY % 2 == 0)
				{
					if (i == -1 && (j == -1 || j == 1)) continue;
				}
				else if (currentNode.nodeY % 2 == 1)
				{
					if (i == 1 && (j == -1 || j == 1)) continue;
				}

				if (alreadyClosed(currentNode.nodeX + i, currentNode.nodeY + j)) continue;
				if (alreadyOpend(currentNode.nodeX + i, currentNode.nodeY + j)) continue;


				if (!fly && _battleArr[currentNode.nodeX + i][currentNode.nodeY + j].closed) continue;

				ZeroMemory(&findNode, sizeof(tagHexaFind));
				findNode.nodeX = currentNode.nodeX + i;
				findNode.nodeY = currentNode.nodeY + j;
				findNode.g = currentNode.g +1;
				findNode.parentX = currentNode.nodeX;
				findNode.parentY = currentNode.nodeY;
				findNode.h = getValueH(findNode.nodeX, findNode.nodeY, destX, destY);
				findNode.f = findNode.g + findNode.h;

				_openlist.push_back(findNode);


			}
		}

		if (_openlist.size() == 0) end = true;

		for (int i = 0; i < _openlist.size(); i++)
		{
			if (_openlist[i].nodeX == destX && _openlist[i].nodeY == destY)
			{
				end = true;
				findPath = true;

				_closelist.push_back(_openlist[i]);

				point.x = _openlist[i].nodeX;
				point.y = _openlist[i].nodeY;

				shortestPath.push_back(point);

				break;

			}
		}


		sort(_openlist.begin(), _openlist.end());



		if (end) break;
	}






	if (findPath)
	{
		while (true)
		{
			for (int i = _closelist.size() -1; i >= 0 ; i--)
			{
				if (_closelist[i].nodeX == shortestPath[0].x &&
					_closelist[i].nodeY == shortestPath[0].y)
				{
					point.x = _closelist[i].parentX;
					point.y = _closelist[i].parentY;

					shortestPath.insert(shortestPath.begin(), point);
					if(point.x == x && point.y == y) return shortestPath;

					break;
				}

			}
		}	
	}
	else
	{


		return shortestPath;

	}
}

int battle::getValueH(int x, int y, int destX, int destY)
{
	int h = 0;
	int dis = abs(destY - y);
	if (dis % 2 == 0)
	{
		h = dis;
		if (destX < x - dis / 2) h += (x - dis / 2) - destX;
		else if (destX > x + dis / 2) h += destX - (x + dis / 2);
	}
	else if (dis % 2 == 1)
	{
		h = dis;
		if (y % 2 == 0)
		{
			if (destX < x - dis / 2) h += (x - dis / 2) - destX;
			else if (destX > x + (dis + 1) / 2) h += destX - (x + (dis + 1) / 2);

		}
		else if (y % 2 == 1)
		{
			if (destX < x - (dis + 1) / 2) h += (x - (dis + 1) / 2) - destX;
			else if (destX > x + dis / 2) h += destX - (x + dis / 2);

		}
	}


	return h;
}

bool battle::alreadyClosed(int x, int y)
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

bool battle::alreadyOpend(int x, int y)
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