#ifndef SWORDFISHINFO_H
#define SWORDFISHINFO_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

struct Settings {
    int pos_x, pos_y, delay;
    float dir_x, dir_y;
};

class SwordfishInfo
{
public:
    SwordfishInfo();
    std::vector<Settings> getSwordfishList();
    void setSwordfishList(std::vector<Settings> swordfishList);
    void addSwordfish(int pos_x, int pos_y, int delay, float dir_x, float dir_y);
    
private:
    std::vector<Settings> swordfishList;
};
#endif