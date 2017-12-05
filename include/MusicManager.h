#include <SFML/Audio.hpp>
#include <map>

class MusicManager
{
    public:
        MusicManager();
        void add();
        void play(std::string sound);
        void stop();
        void playBackground(std::string backgroundMusic);
        void stopBackground();
    
        static std::map<std::string, sf::SoundBuffer> musicList;
        static std::map<std::string, sf::SoundBuffer> backgroundMusicList;
    private:
        sf::SoundBuffer _globalBuffer;
        sf::SoundBuffer _backgroundBuffer;
        sf::Sound _globalSound;
        sf::Sound _backgroundSound;
    
};
