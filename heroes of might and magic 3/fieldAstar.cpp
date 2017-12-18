#include "stdafx.h"
#include "playMap.h"

vector<tagTileInfo> playMap::aStar(POINT currentPoint, POINT goalPoint)
{
	_openlist.clear();
	_closelist.clear();

	//목적지까지 가는 길 저장할 벡터

	vector<tagTileInfo> way;

	//시작 지점 설정

	tagAStar startPoint;

	startPoint.g = 0;
	startPoint.h = getDistance(currentPoint.x, currentPoint.y, goalPoint.x, goalPoint.y);
	startPoint.f = startPoint.g + startPoint.h;
	startPoint.x = currentPoint.x / TILESIZE;
	startPoint.y = currentPoint.y / TILESIZE;
	startPoint.px = startPoint.x;
	startPoint.py = startPoint.y;
	//
	//시작 지점을 colselist에 push_back
	_closelist.push_back(startPoint);
	//8방향 탐색 후 열린 목록에 추가
	add_eightway(startPoint, goalPoint);

	//openlist에 목적지가 있는 경우?
	if (search_openlist_exsist(goalPoint.x / TILESIZE, goalPoint.y / TILESIZE))
	{
		way.push_back(_map[goalPoint.x / TILESIZE][goalPoint.y / TILESIZE]);
		way.push_back(_map[currentPoint.x / TILESIZE][currentPoint.y / TILESIZE]);

		return way;
	}

	tagAStar curV;
	bool findWay;
	while (true)
	{
		//openlist가 비었거나 목적지를 찾은 경우
		//사이즈가 0일때는 실행하지 앟는다.
		if (_openlist.size() == 0)
		{
			findWay = false;
			break;
		}
		else if (search_openlist_exsist(goalPoint.x / TILESIZE, goalPoint.y / TILESIZE))
		{
			findWay = true;
			break;
		}
		curV = pop_openlist();
		add_closelist(curV);

		add_eightway(curV, goalPoint);
	}

	//길이 있을 경우
	if (findWay)
	{

		way.push_back(_map[curV.x][curV.y]);
		while (true)
		{
			if (curV.x == currentPoint.x / TILESIZE && curV.y == currentPoint.y / TILESIZE)
			{
				break;
			}
			else
			{
				curV = pop_closelist(curV.px, curV.py);
				way.push_back(_map[curV.x][curV.y]);
			}
		}
		way.insert(way.begin(), _map[goalPoint.x / TILESIZE][goalPoint.y / TILESIZE]);
		return way;
	}
	


}

void playMap::add_openlist(tagAStar v)
{
	for (auto i : _openlist)
	{
		if (i.x == v.x && i.y == v.y)
		{
			return;
		}
	}
	for (auto i : _closelist)
	{
		if ((i.x == v.x && i.y == v.y))
		{

			return;
		}
	}
	_openlist.push_back(v);
	sort(_openlist.begin(), _openlist.end());
}