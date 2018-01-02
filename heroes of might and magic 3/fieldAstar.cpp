#include "stdafx.h"
#include "playMap.h"

vector<POINT> playMap::getPath(int x, int y, int destX, int destY)
{
	bool end = false;
	bool findPath = false;
	vector<POINT> shortestPath;
	POINT point;
	tagPathFindSecond currentNode;
	tagPathFind findNode;

	ZeroMemory(&currentNode, sizeof(tagPathFind));


	if (destX < 0 || destY < 0 || destX >= MAXTILE || destY >= MAXTILE) return shortestPath;



	if ((_map[destX][destY].isClosed && !_map[destX][destY].loot)||
		_map[destX][destY].tile == TILE_WATER ) return shortestPath;


	//======= 벡터 설겆이 ==========
	_openlist.clear();
	_closelist.clear();
	shortestPath.clear();

	
	currentNode.nodeX = x;
	currentNode.nodeY = y;
	currentNode.parentX = x;
	currentNode.parentY = y;
	currentNode.g = 0;
	currentNode.direction = 0;
	if (_road[currentNode.nodeX][currentNode.nodeY].road == ROAD_NORMAL ||
		_road[currentNode.nodeX][currentNode.nodeY].road == ROAD_ROCK)
	{
		currentNode.road = 2;
	}
	else currentNode.road = 0;

	if (abs(destX - currentNode.nodeX) >= abs(destY - currentNode.nodeY))
	{
		int diagonal = abs(destY - currentNode.nodeY);
		int vertical = abs(destX - currentNode.nodeX) - diagonal;

		currentNode.h = diagonal * 140 + vertical * 100;

		if (currentNode.road == 2 && diagonal) currentNode.h -= 35;
		else if (currentNode.road == 2 && !diagonal) currentNode.h -= 25;
	}
	else
	{
		int diagonal = abs(destX - currentNode.nodeX);
		int vertical = abs(destY - currentNode.nodeY) - diagonal;
		currentNode.h = diagonal * 140 + vertical * 100;

		if (currentNode.road == 2 && diagonal) currentNode.h -= 35;
		else if (currentNode.road == 2 && !diagonal) currentNode.h -= 25;

	}
	currentNode.f = currentNode.g + currentNode.h;
	_closelist.push_back(currentNode);

	

	//========== 끝까지 갈때까지 반복해야 하는데..........
	//========= openlist 뒤져서 목표지점인게 있기전까진 반복
	while(true)
	{

		//============ 선택된건 클로즈에 넣고
		if (_openlist.size() != 0)
		{
			ZeroMemory(&currentNode, sizeof(tagPathFind));
			currentNode.nodeX = _openlist[0].nodeX;
			currentNode.nodeY = _openlist[0].nodeY;
			currentNode.f = _openlist[0].f;
			currentNode.g = _openlist[0].g;
			currentNode.h = _openlist[0].h;
			currentNode.parentX = _openlist[0].parentX;
			currentNode.parentY = _openlist[0].parentY;
			currentNode.road = _openlist[0].road;
			currentNode.direction = _openlist[0].direction;
			_openlist.erase(_openlist.begin());


			_closelist.push_back(currentNode);

		}


		//================ 먼저 주변에 더 나은 경로가 있는지 탐색 ============
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0) continue;
				if (currentNode.nodeX + i < 0 || currentNode.nodeX + i >= MAXTILE ||
					currentNode.nodeY + j < 0 || currentNode.nodeY + j >= MAXTILE) continue;

				if (_map[currentNode.nodeX + i][currentNode.nodeY + j].entrance && j == 1 && i == 0) continue;

				//if (alreadyOpend(currentNode.nodeX + i, currentNode.nodeY + j))
				//{
				//	ZeroMemory(&findNode, sizeof(tagPathFind));
				//	for (int k = 0; k < _openlist.size(); k++)
				//	{
				//		if (_openlist[k].nodeX == currentNode.nodeX + i &&
				//			_openlist[k].nodeY == currentNode.nodeY + j)
				//		{
				//			findNode.nodeX = _openlist[k].nodeX;
				//			findNode.nodeY = _openlist[k].nodeY;
				//			findNode.f = _openlist[k].f;
				//			findNode.g = _openlist[k].g;
				//			findNode.h = _openlist[k].h;
				//			findNode.parentX = _openlist[k].parentX;
				//			findNode.parentY = _openlist[k].parentY;
				//			findNode.direction = _openlist[k].direction;
				//			findNode.road = _openlist[k].road;
				//			break;
				//		}
				//	}
				//
				//
				//	if (i == 0 || j == 0)
				//	{
				//		if (findNode.road == 2)
				//		{
				//			if (currentNode.g >= findNode.g + 75)
				//			{
				//				_closelist[_closelist.size() - 1].g = findNode.g + 75;
				//				_closelist[_closelist.size() - 1].f =
				//					_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
				//				_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
				//				_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
				//			}
				//		
				//		
				//		
				//		
				//		}
				//		else
				//		{
				//			if (currentNode.g >= findNode.g + 100)
				//			{
				//				_closelist[_closelist.size() - 1].g = findNode.g + 100;
				//				_closelist[_closelist.size() - 1].f =
				//					_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
				//				_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
				//				_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
				//			}
				//		
				//		}
				//
				//
				//
				//
				//
				//
				//		//if (currentNode.g >=findNode.g + 10)
				//		//{
				//		//	_closelist[_closelist.size() - 1].g = findNode.g + 10;
				//		//	_closelist[_closelist.size() - 1].f = 
				//		//		_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
				//		//	_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
				//		//	_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
				//		//}
				//	}
				//	else
				//	{
				//		if (findNode.road == 2)
				//		{
				//			if (currentNode.g >= findNode.g + 105)
				//			{
				//				_closelist[_closelist.size() - 1].g = findNode.g + 105;
				//				_closelist[_closelist.size() - 1].f =
				//					_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
				//				_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
				//				_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
				//			}
				//		
				//		
				//		
				//		
				//		}
				//		else
				//		{
				//			if (currentNode.g >= findNode.g + 140)
				//			{
				//				_closelist[_closelist.size() - 1].g = findNode.g + 140;
				//				_closelist[_closelist.size() - 1].f =
				//					_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
				//				_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
				//				_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
				//			}
				//		
				//		}
				//
				//
				//
				//
				//
				//		//if (currentNode.g >= findNode.g + 14)
				//		//{
				//		//	_closelist[_closelist.size() - 1].g = findNode.g + 14;
				//		//	_closelist[_closelist.size() - 1].f =
				//		//		_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
				//		//	_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
				//		//	_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
				//		//}
				//
				//	}
				//	currentNode.g = _closelist[_closelist.size() - 1].g;
				//	currentNode.f = _closelist[_closelist.size() - 1].f;
				//	currentNode.parentX = _closelist[_closelist.size() - 1].parentX;
				//	currentNode.parentY = _closelist[_closelist.size() - 1].parentY;
				//
				//}
				if(alreadyClosed(currentNode.nodeX + i, currentNode.nodeY + j))
				{
					if (currentNode.nodeX + i < 0 || currentNode.nodeX + i >= MAXTILE ||
						currentNode.nodeY + j < 0 || currentNode.nodeY + j >= MAXTILE) continue;

					if (_map[currentNode.nodeX + i][currentNode.nodeY + j].entrance && j == 1) continue;



					ZeroMemory(&findNode, sizeof(tagPathFind));
					for (int k = 0; k < _closelist.size(); k++)
					{
						if (_closelist[k].nodeX == currentNode.nodeX + i &&
							_closelist[k].nodeY == currentNode.nodeY + j)
						{
							findNode.nodeX = _closelist[k].nodeX;
							findNode.nodeY = _closelist[k].nodeY;
							findNode.f = _closelist[k].f;
							findNode.g = _closelist[k].g;
							findNode.h = _closelist[k].h;
							findNode.parentX = _closelist[k].parentX;
							findNode.parentY = _closelist[k].parentY;
							break;
						}
					}


					if (i == 0 || j == 0)
					{
						if (findNode.road == 2)
						{
							if (currentNode.g >= findNode.g + 75)
							{
								_closelist[_closelist.size() - 1].g = findNode.g + 75;
								_closelist[_closelist.size() - 1].f =
									_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
								_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
								_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
							}
						
						
						
						
						}
						else
						{
							if (currentNode.g >= findNode.g + 100)
							{
								_closelist[_closelist.size() - 1].g = findNode.g + 100;
								_closelist[_closelist.size() - 1].f =
									_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
								_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
								_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
							}
						
						}




						//if (currentNode.g >= findNode.g + 10)
						//{
						//	_closelist[_closelist.size() - 1].g = findNode.g + 10;
						//	_closelist[_closelist.size() - 1].f =
						//		_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
						//	_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
						//	_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
						//}
					}
					else 
					{
						if (findNode.road == 2)
						{
							if (currentNode.g >= findNode.g + 105)
							{
								_closelist[_closelist.size() - 1].g = findNode.g + 105;
								_closelist[_closelist.size() - 1].f =
									_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
								_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
								_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
							}
						
						
						
						
						}
						else
						{
							if (currentNode.g >= findNode.g + 140)
							{
								_closelist[_closelist.size() - 1].g = findNode.g + 140;
								_closelist[_closelist.size() - 1].f =
									_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
								_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
								_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
							}
						
						}



						//if (currentNode.g >= findNode.g + 14)
						//{
						//	_closelist[_closelist.size() - 1].g = findNode.g + 14;
						//	_closelist[_closelist.size() - 1].f =
						//		_closelist[_closelist.size() - 1].g + _closelist[_closelist.size() - 1].h;
						//	_closelist[_closelist.size() - 1].parentX = findNode.nodeX;
						//	_closelist[_closelist.size() - 1].parentY = findNode.nodeY;
						//}

					}
					currentNode.g = _closelist[_closelist.size() - 1].g;
					currentNode.f = _closelist[_closelist.size() - 1].f;
					currentNode.parentX = _closelist[_closelist.size() - 1].parentX;
					currentNode.parentY = _closelist[_closelist.size() - 1].parentY;

				}


			}

		}

		//====== 그 주변이 열려 있다면 오픈에 넣고 parentX Y 설정 =======
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i + currentNode.nodeX < 0 || i + currentNode.nodeX >= MAXTILE ||
					j + currentNode.nodeY < 0 || j + currentNode.nodeY >= MAXTILE) continue;
				if (j == 1 && _map[currentNode.nodeX + i][currentNode.nodeY + j].entrance) continue;
				if (j == -1 && _map[currentNode.nodeX][currentNode.nodeY].entrance) continue;




				if ((!_map[currentNode.nodeX + i][currentNode.nodeY + j].isClosed			||
					(currentNode.nodeX + i == destX && currentNode.nodeY + j == destY))		&&
					!isClosed(currentNode.nodeX + i, currentNode.nodeY + j)					&&
					_map[currentNode.nodeX + i][currentNode.nodeY + j].tile != TILE_WATER   ) 
				{

					ZeroMemory(&findNode, sizeof(tagPathFind));
					findNode.nodeX = currentNode.nodeX + i;
					findNode.nodeY = currentNode.nodeY + j;
					findNode.g = currentNode.g;
					findNode.parentX = currentNode.nodeX;
					findNode.parentY = currentNode.nodeY;						
				
					if (_road[findNode.nodeX][findNode.nodeY].road == ROAD_NORMAL ||
						_road[findNode.nodeX][findNode.nodeY].road == ROAD_ROCK)
					{
						findNode.road = 2;
					}
					else findNode.road = 0;




					//=======넣기 전에 FGH값 계산을 하고 =========
					if (i == 0 || j == 0)
					{
						if (_road[currentNode.nodeX][currentNode.nodeY].road == ROAD_NORMAL ||
							_road[currentNode.nodeX][currentNode.nodeY].road == ROAD_ROCK)
						{
							findNode.g += 75;
						}
						else findNode.g += 100;
						
						findNode.direction = 1;



						//findNode.g += 10;
					}
					else
					{
						if (_road[currentNode.nodeX][currentNode.nodeY].road == ROAD_NORMAL ||
							_road[currentNode.nodeX][currentNode.nodeY].road == ROAD_ROCK)
						{
							findNode.g += 105;
						}
						else findNode.g += 140;
						
						
						findNode.direction = 0;

						//findNode.g += 14;
					}

					if (abs(destX - findNode.nodeX) >= abs(destY - findNode.nodeY))
					{
						int diagonal = abs(destY - findNode.nodeY);
						int vertical = abs(destX - findNode.nodeX) - diagonal;

						findNode.h = diagonal * 140 + vertical * 100;

						if (findNode.road == 2 && diagonal) findNode.h -= 35;
						else if (findNode.road == 2 && !diagonal) findNode.h -= 25;
					}
					else
					{
						int diagonal = abs(destX - findNode.nodeX);
						int vertical = abs(destY - findNode.nodeY) - diagonal;
						findNode.h = diagonal * 140 + vertical * 100;

						if (findNode.road == 2 && diagonal) findNode.h -= 35;
						else if (findNode.road == 2 && !diagonal) findNode.h -= 25;
					}
					findNode.f = findNode.g + findNode.h;

					_openlist.push_back(findNode);
				}
			}
		}

		//============= 길찾는걸 포기할때
		if (_openlist.size() == 0 ||  _closelist.size() >1000)
		{
			end = true;
		}

		//================ 길을 찾은거임
		for (int i = 0; i < _openlist.size(); i++)
		{
			if (_openlist[i].nodeX == destX && _openlist[i].nodeY == destY)
			{
				end = true;
				findPath = true;

				tagPathFindSecond tmp;
				tmp.f = _openlist[i].f;
				tmp.g = _openlist[i].g;
				tmp.h = _openlist[i].h;
				tmp.nodeX = _openlist[i].nodeX;
				tmp.nodeY = _openlist[i].nodeY;
				tmp.parentX = _openlist[i].parentX;
				tmp.parentY = _openlist[i].parentY;


				_closelist.push_back(tmp);
				
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
			for (int i = 0; i < _closelist.size(); i++)
			{
				if (_closelist[i].nodeX == shortestPath[0].x &&
					_closelist[i].nodeY == shortestPath[0].y)
				{
					point.x = _closelist[i].parentX;
					point.y = _closelist[i].parentY;


					shortestPath.insert(shortestPath.begin(),point);

				}


				if (point.x == x && point.y == y)
				{
					return shortestPath;
				}

				
			}
		}
	}
	else
	{
		sort(_closelist.begin(), _closelist.end());
		point.x = _closelist[0].nodeX;
		point.y = _closelist[0].nodeY;
		shortestPath.push_back(point);
		while (true)
		{
			for (int i = 0; i < _closelist.size(); i++)
			{
				if (_closelist[i].nodeX == shortestPath[0].x &&
					_closelist[i].nodeY == shortestPath[0].y)
				{
					point.x = _closelist[i].parentX;
					point.y = _closelist[i].parentY;


					shortestPath.insert(shortestPath.begin(), point);
					break;
				}



			}
				if (point.x == x && point.y == y)
				{
					return shortestPath;
				}
		}

	}


}

bool playMap::isClosed(int x, int y)
{
	for (auto i : _openlist)
	{
		if (i.nodeX == x && i.nodeY == y)
		{
			return true;
		}
	}

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

bool playMap::alreadyClosed(int x, int y)
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
