#ifndef MUSIC_MANAGER
#define MUSIC_MANAGER
#include <SFML/Audio.hpp>
#include <map>

class MusicManager
{
    public:
        MusicManager();
        void addMusic(std::string sound);
        void play(std::string sound);
        void stop();
        void playBackground(std::string sound);
    
        static std::map<std::string, sf::SoundBuffer> musicList;
        static std::vector<sf::Sound> musicPlaying;
    private:
        sf::SoundBuffer _globalBuffer;
    
};

#endif
