#ifndef SHARK_H
#define SHARK_H

#include "Fish.h"

class Shark:public Fish
{
    public:
        enum State {NORMAL,CRAZY,WEAKEN,ATTACKED,SHOT,SHOCKED,DIE};
        enum Type {SHARK1,SHARK2,SHARK_UP1,SHARK_UP2};
        Shark(Type type=SHARK1);
        Shark(const Shark&)=delete;

        Shark& operator=(const Shark&)=delete;

        void init();

        void setNumPartition(int numPartition);
        int getNumPartition() const;
        State getState() const;
        void setTarget(std::shared_ptr<Fish> target);
        std::shared_ptr<Fish> getTarget() const;
        float getSpeed() const;
        void setSize(float size);
        sf::Vector2f getCenter() const;
        float getRadius() const;
        sf::Vector2f getHeadPosition() const;
        void setType(Type type);
        Type getType() const;

        void shocked();
        void shot();
        void hurt();
        virtual void attacked() override;

        virtual void update(float deltaTime) override;
    private:
        virtual void updateShape() override;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
        static const float HEAD_SIZE,TAIL_SIZE,KNOT_DIST,NORMAL_SPEED,CRAZY_SPEED,ESCAPE_SPEED,NORMAL_SIZE,CRAZY_SIZE,ESCAPE_SIZE,WEAKEN_SIZE,ATTACKED_TIME,SHOT_TIME;
        static const int HP;
        int _numPartition;
        sf::VertexArray _body;
        sf::VertexArray _bodyShadow;
        sf::RectangleShape _head,_fins,_tail;
        State _state;
        float _size;
        float _speed;
        float _timer;
        int _current_HP;
        std::shared_ptr<Fish> _target;
        Type _type;
};
#endif
