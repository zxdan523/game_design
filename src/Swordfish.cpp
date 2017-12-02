#include <cassert>
#include <cmath>
#include "Swordfish.h"
#include "util.h"
#include "Constants.h"

const float Swordfish::PREPARE_TIME=3.0f;
const float Swordfish::SHOOT_TIME=1.0f;
const float Swordfish::SIZE=100.0f;
const float Swordfish::SHOOT_SPEED=500.0f;

Swordfish::Swordfish(sf::Vector2f pos,sf::Vector2f dir)
{
  _body=sf::RectangleShape(sf::Vector2f(2*SIZE,SIZE));
  _body.setOrigin(1.0f*SIZE,0.5f*SIZE);
  _body.setPosition(pos);
  _body.setRotation(angle(dir));
  _oriPos=pos;
  _dir=normalize(dir);
    
  _attackLine.setSize(sf::Vector2f(10000, 5));
  _attackLine.setOrigin(0,2.5f);
  _attackLine.setPosition(pos);
  _attackLine.setRotation(angle(dir));
  _attackLine.setFillColor(sf::Color(255,0,0,255));
  _attackLine.setOutlineThickness(0.0f);
  _timer=0.0f;
  _state=PREPARE;
  _speed=SHOOT_SPEED;
}

void Swordfish::init()
{
    assert(_texture!=nullptr);
    assert(_textureAreas!=nullptr);
    _body.setTexture(_texture.get());
    _body.setTextureRect((*_textureAreas)["Swordfish"]);
}

Swordfish::State Swordfish::getState() const
{
    return _state;
}

sf::Vector2f Swordfish::getCenter() const
{
    return _body.getPosition();
}

float Swordfish::getAttackRadius() const
{
    return SIZE;
}
void Swordfish::update(float deltaTime)
{
    sf::Vector2f pos=_body.getPosition();
    switch(_state)
    {
        case PREPARE:
            _timer+=deltaTime;
            _attackLine.setFillColor(sf::Color(255,0,0,255*(1.0f-_timer/PREPARE_TIME)));
            if(_timer>=PREPARE_TIME)
            {
                _timer=0;
                _state=SHOOT;
            }
            break;
        case SHOOT:
            _timer+=deltaTime;
            _body.setPosition(_oriPos+_speed*_timer*_dir);
            if(pos.x<-SIZE||pos.y<-SIZE||pos.x>WINDOW_WIDTH+SIZE||pos.y>WINDOW_HEIGHT+SIZE)
            {
                _state=SHOOT_END;
            }
            else
            {
                sf::Vector2f vel(randomFloat(1.0f,2.0f),0.0f);
                if(_dir.x>0) vel.x*=-1;
                _bubbles.push_back(Bubble(_body.getPosition(),vel));
                _bubbles[_bubbles.size()-1].setTexture(_texture);
                _bubbles[_bubbles.size()-1].setTextureArea((*_textureAreas)["bubble"]);
            }
            break;
        default:
            break;
    }
    Fish::update(deltaTime);
}

void Swordfish::updateShape()
{
}

void Swordfish::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    Fish::draw(target,states);
    states.transform*=getTransform();
    if(_state==PREPARE)
    {
      target.draw(_attackLine,states);
    }
    target.draw(_body,states);
}
