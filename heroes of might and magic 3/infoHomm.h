#pragma once

#define TILESIZE 32

#define MAXTILE 108

enum TILE
{
	TILE_NONE,
	TILE_GREEN,
	TILE_WATER,
	TILE_SNOW,
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

struct tagTileInfo
{
	image* img;
	int sourX, sourY;
	int destX, destY;
	TILE tile;

};

struct tagObjInfo
{
	image* img;
	int sourX, sourY;
	int destX, destY;
	MAPOBJECT obj;

};