#ifndef MINIONS_H
#define MINIONS_H

#include "Fish.h"
class Minions:public Fish
{
    public:
        enum State {NORMAL,WEAK,DIE,SHOCKED,SHOT,ATTACK,ATTACK_END};
        
        Minions(sf::Vector2f pos=sf::Vector2f());
        Minions(const Minions&)=delete;

        Minions& operator=(const Minions&)=delete;

        void init();
        State getState() const;
        float getAttackRadius() const;
        void setAttackTarget(const std::shared_ptr<Fish>& attackTarget);
        const std::shared_ptr<Fish>& getAttackTarget() const;
        float getSpeed() const;

        void attacking();
        void shot();
        void shocked();
        void weaken();
        void recovered();
        void defeated();

        virtual void update(float deltaTime) override;
    private:
        virtual void updateShape() override;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;

        std::shared_ptr<Fish> _attackTarget;
        sf::RectangleShape _body;
        float _attackRadius;
        float _timer;
        float _speed;
        State _state;
        static const float NORMAL_SIZE,WEAK_SIZE,WEAK_TIME,SHOT_TIME, NORMAL_SPEED, ATTACK_SPEED,ATTACK_RADIUS, ESCAPE_SPEED;
};
#endif
