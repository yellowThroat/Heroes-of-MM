#pragma once

#define TILESIZE 32

#define MAXTILE 36

#define MINISIZE (216 / MAXTILE)

enum TILE
{
	TILE_GREEN,
	TILE_WATER,
	TILE_SNOW,
	TILE_NONE,
	TILE_END
};

enum MAPOBJECT
{
	OBJ_NONE,

	OBJ_OBSTACLE,
	OBJ_CHEST,
	OBJ_ARTIFACT,
	OBJ_CRETURE,
	OBJ_RESOURCE,
	OBJ_EVENT,

	OBJ_END


};

enum EVENT
{
	EV_LVUP,
	EV_LUCK,
	EV_SKILL,
	EV_MAGIC,
	EV_END
};

enum MINE
{
	MINE_GOLD,
	MINE_CRYSTAL,
	MINE_WOOD,
	MINE_IRON,
	MINE_SULFUR,
	MINE_MERCURY,
	MINE_GEM,
	MINE_END
};

enum CAMP
{
	CAMP_CASTLE,
	CAMP_DUNGEON,
	CAMP_END
};

enum TILEVIEW
{
	TILEVIEW_DARK,
	TILEVIEW_
};

enum CATEGORY
{
	CATE_NULL,
	CATE_TILE,
	CATE_ROAD,
	CATE_OBSTACLE,
	CATE_UNIT,
	CATE_RESOURCE,
	CATE_OBJ,
	CATE_END
};

struct tagTileInfo
{
	TILE tile;
	image* img;
	image* miniImg;
	bool isChanged;
	int sourX, sourY;
	int destX, destY;
	int miniX, miniY;

};

struct tagObjInfo
{
	MAPOBJECT obj;
	image* img;
	int sourX, sourY;
	int destX, destY;

};

//========= 주변 타일 검출==========
#define LEFTTOP				0x00001
#define MIDDLETOP			0x00002
#define RIGHTTOP			0x00004
#define LEFTMIDDLE			0x00008
#define RIGHTMIDDLE			0x00010
#define LEFTBOTTOM			0x00020
#define MIDDLEBOTTOM		0x00040
#define RIGHTBOTTOM			0x00080

//========= 모서리 정하기 ===========
#define EDGE1		LEFTTOP			+ MIDDLETOP		+ LEFTMIDDLE		// 좌 상
#define EDGE2		MIDDLETOP		+ RIGHTTOP		+ RIGHTMIDDLE		// 우 상
#define EDGE3		LEFTMIDDLE		+ LEFTBOTTOM	+ MIDDLEBOTTOM		// 좌 하
#define EDGE4		MIDDLEBOTTOM	+ RIGHTBOTTOM	+ RIGHTMIDDLE		// 우 하

//========= 상 하 좌 우 =============
#define LEFT		LEFTTOP			+ LEFTMIDDLE	+ LEFTBOTTOM
#define RIGHT		RIGHTTOP		+ RIGHTMIDDLE	+ RIGHTBOTTOM
#define UP			LEFTTOP			+ MIDDLETOP		+ RIGHTTOP
#define DOWN		LEFTBOTTOM		+ MIDDLEBOTTOM	+ RIGHTBOTTOM

