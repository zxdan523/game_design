#include "SwordfishInfo.h"

SwordfishInfo::SwordfishInfo() {

}

std::vector<Settings> SwordfishInfo::getSwordfishList() {
    return swordfishList;
}

void SwordfishInfo::setSwordfishList(std::vector<Settings> swordfishList) {
    this->swordfishList = swordfishList;
}

void SwordfishInfo::addSwordfish(int pos_x, int pos_y, int delay, float dir_x, float dir_y) {

	Settings settings;
	settings.pos_x = pos_x;
	settings.pos_y = pos_y;
	settings.delay = delay;
	settings.dir_x = dir_x;
	settings.dir_y = dir_y;
	swordfishList.push_back(settings);
}