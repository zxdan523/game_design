#include "util.h"
#include "Constants.h" 
#include "PowerUp.h"
#include <cassert>

const float PowerUp::SIZE=50.0f;
const float PowerUp::MAX_SPEED=100.0f;

PowerUp::PowerUp(PowerUp::TYPE type)
{
    _type=type;
    _shape=sf::RectangleShape(sf::Vector2f(SIZE,SIZE));
    _shape.setOrigin(_shape.getSize()*0.5f);
    _shape.setPosition(sf::Vector2f(randomInt(WINDOW_WIDTH-SIZE)+SIZE/2,WINDOW_HEIGHT));
    _speed=randomFloat(MAX_SPEED*0.5f,MAX_SPEED);
}

void PowerUp::init()
{
    assert(_texture!=nullptr);
    assert(_textureAreas!=nullptr);
    _shape.setTexture(_texture.get());
    switch(_type)
    {
        case TIME_MACHINE:
            _shape.setTextureRect((*_textureAreas)["TimeMachineBubble"]);
            break;
        case OCTOPUS:
            _shape.setTextureRect((*_textureAreas)["OctopusBubble"]);
            break;
        case DECOY:
            _shape.setTextureRect((*_textureAreas)["DecoyBubble"]);
            break;
        default:
            break;
    }
}

void PowerUp::setTexture(const std::shared_ptr<sf::Texture>& texture)
{
    _texture=texture;
}

void PowerUp::setTextureAreas(const std::shared_ptr<std::map<std::string,sf::IntRect>>& textureAreas)
{
    _textureAreas=textureAreas;
}

float PowerUp::getSpeed() const
{
    return _speed;
}

float PowerUp::getSize() const
{
    return SIZE;
}

sf::Vector2f PowerUp::getPosition() const
{
    return _shape.getPosition();
}

PowerUp::TYPE PowerUp::getType() const
{
    return _type;
}

bool PowerUp::disapear() const
{
    return _shape.getPosition().y<=0;
}
void PowerUp::update(float deltaTime)
{
    if(_shape.getPosition().y>0)
    {
        _shape.move(0.0f,-_speed*deltaTime);
    }
}

void PowerUp::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(_shape,states);
}
