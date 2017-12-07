#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>
#include "MusicManager.h"

std::map<std::string, sf::SoundBuffer> MusicManager::musicList = std::map<std::string, sf::SoundBuffer>();
std::vector<sf::Sound> MusicManager::musicPlaying = std::vector<sf::Sound>();
sf::Music music;

MusicManager::MusicManager()
{
    
}

// Add music to musicList map from resources folder
void MusicManager::addMusic(std::string sound)
{
    if (!_globalBuffer.loadFromFile("../resources/" + sound))
        return;
    musicList[sound] = _globalBuffer;
}

// Plays Sound from the vector and adds new Sounds if needed
void MusicManager::play(std::string sound)
{
    if (musicPlaying.size() == 0)
    {
        musicPlaying.push_back(sf::Sound());
        musicPlaying.at(0).setBuffer(musicList[sound]);
        musicPlaying.at(0).play();
    }
    else
    {
        int pointer = -1;
        for (int i = 0; i < musicPlaying.size(); i++)
        {
            if (musicPlaying.at(i).getStatus() != sf::Sound::Playing && pointer == -1)
            {
                pointer = i;
            }
        }
        if (pointer != -1)
        {
            musicPlaying.at(pointer).setBuffer(musicList[sound]);
            musicPlaying.at(pointer).play();
        }
        else
        {
            musicPlaying.push_back(sf::Sound());
            musicPlaying.at(musicPlaying.size() - 1).setBuffer(musicList[sound]);
            musicPlaying.at(musicPlaying.size() - 1).play();
        }
    }
}

// Stops all sounds and music playing in the application
void MusicManager::stop()
{
    for (int i = 0; i < musicPlaying.size(); i++)
    {
        if (musicPlaying.at(i).getStatus() == sf::Sound::Playing)
        {
            musicPlaying.at(i).pause();
        }
    }
    music.stop();
}

//Plays and loops background Music from the resources folder
void MusicManager::playBackground(std::string sound)
{
    if (!music.openFromFile("../resources/" + sound))
        return;
    music.setLoop(true);
    music.play();
}

