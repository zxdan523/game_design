#ifndef POWER_UP_SYSTEM
#define POWER_UP_SYSTEM
#include <SFML/Graphics.hpp>
#include <vector>
#include "PowerUp.h"
#include "ProgressBar.h"

class PowerUpSystem:public sf::Drawable
{
    public:
        PowerUpSystem();
        PowerUpSystem(const PowerUpSystem&)=delete;

        PowerUpSystem& operator=(const PowerUpSystem&)=delete;

        void init();
        void setTexture(const std::shared_ptr<sf::Texture>& texture);
        void setTextureAreas(const std::shared_ptr<std::map<std::string,sf::IntRect>>& textureAreas);

        void update(float deltaTime);

        void grabToolBubble(const sf::Vector2f& center,float radius);
        void useTool(PowerUp::TYPE type,sf::Vector2f pos);
        std::shared_ptr<sf::RectangleShape> getToolInUse() const;
        PowerUp::TYPE getTypeInUse() const;
        float getOctopusArea() const;



    private:
        static const float LOGO_SIZE,BAR_WIDTH,TOOL_SIZE,DURATION,OCTOPUS_AREA,TOOL_NUM;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;

        std::vector<std::shared_ptr<PowerUp>> _powerUp;
        std::shared_ptr<ProgressBar> _timeMachineBar;
        std::shared_ptr<ProgressBar> _octopusBar;
        std::shared_ptr<ProgressBar> _decoyBar;
        sf::RectangleShape _timeMachineLogo;
        sf::RectangleShape _octopusLogo;
        sf::RectangleShape _decoyLogo;
        sf::RectangleShape _timeMachine;
        sf::RectangleShape _octopus;
        sf::RectangleShape _decoy;
        PowerUp::TYPE _typeInUse;
        float _timer;
        std::shared_ptr<sf::Texture> _texture;
        std::shared_ptr<std::map<std::string,sf::IntRect>> _textureAreas;

};
#endif
