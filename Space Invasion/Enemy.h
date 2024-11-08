#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<iostream>

class Enemy
{
private:
    int type;
    float speed;
    int hp;
    int hpMax;
    int damage;
    int points;
    sf::Sprite rocks;
    sf::Texture texture;

    void initShape();
    void initVariables();
    void initSprite();
    float shootCooldownMax;  // Max cooldown for shooting
    float shootCooldown;     // Current cooldown timer
    void validatePosition(float& posx, float& posy);

public:
    Enemy(float posx, float posy);
    virtual ~Enemy();

    //Accessors
    const sf::FloatRect getbounds() const;
    // Functions
    void update();
    void render(sf::RenderTarget* target);

    void takeDamage(int damage);
    bool isDead() const;
    int getPoints() const;
    int getDamage() const;

    bool canShoot();

};

#endif //ENEMY_H
