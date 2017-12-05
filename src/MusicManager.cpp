#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>
#include "MusicManager.h"

std::map<std::string, sf::SoundBuffer> MusicManager::musicList = std::map<std::string, sf::SoundBuffer>();
std::map<std::string, sf::SoundBuffer> MusicManager::backgroundMusicList = std::map<std::string, sf::SoundBuffer>();

MusicManager::MusicManager()
{
    
}

void MusicManager::add()
{
    if (!_globalBuffer.loadFromFile("../resources/canary.wav"))
        return;
    musicList["canary"] = _globalBuffer;
    if (!_globalBuffer.loadFromFile("../resources/orchestral.ogg"))
        return;
    musicList["orchestral"] = _globalBuffer;
    if (!_globalBuffer.loadFromFile("../resources/ding.flac"))
        return;
    musicList["ding"] = _globalBuffer;
    
    if (!_backgroundBuffer.loadFromFile("../resources/background1.mp3"))
        return;
    backgroundMusicList["background1"] = _globalBuffer;
}

void MusicManager::stop()
{
    _globalSound.pause();
}

void MusicManager::play(std::string sound)
{
    _globalBuffer = musicList[sound];
    _globalSound.setBuffer(_globalBuffer);
    _globalSound.play();
}

void MusicManager::stopBackground()
{
    _backgroundSound.pause();
}

void MusicManager::playBackground(std::string background)
{
    _backgroundBuffer = backgroundMusicList[background];
    _backgroundSound.setBuffer(_backgroundBuffer);
    _backgroundSound.play();
}
