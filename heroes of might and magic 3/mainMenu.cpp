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
				DATABASE->loadFileList();
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
	{
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

	}
	
	//===================== U I ===============================
	
	//===================== G A M E S C E N E ============================
	{
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
		IMAGEMANAGER->addFrameImage("number", "image/gameScene/ui/number.bmp", 70, 10, 10, 1, true, RGB(255, 0, 255));

	}

	//===================== H E R O =================
	{
		IMAGEMANAGER->addFrameImage("hero_castle", "image/gameScene/hero/hero_castle.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hero_castle_shadow", "image/gameScene/hero/hero_castle_shadow.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hero_dungeon", "image/gameScene/hero/hero_dungeon.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hero_dungeon_shadow", "image/gameScene/hero/hero_dungeon_shadow.bmp", 864, 512, 9, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hero_flag", "image/gameScene/hero/hero_flag.bmp", 192, 512, 2, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("hero_castle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hero_dungeon_shadow")->AlphaInit();
		IMAGEMANAGER->addFrameImage("path", "image/gameScene/hero/path.bmp", 192, 288, 6, 9, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("path_middle", "image/gameScene/hero/middlePath.bmp", 768, 32, 24, 1, true, RGB(255, 0, 255));

		IMAGEMANAGER->addFrameImage("portrait_large", "image/gameScene/hero/portrait/large.bmp", 290, 128, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("portrait_small", "image/gameScene/hero/portrait/small.bmp", 230, 60, 5, 2, true, RGB(255, 0, 255));





	}

	//==================== C A M P
	{
		IMAGEMANAGER->addImage("castle_back", "image/gameScene/camp/castle/castle_back.bmp", 800, 374, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("dungeon_back", "image/gameScene/camp/dungeon/dungeon_back.bmp", 800, 374, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("city_UI", "image/gameScene/camp/cityUI.bmp", 800, 226, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_hall", "image/gameScene/camp/castle/hall.bmp", 864, 386, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_hall_ani", "image/gameScene/camp/castle/hall_ani.bmp", 1944, 772, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_fort", "image/gameScene/camp/castle/fort.bmp", 966, 420, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_barrack", "image/gameScene/camp/castle/barrack.bmp", 128, 222, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_archer", "image/gameScene/camp/castle/archer_barrack.bmp", 226, 142, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_tower", "image/gameScene/camp/castle/tower.bmp", 200, 572, 2, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_sword", "image/gameScene/camp/castle/sword.bmp", 286, 160, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_abbey", "image/gameScene/camp/castle/abbey.bmp", 276, 174, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_ground", "image/gameScene/camp/castle/ground.bmp", 602, 216, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_ground_ani", "image/gameScene/camp/castle/ground_ani.bmp", 2709, 216, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_door", "image/gameScene/camp/castle/door.bmp", 572, 232, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_waterfall", "image/gameScene/camp/castle/waterfall.bmp", 240, 38, 10, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_stable", "image/gameScene/camp/castle/stable.bmp", 120, 116, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_market", "image/gameScene/camp/castle/market.bmp", 291, 220, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_storage", "image/gameScene/camp/castle/storage.bmp", 42, 150, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_guild", "image/gameScene/camp/castle/guild.bmp", 384, 386, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_guild_ani", "image/gameScene/camp/castle/guild_ani.bmp", 960, 386, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_pub", "image/gameScene/camp/castle/pub.bmp", 210, 352, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("castle_forge", "image/gameScene/camp/castle/forge.bmp", 127, 238, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("castle_RGB", "image/gameScene/camp/castle/castle_RGB.bmp", 800, 374, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hall_color", "image/gameScene/camp/window/hall_color.bmp", 152, 72, 1, 4, true, RGB(255, 0, 255));

	}

	//==== window
	{
		IMAGEMANAGER->addImage("build_impossible", "image/gameScene/camp/window/build_impossible.bmp", 64, 30, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("window_build", "image/gameScene/camp/window/window_build.bmp", 403, 528, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("window_build_shadow", "image/gameScene/camp/window/window_build_shadow.bmp", 403, 528, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("window_build_shadow")->AlphaInit();
		IMAGEMANAGER->addImage("window_recruit", "image/gameScene/camp/window/window_recruit.bmp", 493, 404, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("window_recruit_shadow", "image/gameScene/camp/window/window_recruit_shadow.bmp", 493, 404, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("window_recruit_shadow")->AlphaInit();
		IMAGEMANAGER->addImage("window_3x2_hall", "image/gameScene/camp/window/window_3x2_hall.bmp", 800, 600, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("window_4x3_hall", "image/gameScene/camp/window/window_4x3_hall.bmp", 800, 600, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("icon_resources", "image/gameScene/camp/window/resources.bmp", 224, 32, 7, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("window_castle_fort", "image/gameScene/camp/window/window_castle_fort.bmp", 800, 600, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("castle_fort_back", "image/gameScene/camp/window/castle_fort_back.bmp", 102, 140, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("window_castle_hall", "image/gameScene/camp/window/window_castle_hall.bmp", 800, 600, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_academy", "image/gameScene/camp/dungeon/hall_academy.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_arti", "image/gameScene/camp/dungeon/hall_arti.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_cloud", "image/gameScene/camp/dungeon/hall_cloud.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_drag1", "image/gameScene/camp/dungeon/hall_drag1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_drag2", "image/gameScene/camp/dungeon/hall_drag2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_farm1", "image/gameScene/camp/dungeon/hall_farm1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_farm2", "image/gameScene/camp/dungeon/hall_farm2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_farm3", "image/gameScene/camp/dungeon/hall_farm3.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_forge", "image/gameScene/camp/dungeon/hall_forge.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_fort1", "image/gameScene/camp/dungeon/hall_fort1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_fort2", "image/gameScene/camp/dungeon/hall_fort2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_fort3", "image/gameScene/camp/dungeon/hall_fort3.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_guild1", "image/gameScene/camp/dungeon/hall_guild1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_guild2", "image/gameScene/camp/dungeon/hall_guild2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_guild3", "image/gameScene/camp/dungeon/hall_guild3.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_guild4", "image/gameScene/camp/dungeon/hall_guild4.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_guild5", "image/gameScene/camp/dungeon/hall_guild5.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_hall1", "image/gameScene/camp/dungeon/hall_hall1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_hall2", "image/gameScene/camp/dungeon/hall_hall2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_hall3", "image/gameScene/camp/dungeon/hall_hall3.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_hall4", "image/gameScene/camp/dungeon/hall_hall4.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_mant1", "image/gameScene/camp/dungeon/hall_mant1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_mant2", "image/gameScene/camp/dungeon/hall_mant2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_market1", "image/gameScene/camp/dungeon/hall_market1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_market2", "image/gameScene/camp/dungeon/hall_market2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_maze1", "image/gameScene/camp/dungeon/hall_maze1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_maze2", "image/gameScene/camp/dungeon/hall_maze2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_nest1", "image/gameScene/camp/dungeon/hall_nest1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_nest2", "image/gameScene/camp/dungeon/hall_nest2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_pillar1", "image/gameScene/camp/dungeon/hall_pillar1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_pillar2", "image/gameScene/camp/dungeon/hall_pillar2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_port", "image/gameScene/camp/dungeon/hall_port.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_pub", "image/gameScene/camp/dungeon/hall_pub.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_temple1", "image/gameScene/camp/dungeon/hall_temple1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Dhall_temple2", "image/gameScene/camp/dungeon/hall_temple2.bmp", 150, 70, true, RGB(255, 0, 255));
		
		IMAGEMANAGER->addImage("Chall_archer1", "image/gameScene/camp/castle/hall_archer1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_archer2", "image/gameScene/camp/castle/hall_archer2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_caval1", "image/gameScene/camp/castle/hall_caval1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_caval2", "image/gameScene/camp/castle/hall_caval2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_cru1", "image/gameScene/camp/castle/hall_cru1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_cru2", "image/gameScene/camp/castle/hall_cru2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_abbey1", "image/gameScene/camp/castle/hall_abbey1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_abbey2", "image/gameScene/camp/castle/hall_abbey2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_dock", "image/gameScene/camp/castle/hall_dock.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_door1", "image/gameScene/camp/castle/hall_door1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_door2", "image/gameScene/camp/castle/hall_door2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_forge", "image/gameScene/camp/castle/hall_forge.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_guild1", "image/gameScene/camp/castle/hall_guild1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_guild2", "image/gameScene/camp/castle/hall_guild2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_guild3", "image/gameScene/camp/castle/hall_guild3.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_guild4", "image/gameScene/camp/castle/hall_guild4.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_hall1", "image/gameScene/camp/castle/hall_hall1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_hall2", "image/gameScene/camp/castle/hall_hall2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_hall3", "image/gameScene/camp/castle/hall_hall3.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_hall4", "image/gameScene/camp/castle/hall_hall4.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_market1", "image/gameScene/camp/castle/hall_market1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_market2", "image/gameScene/camp/castle/hall_market2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_pike1", "image/gameScene/camp/castle/hall_pike1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_pike2", "image/gameScene/camp/castle/hall_pike2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_pub1", "image/gameScene/camp/castle/hall_pub1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_pub2", "image/gameScene/camp/castle/hall_pub2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_stable", "image/gameScene/camp/castle/hall_stable.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_tower1", "image/gameScene/camp/castle/hall_tower1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_tower2", "image/gameScene/camp/castle/hall_tower2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_tower3", "image/gameScene/camp/castle/hall_tower3.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_tower4", "image/gameScene/camp/castle/hall_tower4.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_fort1", "image/gameScene/camp/castle/hall_fort1.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_fort2", "image/gameScene/camp/castle/hall_fort2.bmp", 150, 70, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Chall_fort3", "image/gameScene/camp/castle/hall_fort3.bmp", 150, 70, true, RGB(255, 0, 255));
		
		
		IMAGEMANAGER->addFrameImage("dungeon_academy", "image/gameScene/camp/dungeon/academy.bmp", 134, 152, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_cloud", "image/gameScene/camp/dungeon/cloud_test.bmp", 1440, 136, 10, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_draCave", "image/gameScene/camp/dungeon/draCave.bmp", 500, 180, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_draCave_ani", "image/gameScene/camp/dungeon/draCave_ani.bmp", 2250, 180, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_farm", "image/gameScene/camp/dungeon/farm.bmp", 1184, 592, 8, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_forge", "image/gameScene/camp/dungeon/forge.bmp", 88, 188, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_fort", "image/gameScene/camp/dungeon/fort.bmp", 594, 488, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_guild", "image/gameScene/camp/dungeon/guild.bmp", 440, 368, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_hall", "image/gameScene/camp/dungeon/hall.bmp", 712, 188, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_manCave", "image/gameScene/camp/dungeon/manCave.bmp", 316, 176, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_market", "image/gameScene/camp/dungeon/market.bmp", 190, 112, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_maze", "image/gameScene/camp/dungeon/maze.bmp", 256, 148, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_nest", "image/gameScene/camp/dungeon/nest.bmp", 160, 176, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_pillar", "image/gameScene/camp/dungeon/pillar.bmp", 1020, 472, 10, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_portal", "image/gameScene/camp/dungeon/portal.bmp", 1000, 200, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_pub", "image/gameScene/camp/dungeon/pub.bmp", 74, 132, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_storage", "image/gameScene/camp/dungeon/storage.bmp", 70, 68, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_temple", "image/gameScene/camp/dungeon/temple.bmp", 208, 168, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("dungeon_artifact", "image/gameScene/camp/dungeon/artifact.bmp", 54, 160, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("dungeon_RGB", "image/gameScene/camp/dungeon/dungeon_RGB.bmp", 800, 374, true, RGB(255, 0, 255));
		
		//==== window
		IMAGEMANAGER->addImage("window_dungeon_fort", "image/gameScene/camp/window/window_dungeon_fort.bmp", 800, 600, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("dungeon_fort_back", "image/gameScene/camp/window/dungeon_fort_back.bmp", 102, 140, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("window_dungeon_hall", "image/gameScene/camp/window/window_dungeon_hall.bmp", 800, 600, true, RGB(255, 0, 255));
		
	}



	//==============================  U  I =============================
	
	IMAGEMANAGER->addImage("window_heroinfo", "image/gameScene/ui/window_heroinfo.bmp", 680, 592, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("window_heroinfo_shadow", "image/gameScene/ui/window_heroinfo_shadow.bmp", 680, 592, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("window_heroinfo_shadow")->AlphaInit();
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
	IMAGEMANAGER->addImage("select_hero", "image/gameScene/ui/select_hero.bmp", 48, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("select_creature", "image/gameScene/ui/select_creature.bmp", 58, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("window_creatureinfo", "image/gameScene/ui/window_creatureinfo.bmp", 306, 318, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("window_creatureinfo_shadow", "image/gameScene/ui/window_creatureinfo_shadow.bmp", 306, 318, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("window_creatureinfo_shadow")->AlphaInit();
	IMAGEMANAGER->addFrameImage("flag_large", "image/gameScene/ui/flag_large.bmp", 116, 64,2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("recruit_bar", "image/gameScene/camp/window/recruitBar.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("recruit_right", "image/gameScene/camp/window/recruitRight.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("recruit_left", "image/gameScene/camp/window/recruitLeft.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("recruit_confirm", "image/gameScene/camp/window/recruitConfirm.bmp", 128, 32, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("recruit_cancel", "image/gameScene/camp/window/recruitCancel.bmp", 128, 32, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("recruit_max", "image/gameScene/camp/window/recruitmax.bmp", 128, 32, 1, 2, true, RGB(255, 0, 255));


	//============================== U N I T =============================
	IMAGEMANAGER->addFrameImage("creature_portrait", "image/gameScene/hero/creature/portrait.bmp", 406, 256, 7, 4, true, RGB(255, 0, 255));


	//========== pikeman
	{
		IMAGEMANAGER->addFrameImage("pikeman_down", "image/Castle Creature/11_pikeman/pikeman_attack_down.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_down_shadow", "image/Castle Creature/11_pikeman/pikeman_attack_down_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_up", "image/Castle Creature/11_pikeman/pikeman_attack_up.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_up_shadow", "image/Castle Creature/11_pikeman/pikeman_attack_up_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_front", "image/Castle Creature/11_pikeman/pikeman_attack_front.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_front_shadow", "image/Castle Creature/11_pikeman/pikeman_attack_front_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_damaged", "image/Castle Creature/11_pikeman/pikeman_damaged.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_damaged_shadow", "image/Castle Creature/11_pikeman/pikeman_damaged_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_dead", "image/Castle Creature/11_pikeman/pikeman_dead.bmp", 700, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_dead_shadow", "image/Castle Creature/11_pikeman/pikeman_dead_shadow.bmp", 700, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_idle", "image/Castle Creature/11_pikeman/pikeman_idle.bmp", 140, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_idle_shadow", "image/Castle Creature/11_pikeman/pikeman_idle_shadow.bmp", 140, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_move", "image/Castle Creature/11_pikeman/pikeman_move.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_move_shadow", "image/Castle Creature/11_pikeman/pikeman_move_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_select", "image/Castle Creature/11_pikeman/pikeman_select.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_select_shadow", "image/Castle Creature/11_pikeman/pikeman_select_shadow.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_switch", "image/Castle Creature/11_pikeman/pikeman_switch.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("pikeman_switch_shadow", "image/Castle Creature/11_pikeman/pikeman_switch_shadow.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("pikeman_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("pikeman_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("pikeman_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("pikeman_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("pikeman_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("pikeman_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("pikeman_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("pikeman_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("pikeman_select_shadow")->AlphaInit();

	}

	//========== halberdier
	{
		IMAGEMANAGER->addFrameImage("halberdier_down", "image/Castle Creature/12_halberdier/halberdier_attack_down.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_down_shadow", "image/Castle Creature/12_halberdier/halberdier_attack_down_shadow.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_up", "image/Castle Creature/12_halberdier/halberdier_attack_up.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_up_shadow", "image/Castle Creature/12_halberdier/halberdier_attack_up_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_front", "image/Castle Creature/12_halberdier/halberdier_attack_front.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_front_shadow", "image/Castle Creature/12_halberdier/halberdier_attack_front_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_damaged", "image/Castle Creature/12_halberdier/halberdier_damaged.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_damaged_shadow", "image/Castle Creature/12_halberdier/halberdier_damaged_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_dead", "image/Castle Creature/12_halberdier/halberdier_dead.bmp", 420, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_dead_shadow", "image/Castle Creature/12_halberdier/halberdier_dead_shadow.bmp", 420, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_idle", "image/Castle Creature/12_halberdier/halberdier_idle.bmp", 140, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_idle_shadow", "image/Castle Creature/12_halberdier/halberdier_idle_shadow.bmp", 140, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_move", "image/Castle Creature/12_halberdier/halberdier_move.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_move_shadow", "image/Castle Creature/12_halberdier/halberdier_move_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_select", "image/Castle Creature/12_halberdier/halberdier_select.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_select_shadow", "image/Castle Creature/12_halberdier/halberdier_select_shadow.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_switch", "image/Castle Creature/12_halberdier/halberdier_switch.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("halberdier_switch_shadow", "image/Castle Creature/12_halberdier/halberdier_switch_shadow.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("halberdier_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("halberdier_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("halberdier_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("halberdier_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("halberdier_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("halberdier_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("halberdier_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("halberdier_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("halberdier_select_shadow")->AlphaInit();

	}

	//========== archer
	{
		IMAGEMANAGER->addFrameImage("archer_melee", "image/Castle Creature/21_archer/archer_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_melee_shadow", "image/Castle Creature/21_archer/archer_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_range", "image/Castle Creature/21_archer/archer_attack_range.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_range_shadow", "image/Castle Creature/21_archer/archer_attack_range.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_damaged", "image/Castle Creature/21_archer/archer_damaged.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_damaged_shadow", "image/Castle Creature/21_archer/archer_damaged_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_dead", "image/Castle Creature/21_archer/archer_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_dead_shadow", "image/Castle Creature/21_archer/archer_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_idle", "image/Castle Creature/21_archer/archer_idle.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_idle_shadow", "image/Castle Creature/21_archer/archer_idle_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_move", "image/Castle Creature/21_archer/archer_move.bmp", 1440, 240, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_move_shadow", "image/Castle Creature/21_archer/archer_move_shadow.bmp", 1440, 240, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_select", "image/Castle Creature/21_archer/archer_select.bmp", 960, 240, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_select_shadow", "image/Castle Creature/21_archer/archer_select_shadow.bmp", 960, 240, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_switch", "image/Castle Creature/21_archer/archer_switch.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_switch_shadow", "image/Castle Creature/21_archer/archer_switch_shadow.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("archer_melee_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("archer_range_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("archer_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("archer_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("archer_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("archer_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("archer_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("archer_select_shadow")->AlphaInit();

	}

	//========== mask
	{
		IMAGEMANAGER->addFrameImage("mask_melee", "image/Castle Creature/22_mask/mask_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_melee_shadow", "image/Castle Creature/22_mask/mask_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_range", "image/Castle Creature/22_mask/mask_attack_range.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_range_shadow", "image/Castle Creature/22_mask/mask_attack_range.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_damaged", "image/Castle Creature/22_mask/mask_damaged.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_damaged_shadow", "image/Castle Creature/22_mask/mask_damaged_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_dead", "image/Castle Creature/22_mask/mask_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_dead_shadow", "image/Castle Creature/22_mask/mask_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_idle", "image/Castle Creature/22_mask/mask_idle.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_idle_shadow", "image/Castle Creature/22_mask/mask_idle_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_move", "image/Castle Creature/22_mask/mask_move.bmp", 1440, 240, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_move_shadow", "image/Castle Creature/22_mask/mask_move_shadow.bmp", 1440, 240, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_select", "image/Castle Creature/22_mask/mask_select.bmp", 960, 240, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_select_shadow", "image/Castle Creature/22_mask/mask_select_shadow.bmp", 960, 240, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_switch", "image/Castle Creature/22_mask/mask_switch.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("mask_switch_shadow", "image/Castle Creature/22_mask/mask_switch_shadow.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("mask_melee_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("mask_range_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("mask_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("mask_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("mask_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("mask_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("mask_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("mask_select_shadow")->AlphaInit();

	}

	//========== griffin
	{
		IMAGEMANAGER->addFrameImage("griffin_down", "image/Castle Creature/31_griffin/griffin_attack_down.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_down_shadow", "image/Castle Creature/31_griffin/griffin_attack_down_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_up", "image/Castle Creature/31_griffin/griffin_attack_up.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_up_shadow", "image/Castle Creature/31_griffin/griffin_attack_up_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_front", "image/Castle Creature/31_griffin/griffin_attack_front.bmp", 1400, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_front_shadow", "image/Castle Creature/31_griffin/griffin_attack_front_shadow.bmp", 1400, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_damaged", "image/Castle Creature/31_griffin/griffin_damaged.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_damaged_shadow", "image/Castle Creature/31_griffin/griffin_damaged_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_dead", "image/Castle Creature/31_griffin/griffin_dead.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_dead_shadow", "image/Castle Creature/31_griffin/griffin_dead_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_idle", "image/Castle Creature/31_griffin/griffin_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_idle_shadow", "image/Castle Creature/31_griffin/griffin_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_move", "image/Castle Creature/31_griffin/griffin_move.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_move_shadow", "image/Castle Creature/31_griffin/griffin_move_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_select", "image/Castle Creature/31_griffin/griffin_select.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_select_shadow", "image/Castle Creature/31_griffin/griffin_select_shadow.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_switch", "image/Castle Creature/31_griffin/griffin_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("griffin_switch_shadow", "image/Castle Creature/31_griffin/griffin_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("griffin_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("griffin_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("griffin_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("griffin_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("griffin_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("griffin_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("griffin_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("griffin_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("griffin_select_shadow")->AlphaInit();

	}

	//========== royal griffin
	{
		IMAGEMANAGER->addFrameImage("royal_down", "image/Castle Creature/32_royal/royal_attack_down.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_down_shadow", "image/Castle Creature/32_royal/royal_attack_down_shadow.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_up", "image/Castle Creature/32_royal/royal_attack_up.bmp", 1320, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_up_shadow", "image/Castle Creature/32_royal/royal_attack_up_shadow.bmp", 1320, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_front", "image/Castle Creature/32_royal/royal_attack_front.bmp", 1540, 320, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_front_shadow", "image/Castle Creature/32_royal/royal_attack_front_shadow.bmp", 1540, 320, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_damaged", "image/Castle Creature/32_royal/royal_damaged.bmp", 1100, 320, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_damaged_shadow", "image/Castle Creature/32_royal/royal_damaged_shadow.bmp", 1100, 320, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_dead", "image/Castle Creature/32_royal/royal_dead.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_dead_shadow", "image/Castle Creature/32_royal/royal_dead_shadow.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_idle", "image/Castle Creature/32_royal/royal_idle.bmp", 220, 320, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_idle_shadow", "image/Castle Creature/32_royal/royal_idle_shadow.bmp", 220, 320, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_move", "image/Castle Creature/32_royal/royal_move.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_move_shadow", "image/Castle Creature/32_royal/royal_move_shadow.bmp", 1760, 320, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_select", "image/Castle Creature/32_royal/royal_select.bmp", 1100, 320, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_select_shadow", "image/Castle Creature/32_royal/royal_select_shadow.bmp", 1100, 320, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_switch", "image/Castle Creature/32_royal/royal_switch.bmp", 440, 320, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("royal_switch_shadow", "image/Castle Creature/32_royal/royal_switch_shadow.bmp", 440, 320, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("royal_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("royal_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("royal_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("royal_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("royal_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("royal_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("royal_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("royal_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("royal_select_shadow")->AlphaInit();

	}

	//========== swordman
	{
		IMAGEMANAGER->addFrameImage("sword_down", "image/Castle Creature/41_sword/sword_attack_down.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_down_shadow", "image/Castle Creature/41_sword/sword_attack_down_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_up", "image/Castle Creature/41_sword/sword_attack_up.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_up_shadow", "image/Castle Creature/41_sword/sword_attack_up_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_front", "image/Castle Creature/41_sword/sword_attack_front.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_front_shadow", "image/Castle Creature/41_sword/sword_attack_front_shadow.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_damaged", "image/Castle Creature/41_sword/sword_damaged.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_damaged_shadow", "image/Castle Creature/41_sword/sword_damaged_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_dead", "image/Castle Creature/41_sword/sword_dead.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_dead_shadow", "image/Castle Creature/41_sword/sword_dead_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_idle", "image/Castle Creature/41_sword/sword_idle.bmp", 160, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_idle_shadow", "image/Castle Creature/41_sword/sword_idle_shadow.bmp", 160, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_move", "image/Castle Creature/41_sword/sword_move.bmp", 1920, 280, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_move_shadow", "image/Castle Creature/41_sword/sword_move_shadow.bmp", 1920, 280, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_select", "image/Castle Creature/41_sword/sword_select.bmp", 640, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_select_shadow", "image/Castle Creature/41_sword/sword_select_shadow.bmp", 640, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_switch", "image/Castle Creature/41_sword/sword_switch.bmp", 320, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("sword_switch_shadow", "image/Castle Creature/41_sword/sword_switch_shadow.bmp", 320, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("sword_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("sword_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("sword_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("sword_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("sword_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("sword_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("sword_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("sword_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("sword_select_shadow")->AlphaInit();
	}

	//========== crusader
	{
		IMAGEMANAGER->addFrameImage("cru_down", "image/Castle Creature/42_cru/cru_attack_down.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_down_shadow", "image/Castle Creature/42_cru/cru_attack_down_shadow.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_up", "image/Castle Creature/42_cru/cru_attack_up.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_up_shadow", "image/Castle Creature/42_cru/cru_attack_up_shadow.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_front", "image/Castle Creature/42_cru/cru_attack_front.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_front_shadow", "image/Castle Creature/42_cru/cru_attack_front_shadow.bmp", 1120, 280, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_damaged", "image/Castle Creature/42_cru/cru_damaged.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_damaged_shadow", "image/Castle Creature/42_cru/cru_damaged_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_dead", "image/Castle Creature/42_cru/cru_dead.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_dead_shadow", "image/Castle Creature/42_cru/cru_dead_shadow.bmp", 960, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_idle", "image/Castle Creature/42_cru/cru_idle.bmp", 160, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_idle_shadow", "image/Castle Creature/42_cru/cru_idle_shadow.bmp", 160, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_move", "image/Castle Creature/42_cru/cru_move.bmp", 1920, 280, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_move_shadow", "image/Castle Creature/42_cru/cru_move_shadow.bmp", 1920, 280, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_select", "image/Castle Creature/42_cru/cru_select.bmp", 480, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_select_shadow", "image/Castle Creature/42_cru/cru_select_shadow.bmp", 480, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_switch", "image/Castle Creature/42_cru/cru_switch.bmp", 320, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cru_switch_shadow", "image/Castle Creature/42_cru/cru_switch_shadow.bmp", 320, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("cru_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cru_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cru_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cru_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cru_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cru_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cru_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cru_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cru_select_shadow")->AlphaInit();

	}

	//========== monk
	{
		IMAGEMANAGER->addFrameImage("monk_melee", "image/Castle Creature/51_monk/monk_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_melee_shadow", "image/Castle Creature/51_monk/monk_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_range", "image/Castle Creature/51_monk/monk_attack_range.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_range_shadow", "image/Castle Creature/51_monk/monk_attack_range.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_damaged", "image/Castle Creature/51_monk/monk_damaged.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_damaged_shadow", "image/Castle Creature/51_monk/monk_damaged_shadow.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_dead", "image/Castle Creature/51_monk/monk_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_dead_shadow", "image/Castle Creature/51_monk/monk_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_idle", "image/Castle Creature/51_monk/monk_idle.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_idle_shadow", "image/Castle Creature/51_monk/monk_idle_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_move", "image/Castle Creature/51_monk/monk_move.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_move_shadow", "image/Castle Creature/51_monk/monk_move_shadow.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_select", "image/Castle Creature/51_monk/monk_select.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_select_shadow", "image/Castle Creature/51_monk/monk_select_shadow.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_switch", "image/Castle Creature/51_monk/monk_switch.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("monk_switch_shadow", "image/Castle Creature/51_monk/monk_switch_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("monk_melee_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("monk_range_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("monk_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("monk_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("monk_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("monk_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("monk_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("monk_select_shadow")->AlphaInit();

	}

	//========== zealot
	{
		IMAGEMANAGER->addFrameImage("zealot_melee", "image/Castle Creature/52_zealot/zealot_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_melee_shadow", "image/Castle Creature/52_zealot/zealot_attack_melee.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_range", "image/Castle Creature/52_zealot/zealot_attack_range.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_range_shadow", "image/Castle Creature/52_zealot/zealot_attack_range.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_damaged", "image/Castle Creature/52_zealot/zealot_damaged.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_damaged_shadow", "image/Castle Creature/52_zealot/zealot_damaged_shadow.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_dead", "image/Castle Creature/52_zealot/zealot_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_dead_shadow", "image/Castle Creature/52_zealot/zealot_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_idle", "image/Castle Creature/52_zealot/zealot_idle.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_idle_shadow", "image/Castle Creature/52_zealot/zealot_idle_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_move", "image/Castle Creature/52_zealot/zealot_move.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_move_shadow", "image/Castle Creature/52_zealot/zealot_move_shadow.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_select", "image/Castle Creature/52_zealot/zealot_select.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_select_shadow", "image/Castle Creature/52_zealot/zealot_select_shadow.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_switch", "image/Castle Creature/52_zealot/zealot_switch.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("zealot_switch_shadow", "image/Castle Creature/52_zealot/zealot_switch_shadow.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("zealot_melee_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("zealot_range_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("zealot_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("zealot_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("zealot_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("zealot_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("zealot_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("zealot_select_shadow")->AlphaInit();

	}

	//========== cavalier
	{
		IMAGEMANAGER->addFrameImage("cavalier_down", "image/Castle Creature/61_cavalier/cavalier_attack_down.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_down_shadow", "image/Castle Creature/61_cavalier/cavalier_attack_down_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_up", "image/Castle Creature/61_cavalier/cavalier_attack_up.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_up_shadow", "image/Castle Creature/61_cavalier/cavalier_attack_up_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_front", "image/Castle Creature/61_cavalier/cavalier_attack_front.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_front_shadow", "image/Castle Creature/61_cavalier/cavalier_attack_front_shadow.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_damaged", "image/Castle Creature/61_cavalier/cavalier_damaged.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_damaged_shadow", "image/Castle Creature/61_cavalier/cavalier_damaged_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_dead", "image/Castle Creature/61_cavalier/cavalier_dead.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_dead_shadow", "image/Castle Creature/61_cavalier/cavalier_dead_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_idle", "image/Castle Creature/61_cavalier/cavalier_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_idle_shadow", "image/Castle Creature/61_cavalier/cavalier_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_move", "image/Castle Creature/61_cavalier/cavalier_move.bmp", 3200, 280, 16, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_move_shadow", "image/Castle Creature/61_cavalier/cavalier_move_shadow.bmp", 3200, 280, 16, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_select", "image/Castle Creature/61_cavalier/cavalier_select.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_select_shadow", "image/Castle Creature/61_cavalier/cavalier_select_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_switch", "image/Castle Creature/61_cavalier/cavalier_switch.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("cavalier_switch_shadow", "image/Castle Creature/61_cavalier/cavalier_switch_shadow.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("cavalier_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cavalier_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cavalier_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cavalier_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cavalier_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cavalier_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cavalier_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cavalier_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("cavalier_select_shadow")->AlphaInit();

	}

	//========== champion
	{
		IMAGEMANAGER->addFrameImage("champion_down", "image/Castle Creature/62_champion/champion_attack_down.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_down_shadow", "image/Castle Creature/62_champion/champion_attack_down_shadow.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_up", "image/Castle Creature/62_champion/champion_attack_up.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_up_shadow", "image/Castle Creature/62_champion/champion_attack_up_shadow.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_front", "image/Castle Creature/62_champion/champion_attack_front.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_front_shadow", "image/Castle Creature/62_champion/champion_attack_front_shadow.bmp", 1800, 280, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_damaged", "image/Castle Creature/62_champion/champion_damaged.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_damaged_shadow", "image/Castle Creature/62_champion/champion_damaged_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_dead", "image/Castle Creature/62_champion/champion_dead.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_dead_shadow", "image/Castle Creature/62_champion/champion_dead_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_idle", "image/Castle Creature/62_champion/champion_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_idle_shadow", "image/Castle Creature/62_champion/champion_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_move", "image/Castle Creature/62_champion/champion_move.bmp", 3400, 280, 17, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_move_shadow", "image/Castle Creature/62_champion/champion_move_shadow.bmp", 3400, 280, 17, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_select", "image/Castle Creature/62_champion/champion_select.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_select_shadow", "image/Castle Creature/62_champion/champion_select_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_switch", "image/Castle Creature/62_champion/champion_switch.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("champion_switch_shadow", "image/Castle Creature/62_champion/champion_switch_shadow.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("champion_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("champion_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("champion_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("champion_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("champion_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("champion_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("champion_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("champion_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("champion_select_shadow")->AlphaInit();

	}

	//========== angel
	{
		IMAGEMANAGER->addFrameImage("angel_down", "image/Castle Creature/71_angel/angel_attack_down.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_down_shadow", "image/Castle Creature/71_angel/angel_attack_down_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_up", "image/Castle Creature/71_angel/angel_attack_up.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_up_shadow", "image/Castle Creature/71_angel/angel_attack_up_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_front", "image/Castle Creature/71_angel/angel_attack_front.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_front_shadow", "image/Castle Creature/71_angel/angel_attack_front_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_damaged", "image/Castle Creature/71_angel/angel_damaged.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_damaged_shadow", "image/Castle Creature/71_angel/angel_damaged_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_dead", "image/Castle Creature/71_angel/angel_dead.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_dead_shadow", "image/Castle Creature/71_angel/angel_dead_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_idle", "image/Castle Creature/71_angel/angel_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_idle_shadow", "image/Castle Creature/71_angel/angel_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_move", "image/Castle Creature/71_angel/angel_move.bmp", 2200, 280, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_move_shadow", "image/Castle Creature/71_angel/angel_move_shadow.bmp", 2200, 280, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_select", "image/Castle Creature/71_angel/angel_select.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_select_shadow", "image/Castle Creature/71_angel/angel_select_shadow.bmp", 600, 280, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_switch", "image/Castle Creature/71_angel/angel_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("angel_switch_shadow", "image/Castle Creature/71_angel/angel_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("angel_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("angel_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("angel_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("angel_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("angel_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("angel_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("angel_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("angel_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("angel_select_shadow")->AlphaInit();

	}

	//========== arc angel
	{
		IMAGEMANAGER->addFrameImage("arc_down", "image/Castle Creature/72_arc/arc_attack_down.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_down_shadow", "image/Castle Creature/72_arc/arc_attack_down_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_up", "image/Castle Creature/72_arc/arc_attack_up.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_up_shadow", "image/Castle Creature/72_arc/arc_attack_up_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_front", "image/Castle Creature/72_arc/arc_attack_front.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_front_shadow", "image/Castle Creature/72_arc/arc_attack_front_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_damaged", "image/Castle Creature/72_arc/arc_damaged.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_damaged_shadow", "image/Castle Creature/72_arc/arc_damaged_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_dead", "image/Castle Creature/72_arc/arc_dead.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_dead_shadow", "image/Castle Creature/72_arc/arc_dead_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_idle", "image/Castle Creature/72_arc/arc_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_idle_shadow", "image/Castle Creature/72_arc/arc_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_move", "image/Castle Creature/72_arc/arc_move.bmp", 2400, 280, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_move_shadow", "image/Castle Creature/72_arc/arc_move_shadow.bmp", 2400, 280, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_select", "image/Castle Creature/72_arc/arc_select.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_select_shadow", "image/Castle Creature/72_arc/arc_select_shadow.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_switch", "image/Castle Creature/72_arc/arc_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("arc_switch_shadow", "image/Castle Creature/72_arc/arc_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("arc_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("arc_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("arc_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("arc_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("arc_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("arc_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("arc_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("arc_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("arc_select_shadow")->AlphaInit();

	}


	//========== troglodyte
	{
		IMAGEMANAGER->addFrameImage("troglodyte_down", "image/Dungeon Creature/11_troglodyte/troglodyte_down.bmp",960,320,6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_down_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_down_shadow.bmp",960,320,6 , 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_up", "image/Dungeon Creature/11_troglodyte/troglodyte_up.bmp",800,320, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_up_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_up_shadow.bmp",800,320, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_front", "image/Dungeon Creature/11_troglodyte/troglodyte_front.bmp",960,320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_front_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_front_shadow.bmp",960,320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_damaged", "image/Dungeon Creature/11_troglodyte/troglodyte_damaged.bmp",960,320,6 , 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_damaged_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_damaged_shadow.bmp",960,320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_dead", "image/Dungeon Creature/11_troglodyte/troglodyte_dead.bmp", 800,320,5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_dead_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_dead_shadow.bmp", 800,320,5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_idle", "image/Dungeon Creature/11_troglodyte/troglodyte_idle.bmp",160,320,1 , 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_idle_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_idle_shadow.bmp",160,320, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_move", "image/Dungeon Creature/11_troglodyte/troglodyte_move.bmp",1120,320,7 , 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_move_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_move_shadow.bmp",1120,320,7 , 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_select", "image/Dungeon Creature/11_troglodyte/troglodyte_select.bmp", 960,320,6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_select_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_select_shadow.bmp",960,320,6 , 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_switch", "image/Dungeon Creature/11_troglodyte/troglodyte_switch.bmp", 320,320,2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("troglodyte_switch_shadow", "image/Dungeon Creature/11_troglodyte/troglodyte_switch_shadow.bmp",320,320,2 , 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("troglodyte_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("troglodyte_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("troglodyte_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("troglodyte_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("troglodyte_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("troglodyte_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("troglodyte_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("troglodyte_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("troglodyte_select_shadow")->AlphaInit();

	}


	//infernal troglodyte
	{
		IMAGEMANAGER->addFrameImage("infernal_down", "image/Dungeon Creature/12_infernal/infernal_attack_down.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_down_shadow", "image/Dungeon Creature/12_infernal/infernal_attack_down_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_up", "image/Dungeon Creature/12_infernal/infernal_attack_up.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_up_shadow", "image/Dungeon Creature/12_infernal/infernal_attack_up_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_front", "image/Dungeon Creature/12_infernal/infernal_attack_front.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_front_shadow", "image/Dungeon Creature/12_infernal/infernal_attack_front_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_damaged", "image/Dungeon Creature/12_infernal/infernal_damaged.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_damaged_shadow", "image/Dungeon Creature/12_infernal/infernal_damaged_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_dead", "image/Dungeon Creature/12_infernal/infernal_dead.bmp", 800, 320, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_dead_shadow", "image/Dungeon Creature/12_infernal/infernal_dead_shadow.bmp", 800, 320, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_idle", "image/Dungeon Creature/12_infernal/infernal_idle.bmp", 160, 320, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_idle_shadow", "image/Dungeon Creature/12_infernal/infernal_idle_shadow.bmp", 160, 320, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_move", "image/Dungeon Creature/12_infernal/infernal_move.bmp", 1120, 320, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_move_shadow", "image/Dungeon Creature/12_infernal/infernal_move_shadow.bmp", 1120, 320, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_select", "image/Dungeon Creature/12_infernal/infernal_select.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_select_shadow", "image/Dungeon Creature/12_infernal/infernal_select_shadow.bmp", 960, 320, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_switch", "image/Dungeon Creature/12_infernal/infernal_switch.bmp", 320, 320, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("infernal_switch_shadow", "image/Dungeon Creature/12_infernal/infernal_switch_shadow.bmp", 320, 320, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("infernal_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("infernal_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("infernal_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("infernal_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("infernal_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("infernal_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("infernal_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("infernal_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("infernal_select_shadow")->AlphaInit();

	}

	//========== harpy
	{
		IMAGEMANAGER->addFrameImage("harpy_down", "image/Dungeon Creature/21_harpy/harpy_attack_down.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_down_shadow", "image/Dungeon Creature/21_harpy/harpy_attack_down_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_front", "image/Dungeon Creature/21_harpy/harpy_attack_front.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_front_shadow", "image/Dungeon Creature/21_harpy/harpy_attack_front_shadow.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_up", "image/Dungeon Creature/21_harpy/harpy_attack_up.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_up_shadow", "image/Dungeon Creature/21_harpy/harpy_attack_up_shadow.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_damaged", "image/Dungeon Creature/21_harpy/harpy_damaged.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_damaged_shadow", "image/Dungeon Creature/21_harpy/harpy_damaged_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_dead", "image/Dungeon Creature/21_harpy/harpy_dead.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_dead_shadow", "image/Dungeon Creature/21_harpy/harpy_dead_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_idle", "image/Dungeon Creature/21_harpy/harpy_idle.bmp", 160, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_idle_shadow", "image/Dungeon Creature/21_harpy/harpy_idle_shadow.bmp", 160, 240, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_move", "image/Dungeon Creature/21_harpy/harpy_move.bmp", 2080, 240, 13, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_move_shadow", "image/Dungeon Creature/21_harpy/harpy_move_shadow.bmp", 2080, 240, 13, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_select", "image/Dungeon Creature/21_harpy/harpy_select.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_select_shadow", "image/Dungeon Creature/21_harpy/harpy_select_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_switch", "image/Dungeon Creature/21_harpy/harpy_switch.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("harpy_switch_shadow", "image/Dungeon Creature/21_harpy/harpy_switch_shadow.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("harpy_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("harpy_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("harpy_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("harpy_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("harpy_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("harpy_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("harpy_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("harpy_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("harpy_dead_shadow")->AlphaInit();

	}

	//========== harpy hag
	{
		IMAGEMANAGER->addFrameImage("hag_down", "image/Dungeon Creature/22_hag/hag_attack_down.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_down_shadow", "image/Dungeon Creature/22_hag/hag_attack_down_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_front", "image/Dungeon Creature/22_hag/hag_attack_front.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_front_shadow", "image/Dungeon Creature/22_hag/hag_attack_front_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_up", "image/Dungeon Creature/22_hag/hag_attack_up.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_up_shadow", "image/Dungeon Creature/22_hag/hag_attack_up_shadow.bmp", 1600, 240, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_damaged", "image/Dungeon Creature/22_hag/hag_damaged.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_damaged_shadow", "image/Dungeon Creature/22_hag/hag_damaged_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_dead", "image/Dungeon Creature/22_hag/hag_dead.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_dead_shadow", "image/Dungeon Creature/22_hag/hag_dead_shadow.bmp", 1120, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_idle", "image/Dungeon Creature/22_hag/hag_idle.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_idle_shadow", "image/Dungeon Creature/22_hag/hag_idle_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_move", "image/Dungeon Creature/22_hag/hag_move.bmp", 2080, 240, 13, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_move_shadow", "image/Dungeon Creature/22_hag/hag_move_shadow.bmp", 2080, 240, 13, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_select", "image/Dungeon Creature/22_hag/hag_select.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_select_shadow", "image/Dungeon Creature/22_hag/hag_select_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_switch", "image/Dungeon Creature/22_hag/hag_switch.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("hag_switch_shadow", "image/Dungeon Creature/22_hag/hag_switch_shadow.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("hag_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hag_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hag_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hag_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hag_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hag_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hag_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hag_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("hag_dead_shadow")->AlphaInit();

	}

	//========== beholder
	{
		IMAGEMANAGER->addFrameImage("beholder_down", "image/Dungeon Creature/31_beholder/beholder_attack_down.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_down_shadow", "image/Dungeon Creature/31_beholder/beholder_attack_down_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_front", "image/Dungeon Creature/31_beholder/beholder_attack_front.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_front_shadow", "image/Dungeon Creature/31_beholder/beholder_attack_front_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_up", "image/Dungeon Creature/31_beholder/beholder_attack_up.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_up_shadow", "image/Dungeon Creature/31_beholder/beholder_attack_up_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_damaged", "image/Dungeon Creature/31_beholder/beholder_damaged.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_damaged_shadow", "image/Dungeon Creature/31_beholder/beholder_damaged_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_dead", "image/Dungeon Creature/31_beholder/beholder_dead.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_dead_shadow", "image/Dungeon Creature/31_beholder/beholder_dead_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_idle", "image/Dungeon Creature/31_beholder/beholder_idle.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_idle_shadow", "image/Dungeon Creature/31_beholder/beholder_idle_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_move", "image/Dungeon Creature/31_beholder/beholder_move.bmp", 2560, 240, 16, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_move_shadow", "image/Dungeon Creature/31_beholder/beholder_move_shadow.bmp", 2560, 240, 16, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_select", "image/Dungeon Creature/31_beholder/beholder_select.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_select_shadow", "image/Dungeon Creature/31_beholder/beholder_select_shadow.bmp", 480, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_range", "image/Dungeon Creature/31_beholder/beholder_attack_range.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("beholder_range_shadow", "image/Dungeon Creature/31_beholder/beholder_attack_range_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("beholder_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("beholder_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("beholder_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("beholder_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("beholder_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("beholder_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("beholder_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("beholder_range_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("beholder_dead_shadow")->AlphaInit();

	}

	//========== evil eye
	{
		IMAGEMANAGER->addFrameImage("evil_down", "image/Dungeon Creature/32_evil/evil_attack_down.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_down_shadow", "image/Dungeon Creature/32_evil/evil_attack_down_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_front", "image/Dungeon Creature/32_evil/evil_attack_front.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_front_shadow", "image/Dungeon Creature/32_evil/evil_attack_front_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_up", "image/Dungeon Creature/32_evil/evil_attack_up.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_up_shadow", "image/Dungeon Creature/32_evil/evil_attack_up_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_damaged", "image/Dungeon Creature/32_evil/evil_damaged.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_damaged_shadow", "image/Dungeon Creature/32_evil/evil_damaged_shadow.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_dead", "image/Dungeon Creature/32_evil/evil_dead.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_dead_shadow", "image/Dungeon Creature/32_evil/evil_dead_shadow.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_idle", "image/Dungeon Creature/32_evil/evil_idle.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_idle_shadow", "image/Dungeon Creature/32_evil/evil_idle_shadow.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_move", "image/Dungeon Creature/32_evil/evil_move.bmp", 2520, 240, 14, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_move_shadow", "image/Dungeon Creature/32_evil/evil_move_shadow.bmp", 2520, 240, 14, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_select", "image/Dungeon Creature/32_evil/evil_select.bmp", 540, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_select_shadow", "image/Dungeon Creature/32_evil/evil_select_shadow.bmp", 540, 240, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_range", "image/Dungeon Creature/32_evil/evil_attack_range.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("evil_range_shadow", "image/Dungeon Creature/32_evil/evil_attack_range_shadow.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("evil_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("evil_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("evil_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("evil_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("evil_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("evil_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("evil_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("evil_range_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("evil_dead_shadow")->AlphaInit();

	}

	//========== medusa
	{
		IMAGEMANAGER->addFrameImage("medusa_melee", "image/Dungeon Creature/41_medusa/medusa_attack_melee.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_melee_shadow", "image/Dungeon Creature/41_medusa/medusa_attack_melee_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_damaged", "image/Dungeon Creature/41_medusa/medusa_damaged.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_damaged_shadow", "image/Dungeon Creature/41_medusa/medusa_damaged_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_dead", "image/Dungeon Creature/41_medusa/medusa_dead.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_dead_shadow", "image/Dungeon Creature/41_medusa/medusa_dead_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_idle", "image/Dungeon Creature/41_medusa/medusa_idle.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_idle_shadow", "image/Dungeon Creature/41_medusa/medusa_idle_shadow.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_move", "image/Dungeon Creature/41_medusa/medusa_move.bmp", 1920, 240, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_move_shadow", "image/Dungeon Creature/41_medusa/medusa_move_shadow.bmp", 1920, 240, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_select", "image/Dungeon Creature/41_medusa/medusa_select.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_select_shadow", "image/Dungeon Creature/41_medusa/medusa_select_shadow.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_range", "image/Dungeon Creature/41_medusa/medusa_attack_range.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_range_shadow", "image/Dungeon Creature/41_medusa/medusa_attack_range_shadow.bmp", 960, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_switch", "image/Dungeon Creature/41_medusa/medusa_switch.bmp", 320, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("medusa_switch_shadow", "image/Dungeon Creature/41_medusa/medusa_switch_shadow.bmp", 320, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("medusa_melee_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("medusa_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("medusa_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("medusa_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("medusa_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("medusa_range_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("medusa_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("medusa_switch_shadow")->AlphaInit();

	}


	//=========== queen
	{
		IMAGEMANAGER->addFrameImage("queen_melee", "image/Dungeon Creature/42_queen/queen_attack_melee.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_melee_shadow", "image/Dungeon Creature/42_queen/queen_attack_melee_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_damaged", "image/Dungeon Creature/42_queen/queen_damaged.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_damaged_shadow", "image/Dungeon Creature/42_queen/queen_damaged_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_dead", "image/Dungeon Creature/42_queen/queen_dead.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_dead_shadow", "image/Dungeon Creature/42_queen/queen_dead_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_idle", "image/Dungeon Creature/42_queen/queen_idle.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_idle_shadow", "image/Dungeon Creature/42_queen/queen_idle_shadow.bmp", 720, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_move", "image/Dungeon Creature/42_queen/queen_move.bmp", 2160, 240, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_move_shadow", "image/Dungeon Creature/42_queen/queen_move_shadow.bmp", 2160, 240, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_select", "image/Dungeon Creature/42_queen/queen_select.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_select_shadow", "image/Dungeon Creature/42_queen/queen_select_shadow.bmp", 900, 240, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_range", "image/Dungeon Creature/42_queen/queen_attack_range.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_range_shadow", "image/Dungeon Creature/42_queen/queen_attack_range_shadow.bmp", 1080, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_switch", "image/Dungeon Creature/42_queen/queen_switch.bmp", 360, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("queen_switch_shadow", "image/Dungeon Creature/42_queen/queen_switch_shadow.bmp", 360, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("queen_melee_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("queen_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("queen_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("queen_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("queen_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("queen_range_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("queen_dead_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("queen_switch_shadow")->AlphaInit();

	}

	//========== minotarus
	{
		IMAGEMANAGER->addFrameImage("minotaur_down", "image/Dungeon Creature/51_minotaur/minotaur_attack_down.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_down_shadow", "image/Dungeon Creature/51_minotaur/minotaur_attack_down_shadow.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_front", "image/Dungeon Creature/51_minotaur/minotaur_attack_front.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_front_shadow", "image/Dungeon Creature/51_minotaur/minotaur_attack_front_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_up", "image/Dungeon Creature/51_minotaur/minotaur_attack_up.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_up_shadow", "image/Dungeon Creature/51_minotaur/minotaur_attack_up_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_damaged", "image/Dungeon Creature/51_minotaur/minotaur_damaged.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_damaged_shadow", "image/Dungeon Creature/51_minotaur/minotaur_damaged_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_dead", "image/Dungeon Creature/51_minotaur/minotaur_dead.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_dead_shadow", "image/Dungeon Creature/51_minotaur/minotaur_dead_shadow.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_idle", "image/Dungeon Creature/51_minotaur/minotaur_idle.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_idle_shadow", "image/Dungeon Creature/51_minotaur/minotaur_idle_shadow.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_move", "image/Dungeon Creature/51_minotaur/minotaur_move.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_move_shadow", "image/Dungeon Creature/51_minotaur/minotaur_move_shadow.bmp", 840, 240, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_select", "image/Dungeon Creature/51_minotaur/minotaur_select.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_select_shadow", "image/Dungeon Creature/51_minotaur/minotaur_select_shadow.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_switch", "image/Dungeon Creature/51_minotaur/minotaur_switch.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("minotaur_switch_shadow", "image/Dungeon Creature/51_minotaur/minotaur_switch_shadow.bmp", 240, 240, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("minotaur_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("minotaur_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("minotaur_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("minotaur_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("minotaur_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("minotaur_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("minotaur_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("minotaur_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("minotaur_dead_shadow")->AlphaInit();

	}

	//========== king
	{
	IMAGEMANAGER->addFrameImage("king_down", "image/Dungeon Creature/52_king/king_attack_down.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_down_shadow", "image/Dungeon Creature/52_king/king_attack_down_shadow.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_front", "image/Dungeon Creature/52_king/king_attack_front.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_front_shadow", "image/Dungeon Creature/52_king/king_attack_front_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_up", "image/Dungeon Creature/52_king/king_attack_up.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_up_shadow", "image/Dungeon Creature/52_king/king_attack_up_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_damaged", "image/Dungeon Creature/52_king/king_damaged.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_damaged_shadow", "image/Dungeon Creature/52_king/king_damaged_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_dead", "image/Dungeon Creature/52_king/king_dead.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_dead_shadow", "image/Dungeon Creature/52_king/king_dead_shadow.bmp", 840, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_idle", "image/Dungeon Creature/52_king/king_idle.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_idle_shadow", "image/Dungeon Creature/52_king/king_idle_shadow.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_move", "image/Dungeon Creature/52_king/king_move.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_move_shadow", "image/Dungeon Creature/52_king/king_move_shadow.bmp", 980, 280, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_select", "image/Dungeon Creature/52_king/king_select.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_select_shadow", "image/Dungeon Creature/52_king/king_select_shadow.bmp", 560, 280, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_switch", "image/Dungeon Creature/52_king/king_switch.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("king_switch_shadow", "image/Dungeon Creature/52_king/king_switch_shadow.bmp", 280, 280, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("king_down_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("king_up_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("king_front_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("king_damaged_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("king_idle_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("king_move_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("king_select_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("king_switch_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("king_dead_shadow")->AlphaInit();

	}

	//========== manticore
	{
		IMAGEMANAGER->addFrameImage("manticore_down", "image/Dungeon Creature/61_manticore/manticore_attack_down.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_down_shadow", "image/Dungeon Creature/61_manticore/manticore_attack_down_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_front", "image/Dungeon Creature/61_manticore/manticore_attack_front.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_front_shadow", "image/Dungeon Creature/61_manticore/manticore_attack_front_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_up", "image/Dungeon Creature/61_manticore/manticore_attack_up.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_up_shadow", "image/Dungeon Creature/61_manticore/manticore_attack_up_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_damaged", "image/Dungeon Creature/61_manticore/manticore_damaged.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_damaged_shadow", "image/Dungeon Creature/61_manticore/manticore_damaged_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_dead", "image/Dungeon Creature/61_manticore/manticore_dead.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_dead_shadow", "image/Dungeon Creature/61_manticore/manticore_dead_shadow.bmp", 1200, 280, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_idle", "image/Dungeon Creature/61_manticore/manticore_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_idle_shadow", "image/Dungeon Creature/61_manticore/manticore_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_move", "image/Dungeon Creature/61_manticore/manticore_move.bmp", 2600, 280, 13, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_move_shadow", "image/Dungeon Creature/61_manticore/manticore_move_shadow.bmp", 2600, 280, 13, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_select", "image/Dungeon Creature/61_manticore/manticore_select.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_select_shadow", "image/Dungeon Creature/61_manticore/manticore_select_shadow.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_switch", "image/Dungeon Creature/61_manticore/manticore_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("manticore_switch_shadow", "image/Dungeon Creature/61_manticore/manticore_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("manticore_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("manticore_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("manticore_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("manticore_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("manticore_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("manticore_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("manticore_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("manticore_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("manticore_dead_shadow")->AlphaInit();


	}
	//========== scorpicore
	{
		IMAGEMANAGER->addFrameImage("scorpicore_down", "image/Dungeon Creature/62_scorpicore/scorpicore_attack_down.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_down_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_attack_down_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_front", "image/Dungeon Creature/62_scorpicore/scorpicore_attack_front.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_front_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_attack_front_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_up", "image/Dungeon Creature/62_scorpicore/scorpicore_attack_up.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_up_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_attack_up_shadow.bmp", 1600, 280, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_damaged", "image/Dungeon Creature/62_scorpicore/scorpicore_damaged.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_damaged_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_damaged_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_dead", "image/Dungeon Creature/62_scorpicore/scorpicore_dead.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_dead_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_dead_shadow.bmp", 1000, 280, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_idle", "image/Dungeon Creature/62_scorpicore/scorpicore_idle.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_idle_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_idle_shadow.bmp", 200, 280, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_move", "image/Dungeon Creature/62_scorpicore/scorpicore_move.bmp", 2400, 280, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_move_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_move_shadow.bmp", 2400, 280, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_select", "image/Dungeon Creature/62_scorpicore/scorpicore_select.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_select_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_select_shadow.bmp", 800, 280, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_switch", "image/Dungeon Creature/62_scorpicore/scorpicore_switch.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("scorpicore_switch_shadow", "image/Dungeon Creature/62_scorpicore/scorpicore_switch_shadow.bmp", 400, 280, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("scorpicore_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("scorpicore_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("scorpicore_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("scorpicore_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("scorpicore_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("scorpicore_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("scorpicore_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("scorpicore_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("scorpicore_dead_shadow")->AlphaInit();


	}


	//========== red dragon
	{
	IMAGEMANAGER->addFrameImage("red_attack_down", "image/Dungeon Creature/71_red/red_attack_down.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_attack_down_shadow", "image/Dungeon Creature/71_red/red_attack_down_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_attack_front", "image/Dungeon Creature/71_red/red_attack_front.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_attack_front_shadow", "image/Dungeon Creature/71_red/red_attack_front_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_attack_up", "image/Dungeon Creature/71_red/red_attack_up.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_attack_up_shadow", "image/Dungeon Creature/71_red/red_attack_up_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_damaged", "image/Dungeon Creature/71_red/red_damaged.bmp", 2100, 440, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_damaged_shadow", "image/Dungeon Creature/71_red/red_damaged.bmp", 2100, 440, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_dead", "image/Dungeon Creature/71_red/red_dead.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_dead_shadow", "image/Dungeon Creature/71_red/red_dead_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_idle", "image/Dungeon Creature/71_red/red_idle.bmp", 300, 440, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_idle_shadow", "image/Dungeon Creature/71_red/red_idle_shadow.bmp", 300, 440, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_move", "image/Dungeon Creature/71_red/red_move.bmp", 3300, 440, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_move_shadow", "image/Dungeon Creature/71_red/red_move_shadow.bmp", 3300, 440, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_select", "image/Dungeon Creature/71_red/red_select.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_select_shadow", "image/Dungeon Creature/71_red/red_select_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_switch", "image/Dungeon Creature/71_red/red_switch.bmp", 600, 440, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_switch_shadow", "image/Dungeon Creature/71_red/red_switch_shadow.bmp", 600, 440, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("red_attack_down_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("red_attack_up_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("red_attack_front_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("red_damaged_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("red_idle_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("red_move_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("red_select_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("red_switch_shadow")->AlphaInit();
	IMAGEMANAGER->findImage("red_dead_shadow")->AlphaInit();

	}

	//========== black dragon
	{
		IMAGEMANAGER->addFrameImage("black_attack_down", "image/Dungeon Creature/72_black/black_attack_down.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_attack_down_shadow", "image/Dungeon Creature/72_black/black_attack_down_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_attack_front", "image/Dungeon Creature/72_black/black_attack_front.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_attack_front_shadow", "image/Dungeon Creature/72_black/black_attack_front_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_attack_up", "image/Dungeon Creature/72_black/black_attack_up.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_attack_up_shadow", "image/Dungeon Creature/72_black/black_attack_up_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_damaged", "image/Dungeon Creature/72_black/black_damaged.bmp", 1500, 440, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_damaged_shadow", "image/Dungeon Creature/72_black/black_damaged.bmp", 1500, 440, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_dead", "image/Dungeon Creature/72_black/black_dead.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_dead_shadow", "image/Dungeon Creature/72_black/black_dead_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_idle", "image/Dungeon Creature/72_black/black_idle.bmp", 300, 440, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_idle_shadow", "image/Dungeon Creature/72_black/black_idle_shadow.bmp", 300, 440, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_move", "image/Dungeon Creature/72_black/black_move.bmp", 3300, 440, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_move_shadow", "image/Dungeon Creature/72_black/black_move_shadow.bmp", 3300, 440, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_select", "image/Dungeon Creature/72_black/black_select.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_select_shadow", "image/Dungeon Creature/72_black/black_select_shadow.bmp", 1800, 440, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_switch", "image/Dungeon Creature/72_black/black_switch.bmp", 600, 440, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("black_switch_shadow", "image/Dungeon Creature/72_black/black_switch_shadow.bmp", 600, 440, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->findImage("black_attack_down_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("black_attack_up_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("black_attack_front_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("black_damaged_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("black_idle_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("black_move_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("black_select_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("black_switch_shadow")->AlphaInit();
		IMAGEMANAGER->findImage("black_dead_shadow")->AlphaInit();

	}






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