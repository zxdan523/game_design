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

        virtual void updateShape() override;
    private:
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
        int _numPartition;
        sf::VertexArray _body;
        sf::RectangleShape _mouth,_fin_big_left,_fin_big_right,_fin_tiny_left,_fin_tiny_right,_tail,_eye_left,_eye_right;
};
#endif
