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
			sprintf(hero.name, "크리스티안");
			hero.kind = 0;
			hero.job = 0;
			hero.indexX = 1;
		}
		break;

		case NAME_TIRIS:
		{
			hero.indexX = 0;
			sprintf(hero.name, "티리스");
			hero.kind = 0;
			hero.job = 0;
			hero.indexX = 0;

		}
		break;

		case NAME_ADELLA:
		{
			sprintf(hero.name, "아델라");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 2;

		}

		break;

		case NAME_ADELAIDE:
		{
			sprintf(hero.name, "아델레이드");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 3;

		}

		break;
		case NAME_RYAN:
		{
			sprintf(hero.name, "라이언");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 4;

		}

		break;

		case NAME_DAYS:
		{
			sprintf(hero.name, "데이스");
			hero.kind = 1;
			hero.job = 0;
			hero.indexX = 1;

		}

		break;

		case NAME_DAMACON:
		{
			sprintf(hero.name, "다마콘");
			hero.kind = 1;
			hero.job = 0;
			hero.indexX = 0;

		}

		break;

		case NAME_DARKSTONE:
		{
			sprintf(hero.name, "다크스톤");
			hero.kind = 1;
			hero.job = 1;
			hero.indexX = 4;

		}

		break;

		case NAME_ZEDITE:
		{
			sprintf(hero.name, "제다이트");
			hero.kind = 1;
			hero.job = 1;
			hero.indexX = 2;

		}

		break;

		case NAME_SEPHINE:
		{
			sprintf(hero.name, "세핀로스");
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
				sprintf(hero.jobName, "기사");
				hero.str = 2;
				hero.def = 2;
				hero.wiz = 1;
				hero.inte = 1;


			}
			else
			{
				sprintf(hero.jobName, "클레릭");
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
				sprintf(hero.jobName, "오버로드");
				hero.str = 2;
				hero.def = 2;
				hero.wiz = 1;
				hero.inte = 1;

			}
			else
			{
				sprintf(hero.jobName, "워락");
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
		creature.morale = 0;
		creature.luck = 0;

		for (int i = 0; i < STATE_END; i++)
		{
			creature.img[i] = new image;
			creature.imgShadow[i] = new image;
		}
		


		switch (creature.kind)
		{
		case 0:

			switch (creature.tier)
			{
			case 0:
				sprintf(creature.name, "창병");
				creature.atk = 4;
				creature.def = 5;
				creature.hp = 10;
				creature.minDmg = 1;
				creature.maxDmg = 3;
				creature.speed = 4;

				creature.img[0]->init("image/Castle Creature/11_pikeman/pikeman_attack_down", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[1]->init("image/Castle Creature/11_pikeman/pikeman_attack_front", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[2]->init("image/Castle Creature/11_pikeman/pikeman_attack_up", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[8]->init("image/Castle Creature/11_pikeman/pikeman_damaged", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[9]->init("image/Castle Creature/11_pikeman/pikeman_dead", 700, 280, 5, 2, true, RGB(255, 0, 255));
				creature.img[7]->init("image/Castle Creature/11_pikeman/pikeman_idle", 140, 280, 1, 2, true, RGB(255, 0, 255));
				creature.img[3]->init("image/Castle Creature/11_pikeman/pikeman_move", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[4]->init("image/Castle Creature/11_pikeman/pikeman_select", 560, 280, 4, 2, true, RGB(255, 0, 255));
				creature.img[5]->init("image/Castle Creature/11_pikeman/pikeman_switch", 280, 280, 2, 2, true, RGB(255, 0, 255));
				creature.imgShadow[0]->init("image/Castle Creature/11_pikeman/pikeman_attack_down_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[1]->init("image/Castle Creature/11_pikeman/pikeman_attack_front_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[2]->init("image/Castle Creature/11_pikeman/pikeman_attack_up_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[8]->init("image/Castle Creature/11_pikeman/pikeman_attack_damaged_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[9]->init("image/Castle Creature/11_pikeman/pikeman_attack_dead_shadow", 700, 280, 5, 2, true, RGB(255, 0, 255));
				creature.imgShadow[7]->init("image/Castle Creature/11_pikeman/pikeman_attack_idle_shadow", 140, 280, 1, 2, true, RGB(255, 0, 255));
				creature.imgShadow[3]->init("image/Castle Creature/11_pikeman/pikeman_attack_move_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[4]->init("image/Castle Creature/11_pikeman/pikeman_attack_select_shadow", 560, 280, 4, 2, true, RGB(255, 0, 255));
				creature.imgShadow[5]->init("image/Castle Creature/11_pikeman/pikeman_attack_switch_shadow", 280, 280, 2, 2, true, RGB(255, 0, 255));
				for (int i = 0; i < STATE_END; i++)
				{
					if (i == (int)STATE_RANGE) continue;
					creature.imgShadow[i]->AlphaInit();
				}



				if (creature.level)
				{
					sprintf(creature.name, "도끼 창병");
					creature.atk = 6;
					creature.def = 5;
					creature.hp = 10;
					creature.minDmg = 2;
					creature.maxDmg = 3;
					creature.speed = 5;

					creature.img[0]->init("image/Castle Creature/12_halberdier/halberdier_attack_down", 980, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/12_halberdier/halberdier_attack_front", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/12_halberdier/halberdier_attack_up", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/12_halberdier/halberdier_damaged", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/12_halberdier/halberdier_dead", 420, 280, 3, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/12_halberdier/halberdier_idle", 140, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/12_halberdier/halberdier_move", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/12_halberdier/halberdier_select", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/12_halberdier/halberdier_switch", 280, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/12_halberdier/halberdier_attack_down_shadow", 980, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/12_halberdier/halberdier_attack_front_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/12_halberdier/halberdier_attack_up_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/12_halberdier/halberdier_attack_damaged_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/12_halberdier/halberdier_attack_dead_shadow", 420, 280, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/12_halberdier/halberdier_attack_idle_shadow", 140, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/12_halberdier/halberdier_attack_move_shadow", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/12_halberdier/halberdier_attack_select_shadow", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/12_halberdier/halberdier_attack_switch_shadow", 280, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}


				}
				
			break;
				
			case 1:
				sprintf(creature.name, "궁수");
				creature.atk = 6;
				creature.def =3;
				creature.hp = 10;
				creature.minDmg = 2;
				creature.maxDmg = 3;
				creature.speed = 4;
				creature.img[0]->init("image/Castle Creature/21_archer/archer_attack_melee", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.img[1]->init("image/Castle Creature/21_archer/archer_attack_melee", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.img[2]->init("image/Castle Creature/21_archer/archer_attack_melee", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.img[6]->init("image/Castle Creature/21_archer/archer_attack_range", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.img[8]->init("image/Castle Creature/21_archer/archer_damaged", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.img[9]->init("image/Castle Creature/21_archer/archer_dead", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.img[7]->init("image/Castle Creature/21_archer/archer_idle", 120, 240, 1, 2, true, RGB(255, 0, 255));
				creature.img[3]->init("image/Castle Creature/21_archer/archer_move", 1440, 240, 12, 2, true, RGB(255, 0, 255));
				creature.img[4]->init("image/Castle Creature/21_archer/archer_select", 960, 240, 8, 2, true, RGB(255, 0, 255));
				creature.img[5]->init("image/Castle Creature/21_archer/archer_switch", 240, 240, 2, 2, true, RGB(255, 0, 255));
				creature.imgShadow[0]->init("image/Castle Creature/21_archer/archer_attack_melee_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[1]->init("image/Castle Creature/21_archer/archer_attack_melee_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[2]->init("image/Castle Creature/21_archer/archer_attack_melee_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[6]->init("image/Castle Creature/21_archer/archer_attack_range_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[8]->init("image/Castle Creature/21_archer/archer_attack_damaged_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[9]->init("image/Castle Creature/21_archer/archer_attack_dead_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[7]->init("image/Castle Creature/21_archer/archer_attack_idle_shadow", 120, 240, 1, 2, true, RGB(255, 0, 255));
				creature.imgShadow[3]->init("image/Castle Creature/21_archer/archer_attack_move_shadow", 1440, 240, 12, 2, true, RGB(255, 0, 255));
				creature.imgShadow[4]->init("image/Castle Creature/21_archer/archer_attack_select_shadow", 960, 240, 8, 2, true, RGB(255, 0, 255));
				creature.imgShadow[5]->init("image/Castle Creature/21_archer/archer_attack_switch_shadow", 240, 240, 2, 2, true, RGB(255, 0, 255));
				for (int i = 0; i < STATE_END; i++)
				{
					creature.imgShadow[i]->AlphaInit();
				}



				if (creature.level)
				{
					sprintf(creature.name, "저격수");
					creature.atk = 6;
					creature.def = 3;
					creature.hp = 10;
					creature.minDmg = 2;
					creature.maxDmg = 3;
					creature.speed = 6;

					creature.img[0]->init("image/Castle Creature/22_mask/mask_attack_melee", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/22_mask/mask_attack_melee", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/22_mask/mask_attack_melee", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Castle Creature/22_mask/mask_attack_range", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/22_mask/mask_damaged", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/22_mask/mask_dead", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/22_mask/mask_idle", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/22_mask/mask_move", 1440, 240, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/22_mask/mask_select", 960, 240, 8, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/22_mask/mask_switch", 240, 240, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/22_mask/mask_attack_melee_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/22_mask/mask_attack_melee_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/22_mask/mask_attack_melee_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Castle Creature/22_mask/mask_attack_range_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/22_mask/mask_attack_damaged_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/22_mask/mask_attack_dead_shadow", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/22_mask/mask_attack_idle_shadow", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/22_mask/mask_attack_move_shadow", 1440, 240, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/22_mask/mask_attack_select_shadow", 960, 240, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/22_mask/mask_attack_switch_shadow", 240, 240, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}

				}

			break;

			case 2:
				sprintf(creature.name, "그리핀");
				creature.atk = 8;
				creature.def = 8;
				creature.hp = 25;
				creature.minDmg = 3;
				creature.maxDmg = 6;
				creature.speed = 6;

				creature.img[0]->init("image/Castle Creature/31_griffin/griffin_attack_down", 1600, 280, 8, 2, true, RGB(255, 0, 255));
				creature.img[1]->init("image/Castle Creature/31_griffin/griffin_attack_front", 1400, 280, 7, 2, true, RGB(255, 0, 255));
				creature.img[2]->init("image/Castle Creature/31_griffin/griffin_attack_up", 1200, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[8]->init("image/Castle Creature/31_griffin/griffin_damaged", 1000, 280, 5, 2, true, RGB(255, 0, 255));
				creature.img[9]->init("image/Castle Creature/31_griffin/griffin_dead", 1600, 280, 8, 2, true, RGB(255, 0, 255));
				creature.img[7]->init("image/Castle Creature/31_griffin/griffin_idle", 200, 280, 1, 2, true, RGB(255, 0, 255));
				creature.img[3]->init("image/Castle Creature/31_griffin/griffin_move", 1600, 280, 8, 2, true, RGB(255, 0, 255));
				creature.img[4]->init("image/Castle Creature/31_griffin/griffin_select", 600, 280, 3, 2, true, RGB(255, 0, 255));
				creature.img[5]->init("image/Castle Creature/31_griffin/griffin_switch", 400, 280, 2, 2, true, RGB(255, 0, 255));
				creature.imgShadow[0]->init("image/Castle Creature/31_griffin/griffin_attack_down_shadow", 1600,280, 8, 2, true, RGB(255, 0, 255));
				creature.imgShadow[1]->init("image/Castle Creature/31_griffin/griffin_attack_front_shadow", 1400, 280, 7, 2, true, RGB(255, 0, 255));
				creature.imgShadow[2]->init("image/Castle Creature/31_griffin/griffin_attack_up_shadow", 1200, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[8]->init("image/Castle Creature/31_griffin/griffin_attack_damaged_shadow", 1000, 280, 5, 2, true, RGB(255, 0, 255));
				creature.imgShadow[9]->init("image/Castle Creature/31_griffin/griffin_attack_dead_shadow", 1600, 280, 8, 2, true, RGB(255, 0, 255));
				creature.imgShadow[7]->init("image/Castle Creature/31_griffin/griffin_attack_idle_shadow", 200, 280, 1, 2, true, RGB(255, 0, 255));
				creature.imgShadow[3]->init("image/Castle Creature/31_griffin/griffin_attack_move_shadow", 1600, 280, 8, 2, true, RGB(255, 0, 255));
				creature.imgShadow[4]->init("image/Castle Creature/31_griffin/griffin_attack_select_shadow", 600, 280, 3, 2, true, RGB(255, 0, 255));
				creature.imgShadow[5]->init("image/Castle Creature/31_griffin/griffin_attack_switch_shadow", 400, 280, 2, 2, true, RGB(255, 0, 255));
				for (int i = 0; i < STATE_END; i++)
				{
					if (i == (int)STATE_RANGE) continue;
					creature.imgShadow[i]->AlphaInit();
				}


				if (creature.level)
				{
					sprintf(creature.name, "로열 그리핀");
					creature.atk = 9;
					creature.def = 9;
					creature.hp = 25;
					creature.minDmg = 3;
					creature.maxDmg = 6;
					creature.speed = 9;

					creature.img[0]->init("image/Castle Creature/32_royal/royal_attack_down", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/32_royal/royal_attack_front", 1540, 320, 7, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/32_royal/royal_attack_up", 1320, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/32_royal/royal_damaged", 1100, 320, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/32_royal/royal_dead", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/32_royal/royal_idle", 220, 320, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/32_royal/royal_move", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/32_royal/royal_select", 1100, 320, 5, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/32_royal/royal_switch", 440, 320, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/32_royal/royal_attack_down_shadow", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/32_royal/royal_attack_front_shadow", 1540, 320, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/32_royal/royal_attack_up_shadow", 1320, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/32_royal/royal_attack_damaged_shadow", 1100, 320, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/32_royal/royal_attack_dead_shadow", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/32_royal/royal_attack_idle_shadow", 220, 320, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/32_royal/royal_attack_move_shadow", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/32_royal/royal_attack_select_shadow", 1100, 320, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/32_royal/royal_attack_switch_shadow", 440, 320, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}


			break;

			case 3:
				sprintf(creature.name, "검사");
				creature.atk = 10;
				creature.def = 12;
				creature.hp = 35;
				creature.minDmg = 6;
				creature.maxDmg = 9;
				creature.speed = 5;

				creature.img[0]->init("image/Castle Creature/41_sword/sword_attack_down", 960, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[1]->init("image/Castle Creature/41_sword/sword_attack_front", 1120, 280, 7, 2, true, RGB(255, 0, 255));
				creature.img[2]->init("image/Castle Creature/41_sword/sword_attack_up", 960, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[8]->init("image/Castle Creature/41_sword/sword_damaged", 960, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[9]->init("image/Castle Creature/41_sword/sword_dead", 960, 280, 6, 2, true, RGB(255, 0, 255));
				creature.img[7]->init("image/Castle Creature/41_sword/sword_idle", 160, 280, 1, 2, true, RGB(255, 0, 255));
				creature.img[3]->init("image/Castle Creature/41_sword/sword_move", 1920, 280, 12, 2, true, RGB(255, 0, 255));
				creature.img[4]->init("image/Castle Creature/41_sword/sword_select", 640, 280, 4, 2, true, RGB(255, 0, 255));
				creature.img[5]->init("image/Castle Creature/41_sword/sword_switch", 320, 280, 2, 2, true, RGB(255, 0, 255));
				creature.imgShadow[0]->init("image/Castle Creature/41_sword/sword_attack_down_shadow", 960, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[1]->init("image/Castle Creature/41_sword/sword_attack_front_shadow", 1120, 280, 7, 2, true, RGB(255, 0, 255));
				creature.imgShadow[2]->init("image/Castle Creature/41_sword/sword_attack_up_shadow", 960, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[8]->init("image/Castle Creature/41_sword/sword_attack_damaged_shadow", 960, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[9]->init("image/Castle Creature/41_sword/sword_attack_dead_shadow", 960, 280, 6, 2, true, RGB(255, 0, 255));
				creature.imgShadow[7]->init("image/Castle Creature/41_sword/sword_attack_idle_shadow", 160, 280, 1, 2, true, RGB(255, 0, 255));
				creature.imgShadow[3]->init("image/Castle Creature/41_sword/sword_attack_move_shadow", 1920, 280, 12, 2, true, RGB(255, 0, 255));
				creature.imgShadow[4]->init("image/Castle Creature/41_sword/sword_attack_select_shadow", 640, 280, 4, 2, true, RGB(255, 0, 255));
				creature.imgShadow[5]->init("image/Castle Creature/41_sword/sword_attack_switch_shadow", 320, 280, 2, 2, true, RGB(255, 0, 255));
				for (int i = 0; i < STATE_END; i++)
				{
					if (i == (int)STATE_RANGE) continue;
					creature.imgShadow[i]->AlphaInit();
				}



				if (creature.level)
				{
					sprintf(creature.name, "크루세이더");
					creature.atk = 12;
					creature.def = 12;
					creature.hp = 35;
					creature.minDmg = 7;
					creature.maxDmg = 10;
					creature.speed = 6;
				}


			break;

			case 4:
				sprintf(creature.name, "수도사");
				creature.atk = 12;
				creature.def = 7;
				creature.hp = 30;
				creature.minDmg = 10;
				creature.maxDmg = 12;
				creature.speed = 5;

				if (creature.level)
				{
					sprintf(creature.name, "열성 수도사");
					creature.atk = 12;
					creature.def = 10;
					creature.hp = 30;
					creature.minDmg = 10;
					creature.maxDmg = 12;
					creature.speed = 7;
				}


			break;

			case 5:
				sprintf(creature.name, "기사단");
				creature.atk = 15;
				creature.def = 15;
				creature.hp = 100;
				creature.minDmg = 15;
				creature.maxDmg = 25;
				creature.speed = 7;

				if (creature.level)
				{
					sprintf(creature.name, "챔피언");
					creature.atk = 16;
					creature.def = 16;
					creature.hp = 100;
					creature.minDmg = 20;
					creature.maxDmg = 25;
					creature.speed = 9;
				}


			break;

			case 6:
				sprintf(creature.name, "천사");
				creature.atk = 20;
				creature.def = 20;
				creature.hp = 200;
				creature.minDmg = 50;
				creature.maxDmg = 50;
				creature.speed = 12;

				if (creature.level)
				{
					sprintf(creature.name, "대천사");
					creature.atk = 30;
					creature.def = 30;
					creature.hp = 250;
					creature.minDmg = 50;
					creature.maxDmg = 50;
					creature.speed = 18;
				}


			break;
			}




		break;

		case 1:

			switch (creature.tier)
			{
			case 0:
				sprintf(creature.name, "동굴인");
				creature.atk = 4;
				creature.def = 3;
				creature.hp = 5;
				creature.minDmg = 1;
				creature.maxDmg = 3;
				creature.speed = 4;

				if (creature.level)
				{
					sprintf(creature.name, "지옥의 동굴인");
					creature.atk = 5;
					creature.def = 4;
					creature.hp = 6;
					creature.minDmg = 1;
					creature.maxDmg = 3;
					creature.speed = 5;
				}

				break;

			case 1:
				sprintf(creature.name, "하피");
				creature.atk = 6;
				creature.def = 5;
				creature.hp = 14;
				creature.minDmg = 1;
				creature.maxDmg = 4;
				creature.speed = 6;

				if (creature.level)
				{
					sprintf(creature.name, "마녀 하피");
					creature.atk = 6;
					creature.def = 6;
					creature.hp = 14;
					creature.minDmg = 1;
					creature.maxDmg = 5;
					creature.speed = 9;
				}

				break;

			case 2:
				sprintf(creature.name, "주시자");
				creature.atk = 9;
				creature.def = 7;
				creature.hp = 22;
				creature.minDmg = 3;
				creature.maxDmg = 5;
				creature.speed = 5;

				if (creature.level)
				{
					sprintf(creature.name, "악마의 눈");
					creature.atk = 10;
					creature.def = 8;
					creature.hp = 22;
					creature.minDmg = 3;
					creature.maxDmg = 5;
					creature.speed = 7;
				}


				break;

			case 3:
				sprintf(creature.name, "메두사");
				creature.atk = 9;
				creature.def = 9;
				creature.hp = 25;
				creature.minDmg = 6;
				creature.maxDmg = 8;
				creature.speed = 5;

				if (creature.level)
				{
					sprintf(creature.name, "메두사 퀸");
					creature.atk = 10;
					creature.def = 10;
					creature.hp = 30;
					creature.minDmg = 6;
					creature.maxDmg = 8;
					creature.speed = 6;
				}


				break;

			case 4:
				sprintf(creature.name, "미노타우르스");
				creature.atk = 14;
				creature.def = 12;
				creature.hp = 50;
				creature.minDmg = 12;
				creature.maxDmg = 20;
				creature.speed = 6;

				if (creature.level)
				{
					sprintf(creature.name, "미노타우르스 킹");
					creature.atk = 15;
					creature.def = 15;
					creature.hp = 50;
					creature.minDmg = 12;
					creature.maxDmg = 20;
					creature.speed = 8;
				}


				break;

			case 5:
				sprintf(creature.name, "만티코어");
				creature.atk = 15;
				creature.def = 13;
				creature.hp = 80;
				creature.minDmg = 14;
				creature.maxDmg = 20;
				creature.speed = 7;

				if (creature.level)
				{
					sprintf(creature.name, "스코피코어");
					creature.atk = 16;
					creature.def = 14;
					creature.hp = 80;
					creature.minDmg = 14;
					creature.maxDmg = 20;
					creature.speed = 11;
				}


				break;

			case 6:
				sprintf(creature.name, "레드 드래곤");
				creature.atk = 19;
				creature.def = 19;
				creature.hp = 180;
				creature.minDmg = 40;
				creature.maxDmg = 50;
				creature.speed = 11;

				if (creature.level)
				{
					sprintf(creature.name, "블랙 드래곤");
					creature.atk = 25;
					creature.def = 25;
					creature.hp = 300;
					creature.minDmg = 40;
					creature.maxDmg = 50;
					creature.speed = 15;
				}


				break;
			}

		break;
		}





		return creature;
	}







}