#ifndef POWER_UP_H
#define POWER_UP_H
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

class PowerUp:public sf::Drawable
{
    public:
        enum TYPE {TIME_MACHINE,OCTOPUS,DECOY,NONE};
        PowerUp(TYPE type);
        PowerUp(const PowerUp& pu)=delete;

        PowerUp& operator=(const PowerUp& pu)=delete;

        void init();
        void setTexture(const std::shared_ptr<sf::Texture>& texture);
        void setTextureAreas(const std::shared_ptr<std::map<std::string,sf::IntRect>>& textureAreas);
        float getSpeed() const;
        float getSize() const;
        sf::Vector2f getPosition() const;
        TYPE getType() const;
        bool disapear() const;

        void update(float deltaTime);

    private:
        static const float SIZE,MAX_SPEED;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;

        TYPE _type;
        sf::RectangleShape _shape;
        std::shared_ptr<sf::Texture> _texture;
        float _speed;
        std::shared_ptr<std::map<std::string,sf::IntRect>> _textureAreas;
};
#endif
