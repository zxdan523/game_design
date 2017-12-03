#include "LevelInfo.h"

LevelInfo::LevelInfo() {
	level_number = 1;
	level_length = 120;
	minion_num = 5;
	bg_img_name = "bg_img_1";
	bg_music_name = "bg_music_1";
}

int LevelInfo::getLevelNumber() {
	return level_number;
}

void LevelInfo::setLevelNumber(int level_number) {
	this->level_number = level_number;
}

int LevelInfo::getLevelLength() {
	return level_length;
}

void LevelInfo::setLevelLength(int level_length) {
	this->level_length = level_length;
}

int LevelInfo::getMinionNumber() {
	return minion_num;
}

void LevelInfo::setMinionNumber(int minion_num) {
	this->minion_num = minion_num;
}

std::vector<std::vector<sf::Vector2f>> LevelInfo::getTerrain() {
	return terrain;
}

void LevelInfo::setTerrain(std::vector<std::vector<sf::Vector2f>> terrain) {
	this->terrain = terrain;
}

std::string LevelInfo::getBackgroundImage() {
	return bg_img_name;
}


void LevelInfo::setBackgroundImage(std::string bg_img_name) {
	this->bg_img_name = bg_img_name;
}

std::string LevelInfo::getBackgroundMusic() {
	return bg_music_name;
}

void LevelInfo::setBackgroundMusic(std::string bg_music_name) {
	this->bg_music_name = bg_music_name;
}