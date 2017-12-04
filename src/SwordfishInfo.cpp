#include "SwordfishInfo.h"

SwordfishInfo::SwordfishInfo() {
    delay = (0,0,0,0,0);
    swordfishList = (sf1,sf2,sf3,sf4,sf5);
}

std::vector<shared_ptr<Swordfish>> SwordfishInfo::getSwordfish(int swordfish) {
    return swordfishList[swordfish];
}

void SwordfishInfo::setSwordfish(std::vector<shared_ptr<Swordfish>> swordfishList) {
    this->swordfishList = swordfishList;
}

void SwordfishInfo::setDelay(std::vector<int> delay) {
    this->delay = delay;
}

int SwordfishInfo::getDelay(int swordfish) {
    return delay[swordfish];
}