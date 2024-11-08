// Star.h
#pragma once
#include<SFML/Graphics.hpp>

class Star {
public:
    Star(float x, float y, float radius);

    void update();
    void render(sf::RenderTarget& target);

private:
    sf::CircleShape shape;
    float speed;
    float twinkleSpeed;
    float twinkleOffset;
    sf::Vector2f velocity; // Velocity for movement

};
