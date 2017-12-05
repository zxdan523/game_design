#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "PowerUpSystem.h"
#include "Larry.h"
#include "Minions.h"
#include "Shark.h"
#include "Eel.h"
#include "Swordfish.h"
#include "MusicManager.h"
#include "TextureManager.h"
#include "ProgressBar.h"
#include "Constants.h"

class GameView:public sf::Drawable
{
    public:
        GameView(const std::shared_ptr<Larry>& larry_ptr,
                 const std::shared_ptr<std::vector<std::shared_ptr<Minions>>>& minions_ptr,
                 const std::shared_ptr<Shark>& shark_ptr1,
                 const std::shared_ptr<Shark>& shark_ptr2,
                 const std::shared_ptr<Eel>& eel_ptr,
                 const std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>>& swordfish_ptr,
                 const std::shared_ptr<PowerUpSystem>& powerup_ptr,
                 const std::shared_ptr<MusicManager>& musicManager_ptr,
                 const std::shared_ptr<TextureManager>& textureManager_ptr);

        void playMusic(std::string name) const;
        void stopMusic() const;

        void resetSwordfishPtr(const std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>>& swordfish_ptr);
        void addBackgroundImage(sf::Texture* texture);

        void playIntro();
        void stopPlayIntro();

        void enableShark1();
        void disableShark1();
        void enableShark2();
        void disableShark2();
        void enableEel();
        void disableEel();
        void enableSwordfish();
        void disableSwordfish();

        void enableEelBar();
        void disableEelBar();
        void enableSwordfishBar();
        void disableSwordfishBar();

        void setEelBar(float val);
        void setSwordfishBar(float val);
        void setSharkBar(float val);

    private:
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
        std::shared_ptr<Larry> _larry_ptr;
        std::shared_ptr<std::vector<std::shared_ptr<Minions>>> _minions_ptr;
        std::shared_ptr<Shark> _shark_ptr1;
        std::shared_ptr<Shark> _shark_ptr2;
        std::shared_ptr<Eel> _eel_ptr;
        std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>> _swordfish_ptr;
        std::shared_ptr<PowerUpSystem> _powerup_ptr;
        std::shared_ptr<MusicManager> _musicManager_ptr;
        std::shared_ptr<TextureManager> _textureManager_ptr;
        bool _showShark1,_showShark2,_showEel,_showSwordfish,_showEelBar,_showSwordfishBar;
        std::shared_ptr<ProgressBar> _eelBar,_swordfishBar,_sharkBar;
        sf::RectangleShape _eelLogo,_swordfishLogo,_shark1Logo,_shark2Logo,_bgImg;
        bool _playIntro;
};
#endif
