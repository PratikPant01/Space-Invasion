#pragma once
#include <SFML/Graphics.hpp>

class Projectile
{
private:
    sf::Sprite sprite;
    sf::Vector2f direction;
    float speed;

public:
    // Constructor takes position and normalized direction vector
    Projectile(sf::Vector2f position, sf::Vector2f direction);

    // Core functions
    void update();
    void render(sf::RenderTarget& target);

    // Utility functions
    sf::FloatRect getBounds() const;
    bool isOffScreen(const sf::RenderTarget& target) const;

    // Getters
    const sf::Vector2f& getPosition() const { return sprite.getPosition(); }
    const sf::Vector2f& getDirection() const { return direction; }
};