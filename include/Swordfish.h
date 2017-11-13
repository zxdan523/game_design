#ifndef SWORDFISH_H
#define SWORDFISH_H

#include "Fish.h"
class Swordfish:public Fish
{
public:
    enum State {NORMAL,CHARGE,RELEASED};
    
    Swordfish(sf::Vector2f pos=sf::Vector2f());
    Swordfish(const Swordfish&)=delete;
    
    Swordfish& operator=(const Swordfish&)=delete;
    
    void init();
    State getState() const;
    
    void triggered();
    
    virtual void update(float deltaTime) override;
    virtual void updateShape() override;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    
    sf::RectangleShape _body;
    sf::RectangleShape _attackLine;
    
    float _timer;
    State _state;
    static const float TOTAL_TIME,CHARGE_TIME,RELEASE_TIME,BLINK_TIME,SIZE;
};
#endif
