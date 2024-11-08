#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

    int hp;
    int hpMax;
    int score;

    float movementSpeed;
    float attackCooldown;
    float attackCooldownmax;

    void initVariables();
    void initTexture();
    void initSprite();

public:
    Player();
    virtual ~Player();

    void takeDamage(int damage);
    void addScore(int points);
    bool isAlive() const;
    int getHp() const;
    int getHpMax() const;
    int getScore() const;

    // Declare the functions here, make sure they're not static
    void resetHp();  // Reset the health to max value
    sf::FloatRect getBounds() const;  // Get the player's bounding box

    const sf::Vector2f& getPos() const;
    void move(const float dx, const float dy);
    const bool canAttack();
    void updateAttack();
    void update();
    void render(sf::RenderTarget& target);

    void setPosition(float x, float y);

};
