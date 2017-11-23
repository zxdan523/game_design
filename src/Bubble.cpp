#include <cassert>
#include "Bubble.h"
#include "util.h"
#include "Constants.h"
const float Bubble::RESIST=0.00001f;
Bubble::Bubble(const sf::Vector2f& pos,const sf::Vector2f& vel)
{
    _pos=pos;
    _vel=vel;
    _lifeTime=randomFloat(1.0f,2.0f);
    float size=randomFloat(5.0f,20.0f);
    _shape=sf::RectangleShape(sf::Vector2f(size,size));
    _shape.setOrigin(0.5f*_shape.getSize());
    _shape.setScale(1.0f,1.0f);
    _shape.setPosition(_pos);
    _timer=0.0f;
}

Bubble::Bubble(const Bubble& bubble)
{
    _pos=bubble._pos;
    _vel=bubble._vel;
    _lifeTime=bubble._lifeTime;
    _shape=bubble._shape;
}

Bubble& Bubble::operator=(const Bubble& bubble)
{
    _pos=bubble._pos;
    _vel=bubble._vel;
    _lifeTime=bubble._lifeTime;
    _shape=bubble._shape;
    return *this;
}

void Bubble::setPosition(const sf::Vector2f& pos)
{
    _shape.setPosition(_pos);
}

sf::Vector2f Bubble::getPosition() const
{
    return _shape.getPosition();
}

void Bubble::setVelocity(const sf::Vector2f& vel)
{
    _vel=vel;
}

sf::Vector2f Bubble::getVelocity() const
{
    return _vel;
}

void Bubble::setLifeTime(float lifeTime)
{
    _lifeTime=lifeTime;
}

float Bubble::getLifeTime() const
{
    return _lifeTime;
}

void Bubble::setTexture(const std::shared_ptr<sf::Texture>& texture)
{
    assert(texture!=nullptr);
    _shape.setTexture(texture.get());
}

void Bubble::setTextureArea(const sf::IntRect& area)
{
    _shape.setTextureRect(area);
}

bool Bubble::ended() const
{
    sf::Vector2f pos=_shape.getPosition();
    return /*(_timer>=_lifeTime)||*/(pos.x<0)||(pos.x>WINDOW_WIDTH)||(pos.y<0)||(pos.y>WINDOW_HEIGHT);
}
void Bubble::update(float deltaTime)
{
    //if(_timer<_lifeTime)
    //{
        _timer+=deltaTime;
        _shape.setScale(_timer/_lifeTime,_timer/_lifeTime);
        _shape.setScale(1.0f,1.0f);
        _vel.x-=RESIST;
        _vel.y-=0.01f;
        _shape.move(_vel);
    //}
}

void Bubble::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    states.transform*=getTransform();
    target.draw(_shape,states);
}
