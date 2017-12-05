#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>
#include "MusicManager.h"

std::map<std::string, sf::SoundBuffer> MusicManager::musicList = std::map<std::string, sf::SoundBuffer>();
std::vector<sf::Sound> MusicManager::playingSounds = std::vector<sf::Sound>();
sf::Music music;

MusicManager::MusicManager()
{
    
}

void MusicManager::addMusic(std::string sound)
{
    if (!_globalBuffer.loadFromFile("../resources/" + sound))
        return;
    musicList[sound] = _globalBuffer;
}

void MusicManager::play(std::string sound)
{
    if (playingSounds.size() == 0)
    {
        playingSounds.push_back(sf::Sound());
        playingSounds.at(0).setBuffer(musicList[sound]);
        playingSounds.at(0).play();
    }
    else
    {
        int location = -1;
        for (int i = 0; i < playingSounds.size(); i++)
        {
            if (playingSounds.at(i).getStatus() != sf::Sound::Playing && location == -1)
            {
                location = i;
            }
        }
        if (location != -1)
        {
            playingSounds.at(location).setBuffer(musicList[sound]);
            playingSounds.at(location).play();
        }
        else
        {
            playingSounds.push_back(sf::Sound());
            playingSounds.at(playingSounds.size()-1).setBuffer(musicList[sound]);
            playingSounds.at(playingSounds.size() - 1).play();
        }
    }
}

void MusicManager::stop()
{
    for (int i = 0; i < playingSounds.size(); i++)
    {
        if (playingSounds.at(i).getStatus() == sf::Sound::Playing)
        {
            playingSounds.at(i).pause();
        }
    }
    music.stop();
}

void MusicManager::playBackground(std::string sound)
{
    if (!music.openFromFile("../resources/" + sound))
        return;
    music.setLoop(true);
    music.play();
}

