#include <cassert>
#include <iostream>
#include "Fish.h"
#include "util.h"
#include "Constants.h"

Fish::Fish()
{
    _hasTexture=false;
    _headDist=10.0f;
}

void Fish::addKnot(const Knot& knot)
{
    _knots.push_back(knot);
}

Knot Fish::getKnot(int i) const
{
    assert(i<_knots.size());
    return _knots[i];
}

void Fish::setTexture(const std::shared_ptr<sf::Texture>& texture)
{
    _texture=texture;
    _hasTexture=true;
}

const std::shared_ptr<sf::Texture>& Fish::getTexture() const
{
    assert(_hasTexture);    
    return _texture;
}

void Fish::setTextureAreas(const std::shared_ptr<std::map<std::string,sf::IntRect>>& areas)
{
    _textureAreas=areas;
}

const std::shared_ptr<std::map<std::string,sf::IntRect>>& Fish::getTextureAreas() const
{
    return _textureAreas;
}

void Fish::setHeadDistance(float headDist)
{
    _headDist=headDist;
}

float Fish::getHeadDistance() const
{
    return _headDist;
}

const std::shared_ptr<std::vector<Knot>> Fish::getKnots() const
{
    return std::make_shared<std::vector<Knot>>(_knots);
}
void Fish::swimTo(const sf::Vector2f& dest)
{
    if(_knots.size()>0)
    {
        sf::Vector2f diff=dest-_knots[0].getPosition();
        _knots[0].setRotation(angle(diff));
        _knots[0].setPosition(_knots[0].getPosition()+(mag(diff)-_headDist)*normalize(diff));
        
        for(size_t i=1;i<_knots.size();i++)
        {
            sf::Vector2f diff=_knots[i-1].getPosition()-_knots[i].getPosition();
            sf::Vector2f nextPos=_knots[i].getPosition()+(mag(diff)-_knots[i-1].getWidth())*normalize(diff);
            _knots[i].setRotation(angle(diff));
            _knots[i].setPosition(nextPos);
        }

        if(randomInt(20)>19)
        {
            sf::Vector2f vel(randomFloat(1.0f,2.0f),0.0f);
            if(diff.x>0) vel.x*=-1; 
            _bubbles.push_back(Bubble(_knots[0].getPosition(),vel));
            _bubbles[_bubbles.size()-1].setTexture(_texture);
            _bubbles[_bubbles.size()-1].setTextureArea((*_textureAreas)["bubble"]);
        }
    }
}

void Fish::update(float deltaTime)
{
    for(int i=0;i<_bubbles.size();i++)
    {
        _bubbles[i].update(deltaTime);
        if(_bubbles[i].ended())
        {
            _bubbles.erase(_bubbles.begin()+i);
        }
    }
    updateShape();
}

void Fish::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    for(int i=0;i<_bubbles.size();i++)
    {
        target.draw(_bubbles[i],states);
    }
}
