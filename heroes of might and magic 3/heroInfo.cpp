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
			sprintf_s(hero.name, "크리스티안");
			hero.kind = 0;
			hero.job = 0;
			hero.indexX = 1;
		}
		break;

		case NAME_TIRIS:
		{
			hero.indexX = 0;
			sprintf_s(hero.name, "티리스");
			hero.kind = 0;
			hero.job = 0;
			hero.indexX = 0;

		}
		break;

		case NAME_ADELLA:
		{
			sprintf_s(hero.name, "아델라");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 2;

		}

		break;

		case NAME_ADELAIDE:
		{
			sprintf_s(hero.name, "아델레이드");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 3;

		}

		break;
		case NAME_RYAN:
		{
			sprintf_s(hero.name, "라이언");
			hero.kind = 0;
			hero.job = 1;
			hero.indexX = 4;

		}

		break;

		case NAME_DAYS:
		{
			sprintf_s(hero.name, "데이스");
			hero.kind = 1;
			hero.job = 0;
			hero.indexX = 1;

		}

		break;

		case NAME_DAMACON:
		{
			sprintf_s(hero.name, "다마콘");
			hero.kind = 1;
			hero.job = 0;
			hero.indexX = 0;

		}

		break;

		case NAME_DARKSTONE:
		{
			sprintf_s(hero.name, "다크스톤");
			hero.kind = 1;
			hero.job = 1;
			hero.indexX = 4;

		}

		break;

		case NAME_ZEDITE:
		{
			sprintf_s(hero.name, "제다이트");
			hero.kind = 1;
			hero.job = 1;
			hero.indexX = 2;

		}

		break;

		case NAME_SEPHINE:
		{
			sprintf_s(hero.name, "세핀로스");
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
			//hero.fieldShadow = IMAGEMANAGER->findImage("hero_castle_shadow.bmp");

			if (hero.job == 0)
			{
				sprintf_s(hero.jobName, "기사");
				hero.str = 2;
				hero.def = 2;
				hero.spell = 1;
				hero.intel = 1;


			}
			else
			{
				sprintf_s(hero.jobName, "클레릭");
				hero.str = 1;
				hero.def = 0;
				hero.spell = 2;
				hero.intel = 2;
			}

		break;

		case 1:

			hero.indexY = 1;
			hero.field->init("image/gameScene/hero/hero_dungeon.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
			hero.fieldShadow->init("image/gameScene/hero/hero_dungeon_shadow.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
			hero.fieldShadow->AlphaInit();
			//hero.field = IMAGEMANAGER->findImage("hero_dungeon");
			//hero.fieldShadow = IMAGEMANAGER->findImage("hero_dungeon_shadow.bmp");

			if (hero.job == 0)
			{
				sprintf_s(hero.jobName, "오버로드");
				hero.str = 2;
				hero.def = 2;
				hero.spell = 1;
				hero.intel = 1;

			}
			else
			{
				sprintf_s(hero.jobName, "워락");
				hero.str = 0;
				hero.def = 0;
				hero.spell = 3;
				hero.intel = 2;

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
		creature.state = STATE_IDLE;
		creature.quantity = 1;
		creature.arrNum = 0;
		creature.target = 0;
		creature.isDead = false;
		creature.moveEnd = 0;
		creature.moveStart = 0;
		creature.fly = false;


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
				if (!creature.level)
				{
					sprintf_s(creature.name, "창병");
					creature.atk = 4;
					creature.def = 5;
					creature.hp = 10;
					creature.minDmg = 1;
					creature.maxDmg = 3;
					creature.speed = 4;
					creature.startX = 58;
					creature.startY = 119;
					creature.size = 1;

					creature.img[0]->init("image/Castle Creature/11_pikeman/pikeman_attack_down.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/11_pikeman/pikeman_attack_front.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/11_pikeman/pikeman_attack_up.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/11_pikeman/pikeman_damaged.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/11_pikeman/pikeman_dead.bmp", 700, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/11_pikeman/pikeman_idle.bmp", 140, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/11_pikeman/pikeman_move.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/11_pikeman/pikeman_select.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/11_pikeman/pikeman_switch.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/11_pikeman/pikeman_attack_down_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/11_pikeman/pikeman_attack_front_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/11_pikeman/pikeman_attack_up_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/11_pikeman/pikeman_damaged_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/11_pikeman/pikeman_dead_shadow.bmp", 700, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/11_pikeman/pikeman_idle_shadow.bmp", 140, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/11_pikeman/pikeman_move_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/11_pikeman/pikeman_select_shadow.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/11_pikeman/pikeman_switch_shadow.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "도끼 창병");
					creature.atk = 6;
					creature.def = 5;
					creature.hp = 10;
					creature.minDmg = 2;
					creature.maxDmg = 3;
					creature.speed = 5;
					creature.startX = 57;
					creature.startY = 119;
					creature.size = 1;

					creature.img[0]->init("image/Castle Creature/12_halberdier/halberdier_attack_down.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/12_halberdier/halberdier_attack_front.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/12_halberdier/halberdier_attack_up.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/12_halberdier/halberdier_damaged.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/12_halberdier/halberdier_dead.bmp", 420, 280, 3, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/12_halberdier/halberdier_idle.bmp", 140, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/12_halberdier/halberdier_move.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/12_halberdier/halberdier_select.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/12_halberdier/halberdier_switch.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/12_halberdier/halberdier_attack_down_shadow.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/12_halberdier/halberdier_attack_front_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/12_halberdier/halberdier_attack_up_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/12_halberdier/halberdier_damaged_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/12_halberdier/halberdier_dead_shadow.bmp", 420, 280, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/12_halberdier/halberdier_idle_shadow.bmp", 140, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/12_halberdier/halberdier_move_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/12_halberdier/halberdier_select_shadow.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/12_halberdier/halberdier_switch_shadow.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}


				}
				
			break;
				
			case 1:
				if (!creature.level)
				{				
					sprintf_s(creature.name, "궁수");
					creature.atk = 6;
					creature.def =3;
					creature.hp = 10;
					creature.minDmg = 2;
					creature.maxDmg = 3;
					creature.speed = 4;
					creature.startX = 57;
					creature.startY = 100;
					creature.size = 1;

					creature.img[0]->init("image/Castle Creature/21_archer/archer_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/21_archer/archer_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/21_archer/archer_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Castle Creature/21_archer/archer_attack_range.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/21_archer/archer_damaged.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/21_archer/archer_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/21_archer/archer_idle.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/21_archer/archer_move.bmp", 1440, 240, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/21_archer/archer_select.bmp", 960, 240, 8, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/21_archer/archer_switch.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/21_archer/archer_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/21_archer/archer_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/21_archer/archer_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Castle Creature/21_archer/archer_attack_range_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/21_archer/archer_damaged_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/21_archer/archer_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/21_archer/archer_idle_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/21_archer/archer_move_shadow.bmp", 1440, 240, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/21_archer/archer_select_shadow.bmp", 960, 240, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/21_archer/archer_switch_shadow.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}


				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "저격수");
					creature.atk = 6;
					creature.def = 3;
					creature.hp = 10;
					creature.minDmg = 2;
					creature.maxDmg = 3;
					creature.speed = 6;
					creature.startX = 57;
					creature.startY = 100;
					creature.size = 1;

					creature.img[0]->init("image/Castle Creature/22_mask/mask_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/22_mask/mask_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/22_mask/mask_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Castle Creature/22_mask/mask_attack_range.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/22_mask/mask_damaged.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/22_mask/mask_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/22_mask/mask_idle.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/22_mask/mask_move.bmp", 1440, 240, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/22_mask/mask_select.bmp", 960, 240, 8, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/22_mask/mask_switch.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/22_mask/mask_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/22_mask/mask_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/22_mask/mask_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Castle Creature/22_mask/mask_attack_range_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/22_mask/mask_damaged_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/22_mask/mask_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/22_mask/mask_idle_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/22_mask/mask_move_shadow.bmp", 1440, 240, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/22_mask/mask_select_shadow.bmp", 960, 240, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/22_mask/mask_switch_shadow.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}

				}

			break;

			case 2:
				if (!creature.level)
				{

					sprintf_s(creature.name, "그리핀");
					creature.atk = 8;
					creature.def = 8;
					creature.hp = 25;
					creature.minDmg = 3;
					creature.maxDmg = 6;
					creature.speed = 6;
					creature.startX = 100;
					creature.startY = 120;
					creature.size = 2;
					creature.fly = true;
					creature.moveStart = 2;
					creature.moveEnd = 2;

					creature.img[0]->init("image/Castle Creature/31_griffin/griffin_attack_down.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/31_griffin/griffin_attack_front.bmp", 1400, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/31_griffin/griffin_attack_up.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/31_griffin/griffin_damaged.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/31_griffin/griffin_dead.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/31_griffin/griffin_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/31_griffin/griffin_move.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/31_griffin/griffin_select.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/31_griffin/griffin_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/31_griffin/griffin_attack_down_shadow.bmp", 1600,280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/31_griffin/griffin_attack_front_shadow.bmp", 1400, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/31_griffin/griffin_attack_up_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/31_griffin/griffin_damaged_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/31_griffin/griffin_dead_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/31_griffin/griffin_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/31_griffin/griffin_move_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/31_griffin/griffin_select_shadow.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/31_griffin/griffin_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}


				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "로열 그리핀");
					creature.atk = 9;
					creature.def = 9;
					creature.hp = 25;
					creature.minDmg = 3;
					creature.maxDmg = 6;
					creature.speed = 9;
					creature.startX = 126;
					creature.startY = 126;
					creature.size = 2;
					creature.fly = true;
					creature.moveStart = 2;
					creature.moveEnd = 2;

					creature.img[0]->init("image/Castle Creature/32_royal/royal_attack_down.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/32_royal/royal_attack_front.bmp", 1540, 320, 7, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/32_royal/royal_attack_up.bmp", 1320, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/32_royal/royal_damaged.bmp", 1100, 320, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/32_royal/royal_dead.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/32_royal/royal_idle.bmp", 220, 320, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/32_royal/royal_move.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/32_royal/royal_select.bmp", 1100, 320, 5, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/32_royal/royal_switch.bmp", 440, 320, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/32_royal/royal_attack_down_shadow.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/32_royal/royal_attack_front_shadow.bmp", 1540, 320, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/32_royal/royal_attack_up_shadow.bmp", 1320, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/32_royal/royal_damaged_shadow.bmp", 1100, 320, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/32_royal/royal_dead_shadow.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/32_royal/royal_idle_shadow.bmp", 220, 320, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/32_royal/royal_move_shadow.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/32_royal/royal_select_shadow.bmp", 1100, 320, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/32_royal/royal_switch_shadow.bmp", 440, 320, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}


			break;

			case 3:
				if (!creature.level)
				{
					sprintf_s(creature.name, "검사");
					creature.atk = 10;
					creature.def = 12;
					creature.hp = 35;
					creature.minDmg = 6;
					creature.maxDmg = 9;
					creature.speed = 5;
					creature.startX = 80;
					creature.startY = 120;
					creature.size = 1;

					creature.img[0]->init("image/Castle Creature/41_sword/sword_attack_down.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/41_sword/sword_attack_front.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/41_sword/sword_attack_up.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/41_sword/sword_damaged.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/41_sword/sword_dead.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/41_sword/sword_idle.bmp", 160, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/41_sword/sword_move.bmp", 1920, 280, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/41_sword/sword_select.bmp", 640, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/41_sword/sword_switch.bmp", 320, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/41_sword/sword_attack_down_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/41_sword/sword_attack_front_shadow.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/41_sword/sword_attack_up_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/41_sword/sword_damaged_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/41_sword/sword_dead_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/41_sword/sword_idle_shadow.bmp", 160, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/41_sword/sword_move_shadow.bmp", 1920, 280, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/41_sword/sword_select_shadow.bmp", 640, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/41_sword/sword_switch_shadow.bmp", 320, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "크루세이더");
					creature.atk = 12;
					creature.def = 12;
					creature.hp = 35;
					creature.minDmg = 7;
					creature.maxDmg = 10;
					creature.speed = 6;
					creature.startX = 80;
					creature.startY = 120;
					creature.size = 1;
					creature.img[0]->init("image/Castle Creature/42_cru/cru_attack_down.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/42_cru/cru_attack_front.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/42_cru/cru_attack_up.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/42_cru/cru_damaged.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/42_cru/cru_dead.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/42_cru/cru_idle.bmp", 160, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/42_cru/cru_move.bmp", 1920, 280, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/42_cru/cru_select.bmp", 480, 280, 3, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/42_cru/cru_switch.bmp", 320, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/42_cru/cru_attack_down_shadow.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/42_cru/cru_attack_front_shadow.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/42_cru/cru_attack_up_shadow.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/42_cru/cru_damaged_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/42_cru/cru_dead_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/42_cru/cru_idle_shadow.bmp", 160, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/42_cru/cru_move_shadow.bmp", 1920, 280, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/42_cru/cru_select_shadow.bmp", 480, 280, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/42_cru/cru_switch_shadow.bmp", 320, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}


			break;

			case 4:
				if (!creature.level)
				{
					sprintf_s(creature.name, "수도사");
					creature.atk = 12;
					creature.def = 7;
					creature.hp = 30;
					creature.minDmg = 10;
					creature.maxDmg = 12;
					creature.speed = 5;
					creature.startX = 57;
					creature.startY = 100;
					creature.size = 1;

					creature.img[0]->init("image/Castle Creature/51_monk/monk_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/51_monk/monk_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/51_monk/monk_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Castle Creature/51_monk/monk_attack_range.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/51_monk/monk_damaged.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/51_monk/monk_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/51_monk/monk_idle.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/51_monk/monk_move.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/51_monk/monk_select.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/51_monk/monk_switch.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/51_monk/monk_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/51_monk/monk_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/51_monk/monk_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Castle Creature/51_monk/monk_attack_range_shadow.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/51_monk/monk_damaged_shadow.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/51_monk/monk_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/51_monk/monk_idle_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/51_monk/monk_move_shadow.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/51_monk/monk_select_shadow.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/51_monk/monk_switch_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}


				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "열성 수도사");
					creature.atk = 12;
					creature.def = 10;
					creature.hp = 30;
					creature.minDmg = 10;
					creature.maxDmg = 12;
					creature.speed = 7;
					creature.startX = 57;
					creature.startY = 100;
					creature.size = 1;
					creature.img[0]->init("image/Castle Creature/52_zealot/zealot_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/52_zealot/zealot_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/52_zealot/zealot_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Castle Creature/52_zealot/zealot_attack_range.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/52_zealot/zealot_damaged.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/52_zealot/zealot_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/52_zealot/zealot_idle.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/52_zealot/zealot_move.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/52_zealot/zealot_select.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/52_zealot/zealot_switch.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/52_zealot/zealot_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/52_zealot/zealot_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/52_zealot/zealot_attack_melee_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Castle Creature/52_zealot/zealot_attack_range_shadow.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/52_zealot/zealot_damaged_shadow.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/52_zealot/zealot_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/52_zealot/zealot_idle_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/52_zealot/zealot_move_shadow.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/52_zealot/zealot_select_shadow.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/52_zealot/zealot_switch_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}

				}


			break;

			case 5:
				if (!creature.level)
				{
					sprintf_s(creature.name, "기사단");
					creature.atk = 15;
					creature.def = 15;
					creature.hp = 100;
					creature.minDmg = 15;
					creature.maxDmg = 25;
					creature.speed = 7;
					creature.startX = 74;
					creature.startY = 120;
					creature.size = 2;
					creature.moveStart = 2;
					creature.moveEnd = 0;


					creature.img[0]->init("image/Castle Creature/61_cavalier/cavalier_attack_down.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/61_cavalier/cavalier_attack_front.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/61_cavalier/cavalier_attack_up.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/61_cavalier/cavalier_damaged.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/61_cavalier/cavalier_dead.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/61_cavalier/cavalier_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/61_cavalier/cavalier_move.bmp", 3200, 280, 16, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/61_cavalier/cavalier_select.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/61_cavalier/cavalier_switch.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/61_cavalier/cavalier_attack_down_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/61_cavalier/cavalier_attack_front_shadow.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/61_cavalier/cavalier_attack_up_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/61_cavalier/cavalier_damaged_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/61_cavalier/cavalier_dead_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/61_cavalier/cavalier_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/61_cavalier/cavalier_move_shadow.bmp", 3200, 280, 16, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/61_cavalier/cavalier_select_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/61_cavalier/cavalier_switch_shadow.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}


				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "챔피언");
					creature.atk = 16;
					creature.def = 16;
					creature.hp = 100;
					creature.minDmg = 20;
					creature.maxDmg = 25;
					creature.speed = 9;
					creature.startX = 74;
					creature.startY = 120;
					creature.size = 2;
					creature.moveStart = 2;
					creature.moveEnd = 0;

					creature.img[0]->init("image/Castle Creature/62_champion/champion_attack_down.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/62_champion/champion_attack_front.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/62_champion/champion_attack_up.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/62_champion/champion_damaged.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/62_champion/champion_dead.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/62_champion/champion_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/62_champion/champion_move.bmp", 3400, 280, 17, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/62_champion/champion_select.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/62_champion/champion_switch.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/62_champion/champion_attack_down_shadow.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/62_champion/champion_attack_front_shadow.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/62_champion/champion_attack_up_shadow.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/62_champion/champion_damaged_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/62_champion/champion_dead_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/62_champion/champion_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/62_champion/champion_move_shadow.bmp", 3400, 280, 17, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/62_champion/champion_select_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/62_champion/champion_switch_shadow.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}


			break;

			case 6:
				if (!creature.level)
				{
					sprintf_s(creature.name, "천사");
					creature.atk = 20;
					creature.def = 20;
					creature.hp = 200;
					creature.minDmg = 50;
					creature.maxDmg = 50;
					creature.speed = 12;
					creature.startX = 96;
					creature.startY = 128;
					creature.size = 1;
					creature.fly = true;
					creature.moveStart = 2;
					creature.moveEnd = 2;

					creature.img[0]->init("image/Castle Creature/71_angel/angel_attack_down.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/71_angel/angel_attack_front.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/71_angel/angel_attack_up.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/71_angel/angel_damaged.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/71_angel/angel_dead.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/71_angel/angel_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/71_angel/angel_move.bmp", 2200, 280, 11, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/71_angel/angel_select.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/71_angel/angel_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/71_angel/angel_attack_down_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/71_angel/angel_attack_front_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/71_angel/angel_attack_up_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/71_angel/angel_damaged_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/71_angel/angel_dead_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/71_angel/angel_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/71_angel/angel_move_shadow.bmp", 2200, 280, 11, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/71_angel/angel_select_shadow.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/71_angel/angel_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "대천사");
					creature.atk = 30;
					creature.def = 30;
					creature.hp = 250;
					creature.minDmg = 50;
					creature.maxDmg = 50;
					creature.speed = 18;
					creature.startX = 100;
					creature.startY = 130;
					creature.size = 2;
					creature.fly = true;
					creature.moveStart = 2;
					creature.moveEnd = 2;

					creature.img[0]->init("image/Castle Creature/72_arc/arc_attack_down.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Castle Creature/72_arc/arc_attack_front.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Castle Creature/72_arc/arc_attack_up.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Castle Creature/72_arc/arc_damaged.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Castle Creature/72_arc/arc_dead.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Castle Creature/72_arc/arc_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Castle Creature/72_arc/arc_move.bmp", 2400, 280, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Castle Creature/72_arc/arc_select.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Castle Creature/72_arc/arc_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Castle Creature/72_arc/arc_attack_down_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Castle Creature/72_arc/arc_attack_front_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Castle Creature/72_arc/arc_attack_up_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Castle Creature/72_arc/arc_damaged_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Castle Creature/72_arc/arc_dead_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Castle Creature/72_arc/arc_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Castle Creature/72_arc/arc_move_shadow.bmp", 2400, 280, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Castle Creature/72_arc/arc_select_shadow.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Castle Creature/72_arc/arc_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}


				}


			break;
			}




		break;

		case 1:

			switch (creature.tier)
			{
			case 0:
				if (!creature.level)
				{
					sprintf_s(creature.name, "동굴인");
					creature.atk = 4;
					creature.def = 3;
					creature.hp = 5;
					creature.minDmg = 1;
					creature.maxDmg = 3;
					creature.speed = 4;
					creature.startX = 57;
					creature.startY = 120;
					creature.size = 1;

					creature.img[0]->init("image/Dungeon Creature/11_troglodyte/troglodyte_down.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/11_troglodyte/troglodyte_front.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/11_troglodyte/troglodyte_up.bmp", 800, 320, 5, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/11_troglodyte/troglodyte_damaged.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/11_troglodyte/troglodyte_dead.bmp", 800, 320, 5, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/11_troglodyte/troglodyte_idle.bmp", 160, 320, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/11_troglodyte/troglodyte_move.bmp", 1120, 320, 7, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/11_troglodyte/troglodyte_select.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/11_troglodyte/troglodyte_switch.bmp", 320, 320, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/11_troglodyte/troglodyte_down_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/11_troglodyte/troglodyte_front_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/11_troglodyte/troglodyte_up_shadow.bmp", 800, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/11_troglodyte/troglodyte_damaged_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/11_troglodyte/troglodyte_dead_shadow.bmp", 800, 320, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/11_troglodyte/troglodyte_idle_shadow.bmp", 160, 320, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/11_troglodyte/troglodyte_move_shadow.bmp", 1120, 320, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/11_troglodyte/troglodyte_select_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/11_troglodyte/troglodyte_switch_shadow.bmp", 320, 320, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "지옥의 동굴인");
					creature.atk = 5;
					creature.def = 4;
					creature.hp = 6;
					creature.minDmg = 1;
					creature.maxDmg = 3;
					creature.speed = 5;
					creature.startX = 56;
					creature.startY = 120;
					creature.size = 1;

					creature.img[0]->init("image/Dungeon Creature/12_infernal/infernal_attack_down.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/12_infernal/infernal_attack_front.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/12_infernal/infernal_attack_up.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/12_infernal/infernal_damaged.bmp", 1120, 320, 7, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/12_infernal/infernal_dead.bmp", 640, 320, 4, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/12_infernal/infernal_idle.bmp", 160, 320, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/12_infernal/infernal_move.bmp", 1120, 320, 7, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/12_infernal/infernal_select.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/12_infernal/infernal_switch.bmp", 320, 320, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/12_infernal/infernal_attack_down_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/12_infernal/infernal_attack_front_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/12_infernal/infernal_attack_up_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/12_infernal/infernal_damaged_shadow.bmp", 1120, 320, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/12_infernal/infernal_dead_shadow.bmp", 640, 320, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/12_infernal/infernal_idle_shadow.bmp", 160, 320, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/12_infernal/infernal_move_shadow.bmp", 1120, 320, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/12_infernal/infernal_select_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/12_infernal/infernal_switch_shadow.bmp", 320, 320, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}

				break;

			case 1:
				if (!creature.level)
				{
					sprintf_s(creature.name, "하피");
					creature.atk = 6;
					creature.def = 5;
					creature.hp = 14;
					creature.minDmg = 1;
					creature.maxDmg = 4;
					creature.speed = 6;
					creature.startX = 64;
					creature.startY = 100;
					creature.size = 1;
					creature.fly = true;
					creature.moveStart = 2;
					creature.moveEnd = 4;


					creature.img[0]->init("image/Dungeon Creature/21_harpy/harpy_attack_down.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/21_harpy/harpy_attack_front.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/21_harpy/harpy_attack_up.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/21_harpy/harpy_damaged.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/21_harpy/harpy_dead.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/21_harpy/harpy_idle.bmp", 160, 240, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/21_harpy/harpy_move.bmp", 2080, 240, 13, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/21_harpy/harpy_select.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/21_harpy/harpy_switch.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/21_harpy/harpy_attack_down_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/21_harpy/harpy_attack_front_shadow.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/21_harpy/harpy_attack_up_shadow.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/21_harpy/harpy_damaged_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/21_harpy/harpy_dead_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/21_harpy/harpy_idle_shadow.bmp", 160, 240, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/21_harpy/harpy_move_shadow.bmp", 2080, 240, 13, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/21_harpy/harpy_select_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/21_harpy/harpy_switch_shadow.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "마녀 하피");
					creature.atk = 6;
					creature.def = 6;
					creature.hp = 14;
					creature.minDmg = 1;
					creature.maxDmg = 5;
					creature.speed = 9;
					creature.startX = 64;
					creature.startY = 100;
					creature.size = 1;
					creature.fly = true;
					creature.moveStart = 2;
					creature.moveEnd = 4;

					creature.img[0]->init("image/Dungeon Creature/22_hag/hag_attack_down.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/22_hag/hag_attack_front.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/22_hag/hag_attack_up.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/22_hag/hag_damaged.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/22_hag/hag_dead.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/22_hag/hag_idle.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/22_hag/hag_move.bmp", 2080, 240, 13, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/22_hag/hag_select.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/22_hag/hag_switch.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/22_hag/hag_attack_down_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/22_hag/hag_attack_front_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/22_hag/hag_attack_up_shadow.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/22_hag/hag_damaged_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/22_hag/hag_dead_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/22_hag/hag_idle_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/22_hag/hag_move_shadow.bmp", 2080, 240, 13, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/22_hag/hag_select_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/22_hag/hag_switch_shadow.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}

				break;

			case 2:
				if (!creature.level)
				{
					sprintf_s(creature.name, "주시자");
					creature.atk = 9;
					creature.def = 7;
					creature.hp = 22;
					creature.minDmg = 3;
					creature.maxDmg = 5;
					creature.speed = 5;
					creature.startX = 74;
					creature.startY = 104;
					creature.size = 1;

					creature.img[0]->init("image/Dungeon Creature/31_beholder/beholder_attack_down.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/31_beholder/beholder_attack_front.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/31_beholder/beholder_attack_up.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Dungeon Creature/31_beholder/beholder_attack_range.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/31_beholder/beholder_damaged.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/31_beholder/beholder_dead.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/31_beholder/beholder_idle.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/31_beholder/beholder_move.bmp", 2560, 240, 16, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/31_beholder/beholder_select.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/31_beholder/beholder_idle.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/31_beholder/beholder_attack_down_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/31_beholder/beholder_attack_front_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/31_beholder/beholder_attack_up_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Dungeon Creature/31_beholder/beholder_attack_range_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/31_beholder/beholder_damaged_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/31_beholder/beholder_dead_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/31_beholder/beholder_idle_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/31_beholder/beholder_move_shadow.bmp", 2560, 240, 16, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/31_beholder/beholder_select_shadow.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/31_beholder/beholder_idle_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));

					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "악마의 눈");
					creature.atk = 10;
					creature.def = 8;
					creature.hp = 22;
					creature.minDmg = 3;
					creature.maxDmg = 5;
					creature.speed = 7;
					creature.startX = 86;
					creature.startY = 100;
					creature.size = 1;

					creature.img[0]->init("image/Dungeon Creature/32_evil/evil_attack_down.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/32_evil/evil_attack_front.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/32_evil/evil_attack_up.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Dungeon Creature/32_evil/evil_attack_range.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/32_evil/evil_damaged.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/32_evil/evil_dead.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/32_evil/evil_idle.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/32_evil/evil_move.bmp", 2520, 240, 14, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/32_evil/evil_select.bmp", 540, 240, 3, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/32_evil/evil_idle.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/32_evil/evil_attack_down_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/32_evil/evil_attack_front_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/32_evil/evil_attack_up_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Dungeon Creature/32_evil/evil_attack_range_shadow.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/32_evil/evil_damaged_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/32_evil/evil_dead_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/32_evil/evil_idle_shadow.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/32_evil/evil_move_shadow.bmp", 2520, 240, 14, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/32_evil/evil_select_shadow.bmp", 540, 240, 3, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/32_evil/evil_idle_shadow.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));

					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}

				}


				break;

			case 3:
				if (!creature.level)
				{
					sprintf_s(creature.name, "메두사");
					creature.atk = 9;
					creature.def = 9;
					creature.hp = 25;
					creature.minDmg = 6;
					creature.maxDmg = 8;
					creature.speed = 5;
					creature.startX = 68;
					creature.startY = 111;
					creature.size = 2;

					creature.img[0]->init("image/Dungeon Creature/41_medusa/medusa_attack_melee.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/41_medusa/medusa_attack_melee.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/41_medusa/medusa_attack_melee.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Dungeon Creature/41_medusa/medusa_attack_range.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/41_medusa/medusa_damaged.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/41_medusa/medusa_dead.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/41_medusa/medusa_idle.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/41_medusa/medusa_move.bmp", 1920, 240, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/41_medusa/medusa_select.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/41_medusa/medusa_idle.bmp", 320, 240, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/41_medusa/medusa_attack_melee_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/41_medusa/medusa_attack_melee_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/41_medusa/medusa_attack_melee_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Dungeon Creature/41_medusa/medusa_attack_range_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/41_medusa/medusa_damaged_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/41_medusa/medusa_dead_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/41_medusa/medusa_idle_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/41_medusa/medusa_move_shadow.bmp", 1920, 240, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/41_medusa/medusa_select_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/41_medusa/medusa_idle_shadow.bmp", 320, 240, 2, 2, true, RGB(255, 0, 255));

					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}


				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "메두사 퀸");
					creature.atk = 10;
					creature.def = 10;
					creature.hp = 30;
					creature.minDmg = 6;
					creature.maxDmg = 8;
					creature.speed = 6;
					creature.startX = 89;
					creature.startY = 110;
					creature.size = 2;


					creature.img[0]->init("image/Dungeon Creature/42_queen/queen_attack_melee.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/42_queen/queen_attack_melee.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/42_queen/queen_attack_melee.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[6]->init("image/Dungeon Creature/42_queen/queen_attack_range.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/42_queen/queen_damaged.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/42_queen/queen_dead.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/42_queen/queen_idle.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/42_queen/queen_move.bmp", 2160, 240, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/42_queen/queen_select.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/42_queen/queen_idle.bmp", 360, 240, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/42_queen/queen_attack_melee_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/42_queen/queen_attack_melee_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/42_queen/queen_attack_melee_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[6]->init("image/Dungeon Creature/42_queen/queen_attack_range_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/42_queen/queen_damaged_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/42_queen/queen_dead_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/42_queen/queen_idle_shadow.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/42_queen/queen_move_shadow.bmp", 2160, 240, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/42_queen/queen_select_shadow.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/42_queen/queen_idle_shadow.bmp", 360, 240, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						creature.imgShadow[i]->AlphaInit();
					}

				}


				break;

			case 4:
				if (!creature.level)
				{
					sprintf_s(creature.name, "미노타우르스");
					creature.atk = 14;
					creature.def = 12;
					creature.hp = 50;
					creature.minDmg = 12;
					creature.maxDmg = 20;
					creature.speed = 6;
					creature.startX = 58;
					creature.startY = 100;
					creature.size = 1;

					creature.img[0]->init("image/Dungeon Creature/51_minotaur/minotaur_attack_down.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/51_minotaur/minotaur_attack_front.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/51_minotaur/minotaur_attack_up.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/51_minotaur/minotaur_damaged.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/51_minotaur/minotaur_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/51_minotaur/minotaur_idle.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/51_minotaur/minotaur_move.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/51_minotaur/minotaur_select.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/51_minotaur/minotaur_switch.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/51_minotaur/minotaur_attack_down_shadow.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/51_minotaur/minotaur_attack_front_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/51_minotaur/minotaur_attack_up_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/51_minotaur/minotaur_damaged_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/51_minotaur/minotaur_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/51_minotaur/minotaur_idle_shadow.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/51_minotaur/minotaur_move_shadow.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/51_minotaur/minotaur_select_shadow.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/51_minotaur/minotaur_switch_shadow.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "미노타우르스 킹");
					creature.atk = 15;
					creature.def = 15;
					creature.hp = 50;
					creature.minDmg = 12;
					creature.maxDmg = 20;
					creature.speed = 8;
					creature.startX = 65;
					creature.startY = 114;
					creature.size = 1;

					creature.img[0]->init("image/Dungeon Creature/52_king/king_attack_down.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/52_king/king_attack_front.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/52_king/king_attack_up.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/52_king/king_damaged.bmp", 810, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/52_king/king_dead.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/52_king/king_idle.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/52_king/king_move.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/52_king/king_select.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/52_king/king_switch.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/52_king/king_attack_down_shadow.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/52_king/king_attack_front_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/52_king/king_attack_up_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/52_king/king_damaged_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/52_king/king_dead_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/52_king/king_idle_shadow.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/52_king/king_move_shadow.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/52_king/king_select_shadow.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/52_king/king_switch_shadow.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}


				}


				break;

			case 5:
				if (!creature.level)
				{
					sprintf_s(creature.name, "만티코어");
					creature.atk = 15;
					creature.def = 13;
					creature.hp = 80;
					creature.minDmg = 14;
					creature.maxDmg = 20;
					creature.speed = 7;
					creature.startX = 104;
					creature.startY = 121;
					creature.size = 2;
					creature.fly = true;
					creature.moveStart = 3;
					creature.moveEnd = 4;


					creature.img[0]->init("image/Dungeon Creature/61_manticore/manticore_attack_down.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/61_manticore/manticore_attack_front.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/61_manticore/manticore_attack_up.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/61_manticore/manticore_damaged.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/61_manticore/manticore_dead.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/61_manticore/manticore_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/61_manticore/manticore_move.bmp", 2600, 280, 13, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/61_manticore/manticore_select.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/61_manticore/manticore_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/61_manticore/manticore_attack_down_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/61_manticore/manticore_attack_front_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/61_manticore/manticore_attack_up_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/61_manticore/manticore_damaged_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/61_manticore/manticore_dead_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/61_manticore/manticore_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/61_manticore/manticore_move_shadow.bmp", 2600, 280, 13, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/61_manticore/manticore_select_shadow.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/61_manticore/manticore_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "스코피코어");
					creature.atk = 16;
					creature.def = 14;
					creature.hp = 80;
					creature.minDmg = 14;
					creature.maxDmg = 20;
					creature.speed = 11;
					creature.startX = 102;
					creature.startY = 122;
					creature.size = 2;
					creature.fly = true;
					creature.moveStart = 3;
					creature.moveEnd = 3;

					creature.img[0]->init("image/Dungeon Creature/62_scorpicore/scorpicore_attack_down.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/62_scorpicore/scorpicore_attack_front.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/62_scorpicore/scorpicore_attack_up.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/62_scorpicore/scorpicore_damaged.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/62_scorpicore/scorpicore_dead.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/62_scorpicore/scorpicore_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/62_scorpicore/scorpicore_move.bmp", 2400, 280, 12, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/62_scorpicore/scorpicore_select.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/62_scorpicore/scorpicore_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/62_scorpicore/scorpicore_attack_down_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/62_scorpicore/scorpicore_attack_front_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/62_scorpicore/scorpicore_attack_up_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/62_scorpicore/scorpicore_damaged_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/62_scorpicore/scorpicore_dead_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/62_scorpicore/scorpicore_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/62_scorpicore/scorpicore_move_shadow.bmp", 2400, 280, 12, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/62_scorpicore/scorpicore_select_shadow.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/62_scorpicore/scorpicore_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}



				}


				break;

			case 6:
				if (!creature.level)
				{
					sprintf_s(creature.name, "레드 드래곤");
					creature.atk = 19;
					creature.def = 19;
					creature.hp = 180;
					creature.minDmg = 40;
					creature.maxDmg = 50;
					creature.speed = 11;
					creature.startX = 110;
					creature.startY = 154;
					creature.size = 2;
					creature.fly = true;
					creature.moveStart = 3;
					creature.moveEnd = 5;

					creature.img[0]->init("image/Dungeon Creature/71_red/red_attack_down.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/71_red/red_attack_front.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/71_red/red_attack_up.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/71_red/red_damaged.bmp", 2100, 440, 7, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/71_red/red_dead.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/71_red/red_idle.bmp", 300, 440, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/71_red/red_move.bmp", 3300, 440, 11, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/71_red/red_select.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/71_red/red_switch.bmp", 600, 440, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/71_red/red_attack_down_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/71_red/red_attack_front_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/71_red/red_attack_up_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/71_red/red_damaged_shadow.bmp", 2100, 440, 7, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/71_red/red_dead_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/71_red/red_idle_shadow.bmp", 300, 440, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/71_red/red_move_shadow.bmp", 3300, 440, 11, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/71_red/red_select_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/71_red/red_switch_shadow.bmp", 600, 440, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}
				else if (creature.level)
				{
					sprintf_s(creature.name, "블랙 드래곤");
					creature.atk = 25;
					creature.def = 25;
					creature.hp = 300;
					creature.minDmg = 40;
					creature.maxDmg = 50;
					creature.speed = 15;
					creature.startX = 140;
					creature.startY = 154;
					creature.size = 2;
					creature.fly = true;
					creature.moveStart = 3;
					creature.moveEnd = 5;


					creature.img[0]->init("image/Dungeon Creature/72_black/black_attack_down.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[1]->init("image/Dungeon Creature/72_black/black_attack_front.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[2]->init("image/Dungeon Creature/72_black/black_attack_up.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[8]->init("image/Dungeon Creature/72_black/black_damaged.bmp", 1500, 440, 5, 2, true, RGB(255, 0, 255));
					creature.img[9]->init("image/Dungeon Creature/72_black/black_dead.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[7]->init("image/Dungeon Creature/72_black/black_idle.bmp", 300, 440, 1, 2, true, RGB(255, 0, 255));
					creature.img[3]->init("image/Dungeon Creature/72_black/black_move.bmp", 3300, 440, 11, 2, true, RGB(255, 0, 255));
					creature.img[4]->init("image/Dungeon Creature/72_black/black_select.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.img[5]->init("image/Dungeon Creature/72_black/black_switch.bmp", 600, 440, 2, 2, true, RGB(255, 0, 255));
					creature.imgShadow[0]->init("image/Dungeon Creature/72_black/black_attack_down_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[1]->init("image/Dungeon Creature/72_black/black_attack_front_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[2]->init("image/Dungeon Creature/72_black/black_attack_up_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[8]->init("image/Dungeon Creature/72_black/black_damaged_shadow.bmp", 1500, 440, 5, 2, true, RGB(255, 0, 255));
					creature.imgShadow[9]->init("image/Dungeon Creature/72_black/black_dead_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[7]->init("image/Dungeon Creature/72_black/black_idle_shadow.bmp", 300, 440, 1, 2, true, RGB(255, 0, 255));
					creature.imgShadow[3]->init("image/Dungeon Creature/72_black/black_move_shadow.bmp", 3300, 440, 11, 2, true, RGB(255, 0, 255));
					creature.imgShadow[4]->init("image/Dungeon Creature/72_black/black_select_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
					creature.imgShadow[5]->init("image/Dungeon Creature/72_black/black_switch_shadow.bmp", 600, 440, 2, 2, true, RGB(255, 0, 255));
					for (int i = 0; i < STATE_END; i++)
					{
						if (i == (int)STATE_RANGE) continue;
						creature.imgShadow[i]->AlphaInit();
					}

				}


				break;
			}

		break;
		}

		creature.currentHp = creature.hp;





		return creature;
	}







}