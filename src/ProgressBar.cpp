#include <cassert>
#include "ProgressBar.h"

ProgressBar::ProgressBar(int width,int height,int range,int value,const sf::Color& barColor)
{
    _range=range;
    _value=value;
    _barFrame=sf::RectangleShape(sf::Vector2f(width,height));
    _progress=sf::RectangleShape(sf::Vector2f(width*(float)_value/_range,height));
    _barFrame.setFillColor(sf::Color(255,255,255));
    _progress.setFillColor(barColor);
    _barFrame.setOrigin(_barFrame.getSize()*0.5f);
}

ProgressBar::ProgressBar(const ProgressBar& pb)
{
    _range=pb._range;
    _value=pb._value;
    _barFrame=pb._barFrame;
    _progress=pb._progress;
}

ProgressBar& ProgressBar::operator =(const ProgressBar& pb)
{
    _range=pb._range;
    _value=pb._value;
    _barFrame=pb._barFrame;
    _progress=pb._progress;
    return *this;
}
void ProgressBar::setPosition(const sf::Vector2f& pos)
{
    _barFrame.setPosition(pos);
    _progress.setPosition(pos-_barFrame.getSize()*0.5f);
}
sf::Vector2f ProgressBar::getPosition() const
{
    return _barFrame.getPosition();
}
void ProgressBar::setValue(int value)
{
    _value=value;
    if(_value>_range)_value=_range;
    if(_value<0.0f) _value=0;
    _progress.setSize(sf::Vector2f(_barFrame.getSize().x*_value/_range,_barFrame.getSize().y));
}

int ProgressBar::getValue() const
{
    return _value;
}

void ProgressBar::setRange(int range)
{
    _range=range;
}

int ProgressBar::getRange() const
{
    return _range;
}

void ProgressBar::setColor(const sf::Color& barColor)
{
    _progress.setFillColor(barColor);
}

sf::Color ProgressBar::getColor() const
{
    return _progress.getFillColor();
}

void ProgressBar::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    states.transform*=getTransform();
    target.draw(_barFrame,states);
    target.draw(_progress,states);
}
