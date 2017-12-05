#ifndef MUSIC_MANAGER
#define MUSIC_MANAGER
#include <SFML/Audio.hpp>
#include <map>

class MusicManager
{
    public:
        MusicManager();
        void add();
        void play(std::string sound);
        void stop();
    
        static std::map<std::string, sf::SoundBuffer> musicList;
    private:
        sf::SoundBuffer _globalBuffer;
        sf::Sound _globalSound;
    
};

#endif
