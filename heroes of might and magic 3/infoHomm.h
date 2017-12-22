#pragma once

#define TILESIZE 32

#define MAXTILE 72

#define MINISIZE (144 / MAXTILE)

#define SHADOWALPHA 150

#define MINCAMERA -6
#define MAXCAMERAX 30
#define MAXCAMERAY 24

#define MAXSAVE 10

enum TILE
{
	TILE_GREEN,
	TILE_WATER,
	TILE_VOLCANO,
	TILE_SNOW,
	TILE_NONE,
	TILE_END
};

enum ROAD
{
	ROAD_NORMAL,
	ROAD_ROCK,
	ROAD_RIVER,
	ROAD_END
};

enum CREATURESTATE
{
	STATE_DOWN,
	STATE_FRONT,
	STATE_UP,
	STATE_MOVE,
	STATE_SELECT,
	STATE_SWITCH,
	STATE_IDLE,
	STATE_DAMAGED,
	STATE_DEAD,
	STATE_END
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
	EV_PHYSICAL,
	EV_MAGICAL,
	EV_SKILL,
	EV_MAGIC,
	EV_LUCK,
	EV_MORALE,
	EV_EXPLORE,
	EV_MOVEMENT,
	EV_RESOURCE,
	EV_NULL,
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
	MINE_NULL,
	MINE_END
};

enum CAMP
{
	CAMP_CASTLE,
	CAMP_DUNGEON,
	CAMP_NULL,
	CAMP_END
};

enum TILEVIEW
{
	TILEVIEW_DARK,
	TILEVIEW_BRIGHT,
	TILEVIEW_END
};

typedef enum CATEGORY
{
	CATE_TILE,
	CATE_ROAD,
	CATE_BUILDING,
	CATE_OBS,
	CATE_LOOTING,
	CATE_UNIT,
	CATE_NULL,
	CATE_END
}FIRST;

typedef enum SMALLCATE
{
	SMC_ZERO,
	SMC_ONE,
	SMC_TWO,
	SMC_THREE,
	SMC_FOUR,
	SMC_FIVE,
	SMC_NULL,
	SMC_END
}SECOND;

enum SELECTMENU
{
	MENU_MAIN,
	MENU_RESTART,
	MENU_SAVE,
	MENU_LOAD,
	MENU_NULL,
	MENU_END
};

enum CONFIRM
{
	CON_ANY,
	CON_SAVE,
	CON_END
};

typedef enum MAINMENUBUTTON
{
	MMB_NEW,
	MMB_LOAD,
	MMB_MAP,
	MMB_CREDIT,
	MMB_QUIT,
	MMB_END
}MMB;

struct tagTileInfo
{
	TILE tile;
	image* img;
	image* miniImg;
	bool isChanged;
	bool isClosed;
	bool entrance;
	int sourX, sourY;
	int destX, destY;
	int miniX, miniY;


};

struct tagRoadInfo
{
	ROAD road;
	image* img;
	bool isChanged;
	int sourX, sourY;
	int destX, destY;

};
struct tagCampInfo
{
	int player;
	int hall;
	int fort;
	int pub;
	int guild;
	int market;
	int forge;
	int level[7];
	int special[5];
	char name[256];

	tagCampInfo()
	{
		player = 0;
		hall = 1;
		fort = 0;
		pub = 0;
		guild = 0;
		market = 0;
		forge = 0;
		for (int i = 0; i < 7; i++)
		{
			level[i] = 0;
		}
		for (int i = 0; i < 5; i++)
		{
			special[i] = 0;
		}
	}
};

struct tagHero
{
	image* portraitLarge;
	image* portraitSmall;
	image* battle;
	image* field;
	image* fieldShadow;
	image* flag;

	char name[256];
	int str;
	int def;
	int wiz;
	int inte;
	int indexX, indexY;
	int myNum;
	float angle;
	bool isSelected;

};

typedef struct tagBuildingInfo
{
	CAMP camp;
	EVENT ev;
	MINE mine;
	image* img;
	image* imgShadow;
	struct tagCampInfo campInfo;
	int elements;
	int imgX, imgY;
	int sizeX, sizeY;
	int sourX, sourY;
	int destX, destY;
	int enterX, enterY;
	int miniX;
	bool isClosed;
	bool enter;

	bool operator<(const tagBuildingInfo &v) const {
		return (destY + enterY < v.destY + v.enterY);
	}

}building;


struct tagObjInfo
{
	MAPOBJECT obj;
	image* img;
	int sourX, sourY;
	int destX, destY;

};

struct tagRemember
{
	image* img;
	image* imgShadow;
	CAMP camp;
	MINE mine;
	EVENT ev;
	int elements;
	int destX;
	int destY;
	int sizeX;
	int sizeY;
	int sourX;
	int sourY;
	int imgX;
	int imgY;
	int miniX;
	int type;
};

typedef struct tagSaveFile
{
	int number;
	string fileName;

}SAVE;

struct tagSaveInfo
{
	int type;
	int sourX,  sourY;
	int destX,  destY;
	int miniX,  miniY;
	int imgX,  imgY;
	int sizeX,  sizeY;
	int enterX, enterY;
	bool closed;
	bool enter;
	struct tagCampInfo campInfo;

};




//========= �ֺ� Ÿ�� ����==========
#define LEFTTOP				0x00001
#define MIDDLETOP			0x00002
#define RIGHTTOP			0x00004
#define LEFTMIDDLE			0x00008
#define RIGHTMIDDLE			0x00010
#define LEFTBOTTOM			0x00020
#define MIDDLEBOTTOM		0x00040
#define RIGHTBOTTOM			0x00080
#define ALLDIRECTION		255

//========= �𼭸� ���ϱ� ===========
#define EDGE1		LEFTTOP			+ MIDDLETOP		+ LEFTMIDDLE		// �� ��
#define EDGE2		MIDDLETOP		+ RIGHTTOP		+ RIGHTMIDDLE		// �� ��
#define EDGE3		LEFTMIDDLE		+ LEFTBOTTOM	+ MIDDLEBOTTOM		// �� ��
#define EDGE4		MIDDLEBOTTOM	+ RIGHTBOTTOM	+ RIGHTMIDDLE		// �� ��

#define EDGE5		LEFTMIDDLE		+ MIDDLETOP			// �� ��	
#define EDGE6		MIDDLETOP		+ RIGHTMIDDLE		// �� ��
#define EDGE7		RIGHTMIDDLE		+ MIDDLEBOTTOM		// �� ��
#define EDGE8		MIDDLEBOTTOM	+ LEFTMIDDLE		// �� ��

//========= �� �� �� �� =============
#define LEFT		LEFTTOP			+ LEFTMIDDLE	+ LEFTBOTTOM	
#define RIGHT		RIGHTTOP		+ RIGHTMIDDLE	+ RIGHTBOTTOM
#define UP			LEFTTOP			+ MIDDLETOP		+ RIGHTTOP
#define DOWN		LEFTBOTTOM		+ MIDDLEBOTTOM	+ RIGHTBOTTOM

//========= �� �� �� ==============
#define ALL			LEFTMIDDLE		+ MIDDLETOP		+ RIGHTMIDDLE	+ MIDDLEBOTTOM

//========= ELEMENTS ===============
#define ELEMENTCASTLE			0x00040 //ũ���Ŀ� ��
#define ELEMENTDUNGEON			0x00080 //ũ���Ŀ� ��

#define TIERONE					010		//���� ����
#define TIERTWO					020

#define ELEMENTRESOURCE			0x00020 //�ڿ��� ��
#define ELEMENTMINE				0x00100 //���ο� ��
#define ELEMENTEVENT			0x00200 //�̺��� ��
#define ELEMENTARTIFACT			0x00400 //���ۿ� ��
#define ELEMENTCAMP				0x00800 //ķ���� ��
#define ELEMENTOBS				0x01000 //�ɽ��� ����