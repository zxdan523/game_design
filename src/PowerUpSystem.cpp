#include <cassert>
#include "util.h"
#include "PowerUpSystem.h"
#include "Constants.h"
const float PowerUpSystem::LOGO_SIZE=50.0f;
const float PowerUpSystem::BAR_WIDTH=200.0f;
const float PowerUpSystem::TOOL_SIZE=50.0f;
const float PowerUpSystem::DURATION=5.0f;
const float PowerUpSystem::OCTOPUS_AREA=200.0f;
const float PowerUpSystem::TOOL_NUM=10.0f;

PowerUpSystem::PowerUpSystem()
{
    _timeMachineBar=std::make_shared<ProgressBar>(BAR_WIDTH,BAR_WIDTH/20.0f,TOOL_NUM,0,sf::Color::Red);
    _octopusBar=std::make_shared<ProgressBar>(BAR_WIDTH,BAR_WIDTH/20.0f,TOOL_NUM,0,sf::Color(184,82,158));
    _decoyBar=std::make_shared<ProgressBar>(BAR_WIDTH,BAR_WIDTH/20.0f,TOOL_NUM,0,sf::Color::Yellow);
    _timeMachineLogo=sf::RectangleShape(sf::Vector2f(LOGO_SIZE,LOGO_SIZE));
    _timeMachineLogo.setOrigin(_timeMachineLogo.getSize()*0.5f);
    _octopusLogo=sf::RectangleShape(sf::Vector2f(LOGO_SIZE,LOGO_SIZE));
    _octopusLogo.setOrigin(_octopusLogo.getSize()*0.5f);
    _decoyLogo=sf::RectangleShape(sf::Vector2f(LOGO_SIZE,LOGO_SIZE));
    _decoyLogo.setOrigin(_decoyLogo.getSize()*0.5f);
    _timeMachineBar->setPosition(sf::Vector2f(WINDOW_WIDTH-20-BAR_WIDTH/2.0f,WINDOW_HEIGHT-3*LOGO_SIZE));
    _timeMachineLogo.setPosition(_timeMachineBar->getPosition()+sf::Vector2f(-BAR_WIDTH/2.0f-LOGO_SIZE/2.0f+10.0f,0.0f));
    _octopusBar->setPosition(sf::Vector2f(WINDOW_WIDTH-20-BAR_WIDTH/2.0f,WINDOW_HEIGHT-2*LOGO_SIZE));
    _octopusLogo.setPosition(_octopusBar->getPosition()+sf::Vector2f(-BAR_WIDTH/2.0f-LOGO_SIZE/2.0f+10.0f,0.0f));
    _decoyBar->setPosition(sf::Vector2f(WINDOW_WIDTH-20-BAR_WIDTH/2.0f,WINDOW_HEIGHT-LOGO_SIZE));
    _decoyLogo.setPosition(_decoyBar->getPosition()+sf::Vector2f(-BAR_WIDTH/2.0f-LOGO_SIZE/2.0f+10.0f,0.0f));

    _timeMachine=sf::RectangleShape(sf::Vector2f(TOOL_SIZE,TOOL_SIZE));
    _timeMachine.setOrigin(_timeMachine.getSize()*0.5f);
    _octopus=sf::RectangleShape(sf::Vector2f(OCTOPUS_AREA,OCTOPUS_AREA));
    _octopus.setOrigin(_octopus.getSize()*0.5f);
    _decoy=sf::RectangleShape(sf::Vector2f(TOOL_SIZE,TOOL_SIZE));
    _decoy.setOrigin(_decoy.getSize()*0.5f);
   
}

void PowerUpSystem::init()
{
    _timeMachineBar->setValue(0);
    _octopusBar->setValue(0);
    _decoyBar->setValue(0);
     _typeInUse=PowerUp::NONE;
    _timer=0;
    assert(_texture!=nullptr);
    assert(_textureAreas!=nullptr);
    _timeMachineLogo.setTexture(_texture.get());
    _timeMachineLogo.setTextureRect((*_textureAreas)["TimeMachineLogo"]);
    _timeMachine.setTexture(_texture.get());
    _timeMachine.setTextureRect((*_textureAreas)["TimeMachine"]);
    _octopusLogo.setTexture(_texture.get());
    _octopusLogo.setTextureRect((*_textureAreas)["OctopusLogo"]);
    _octopus.setTexture(_texture.get());
    _octopus.setTextureRect((*_textureAreas)["Octopus"]);
    _decoyLogo.setTexture(_texture.get());
    _decoyLogo.setTextureRect((*_textureAreas)["DecoyLogo"]);
    _decoy.setTexture(_texture.get());
    _decoy.setTextureRect((*_textureAreas)["Decoy"]);
}

void PowerUpSystem::setTexture(const std::shared_ptr<sf::Texture>& texture)
{
    _texture=texture;
}

void PowerUpSystem::setTextureAreas(const std::shared_ptr<std::map<std::string,sf::IntRect>>& textureAreas)
{
    _textureAreas=textureAreas;
}

void PowerUpSystem::update(float deltaTime)
{
    if(_typeInUse!=PowerUp::NONE)
    {
        _timer-=deltaTime;
    }
    switch(_typeInUse)
    {
        case PowerUp::TIME_MACHINE:
            if(_timer<=0.0f)
            {
                _timeMachineBar->setValue(0);
                _typeInUse=PowerUp::NONE;
            }
            else
            {
                _timeMachineBar->setValue(TOOL_NUM*_timer/DURATION);
                _timeMachine.setFillColor(sf::Color(255,255,255,255*_timer/DURATION));
            }
            break;
        case PowerUp::OCTOPUS:
            if(_timer<=0.0f)
            {
                _octopusBar->setValue(0);
                _typeInUse=PowerUp::NONE;
            }
            else
            {
                _octopusBar->setValue(TOOL_NUM*_timer/DURATION);
                _octopus.setFillColor(sf::Color(255,255,255,255*_timer/DURATION));
            }
            break;
        case PowerUp::DECOY:
            if(_timer<=0.0f)
            {
                _decoyBar->setValue(0);
                _typeInUse=PowerUp::NONE;
            }
            else
            {
                _decoyBar->setValue(TOOL_NUM*_timer/DURATION);
                _decoy.setFillColor(sf::Color(255,255,255,255*_timer/DURATION));
            }
            break;
        case PowerUp::NONE:
            break;
    }

    if(randomInt(600)>599)
    {
        int type=randomInt(10)%3;
        std::shared_ptr<PowerUp> pu=std::make_shared<PowerUp>((PowerUp::TYPE)type);
        pu->setTexture(_texture);
        pu->setTextureAreas(_textureAreas);
        pu->init();
        _powerUp.push_back(pu);
    }
    for(int i=0;i<_powerUp.size();i++)
    {
        _powerUp[i]->update(deltaTime);
        if(_powerUp[i]->disapear())
        {
            _powerUp.erase(_powerUp.begin()+i);
        }
    }
}

bool PowerUpSystem::grabToolBubble(const sf::Vector2f& center,float radius)
{
    bool is_grab=false;
    for(int i=0;i<_powerUp.size();i++)
    {
        if(mag(_powerUp[i]->getPosition()-center)<_powerUp[i]->getSize()*0.5f+radius)
        {
            is_grab=true;
            PowerUp::TYPE type=_powerUp[i]->getType();
            int value=0;
            switch(type)
            {
                case PowerUp::TIME_MACHINE:
                    value=_timeMachineBar->getValue()+1;
                    if(value>=TOOL_NUM)
                    {
                        value=TOOL_NUM;
                    }
                    _timeMachineBar->setValue(value);
                    break;
                case PowerUp::OCTOPUS:
                    value=_octopusBar->getValue()+1;
                    if(value>=TOOL_NUM)
                    {
                        value=TOOL_NUM;
                    }
                    _octopusBar->setValue(value);
                    break;
                case PowerUp::DECOY:
                    value=_decoyBar->getValue()+1;
                    if(value>=TOOL_NUM)
                    {
                        value=TOOL_NUM;
                    }
                    _decoyBar->setValue(value);
                    break;
                case PowerUp::NONE:
                    break;
            }
            _powerUp.erase(_powerUp.begin()+i);
        }
    }
    return is_grab;
}

void PowerUpSystem::useTool(PowerUp::TYPE type,sf::Vector2f pos)
{
    if(_typeInUse==PowerUp::NONE)
    {
        switch(type)
        {
            case PowerUp::TIME_MACHINE:
                if(_timeMachineBar->getValue()==TOOL_NUM)
                {
                    _timeMachine.setPosition(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT)*0.5f);
                    _typeInUse=type;
                    _timer=DURATION;
                }
                break;
            case PowerUp::OCTOPUS:
                if(_octopusBar->getValue()==TOOL_NUM)
                {
                    _octopus.setPosition(pos);
                    _typeInUse=type;
                    _timer=DURATION;
                }
                break;
            case PowerUp::DECOY:
                if(_decoyBar->getValue()==TOOL_NUM)
                {
                    _decoy.setPosition(pos);
                    _typeInUse=type;
                    _timer=DURATION;
                }
                break;
            case PowerUp::NONE:
                break;
        }
    }
}

std::shared_ptr<sf::RectangleShape> PowerUpSystem::getToolInUse() const
{
    std::shared_ptr<sf::RectangleShape> shape;
    switch(_typeInUse)
    {
        case PowerUp::TIME_MACHINE:
            shape=std::make_shared<sf::RectangleShape>(_timeMachine);
            break;
        case PowerUp::OCTOPUS:
            shape=std::make_shared<sf::RectangleShape>(_octopus);
            break;
        case PowerUp::DECOY:
            shape=std::make_shared<sf::RectangleShape>(_decoy);
            break;
        case PowerUp::NONE:
            break;
    }
    return shape;
}

PowerUp::TYPE PowerUpSystem::getTypeInUse() const
{
    return _typeInUse;
}

float PowerUpSystem::getOctopusArea() const
{
    return OCTOPUS_AREA;
}

void PowerUpSystem::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(*_timeMachineBar);
    target.draw(*_octopusBar);
    target.draw(*_decoyBar);
    target.draw(_timeMachineLogo);
    target.draw(_octopusLogo);
    target.draw(_decoyLogo);
    switch(_typeInUse)
    {
        case PowerUp::TIME_MACHINE:
            target.draw(_timeMachine,states);
            break;
        case PowerUp::OCTOPUS:
            target.draw(_octopus,states);
            break;
        case PowerUp::DECOY:
            target.draw(_decoy,states);
            break;
        case PowerUp::NONE:
            break;
    }

    for(int i=0;i<_powerUp.size();i++)
    {
        target.draw(*_powerUp[i],states);
    }

    
}
