#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>
#include "music_manager.h"

std::map<std::string, sf::SoundBuffer> music_manager::music_list = std::map<std::string, sf::SoundBuffer>();
music_manager::music_manager()
{
    
}

void music_manager::add()
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../resources/canary.wav"))
        return;
    music_list["canary"] = buffer;
    if (!buffer.loadFromFile("../resources/orchestral.ogg"))
        return;
    music_list["orchestral"] = buffer;
    if (!buffer.loadFromFile("../resources/ding.flac"))
        return;
    music_list["ding"] = buffer;
}

void music_manager::stop()
{
    global_sound.pause();
}

void music_manager::play(std::string sound)
{
    global_buffer = music_list[sound];
    global_sound.setBuffer(global_buffer);
    global_sound.play();
}