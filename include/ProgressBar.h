#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <map>

class ProgressBar:public sf::Drawable,public sf::Transformable
{
    public:
        ProgressBar(int width,int height,int range,int value,const sf::Color& barColor);
        ProgressBar(const ProgressBar& pb);

        ProgressBar& operator =(const ProgressBar& pb);
        
        void setPosition(const sf::Vector2f& pos);
        sf::Vector2f getPosition() const;
        void setValue(int value);
        int getValue() const;
        void setRange(int range);
        int getRange() const;
        void setColor(const sf::Color& barColor);
        sf::Color getColor() const;

    private:

        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;

        sf::RectangleShape _progress;
        sf::RectangleShape _barFrame;
        int _value;
        int _range;
};
#endif
