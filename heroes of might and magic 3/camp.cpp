#include "stdafx.h"
#include "camp.h"
#include "player.h"

camp::camp() {}
camp::~camp() {}


HRESULT camp::init(building info)
{
	//================================================
	// �ǹ� ���ڰ� 0�̸� �������� ���� ����			//
	// hall �� 1���� ���� : ����ȸ��					//
	// 1 �̻��� �ǹ� ����								//
	// �÷��̾�� 0�̸� �� 1�̻� �ش� �÷��̾ �Ҽ�	//
	//================================================
	ZeroMemory(&_buildingInfo, sizeof(tagBuildingInfo));

	_buildingInfo = info;
	_buildingInfo.campInfo.hall = 1;
	buildingInit();
	structureInit();
	unitSampleInit();
	recruitInit();

	_fieldPoint.x = _buildingInfo.destX + _buildingInfo.enterX;
	_fieldPoint.y = _buildingInfo.destY + _buildingInfo.enterY;

	_beBuilt = false;
	_contents = false;
	_showWindow = false;

	switch (_buildingInfo.camp)
	{
	case CAMP_CASTLE:
		
	break;
	
	case CAMP_DUNGEON:
		
	break;

	}



	return S_OK;
}

void camp::release(void)
{

}

void camp::update(void)
{
	//=================== F U N C T I O N ===================
	buildingCondition();			// 
	cameraSetting();				// �÷��� ī�޶� ���� �ǽð� �ޱ�
	setFrameCycle();
	
}

void camp::render(void)
{
	fieldDraw();


}

void camp::fieldDraw(void)
{
	IMAGEMANAGER->findImage("enter")->render(getMemDC(),
		_fieldPoint.x * TILESIZE - DATABASE->getPlayCameraX(),
		_fieldPoint.y * TILESIZE - DATABASE->getPlayCameraY());


	if (_buildingInfo.destX - _buildingInfo.imgX - _cameraArr.x >= -8 &&
		_buildingInfo.destX + _buildingInfo.sizeX / 2 - _cameraArr.x <= 32 &&
		_buildingInfo.destY - _buildingInfo.imgY - _cameraArr.y >= -6 &&
		_buildingInfo.destY - _buildingInfo.sizeY / 2 - _cameraArr.y <= 24)
	{
		if (_fort <= 2)
		{
			_fieldImg->frameRender(getMemDC(),
				(_buildingInfo.destX - _buildingInfo.imgX)*TILESIZE - DATABASE->getPlayCameraX(),
				(_buildingInfo.destY - _buildingInfo.imgY)*TILESIZE - DATABASE->getPlayCameraY(),
				_fort, 0);

			_fieldShadowImg->alphaFrameRender(getMemDC(),
				(_buildingInfo.destX - _buildingInfo.imgX)*TILESIZE - DATABASE->getPlayCameraX(),
				(_buildingInfo.destY - _buildingInfo.imgY)*TILESIZE - DATABASE->getPlayCameraY(),
				_fort, 0,190);

		}

		else
		{
			_fieldImg->frameRender(getMemDC(),
				(_buildingInfo.destX - _buildingInfo.imgX)*TILESIZE - DATABASE->getPlayCameraX(),
				(_buildingInfo.destY - _buildingInfo.imgY)*TILESIZE - DATABASE->getPlayCameraY(),
				2, 0);
			_fieldShadowImg->alphaFrameRender(getMemDC(),
				(_buildingInfo.destX - _buildingInfo.imgX)*TILESIZE - DATABASE->getPlayCameraX(),
				(_buildingInfo.destY - _buildingInfo.imgY)*TILESIZE - DATABASE->getPlayCameraY(),
				2, 0,190);

		}
	}
	


}

void camp::castleDraw(void)
{
	
	IMAGEMANAGER->findImage("city_UI")->render(getMemDC(), 0, 374);
	IMAGEMANAGER->findImage("mapToolUI")->render(getMemDC(), 800, 0);

	//============ Ư�� �ǹ� ��ȣ ==============
	// 0 : �׸��� ��ä
	// 1 : ������
	// 2 : ������
	// 3 : ���
	// 4 : �˻���ȸ

	IMAGEMANAGER->findImage("castle_back")->render(getMemDC());
	IMAGEMANAGER->findImage("castle_waterfall")->frameRender(getMemDC(),
		46, 119);
	IMAGEMANAGER->findImage("castle_stable")->frameRender(getMemDC(),
		384, 193, _special[2] - 1,IMAGEMANAGER->findImage("castle_stable")->getFrameY());
	IMAGEMANAGER->findImage("castle_storage")->frameRender(getMemDC(),
		488, 228, _market - 2, IMAGEMANAGER->findImage("castle_storage")->getFrameY());
	IMAGEMANAGER->findImage("castle_market")->frameRender(getMemDC(),
		413, 264, _market - 1, IMAGEMANAGER->findImage("castle_market")->getFrameY());
	IMAGEMANAGER->findImage("castle_guild")->frameRender(getMemDC(),
		704, 76, _guild -1 , IMAGEMANAGER->findImage("castle_guild")->getFrameY());
	IMAGEMANAGER->findImage("castle_guild_ani")->frameRender(getMemDC(),
		704, 76, IMAGEMANAGER->findImage("castle_guild_ani")->getFrameX(),_guild -1 );
	IMAGEMANAGER->findImage("castle_fort")->frameRender(getMemDC(),
		478, 37, _fort -1 , IMAGEMANAGER->findImage("castle_fort")->getFrameY());
	IMAGEMANAGER->findImage("castle_barrack")->frameRender(getMemDC(),
		304, 65, _level[0] -1 , IMAGEMANAGER->findImage("castle_barrack")->getFrameY());
	IMAGEMANAGER->findImage("castle_archer")->frameRender(getMemDC(),
		360, 115, _level[1] -1 , IMAGEMANAGER->findImage("castle_archer")->getFrameY());
	IMAGEMANAGER->findImage("castle_tower")->frameRender(getMemDC(),
		81, 44, _level[2] -1 , _special[0] + IMAGEMANAGER->findImage("castle_tower")->getFrameY()*2);
	IMAGEMANAGER->findImage("castle_sword")->frameRender(getMemDC(),
		176, 85, _level[3] -1, IMAGEMANAGER->findImage("castle_sword")->getFrameY());
	IMAGEMANAGER->findImage("castle_abbey")->frameRender(getMemDC(),
		563, 173, _level[4] -1 , IMAGEMANAGER->findImage("castle_abbey")->getFrameY());
	IMAGEMANAGER->findImage("castle_ground")->frameRender(getMemDC(),
		160, 190, _level[5] - 1, IMAGEMANAGER->findImage("castle_ground")->getFrameY());
	IMAGEMANAGER->findImage("castle_ground_ani")->frameRender(getMemDC(),
		160, 190, IMAGEMANAGER->findImage("castle_ground_ani")->getFrameX(), _level[5] - 1);
	IMAGEMANAGER->findImage("castle_hall")->frameRender(getMemDC(),
		0, 154, _hall -1 , IMAGEMANAGER->findImage("castle_hall")->getFrameY());
	IMAGEMANAGER->findImage("castle_hall_ani")->frameRender(getMemDC(),
		0, 154, IMAGEMANAGER->findImage("castle_hall_ani")->getFrameX(), _hall - 1);
	IMAGEMANAGER->findImage("castle_pub")->frameRender(getMemDC(),
		0, 198, _pub - 1, IMAGEMANAGER->findImage("castle_pub")->getFrameY());
	IMAGEMANAGER->findImage("castle_forge")->frameRender(getMemDC(),
		231, 255, _forge - 1, IMAGEMANAGER->findImage("castle_forge")->getFrameY());
	IMAGEMANAGER->findImage("castle_door")->frameRender(getMemDC(),
		302, 1, _level[6] - 1, IMAGEMANAGER->findImage("castle_door")->getFrameY());

	if (_showWindow)
	{
		switch (_windowNum)
		{
			//============== Ȧ
		case 0:
		{
			IMAGEMANAGER->findImage("window_3x2_hall")->render(getMemDC());
			for (int i = 0; i < 16; i++)
				{
					SetTextColor(getMemDC(), RGB(255, 255, 255));
				
					_structure[i].img->render(getMemDC(), _structure[i].x, _structure[i].y);
				
					_structure[i].checkImg->frameRender(getMemDC(),
						_structure[i].x - 1,
						_structure[i].y + 70, 0,
						_structure[i].index);
				
					TextOut(getMemDC(),
						_structure[i].x + 75 - strlen(_structure[i].name) / 2 * 8,
						_structure[i].y + 72, _structure[i].name,
						strlen(_structure[i].name));
					SetTextColor(getMemDC(), RGB(0, 0, 0));

				}
			if (_contents)
			{
				IMAGEMANAGER->findImage("window_build")->render(getMemDC(), 202, 40);
				IMAGEMANAGER->findImage("window_build_shadow")->alphaRender(getMemDC(), 202, 40, 100);

				_saveStructure.img->render(getMemDC(), 325, 88);

				SetTextColor(getMemDC(), RGB(255, 255, 255));

				if (strlen(_saveStructure.explantion) <= 42)
				{
					TextOut(getMemDC(), 240, 201, _saveStructure.explantion, strlen(_saveStructure.explantion));
				}
				else if (strlen(_saveStructure.explantion) > 42 && strlen(_saveStructure.explantion) <= 86)
				{
					int len = 0;
					for (int i = 36; i < 44; i++)
					{
						if (*(_saveStructure.explantion + i) == ' ' )
						{
							len = i;
							break;
						}
					}
					TextOut(getMemDC(), 240, 193, _saveStructure.explantion, len);
					TextOut(getMemDC(), 240, 209, _saveStructure.explantion + len + 1, strlen(_saveStructure.explantion) - len - 1);
				}
				else
				{
					int len = 0;
					int lenS = 0;
					for (int i = 36; i < 44; i++)
					{
						if (*(_saveStructure.explantion + i) == ' ')
						{
							len = i;
							break;
						}
					}
					for (int i = 76; i < 86; i++)
					{
						if (*(_saveStructure.explantion + i) == ' ')
						{
							lenS = i;
							break;
						}
					}
					TextOut(getMemDC(), 240, 185, _saveStructure.explantion, len);
					TextOut(getMemDC(), 240, 201, _saveStructure.explantion + len + 1, lenS - len);
					TextOut(getMemDC(), 240, 217, _saveStructure.explantion + lenS + 1, strlen(_saveStructure.explantion) - lenS - 1);


				}

				//============ �Ǽ� ���� ���� �˸�
				if (_saveStructure.needBuilding)
				{
					SetTextColor(getMemDC(), RGB(255, 255, 255));
					TextOut(getMemDC(), 385, 274, "�䱸 :", 6);
					TextOut(getMemDC(),
						399 - strlen(_saveStructure.needBuild) / 2 * 8,
						290, _saveStructure.needBuild, strlen(_saveStructure.needBuild));
				}
				else
				{
					if(_saveStructure.index != 3)
					TextOut(getMemDC(), 235, 282, "�ǹ��� ���� ���� ������ ��� �����Ͽ����ϴ�.",44 );

				}


				if (_saveStructure.index == 0)
				{

				}
				else 
				{
					IMAGEMANAGER->findImage("build_impossible")->render(getMemDC(), 247, 486);
				}
				if (_saveStructure.index == 3)
				{
					TextOut(getMemDC(), 251, 282, "�� ������ �� �ǹ��� �Ǽ��� �� �����ϴ�.", 39);

				}


				SetTextColor(getMemDC(), RGB(0, 0, 0));
				for (int i = 0; i < 4; i++)
				{
					IMAGEMANAGER->findImage("icon_resources")->frameRender(getMemDC(),
						264+ i*80, 344, i, 0);
				}

				for (int i = 0; i < 3; i++)
				{
					IMAGEMANAGER->findImage("icon_resources")->frameRender(getMemDC(),
						304+ 80*i, 417, 4 + i, 0);
				}

				numberDraw(getMemDC(), _saveStructure.wood, 277, 384);
				numberDraw(getMemDC(), _saveStructure.mercury, 357, 384);
				numberDraw(getMemDC(), _saveStructure.iron, 437, 384);
				numberDraw(getMemDC(), _saveStructure.sulfur, 517, 384);
				numberDraw(getMemDC(), _saveStructure.crystal, 317, 457);
				numberDraw(getMemDC(), _saveStructure.gem, 397, 457);
				numberDraw(getMemDC(), _saveStructure.gold, 470, 457);

			}


		}
		break;
			
		case 1:
		if(_fort > 0)
		{			
			//============== ��ä
			for (int i = 0; i < 6; i++)
				{
					IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(),
						168 + 394 * (i % 2), 25 + 133 * (i / 2));
				}
			IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(),
				364, 424);

			for (int i = 0; i < 6; i++)
				{
					IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(),
						168 + 394 * (i % 2), 25 + 133 * (i / 2));
				}
			IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(),
				364, 424);

			for (int i = 0; i < 14; i++)
				{
					if (_unitSample[i].img[_unitSample[i].state] != NULL)
					{
						if (_level[0] < 2 && i == 1) continue;
						else if (_level[0] >= 2 && i == 0) continue;

						if (_level[1] < 2 && i == 3) continue;
						else if (_level[1] >= 2 && i == 2) continue;

						if (_level[2] < 2 && i == 5) continue;
						else if (_level[2] >= 2 && i == 4) continue;

						if (_level[3] < 2 && i == 7) continue;
						else if (_level[3] >= 2 && i == 6) continue;

						if (_level[4] < 2 && i == 9) continue;
						else if (_level[4] >= 2 && i == 8) continue;

						if (_level[5] < 2 && i == 11) continue;
						else if (_level[5] >= 2 && i == 10) continue;

						if (_level[6] < 2 && i == 13) continue;
						else if (_level[6] >= 2 && i == 12) continue;

						_unitSample[i].img[_unitSample[i].state]->frameRender(getMemDC(),
							_unitSample[i].x, _unitSample[i].y);
						_unitSample[i].shadowImg[_unitSample[i].state]->alphaFrameRender(getMemDC(),
							_unitSample[i].x, _unitSample[i].y, SHADOWALPHA);

					}

				}

			IMAGEMANAGER->findImage("window_castle_fort")->render(getMemDC());



			//================== ��ũ��Ʈ â ��
			if (_contents)
			{
				char tmp[256];
				int num = _saveRecruit.num *2 + _level[_saveRecruit.num] - 1 ;
				
				if (_level[_saveRecruit.num] > 0)
				{
					HFONT font1 = CreateFont(24, 0, 0, 0, 50, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));

					HFONT oldfont = (HFONT)SelectObject(getMemDC(), font1);
					SetTextColor(getMemDC(), RGB(248, 228, 144));


					// ���� 240 110 -> 383 126 /////  189 59  332 75 
					IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(), 332, 75);


					_unitSample[num].img[_unitSample[num].state]->frameRender(getMemDC(),
						383 - _unitSample[num].img[_unitSample[num].state]->getFrameWidth() / 2,
						136 - _unitSample[num].img[_unitSample[num].state]->getFrameHeight() / 2);

					_unitSample[num].shadowImg[_unitSample[num].state]->alphaFrameRender(getMemDC(),
						383 - _unitSample[num].img[_unitSample[num].state]->getFrameWidth() / 2,
						136 - _unitSample[num].img[_unitSample[num].state]->getFrameHeight() / 2 , 140);

					IMAGEMANAGER->findImage("window_recruit")->render(getMemDC(), 143, 16);
					IMAGEMANAGER->findImage("window_recruit_shadow")->alphaRender(getMemDC(), 143, 16, 100);


					sprintf(tmp, "��� %s", _saveRecruit.unit);
					SelectObject(getMemDC(), font1);
					TextOut(getMemDC(), 389 - strlen(tmp) / 2 * 16, 36, tmp, strlen(tmp));

					SetTextColor(getMemDC(), RGB(0, 0, 0));
					DeleteObject(font1);
					SelectObject(getMemDC(), oldfont);

				}
				else _contents = false;



				
			}





		}
		else _showWindow = false;

		break;

		case 2: case 3: case 4: case 5: case 6: case 7: case 8:
		{
			//================== ��ũ��Ʈ â ��
			char tmp[256];
			int num = _saveRecruit.num * 2 + _level[_saveRecruit.num] - 1;

			if (_level[_saveRecruit.num] > 0)
			{
				HFONT font1 = CreateFont(24, 0, 0, 0, 50, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));

				HFONT oldfont = (HFONT)SelectObject(getMemDC(), font1);
				SetTextColor(getMemDC(), RGB(248, 228, 144));


				// ���� 240 110 -> 383 126 /////  189 59  332 75 
				IMAGEMANAGER->findImage("castle_fort_back")->render(getMemDC(), 332, 75);


				_unitSample[num].img[_unitSample[num].state]->frameRender(getMemDC(),
					383 - _unitSample[num].img[_unitSample[num].state]->getFrameWidth() / 2,
					136 - _unitSample[num].img[_unitSample[num].state]->getFrameHeight() / 2);

				_unitSample[num].shadowImg[_unitSample[num].state]->alphaFrameRender(getMemDC(),
					383 - _unitSample[num].img[_unitSample[num].state]->getFrameWidth() / 2,
					136 - _unitSample[num].img[_unitSample[num].state]->getFrameHeight() / 2, 140);

				IMAGEMANAGER->findImage("window_recruit")->render(getMemDC(), 143, 16);
				IMAGEMANAGER->findImage("window_recruit_shadow")->alphaRender(getMemDC(), 143, 16, 100);


				sprintf(tmp, "��� %s", _saveRecruit.unit);
				SelectObject(getMemDC(), font1);
				TextOut(getMemDC(), 389 - strlen(tmp) / 2 * 16, 36, tmp, strlen(tmp));

				SetTextColor(getMemDC(), RGB(0, 0, 0));
				DeleteObject(font1);
				SelectObject(getMemDC(), oldfont);


			}
			else _showWindow = false;




		}

		break;

		default:
		{
			_showWindow = false;
		}
		break;

		}
	}

	numberDraw(getMemDC(), _property.wood, 46, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.mercury, 130, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.iron, 206, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.sulfur, 288, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.crystal, 368, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.gem, 446, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.gold, 528, WINSIZEY - 40);


}

void camp::dungeonDraw(void)
{
	IMAGEMANAGER->findImage("city_UI")->render(getMemDC(), 0, 374);
	IMAGEMANAGER->findImage("mapToolUI")->render(getMemDC(), 800, 0);

	// 0 : ���� ��
	// 1 : ��ī����
	// 2 : ���� ����
	// 3 : ��Ƽ��Ʈ ����
	// 4 : ��Ż
	IMAGEMANAGER->findImage("dungeon_back")->render(getMemDC());

	IMAGEMANAGER->findImage("dungeon_temple")->frameRender(getMemDC(),
		300, 29, _level[3] - 1,IMAGEMANAGER->findImage("dungeon_temple")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_maze")->frameRender(getMemDC(),
		519, 172, _level[4] - 1,IMAGEMANAGER->findImage("dungeon_maze")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_manCave")->frameRender(getMemDC(),
		270, 253, _level[5] - 1, IMAGEMANAGER->findImage("dungeon_manCave")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_draCave")->frameRender(getMemDC(),
		550, 0, _level[6] - 1,IMAGEMANAGER->findImage("dungeon_draCave")->getFrameY());
	
	IMAGEMANAGER->findImage("dungeon_draCave_ani")->frameRender(getMemDC(),
		550, 0, IMAGEMANAGER->findImage("dungeon_draCave_ani")->getFrameX(), _level[6] - 1);

	IMAGEMANAGER->findImage("dungeon_academy")->frameRender(getMemDC(),
		311, 298, _special[0] - 1, IMAGEMANAGER->findImage("dungeon_academy")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_guild")->frameRender(getMemDC(),
		164, 15, _guild - 1, IMAGEMANAGER->findImage("dungeon_guild")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_forge")->frameRender(getMemDC(),
		546, 250, _forge - 1, IMAGEMANAGER->findImage("dungeon_forge")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_market")->frameRender(getMemDC(),
		590, 318, _market - 1, IMAGEMANAGER->findImage("dungeon_market")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_storage")->frameRender(getMemDC(),
		624, 335l, _market - 2, IMAGEMANAGER->findImage("dungeon_storage")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_artifact")->frameRender(getMemDC(),
		745, 297, _special[3] - 1, IMAGEMANAGER->findImage("dungeon_artifact")->getFrameY());

	if(_special[4]) IMAGEMANAGER->findImage("dungeon_portal")->frameRender(getMemDC(),
		687, 177);

	if(_special[2])
	IMAGEMANAGER->findImage("dungeon_cloud")->frameRender(getMemDC(),
		131, 26, IMAGEMANAGER->findImage("dungeon_cloud")->getFrameX(),
		_guild/5 + IMAGEMANAGER->findImage("dungeon_cloud")->getFrameY() * 2);

	IMAGEMANAGER->findImage("dungeon_pub")->frameRender(getMemDC(),
		211, 297, _pub - 1, IMAGEMANAGER->findImage("dungeon_pub")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_hall")->frameRender(getMemDC(),
		0, 203, _hall - 1, IMAGEMANAGER->findImage("dungeon_hall")->getFrameY());

	IMAGEMANAGER->findImage("dungeon_fort")->frameRender(getMemDC(),
		363, 87, _fort - 1, IMAGEMANAGER->findImage("dungeon_fort")->getFrameY());

	if(_level[2])
	IMAGEMANAGER->findImage("dungeon_pillar")->frameRender(getMemDC(),
		121, 256, IMAGEMANAGER->findImage("dungeon_pillar")->getFrameX()
		,_level[2] + IMAGEMANAGER->findImage("dungeon_pillar")->getFrameY()*2);

	if(_level[0])
	IMAGEMANAGER->findImage("dungeon_farm")->frameRender(getMemDC(),
		0, 300, IMAGEMANAGER->findImage("dungeon_farm")->getFrameX(),
		_level[0] + IMAGEMANAGER->findImage("dungeon_farm")->getFrameY() * 4);

	IMAGEMANAGER->findImage("dungeon_nest")->frameRender(getMemDC(),
		0, 26 , _level[1] - 1, IMAGEMANAGER->findImage("dungeon_nest")->getFrameY());


	if (_showWindow)
	{
		switch (_windowNum)
		{
			//============== Ȧ
		case 0:
		{
			
				IMAGEMANAGER->findImage("window_4x3_hall")->render(getMemDC());
			
				for (int i = 0; i < 18; i++)
				{
					SetTextColor(getMemDC(), RGB(255, 255, 255));

					_structure[i].img->render(getMemDC(), _structure[i].x, _structure[i].y);
				
					_structure[i].checkImg->frameRender(getMemDC(),
						_structure[i].x - 1,
						_structure[i].y + 70, 0,
						_structure[i].index);

					TextOut(getMemDC(),
						_structure[i].x + 75 - strlen(_structure[i].name) / 2 * 8,
						_structure[i].y + 72, _structure[i].name,
						strlen(_structure[i].name));
					SetTextColor(getMemDC(), RGB(0, 0, 0));

				}
				if (_contents)
				{
					IMAGEMANAGER->findImage("window_build")->render(getMemDC(), 202, 40);
					IMAGEMANAGER->findImage("window_build_shadow")->alphaRender(getMemDC(), 202, 40, 100);

					_saveStructure.img->render(getMemDC(), 325, 88);

					SetTextColor(getMemDC(), RGB(255, 255, 255));

					if (strlen(_saveStructure.explantion) <= 42)
					{
						TextOut(getMemDC(), 240, 201, _saveStructure.explantion, strlen(_saveStructure.explantion));
					}
					else if (strlen(_saveStructure.explantion) > 42 && strlen(_saveStructure.explantion) <= 86)
					{
						int len = 0;
						for (int i = 36; i < 44; i++)
						{
							if (*(_saveStructure.explantion + i) == ' ')
							{
								len = i;
								break;
							}
						}
						TextOut(getMemDC(), 240, 193, _saveStructure.explantion, len);
						TextOut(getMemDC(), 240, 209, _saveStructure.explantion + len + 1, strlen(_saveStructure.explantion) - len - 1);
					}
					else
					{
						int len = 0;
						int lenS = 0;
						for (int i = 36; i < 44; i++)
						{
							if (*(_saveStructure.explantion + i) == ' ')
							{
								len = i;
								break;
							}
						}
						for (int i = 76; i < 86; i++)
						{
							if (*(_saveStructure.explantion + i) == ' ')
							{
								lenS = i;
								break;
							}
						}
						TextOut(getMemDC(), 240, 185, _saveStructure.explantion, len);
						TextOut(getMemDC(), 240, 201, _saveStructure.explantion + len + 1, lenS - len);
						TextOut(getMemDC(), 240, 217, _saveStructure.explantion + lenS + 1, strlen(_saveStructure.explantion) - lenS - 1);


					}


					//============ �Ǽ� ���� ���� �˸�
					if (_saveStructure.needBuilding)
					{

						TextOut(getMemDC(), 385, 274, "�䱸 :", 6);
						TextOut(getMemDC(),
							399 - strlen(_saveStructure.needBuild) / 2 * 8,
							290, _saveStructure.needBuild, strlen(_saveStructure.needBuild));
					}
					else
					{
						if (_saveStructure.index != 3)
							TextOut(getMemDC(), 235, 282, "�ǹ��� ���� ���� ������ ��� �����Ͽ����ϴ�.", 44);

					}


					if (_saveStructure.index == 0)
					{

					}
					else
					{
						IMAGEMANAGER->findImage("build_impossible")->render(getMemDC(), 247, 486);
					}
					if (_saveStructure.index == 3)
					{
						TextOut(getMemDC(), 251, 282, "�� ������ �� �ǹ��� �Ǽ��� �� �����ϴ�.", 39);

					}

					SetTextColor(getMemDC(), RGB(0, 0, 0));

					for (int i = 0; i < 4; i++)
					{
						IMAGEMANAGER->findImage("icon_resources")->frameRender(getMemDC(),
							264 + i * 80, 344, i, 0);
					}

					for (int i = 0; i < 3; i++)
					{
						IMAGEMANAGER->findImage("icon_resources")->frameRender(getMemDC(),
							304 + 80 * i, 417, 4 + i, 0);
					}

					numberDraw(getMemDC(), _saveStructure.wood, 277, 384);
					numberDraw(getMemDC(), _saveStructure.mercury, 357, 384);
					numberDraw(getMemDC(), _saveStructure.iron, 437, 384);
					numberDraw(getMemDC(), _saveStructure.sulfur, 517, 384);
					numberDraw(getMemDC(), _saveStructure.crystal, 317, 457);
					numberDraw(getMemDC(), _saveStructure.gem, 397, 457);
					numberDraw(getMemDC(), _saveStructure.gold, 470, 457);

				}

		}
		break;

			//============== ��ä
		case 1:

		if(_fort >0)
		{
			
			
			for (int i = 0; i < 6; i++)
				{
					IMAGEMANAGER->findImage("dungeon_fort_back")->render(getMemDC(),
						168 + 394*(i%2), 25 + 133*(i/2));
				}
		
			IMAGEMANAGER->findImage("dungeon_fort_back")->render(getMemDC(),
				364, 424);
			
			for (int i = 0; i < 14; i++)
				{
					if (_unitSample[i].img[_unitSample[i].state] != NULL)
					{
						if (_level[0] < 2 && i == 1) continue;
						else if (_level[0] >= 2 && i == 0) continue;

						if (_level[1] < 2 && i == 3) continue;
						else if (_level[1] >= 2 && i == 2) continue;

						if (_level[2] < 2 && i == 5) continue;
						else if (_level[2] >= 2 && i == 4) continue;

						if (_level[3] < 2 && i == 7) continue;
						else if (_level[3] >= 2 && i == 6) continue;

						if (_level[4] < 2 && i == 9) continue;
						else if (_level[4] >= 2 && i == 8) continue;

						if (_level[5] < 2 && i == 11) continue;
						else if (_level[5] >= 2 && i == 10) continue;

						if (_level[6] < 2 && i == 13) continue;
						else if (_level[6] >= 2 && i == 12) continue;

						_unitSample[i].img[_unitSample[i].state]->frameRender(getMemDC(),
							_unitSample[i].x, _unitSample[i].y);
						_unitSample[i].shadowImg[_unitSample[i].state]->alphaFrameRender(getMemDC(),
							_unitSample[i].x, _unitSample[i].y,SHADOWALPHA);

					}

				}

			IMAGEMANAGER->findImage("window_dungeon_fort")->render(getMemDC());

			//================== ��ũ��Ʈ â ��
			if (_contents)
			{
				char tmp[256];
				int num = _saveRecruit.num * 2 + _level[_saveRecruit.num] - 1;

				if (_level[_saveRecruit.num] > 0)
				{
					HFONT font1 = CreateFont(24, 0, 0, 0, 50, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));

					HFONT oldfont = (HFONT)SelectObject(getMemDC(), font1);
					SetTextColor(getMemDC(), RGB(248, 228, 144));


					// ���� 240 110 -> 383 126 /////  189 59  332 75 
					IMAGEMANAGER->findImage("dungeon_fort_back")->render(getMemDC(), 332, 75);


					_unitSample[num].img[_unitSample[num].state]->frameRender(getMemDC(),
						383 - _unitSample[num].img[_unitSample[num].state]->getFrameWidth() / 2,
						136 - _unitSample[num].img[_unitSample[num].state]->getFrameHeight() / 2);

					_unitSample[num].shadowImg[_unitSample[num].state]->alphaFrameRender(getMemDC(),
						383 - _unitSample[num].img[_unitSample[num].state]->getFrameWidth() / 2,
						136 - _unitSample[num].img[_unitSample[num].state]->getFrameHeight() / 2, 140);

					IMAGEMANAGER->findImage("window_recruit")->render(getMemDC(), 143, 16);
					IMAGEMANAGER->findImage("window_recruit_shadow")->alphaRender(getMemDC(), 143, 16, 100);


					sprintf(tmp, "��� %s", _saveRecruit.unit);
					SelectObject(getMemDC(), font1);
					TextOut(getMemDC(), 389 - strlen(tmp) / 2 * 16, 36, tmp, strlen(tmp));

					SetTextColor(getMemDC(), RGB(0, 0, 0));
					DeleteObject(font1);
					SelectObject(getMemDC(), oldfont);

				}
				else _contents = false;


			}








		}
		else _showWindow = false;

		break;

		case 2: case 3: case 4: case 5: case 6: case 7: case 8:
		{
			//================== ��ũ��Ʈ â ��
			char tmp[256];
			int num = _saveRecruit.num * 2 + _level[_saveRecruit.num] - 1;

			if (_level[_saveRecruit.num] > 0)
			{
				HFONT font1 = CreateFont(24, 0, 0, 0, 50, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));

				HFONT oldfont = (HFONT)SelectObject(getMemDC(), font1);
				SetTextColor(getMemDC(), RGB(248, 228, 144));


				// ���� 240 110 -> 383 126 /////  189 59  332 75 
				IMAGEMANAGER->findImage("dungeon_fort_back")->render(getMemDC(), 332, 75);


				_unitSample[num].img[_unitSample[num].state]->frameRender(getMemDC(),
					383 - _unitSample[num].img[_unitSample[num].state]->getFrameWidth() / 2,
					136 - _unitSample[num].img[_unitSample[num].state]->getFrameHeight() / 2);

				_unitSample[num].shadowImg[_unitSample[num].state]->alphaFrameRender(getMemDC(),
					383 - _unitSample[num].img[_unitSample[num].state]->getFrameWidth() / 2,
					136 - _unitSample[num].img[_unitSample[num].state]->getFrameHeight() / 2, 140);

				IMAGEMANAGER->findImage("window_recruit")->render(getMemDC(), 143, 16);
				IMAGEMANAGER->findImage("window_recruit_shadow")->alphaRender(getMemDC(), 143, 16, 100);


				sprintf(tmp, "��� %s", _saveRecruit.unit);
				SelectObject(getMemDC(), font1);
				TextOut(getMemDC(), 389 - strlen(tmp) / 2 * 16, 36, tmp, strlen(tmp));

				SetTextColor(getMemDC(), RGB(0, 0, 0));
				DeleteObject(font1);
				SelectObject(getMemDC(), oldfont);


			}
			else _showWindow = false;




		}

		break;


		default:
			_showWindow = false;
		break;
		}
	}

	numberDraw(getMemDC(), _property.wood, 46, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.mercury, 130, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.iron, 206, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.sulfur, 288, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.crystal, 368, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.gem, 446, WINSIZEY - 40);
	numberDraw(getMemDC(), _property.gold, 528, WINSIZEY - 40);



}

void camp::setFrameCycle(void)
{
	frameCycle("castle_hall_ani", 12,true);
	frameCycle("castle_ground_ani", 12,true);
	frameCycle("castle_waterfall", 8);
	frameCycle("castle_guild_ani", 8);


	frameCycle("dungeon_farm", 8);
	frameCycle("dungeon_cloud", 8);
	frameCycle("dungeon_pillar", 8);
	frameCycle("dungeon_draCave_ani", 8);
	frameCycle("dungeon_portal", 8);





	//================ unit sample
	
	if (_showWindow )
	{
		if(_windowNum >=1 && _windowNum <= 8)
		{
			for (int i = 0; i < 14; i++)
			{
				if (_unitSample[i].img[_unitSample[i].state] != NULL)
				{


					if ((int)(TIMEMANAGER->getWorldTime() / TIMEMANAGER->getElapsedTime()) % 8 == 0)
					{
				
						if (_unitSample[i].img[_unitSample[i].state]->getFrameX() >=
							_unitSample[i].img[_unitSample[i].state]->getMaxFrameX())
						{
							_unitSample[i].img[_unitSample[i].state]->setFrameX(-1);
							_unitSample[i].shadowImg[_unitSample[i].state]->setFrameX(-1);
							_unitSample[i].state = (CREATURESTATE)(_unitSample[i].state + 1);
				



							if (_unitSample[i].state == STATE_SWITCH) _unitSample[i].state = STATE_DOWN;
						}
				
				
				
				
					
						_unitSample[i].img[_unitSample[i].state]->setFrameX(_unitSample[i].img[_unitSample[i].state]->getFrameX() + 1);
						_unitSample[i].shadowImg[_unitSample[i].state]->setFrameX(_unitSample[i].shadowImg[_unitSample[i].state]->getFrameX() + 1);

					}


				}
			
			}

		}
		


	}
	


}

void camp::selectBox(void)
{
	if (_buildingInfo.camp == CAMP_CASTLE)
	{
		if (getPixelC(0)) IMAGEMANAGER->findImage("castle_hall")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_hall")->				setFrameY(0);	
		
		if (getPixelC(1)) IMAGEMANAGER->findImage("castle_fort")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_fort")->				setFrameY(0);
		
		if (getPixelC(2)) IMAGEMANAGER->findImage("castle_barrack")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_barrack")->			setFrameY(0);

		if (getPixelC(3)) IMAGEMANAGER->findImage("castle_archer")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_archer")->				setFrameY(0);

		if (getPixelC(4)) IMAGEMANAGER->findImage("castle_tower")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_tower")->				setFrameY(0);

		if (getPixelC(5)) IMAGEMANAGER->findImage("castle_sword")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_sword")->				setFrameY(0);
		
		if (getPixelC(6)) IMAGEMANAGER->findImage("castle_abbey")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_abbey")->				setFrameY(0);

		if (getPixelC(7)) IMAGEMANAGER->findImage("castle_ground")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_ground")->				setFrameY(0);

		if (getPixelC(8)) IMAGEMANAGER->findImage("castle_door")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_door")->				setFrameY(0);
	
		if (getPixelC(9)) IMAGEMANAGER->findImage("castle_pub")->		setFrameY(1);
		else IMAGEMANAGER->findImage("castle_pub")->				setFrameY(0);

		if (getPixelC(10)) IMAGEMANAGER->findImage("castle_forge")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_forge")->				setFrameY(0);

		if (getPixelC(11)) IMAGEMANAGER->findImage("castle_market")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_market")->				setFrameY(0);

		if (getPixelC(12)) IMAGEMANAGER->findImage("castle_guild")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_guild")->				setFrameY(0);
		
		if (getPixelC(13)) IMAGEMANAGER->findImage("castle_stable")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_stable")->				setFrameY(0);

		if (getPixelC(14)) IMAGEMANAGER->findImage("castle_storage")->	setFrameY(1);
		else IMAGEMANAGER->findImage("castle_storage")->			setFrameY(0);

	}
	else if (_buildingInfo.camp == CAMP_DUNGEON)
	{
		if (getPixelD(0)) IMAGEMANAGER->findImage("dungeon_hall")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_hall")->setFrameY(0);

		if (getPixelD(1)) IMAGEMANAGER->findImage("dungeon_fort")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_fort")->setFrameY(0);

		if (getPixelD(2)) IMAGEMANAGER->findImage("dungeon_farm")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_farm")->setFrameY(0);

		if (getPixelD(3)) IMAGEMANAGER->findImage("dungeon_nest")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_nest")->setFrameY(0);

		if (getPixelD(4)) IMAGEMANAGER->findImage("dungeon_pillar")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_pillar")->setFrameY(0);

		if (getPixelD(5)) IMAGEMANAGER->findImage("dungeon_temple")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_temple")->setFrameY(0);

		if (getPixelD(6)) IMAGEMANAGER->findImage("dungeon_maze")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_maze")->setFrameY(0);

		if (getPixelD(7)) IMAGEMANAGER->findImage("dungeon_manCave")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_manCave")->setFrameY(0);

		if (getPixelD(8)) IMAGEMANAGER->findImage("dungeon_draCave")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_draCave")->setFrameY(0);

		if (getPixelD(9)) IMAGEMANAGER->findImage("dungeon_pub")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_pub")->setFrameY(0);
	
		if (getPixelD(10)) IMAGEMANAGER->findImage("dungeon_forge")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_forge")->setFrameY(0);
		
		if (getPixelD(11)) IMAGEMANAGER->findImage("dungeon_market")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_market")->setFrameY(0);

		if (getPixelD(12)) IMAGEMANAGER->findImage("dungeon_guild")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_guild")->setFrameY(0);

		if (getPixelD(13)) IMAGEMANAGER->findImage("dungeon_cloud")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_cloud")->setFrameY(0);

		if (getPixelD(14)) IMAGEMANAGER->findImage("dungeon_storage")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_storage")->setFrameY(0);

		if (getPixelD(15)) IMAGEMANAGER->findImage("dungeon_artifact")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_artifact")->setFrameY(0);

		if (getPixelD(16)) IMAGEMANAGER->findImage("dungeon_portal")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_portal")->setFrameY(0);

		if (getPixelD(17)) IMAGEMANAGER->findImage("dungeon_academy")->setFrameY(1);
		else IMAGEMANAGER->findImage("dungeon_academy")->setFrameY(0);

	}




}

void camp::buildingInit()
{
	_cityScene = false;
	strcpy(_name, _buildingInfo.campInfo.name);
	_camp				= _buildingInfo.camp;
	_hall				= _buildingInfo.campInfo.hall;
	_fort				= _buildingInfo.campInfo.fort;
	_pub				= _buildingInfo.campInfo.pub;
	_guild				= _buildingInfo.campInfo.guild;
	_market				= _buildingInfo.campInfo.market;
	_forge				= _buildingInfo.campInfo.forge;
	_player				= _buildingInfo.campInfo.player;
	for (int i = 0; i < 7; i++)
	{
		_level[i]		= _buildingInfo.campInfo.level[i];
	}
	for (int i = 0; i < 5; i++)
	{
		_special[i]		= _buildingInfo.campInfo.special[i];
	}
	//================== �ʵ� �̹��� =====================

	switch (_camp)
	{
	case CAMP_CASTLE:
		_fieldImg = IMAGEMANAGER->findImage("building_castle");
		_fieldShadowImg = IMAGEMANAGER->findImage("building_castle_shadow");
		break;
	case CAMP_DUNGEON:
		_fieldImg = IMAGEMANAGER->findImage("building_dungeon");
		_fieldShadowImg = IMAGEMANAGER->findImage("building_dungeon_shadow");
		break;
	}

	_fieldRect = RectMake(_buildingInfo.destX, _buildingInfo.destY,
		_buildingInfo.sizeX, _buildingInfo.sizeY);

}

void camp::inputCity(void)
{
	//���� ���� ���� �ִ���?
		//�ٸ� ���� �ִ� â ����?
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_showWindow)
		{
			switch (_camp)
			{
			case CAMP_CASTLE:
				if (getMenuC())
				{
					_showWindow = true;
					_windowNum = getPixelC();

					if (getPixelC() >= 2 && getPixelC() <= 8)
					{
						_saveRecruit = _recruit[getPixelC() - 2];
					}

				}

				break;
			case CAMP_DUNGEON:
				if (getMenuD())
				{
					_showWindow = true;
					_windowNum = getPixelD();

					if (getPixelD() >= 2 && getPixelD() <= 8)
					{
						_saveRecruit = _recruit[getPixelD() - 2];
					}

				}

				break;
			}
			//===========������ ������ ��ư
			if (PtInRect(&RectMake(744, 544, 48, 30), _ptMouse))
			{
				_play->setScene(false);
				_play->setProperty(_property);
			}
		}
		//=========â�� ���� �־�?
		else
		{
			switch (_camp)
			{
			case CAMP_CASTLE:
				switch (_windowNum)
				{
					//===========Ȧ�� ��������
				case 0:
				{
					if (!_contents)
					{
						if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
						{
							_showWindow = false;
						}
						for (int i = 0; i < 16; i++)
						{
							if (PtInRect(&RectMake(
								_structure[i].x, _structure[i].y, 150, 70), _ptMouse))
							{
								_contents = true;
								_saveStructure = _structure[i];
							}
						}


					}
					else
					{
						if (PtInRect(&RectMake(247, 486, 64, 30), _ptMouse))
						{
							if (_saveStructure.index == 0)
							{
								_contents = false;
								_showWindow = false;
								_property.crystal -= _saveStructure.crystal;
								_property.mercury -= _saveStructure.mercury;
								_property.sulfur -= _saveStructure.sulfur;
								_property.gold -= _saveStructure.gold;
								_property.wood -= _saveStructure.wood;
								_property.iron -= _saveStructure.iron;
								_property.gem -= _saveStructure.gem;
								switch (_saveStructure.num)
								{
								case 0: _hall++;
								break;
								case 1: _fort++;
								break;
								case 2: if (_pub == 0) _pub++; else _special[4]++;
								break;
								case 3: _forge++;
								break;
								case 4: _market++;  
								break;
								case 5: _guild++;
								break;
								case 6: _special[1]++;
								break;
								case 7: _special[2]++;
								break;
								case 8: _special[0]++;
								break;
								case 9: _level[0]++;
								break;
								case 10: _level[1]++;
								break;
								case 11: _level[2]++;
								break;
								case 12: _level[3]++;
								break;
								case 13: _level[4]++;
								break;
								case 14: _level[5]++;
								break;
								case 15: _level[6]++;
								break;
								}
								structureInit();
								recruitInit();


							}

					
						}
						if (PtInRect(&RectMake(492, 486, 64, 30), _ptMouse))
						{
							_contents = false;
						}
					}


				}
				break;

					//=========��ä�� ��������
				case 1:
				{
					if (!_contents)
					{
						//============== recruit window�� �����
						for (int i = 0; i < 7; i++)
						{
							if (PtInRect(&RectMake(_recruit[i].x, _recruit[i].y, 386, 126), _ptMouse))
							{
								_saveRecruit = _recruit[i];
								_contents = true;




							}
						}







						//============== â �ݴ°�
						if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
						{
							_showWindow = false;
						}

					}
					else
					{
						//================ recruit window�� ������

						//============== â �ݴ°�
						if (PtInRect(&RectMake(433, 329, 64, 32), _ptMouse))
						{
							_contents = false;
						}


					}

				}
				break;

				case 2: case 3: case 4: case 5: case 6: case 7: case 8:

					if (PtInRect(&RectMake(433, 329, 64, 32), _ptMouse))
					{
						_showWindow = false;
					}



				break;

				default:
				{
					_showWindow = false;
				}
				break;
				}
			break;


			case CAMP_DUNGEON:
				switch (_windowNum)
				{
				case 0:
					if (!_contents)
					{
						if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
						{
							_showWindow = false;
						}
						for (int i = 0; i < 18; i++)
						{
							if (PtInRect(&RectMake(
								_structure[i].x, _structure[i].y, 150, 70), _ptMouse))
							{
								_contents = true;
								_saveStructure = _structure[i];
							}
						}


					}
					else
					{
						if (PtInRect(&RectMake(247, 486, 64, 30), _ptMouse))
						{
							if (_saveStructure.index == 0)
							{
								_contents = false;
								_showWindow = false;
								_property.crystal -= _saveStructure.crystal;
								_property.mercury -= _saveStructure.mercury;
								_property.sulfur -= _saveStructure.sulfur;
								_property.gold -= _saveStructure.gold;
								_property.wood -= _saveStructure.wood;
								_property.iron -= _saveStructure.iron;
								_property.gem -= _saveStructure.gem;
								switch (_saveStructure.num)
								{
								case 0: _hall++;
									break;
								case 1: _fort++;
									break;
								case 2: _pub++; 
									break;
								case 3: _forge++;
									break;
								case 4: _market++;  
									break;
								case 5: _guild++;
									break;
								case 6: _special[2]++;
									break;
								case 7: _special[3]++;
									break;
								case 8: _special[1]++;
									break;
								case 9: _level[0]++;
									break;
								case 10: _level[1]++;
									break;
								case 11: _level[2]++;
									break;
								case 12: _level[3]++;
									break;
								case 13: _level[4]++;
									break;
								case 14: _level[5]++;
									break;
								case 15: _level[6]++;
									break;
								case 16: _special[4]++;
									break;
								case 17: _special[0]++;
									break;
								}
								structureInit();



							}

						}


						if (PtInRect(&RectMake(492, 486, 64, 30), _ptMouse))
						{
							_contents = false;
						}
					}

				break;

				case 1:

					if (!_contents)
					{

						//============== recruit window�� �����
						for (int i = 0; i < 7; i++)
						{
							if (PtInRect(&RectMake(_recruit[i].x, _recruit[i].y, 386, 126), _ptMouse))
							{
								_saveRecruit = _recruit[i];
								_contents = true;




							}
						}



						if (PtInRect(&RectMake(748, 556, 48, 40), _ptMouse))
						{
							_showWindow = false;
						}

					}
					else
					{
						//================ recruit window�� ������

						//============== â �ݴ°�
						if (PtInRect(&RectMake(433, 329, 64, 32), _ptMouse))
						{
							_contents = false;
						}

					}
			
				break;

				case 2: case 3: case 4: case 5: case 6: case 7: case 8:

					if (PtInRect(&RectMake(433, 329, 64, 32), _ptMouse))
					{
						_showWindow = false;
					}

				break;

				default:

					_showWindow = false;

				break;

				}
				break;
			}
		}

	}
	



}

void camp::buildingCondition(void)
{
	
	if (_hall > 4) _hall = 4;
	if (_fort > 4) _fort = 4;
	if (_pub > 1) _pub = 1;
	if (_market > 1) _market = 1;
	if (_forge > 1) _forge = 1;
	for (int i = 0; i < 7; i++)
	{
		if (_level[i] > 2) _level[i] = 2;
	}
	for (int i = 0; i < 5; i++)
	{
		if (_special[i] > 1) _special[i] = 1;
	}

	switch (_camp)
	{
	case CAMP_CASTLE:
		if (_guild > 4) _guild = 4;
		
		break;
	case CAMP_DUNGEON:
		if (_guild > 5) _guild = 5;
		break;
	}
	

	//================= �̹��� �� ��������
	if (!_beBuilt)
	{
			//============= ����ǹ� ����
		switch (_camp)
		{
		case CAMP_CASTLE:
			if (_fort < 1)	_structure[9].needBuilding = true;
			else _structure[0].needBuilding = false;

			if (_level[0] < 1 || _level[3] < 1)	_structure[11].needBuilding = true;
			else _structure[11].needBuilding = false;

			if (_level[0] < 1 || _forge < 1) _structure[12].needBuilding = true;
			else _structure[12].needBuilding = false;

			if (_level[0] < 1 || _guild < 1) _structure[13].needBuilding = true;
			else _structure[13].needBuilding = false;

			if (_level[0] < 1 || _special[2] < 1) _structure[14].needBuilding = true;
			else _structure[14].needBuilding = false;

			if (_level[0] < 1 || _level[4] < 1) _structure[15].needBuilding = true;
			else _structure[15].needBuilding = false;

			if (_level[2] < 1) _structure[8].needBuilding = true;
			else _structure[8].needBuilding = false;

			if (_level[0] < 1) _structure[7].needBuilding = true;
			else _structure[7].needBuilding = false;

			switch (_hall)
			{
			case 1:
				if (_pub < 1) _structure[0].needBuilding = true;
				else _structure[0].needBuilding = false;
				break;
			case 2:
				if (_market < 1 || _forge < 1 || _guild < 1) _structure[0].needBuilding = true;
				else _structure[0].needBuilding = false;
				break;
			case 3:
				if (_fort < 3) _structure[0].needBuilding = true;
				else _structure[0].needBuilding = false;
				break;
			}

		break;
	
		case CAMP_DUNGEON:
			if (_fort < 1) _structure[9].needBuilding = true;
			else _structure[9].needBuilding = false;

			if (_level[0] < 1)
			{
				_structure[10].needBuilding = true;
				_structure[11].needBuilding = true;
			}
			else
			{
				_structure[10].needBuilding = false;
				_structure[11].needBuilding = false;
			}

			if (_level[1] < 1 || _level[2] < 1) _structure[12].needBuilding = true;
			else _structure[12].needBuilding = false;

			if (_level[3] < 1)
			{
				_structure[13].needBuilding = true;
				_structure[14].needBuilding = true;
			}
			else
			{
				_structure[13].needBuilding = false;
				_structure[14].needBuilding = false;
			}

			switch (_level[6])
			{
			case 0:

				if (_level[5] < 1 || _level[4] < 1 || _guild < 2) _structure[15].needBuilding = true;
				else _structure->needBuilding = false;

			break;

			case 1:

				if (_guild < 3) _structure[15].needBuilding = true;
				else _structure[15].needBuilding = false;

			break;
			}

			if (_special[0] < 1) _structure[17].needBuilding = true;
			else _structure[17].needBuilding = false;

			if (_guild < 1) _structure[6].needBuilding = true;
			else _structure[6].needBuilding = false;

			if (_market < 1) _structure[7].needBuilding = true;
			else _structure[7].needBuilding = false;

			switch (_hall)
			{
			case 0:


			break;

			if (_pub < 1) _structure[0].needBuilding = true;
			else _structure[0].needBuilding = false;

			case 1:

				if (_market < 1 || _forge < 1 || _guild < 1) _structure[0].needBuilding = true;
				else _structure[0].needBuilding = false;

			break;

			case 2:

				if (_fort < 3) _structure[0].needBuilding = true;
				else _structure[0].needBuilding = false;

			break;
			}








		break;
		}


		




		for (int i = 0; i < 18; i++)
		{
			if (_structure[i].wood <= _property.wood &&
				_structure[i].iron <= _property.iron &&
				_structure[i].crystal <= _property.crystal &&
				_structure[i].mercury <= _property.mercury &&
				_structure[i].sulfur <= _property.sulfur &&
				_structure[i].gold <= _property.gold &&
				_structure[i].gem <= _property.gem)
			{
				_structure[i].needResources = false;
				_structure[i].index = 0;
			}
			else
			{
				_structure[i].index = 1;
				_structure[i].needResources = true;
			}

			if (_structure[i].needBuilding || _structure[i].needResources) _structure[i].index = 1;
			else _structure[i].index = 0;

		}

	}
	else
	{
		for (int i = 0; i < 18; i++)
		{
			_structure[i].index = 1;

		}

	}

	//============================================



	

	//================== ���̻� ������ ������

	if (_hall >= 4) _structure[0].index = 2;
	if (_fort >= 3) _structure[1].index = 2;
	for (int i = 0; i < 7; i++)
	{
		if (_level[i] >= 2) _structure[9 + i].index = 2;
	}
	if (_forge >= 1)_structure[3].index = 2;
	if (_market >= 2) _structure[4].index = 2;
	switch (_camp)
	{
	case CAMP_CASTLE:
		if (_guild >= 4) _structure[5].index = 2;
		if (_special[0] >= 1) _structure[8].index = 2;
		_structure[6].index = 3;
		if (_special[2] >= 1) _structure[7].index = 2;
		if (_special[3] >= 1) _structure[2].index = 2;
		break;
	case CAMP_DUNGEON:
		if (_guild >= 5) _structure[5].index = 2;
		if (_pub >= 1) _structure[2].index = 2;
		if (_special[0] >= 1) _structure[17].index = 2;
		if (_special[1] >= 1) _structure[9].index = 2;
		if (_special[2] >= 1) _structure[6].index = 2;
		if (_special[3] >= 1) _structure[8].index = 2;
		if (_special[4] >= 1) _structure[16].index = 2;

		break;
	}

	










}

void camp::recruitInit(void)
{
	for (int i = 0; i < 7; i++)
	{
		ZeroMemory(&_recruit[i], sizeof(tagRecruit));
		_recruit[i].num = i;
		if (i != 6)
		{
			_recruit[i].x = 10 + (i % 2) * 394;
			_recruit[i].y = 22 + (i / 2) * 133;
		}
		else
		{
			_recruit[i].x = 206;
			_recruit[i].y = 421;

			// ������� 386 * 126
		}
	}
	switch (_camp)
	{
	case CAMP_CASTLE:
		if (_level[0] == 1)
		{
			sprintf(_recruit[0].unit, "â��");
			sprintf(_recruit[0].building, "������");
			
			

		}
		else if (_level[0] == 2)
		{
			sprintf(_recruit[0].unit, "���� â��");
			sprintf(_recruit[0].building, "���� ������");

		}

		if (_level[1] == 1)
		{
			sprintf(_recruit[1].unit, "�ü�");
			sprintf(_recruit[1].building, "�ü��ʼ�");

		}
		else if (_level[1] == 2)
		{
			sprintf(_recruit[1].unit, "���ݼ�");
			sprintf(_recruit[1].building, "���� �ü��ʼ�");

		}
		if (_level[2] == 1)
		{
			sprintf(_recruit[2].unit, "�׸���");
			sprintf(_recruit[2].building, "�׸��� Ÿ��");

		}
		else if (_level[2] == 2)
		{
			sprintf(_recruit[2].unit, "�ο� �׸���");
			sprintf(_recruit[2].building, "���� �׸��� Ÿ��");

		}
		if (_level[3] == 1)
		{
			sprintf(_recruit[3].unit, "�˻�");
			sprintf(_recruit[3].building, "����");

		}
		else if (_level[3] == 2)
		{
			sprintf(_recruit[3].unit, "ũ�缼�̴�");
			sprintf(_recruit[3].building, "���� ����");
							 
		}
		if (_level[4] == 1)
		{
			sprintf(_recruit[4].unit, "������");
			sprintf(_recruit[4].building, "������");

		}
		else if (_level[4] == 2)
		{
			sprintf(_recruit[4].unit, "���� ������");
			sprintf(_recruit[4].building, "���� ������");


		}
		if (_level[5] == 1)
		{
			sprintf(_recruit[5].unit, "����");
			sprintf(_recruit[5].building, "������");

		}
		else if (_level[5] == 2)
		{
			sprintf(_recruit[5].unit, "è�Ǿ�");
			sprintf(_recruit[5].building, "���� ������");

		}
		if (_level[6] == 1)
		{
			sprintf(_recruit[6].unit, "õ��");
			sprintf(_recruit[6].building, "õ���� ��");

		}
		else if (_level[6] == 2)
		{
			sprintf(_recruit[6].unit, "��õ��");
			sprintf(_recruit[6].building, "���� õ���� ��");

		}

		break;
	case CAMP_DUNGEON:

		if (_level[0] == 1)
		{
			sprintf(_recruit[0].unit, "������");
			sprintf(_recruit[0].building, "������");



		}
		else if (_level[0] == 2)
		{
			sprintf(_recruit[0].unit, "������ ������");
			sprintf(_recruit[0].building, "���� ������");

		}

		if (_level[1] == 1)
		{
			sprintf(_recruit[1].unit, "����");
			sprintf(_recruit[1].building, "���� ����");

		}
		else if (_level[1] == 2)
		{
			sprintf(_recruit[1].unit, "���Ǹ���");
			sprintf(_recruit[1].building, "���� ���� ����");

		}
		if (_level[2] == 1)
		{
			sprintf(_recruit[2].unit, "�ֽ���");
			sprintf(_recruit[2].building, "�ֽ��� ���");

		}
		else if (_level[2] == 2)
		{
			sprintf(_recruit[2].unit, "�Ǹ��� ��");
			sprintf(_recruit[2].building, "���� �ֽ��� ���");

		}
		if (_level[3] == 1)
		{
			sprintf(_recruit[3].unit, "�޵λ�");
			sprintf(_recruit[3].building, "ħ���� ȸ��");

		}
		else if (_level[3] == 2)
		{
			sprintf(_recruit[3].unit, "�޵λ� ��");
			sprintf(_recruit[3].building, "���� ħ���� ȸ��");

		}
		if (_level[4] == 1)
		{
			sprintf(_recruit[4].unit, "�̳�Ÿ�츣��");
			sprintf(_recruit[4].building, "�̱�");

		}
		else if (_level[4] == 2)
		{
			sprintf(_recruit[4].unit, "�̳�Ÿ�츣�� ŷ");
			sprintf(_recruit[4].building, "���� �̱�");


		}
		if (_level[5] == 1)
		{
			sprintf(_recruit[5].unit, "��Ƽ�ھ�");
			sprintf(_recruit[5].building, "��Ƽ�ھ� ����");

		}
		else if (_level[5] == 2)
		{
			sprintf(_recruit[5].unit, "�������ھ�");
			sprintf(_recruit[5].building, "���� ��Ƽ�ھ� ����");

		}
		if (_level[6] == 1)
		{
			sprintf(_recruit[6].unit, "���� �巡��");
			sprintf(_recruit[6].building, "�巡�� ����");

		}
		else if (_level[6] == 2)
		{
			sprintf(_recruit[6].unit, "�� �巡��");
			sprintf(_recruit[6].building, "���� �巡�� ����");

		}

		break;
	}

}

void camp::structureInit(void)
{
	for (int i = 0; i < 18; i++)
	{
		ZeroMemory(&_structure[i], sizeof(tagStructure));
		_structure[i].checkImg = IMAGEMANAGER->findImage("hall_color");
		_structure[i].num = i;
	}

	switch (_camp)
	{
	case CAMP_CASTLE:
		for (int i = 0; i < 4; i++)
		{
			_structure[i].y = 37;
			_structure[i].x = 34 + 194 * i;
		}
		for (int i = 4; i < 7; i++)
		{
			_structure[i].y = 141;
			_structure[i].x = 131 + 194 * (i - 4);
		}
		for (int i = 7; i < 9; i++)
		{
			_structure[i].y = 245;
			_structure[i].x = 228 + 194 * (i - 7);
		}
		for (int i = 9; i < 13; i++)
		{
			_structure[i].y = 349;
			_structure[i].x = 34 + 194 * (i - 9);
		}
		for (int i = 13; i < 16; i++)
		{
			_structure[i].y = 453;
			_structure[i].x = 131 + 194 * (i - 13);
		}




		//========== Ȧ
		switch (_hall)
		{
		case 0:
			sprintf(_structure[0].name, "����ȸ��");
			sprintf(_structure[0].explantion, "����ȸ���� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 500�� �����Ѵ�.");
			_structure[0].img = IMAGEMANAGER->findImage("Chall_hall1");

			break;
		case 1:
			sprintf(_structure[0].name, "�ù�ȸ��");
			sprintf(_structure[0].explantion, "�ù�ȸ���� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 1000�� �����Ѵ�.");
			sprintf(_structure[0].needBuild, "������");
			_structure[0].img = IMAGEMANAGER->findImage("Chall_hall2");
			_structure[0].gold = 2500;
			break;
		case 2:
			sprintf(_structure[0].name, "��û");
			sprintf(_structure[0].explantion, "��û�� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 2000�� �����Ѵ�.");
			sprintf(_structure[0].needBuild, "����, ���尣, ������� 1����");
			_structure[0].img = IMAGEMANAGER->findImage("Chall_hall3");
			_structure[0].gold = 5000;
			break;
		case 3:
			sprintf(_structure[0].name, "�ǻ��");
			sprintf(_structure[0].explantion, "�ǻ���� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 4000�� �����Ѵ�.");
			sprintf(_structure[0].needBuild, "��");
			_structure[0].img = IMAGEMANAGER->findImage("Chall_hall4");
			_structure[0].gold = 10000;
			break;
		default:
			sprintf(_structure[0].name, "�ǻ��");
			sprintf(_structure[0].explantion, "�ǻ���� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 4000�� �����Ѵ�.");
			_structure[0].img = IMAGEMANAGER->findImage("Chall_hall4");
			_structure[0].gold = 10000;
			break;
		}

		switch (_fort)
		{
		case 0:
			sprintf(_structure[1].name, "����");
			sprintf(_structure[1].explantion, "���縦 �Ǽ��ϸ� ������ ��ֹ��� ��ġ�Ǿ� ������ ���� ����Ѵ�.");
			_structure[1].img = IMAGEMANAGER->findImage("Chall_fort1");
			_structure[1].gold = 5000;
			_structure[1].wood = 20;
			_structure[1].iron = 20;
			break;
		case 1:
			sprintf(_structure[1].name, "��ä");
			sprintf(_structure[1].explantion, "��ä�� �Ǽ��ϸ� �⺻������ ������� 50% ���ǰ�, ������ ��ֹ��� ��ġ�Ǿ� ������ ���� ����Ѵ�.");
			_structure[1].img = IMAGEMANAGER->findImage("Chall_fort2");
			_structure[1].gold = 2500;
			_structure[1].iron = 5;
			break;
		case 2:
			sprintf(_structure[1].name, "��");
			sprintf(_structure[1].explantion, "���� �Ǽ��ϸ� �⺻������ ������� 50% ���ǰ�, ������ ��ֹ��� ��ġ�Ǿ� ������ ���� ����Ѵ�.");
			_structure[1].img = IMAGEMANAGER->findImage("Chall_fort3");
			_structure[1].gold = 5000;
			_structure[1].iron = 10;
			_structure[1].wood = 10;
			break;
		default:
			sprintf(_structure[1].name, "��");
			sprintf(_structure[1].explantion, "���� �Ǽ��ϸ� �⺻������ ������� 50% ���ǰ�, ������ ��ֹ��� ��ġ�Ǿ� ������ ���� ����Ѵ�.");
			_structure[1].img = IMAGEMANAGER->findImage("Chall_fort3");
			_structure[1].gold = 5000;
			_structure[1].iron = 10;
			_structure[1].wood = 10;
			break;
		}

		switch (_pub)
		{
		case 0:
			sprintf(_structure[2].name, "������");
			sprintf(_structure[2].explantion, "�������� ���������� ���δ��� ��⸦ �����ش�.");
			_structure[2].img = IMAGEMANAGER->findImage("Chall_pub1");
			_structure[2].gold = 500;
			_structure[2].wood = 5;
			break;
		case 1:
			sprintf(_structure[2].name, "�˻���ȸ");
			sprintf(_structure[2].explantion, "���������� ������ ��� +2");
			_structure[2].img = IMAGEMANAGER->findImage("Chall_pub2");
			_structure[2].gold = 500;
			_structure[2].wood = 5;
			break;
		default:
			sprintf(_structure[2].name, "�˻���ȸ");
			sprintf(_structure[2].explantion, "���������� ������ ��� +2");
			_structure[2].img = IMAGEMANAGER->findImage("Chall_pub2");
			_structure[2].gold = 500;
			_structure[2].wood = 5;
			break;
		}

		sprintf(_structure[3].name, "���尣");
		sprintf(_structure[3].explantion, "���尣�� ����� �δ뿡 ����� �������ش�.");
		_structure[3].img = IMAGEMANAGER->findImage("Chall_forge");
		_structure[3].gold = 1000;
		_structure[3].wood = 5;

		switch (_market)
		{
		case 0:
			sprintf(_structure[4].name, "����");
			sprintf(_structure[4].explantion, "������ ���� �������� ������ �����ϰ� ���ش�.(������ ���� �������� �ŷ������ �����ȴ�.)");
			_structure[4].img = IMAGEMANAGER->findImage("Chall_market1");
			_structure[4].gold = 500;
			_structure[4].wood = 5;

		break;

		case 1:
			sprintf(_structure[4].name, "�ڿ�â��");
			sprintf(_structure[4].explantion, "���� ����� ö���� +1");
			_structure[4].img = IMAGEMANAGER->findImage("Chall_market2");
			_structure[4].gold = 5000;
			_structure[4].iron = 5;

		break;

		default:
			sprintf(_structure[4].name, "�ڿ�â��");
			sprintf(_structure[4].explantion, "���� ����� ö���� +1");
			_structure[4].img = IMAGEMANAGER->findImage("Chall_market2");
			_structure[4].gold = 5000;
			_structure[4].iron = 5;

		break;
		}

		switch (_guild)
		{
		case 0:
			sprintf(_structure[5].name, "������� 1����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Chall_guild1");
			_structure[5].gold = 2000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;

			break;

		case 1:
			sprintf(_structure[5].name, "������� 2����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Chall_guild2");
			_structure[5].gold = 1000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;
			_structure[5].mercury = 4;
			_structure[5].crystal = 4;
			_structure[5].sulfur = 4;
			_structure[5].gem = 4;

			break;

		case 2:
			sprintf(_structure[5].name, "������� 3����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Chall_guild3");
			_structure[5].gold = 1000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;
			_structure[5].mercury = 6;
			_structure[5].crystal = 6;
			_structure[5].sulfur = 6;
			_structure[5].gem = 6;


			break;

		default:
			sprintf(_structure[5].name, "������� 4����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Chall_guild4");
			_structure[5].gold = 1000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;
			_structure[5].mercury = 8;
			_structure[5].crystal = 8;
			_structure[5].sulfur = 8;
			_structure[5].gem = 8;

			break;
		}

		sprintf(_structure[6].name, "������");
		sprintf(_structure[6].explantion, "�����ҿ����� �踦 ������ �� �ִ�.");
		_structure[6].img = IMAGEMANAGER->findImage("Chall_dock");
		_structure[6].gold = 2000;
		_structure[6].wood = 20;

		sprintf(_structure[7].name, "������");
		sprintf(_structure[7].explantion, "�����ҿ����� �踦 ������ �� �ִ�.");
		sprintf(_structure[7].needBuild, "����");
		_structure[7].img = IMAGEMANAGER->findImage("Chall_stable");
		_structure[7].gold = 2000;
		_structure[7].wood = 10;


		sprintf(_structure[8].name, "�׸��� ��ä");
		sprintf(_structure[8].explantion, "�׸����� ������ +3");
		sprintf(_structure[8].needBuild, "�׸��� Ÿ��");
		_structure[8].gold = 2000;
		_structure[8].wood = 10;
		if (_level[2] == 0) _structure[8].img = IMAGEMANAGER->findImage("Chall_tower3");
		else _structure[8].img = IMAGEMANAGER->findImage("Chall_tower4");

		if (_level[0] == 0)
		{
			sprintf(_structure[9].name, "������");
			sprintf(_structure[9].explantion, "â�� ����");
			sprintf(_structure[9].needBuild, "����");
			_structure[9].gold = 500;
			_structure[9].iron = 10;
			_structure[9].img = IMAGEMANAGER->findImage("Chall_pike1");	
		}
		else
		{
			sprintf(_structure[9].name, "���� ������");
			sprintf(_structure[9].explantion, "����â�� ����");
			_structure[9].gold = 1000;
			_structure[9].iron = 5;
			_structure[9].img = IMAGEMANAGER->findImage("Chall_pike2");

		}
		if (_level[1] == 0)
		{
			sprintf(_structure[10].name, "�ü��ʼ�");
			sprintf(_structure[10].explantion, "�ü� ����");
			_structure[10].gold = 1000;
			_structure[10].iron = 5;
			_structure[10].wood = 5;
			_structure[10].img = IMAGEMANAGER->findImage("Chall_archer1");
		}
		else
		{
			sprintf(_structure[10].name, "���� �ü��ʼ�");
			sprintf(_structure[10].explantion, "���ݼ� ����");
			_structure[10].gold = 1000;
			_structure[10].iron = 5;
			_structure[10].wood = 5;
			_structure[10].img = IMAGEMANAGER->findImage("Chall_archer2");

		}

		if (_level[2] == 0)
		{
			sprintf(_structure[11].name, "�׸��� Ÿ��");
			sprintf(_structure[11].explantion, "�׸��� ����");
			sprintf(_structure[11].needBuild, "����");
			_structure[11].gold = 1000;
			_structure[11].iron = 5;
			_structure[11].img = IMAGEMANAGER->findImage("Chall_tower1");
		}
		else
		{
			sprintf(_structure[11].name, "���� �׸��� Ÿ��");
			sprintf(_structure[11].explantion, "�ο� �׸��� ����");
			_structure[11].gold = 1000;
			_structure[11].iron = 5;
			_structure[11].img = IMAGEMANAGER->findImage("Chall_tower2");
		}
		if (_level[3] == 0)
		{
			sprintf(_structure[12].name, "����");
			sprintf(_structure[12].explantion, "�˻� ����");
			sprintf(_structure[12].needBuild, "���尣");
			_structure[12].gold = 2000;
			_structure[12].iron = 5;
			_structure[12].img = IMAGEMANAGER->findImage("Chall_cru1");
		}
		else
		{
			sprintf(_structure[12].name, "���� ����");
			sprintf(_structure[12].explantion, "ũ�缼�̴� ����");
			_structure[12].gold = 2000;
			_structure[12].iron = 5;
			_structure[12].crystal = 5;
			_structure[12].img = IMAGEMANAGER->findImage("Chall_cru2");
		}
		if (_level[4] == 0)
		{
			sprintf(_structure[13].name, "������");
			sprintf(_structure[13].explantion, "������ ����");
			sprintf(_structure[13].needBuild, "����, ���� ��� 1����");
			_structure[13].img = IMAGEMANAGER->findImage("Chall_abbey1");
			_structure[13].gold = 3000;
			_structure[13].iron = 5;
			_structure[13].wood = 5;
			_structure[13].crystal = 2;
			_structure[13].gem= 2;
			_structure[13].sulfur = 2;
			_structure[13].mercury = 2;
		}
		else
		{
			sprintf(_structure[13].name, "���� ������");
			sprintf(_structure[13].explantion, "���� ������ ����");
			_structure[13].img = IMAGEMANAGER->findImage("Chall_abbey2");
			_structure[13].gold = 1000;
			_structure[13].iron = 5;
			_structure[13].wood = 5;
			_structure[13].crystal = 2;
			_structure[13].gem = 2;
			_structure[13].sulfur = 2;
			_structure[13].mercury = 2;
		}
		if (_level[5] == 0)
		{
			sprintf(_structure[14].name, "������");
			sprintf(_structure[14].explantion, "���� ����");
			sprintf(_structure[14].needBuild, "����, ������");
			_structure[14].img = IMAGEMANAGER->findImage("Chall_caval1");
			_structure[14].gold = 5000;
			_structure[14].wood = 20;
		}
		else
		{
			sprintf(_structure[14].name, "���� ������");
			sprintf(_structure[14].explantion, "è�Ǿ� ����");
			_structure[14].img = IMAGEMANAGER->findImage("Chall_caval2");
			_structure[14].gold = 3000;
			_structure[14].wood = 10;
		}
		if (_level[6] == 0)
		{
			sprintf(_structure[15].name, "õ���� ��");
			sprintf(_structure[15].explantion, "õ�� ����");
			sprintf(_structure[15].needBuild, "����, ������");
			_structure[15].img = IMAGEMANAGER->findImage("Chall_door1");
			_structure[15].gold = 20000;
			_structure[15].sulfur = 10;
			_structure[15].mercury = 10;
			_structure[15].gem = 10;
			_structure[15].crystal = 10;
		}
		else
		{
			sprintf(_structure[15].name, "���� õ���� ��");
			sprintf(_structure[15].explantion, "��õ�� ����");
			_structure[15].img = IMAGEMANAGER->findImage("Chall_door2");
			_structure[15].gold = 20000;
			_structure[15].sulfur = 10;
			_structure[15].mercury = 10;
			_structure[15].gem = 10;
			_structure[15].crystal = 10;
		}

		break;
	case CAMP_DUNGEON:
		for (int i = 0; i < 4; i++)
		{
			_structure[i].y = 37;
			_structure[i].x = 34 + 194 * i;
		}
		for (int i = 4; i < 7; i++)
		{
			_structure[i].y = 141;
			_structure[i].x = 34 + 194 * (i - 4);
		}
		for (int i = 7; i < 9; i++)
		{
			_structure[i].y = 245;
			_structure[i].x = 131 + 194 * (i - 7);
		}
		for (int i = 9; i < 13; i++)
		{
			_structure[i].y = 349;
			_structure[i].x = 34 + 194 * (i - 9);
		}
		for (int i = 13; i < 16; i++)
		{
			_structure[i].y = 453;
			_structure[i].x = 131 + 194 * (i - 13);
		}
		_structure[16].x = 616;
		_structure[16].y = 141;
		_structure[17].x = 519;
		_structure[17].y = 245;


		switch (_hall)
		{
		case 0:
			sprintf(_structure[0].name, "����ȸ��");
			sprintf(_structure[0].explantion, "����ȸ���� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 500�� �����Ѵ�.");
			_structure[0].img = IMAGEMANAGER->findImage("Dhall_hall1");

			break;
		case 1:
			sprintf(_structure[0].name, "�ù�ȸ��");
			sprintf(_structure[0].explantion, "�ù�ȸ���� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 1000�� �����Ѵ�.");
			sprintf(_structure[0].needBuild, "������");
			_structure[0].img = IMAGEMANAGER->findImage("Dhall_hall2");
			_structure[0].gold = 2500;
			break;
		case 2:
			sprintf(_structure[0].name, "��û");
			sprintf(_structure[0].explantion, "��û�� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 2000�� �����Ѵ�.");
			sprintf(_structure[0].needBuild, "����, ���尣, ���� ��� 1����");
			_structure[0].img = IMAGEMANAGER->findImage("Dhall_hall3");
			_structure[0].gold = 5000;
			break;
		case 3:
			sprintf(_structure[0].name, "�ǻ��");
			sprintf(_structure[0].explantion, "�ǻ���� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 4000�� �����Ѵ�.");
			sprintf(_structure[0].needBuild, "��");
			_structure[0].img = IMAGEMANAGER->findImage("Dhall_hall4");
			_structure[0].gold = 10000;
			break;
		default:
			sprintf(_structure[0].name, "�ǻ��");
			sprintf(_structure[0].explantion, "�ǻ���� ������ �پ��� �ǹ����� �Ǽ��� �� �ְ� ���ָ�, ���� �� 4000�� �����Ѵ�.");
			_structure[0].img = IMAGEMANAGER->findImage("Dhall_hall4");
			_structure[0].gold = 10000;
			break;
		}

		switch (_fort)
		{
		case 0:
			sprintf(_structure[1].name, "����");
			sprintf(_structure[1].explantion, "���縦 �Ǽ��ϸ� ������ ��ֹ��� ��ġ�Ǿ� ������ ���� ����Ѵ�.");
			_structure[1].img = IMAGEMANAGER->findImage("Dhall_fort1");
			_structure[1].gold = 5000;
			_structure[1].wood = 20;
			_structure[1].iron = 20;
			break;
		case 1:
			sprintf(_structure[1].name, "��ä");
			sprintf(_structure[1].explantion, "��ä�� �Ǽ��ϸ� �⺻������ ������� 50% ���ǰ�, ������ ��ֹ��� ��ġ�Ǿ� ������ ���� ����Ѵ�.");
			_structure[1].img = IMAGEMANAGER->findImage("Dhall_fort2");
			_structure[1].gold = 2500;
			_structure[1].iron = 5;
			break;
		case 2:
			sprintf(_structure[1].name, "��");
			sprintf(_structure[1].explantion, "���� �Ǽ��ϸ� �⺻������ ������� 50% ���ǰ�, ������ ��ֹ��� ��ġ�Ǿ� ������ ���� ����Ѵ�.");
			_structure[1].img = IMAGEMANAGER->findImage("Dhall_fort3");
			_structure[1].gold = 5000;
			_structure[1].iron = 10;
			_structure[1].wood = 10;
			break;
		default:
			sprintf(_structure[1].name, "��");
			sprintf(_structure[1].explantion, "���� �Ǽ��ϸ� �⺻������ ������� 50% ���ǰ�, ������ ��ֹ��� ��ġ�Ǿ� ������ ���� ����Ѵ�.");
			_structure[1].img = IMAGEMANAGER->findImage("Dhall_fort3");
			_structure[1].gold = 5000;
			_structure[1].iron = 10;
			_structure[1].wood = 10;
			break;
		}

		sprintf(_structure[2].name, "������");
		sprintf(_structure[2].explantion, "�������� ���������� ���δ��� ��⸦ �����ش�.");
		_structure[2].img = IMAGEMANAGER->findImage("Dhall_pub");
		_structure[2].gold = 500;
		_structure[2].wood = 5;

		sprintf(_structure[3].name, "���尣");
		sprintf(_structure[3].explantion, "���尣�� ����� �δ뿡 ����� �������ش�.");
		_structure[3].img = IMAGEMANAGER->findImage("Dhall_forge");
		_structure[3].gold = 1000;
		_structure[3].wood = 5;

		switch (_market)
		{
		case 0:
			sprintf(_structure[4].name, "����");
			sprintf(_structure[4].explantion, "������ ���� �������� ������ �����ϰ� ���ش�.(������ ���� �������� �ŷ������ �����ȴ�.)");
			_structure[4].img = IMAGEMANAGER->findImage("Dhall_market1");
			_structure[4].gold = 500;
			_structure[4].wood = 5;

			break;

		default:
			sprintf(_structure[4].name, "�ڿ�â��");
			sprintf(_structure[4].explantion, "���� ��Ȳ +1");
			_structure[4].img = IMAGEMANAGER->findImage("Dhall_market2");
			_structure[4].gold = 5000;
			_structure[4].iron = 5;

			break;
		}

		switch (_guild)
		{
		case 0:
			sprintf(_structure[5].name, "������� 1����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Dhall_guild1");
			_structure[5].gold = 2000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;

			break;

		case 1:
			sprintf(_structure[5].name, "������� 2����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Dhall_guild2");
			_structure[5].gold = 1000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;
			_structure[5].mercury = 4;
			_structure[5].crystal = 4;
			_structure[5].sulfur = 4;
			_structure[5].gem = 4;

			break;

		case 2:
			sprintf(_structure[5].name, "������� 3����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Dhall_guild3");
			_structure[5].gold = 1000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;
			_structure[5].mercury = 6;
			_structure[5].crystal = 6;
			_structure[5].sulfur = 6;
			_structure[5].gem = 6;


			break;
		case 3:
			sprintf(_structure[5].name, "������� 4����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Dhall_guild4");
			_structure[5].gold = 1000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;
			_structure[5].mercury = 8;
			_structure[5].crystal = 8;
			_structure[5].sulfur = 8;
			_structure[5].gem = 8;

			break;

		default:
			sprintf(_structure[5].name, "������� 5����");
			sprintf(_structure[5].explantion, "���� ��忡 �� ������ �װ��� ���ϵ� ������ ���� �ȴ�.");
			_structure[5].img = IMAGEMANAGER->findImage("Dhall_guild5");
			_structure[5].gold = 1000;
			_structure[5].iron = 5;
			_structure[5].wood = 5;
			_structure[5].mercury = 10;
			_structure[5].crystal = 10;
			_structure[5].sulfur = 10;
			_structure[5].gem = 10;

			break;
		}

		sprintf(_structure[6].name, "���� �ҿ뵹��");
		sprintf(_structure[6].explantion, "�Ͻ������� ����볪 �湮�ϴ� ������ ���� ������ 2��� ����");
		sprintf(_structure[6].needBuild, "���� ��� 1����");
		_structure[6].img = IMAGEMANAGER->findImage("Dhall_cloud");
		_structure[6].gold = 1000;

		sprintf(_structure[7].name, "��Ƽ��Ʈ ����");
		sprintf(_structure[7].explantion, "�پ��� ��Ƽ��Ʈ ���� ����.");
		sprintf(_structure[7].needBuild, "����");
		_structure[7].img = IMAGEMANAGER->findImage("Dhall_arti");
		_structure[7].gold = 10000;


		sprintf(_structure[8].name, "���� ��ī����");
		sprintf(_structure[8].explantion, "�湮�ϴ� ������ ����ġ +1000(�Ѹ�� �ѹ�����)");
		_structure[8].gold = 1000;
		_structure[8].wood = 5;
		_structure[8].iron = 5;
		_structure[8].img = IMAGEMANAGER->findImage("Dhall_academy");

		if (_level[0] == 0)
		{
			sprintf(_structure[9].name, "������");
			sprintf(_structure[9].explantion, "������ ����");
			sprintf(_structure[9].needBuild, "����");
			_structure[9].gold = 400;
			_structure[9].wood = 10;
			_structure[9].img = IMAGEMANAGER->findImage("Dhall_farm1");
		}
		else
		{
			sprintf(_structure[9].name, "���� ������");
			sprintf(_structure[9].explantion, "������ ������ ����");
			_structure[9].gold = 1000;
			_structure[9].wood = 5;
			_structure[9].img = IMAGEMANAGER->findImage("Dhall_farm2");

		}
		if (_level[1] == 0)
		{
			sprintf(_structure[10].name, "���� ����");
			sprintf(_structure[10].explantion, "���� ����");
			sprintf(_structure[10].needBuild, "������");
			_structure[10].img = IMAGEMANAGER->findImage("Dhall_nest1");
			_structure[10].gold = 1000;
		}
		else
		{
			sprintf(_structure[10].name, "���� ���� ����");
			sprintf(_structure[10].explantion, "���� ���� ����");
			_structure[10].gold = 1000;
			_structure[10].img = IMAGEMANAGER->findImage("Dhall_nest2");
			_structure[10].mercury = 2;
			_structure[10].sulfur = 2;

		}

		if (_level[2] == 0)
		{
			sprintf(_structure[11].name, "�ֽ��� ���");
			sprintf(_structure[11].explantion, "�ֽ��� ����");
			sprintf(_structure[11].needBuild, "������");
			_structure[11].gold = 1000;
			_structure[11].iron = 1;
			_structure[11].wood = 1;
			_structure[11].sulfur = 1;
			_structure[11].mercury = 1;
			_structure[11].gem = 1;
			_structure[11].crystal = 1;
			_structure[11].img = IMAGEMANAGER->findImage("Dhall_pillar1");
		}
		else
		{
			sprintf(_structure[11].name, "���� �ֽ��� ���");
			sprintf(_structure[11].explantion, "�Ǹ��� �� ����");
			_structure[11].gold = 1000;
			_structure[11].iron = 1;
			_structure[11].wood = 1;
			_structure[11].sulfur = 1;
			_structure[11].mercury = 1;
			_structure[11].gem = 1;
			_structure[11].crystal = 1;
			_structure[11].img = IMAGEMANAGER->findImage("Dhall_pillar2");
		}
		if (_level[3] == 0)
		{
			sprintf(_structure[12].name, "ħ���� ȸ��");
			sprintf(_structure[12].explantion, "�޵λ� ����");
			sprintf(_structure[12].needBuild, "���� ���� , �ֽ��� ���");
			_structure[12].gold = 2000;
			_structure[12].wood = 5;
			_structure[12].iron = 10;
			_structure[12].img = IMAGEMANAGER->findImage("Dhall_temple1");
		}
		else
		{
			sprintf(_structure[12].name, "���� ħ���� ȸ��");
			sprintf(_structure[12].explantion, "�޵λ� ���� ����");
			_structure[12].gold = 1500;
			_structure[12].wood = 5;
			_structure[12].img = IMAGEMANAGER->findImage("Dhall_temple2");
		}
		if (_level[4] == 0)
		{
			sprintf(_structure[13].name, "�̱�");
			sprintf(_structure[13].explantion, "�̳�Ÿ�츣�� ����");
			sprintf(_structure[13].needBuild, "ħ���� ȸ��");
			_structure[13].img = IMAGEMANAGER->findImage("Dhall_maze1");
			_structure[13].gold = 4000;
			_structure[13].iron = 10;
			_structure[13].gem = 10;
		}
		else
		{
			sprintf(_structure[13].name, "���� �̱�");
			sprintf(_structure[13].explantion, "�̳�Ÿ�츣�� ŷ ����");
			_structure[13].img = IMAGEMANAGER->findImage("Dhall_maze2");
			_structure[13].gold = 3000;
			_structure[13].iron = 5;
			_structure[13].gem = 5;
		}
		if (_level[5] == 0)
		{
			sprintf(_structure[14].name, "��Ƽ�ھ� ����");
			sprintf(_structure[14].explantion, "��Ƽ�ھ� ����");
			sprintf(_structure[14].needBuild, "ħ���� ȸ��");
			_structure[14].img = IMAGEMANAGER->findImage("Dhall_mant1");
			_structure[14].gold = 5000;
			_structure[14].wood = 5;
			_structure[14].iron = 5;
			_structure[14].sulfur = 5;
			_structure[14].mercury = 5;
		}
		else
		{
			sprintf(_structure[14].name, "���� ��Ƽ�ھ� ����");
			sprintf(_structure[14].explantion, "�����ǿ� ����");
			_structure[14].img = IMAGEMANAGER->findImage("Dhall_mati2");
			_structure[14].gold = 3000;
			_structure[14].wood = 5;
			_structure[14].iron = 5;
			_structure[14].sulfur = 5;
			_structure[14].mercury = 5;
		}
		if (_level[6] == 0)
		{
			sprintf(_structure[15].name, "�巡�� ����");
			sprintf(_structure[15].explantion, "���� �巡�� ����");
			sprintf(_structure[15].needBuild, "�̱�, ��Ƽ�ھ� ����, ������� 2����");
			_structure[15].img = IMAGEMANAGER->findImage("Dhall_drag1");
			_structure[15].gold = 15000;
			_structure[15].iron = 15;
			_structure[15].wood = 15;
			_structure[15].sulfur = 20;
		}
		else
		{
			sprintf(_structure[15].name, "���� �巡�� ����");
			sprintf(_structure[15].explantion, "�� �巡�� ����");
			sprintf(_structure[15].needBuild, "������� 3����");
			_structure[15].img = IMAGEMANAGER->findImage("Dhall_drag2");
			_structure[15].gold = 15000;
			_structure[15].iron = 15;
			_structure[15].wood = 15;
			_structure[15].sulfur = 20;
		}

		sprintf(_structure[16].name, "��ȯ�� ��");
		sprintf(_structure[16].explantion, "������ �ܺ��� ���� ���������� ������ ��ȯ�� �� ����");
		_structure[16].img = IMAGEMANAGER->findImage("Dhall_port");
		_structure[16].gold = 2500;
		_structure[16].iron = 5;

		sprintf(_structure[17].name, "���� ��");
		sprintf(_structure[17].explantion, "������ ������ +7");
		sprintf(_structure[17].needBuild, "������");
		_structure[17].img = IMAGEMANAGER->findImage("Dhall_farm3");
		_structure[17].gold = 1000;


		break;
	}




}

void camp::cameraSetting(void)
{
	_cameraX = DATABASE->getPlayCameraX();
	_cameraY = DATABASE->getPlayCameraY();

	_cameraArr.x = _cameraX / TILESIZE;
	_cameraArr.y = _cameraY / TILESIZE;

}

void camp::changeState(image* img, int delay)
{




}

void camp::unitSampleInit(void)
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j <= STATE_END; j++)
		{
			_unitSample[i].img[j] = NULL;
		}
		_unitSample[i].state = STATE_MOVE;
		_unitSample[i].x = 100;
		_unitSample[i].y = 100;




	}



	switch (_camp)
	{
	case CAMP_CASTLE:
		//============= pikeman
		_unitSample[0].x = 158;
		_unitSample[0].y = 15;
		_unitSample[0].img[STATE_UP] = IMAGEMANAGER->findImage("pikeman_up");
		_unitSample[0].img[STATE_DOWN] = IMAGEMANAGER->findImage("pikeman_down");
		_unitSample[0].img[STATE_FRONT] = IMAGEMANAGER->findImage("pikeman_front");
		_unitSample[0].img[STATE_MOVE] = IMAGEMANAGER->findImage("pikeman_move");
		_unitSample[0].img[STATE_SELECT] = IMAGEMANAGER->findImage("pikeman_select");
		_unitSample[0].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("pikeman_up_shadow");
		_unitSample[0].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("pikeman_down_shadow");
		_unitSample[0].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("pikeman_front_shadow");
		_unitSample[0].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("pikeman_move_shadow");
		_unitSample[0].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("pikeman_select_shadow");

		//============= halberdier
		_unitSample[1].x = 158;
		_unitSample[1].y = 15;
		_unitSample[1].img[STATE_UP] = IMAGEMANAGER->findImage("halberdier_up");
		_unitSample[1].img[STATE_DOWN] = IMAGEMANAGER->findImage("halberdier_down");
		_unitSample[1].img[STATE_FRONT] = IMAGEMANAGER->findImage("halberdier_front");
		_unitSample[1].img[STATE_MOVE] = IMAGEMANAGER->findImage("halberdier_move");
		_unitSample[1].img[STATE_SELECT] = IMAGEMANAGER->findImage("halberdier_select");
		_unitSample[1].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("halberdier_up_shadow");
		_unitSample[1].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("halberdier_down_shadow");
		_unitSample[1].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("halberdier_front_shadow");
		_unitSample[1].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("halberdier_move_shadow");
		_unitSample[1].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("halberdier_select_shadow");

		//============== archer 
		_unitSample[2].x = 552;
		_unitSample[2].y = 25;
		_unitSample[2].img[STATE_UP] = IMAGEMANAGER->findImage("archer_melee");
		_unitSample[2].img[STATE_DOWN] = IMAGEMANAGER->findImage("archer_range");
		_unitSample[2].img[STATE_FRONT] = IMAGEMANAGER->findImage("archer_melee");
		_unitSample[2].img[STATE_MOVE] = IMAGEMANAGER->findImage("archer_move");
		_unitSample[2].img[STATE_SELECT] = IMAGEMANAGER->findImage("archer_select");
		_unitSample[2].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("archer_melee_shadow");
		_unitSample[2].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("archer_range_shadow");
		_unitSample[2].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("archer_melee_shadow");
		_unitSample[2].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("archer_move_shadow");
		_unitSample[2].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("archer_select_shadow");

		//=============== mask man
		_unitSample[3].x = 552;
		_unitSample[3].y = 25;
		_unitSample[3].img[STATE_UP] = IMAGEMANAGER->findImage("mask_melee");
		_unitSample[3].img[STATE_DOWN] = IMAGEMANAGER->findImage("mask_range");
		_unitSample[3].img[STATE_FRONT] = IMAGEMANAGER->findImage("mask_melee");
		_unitSample[3].img[STATE_MOVE] = IMAGEMANAGER->findImage("mask_move");
		_unitSample[3].img[STATE_SELECT] = IMAGEMANAGER->findImage("mask_select");
		_unitSample[3].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("mask_melee_shadow");
		_unitSample[3].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("mask_range_shadow");
		_unitSample[3].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("mask_melee_shadow");
		_unitSample[3].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("mask_move_shadow");
		_unitSample[3].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("mask_select_shadow");





		//============= griffin
		_unitSample[4].x = 113;
		_unitSample[4].y = 138;
		_unitSample[4].img[STATE_UP] = IMAGEMANAGER->findImage("griffin_up");
		_unitSample[4].img[STATE_DOWN] = IMAGEMANAGER->findImage("griffin_down");
		_unitSample[4].img[STATE_FRONT] = IMAGEMANAGER->findImage("griffin_front");
		_unitSample[4].img[STATE_MOVE] = IMAGEMANAGER->findImage("griffin_move");
		_unitSample[4].img[STATE_SELECT] = IMAGEMANAGER->findImage("griffin_select");
		_unitSample[4].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("griffin_up_shadow");
		_unitSample[4].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("griffin_down_shadow");
		_unitSample[4].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("griffin_front_shadow");
		_unitSample[4].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("griffin_move_shadow");
		_unitSample[4].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("griffin_select_shadow");


		//============= royal griffin
		_unitSample[5].x = 108;
		_unitSample[5].y = 138;
		_unitSample[5].img[STATE_UP] = IMAGEMANAGER->findImage("royal_up");
		_unitSample[5].img[STATE_DOWN] = IMAGEMANAGER->findImage("royal_down");
		_unitSample[5].img[STATE_FRONT] = IMAGEMANAGER->findImage("royal_front");
		_unitSample[5].img[STATE_MOVE] = IMAGEMANAGER->findImage("royal_move");
		_unitSample[5].img[STATE_SELECT] = IMAGEMANAGER->findImage("royal_select");
		_unitSample[5].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("royal_up_shadow");
		_unitSample[5].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("royal_down_shadow");
		_unitSample[5].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("royal_front_shadow");
		_unitSample[5].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("royal_move_shadow");
		_unitSample[5].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("royal_select_shadow");


		//============= swordman

		_unitSample[6].x = 532;
		_unitSample[6].y = 138;
		_unitSample[6].img[STATE_UP] = IMAGEMANAGER->findImage("sword_up");
		_unitSample[6].img[STATE_DOWN] = IMAGEMANAGER->findImage("sword_down");
		_unitSample[6].img[STATE_FRONT] = IMAGEMANAGER->findImage("sword_front");
		_unitSample[6].img[STATE_MOVE] = IMAGEMANAGER->findImage("sword_move");
		_unitSample[6].img[STATE_SELECT] = IMAGEMANAGER->findImage("sword_select");
		_unitSample[6].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("sword_up_shadow");
		_unitSample[6].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("sword_down_shadow");
		_unitSample[6].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("sword_front_shadow");
		_unitSample[6].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("sword_move_shadow");
		_unitSample[6].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("sword_select_shadow");

		//============= crusader

		_unitSample[7].x = 522;
		_unitSample[7].y = 138;
		_unitSample[7].img[STATE_UP] = IMAGEMANAGER->findImage("cru_up");
		_unitSample[7].img[STATE_DOWN] = IMAGEMANAGER->findImage("cru_down");
		_unitSample[7].img[STATE_FRONT] = IMAGEMANAGER->findImage("cru_front");
		_unitSample[7].img[STATE_MOVE] = IMAGEMANAGER->findImage("cru_move");
		_unitSample[7].img[STATE_SELECT] = IMAGEMANAGER->findImage("cru_select");
		_unitSample[7].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("cru_up_shadow");
		_unitSample[7].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("cru_down_shadow");
		_unitSample[7].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("cru_front_shadow");
		_unitSample[7].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("cru_move_shadow");
		_unitSample[7].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("cru_select_shadow");

		//============= monk

		_unitSample[8].x = 158;
		_unitSample[8].y = 291;
		_unitSample[8].img[STATE_UP] = IMAGEMANAGER->findImage("monk_melee");
		_unitSample[8].img[STATE_DOWN] = IMAGEMANAGER->findImage("monk_range");
		_unitSample[8].img[STATE_FRONT] = IMAGEMANAGER->findImage("monk_melee");
		_unitSample[8].img[STATE_MOVE] = IMAGEMANAGER->findImage("monk_move");
		_unitSample[8].img[STATE_SELECT] = IMAGEMANAGER->findImage("monk_select");
		_unitSample[8].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("monk_melee_shadow");
		_unitSample[8].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("monk_range_shadow");
		_unitSample[8].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("monk_melee_shadow");
		_unitSample[8].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("monk_move_shadow");
		_unitSample[8].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("monk_select_shadow");

		//============= zealot

		_unitSample[9].x = 158;
		_unitSample[9].y = 291;
		_unitSample[9].img[STATE_UP] = IMAGEMANAGER->findImage("zealot_melee");
		_unitSample[9].img[STATE_DOWN] = IMAGEMANAGER->findImage("zealot_range");
		_unitSample[9].img[STATE_FRONT] = IMAGEMANAGER->findImage("zealot_melee");
		_unitSample[9].img[STATE_MOVE] = IMAGEMANAGER->findImage("zealot_move");
		_unitSample[9].img[STATE_SELECT] = IMAGEMANAGER->findImage("zealot_select");
		_unitSample[9].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("zealot_melee_shadow");
		_unitSample[9].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("zealot_range_shadow");
		_unitSample[9].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("zealot_melee_shadow");
		_unitSample[9].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("zealot_move_shadow");
		_unitSample[9].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("zealot_select_shadow");

		//============= cavalier

		_unitSample[10].x = 527;
		_unitSample[10].y = 281;
		_unitSample[10].img[STATE_UP] = IMAGEMANAGER->findImage("cavalier_up");
		_unitSample[10].img[STATE_DOWN] = IMAGEMANAGER->findImage("cavalier_down");
		_unitSample[10].img[STATE_FRONT] = IMAGEMANAGER->findImage("cavalier_front");
		_unitSample[10].img[STATE_MOVE] = IMAGEMANAGER->findImage("cavalier_move");
		_unitSample[10].img[STATE_SELECT] = IMAGEMANAGER->findImage("cavalier_select");
		_unitSample[10].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("cavalier_up_shadow");
		_unitSample[10].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("cavalier_down_shadow");
		_unitSample[10].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("cavalier_front_shadow");
		_unitSample[10].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("cavalier_move_shadow");
		_unitSample[10].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("cavalier_select_shadow");

		//============= champion

		_unitSample[11].x = 527;
		_unitSample[11].y = 281;
		_unitSample[11].img[STATE_UP] = IMAGEMANAGER->findImage("champion_up");
		_unitSample[11].img[STATE_DOWN] = IMAGEMANAGER->findImage("champion_down");
		_unitSample[11].img[STATE_FRONT] = IMAGEMANAGER->findImage("champion_front");
		_unitSample[11].img[STATE_MOVE] = IMAGEMANAGER->findImage("champion_move");
		_unitSample[11].img[STATE_SELECT] = IMAGEMANAGER->findImage("champion_select");
		_unitSample[11].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("champion_up_shadow");
		_unitSample[11].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("champion_down_shadow");
		_unitSample[11].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("champion_front_shadow");
		_unitSample[11].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("champion_move_shadow");
		_unitSample[11].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("champion_select_shadow");


		//============= angel
		_unitSample[12].x = 309;
		_unitSample[12].y = 404;
		_unitSample[12].img[STATE_DOWN] = IMAGEMANAGER->findImage("angel_down");
		_unitSample[12].img[STATE_UP] = IMAGEMANAGER->findImage("angel_up");
		_unitSample[12].img[STATE_FRONT] = IMAGEMANAGER->findImage("angel_front");
		_unitSample[12].img[STATE_IDLE] = IMAGEMANAGER->findImage("angel_idle");
		_unitSample[12].img[STATE_SELECT] = IMAGEMANAGER->findImage("angel_select");
		_unitSample[12].img[STATE_MOVE] = IMAGEMANAGER->findImage("angel_move");
		_unitSample[12].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("angel_down_shadow");
		_unitSample[12].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("angel_up_shadow");
		_unitSample[12].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("angel_front_shadow");
		_unitSample[12].shadowImg[STATE_IDLE] = IMAGEMANAGER->findImage("angel_idle_shadow");
		_unitSample[12].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("angel_select_shadow");
		_unitSample[12].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("angel_move_shadow");



		//============= arc angel
		_unitSample[13].x = 309;
		_unitSample[13].y = 404;
		_unitSample[13].img[STATE_DOWN] = IMAGEMANAGER->findImage("arc_down");
		_unitSample[13].img[STATE_UP] = IMAGEMANAGER->findImage("arc_up");
		_unitSample[13].img[STATE_FRONT] = IMAGEMANAGER->findImage("arc_front");
		_unitSample[13].img[STATE_SELECT] = IMAGEMANAGER->findImage("arc_select");
		_unitSample[13].img[STATE_MOVE] = IMAGEMANAGER->findImage("arc_move");
		_unitSample[13].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("arc_down_shadow");
		_unitSample[13].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("arc_up_shadow");
		_unitSample[13].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("arc_front_shadow");
		_unitSample[13].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("arc_select_shadow");
		_unitSample[13].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("arc_move_shadow");

		break;
	case CAMP_DUNGEON:
		
		//============= ������
		_unitSample[0].x = 158;
		_unitSample[0].y = 0;
		_unitSample[0].img[STATE_UP] = IMAGEMANAGER->findImage("troglodyte_up");
		_unitSample[0].img[STATE_DOWN] = IMAGEMANAGER->findImage("troglodyte_down");
		_unitSample[0].img[STATE_FRONT] = IMAGEMANAGER->findImage("troglodyte_front");
		_unitSample[0].img[STATE_MOVE] = IMAGEMANAGER->findImage("troglodyte_move");
		_unitSample[0].img[STATE_SELECT] = IMAGEMANAGER->findImage("troglodyte_select");
		_unitSample[0].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("troglodyte_up_shadow");
		_unitSample[0].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("troglodyte_down_shadow");
		_unitSample[0].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("troglodyte_front_shadow");
		_unitSample[0].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("troglodyte_move_shadow");
		_unitSample[0].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("troglodyte_select_shadow");
		
		//============= ���� ������
		_unitSample[1].x = 158;
		_unitSample[1].y = 0;
		_unitSample[1].img[STATE_UP] = IMAGEMANAGER->findImage("infernal_up");
		_unitSample[1].img[STATE_DOWN] = IMAGEMANAGER->findImage("infernal_down");
		_unitSample[1].img[STATE_FRONT] = IMAGEMANAGER->findImage("infernal_front");
		_unitSample[1].img[STATE_MOVE] = IMAGEMANAGER->findImage("infernal_move");
		_unitSample[1].img[STATE_SELECT] = IMAGEMANAGER->findImage("infernal_select");
		_unitSample[1].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("infernal_up_shadow");
		_unitSample[1].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("infernal_down_shadow");
		_unitSample[1].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("infernal_front_shadow");
		_unitSample[1].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("infernal_move_shadow");
		_unitSample[1].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("infernal_select_shadow");

		//============== ���� 
		_unitSample[2].x = 552;
		_unitSample[2].y = 25;
		_unitSample[2].img[STATE_UP] = IMAGEMANAGER->findImage("harpy_up");
		_unitSample[2].img[STATE_DOWN] = IMAGEMANAGER->findImage("harpy_down");
		_unitSample[2].img[STATE_FRONT] = IMAGEMANAGER->findImage("harpy_front");
		_unitSample[2].img[STATE_MOVE] = IMAGEMANAGER->findImage("harpy_move");
		_unitSample[2].img[STATE_SELECT] = IMAGEMANAGER->findImage("harpy_select");
		_unitSample[2].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("harpy_up_shadow");
		_unitSample[2].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("harpy_down_shadow");
		_unitSample[2].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("harpy_front_shadow");
		_unitSample[2].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("harpy_move_shadow");
		_unitSample[2].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("harpy_select_shadow");

		//=============== ���� ��
		_unitSample[3].x = 552;
		_unitSample[3].y = 25;
		_unitSample[3].img[STATE_UP] = IMAGEMANAGER->findImage("hag_up");
		_unitSample[3].img[STATE_DOWN] = IMAGEMANAGER->findImage("hag_down");
		_unitSample[3].img[STATE_FRONT] = IMAGEMANAGER->findImage("hag_front");
		_unitSample[3].img[STATE_MOVE] = IMAGEMANAGER->findImage("hag_move");
		_unitSample[3].img[STATE_SELECT] = IMAGEMANAGER->findImage("hag_select");
		_unitSample[3].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("hag_up_shadow");
		_unitSample[3].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("hag_down_shadow");
		_unitSample[3].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("hag_front_shadow");
		_unitSample[3].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("hag_move_shadow");
		_unitSample[3].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("hag_select_shadow");



		

		//============= ��Ȧ��
		_unitSample[4].x = 148;
		_unitSample[4].y = 158;
		_unitSample[4].img[STATE_UP] = IMAGEMANAGER->findImage("beholder_up");
		_unitSample[4].img[STATE_DOWN] = IMAGEMANAGER->findImage("beholder_down");
		_unitSample[4].img[STATE_FRONT] = IMAGEMANAGER->findImage("beholder_front");
		_unitSample[4].img[STATE_MOVE] = IMAGEMANAGER->findImage("beholder_move");
		_unitSample[4].img[STATE_SELECT] = IMAGEMANAGER->findImage("beholder_select");
		_unitSample[4].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("beholder_up_shadow");
		_unitSample[4].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("beholder_down_shadow");
		_unitSample[4].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("beholder_front_shadow");
		_unitSample[4].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("beholder_move_shadow");
		_unitSample[4].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("beholder_select_shadow");


		//============= evil eye
		_unitSample[5].x = 148;
		_unitSample[5].y = 158;
		_unitSample[5].img[STATE_UP] = IMAGEMANAGER->findImage("evil_up");
		_unitSample[5].img[STATE_DOWN] = IMAGEMANAGER->findImage("evil_down");
		_unitSample[5].img[STATE_FRONT] = IMAGEMANAGER->findImage("evil_front");
		_unitSample[5].img[STATE_MOVE] = IMAGEMANAGER->findImage("evil_move");
		_unitSample[5].img[STATE_SELECT] = IMAGEMANAGER->findImage("evil_select");
		_unitSample[5].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("evil_up_shadow");
		_unitSample[5].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("evil_down_shadow");
		_unitSample[5].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("evil_front_shadow");
		_unitSample[5].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("evil_move_shadow");
		_unitSample[5].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("evil_select_shadow");


		//============= �޵λ�
		
		_unitSample[6].x = 532;
		_unitSample[6].y = 158;
		_unitSample[6].img[STATE_UP] = IMAGEMANAGER->findImage("medusa_melee");
		_unitSample[6].img[STATE_DOWN] = IMAGEMANAGER->findImage("medusa_melee");
		_unitSample[6].img[STATE_FRONT] = IMAGEMANAGER->findImage("medusa_melee");
		_unitSample[6].img[STATE_MOVE] = IMAGEMANAGER->findImage("medusa_move");
		_unitSample[6].img[STATE_SELECT] = IMAGEMANAGER->findImage("medusa_select");
		_unitSample[6].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("medusa_melee_shadow");
		_unitSample[6].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("medusa_melee_shadow");
		_unitSample[6].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("medusa_melee_shadow");
		_unitSample[6].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("medusa_move_shadow");
		_unitSample[6].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("medusa_select_shadow");

		//============= ��

		_unitSample[7].x = 522;
		_unitSample[7].y = 158;
		_unitSample[7].img[STATE_UP] = IMAGEMANAGER->findImage("queen_melee");
		_unitSample[7].img[STATE_DOWN] = IMAGEMANAGER->findImage("queen_melee");
		_unitSample[7].img[STATE_FRONT] = IMAGEMANAGER->findImage("queen_melee");
		_unitSample[7].img[STATE_MOVE] = IMAGEMANAGER->findImage("queen_move");
		_unitSample[7].img[STATE_SELECT] = IMAGEMANAGER->findImage("queen_select");
		_unitSample[7].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("queen_melee_shadow");
		_unitSample[7].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("queen_melee_shadow");
		_unitSample[7].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("queen_melee_shadow");
		_unitSample[7].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("queen_move_shadow");
		_unitSample[7].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("queen_select_shadow");

		//============= �̳�Ÿ�츣

		_unitSample[8].x = 158;
		_unitSample[8].y = 291;
		_unitSample[8].img[STATE_UP] = IMAGEMANAGER->findImage("minotaur_up");
		_unitSample[8].img[STATE_DOWN] = IMAGEMANAGER->findImage("minotaur_down");
		_unitSample[8].img[STATE_FRONT] = IMAGEMANAGER->findImage("minotaur_front");
		_unitSample[8].img[STATE_MOVE] = IMAGEMANAGER->findImage("minotaur_move");
		_unitSample[8].img[STATE_SELECT] = IMAGEMANAGER->findImage("minotaur_select");
		_unitSample[8].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("minotaur_up_shadow");
		_unitSample[8].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("minotaur_down_shadow");
		_unitSample[8].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("minotaur_front_shadow");
		_unitSample[8].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("minotaur_move_shadow");
		_unitSample[8].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("minotaur_select_shadow");

		//============= minotaurs king

		_unitSample[9].x = 158;
		_unitSample[9].y = 291;
		_unitSample[9].img[STATE_UP] = IMAGEMANAGER->findImage("minotaur_up");
		_unitSample[9].img[STATE_DOWN] = IMAGEMANAGER->findImage("minotaur_down");
		_unitSample[9].img[STATE_FRONT] = IMAGEMANAGER->findImage("minotaur_front");
		_unitSample[9].img[STATE_MOVE] = IMAGEMANAGER->findImage("minotaur_move");
		_unitSample[9].img[STATE_SELECT] = IMAGEMANAGER->findImage("minotaur_select");
		_unitSample[9].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("minotaur_up_shadow");
		_unitSample[9].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("minotaur_down_shadow");
		_unitSample[9].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("minotaur_front_shadow");
		_unitSample[9].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("minotaur_move_shadow");
		_unitSample[9].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("minotaur_select_shadow");

		//============= manticore

		_unitSample[10].x = 512;
		_unitSample[10].y = 281;
		_unitSample[10].img[STATE_UP] = IMAGEMANAGER->findImage("manticore_up");
		_unitSample[10].img[STATE_DOWN] = IMAGEMANAGER->findImage("manticore_down");
		_unitSample[10].img[STATE_FRONT] = IMAGEMANAGER->findImage("manticore_front");
		_unitSample[10].img[STATE_MOVE] = IMAGEMANAGER->findImage("manticore_move");
		_unitSample[10].img[STATE_SELECT] = IMAGEMANAGER->findImage("manticore_select");
		_unitSample[10].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("manticore_up_shadow");
		_unitSample[10].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("manticore_down_shadow");
		_unitSample[10].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("manticore_front_shadow");
		_unitSample[10].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("manticore_move_shadow");
		_unitSample[10].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("manticore_select_shadow");

		//============= scorpicore

		_unitSample[11].x = 512;
		_unitSample[11].y = 281;
		_unitSample[11].img[STATE_UP] = IMAGEMANAGER->findImage("scorpicore_up");
		_unitSample[11].img[STATE_DOWN] = IMAGEMANAGER->findImage("scorpicore_down");
		_unitSample[11].img[STATE_FRONT] = IMAGEMANAGER->findImage("scorpicore_front");
		_unitSample[11].img[STATE_MOVE] = IMAGEMANAGER->findImage("scorpicore_move");
		_unitSample[11].img[STATE_SELECT] = IMAGEMANAGER->findImage("scorpicore_select");
		_unitSample[11].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("scorpicore_up_shadow");
		_unitSample[11].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("scorpicore_down_shadow");
		_unitSample[11].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("scorpicore_front_shadow");
		_unitSample[11].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("scorpicore_move_shadow");
		_unitSample[11].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("scorpicore_select_shadow");


		//============= ���� �巡��
		_unitSample[12].x = 264;
		_unitSample[12].y = 384;
		_unitSample[12].img[STATE_DOWN] = IMAGEMANAGER->findImage("red_attack_down");
		_unitSample[12].img[STATE_UP] = IMAGEMANAGER->findImage("red_attack_up");
		_unitSample[12].img[STATE_FRONT] = IMAGEMANAGER->findImage("red_attack_front");
		_unitSample[12].img[STATE_IDLE] = IMAGEMANAGER->findImage("red_idle");
		_unitSample[12].img[STATE_SELECT] = IMAGEMANAGER->findImage("red_select");
		_unitSample[12].img[STATE_MOVE] = IMAGEMANAGER->findImage("red_move");
		_unitSample[12].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("red_attack_down_shadow");
		_unitSample[12].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("red_attack_up_shadow");
		_unitSample[12].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("red_attack_front_shadow");
		_unitSample[12].shadowImg[STATE_IDLE] = IMAGEMANAGER->findImage("red_idle_shadow");
		_unitSample[12].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("red_select_shadow");
		_unitSample[12].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("red_move_shadow");



		//============= �� �巡��
		_unitSample[13].x = 264;
		_unitSample[13].y = 384;
		_unitSample[13].img[STATE_DOWN] = IMAGEMANAGER->findImage("black_attack_down");
		_unitSample[13].img[STATE_UP] = IMAGEMANAGER->findImage("black_attack_up");
		_unitSample[13].img[STATE_FRONT] = IMAGEMANAGER->findImage("black_attack_front");
		_unitSample[13].img[STATE_IDLE] = IMAGEMANAGER->findImage("black_idle");
		_unitSample[13].img[STATE_SELECT] = IMAGEMANAGER->findImage("black_select");
		_unitSample[13].img[STATE_MOVE] = IMAGEMANAGER->findImage("black_move");
		_unitSample[13].shadowImg[STATE_DOWN] = IMAGEMANAGER->findImage("black_attack_down_shadow");
		_unitSample[13].shadowImg[STATE_UP] = IMAGEMANAGER->findImage("black_attack_up_shadow");
		_unitSample[13].shadowImg[STATE_FRONT] = IMAGEMANAGER->findImage("black_attack_front_shadow");
		_unitSample[13].shadowImg[STATE_IDLE] = IMAGEMANAGER->findImage("black_idle_shadow");
		_unitSample[13].shadowImg[STATE_SELECT] = IMAGEMANAGER->findImage("black_select_shadow");
		_unitSample[13].shadowImg[STATE_MOVE] = IMAGEMANAGER->findImage("black_move_shadow");


		break;
	}



}
