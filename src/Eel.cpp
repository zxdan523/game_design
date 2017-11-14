#include <cassert>
#include <cmath>
#include "Eel.h"
#include "Constants.h"

const int Eel::PARTITION=20;
const float Eel::WIDTH=20.0f;
const float Eel::LENGTH=12.0f;
const float Eel::TOTAL_TIME=10.0f;
const float Eel::CHARGE_TIME=3.0f;
const float Eel::RELEASE_TIME=1.0f;
const float Eel::ATTACK_RADIUS=200.0f;
const float Eel::TRIGGER_RADIUS=50.0f;
const float Eel::BLINK_TIME=1.0f;
const sf::Color Eel::BODY_COLOR=sf::Color::Yellow;

Eel::Eel()
{

    _body=sf::VertexArray(sf::Quads,4*(PARTITION-1));
    for(int i=0;i<PARTITION;i++)
    {
        addKnot(Knot(LENGTH,WIDTH,sf::Vector2f(WINDOW_WIDTH+i*LENGTH,WINDOW_HEIGHT*(1.0f-0.618f))));
        _knots[i].setRotation(180.0f);
        if(i<PARTITION-1)
        {
            _body[4*i].color=BODY_COLOR;
            _body[4*i+1].color=BODY_COLOR;
            _body[4*i+2].color=BODY_COLOR;
            _body[4*i+3].color=BODY_COLOR;
        }
    }

    _mouth=sf::RectangleShape(sf::Vector2f(WIDTH,WIDTH));
    _mouth.setOrigin(sf::Vector2f(0.0f,WIDTH/2.0f));
    _left_eye=sf::RectangleShape(sf::Vector2f(WIDTH,WIDTH));
    _left_eye.setOrigin(sf::Vector2f(WIDTH/2.0f,WIDTH));
    _right_eye=sf::RectangleShape(sf::Vector2f(WIDTH,WIDTH));
    _right_eye.setOrigin(sf::Vector2f(WIDTH/2.0f,0.0f));
    _front_left_fin=sf::RectangleShape(sf::Vector2f(WIDTH,WIDTH));
    _front_left_fin.setOrigin(sf::Vector2f(_front_left_fin.getSize().x,_front_left_fin.getSize().y));
    _front_right_fin=sf::RectangleShape(sf::Vector2f(_front_left_fin.getSize().x,_front_left_fin.getSize().y));
    _front_right_fin.setOrigin(sf::Vector2f(_front_right_fin.getSize().x,0.0f));
    _back_left_fin=sf::RectangleShape(sf::Vector2f(_front_left_fin.getSize().x,_front_left_fin.getSize().y));
    _back_left_fin.setOrigin(sf::Vector2f(_back_left_fin.getSize().x,_back_left_fin.getSize().y));
    _back_right_fin=sf::RectangleShape(sf::Vector2f(_front_left_fin.getSize().x,_front_left_fin.getSize().y));
    _back_right_fin.setOrigin(sf::Vector2f(_back_right_fin.getSize().x,0.0f));
    _tail=sf::RectangleShape(sf::Vector2f(WIDTH,WIDTH));
    _tail.setOrigin(sf::Vector2f(0.0f,WIDTH/2.0f));
    _triggerArea=sf::CircleShape(TRIGGER_RADIUS);
    _triggerArea.setOrigin(TRIGGER_RADIUS,TRIGGER_RADIUS);
    _triggerArea.setFillColor(sf::Color(255,255,0,128));
    _attackArea=sf::CircleShape(ATTACK_RADIUS);
    _attackArea.setOrigin(ATTACK_RADIUS,ATTACK_RADIUS);
    _attackArea.setFillColor(sf::Color(255,255,0,128));
    _timer=0.0f;
    _state=NORMAL;
    _moveAngle=0.0f;
}

void Eel::init()
{
    assert(_texture!=nullptr);
    assert(_textureAreas!=nullptr);
    _mouth.setTexture(_texture.get());
    _mouth.setTextureRect((*_textureAreas)["Eel_mouth"]);
    _left_eye.setTexture(_texture.get());
    _left_eye.setTextureRect((*_textureAreas)["Eel_left_eye"]);
    _right_eye.setTexture(_texture.get());
    _right_eye.setTextureRect((*_textureAreas)["Eel_right_eye"]);
    _front_left_fin.setTexture(_texture.get());
    _front_left_fin.setTextureRect((*_textureAreas)["Eel_left_fin"]);
    _front_right_fin.setTexture(_texture.get());
    _front_right_fin.setTextureRect((*_textureAreas)["Eel_right_fin"]);
    _back_left_fin.setTexture(_texture.get());
    _back_left_fin.setTextureRect((*_textureAreas)["Eel_left_fin"]);
    _back_right_fin.setTexture(_texture.get());
    _back_right_fin.setTextureRect((*_textureAreas)["Eel_right_fin"]);
    _tail.setTexture(_texture.get());
    _tail.setTextureRect((*_textureAreas)["Eel_tail"]);
}

Eel::State Eel::getState() const
{
    return _state;
}

float Eel::getAttackRadius() const
{
    return ATTACK_RADIUS;
}

float Eel::getTriggerRadius() const
{
    return TRIGGER_RADIUS;
}

sf::Vector2f Eel::getCenter() const
{
    return sf::Vector2f(_knots[0].getPosition().x+PARTITION*LENGTH/3.0f,WINDOW_HEIGHT*(1.0f-0.618f));
}
void Eel::triggered()
{
    if(_state!=NORMAL)
        return;
    _state=CHARGE;
    _timer=0.0f;
    _left_eye.setTextureRect((*_textureAreas)["Eel_attack_left_eye"]);
    _right_eye.setTextureRect((*_textureAreas)["Eel_attack_right_eye"]);
    _mouth.setFillColor(sf::Color(255,0,0));
    _front_left_fin.setFillColor(sf::Color(255,0,0));
    _front_right_fin.setFillColor(sf::Color(255,0,0));
    _back_left_fin.setFillColor(sf::Color(255,0,0));
    _back_right_fin.setFillColor(sf::Color(255,0,0));
    _tail.setFillColor(sf::Color(255,0,0));
}

void Eel::update(float deltaTime)
{
    assert(_knots.size()>=1);
    assert(_texture);
    assert(_textureAreas);
    float dist=0.0f;
    int charge_to=0;
    int trans=128;
    switch(_state)
    {
        case NORMAL:
        case RELEASED:
            dist=deltaTime*(WINDOW_WIDTH+LENGTH*PARTITION)/TOTAL_TIME;
            assert(_knots.size()>=1);
            _moveAngle+=M_PI*deltaTime;
            if(_moveAngle>=2*M_PI)
            {
                _moveAngle-=2*M_PI;
            }
            swimTo(_knots[0].getPosition()+(_headDist+dist)*sf::Vector2f(-1.0f*fabs(cos(_moveAngle)),1.0f*sin(_moveAngle)));
            if(_knots[0].getPosition().x<-PARTITION*LENGTH&&_state==RELEASED)
            {
                _state=DISAPEAR;
            }
            break;
        case CHARGE:
            _timer+=deltaTime;
            charge_to=_timer/CHARGE_TIME*(PARTITION-2);
            _body[charge_to*4].color=sf::Color::Red;
            _body[charge_to*4+1].color=sf::Color::Red;
            _body[charge_to*4+2].color=sf::Color::Red;
            _body[charge_to*4+3].color=sf::Color::Red;
            trans=128*(_timer/BLINK_TIME-int(_timer/BLINK_TIME));
            _attackArea.setFillColor(sf::Color(255,0,0,trans));
            if(_timer>=CHARGE_TIME)
            {
                _timer=0.0f;
                _state=RELEASE;
                for(int i=0;i<PARTITION-1;i++)
                {
                    _body[i*4].color=BODY_COLOR;
                    _body[i*4+1].color=BODY_COLOR;
                    _body[i*4+2].color=BODY_COLOR;
                    _body[i*4+3].color=BODY_COLOR;
                }
                _left_eye.setTextureRect((*_textureAreas)["Eel_left_eye"]);
                _right_eye.setTextureRect((*_textureAreas)["Eel_right_eye"]);
                _mouth.setFillColor(sf::Color::White);
                _front_left_fin.setFillColor(sf::Color::White);
                _front_right_fin.setFillColor(sf::Color::White);
                _back_left_fin.setFillColor(sf::Color::White);
                _back_right_fin.setFillColor(sf::Color::White);
                _tail.setFillColor(sf::Color::White);
            }
            break;
        case RELEASE:
            _timer+=deltaTime;
            _attackArea.setFillColor(sf::Color(255,255,100*_timer/RELEASE_TIME,200*_timer/RELEASE_TIME));
            if(_timer>=RELEASE_TIME)
            {
                _timer=0.0f;
                _state=RELEASED;
            }
            break;
        default:
            break;
    }
    updateShape();
}

void Eel::updateShape()
{
    for(int i=0;i<PARTITION-1;i++)
    {
        _body[i*4].position=_knots[i].getVertex(0);
        _body[i*4+1].position=_knots[i].getVertex(1);
        _body[i*4+2].position=_knots[i+1].getVertex(1);
        _body[i*4+3].position=_knots[i+1].getVertex(0);
    }
    _mouth.setPosition(_knots[0].getPosition());
    _mouth.setRotation(_knots[0].getRotation());
    _left_eye.setPosition(_knots[0].getPosition());
    _left_eye.setRotation(_knots[0].getRotation());
    _right_eye.setPosition(_knots[0].getPosition());
    _right_eye.setRotation(_knots[0].getRotation());
    _front_left_fin.setPosition(_knots[(PARTITION-1)/4].getVertex(0));
    _front_left_fin.setRotation(_knots[(PARTITION-1)/4].getRotation());
    _front_right_fin.setPosition(_knots[(PARTITION-1)/4].getVertex(1));
    _front_right_fin.setRotation(_knots[(PARTITION-1)/4].getRotation());
    _back_left_fin.setPosition(_knots[(PARTITION-1)*2/3].getVertex(0));
    _back_left_fin.setRotation(_knots[(PARTITION-1)*2/3].getRotation());
    _back_right_fin.setPosition(_knots[(PARTITION-1)*2/3].getVertex(1));
    _back_right_fin.setRotation(_knots[(PARTITION-1)*2/3].getRotation());

    _tail.setPosition(0.5f*(_knots[PARTITION-1].getVertex(2)+_knots[PARTITION-1].getVertex(3)));
    _tail.setRotation(_knots[PARTITION-1].getRotation());
    _triggerArea.setPosition(_knots[0].getPosition().x+PARTITION*LENGTH/3.0f,WINDOW_HEIGHT*(1.0f-0.618f));
    _attackArea.setPosition(_knots[0].getPosition().x+PARTITION*LENGTH/3.0f,WINDOW_HEIGHT*(1.0f-0.618f));
}

void Eel::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    if(_state==CHARGE||_state==RELEASE)
    {
        target.draw(_attackArea,states);
    }
    if(_state==NORMAL)
    {
        //target.draw(_triggerArea,states);
    }
    states.transform*=getTransform();
    target.draw(_body,states);
    target.draw(_mouth,states);
    target.draw(_left_eye,states);
    target.draw(_right_eye,states);
    target.draw(_front_left_fin,states);
    target.draw(_front_right_fin,states);
    target.draw(_back_left_fin,states);
    target.draw(_back_right_fin,states);
    target.draw(_tail,states);
    
}
