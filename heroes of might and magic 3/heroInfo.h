#pragma once

struct tagSkill
{
	
};

enum skillName
{

};

struct tagHero
{
	image* portraitLarge;		// ū �ʻ�ȭ �̹���
	image* portraitSmall;		// ���� �ʻ�ȭ �̹���
	image* battle;				// ��Ʋ������ �̹���
	image* field;				// �ʵ��� �̹���
	image* fieldShadow;			// �ʵ��� �׸���
	image* flag;				// �ʵ��� ��� 

	char name[256];				// ���� �̸�
	char jobName[256];			// ���� ������
	int level;					// ����
	int str;					// ��
	int def;					// ����
	int wiz;					// ���� (������)
	int inte;					// ���� (�ֹ� ���ݷ�)
	int myNum;					// ������ȣ �ǹ� ����?
	int kind;					// ������
	int job;					// ������
	int indexX, indexY;			// �ʻ�ȭ �ε���
	float angle;				// �ʵ� �� ���� ����
	vector<tagSkill> skill;		// ������ �ִ� ��ų


};

struct tagCreature
{
	image* portrait;
	image* img[STATE_END];
	image* imgShadow[STATE_END];

	int kind;				// ������
	int tier;				// �� Ƽ��?
	int level;				// ������ �ߴ�?

	int position;			// ��ġ 0~6

	char name[256];			// �̸�

	int atk;				// ���ݷ�
	int def;				// ����

	int hp;					// ü��
	int maxDmg;				// �Ƶ�
	int minDmg;				// �ε�
	int speed;				// �ӵ�

	int morale;				// ���
	int luck;				// ���

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
	// ���� ������ ���� �������� ���ؼ�
	tagHero CommonHero(heroName name);

	tagCreature CommonCreature(int kind, int tier, int level);



}