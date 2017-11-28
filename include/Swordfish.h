#ifndef SWORDFISH_H
#define SWORDFISH_H

#include "Fish.h"
class Swordfish:public Fish
{
public:
    enum State {PREPARE,SHOOT,SHOOT_END};
    
    Swordfish(sf::Vector2f pos=sf::Vector2f(),sf::Vector2f dir=sf::Vector2f(1.0f,0.0f));
    Swordfish(const Swordfish&)=delete;
    
    Swordfish& operator=(const Swordfish&)=delete;
    
    void init();
    State getState() const;
    sf::Vector2f getCenter() const;
    float getAttackRadius() const;
    
    virtual void update(float deltaTime) override;
    virtual void updateShape() override;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    
    void setPrepare(float time);
    float getPrepare();
    sf::RectangleShape _body;
    sf::RectangleShape _attackLine;
    
    float _timer;
    State _state;
    sf::Vector2f _oriPos;
    sf::Vector2f _dir;
    float _speed;
    static const float SHOOT_TIME,SIZE,SHOOT_SPEED;
    float PREPARE_TIME;
};
#endif
