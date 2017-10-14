#include <cassert>
#include "Knot.h"

Knot::Knot()
{
    _width=0.0f;
    _height=0.0f;
    setPosition(sf::Vector2f(0.0f,0.0f));
    _vertices=std::vector<sf::Vector2f>(4);
    updateVertices();
}
Knot::Knot(float width,float height,const sf::Vector2f& pos)
{
    _width=width;
    _height=height;
    setPosition(pos);
    _vertices=std::vector<sf::Vector2f>(4);
    updateVertices();
}

Knot::Knot(const Knot& k)
{
    _width=k._width;
    _height=k._height;
    setPosition(k.getPosition());
    setRotation(k.getRotation());
    setScale(k.getScale());
    _vertices=std::vector<sf::Vector2f>(4);
    updateVertices();
}

Knot& Knot::operator=(const Knot& k)
{
    _width=k._width;
    _height=k._height;
    setPosition(k.getPosition());
    setRotation(k.getRotation());
    setScale(k.getScale());
    updateVertices();
    return *this;
}

void Knot::setRect(float width,float height)
{
    _width=width;
    _height=height;
    updateVertices();
}

void Knot::setWidth(float width)
{
    _width=width;
    updateVertices();
}

void Knot::setHeight(float height)
{
    _height=height;
    updateVertices();
}

float Knot::getWidth() const
{
    return _width;
}

float Knot::getHeight() const
{
    return _height;
}

void Knot::updateVertices()
{
    _vertices[0]=sf::Vector2f(0.0f,-_height/2.0f);
    _vertices[1]=sf::Vector2f(0.0f,_height/2.0f);
    _vertices[2]=sf::Vector2f(-_width,_height/2.0f);
    _vertices[3]=sf::Vector2f(-_width,-_height/2.0f);
}

sf::Vector2f Knot::getVertex(int i) const
{
    assert(i<4);
    return getTransform()*_vertices[i];
}
