#include "Minions.h"
#include "util.h"
#include <cassert>
const float Minions::WEAK_TIME=10.0f;
const float Minions::ATTACK_SPEED=100.0f;
const float Minions::SHOT_TIME=1.0f;
const float Minions::NORMAL_SIZE=100.0f;
const float Minions::WEAK_SIZE=NORMAL_SIZE*2.0f/3.0f;
const float Minions::ATTACK_RADIUS=1.5f*NORMAL_SIZE;
const float Minions::NORMAL_SPEED=ATTACK_SPEED/2.0f;
const float Minions::ESCAPE_SPEED=NORMAL_SPEED*2.0f;
const float Minions::ATTACKED_TIME=0.3f;

Minions::Minions(sf::Vector2f pos)
{
    Fish::addKnot(Knot(NORMAL_SIZE,NORMAL_SIZE,pos));
    _body=sf::RectangleShape(sf::Vector2f(NORMAL_SIZE,NORMAL_SIZE));
    _body.setOrigin(NORMAL_SIZE,0.5f*NORMAL_SIZE);
    _recoverBar=std::make_shared<ProgressBar>(WEAK_SIZE,WEAK_SIZE/15.0f,100,0,sf::Color::Red);
}

void Minions::init()
{

    _state=NORMAL;
    _attackRadius=ATTACK_RADIUS;
    _attackTarget=nullptr;
    _timer=0.0f;
    _speed=NORMAL_SPEED;
    assert(_texture!=nullptr);
    assert(_textureAreas!=nullptr);
    _body.setTexture(_texture.get());
    _body.setTextureRect((*_textureAreas)["Minions_normal"]);
    _recoverBar->setValue(0);
}

Minions::State Minions::getState() const
{
    return _state;
}
float Minions::getAttackRadius() const
{
    return _attackRadius;
}
void Minions::setAttackTarget(const std::shared_ptr<Fish>& attackTarget)
{
    _attackTarget=attackTarget;
}
const std::shared_ptr<Fish>& Minions::getAttackTarget()const
{
    return _attackTarget;
}
float Minions::getSpeed() const
{
    return _speed;
}

void Minions::attacking()
{
    if(_state!=NORMAL)
        return;
    _state=ATTACK;
    _timer=0.0f;
    _speed=ATTACK_SPEED;
}

void Minions::attacked()
{
    if(_state==WEAK)
    {
        defeated();
    }
    else if(_state==NORMAL||_state==ATTACK)
    {
        _state=ATTACKED;
        _timer=0.0f;
        _speed=NORMAL_SPEED;
        _body.setFillColor(sf::Color(255,0,0));
    }
}
void Minions::shot()
{
    if(_state==WEAK)
    {
        defeated();
    }
    else if(_state==NORMAL||_state==ATTACK)
    {
        _state=SHOT;
        _timer=0.0f;
        _speed=NORMAL_SPEED;
        assert(_textureAreas!=nullptr);
        _body.setTextureRect((*_textureAreas)["Minions_shot"]);
    }
}

void Minions::shocked()
{
    if(_state==WEAK)
    {
        defeated();
    }
    else if(_state==NORMAL||_state==ATTACK)
    {
        _state=SHOCKED;
        _speed=NORMAL_SPEED;
        assert(_textureAreas!=nullptr);
        _body.setTextureRect((*_textureAreas)["Minions_shocked"]);
    }
}

void Minions::weaken()
{
    _state=WEAK;
    _speed=ESCAPE_SPEED;
    _timer=0.0f;
    _body.setScale(sf::Vector2f(WEAK_SIZE/NORMAL_SIZE,WEAK_SIZE/NORMAL_SIZE));
    _knots[0].setRect(WEAK_SIZE,WEAK_SIZE);
    assert(_textureAreas!=nullptr);
    _body.setTextureRect((*_textureAreas)["Minions_weak"]);
}

void Minions::recovered()
{
    _state=NORMAL;
    _speed=NORMAL_SPEED;
    _body.setScale(sf::Vector2f(1.0f,1.0f));
    _knots[0].setRect(NORMAL_SIZE,NORMAL_SIZE);
    assert(_textureAreas!=nullptr);
    _body.setTextureRect((*_textureAreas)["Minions_normal"]);
}

void Minions::defeated()
{
    _state=DIE;
}

void Minions::update(float deltaTime)
{
    switch(_state)
    {
        case NORMAL:
            if(_attackTarget==nullptr) break;
            if(mag(_attackTarget->getKnot(0).getPosition()-_knots[0].getPosition())<ATTACK_RADIUS)
            {
                attacking();
            }
            break;
        case WEAK:
            _timer+=deltaTime;
            _recoverBar->setValue(_recoverBar->getRange()*_timer/WEAK_TIME);
            _recoverBar->setPosition(_knots[0].getPosition()+sf::Vector2f(0.0,-WEAK_SIZE/sqrt(2)));
            if(_timer>WEAK_TIME)
            {
                _timer=0;
                recovered();
            }
            break;
        case SHOCKED:
            break;
        case SHOT:
            _timer+=deltaTime;
            _knots[0].rotate(360.0f*deltaTime/SHOT_TIME);
            if(_timer>SHOT_TIME)
            {
                _timer=0;
                weaken();
            }
            break;
        case ATTACK:
            if(_attackTarget==nullptr) break;
            if(mag(_attackTarget->getKnot(0).getPosition()-_knots[0].getPosition())>ATTACK_RADIUS)
            {
                recovered();
            }
            break;
        case ATTACKED:
            _timer+=deltaTime;
            if(_timer>ATTACKED_TIME)
            {
                _timer=0;
                _body.setFillColor(sf::Color(255,255,255));
                weaken();
            }
        default:
            break;
    }
    Fish::update(deltaTime);
}

void Minions::updateShape()
{
    assert(_knots.size()>=1);
    _body.setPosition(_knots[0].getPosition());
    _body.setRotation(_knots[0].getRotation());
}

void Minions::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    Fish::draw(target,states);
    states.transform*=getTransform();
    target.draw(_body,states);
    if(_state==WEAK)
    {
        target.draw(*_recoverBar,states);
    }
}



