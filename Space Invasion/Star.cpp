// Star.cpp
#include "Star.h"

Star::Star(float x, float y, float radius)
{
    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition(x, y);
    this->shape.setOrigin(radius, radius); // Center the circle

    // Randomize twinkle speed and offset
    this->twinkleSpeed = static_cast<float>(rand()) / RAND_MAX * 0.1f; // Random speed between 0 and 0.1
    this->twinkleOffset = static_cast<float>(rand()) / RAND_MAX * 360.0f; // Random initial offset

    // Randomize velocity for movement
    float speed = static_cast<float>(rand()) / RAND_MAX * 0.5f; // Random speed between 0 and 0.5
    this->velocity = sf::Vector2f(
        static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f, // Random direction in x
        static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f  // Random direction in y
    );
    this->velocity = this->velocity * speed;
    this->speed = static_cast<float>(rand()) / RAND_MAX * 1.0f + 1.0f; // Random speed between 1 and 3

}

void Star::update()
{
    // Update the twinkle effect by modifying the radius
    float time = std::sin(this->twinkleOffset + (std::clock() / 1000.0f) * this->twinkleSpeed);
    float scale = 0.1f + 0.5f * time; // Scale between 0.5 and 1.0
    this->shape.setScale(scale, scale);

    // Move the star
    this->shape.move(0.f, this->speed);


    // Wrap around the screen
    if (this->shape.getPosition().x < 0.f) this->shape.setPosition(this->shape.getPosition().x + 800.f, this->shape.getPosition().y); // Wrap around horizontally
    if (this->shape.getPosition().x > 800.f) this->shape.setPosition(this->shape.getPosition().x - 800.f, this->shape.getPosition().y); // Wrap around horizontally
    if (this->shape.getPosition().y < 0.f) this->shape.setPosition(this->shape.getPosition().x, this->shape.getPosition().y + 600.f); // Wrap around vertically
    if (this->shape.getPosition().y > 600.f) this->shape.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - 600.f); // Wrap around vertically
}

void Star::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}
