#include "stdafx.h"
#include "mainMenu.h"
#include "mapTool.h"

mainMenu::mainMenu() {}
mainMenu::~mainMenu() {}

HRESULT	mainMenu::init(void)
{
	//============================= I N I T ============================
	imageInit();

	//==================================
	for (int i = 0; i < MAXSAVE; i++)
	{
		ZeroMemory(&_saveFile[i], sizeof(SAVE));
		_saveFile[i].number = i;
	}

	//==================================
	loadFileList();


	_currentButton = MMB_NEW;


	_newActive = false;
	_sceneChange = false;
	_buttonActive = false;
	
	_saveNum = 0;
	_fadeAlpha = 0;

	//=================== R E C T   M A K E ============================
	_mapTool = RectMake(600, 246, 96, 112);
	_saveWindow = RectMake(-450, 10, 450, 580);

	return S_OK;
}

void mainMenu::release(void)
{

}

void mainMenu::update(void)
{
	


	//============= F U N C T I O N =========================
	inputMenu();
	sceneChange();
	if(!_sceneChange && !_newActive) buttonActive();
	windowMove();
}

void mainMenu::render(void)
{

	backgroundDraw();

	windowDraw();

	buttonDraw();

	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), _fadeAlpha);

}

void mainMenu::backgroundDraw(void)
{
	IMAGEMANAGER->findImage("mainBackground")->render(getMemDC());
	IMAGEMANAGER->findImage("mainBackgroundSecond")->render(getMemDC(), 800, 0);
}

void mainMenu::windowDraw(void)
{
	IMAGEMANAGER->findImage("window_save")->render(getMemDC(),
		_saveWindow.left, _saveWindow.top);

	IMAGEMANAGER->findImage("save_selectbox")->render(getMemDC(),
		_saveWindow.left + 23, _saveWindow.top + 116 + 25 * _saveNum);
	
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	for (int i = 0; i < MAXSAVE; i++)
	{
		
		if (_saveFile[i].fileName.size())
			TextOut(getMemDC(), _saveWindow.left + 70, _saveWindow.top + 118 + 25 * _saveFile[i].number,
				_saveFile[i].fileName.c_str(), _saveFile[i].fileName.length());
	}

	SetTextColor(getMemDC(), RGB(0, 0, 0));

}

void mainMenu::buttonDraw(void)
{
	// 565 251
	IMAGEMANAGER->findImage("button_main_maptool")->render(getMemDC(), _mapTool.left, _mapTool.top);
	IMAGEMANAGER->findImage("font_maptool")->render(getMemDC(), _mapTool.left - 35, _mapTool.top + 35);
	if (_buttonActive)
	{
		switch (_currentButton)
		{
		case MMB_NEW:
			IMAGEMANAGER->findImage("button_main_new")->render(getMemDC(), 536, 11);
		break;
		case MMB_LOAD:
			IMAGEMANAGER->findImage("button_main_load")->render(getMemDC(), 529, 132);
		break;
		case MMB_MAP:
			IMAGEMANAGER->findImage("button_main_map")->render(getMemDC(), 563, 251);
			IMAGEMANAGER->findImage("font_maptool")->render(getMemDC(), _mapTool.left - 35, _mapTool.top + 35);

			break;
		case MMB_CREDIT:
			IMAGEMANAGER->findImage("button_main_credit")->render(getMemDC(), 556, 357);
			break;
		case MMB_QUIT:
			IMAGEMANAGER->findImage("button_main_quit")->render(getMemDC(), 587, 469);
			break;
		}

	}
}

void mainMenu::windowMove(void)
{
	if (_newActive)
	{
		_saveWindow.left += 20;
		_saveWindow.right += 20;

		if (_saveWindow.right >= 450)
		{
			_saveWindow.right = 450;
			_saveWindow.left = 0;
		}

	}

	else
	{
		_saveWindow.left -= 20;
		_saveWindow.right -= 20;
		if (_saveWindow.right < 0)
		{
			_saveWindow.left = -450;
			_saveWindow.right = 0;
		}
	}

}

void mainMenu::loadFileList(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("map/saveFileList.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _saveFile, sizeof(SAVE)*MAXSAVE, &read, NULL);

	CloseHandle(file);

}

void mainMenu::loadMap(string mapName)
{
	
}

void mainMenu::sceneChange(void)
{
	if (_sceneChange)
	{
		_fadeAlpha+=4;
		
		if (_fadeAlpha >= 255)
		{
			switch (_currentButton)
			{
			case MMB_NEW:
				DATABASE->setSaveNum(_saveNum);
				DATABASE->setSaveName(_saveFile[_saveNum].fileName);
				SCENEMANAGER->changeScene("gameScene");
				break;
			case MMB_LOAD:
				break;
			case MMB_MAP:
				SCENEMANAGER->changeScene("mapTool");
				break;
			case MMB_CREDIT:
				break;
			case MMB_QUIT:
				break;
			}
		}
	}
}

void mainMenu::buttonActive(void)
{
	if (PtInRect(&RectMake(588, 23, 110, 540), _ptMouse))
	{
		if (_ptMouse.y >= 23 && _ptMouse.y < 116)
		{
			_buttonActive = true;
			_currentButton = MMB_NEW;
		}
		else if (_ptMouse.y >= 142 && _ptMouse.y < 242)
		{
			_buttonActive = true;
			_currentButton = MMB_LOAD;

		}
		else if (_ptMouse.y >= 260 && _ptMouse.y < 340)
		{
			_buttonActive = true;
			_currentButton = MMB_MAP;

		}
		else if (_ptMouse.y >= 370 && _ptMouse.y < 460)
		{
			_buttonActive = true;
			_currentButton = MMB_CREDIT;

		}
		else if (_ptMouse.y >= 485 && _ptMouse.y < 567)
		{
			_buttonActive = true;
			_currentButton = MMB_QUIT;
		}
		else _buttonActive = false;
	} 
	else _buttonActive = false;

}

void mainMenu::inputMenu(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_newActive && _ptMouse.x > 450)
		{
			_newActive = false;
		}

	}


	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//====258 460


		if (_buttonActive)
		{
			switch (_currentButton)
			{
			case MMB_NEW:
				_newActive = true;
				break;
			case MMB_LOAD:
				break;
			case MMB_MAP:
				_sceneChange = true;
				break;
			case MMB_CREDIT:
				break;
			case MMB_QUIT: PostQuitMessage(0);
				break;
			}
		}

		if (!_sceneChange&& _newActive && _ptMouse.x <= 450)
		{
			for (int i = 0; i < MAXSAVE; i++)
			{
				if (PtInRect(&RectMake(_saveWindow.left + 23,
					_saveWindow.top + 116 + i * 25, 360, 25), _ptMouse))
				{
					_saveNum = i;
				}
			}

			if (PtInRect(&RectMake(_saveWindow.left + 258, _saveWindow.top + 460, 94, 42), _ptMouse))
			{
				_sceneChange = true;
			}
		}

	}

}

void mainMenu::imageInit(void)
{

	//===================== M A I N   M E N U ===========================
	IMAGEMANAGER->addImage("mainBackground", "image/ui/mainMenuBackGround.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mainBackgroundSecond", "image/ui/mainMenuSecond.bmp", 300, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("font_maptool", "image/font/font_mapTool.bmp", 175, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_main_maptool", "image/ui/maptoolButton.bmp",96, 112, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_main_new", "image/mainMenu/button_mainMenu_new.bmp", 210, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_main_load", "image/mainMenu/button_mainMenu_load.bmp", 225, 121, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_main_map", "image/mainMenu/button_mainMenu_map.bmp", 164, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_main_credit", "image/mainMenu/button_mainMenu_credit.bmp", 172, 112, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_main_quit", "image/mainMenu/button_mainMenu_quit.bmp", 111, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fade", "image/ui/fade.bmp", 1100, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("fade")->AlphaInit();
	
	//===================== U I ===============================
	
	//===================== G A M E S C E N E ============================
	IMAGEMANAGER->addImage("gameUI", "image/gameScene/ui/gameUI.bmp", 1100, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameMiniview", "image/gameScene/ui/miniView72.bmp", 48, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("game_background", "image/gameScene/ui/background.bmp", 788, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("edge_left", "image/gameScene/ui/edge_left.bmp", 32, 2368, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("edge_right", "image/gameScene/ui/edge_right.bmp", 32, 2368, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("edge_top", "image/gameScene/ui/edge_top.bmp", 2368, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("edge_bottom", "image/gameScene/ui/edge_bottom.bmp", 2368, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("game_mine", "image/mapObject/mine.bmp", 1280, 672, 8, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("game_mine_shadow", "image/mapObject/mine_shadow.bmp", 1280, 672, 8, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("game_mine_shadow")->AlphaInit();
	IMAGEMANAGER->addFrameImage("game_ev", "image/mapObject/ev.bmp", 768, 960, 8, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("game_ev_shadow", "image/mapObject/ev_shadow.bmp", 768, 960, 8, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("game_ev_shadow")->AlphaInit();
	

	//===================== H E R O =================
	IMAGEMANAGER->addFrameImage("hero_castle", "image/gameScene/hero/hero_castle.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hero_castle_shadow", "image/gameScene/hero/hero_castle_shadow.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hero_dungeon", "image/gameScene/hero/hero_dungeon.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hero_dungeon_shadow", "image/gameScene/hero/hero_dungeon_shadow.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hero_flag", "image/gameScene/hero/hero_flag.bmp", 192, 512, 2, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("hero_castle_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("hero_dungeon_shadow")->AlphaInit();
	IMAGEMANAGER->addFrameImage("path", "image/gameScene/hero/path.bmp", 192, 288, 6, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("path_middle", "image/gameScene/hero/middlePath.bmp", 768, 32, 24, 1, true, RGB(255, 0, 255));


	//==============================  U  I =============================
	IMAGEMANAGER->addImage("gamebutton_spell", "image/gameScene/ui/button_spell.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_hero", "image/gameScene/ui/button_nexthero.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_turn", "image/gameScene/ui/button_turn.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_summary", "image/gameScene/ui/button_camp_summary.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_config", "image/gameScene/ui/button_configuration.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_goon", "image/gameScene/ui/button_goon.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("window_config", "image/gameScene/ui/window_config.bmp", 480, 486, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_save", "image/gameScene/ui/select_save.bmp", 100, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_load", "image/gameScene/ui/select_load.bmp", 100, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_re", "image/gameScene/ui/select_re.bmp", 100, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_main", "image/gameScene/ui/select_main.bmp", 100, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_quit", "image/gameScene/ui/select_quit.bmp", 100, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gamebutton_return", "image/gameScene/ui/select_return.bmp", 100, 48, true, RGB(255, 0, 255));




	//================ T E R R A I N ==========================
	IMAGEMANAGER->addFrameImage("terrain", "image/mapTool/terrain_idle.bmp", 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_green", "image/mapTool/terrain_green.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_water", "image/mapTool/terrain_test.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain_volcano", "image/mapTool/terrain_volcano.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));

	//================ R O A D =================================
	IMAGEMANAGER->addFrameImage("road_normal", "image/mapTool/road_normal.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("road_rock", "image/mapTool/road_rock.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("road_river", "image/mapTool/road_river.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));

	//================ B U I L D I N G =========================
	//============ C A M P 
	IMAGEMANAGER->addFrameImage("building_castle", "image/mapTool/camp_castle.bmp", 576, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("building_castle_shadow", "image/mapTool/camp_castle_shadow.bmp", 576, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("building_dungeon", "image/mapTool/camp_dungeon.bmp", 576, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("building_dungeon_shadow", "image/mapTool/camp_dungeon_shadow.bmp", 576, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("building_castle_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("building_dungeon_shadow")->AlphaInit();
	IMAGEMANAGER->addImage("point_castle", "image/mapTool/point_castle.bmp", 192, 192, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("point_dungeon", "image/mapTool/point_dungeon.bmp", 192, 192, true, RGB(255, 0, 255));

	//============ MINE
	IMAGEMANAGER->addFrameImage("mine_gold", "image/mapTool/mine/mine_gold.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_crystal", "image/mapTool/mine/mine_crystal.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_wood", "image/mapTool/mine/mine_wood.bmp", 160, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_iron", "image/mapTool/mine/mine_iron.bmp", 96, 64, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_sulfur", "image/mapTool/mine/mine_sulfur.bmp", 96, 64, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_mercury", "image/mapTool/mine/mine_mercury.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_gem", "image/mapTool/mine/mine_gem.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_gold_shadow", "image/mapTool/mine/mine_gold_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_crystal_shadow", "image/mapTool/mine/mine_crystal_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_wood_shadow", "image/mapTool/mine/mine_wood_shadow.bmp", 160, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_sulfur_shadow", "image/mapTool/mine/mine_sulfur_shadow.bmp", 96, 64, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_mercury_shadow", "image/mapTool/mine/mine_mercury_shadow.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_gem_shadow", "image/mapTool/mine/mine_gem_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("mine_gold_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_crystal_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_wood_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_sulfur_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_mercury_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("mine_gem_shadow")->AlphaInit();
	IMAGEMANAGER->addImage("point_mine", "image/mapTool/point_mine.bmp", 96, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("point_wood", "image/mapTool/point_wood.bmp", 160, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("point_mercury", "image/mapTool/point_mercury.bmp", 96, 96, true, RGB(255, 0, 255));

	//============= E V E N T 
	IMAGEMANAGER->addFrameImage("ev_lvlup", "image/mapTool/ev/ev_lvlup.bmp", 96, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_physical", "image/mapTool/ev/ev_physical.bmp", 96, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_magical", "image/mapTool/ev/ev_magical.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_skill", "image/mapTool/ev/ev_skill.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_magic", "image/mapTool/ev/ev_magic.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_luck", "image/mapTool/ev/ev_luck.bmp", 768, 32, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_morale", "image/mapTool/ev/ev_morale.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_explore", "image/mapTool/ev/ev_explore.bmp", 64, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_movement", "image/mapTool/ev/ev_movement.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_resource", "image/mapTool/ev/ev_resource.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("ev_lvlup_shadow", "image/mapTool/ev/ev_lvlup_shadow.bmp", 96, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_physical_shadow", "image/mapTool/ev/ev_physical_shadow.bmp", 96, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_magical_shadow", "image/mapTool/ev/ev_magical_shadow.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_skill_shadow", "image/mapTool/ev/ev_skill_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_magic_shadow", "image/mapTool/ev/ev_magic_shadow.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_luck_shadow", "image/mapTool/ev/ev_luck_shadow.bmp", 768, 32, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_morale_shadow", "image/mapTool/ev/ev_morale_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_explore_shadow", "image/mapTool/ev/ev_explore_shadow.bmp", 64, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_movement_shadow", "image/mapTool/ev/ev_movement_shadow.bmp", 768, 64, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ev_resource_shadow", "image/mapTool/ev/ev_resource_shadow.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->findImage("ev_lvlup_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_physical_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_magical_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_skill_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_magic_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_luck_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_morale_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_explore_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_movement_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("ev_resource_shadow")->AlphaInit();

	//================ O B S T A C L E =====================
	IMAGEMANAGER->addFrameImage("obstacle_1x1", "image/mapTool/1x1/1x1_obstacle.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_2x2", "image/mapTool/1x1/2x2_obstacle.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_4x4", "image/mapTool/1x1/4x4_obstacle.bmp", 256, 512, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_6x4", "image/mapTool/1x1/6x4_obstacle.bmp", 192, 256, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_1x1_shadow", "image/mapTool/1x1/1x1_obstacle_shadow.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_2x2_shadow", "image/mapTool/1x1/2x2_obstacle_shadow.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_4x4_shadow", "image/mapTool/1x1/4x4_obstacle_shadow.bmp", 256, 512, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("obstacle_6x4_shadow", "image/mapTool/1x1/6x4_obstacle_shadow.bmp", 192, 256, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->findImage("obstacle_1x1_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("obstacle_2x2_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("obstacle_4x4_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("obstacle_6x4_shadow")->AlphaInit();

	//==================== L O O T I N G ====================
	IMAGEMANAGER->addFrameImage("resources", "image/mapTool/resource/resource.bmp", 192, 96, 3, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("resources_shadow", "image/mapTool/resource/resource_shadow.bmp", 192, 96, 3, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("resources_shadow")->AlphaInit();
	IMAGEMANAGER->addFrameImage("artifact_weapon", "image/mapTool/resource/artifact_weapon.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("artifact_shield", "image/mapTool/resource/artifact_shield.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("artifact_armor", "image/mapTool/resource/artifact_armor.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("artifact_helmet", "image/mapTool/resource/artifact_helmet.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("artifact_acc", "image/mapTool/resource/artifact_acc.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));

	//===================== U N I T ===========================
	IMAGEMANAGER->addFrameImage("unit_castle", "image/mapTool/unit/unit_castle.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("unit_dungeon", "image/mapTool/unit/unit_dungeon.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("unit_castle_shadow", "image/mapTool/unit/unit_castle_shadow.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("unit_dungeon_shadow", "image/mapTool/unit/unit_dungeon_shadow.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("unit_castle_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("unit_dungeon_shadow")->AlphaInit();

	//================ M I N I   M A P =====================
	IMAGEMANAGER->addImage("miniView72", "image/mapTool/miniView72_.bmp", 48, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("miniView36", "image/mapTool/miniView36.bmp", 144, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap", "image/mapTool/minimap_idle.bmp", 148, 148, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_green", "image/mapTool/minimap_green.bmp", 148, 148, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_volcano", "image/mapTool/minimap_volcano.bmp", 148, 148, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniTerrain72", "image/mapTool/miniTerrain72.bmp", 15, 15, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniTerrain36", "image/mapTool/miniTerrain36.bmp", 30, 30, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniBuilding72", "image/mapTool/miniBuilding72.bmp", 54, 18, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniBuilding36", "image/mapTool/miniBuilding36.bmp", 108, 36, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniObstacle72", "image/mapTool/1x1/miniObstacle72.bmp", 60, 15, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("miniObstacle36", "image/mapTool/1x1/miniObstacle36.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("miniObstacle72")->AlphaInit();
	IMAGEMANAGER->findImage("miniObstacle36")->AlphaInit();

	//================ U S E R   I N T E R F A C E =================
	IMAGEMANAGER->addImage("mapToolUI", "image/ui/mapToolUI.bmp", 312, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("mapToolUI")->setX(788);
	IMAGEMANAGER->addImage("mapToolMark", "image/ui/mapToolMark.bmp", 300, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("mapToolMark")->setX(796);
	IMAGEMANAGER->findImage("mapToolMark")->setY(2);

	//=============== C U R S O R =========================
	IMAGEMANAGER->addImage("select", "image/mapTool/selectRect.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("select2", "image/mapTool/selectRect2.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("width", "image/mapTool/line_width.bmp", 768, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("height", "image/mapTool/line_height.bmp", 2, 576, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("closed", "image/mapTool/closedArea.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("closed")->AlphaInit();
	IMAGEMANAGER->findImage("closed")->setAlphaSource(50);
	IMAGEMANAGER->addImage("enter", "image/mapTool/enter.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("enter")->AlphaInit();

	//=============== B U T T O N =========================
	IMAGEMANAGER->addFrameImage("button_ma", "image/mapTool/button_ma.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_menu", "image/mapTool/button_menu.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_re", "image/mapTool/button_re.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_save", "image/mapTool/button_save.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_load", "image/mapTool/button_load.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

	//==================================== T I L E 
	IMAGEMANAGER->addFrameImage("tileButton", "image/mapTool/tileButton.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("roadButton", "image/mapTool/roadButton.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_green", "image/mapTool/button_green.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_water", "image/mapTool/button_water.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_volcano", "image/mapTool/button_volcano.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_terrain_green", "image/mapTool/button_terrain_green.bmp", 256, 384, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_terrain_water", "image/mapTool/button_terrain_water.bmp", 256, 384, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_terrain_volcano", "image/mapTool/button_terrain_volcano.bmp", 256, 384, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_terrain_green_large", "image/mapTool/button_terrain_green_L.bmp", 256, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_terrain_water_large", "image/mapTool/button_terrain_water_large.bmp", 256, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_terrain_volcano_large", "image/mapTool/button_terrain_volcano_large.bmp", 256, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("push", "image/mapTool/button_push.bmp", 32, 32, true, RGB(255, 0, 255));

	//==================================== R O A D 
	IMAGEMANAGER->addFrameImage("button_road_normal", "image/mapTool/button_road_normal.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_normal", "image/mapTool/button_normal.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_road_rock", "image/mapTool/button_road_rock.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_rock", "image/mapTool/button_rock.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_road_river", "image/mapTool/button_road_river.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_river", "image/mapTool/button_river.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

	//==================================== C A M P 
	IMAGEMANAGER->addFrameImage("button_castle", "image/mapTool/button_castle.bmp", 256, 128, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_dungeon", "image/mapTool/button_dungeon.bmp", 256, 128, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("buildingButton", "image/mapTool/buildingButton.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_camp", "image/mapTool/button_camp.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

	//==================================== M I N E
	IMAGEMANAGER->addFrameImage("button_mine", "image/mapTool/button_mine.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_gold", "image/mapTool/button_gold.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_crystal", "image/mapTool/button_crystal.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_wood", "image/mapTool/button_wood.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_iron", "image/mapTool/button_iron.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_sulfur", "image/mapTool/button_sulfur.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_mercury", "image/mapTool/button_mercury.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_gem", "image/mapTool/button_gem.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));

	//==================================== E V E N T 
	IMAGEMANAGER->addFrameImage("button_ev", "image/mapTool/button_ev.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_lvlup", "image/mapTool/button_lvlup.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_physical", "image/mapTool/button_physical.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_magical", "image/mapTool/button_magical.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_skill", "image/mapTool/button_skill.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_magic", "image/mapTool/button_magic.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_luck", "image/mapTool/button_luck.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_morale", "image/mapTool/button_morale.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_explore", "image/mapTool/button_explore.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_movement", "image/mapTool/button_movement.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_resource", "image/mapTool/button_resource.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));

	//==================================== O B S T A C L E
	IMAGEMANAGER->addFrameImage("button_obstacle", "image/mapTool/1x1/button_obstacle.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_1x1", "image/mapTool/1x1/button_1x1.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_2x2", "image/mapTool/1x1/button_2x2.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_4x4", "image/mapTool/1x1/button_4x4.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_A", "image/mapTool/1x1/button_A.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_1x1", "image/mapTool/1x1/1x1_obstacle.bmp", 256, 128, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_2x2", "image/mapTool/1x1/2x2_obstacle.bmp", 256, 256, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_4x4", "image/mapTool/1x1/4x4_obstacle.bmp", 256, 512, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_6x4", "image/mapTool/1x1/6x4_obstacle.bmp", 192, 256, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_obstacle_2x2_large", "image/mapTool/1x1/2x2_obstacle.bmp", 256, 256, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_obstacle_4x4_large", "image/mapTool/1x1/4x4_obstacle.bmp", 256, 512, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_obstacle_6x4_large", "image/mapTool/1x1/6x4_obstacle.bmp", 192, 256, true, RGB(255, 0, 255));

	//==================================== R E S O U R C E 
	IMAGEMANAGER->addFrameImage("button_looting", "image/mapTool/resource/button_looting.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_resources", "image/mapTool/resource/button_resource.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_artifact", "image/mapTool/resource/button_artifact.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_looting_artifact", "image/mapTool/resource/button_looting_artifact.bmp", 256, 384, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_looting_artifact_large", "image/mapTool/resource/button_looting_artifact.bmp", 256, 384, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_looting_resources", "image/mapTool/resource/button_looting_resources.bmp", 192, 96, true, RGB(255, 0, 255));

	//==================================== U N I T 
	IMAGEMANAGER->addFrameImage("button_unit", "image/mapTool/unit/button_unit.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_hero", "image/mapTool/unit/button_hero.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_creature", "image/mapTool/unit/button_creature.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_unit_castle", "image/mapTool/unit/unit_castle.bmp", 256, 256, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_unit_dungeon", "image/mapTool/unit/unit_dungeon.bmp", 256, 256, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_unit_castle_large", "image/mapTool/unit/unit_castle.bmp", 256, 256, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_unit_dungeon_large", "image/mapTool/unit/unit_dungeon.bmp", 256, 256, true, RGB(255, 0, 255));
	//====================================== U I 
	IMAGEMANAGER->addFrameImage("empty", "image/mapTool/empty.bmp", 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("emptyS", "image/mapTool/empty.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("up", "image/mapTool/arrow_up.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down", "image/mapTool/arrow_down.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("left", "image/mapTool/arrow_left.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("right", "image/mapTool/arrow_right.bmp", 42, 21, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("size1", "image/mapTool/size_1.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("size2", "image/mapTool/size_2.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sizeF", "image/mapTool/size_flexible.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("erase", "image/mapTool/erase.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_brush_size", "image/mapTool/buttonBrushSize.bmp", 96, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("move", "image/mapTool/moveIcon.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

	//====================================== W I N D O W ==============
	IMAGEMANAGER->addImage("window_confirm", "image/mapTool/button_confirm.bmp", 420, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("window_save", "image/mapTool/window_save.bmp", 450, 580, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save_selectbox", "image/mapTool/save_selectbox.bmp", 360, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("changeName", "image/mapTool/changeName.bmp", 360, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("changeName")->AlphaInit();
	IMAGEMANAGER->addImage("save_confirm", "image/mapTool/savebox.bmp", 419, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tile_select", "image/mapTool/tileSelect.bmp", 256, 512, 1, 4, true, RGB(255, 0, 255));

}