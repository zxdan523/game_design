#include <SFML/Audio.hpp>
#include <map>

class music_manager
{
    public:
        music_manager();
        void add();
        void play(std::string sound);
        void stop();
    
        static std::map<std::string, sf::SoundBuffer> music_list;
    private:
        sf::SoundBuffer global_buffer;
        sf::Sound global_sound;
    
};
