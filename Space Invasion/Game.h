#pragma once
#include <map>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Star.h"

class Game {
private:
    // Window
    sf::RenderWindow* window;

    // Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> enemyBullets;  // Separate vector for enemy bullets
    std::vector<Star*> stars;

    // Player
    Player* player;

    // Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;
	Enemy* enemy;

    // UI Elements
    sf::Font font;
    sf::Text healthText;
    sf::Text scoreText;
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBar;

    // Private functions
    void initwindow();
    void initPlayer();
    void initStars();
    void initTextures();
    void initEnemies();
    void initUI();



    void updateEnemyBullets();
    void checkCollisions();    // New function to check for collisions
    void resetGame();          // New function to reset the game state

public:
    Game();
    virtual ~Game();

    // Main game functions
    void run();
    void updatePollEvents();
    void updateInput();
    void updateEnemies();
    void updateBullets();
    void updateStars();
    void update();
    void render();
    void updateUI();
};
