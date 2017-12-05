#ifndef LEVELINFO_H
#define LEVELINFO_H

#include <string>
#include <SwordfishInfo.h>
#include <SFML/Graphics.hpp>

class LevelInfo {
public:
	LevelInfo();
	int getLevelNumber();
	void setLevelNumber(int level_number);
	int getLevelLength();
	void setLevelLength(int level_length);
	int getMinionNumber();
	void setMinionNumber(int minion_num);
	std::vector<std::vector<sf::Vector2f>> getTerrain();
	void setTerrain(std::vector<std::vector<sf::Vector2f>> terrain);
	std::string getBackgroundImage();
	void setBackgroundImage(std::string bg_img_name);
	std::string getBackgroundMusic();
	void setBackgroundMusic(std::string bg_music_name);
	SwordfishInfo getSwordfishInfo();
	void setSwordfishInfo(SwordfishInfo swordfish_info);
private:
	int level_number, level_length, minion_num;
	std::vector<std::vector<sf::Vector2f>> terrain;
	std::string bg_img_name, bg_music_name;
	SwordfishInfo swordfish_info; 	

};

#endif