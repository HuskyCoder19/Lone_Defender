#include "game/game.hpp"

using namespace std;

Game::Game() {}

Game::~Game() {
    delete m_window;
    delete m_player;
}

bool Game::initialize() {

    // init window & video mode
    m_videoMode.height = 1000;
    m_videoMode.width = 1100;
    m_window =  new sf::RenderWindow(m_videoMode, "Lone Defender");
    m_window->setFramerateLimit(144);
    m_window->setVerticalSyncEnabled(false);

    m_mouseLeft = false;

    // init player
    m_player = new Player();
    m_player->initialize(*m_window);

    m_hitMarker = new HitMarker();
    m_hitMarker->initialize();

    m_isHit = false;
    m_markerCount = 0;

    // init enemies
    m_maxEnemies = 6;
    m_enemySpawnTimer = 0.f;
    m_enemySpawnTimerMax = 100.f;

    // init game variables
    m_level = 1;
    m_isOver = false;
    m_levelIncr = 15;
    m_levelUpVal = 15;

    initFonts();
    initText();

    return true;
}

void Game::initFonts() {
    if (!m_font.loadFromFile("../assets/fonts/Oswald-Bold.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

void Game::initText() {
    
    // score
    m_pointsText.setFont(m_font);
    m_pointsText.setCharacterSize(20);
    m_pointsText.setFillColor(sf::Color::White);
    m_pointsText.setString("Score");
    m_pointsText.setPosition(10, 10);

    // health
    m_healthText.setFont(m_font);
    m_healthText.setCharacterSize(20);
    m_healthText.setFillColor(sf::Color::White);
    m_healthText.setString("Health");
    m_healthText.setPosition(10, 35);

    // level
    m_levelText.setFont(m_font);
    m_levelText.setCharacterSize(20);
    m_levelText.setFillColor(sf::Color::Green);
    m_levelText.setString("Level");
    m_levelText.setPosition(10, 60);

    // game over
    m_overText.setFont(m_font);
    m_overText.setCharacterSize(80);
    m_overText.setFillColor(sf::Color::Blue);
    m_overText.setString("Game Over!");
    m_overText.setOrigin(m_overText.getLocalBounds().width / 2, m_overText.getLocalBounds().height / 2);
    float xPos = m_window->getSize().x / 2;
    float yPos = m_window->getSize().y / 2;
    m_overText.setPosition(xPos, yPos);

}

void Game::gameLoop() {

    while(m_window->isOpen()) {
        pollEvent();
        update();
        render();
    }

}

void Game::pollEvent() {

    while (m_window->pollEvent(m_event)) {
        switch (m_event.type) {
            case sf::Event::Closed:
                m_window->close();
                break;
        }
    }
}

void Game::update() {
    
    // handle game updates

    if (!m_player->isAlive()) {
        // death animation
        m_isOver = m_player->playerDie();
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_player->move(-1.f, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_player->move(1.f, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_player->move(0.f, -1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_player->move(0.f, 1.f);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (m_player->canAttack()) m_mouseLeft = true;
    } else if (!m_player->isAttacking()) {
        m_player->enableAttack();
    }

    if (m_mouseLeft) {
        if (!m_player->attack()) {
            m_mouseLeft = false;
        }
    }

    updateEnemies();

    // update hit marker
    if (m_isHit) {
        if (m_markerCount <= 30) {
            m_hitMarker->setPosition(m_player->getPosition());
            m_markerCount++;
        }
        else {
            m_markerCount = 0;
            m_isHit = false;
        }
    }

    updateText();

}

void Game::render() {
    // handle window rendering
    m_window->clear();

    m_player->render(*m_window);

    if (m_isHit) m_hitMarker->render(*m_window);

    renderEnemies();

    renderText();

    m_window->display();
}

void Game::updateEnemies() {

    // update timer for enemy spawning
    if (m_enemies.size() < m_maxEnemies) {
        if (m_enemySpawnTimer >= m_enemySpawnTimerMax) {
            m_enemySpawnTimer = 0.f; // reset timer
        } else {
            spawnEnemies(); // spawn a new enemy
            m_enemySpawnTimer += 1.f; // increment timer
        }
    }

    // update all enemies
    for (int i = 0 ; i < m_enemies.size() ; i++) {
        
        m_enemies[i]->move(m_player->getPosition());
        
        if (m_mouseLeft && m_enemies[i]->isHit(m_player->getSwordPos())) {
            // delete enemy if it was hit by the sword while attacking
            m_dyingEnemies.push_back(m_enemies[i]); // add to dying enemy vector
            m_enemies.erase(m_enemies.begin() + i); // erase from alive enemy vector
            
            hitEnemy();
        }
        else if (m_enemies[i]->getBounds().contains(m_player->getPosition())) {
            // delete enemy if it reached the player
            delete m_enemies[i];
            m_enemies.erase(m_enemies.begin() + i);
            
            hitPlayer();
        }

    }

    updateDyingEnemies();

}

void Game::renderEnemies() {

    for (int i = 0 ; i < m_enemies.size() ; i++) {
        m_enemies[i]->render(*m_window);
    }

    renderDyingEnemies();

}

void Game::renderDyingEnemies() {

    for (int i = 0 ; i < m_dyingEnemies.size() ; i++) {
        m_dyingEnemies[i]->render(*m_window);
    }

}

void Game::spawnEnemies() {
    Enemy* e = new Enemy();
    e->initialize(*m_window);
    m_enemies.push_back(e);
}

void Game::updateText() {

    string str = "Score : " + to_string(m_player->getScore());
    m_pointsText.setString(str);

    str = "Health : " + to_string(m_player->getHealth());
    m_healthText.setString(str);

    str = "Level : " + to_string(m_level);
    m_levelText.setString(str);

}

void Game::renderText() {

    m_window->draw(m_pointsText);
    m_window->draw(m_healthText);
    m_window->draw(m_levelText);

    if (m_isOver) {
        // render game over text
        m_window->draw(m_overText);
    }

}

void Game::hitEnemy() {

    m_player->hitEnemy();

    int score = m_player->getScore();

    if (score >= m_levelUpVal) {
        nextLevel();
    }

}

void Game::hitPlayer() {

    m_isHit = true;
    m_hitMarker->setPosition(m_player->getPosition());
    m_player->hitPlayer();

}

void Game::nextLevel() {

    m_level++;
    m_player->addHealth();

    m_maxEnemies += 2;

    m_levelIncr += 5;
    m_levelUpVal += m_levelIncr;
    
    // increase the speed of the enemies
    for (int i = 0 ; i < m_enemies.size() ; i++) {
        m_enemies[i]->increaseSpeed();
    }
}

void Game::updateDyingEnemies() {

    for (int i = 0 ; i < m_dyingEnemies.size() ; i++) {
        if (m_dyingEnemies[i]->die()) {
            delete m_dyingEnemies[i];
            m_dyingEnemies.erase(m_dyingEnemies.begin() + i);
        }
    }

}
