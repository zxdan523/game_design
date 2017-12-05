#include "GameView.h"

GameView::GameView(const std::shared_ptr<Larry>& larry_ptr,
                   const std::shared_ptr<std::vector<std::shared_ptr<Minions>>>& minions_ptr,
                   const std::shared_ptr<Shark>& shark_ptr1,
                   const std::shared_ptr<Shark>& shark_ptr2,
                   const std::shared_ptr<Eel>& eel_ptr,
                   const std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>>& swordfish_ptr,
                   const std::shared_ptr<PowerUpSystem>& powerup_ptr,
                   const std::shared_ptr<MusicManager>& musicManager_ptr,
                   const std::shared_ptr<TextureManager>& textureManager_ptr)
{
    _larry_ptr=larry_ptr;
    _minions_ptr=minions_ptr;
    _shark_ptr1=shark_ptr1;
    _shark_ptr2=shark_ptr2;
    _eel_ptr=eel_ptr;
    _swordfish_ptr=swordfish_ptr;
    _powerup_ptr=powerup_ptr;
    _musicManager_ptr=musicManager_ptr;
    _textureManager_ptr=textureManager_ptr;
    _showShark1=false;
    _showShark2=false;
    _showEel=false;
    _showSwordfish=false;
    _showEelBar=false;
    _showSwordfishBar=false;
    _eelBar=std::make_shared<ProgressBar>(WINDOW_WIDTH/5,10,100,0,sf::Color::Yellow);
    _swordfishBar=std::make_shared<ProgressBar>(WINDOW_WIDTH/5,10,100,0,sf::Color(0,63,167));
    _sharkBar=std::make_shared<ProgressBar>(WINDOW_WIDTH/3,10,1000,0,sf::Color(73,73,73));
    _eelBar->setPosition(sf::Vector2f(WINDOW_WIDTH*4/5,50));
    _swordfishBar->setPosition(sf::Vector2f(WINDOW_WIDTH*4/5,50));
    _eelLogo=sf::RectangleShape(sf::Vector2f(100,100));
    _eelLogo.setOrigin(0,50);
    _eelLogo.setPosition(sf::Vector2f(WINDOW_WIDTH*4/5+WINDOW_WIDTH/10,50));
    _eelLogo.setTexture(_textureManager_ptr->get().texture.get());
    _eelLogo.setTextureRect((*_textureManager_ptr->get().areas)["Eel"]);
    _swordfishLogo=sf::RectangleShape(sf::Vector2f(100,50));
    _swordfishLogo.setOrigin(0,25);
    _swordfishLogo.setPosition(sf::Vector2f(WINDOW_WIDTH*4/5+WINDOW_WIDTH/10,50));
    _swordfishLogo.setTexture(_textureManager_ptr->get().texture.get());
    _swordfishLogo.setTextureRect((*_textureManager_ptr->get().areas)["Swordfish"]);

    _sharkBar->setPosition(sf::Vector2f(WINDOW_WIDTH/3,50));
    _shark1Logo=sf::RectangleShape(sf::Vector2f(100,100));
    _shark2Logo=sf::RectangleShape(sf::Vector2f(100,100));
    _shark1Logo.setTexture(_textureManager_ptr->get().texture.get());
    _shark1Logo.setTextureRect((*_textureManager_ptr->get().areas)["Shark1"]);

    _shark1Logo.setPosition(sf::Vector2f(WINDOW_WIDTH/3+WINDOW_WIDTH/6-20,20));
    _shark2Logo.setPosition(sf::Vector2f(WINDOW_WIDTH/3+WINDOW_WIDTH/6+30,10));
    _shark2Logo.setTexture(_textureManager_ptr->get().texture.get());
    _shark2Logo.setTextureRect((*_textureManager_ptr->get().areas)["Shark2"]);

    _bgImg=sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));

}

void GameView::playMusic(std::string name) const
{
    _musicManager_ptr->play(name);
}

void GameView::stopMusic() const
{
    _musicManager_ptr->stop();
}

void GameView::playIntro() 
{
    _playIntro=true;
}

void GameView::stopPlayIntro()
{
    _playIntro=false;
}

void GameView::addBackgroundImage(sf::Texture* texture)
{
    _bgImg.setTexture(texture);
}

void GameView::playBackgroundMusic(std::string name)
{
    _musicManager_ptr->playBackground(name);
}
void GameView::resetSwordfishPtr(const std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>>& swordfish_ptr)
{
    _swordfish_ptr=swordfish_ptr;
}

void GameView::enableShark1()
{
    _showShark1=true;
}

void GameView::disableShark1()
{
    _showShark1=false;
}

void GameView::enableShark2()
{
    _showShark2=true;
}

void GameView::disableShark2()
{
    _showShark2=false;
}

void GameView::enableEel()
{
    _showEel=true;
}

void GameView::disableEel()
{
    _showEel=false;
}

void GameView::enableSwordfish()
{
    _showSwordfish=true;
}

void GameView::disableSwordfish()
{
    _showSwordfish=false;
}

void GameView::enableEelBar()
{
    _showEelBar=true;
}

void GameView::disableEelBar()
{
    _showEelBar=false;
}

void GameView::enableSwordfishBar()
{
    _showSwordfishBar=true;
}

void GameView::disableSwordfishBar()
{
    _showSwordfishBar=false;
}

void GameView::setEelBar(float val)
{
    _eelBar->setValue(val*_eelBar->getRange());
}

void GameView::setSwordfishBar(float val)
{
    _swordfishBar->setValue(val*_swordfishBar->getRange());
}

void GameView::setSharkBar(float val)
{
    _sharkBar->setValue(val*_sharkBar->getRange());
}

void GameView::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(_bgImg,states);
    if(_playIntro) return;
    if(_minions_ptr!=nullptr)
    {
        for(size_t i=0;i!=_minions_ptr->size();i++)
        {
            target.draw(*((*_minions_ptr)[i]),states);
        }
    }
    if(_showSwordfish&&_swordfish_ptr!=nullptr)
    {
        for(size_t i=0;i!=_swordfish_ptr->size();i++)
        {
            target.draw(*((*_swordfish_ptr)[i]),states);
        }
    }
    if(_showShark1&&_shark_ptr1!=nullptr)
    {
        target.draw(*_shark_ptr1,states);
    }
    if(_showShark2&&_shark_ptr2!=nullptr)
    {
        target.draw(*_shark_ptr2,states);
    }
    if(_showEel&&_eel_ptr!=nullptr)
    {
        target.draw(*_eel_ptr,states);
    }
    if(_larry_ptr!=nullptr)
    {
        target.draw(*_larry_ptr,states);
    }
    if(_powerup_ptr!=nullptr)
    {
        target.draw(*_powerup_ptr,states);
    }
    if(_showEelBar)
    {
        target.draw(*_eelBar,states);
        target.draw(_eelLogo,states);
    }
    if(_showSwordfishBar)
    {
        target.draw(*_swordfishBar,states);
        target.draw(_swordfishLogo,states);
    }
    target.draw(*_sharkBar,states);
    target.draw(_shark1Logo,states);
    target.draw(_shark2Logo,states);
}

