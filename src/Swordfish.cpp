#include <cassert>
#include <cmath>
#include "Swordfish.h"
#include "util.h"
#include "Constants.h"

const float Swordfish::TOTAL_TIME=10.0f;
const float Swordfish::CHARGE_TIME=3.0f;
const float Swordfish::RELEASE_TIME=1.0f;
const float Swordfish::BLINK_TIME=1.0f;
const float Swordfish::SIZE=100.0f;

Swordfish::Swordfish(sf::Vector2f pos)
{
  Fish::addKnot(Knot(SIZE,SIZE,pos));
  _body=sf::RectangleShape(sf::Vector2f(SIZE,SIZE));
  _body.setOrigin(SIZE,0.5f*SIZE);
    
  _attackLine.setSize(sf::Vector2f(10000, 5));
  _attackLine.setPosition(pos);
  _timer=0.0f;
  _state=NORMAL;
}

void Swordfish::init()
{
    assert(_texture!=nullptr);
    assert(_textureAreas!=nullptr);
    _body.setTexture(_texture.get());
    _body.setTextureRect((*_textureAreas)["Minions_normal"]);
}

Swordfish::State Swordfish::getState() const
{
  return _state;
}

void Swordfish::triggered()
{
  if(_state!=NORMAL)
    return;
  _attackLine.setPosition(_body.getPosition());
  _attackLine.rotate(_body.getRotation());
  _state=CHARGE;
  _timer=0.0f;
}

void Swordfish::update(float deltaTime)
{
    assert(_knots.size()>=1);
    assert(_texture);
    assert(_textureAreas);
    //sf::Vector2f dist;
    //float dist=0.0f;
    int trans=128;
    switch(_state)
    {
        case NORMAL:
            break;
        case ATTACK:
            //swimTo();
            break;
        case CHARGE:
            _timer+=deltaTime;
            trans=128/(_timer/BLINK_TIME);
            _attackLine.setFillColor(sf::Color(255,0,0,trans));
            if(_timer>CHARGE_TIME)
            {
                _timer=0.0f;
                _state=ATTACK;
            }
            break;
        default:
            break;
    }
    updateShape();
}

void Swordfish::updateShape()
{
    assert(_knots.size()>=1);
    _body.setPosition(_knots[0].getPosition());
    _body.setRotation(_knots[0].getRotation());
}

void Swordfish::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
  if(_state==CHARGE)
    {
      target.draw(_attackLine,states);
    }
  if(_state==NORMAL)
    {
      //target.draw(_triggerArea,states);
    }
  states.transform*=getTransform();
  target.draw(_body,states);
}
