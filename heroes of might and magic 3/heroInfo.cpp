#include "stdafx.h"
#include "heroInfo.h"

namespace HOMM_HERO
{
	tagHero CommonHero(heroName name)
	{
		tagHero hero;
		ZeroMemory(&hero, sizeof(tagHero));
		hero.portraitLarge = IMAGEMANAGER->findImage("portrait_large");
		hero.portraitSmall = IMAGEMANAGER->findImage("portrait_small");
		//hero.flag = IMAGEMANAGER->findImage("hero_flag");
		hero.field = new image;
		hero.fieldShadow = new image;
		hero.flag = new image;
		hero.flag->init("image/gameScene/hero/hero_flag.bmp", 192, 512, 2, 8, true, RGB(255, 0, 255));

		
		
		
		hero.level = 1;

		switch (name)
		{
		case NAME_CHRISTIAN:
		{
			sprintf(hero.name, "ũ����Ƽ��");
			hero.kind = 0;
			hero.job = 0;
			hero.indexX = 1;
		}
		break;

		case NAME_TIRIS:
		{
			hero.indexX = 0;
			sprintf(hero.name, "Ƽ����");
			hero.kind = 0;
			hero.job = 0;
			hero.indexX = 0;

		}
		break;

		case NAME_ADELLA:
		{
			sprintf(hero.name, "�Ƶ���");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 2;

		}

		break;

		case NAME_ADELAIDE:
		{
			sprintf(hero.name, "�Ƶ����̵�");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 3;

		}

		break;
		case NAME_RYAN:
		{
			sprintf(hero.name, "���̾�");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 4;

		}

		break;

		case NAME_DAYS:
		{
			sprintf(hero.name, "���̽�");
			hero.kind = 1;
			hero.job = 0;
			hero.indexX = 1;

		}

		break;

		case NAME_DAMACON:
		{
			sprintf(hero.name, "�ٸ���");
			hero.kind = 1;
			hero.job = 0;
			hero.indexX = 0;

		}

		break;

		case NAME_DARKSTONE:
		{
			sprintf(hero.name, "��ũ����");
			hero.kind = 1;
			hero.job = 1;
			hero.indexX = 4;

		}

		break;

		case NAME_ZEDITE:
		{
			sprintf(hero.name, "������Ʈ");
			hero.kind = 1;
			hero.job = 1;
			hero.indexX = 2;

		}

		break;

		case NAME_SEPHINE:
		{
			sprintf(hero.name, "���ɷν�");
			hero.kind = 1;
			hero.job = 1;
			hero.indexX = 3;

		}

		break;

		case NAME_END:
		break;
		}

		switch (hero.kind)
		{
		case 0:

			hero.indexY = 0;
			hero.field->init("image/gameScene/hero/hero_castle.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
			hero.fieldShadow->init("image/gameScene/hero/hero_castle_shadow.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
			hero.fieldShadow->AlphaInit();

			//hero.field = IMAGEMANAGER->findImage("hero_castle");
			//hero.fieldShadow = IMAGEMANAGER->findImage("hero_castle_shadow");

			if (hero.job == 0)
			{
				sprintf(hero.jobName, "���");
				hero.str = 2;
				hero.def = 2;
				hero.wiz = 1;
				hero.inte = 1;


			}
			else
			{
				sprintf(hero.jobName, "Ŭ����");
				hero.str = 1;
				hero.def = 0;
				hero.wiz = 2;
				hero.inte = 2;
			}

		break;

		case 1:

			hero.indexY = 1;
			hero.field->init("image/gameScene/hero/hero_dungeon.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
			hero.fieldShadow->init("image/gameScene/hero/hero_dungeon_shadow.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
			hero.fieldShadow->AlphaInit();
			//hero.field = IMAGEMANAGER->findImage("hero_dungeon");
			//hero.fieldShadow = IMAGEMANAGER->findImage("hero_dungeon_shadow");

			if (hero.job == 0)
			{
				sprintf(hero.jobName, "�����ε�");
				hero.str = 2;
				hero.def = 2;
				hero.wiz = 1;
				hero.inte = 1;

			}
			else
			{
				sprintf(hero.jobName, "����");
				hero.str = 0;
				hero.def = 0;
				hero.wiz = 3;
				hero.inte = 2;

			}

		break;
		}






		return hero;
	}

	tagCreature CommonCreature(int num, int tier, int level)
	{
		tagCreature creature;

		ZeroMemory(&creature, sizeof(creature));

		creature.portrait = IMAGEMANAGER->findImage("creature_portrait");
		creature.kind = num;
		creature.level = level;
		creature.tier = tier;

		for (int i = 0; i < STATE_END; i++)
		{
			creature.img[i] = new image;
		}
		
		char tmp[256];


		switch (creature.kind)
		{
		case 0:
			switch (creature.tier)
			{
			case 0:
				sprintf(creature.name, "â��");
				
			break;
				
			case 1:

			break;

			case 2:

			break;

			case 3:

			break;

			case 4:

			break;

			case 5:

			break;

			case 6:

			break;
			}




		break;

		case 1:





		break;
		}



		return creature;
	}







}