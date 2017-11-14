#ifndef EEL_H
#define EEL_H

#include "Fish.h"

class Eel:public Fish
{
    public:
        enum State {NORMAL,CHARGE,RELEASE,RELEASED,DISAPEAR};

        Eel();
        Eel(const Eel&)=delete;

        Eel& operator=(const Eel&)=delete;
        void init();
        State getState() const;
        float getAttackRadius() const;
        float getTriggerRadius() const;
        sf::Vector2f getCenter() const;
        
        void triggered();

        virtual void update(float deltaTime) override;
        virtual void updateShape() override;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;

        sf::VertexArray _body;
        sf::RectangleShape _mouth;
        sf::RectangleShape _left_eye;
        sf::RectangleShape _right_eye;
        sf::RectangleShape _front_left_fin;
        sf::RectangleShape _front_right_fin;
        sf::RectangleShape _back_left_fin;
        sf::RectangleShape _back_right_fin;
        sf::RectangleShape _tail;
        sf::CircleShape _triggerArea;
        sf::CircleShape _attackArea;
        float _timer;
        State _state;

        float _moveAngle;
        static const int PARTITION;
        static const sf::Color BODY_COLOR;
        static const float  WIDTH,LENGTH,TOTAL_TIME,CHARGE_TIME,RELEASE_TIME,ATTACK_RADIUS,TRIGGER_RADIUS,BLINK_TIME;
};
#endif
