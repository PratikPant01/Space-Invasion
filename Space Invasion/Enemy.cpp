#include "Enemy.h"
#include<random>
// Initialize variables (type, hp, damage, etc.)
void Enemy::initVariables()
{
    this->speed = 2.f;
    this->type = 0;
    this->hp = 0;
    this->hpMax = 10;
    this->damage = 1;
    this->points = 5;
    this->shootCooldownMax = 120.f;
    this->shootCooldown = this->shootCooldownMax;
}

// Load the texture and handle potential errors
void Enemy::initShape()
{
    if (!this->texture.loadFromFile("Textures/rock.png"))
    {
        std::cerr << "ERROR::ENEMY::Failed to load texture from file" << std::endl;
    }
}

// Initialize the sprite with the loaded texture


void Enemy::initSprite()
{
    // Define the scale range (e.g., between 0.5 and 2.0)
    const float minScale = 0.01f;
    const float maxScale = 0.1f;

    // Generate a random float between minScale and maxScale
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister engine for generating random numbers
    std::uniform_real_distribution<float> dis(minScale, maxScale);

    float scaleFactor = dis(gen); // Random scaling factor

    this->rocks.setTexture(this->texture);

    // Resize the sprite using the random scale factor
    this->rocks.scale(scaleFactor, scaleFactor);
}


// Constructor with position validation
Enemy::Enemy(float posx, float posy)
{
    this->initVariables();
    this->initShape();
    this->initSprite();

    this->validatePosition(posx, posy);
    this->rocks.setPosition(posx, posy);



}

bool Enemy::canShoot() {
    if (this->shootCooldown >= this->shootCooldownMax) {
        this->shootCooldown = 0.f;
        return true;
    }
    return false;
}

Enemy::~Enemy()
{
}

// Function to validate and adjust the enemy's initial position if necessary
void Enemy::validatePosition(float& posx, float& posy)
{
    // Define the screen bounds
    const float screenWidth = 800.0f;
    const float screenHeight = 600.0f;

    // Adjust position if it's outside the screen bounds
    if (posx < 0.0f) posx = 0.0f;
    if (posy < 0.0f) posy = 0.0f;
    if (posx > screenWidth - this->rocks.getGlobalBounds().width)
        posx = screenWidth - this->rocks.getGlobalBounds().width;
    if (posy > screenHeight - this->rocks.getGlobalBounds().height)
        posy = screenHeight - this->rocks.getGlobalBounds().height;
}

const sf::FloatRect Enemy::getbounds() const
{
    return this->rocks.getGlobalBounds();
}

// Update method (expand with enemy behavior as needed)
void Enemy::update()
{
    this->rocks.move(0.f, speed);

    if (this->shootCooldown < this->shootCooldownMax)
        this->shootCooldown += 1.f;
}

// Render the enemy on the screen
void Enemy::render(sf::RenderTarget* target)
{
    if (target)
    {
        target->draw(this->rocks);
    }
}

void Enemy::takeDamage(int damage) {
    this->hp -= damage;
    if (this->hp < 0) this->hp = 0;
}

bool Enemy::isDead() const {
    return this->hp <= 0;
}

int Enemy::getPoints() const {
    return this->points;
}

int Enemy::getDamage() const {
    return this->damage;
}