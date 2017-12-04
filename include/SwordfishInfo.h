#ifndef SWORDFISHINFO_H
#define SWORDFISHINFO_H

#include <string>
#include <SFML/Graphics.hpp>

class SwordfishInfo
{
public:
    SwordfishInfo();
    std::vector<shared_ptr<Swordfish>> getSwordfish(int swordfish);
    void setSwordfish(std::vector<shared_ptr<Swordfish>> swordfishList);
    int getDelay(int swordfish) const;
    void setDelay(std::vector<int> delay);
    
private:
    std::vector<int> delay;
    std::vector<shared_ptr<Swordfish>> swordfishList (sf1,sf2,sf3,sf4,sf5);
};
#endif
