#include "Projectile.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction)
{
    this->speed = 5.f;
    this->direction = direction;

    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        this->direction.x /= length;
        this->direction.y /= length;
    }

    this->sprite.setPosition(position);
    // this->sprite.setTexture(/* load projectile texture here */);

    // Optional: Rotate sprite to face direction of travel
    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
    this->sprite.setRotation(angle);
}

void Projectile::update()
{
    // Move the projectile in the specified direction
    sf::Vector2f movement = direction * speed;
    this->sprite.move(movement);
}

void Projectile::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}

sf::FloatRect Projectile::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

bool Projectile::isOffScreen(const sf::RenderTarget& target) const
{
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2u windowSize = target.getSize();

    return (pos.x < 0 || pos.x > windowSize.x ||
        pos.y < 0 || pos.y > windowSize.y);
}