#include <cmath>
#include "GameLogic.h"
#include "Constants.h"
#include "util.h"

const int GameLogic::MINIONS_NUM=10;
const float GameLogic::PREPARE_TIME=3;
const float GameLogic::EEL_TIME=10;
const float GameLogic::SWORDFISH_TIME=10;
const float GameLogic::MINIONS_TIME=30;

GameLogic::GameLogic(const std::shared_ptr<Larry>& larry,
                     const std::shared_ptr<std::vector<std::shared_ptr<Minions>>>& minions,
                     const std::shared_ptr<std::vector<std::vector<std::shared_ptr<Swordfish>>>>& swordfish,
                     const std::shared_ptr<Shark>& shark1,
                     const std::shared_ptr<Shark>& shark2,
                     const std::shared_ptr<Eel>& eel,
                     const std::shared_ptr<PowerUpSystem>& powerup,
                     const std::shared_ptr<GameView>& gameView,
                     const std::shared_ptr<AIView>& aiView,
                     const std::shared_ptr<TextureManager>& textureManager)
{
    _larry=larry;
    _minions=minions;
    _swordfish=swordfish;
    _shark1=shark1;
    _shark2=shark2;
    _eel=eel;
    _powerup=powerup;
    _gameView=gameView;
    _aiView=aiView;
    _textureManager=textureManager;
}

void GameLogic::levelStart()
{
    _gameView->disableEel();
    _gameView->disableShark1();
    _gameView->disableShark2();
    _gameView->disableSwordfish();
    _aiView->disableEel();
    _aiView->disableShark1();
    _aiView->disableShark2();
    _aiView->disableSwordfish();
    _larry->init();
    _shark1->init();
    _shark2->init();
    _eel->init();
    _powerup->init();
    _minions->clear();
    float interval=WINDOW_WIDTH*2.0f/MINIONS_NUM;
    for(size_t i=0;i<MINIONS_NUM/2;i++)
    {
        _minions->push_back(std::make_shared<Minions>(sf::Vector2f(i*interval,0.0f)));
        (*_minions)[_minions->size()-1]->setTexture(_textureManager->get().texture);
        (*_minions)[_minions->size()-1]->setTextureAreas(_textureManager->get().areas);
        (*_minions)[_minions->size()-1]->init();
        (*_minions)[_minions->size()-1]->setAttackTarget(_larry);
        _minions->push_back(std::make_shared<Minions>(sf::Vector2f(i*interval,WINDOW_HEIGHT)));
        (*_minions)[_minions->size()-1]->setTexture(_textureManager->get().texture);
        (*_minions)[_minions->size()-1]->setTextureAreas(_textureManager->get().areas);
        (*_minions)[_minions->size()-1]->init();
        (*_minions)[_minions->size()-1]->setAttackTarget(_larry);
    }

    for(size_t i=0;i<_swordfish->size();i++)
        for(size_t j=0;j<(*_swordfish)[i].size();j++)
        {
            (*_swordfish)[i][j]->init();
        }

    _sharkIn=false;
    _eelTimer=0.0f;
    _swordfishTimer=0.0f;
    _minionsTimer=0.0f;
    _timer=0.0f;
    _levelTime=120.0f;
    _swordfishId=randomInt(_swordfish->size())%_swordfish->size();
    _stage=PREPARE;
}

void GameLogic::run(float deltaTime)
{
    if(!_sharkIn)
    {
        _timer+=deltaTime;
        _gameView->setSharkBar(_timer/_levelTime);
    }
    switch(_stage)
    {
        case PREPARE:
            if(_timer>PREPARE)
            {
                _stage=WAIT_EEL;
            }
            _gameView->enableEelBar();
            _gameView->setEelBar(0);
            break;
        case WAIT_EEL:
            countEel(deltaTime);
            break;
        case EEL_IN:
            updateEel(deltaTime);
            break;
        case WAIT_SWORDFISH:
            countSwordfish(deltaTime);
            break;
        case SWORDFISH_IN:
            updateSwordfish(deltaTime);    
            break;
    }
    _aiView->update(deltaTime);
    countMinions(deltaTime);
    updateMinions(deltaTime);
    _powerup->update(deltaTime);
    _larry->update(deltaTime);
    _powerup->grabToolBubble(_larry->getKnot(0).getPosition(),_larry->getHeadDistance());
    if(_timer>_levelTime)
    {
        _sharkIn=true;
        _timer=0.0f;
    }
        
}

void GameLogic::keyPressed(int keyCode,float mouseX,float mouseY)
{
    sf::Vector2f mousePos(mouseX,mouseY);
    switch(keyCode)
    {
        case sf::Keyboard::A:
            _powerup->useTool(PowerUp::TIME_MACHINE,mousePos);
            break;
        case sf::Keyboard::S:
            _powerup->useTool(PowerUp::OCTOPUS,mousePos);
            break;
        case sf::Keyboard::D:
            _powerup->useTool(PowerUp::DECOY,mousePos);
            break;
    }
}

void GameLogic::mouseMoved(float mouseX,float mouseY)
{
    _larry->swimTo(sf::Vector2f(mouseX,mouseY));
    for(size_t i=0;i<_minions->size();i++)
    {
        Knot knot=(*_minions)[i]->getKnot(0);
        if(mag(knot.getPosition()-_larry->getKnot(0).getPosition())<knot.getWidth()/2&&(*_minions)[i]->getState()==Minions::WEAK)
        {
            (*_minions)[i]->defeated();
        }
    }
    _aiView->clearDeadMinions();
}
void GameLogic::countEel(float deltaTime)
{
    _eelTimer+=deltaTime;
    _gameView->setEelBar(_eelTimer/EEL_TIME);
    if(_eelTimer>EEL_TIME)
    {
        _aiView->enableEel();
        _gameView->enableEel();
        _eel->init();
        _stage=EEL_IN;
    }
}

void GameLogic::updateEel(float deltaTime)
{
    _eel->update(deltaTime);
    if(_eel->getState()==Eel::NORMAL&&mag(_eel->getCenter()-_larry->getKnot(0).getPosition())<_eel->getTriggerRadius())
    {
        _eel->triggered();
    }
    if(_eel->getState()==Eel::RELEASE&&mag(_eel->getCenter()-_larry->getKnot(0).getPosition())<_eel->getAttackRadius())
    {
        _larry->attacked();
    }
    if(_eel->getState()==Eel::DISAPEAR)
    {
        _gameView->disableEelBar();
        _aiView->disableEel();
        _gameView->disableEel();
        _eelTimer=0.0f;
        _stage=WAIT_SWORDFISH;
        _gameView->enableSwordfishBar();
        _gameView->setSwordfishBar(0);
    }
}

void GameLogic::countSwordfish(float deltaTime)
{
    _swordfishTimer+=deltaTime;
    _gameView->setSwordfishBar(_swordfishTimer/SWORDFISH_TIME);
    if(_swordfishTimer>SWORDFISH_TIME)
    {
        _aiView->enableSwordfish();
        _gameView->enableSwordfish();
        for(size_t i=0;i<(*_swordfish)[_swordfishId].size();i++)
        {
            (*_swordfish)[_swordfishId][i]->init();
        }
        _aiView->resetSwordfishPtr(std::make_shared<std::vector<std::shared_ptr<Swordfish>>>((*_swordfish)[_swordfishId]));
        _gameView->resetSwordfishPtr(std::make_shared<std::vector<std::shared_ptr<Swordfish>>>((*_swordfish)[_swordfishId]));
            _stage=SWORDFISH_IN;
    }
}

void GameLogic::updateSwordfish(float deltaTime)
{
    bool swd_end=true;
    for(size_t i=0;i<(*_swordfish)[_swordfishId].size();i++)
    {
        (*_swordfish)[_swordfishId][i]->update(deltaTime);
        swd_end=swd_end&&((*_swordfish)[_swordfishId][i]->getState()==Swordfish::SHOOT_END);
    }
    if(swd_end)
    {
        _gameView->disableSwordfishBar();
        _aiView->disableSwordfish();
        _gameView->disableSwordfish();
        _swordfishTimer=0.0f;
        _stage=WAIT_EEL;
        _swordfishId=randomInt(_swordfish->size())%_swordfish->size();
        _gameView->enableEelBar();
        _gameView->setEelBar(0);
    }
}

void GameLogic::countMinions(float deltaTime)
{
    _minionsTimer+=deltaTime;
    if(_minionsTimer>MINIONS_TIME)
    {
        if(_minions->size()<MINIONS_NUM)
        {
            int interval=2*WINDOW_WIDTH/MINIONS_NUM;
            while(_minions->size()<MINIONS_NUM)
            {
                int num=_minions->size()-1;
                float xpos=0.0f,ypos=0.0f;
                if(num<MINIONS_NUM/2)
                {
                    xpos=num*interval;
                }
                else
                {
                    xpos=(num-MINIONS_NUM/2)*interval;
                    ypos=WINDOW_HEIGHT;
                }
                _minions->push_back(std::make_shared<Minions>(sf::Vector2f(xpos,ypos)));
                (*_minions)[_minions->size()-1]->setTexture(_textureManager->get().texture);
                (*_minions)[_minions->size()-1]->setTextureAreas(_textureManager->get().areas);
                (*_minions)[_minions->size()-1]->init();
                (*_minions)[_minions->size()-1]->setAttackTarget(_larry);

            }
        }
        else
        {
            _minions->push_back(std::make_shared<Minions>(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT/2.0f)));
            (*_minions)[_minions->size()-1]->setTexture(_textureManager->get().texture);
            (*_minions)[_minions->size()-1]->setTextureAreas(_textureManager->get().areas);
            (*_minions)[_minions->size()-1]->init();
            (*_minions)[_minions->size()-1]->setAttackTarget(_larry);
        }
        _minionsTimer=0.0f;
    }
}

void GameLogic::updateMinions(float deltaTime)
{
    for(size_t i=0;i<_minions->size();i++)
    {
        (*_minions)[i]->update(deltaTime);
    }
}
