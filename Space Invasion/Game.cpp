#include "Game.h"

void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Invasion", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit((int)144);
	this->window->setVerticalSyncEnabled(false);
}
void Game::initPlayer()
{
	this->player = new Player();


}

void Game::initStars()
{
	srand(static_cast<unsigned>(time(0))); // Seed random number generator

	int numStars = 100; // Number of stars
	for (int i = 0; i < numStars; ++i)
	{
		float x = static_cast<float>(rand() % this->window->getSize().x);
		float y = static_cast<float>(rand() % this->window->getSize().y);
		float radius = static_cast<float>(rand() % 3 + 1); // Random radius between 1 and 3

		this->stars.push_back(new Star(x, y, radius));
	}
}

void Game::initEnemies()
{
	this->spawnTimer = 0.f;
	this->spawnTimerMax = 50.f;
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");

}

//con/des
Game::Game()
{
	this->initwindow();
	this->initStars();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
	this->initUI();

}
Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->enemy;

	//delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	//delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//delete all enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
	for (auto* i : this->stars) // Clean up stars
	{
		delete i;
	}

}
//functions

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{

	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->player->move(0.f, 1.f);

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()))
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 32, this->player->getPos().y, 0.f, -1.f, 5.f));

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 32, this->player->getPos().y, 0.f, -1.f, 5.f));

	}
}



void Game::updateStars()
{
	for (auto* star : this->stars)
	{
		star->update();
	}
}


void Game::update() {
	this->updatePollEvents();
	this->updateInput();
	this->updateStars();
	this->player->update();
	this->updateBullets();
	this->updateEnemies();
	this->updateUI();  // Update UI elements
	this->updateEnemyBullets();  // Update enemy bullets
	this->checkCollisions(); // Check for collisions
}


void Game::render() {
	this->window->clear(sf::Color::Black);

	for (auto* star : this->stars) {
		star->render(*this->window);
	}

	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}

	// Render UI (health and score)
	this->window->draw(this->healthText);
	this->window->draw(this->scoreText);
	this->window->draw(this->healthBarBackground);
	this->window->draw(this->healthBar);

	for (auto* bullet : this->enemyBullets) {
		bullet->render(this->window);
	}

	this->window->display();
}


// Game.cpp

void Game::updateBullets() {
	unsigned counter = 0;

	for (auto* bullet : this->bullets) {
		bullet->update();

		// Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height <= 0.f) {
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			continue;
		}

		// Bullet-Enemy Collision
		bool bulletRemoved = false;
		for (size_t j = 0; j < this->enemies.size() && !bulletRemoved; j++) {
			if (bullet->getBounds().intersects(this->enemies[j]->getbounds())) {
				this->enemies[j]->takeDamage(1); // Assuming bullets deal 1 damage
				if (this->enemies[j]->isDead()) {
					this->player->addScore(this->enemies[j]->getPoints());
					delete this->enemies[j];
					this->enemies.erase(this->enemies.begin() + j);
				}
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				bulletRemoved = true;
			}
		}
		if (!bulletRemoved) ++counter;
	}
}

void Game::updateEnemies() {
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(static_cast<float>(rand() % this->window->getSize().x), -50.f));
		this->spawnTimer = 0.f;
	}

	for (size_t i = 0; i < this->enemies.size(); ++i) {
		this->enemies[i]->update();

		// Enemy shooting logic
		if (this->enemies[i]->canShoot()) {
			this->enemyBullets.push_back(
				new Bullet(this->textures["BULLET"], this->enemies[i]->getbounds().left + this->enemies[i]->getbounds().width / 2,
					this->enemies[i]->getbounds().top + this->enemies[i]->getbounds().height,
					0.f, 1.f, 5.f));  // Downward bullet
		}

		// Remove enemies that go off-screen
		if (this->enemies[i]->getbounds().top > this->window->getSize().y) {
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
			--i;
		}
	}
}

void Game::updateEnemyBullets() {
	for (size_t i = 0; i < this->enemyBullets.size(); ++i) {
		this->enemyBullets[i]->update();

		// Remove bullets that go off the bottom of the screen
		if (this->enemyBullets[i]->getBounds().top > this->window->getSize().y) {
			delete this->enemyBullets[i];
			this->enemyBullets.erase(this->enemyBullets.begin() + i);
			--i;
		}
	}
}





void Game::initUI() {
	// Load font
	if (!this->font.loadFromFile("Fonts/arial.ttf")) {
		std::cerr << "ERROR::GAME::Failed to load font!" << std::endl;
	}

	// Initialize health text
	this->healthText.setFont(this->font);
	this->healthText.setCharacterSize(20);
	this->healthText.setFillColor(sf::Color::White);
	this->healthText.setPosition(20.f, 20.f);

	// Initialize score text
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(20);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setPosition(20.f, 50.f);

	// Initialize health bar background
	this->healthBarBackground.setSize(sf::Vector2f(200.f, 20.f));
	this->healthBarBackground.setFillColor(sf::Color(50, 50, 50, 200));
	this->healthBarBackground.setPosition(20.f, 80.f);

	// Initialize health bar
	this->healthBar.setSize(sf::Vector2f(200.f, 20.f));
	this->healthBar.setFillColor(sf::Color::Green);
	this->healthBar.setPosition(20.f, 80.f);
}
void Game::updateUI() {
	// Update health text
	this->healthText.setString("HP: " + std::to_string(this->player->getHp()) + " / " + std::to_string(this->player->getHpMax()));

	// Update score text
	this->scoreText.setString("Score: " + std::to_string(this->player->getScore()));

	// Update health bar
	float healthPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->healthBar.setSize(sf::Vector2f(200.f * healthPercent, 20.f));
}
void Game::resetGame() {
	// Reset player’s HP and position
	this->player->resetHp();
	this->player->setPosition(this->window->getSize().x / 2.f, this->window->getSize().y - 50.f);

	// Clear enemies and bullets
	for (auto* enemy : this->enemies)
		delete enemy;
	this->enemies.clear();

	for (auto* bullet : this->bullets)
		delete bullet;
	this->bullets.clear();

	for (auto* enemyBullet : this->enemyBullets)
		delete enemyBullet;
	this->enemyBullets.clear();
}
void Game::checkCollisions() {
	// Check collision between enemy bullets and player
	for (size_t i = 0; i < this->enemyBullets.size(); ++i) {
		if (this->enemyBullets[i]->getBounds().intersects(this->player->getBounds())) {
			// Reduce player's HP by 10 if hit
			this->player->takeDamage(10);

			// Delete the bullet
			delete this->enemyBullets[i];
			this->enemyBullets.erase(this->enemyBullets.begin() + i);
			--i;

			// Check if player's HP has reached 0
			if (!this->player->isAlive()) {
				this->resetGame();
				return;
			}
		}
	}

	// Check collision between enemies and player
	for (size_t i = 0; i < this->enemies.size(); ++i) {
		if (this->enemies[i]->getbounds().intersects(this->player->getBounds())) {
			// Reduce player's HP by 50 if collided with enemy
			this->player->takeDamage(50);

			// Delete the enemy
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
			--i;

			// Check if player's HP has reached 0
			if (!this->player->isAlive()) {
				this->resetGame();
				return;
			}
		}
	}
}
