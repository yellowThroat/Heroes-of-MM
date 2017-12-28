#pragma once

struct tagSkill
{
	
};

enum skillName
{

};

struct tagHero
{
	image* portraitLarge;		// 큰 초상화 이미지
	image* portraitSmall;		// 작은 초상화 이미지
	image* battle;				// 배틀씬에서 이미지
	image* field;				// 필드위 이미지
	image* fieldShadow;			// 필드위 그림자
	image* flag;				// 필드위 깃발 

	char name[256];				// 영웅 이름
	char jobName[256];			// 영웅 직업명
	int level;					// 레벨
	int str;					// 힘
	int def;					// 방어력
	int wiz;					// 지혜 (마나량)
	int inte;					// 지식 (주문 공격력)
	int myNum;					// 영웅번호 의미 없나?
	int kind;					// 종족값
	int job;					// 직업값
	int indexX, indexY;			// 초상화 인덱스
	float angle;				// 필드 위 방향 각도
	vector<tagSkill> skill;		// 가지고 있는 스킬


};

struct tagCreature
{
	image* portrait;
	image* img[STATE_END];
	image* imgShadow[STATE_END];

	int kind;				// 종족값
	int tier;				// 몇 티어?
	int level;				// 레벨업 했니?

	int position;			// 위치 0~6

	char name[256];			// 이름

	int atk;				// 공격력
	int def;				// 방어력

	int hp;					// 체력
	int maxDmg;				// 맥뎀
	int minDmg;				// 민뎀
	int speed;				// 속도

	int morale;				// 사기
	int luck;				// 행운

	CREATURESTATE state;
};

enum heroName
{
	NAME_CHRISTIAN,
	NAME_TIRIS,
	NAME_ADELLA,
	NAME_ADELAIDE,
	NAME_RYAN,
	NAME_DAYS,
	NAME_DAMACON,
	NAME_DARKSTONE,
	NAME_ZEDITE,
	NAME_SEPHINE,
	NAME_END
};


namespace HOMM_HERO
{
	// 영웅 정보를 쉽게 가져오기 위해서
	tagHero CommonHero(heroName name);

	tagCreature CommonCreature(int kind, int tier, int level);



}