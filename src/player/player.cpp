#include "player/player.hpp"

Player::Player() {}

Player::~Player() {
    delete m_pAnimation;
}

bool Player::initialize(sf::RenderTarget& target) {

    m_speed = 2.f;

    if (!initSprite(target)) return false;

    m_pAnimation = new PlayerAnimation();
    if (!m_pAnimation->initilaize(&m_sprite)) return false;

    m_xBound = target.getSize().x;
    m_yBound = target.getSize().y;

    m_health = 10;
    m_score = 0;

    m_canAttack = true;
    m_isAttacking = false;
    
    return true;
}

void Player::update() {}

void Player::render(sf::RenderTarget& target) {
    target.draw(m_sprite);
}

bool Player::initSprite(sf::RenderTarget& target) {
    
    // load texture and set to sprite
    if (!m_texture.loadFromFile("../assets/textures/goblinsword.png")) return false;
    
    m_sprite.setTexture(m_texture);
    sf::IntRect textureRect = sf::IntRect(0, 0, 64, 64);
    m_sprite.setTextureRect(textureRect);
    
    m_sprite.setScale(1.5, 1.5);
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
    
    float xPos = target.getSize().x / 2;
    float yPos = target.getSize().y / 2;
    m_sprite.setPosition(xPos, yPos);

    return true;
}

void Player::move(float x, float y) {

    if (x > 0) {
        m_pAnimation->moveRight();
    } else if (x < 0) {
        m_pAnimation->moveLeft();
    } else if (y > 0) {
        m_pAnimation->moveDown();
    } else if (y < 0) {
        m_pAnimation->moveUp();
    }

    float width = m_sprite.getLocalBounds().width;
    float height = m_sprite.getLocalBounds().height;

    float xMov = m_sprite.getPosition().x + m_speed * x;
    float yMov = m_sprite.getPosition().y + m_speed * y;

    if (xMov > 0 && xMov < (m_xBound - 30)) {
        // can move in x direction
        m_sprite.move(m_speed * x, 0.f);
    }
    if (yMov > 0 && yMov < (m_yBound - 30)) {
        // can move in y direction
        m_sprite.move(0.f, m_speed * y);
    }
}

bool Player::attack() {
    m_canAttack = false; // disable attacking while current attack in progress
    if (m_pAnimation->attack()) {
        m_isAttacking = true;
        return true;
    } else {
        m_isAttacking = false;
        return false;
    }
    return m_pAnimation->attack();
}

sf::Vector2f Player::getPosition() {
    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    float centerX = bounds.left + bounds.width / 2.0f;
    float centerY = bounds.top + bounds.height / 2.0f;
    sf::Vector2f pos(centerX, centerY);
    return pos;
}

sf::Vector2f Player::getSwordPos() {
    return m_pAnimation->getSwordPos();
}

void Player::hitPlayer() {
    m_health--;
}

void Player::hitEnemy() {
    m_score++;
}

int Player::getScore() {
    return m_score;
}

int Player::getHealth() {
    return m_health;
}

void Player::addHealth() {
    m_health = 10; // set health back to ten
}

bool Player::isAlive() {
    return m_health > 0;
}

bool Player::playerDie() {
    // returns true when death animation is complete
    return m_pAnimation->die();
}

bool Player::canAttack() {
    return m_canAttack;
}

bool Player::isAttacking() {
    return m_isAttacking;
}

void Player::enableAttack() {
    m_canAttack = true; // re-enable attacking 
}
