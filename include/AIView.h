#ifndef AI_VIEW_H
#define AI_VIEW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "PowerUpSystem.h"
#include "Larry.h"
#include "Minions.h"
#include "Shark.h"
#include "Eel.h"
#include "Swordfish.h"
#include "Constants.h"

class AIView
{
    public:
        AIView(const std::shared_ptr<Larry>& larry_ptr,
               const std::shared_ptr<std::vector<std::shared_ptr<Minions>>>& minions_ptr,
               const std::shared_ptr<Shark>& shark_ptr1,
               const std::shared_ptr<Shark>& shark_ptr2,
               const std::shared_ptr<Eel>& eel_ptr,
               const std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>>& swordfish_ptr,
               const std::shared_ptr<PowerUpSystem>& powerup_ptr);

        void resetSwordfishPtr(const std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>>& swordfish_ptr);
        void update(float deltaTime);
        void updateMinions(float deltaTime);
        void updateShark(const std::shared_ptr<Shark>& shark,float deltaTime);
        
        void enableShark1();
        void disableShark1();
        void enableShark2();
        void disableShark2();
        void enableEel();
        void disableEel();
        void enableSwordfish();
        void disableSwordfish();

        void goToTarget(const std::shared_ptr<Minions>& minions,float deltaTime);
        void goToTarget(const std::shared_ptr<Shark>& shark,float deltaTime);
        void escapeFromTarget(const std::shared_ptr<Minions>& minions,float deltaTime);
        void escapeFromTarget(const std::shared_ptr<Shark>& shark,float deltaTime);
        void goToPosition(const std::shared_ptr<Minions>& minions,const sf::Vector2f& pos);
        void goToPosition(const std::shared_ptr<Shark>& shark,const sf::Vector2f& pos);
        void clearDeadMinions();
        void clearTarget(const std::shared_ptr<Fish>& target);
        std::shared_ptr<Fish> findNearestTarget(const std::shared_ptr<Fish>& fish);

    private:
        std::shared_ptr<Larry> _larry_ptr;
        std::shared_ptr<std::vector<std::shared_ptr<Minions>>> _minions_ptr;
        std::shared_ptr<Shark> _shark_ptr1;
        std::shared_ptr<Shark> _shark_ptr2;
        std::shared_ptr<Eel> _eel_ptr;
        std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>> _swordfish_ptr;
        std::shared_ptr<PowerUpSystem> _powerup_ptr;
        bool _enableShark1,_enableShark2,_enableEel,_enableSwordfish;
};
#endif
