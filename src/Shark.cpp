#include "Shark.h"
#include "util.h"
#include <cassert>

const float Shark::HEAD_SIZE=150.0f;
const float Shark::TAIL_SIZE=75.0f;
const float Shark::KNOT_DIST=30.0f;
const float Shark::NORMAL_SPEED=0.01f;
const float Shark::CRAZY_SPEED=0.5f;
const float Shark::ESCAPE_SPEED=0.8f;
const float Shark::NORMAL_SIZE=1.0f;
const float Shark::CRAZY_SIZE=0.6f;
const float Shark::WEAKEN_SIZE=0.5f;
const float Shark::HP=100;

Shark::Shark()
{
    addKnot(Knot(KNOT_DIST,TAIL_SIZE));
    addKnot(Knot(KNOT_DIST,TAIL_SIZE*4.0f/5.0f));
    addKnot(Knot(KNOT_DIST,TAIL_SIZE*3.0f/5.0f));
    addKnot(Knot(KNOT_DIST,TAIL_SIZE/2.0f));
    addKnot(Knot(KNOT_DIST,TAIL_SIZE/5.0f));
    _head=sf::RectangleShape(sf::Vector2f(HEAD_SIZE,HEAD_SIZE));
    _head.setOrigin(sf::Vector2f(0.0f,HEAD_SIZE/2.0f));
    _fins=sf::RectangleShape(sf::Vector2f(TAIL_SIZE/2.0f,TAIL_SIZE));
    _fins.setOrigin(sf::Vector2f(TAIL_SIZE/2.0f,TAIL_SIZE/2.0F));
    _tail=sf::RectangleShape(sf::Vector2f(TAIL_SIZE,TAIL_SIZE*2.0f));
    _tail.setOrigin(sf::Vector2f(TAIL_SIZE,TAIL_SIZE));
    _numPartition=10;
    _body=sf::VertexArray(sf::Quads,4*(_numPartition-1));
    _bodyShadow=sf::VertexArray(sf::Quads,4*(_numPartition-1));
    _speed=NORMAL_SPEED;
    _state=NORMAL;
    _size=1.0f;
    _current_HP=HP;
    setHeadDistance(HEAD_SIZE);
}

void Shark::init()
{
    assert(_texture!=nullptr);
    assert(_textureAreas!=nullptr);
    _head.setTexture(_texture.get());
    _head.setTextureRect((*_textureAreas)["Shark_normal_head"]);
    _fins.setTexture(_texture.get());
    _fins.setTextureRect((*_textureAreas)["Shark_fins"]);
    _tail.setTexture(_texture.get());
    _tail.setTextureRect((*_textureAreas)["Shark_tail"]);
}

void Shark::setSize(float size)
{
    _head.setScale(sf::Vector2f(size,size));
    setHeadDistance(HEAD_SIZE*size);
    _tail.setScale(sf::Vector2f(size,size));
    _fins.setScale(sf::Vector2f(size,size));
    for(size_t i=0;i<_knots.size();i++)
    {
        _knots[i].setWidth(_knots[i].getWidth()*size);
        _knots[i].setHeight(_knots[i].getHeight()*size);
    }
}

void Shark::shocked()
{
    _current_HP-=10;
    if(_current_HP<=HP/2)
    {
        _state=CRAZY;
        setSize(CRAZY_SIZE);
        _size=CRAZY_SIZE;
        _speed=CRAZY_SPEED;
        _head.setTextureRect((*_textureAreas)["Shark_crazy_head"]);
    }
    if(_current_HP<=HP/10)
    {
        _state=WEAKEN;
        _speed=ESCAPE_SPEED;
        setSize(WEAKEN_SIZE);
        _size=WEAKEN_SIZE;
        _head.setTextureRect((*_textureAreas)["Shark_weak_head"]);
    }
    if(_current_HP<=0)
    {
        _current_HP=0;
        _state=DIE;
    }
}

void Shark::shot()
{
    _current_HP-=10;
    if(_current_HP<=HP/2)
    {
        _state=CRAZY;
        setSize(CRAZY_SIZE);
        _size=CRAZY_SIZE;
        _speed=CRAZY_SPEED;
        _head.setTextureRect((*_textureAreas)["Shark_crazy_head"]);
    }
    if(_current_HP<=HP/10)
    {
        _state=WEAKEN;
        _speed=ESCAPE_SPEED;
        setSize(WEAKEN_SIZE);
        _size=WEAKEN_SIZE;
        _head.setTextureRect((*_textureAreas)["Shark_weak_head"]);
    }
    if(_current_HP<=0)
    {
        _current_HP=0;
        _state=DIE;
    }
}

void Shark::setNumPartition(int numPartition)
{
    _numPartition=numPartition;
    _body=sf::VertexArray(sf::Quads,4*(_numPartition-1));
}

int Shark::getNumPartition() const
{
    return _numPartition;
}

Shark::State Shark::getState()const
{
    return _state;
}

void Shark::setTarget(std::shared_ptr<Fish> target)
{
    _target=target;
}

std::shared_ptr<Fish> Shark::getTarget() const
{
    return _target;
}

float Shark::getSpeed() const
{
    return _speed;
}

void Shark::update(float deltaTime)
{
    switch(_state)
    {
        case NORMAL:
            break;
        case CRAZY:
            break;
        case WEAKEN:
            break;
        case DIE:
            break;
        default:
            break;
    }

    updateShape();
}

void Shark::updateShape()
{
    assert(_knots.size()>=5);
    _head.setPosition(_knots[0].getPosition());
    _head.setRotation(_knots[0].getRotation());
    if((_numPartition-1)*4!=_body.getVertexCount())
    {
        _body.clear();
        _body.resize((_numPartition-1)*4);
    }

    std::vector<sf::Vector2f> vertices(_numPartition*2);
    Bezier(_knots,vertices);

    for(size_t i=0;i<_numPartition-1;i++)
    {

        sf::Vector2f dir=normalize(vertices[2*i+1]-vertices[2*i]);
        _body[4*i].position=vertices[2*i]+dir*2.5f*_size;
        _body[4*i+1].position=vertices[2*i+1]-dir*2.5f*_size;
        _bodyShadow[4*i].position=vertices[2*i]-dir*2.5f*_size;
        _bodyShadow[4*i+1].position=vertices[2*i+1]+dir*2.5f*_size;
        
        dir=normalize(vertices[2*(i+1)+1]-vertices[2*(i+1)]);
        _body[4*i+2].position=vertices[2*(i+1)+1]-dir*2.5f*_size;
        _body[4*i+3].position=vertices[2*(i+1)]+dir*2.5f*_size;
        _bodyShadow[4*i+2].position=vertices[2*(i+1)+1]+dir*2.5f*_size;
        _bodyShadow[4*i+3].position=vertices[2*(i+1)]-dir*2.5f*_size;
        _body[4*i].color=sf::Color(72,72,72);
        _body[4*i+1].color=sf::Color(72,72,72);
        _body[4*i+2].color=sf::Color(72,72,72);
        _body[4*i+3].color=sf::Color(72,72,72);
        _bodyShadow[4*i].color=sf::Color::Black;
        _bodyShadow[4*i+1].color=sf::Color::Black;
        _bodyShadow[4*i+2].color=sf::Color::Black;
        _bodyShadow[4*i+3].color=sf::Color::Black;

    }
    _head.setPosition(_knots[0].getPosition());
    _head.setRotation(_knots[0].getRotation());
    _fins.setPosition(_knots[2].getPosition());
    _fins.setRotation(_knots[2].getRotation());
    _tail.setPosition(_knots[4].getPosition());
    _tail.setRotation(_knots[4].getRotation());
}

void Shark::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    states.transform*=getTransform();
    target.draw(_head,states);
    target.draw(_fins,states);
    target.draw(_bodyShadow,states);
    target.draw(_body,states);
    target.draw(_tail,states);
}
