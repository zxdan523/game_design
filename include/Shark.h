#ifndef SHARK_H
#define SHARK_H

#include "Fish.h"

class Shark:public Fish
{
    public:
        enum State {NORMAL,CRAZY,WEAKEN,DIE}; 
        Shark();
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

        void shocked();
        void shot();

        virtual void update(float deltaTime) override;
    private:
        virtual void updateShape() override;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
        static const float HEAD_SIZE,TAIL_SIZE,KNOT_DIST,NORMAL_SPEED,CRAZY_SPEED,ESCAPE_SPEED,NORMAL_SIZE,CRAZY_SIZE,ESCAPE_SIZE,WEAKEN_SIZE;
        static const int HP;
        int _numPartition;
        sf::VertexArray _body;
        sf::VertexArray _bodyShadow;
        sf::RectangleShape _head,_fins,_tail;
        State _state;
        float _size;
        float _speed;
        int _current_HP;
        std::shared_ptr<Fish> _target;
};
#endif
