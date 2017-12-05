#include <cmath>
#include "GameLogic.h"
#include "Constants.h"
#include "util.h"
#include <iostream>
const int GameLogic::MINIONS_NUM=10;
const float GameLogic::PREPARE_TIME=3;
const float GameLogic::EEL_TIME=10;
const float GameLogic::SWORDFISH_TIME=10;
const float GameLogic::MINIONS_TIME=30;
const float GameLogic::INTRO_TIME=10;

GameLogic::GameLogic(const std::shared_ptr<Larry>& larry,
                     const std::shared_ptr<std::vector<std::shared_ptr<Minions>>>& minions,
                     const std::shared_ptr<std::vector<std::vector<std::shared_ptr<Swordfish>>>>& swordfish,
                     const std::shared_ptr<Shark>& shark1,
                     const std::shared_ptr<Shark>& shark2,
                     const std::shared_ptr<Eel>& eel,
                     const std::shared_ptr<PowerUpSystem>& powerup,
                     const std::shared_ptr<GameView>& gameView,
                     const std::shared_ptr<AIView>& aiView,
                     const std::shared_ptr<TextureManager>& textureManager,
                     const std::shared_ptr<std::vector<LevelInfo>> levelInfo)
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
    _levelInfo=levelInfo;
    _currentLevel=0;
}

void GameLogic::levelStart()
{
    if(_currentLevel==5)
    {
        if(!_intro.loadFromFile("../data/win.png"))
        {
            std::cout<<"Cannot open file "<<"../data/win.png"<<std::endl;
        }
        _gameView->addBackgroundImage(&_intro);
        _gameView->playIntro();
        _stage=WIN;
        return;
    }
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
    _shark1->setTarget(_larry);
    _shark2->setTarget(_larry);
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
    LevelInfo level=(*_levelInfo)[_currentLevel];
    //_levelTime=level.getLevelLength();
    _levelTime=10;
    //_gameView->playBackgroundMusic(level.getBackgroundMusic());
    if(!_bgImg.loadFromFile(level.getBackgroundImage()))
    {
        std::cout<<"Cannot open file "<<level.getBackgroundImage()<<std::endl;
    }
    switch(_currentLevel)
    {
        case 0:
            if(!_intro.loadFromFile("../data/level1intro.png"))
            {
                std::cout<<"Cannot open file "<<"../data/level1intro.png"<<std::endl;
            }
            break;
        case 1:
            if(!_intro.loadFromFile("../data/level2intro.png"))
            {
                std::cout<<"Cannot open file "<<"../data/level2intro.png"<<std::endl;
            }
            break;
        case 2:
            if(!_intro.loadFromFile("../data/level3intro.png"))
            {
                std::cout<<"Cannot open file "<<"../data/level3intro.png"<<std::endl;
            }
            break;
        case 3:
            if(!_intro.loadFromFile("../data/level4intro.png"))
            {
                std::cout<<"Cannot open file "<<"../data/level4intro.png"<<std::endl;
            }
            break;
        case 4:
            if(!_intro.loadFromFile("../data/level5intro.png"))
            {
                std::cout<<"Cannot open file "<<"../data/level5intro.png"<<std::endl;
            }
            break;
            
    }
    _gameView->addBackgroundImage(&_intro);
    _gameView->playIntro();
    _swordfishId=randomInt(_swordfish->size())%_swordfish->size();
    _stage=INTRO;
}

void GameLogic::run(float deltaTime)
{
    if(_stage==WIN) return;
    if(!_sharkIn&&_stage!=INTRO)
    {
        _timer+=deltaTime;
        _gameView->setSharkBar(_timer/_levelTime);
    }
    switch(_stage)
    {
        case INTRO:
            _timer+=deltaTime;
            if(_timer>INTRO_TIME)
            {
                _timer=0;
                _stage=PREPARE;
                _gameView->addBackgroundImage(&_bgImg);
                _gameView->stopPlayIntro();
            }
            break;
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
        case WIN:
            break;
    }
    if(_stage==INTRO) return;
    _aiView->update(deltaTime);
    countMinions(deltaTime);
    updateMinions(deltaTime);
    _powerup->update(deltaTime);
    _larry->update(deltaTime);
    _powerup->grabToolBubble(_larry->getKnot(0).getPosition(),_larry->getHeadDistance());
    if(_timer>_levelTime)
    {
        switch(_currentLevel)
        {
            case 0:
                _currentLevel++;
                levelStart();
                break;
            case 1:
                _aiView->enableShark1();
                _gameView->enableShark1();
                _shark1->init();
                _sharkIn=true;
                break;
            case 2:
                _aiView->enableShark2();
                _gameView->enableShark2();
                _shark2->init();
                _sharkIn=true;
                break;
            case 3:
                _aiView->enableShark1();
                _gameView->enableShark1();
                _shark1->setType(Shark::SHARK_UP1);
                _shark1->init();
                _sharkIn=true;
                break;
            case 4:
                _aiView->enableShark1();
                _gameView->enableShark1();
                _aiView->enableShark2();
                _gameView->enableShark2();
                _shark1->setType(Shark::SHARK_UP1);
                _shark1->init();
                _shark2->init();
                _sharkIn=true;
                break;
        }
        _timer=0;
    }
    if(_sharkIn)
    {
        switch(_currentLevel)
        {
            case 0:
                break;
            case 1:
            case 3:
            _shark1->update(deltaTime);
            if(_shark1->getState()==Shark::DIE)
            {
                _sharkIn=false;
                _currentLevel++;
                levelStart();
            }
            break;
            case 2:
            _shark2->update(deltaTime);
            if(_shark2->getState()==Shark::DIE)
            {
                _sharkIn=false;
                _currentLevel++;
                levelStart();
            }
            break;
            case 4:
            _shark1->update(deltaTime);
            _shark2->update(deltaTime);
            if(_shark2->getState()==Shark::DIE&&_shark1->getState()==Shark::DIE)
            {
                _sharkIn=false;
                _currentLevel++;
                levelStart();
            }
            break;
        }
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
        case sf::Keyboard::Return:
            if(_stage==INTRO)
            {
                _gameView->stopPlayIntro();
                _gameView->addBackgroundImage(&_bgImg);
                _timer=0;
                _stage=PREPARE;
            }
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
