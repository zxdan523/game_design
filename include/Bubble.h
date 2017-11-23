#ifndef BUBBLE_H
#define BUBBLE_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <string>
class Bubble:public sf::Drawable, public sf::Transformable
{
    public:
        Bubble(const sf::Vector2f& pos=sf::Vector2f(),const sf::Vector2f& vel=sf::Vector2f(1.0f,0.0f));
        Bubble(const Bubble& bubble);

        Bubble& operator=(const Bubble& bubble);
        void setPosition(const sf::Vector2f& pos);
        sf::Vector2f getPosition() const;
        void setVelocity(const sf::Vector2f& vel);
        sf::Vector2f getVelocity() const;
        void setLifeTime(float lifeTime);
        float getLifeTime() const;

        void setTexture(const std::shared_ptr<sf::Texture>& texture);
        void setTextureArea(const sf::IntRect& area);

        void update(float deltaTime);
        bool ended() const;
    private:
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;

        static const float RESIST;
        sf::RectangleShape _shape;
        sf::Vector2f _pos;
        sf::Vector2f _vel;
        float _lifeTime;
        float _timer;
};
#endif
