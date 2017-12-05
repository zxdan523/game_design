#ifndef LARRY_H
#define LARRY_H

#include "Fish.h"

class Larry:public Fish
{
    public:
        Larry();
        Larry(const Larry&)=delete;

        Larry& operator=(const Larry&)=delete;

        void init();

        void setNumPartition(int numPartition);
        int getNumPartition() const;

        bool isDead() const;

        virtual void attacked() override;

        virtual void update(float deltaTime) override;
    private:
        static const float KNOT_DIST;
        virtual void updateShape() override;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
        bool _dead;
        int _numPartition;
        sf::VertexArray _body;
        sf::VertexArray _back_fin;
        sf::RectangleShape _mouth,_fin_big_left,_fin_big_right,_fin_tiny_left,_fin_tiny_right,_tail,_eye_left,_eye_right;
};
#endif
