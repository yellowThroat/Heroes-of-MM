#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager()
{

}

soundManager::~soundManager()
{

}

HRESULT soundManager::init(void)
{
	System_Create(&_system);
	
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];


	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*)* (TOTALSOUNDBUFFER));

	return S_OK;
}

void soundManager::release()
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 닫기 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}

}

void soundManager::update()
{
	_system->update();

}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	bool addSound = true;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			addSound = false;
			break;
		}

	}

	if (addSound)
	{
		if (loop)
		{
			if (bgm)
			{
				_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
			}
			else
			{
				_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
			}
		}
		else
		{
			if (bgm)
			{
				_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
			}
			else
			{
				_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
			}
		}

		_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));

	}
}

void soundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end();++iter, count++)
	{
		if (keyName == iter->first)
		{
			//구버전 : 첫칸->_sound[count]
			_system->playSound(*iter->second,NULL, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;	
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for ( iter; iter != _mTotalSounds.end(); ++iter,count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}

	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for ( iter ; iter != _mTotalSounds.end(); ++iter,count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);

			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for ( iter ; iter != _mTotalSounds.end(); ++iter,count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);

			break;
		}

	}
}

void soundManager::setVolume(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}

}

void soundManager::setPosition(string keyName, unsigned int position)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(position, FMOD_TIMEUNIT_MS);
			break;
		}
	}

}

unsigned int soundManager::getPosition(string keyName)
{
	unsigned int position;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&position, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return position;

}

float soundManager::getVolume(string keyName)
{
	float volume;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getVolume(&volume);
			break;
		}
	}

	return volume;


}


unsigned int soundManager::getSoundLength(string keyName)
{
	unsigned int soundLength;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_sound[count]->getLength(&soundLength, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return soundLength/1000;

}


bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for ( iter; iter != _mTotalSounds.end(); ++iter,count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPaused;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for ( iter ; iter != _mTotalSounds.end(); ++iter,count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPaused);

			break;
		}

	}
	return isPaused;
}