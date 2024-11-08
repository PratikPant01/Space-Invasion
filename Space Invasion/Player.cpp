#include "Player.h"

// Initialize variables (movement speed, attack cooldown, etc.)
void Player::initVariables() {
    this->movementSpeed = 2.f;
    this->attackCooldownmax = 10.f;
    this->attackCooldown = this->attackCooldownmax;
    this->hp = 100;
    this->hpMax = 100;
    this->score = 0;
}

void Player::initTexture() {
    if (!this->texture.loadFromFile("Textures/space2.png")) {
        std::cout << "Something went wrong: Player texture loading" << "\n";
    }
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.1f, 0.1f);  // Scaling the sprite down to fit the game
}

// Constructor
Player::Player() {
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

// Destructor
Player::~Player() {}

// Position getter
const sf::Vector2f& Player::getPos() const {
    return this->sprite.getPosition();
}

// Move the player and constrain within window bounds
void Player::move(const float dx, const float dy) {
    sf::Vector2f newPos = this->sprite.getPosition() + sf::Vector2f(this->movementSpeed * dx, this->movementSpeed * dy);

    // Constrain movement within the window bounds
    if (newPos.x < 0)
        newPos.x = 0;
    if (newPos.x > 800 - this->sprite.getGlobalBounds().width)  // Assuming window width is 800
        newPos.x = 800 - this->sprite.getGlobalBounds().width;
    if (newPos.y < 0)
        newPos.y = 0;
    if (newPos.y > 600 - this->sprite.getGlobalBounds().height)  // Assuming window height is 600
        newPos.y = 600 - this->sprite.getGlobalBounds().height;

    this->sprite.setPosition(newPos);
}

// Player health and score functions
void Player::takeDamage(int damage) {
    this->hp -= damage;
    if (this->hp < 0) this->hp = 0;  // Prevent negative health
}

void Player::addScore(int points) {
    this->score += points;
}

bool Player::isAlive() const {
    return this->hp > 0;  // Player is alive if HP > 0
}

int Player::getHp() const {
    return this->hp;
}

int Player::getScore() const {
    return this->score;
}

int Player::getHpMax() const {
    return this->hpMax;
}

void Player::resetHp() {
    this->hp = this->hpMax;  // Reset health to maximum value
}

sf::FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();  // Returns the bounds of the player sprite
}

// Attack functions
const bool Player::canAttack() {
    if (this->attackCooldown >= this->attackCooldownmax) {
        this->attackCooldown = 0.f;
        return true;  // Ready to attack
    }
    return false;  // Not ready to attack
}

void Player::updateAttack() {
    if (this->attackCooldown < this->attackCooldownmax)
        this->attackCooldown += 0.5f;  // Increment attack cooldown, you can adjust this rate
}

// Update and render functions
void Player::update() {
    this->updateAttack();  // Update attack cooldown
}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);  // Draw the player sprite
}
void Player::setPosition(float x, float y)
{
    this->sprite.setPosition(x, y);
}