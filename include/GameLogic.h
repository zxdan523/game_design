#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SFML/Graphics.hpp>
#include "GameView.h"
#include "AIView.h"
#include "TextureManager.h"

class GameLogic
{
    public:
        enum Stage{PREPARE,WAIT_EEL,EEL_IN,WAIT_SWORDFISH,SWORDFISH_IN};
        GameLogic(const std::shared_ptr<Larry>& larry,
                  const std::shared_ptr<std::vector<std::shared_ptr<Minions>>>& minions,
                  const std::shared_ptr<std::vector<std::vector<std::shared_ptr<Swordfish>>>>& swordfish,
                  const std::shared_ptr<Shark>& shark1,
                  const std::shared_ptr<Shark>& shark2,
                  const std::shared_ptr<Eel>& eel,
                  const std::shared_ptr<PowerUpSystem>& powerup,
                  const std::shared_ptr<GameView>& gameView,
                  const std::shared_ptr<AIView>& aiView,
                  const std::shared_ptr<TextureManager>& textureManager);
        GameLogic(const GameLogic&)=delete;

        GameLogic& operator=(const GameLogic&)=delete;

        void levelStart();
        void run(float deltaTime);
        void levelEnd();

        void keyPressed(int keyCode,float mouseX,float mouseY);
        void mouseMoved(float mouseX,float mouseY);

        void countEel(float deltaTime);
        void updateEel(float deltaTime);
        void countSwordfish(float deltaTime);
        void updateSwordfish(float deltaTime);
        void countMinions(float deltaTime);
        void updateMinions(float deltaTime);

    private:
        static const int MINIONS_NUM;
        static const float PREPARE_TIME,EEL_TIME,SWORDFISH_TIME,MINIONS_TIME;
        std::shared_ptr<Larry> _larry;
        std::shared_ptr<std::vector<std::shared_ptr<Minions>>> _minions;
        std::shared_ptr<std::vector<std::vector<std::shared_ptr<Swordfish>>>> _swordfish;
        std::shared_ptr<Shark> _shark1;
        std::shared_ptr<Shark> _shark2;
        std::shared_ptr<Eel> _eel;
        std::shared_ptr<PowerUpSystem> _powerup;
        std::shared_ptr<GameView> _gameView;
        std::shared_ptr<AIView> _aiView;
        std::shared_ptr<TextureManager> _textureManager;
        float _timer;
        float _eelTimer;
        float _swordfishTimer;
        float _minionsTimer;
        float _levelTime;
        int _swordfishId;
        bool _sharkIn;
        Stage _stage;
};
#endif
