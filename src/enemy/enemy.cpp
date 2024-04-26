#include "enemy/enemy.hpp"

Enemy::Enemy() {}

Enemy::~Enemy() {
    delete m_pAnimation;
}

bool Enemy::initialize(sf::RenderTarget& target) {

    if (!initSprite(target)) return false;

    m_pAnimation = new EnemyAnimation();
    if (m_pAnimation->initialize(&m_sprite)) return false;

    return true;
}

bool Enemy::initSprite(sf::RenderTarget& target) {
    
    // load texture and set to sprite
    if (!m_texture.loadFromFile("../assets/textures/BODY_skeleton.png")) {
        std::cerr << "[Enemy] error: Failed to load texture\n";
        return false;
    }

    //set texture to sprite
    m_sprite.setTexture(m_texture);
    sf::IntRect textureRect = sf::IntRect(0, 0, 64, 64);
    m_sprite.setTextureRect(textureRect);

    m_sprite.setScale(1.2f, 1.2f);

    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

    // set position randomnly on x or y axis
    float xPos, yPos;

    // generate two random booleans for each axis
    bool randomBool = static_cast<bool>(rand() % 2);
    if (randomBool) {
        // randomly place on x axis
        xPos = static_cast<float>(rand() % target.getSize().x);
        // place on either y = 0 or y = height
        randomBool = static_cast<bool>(rand() % 2);
        if (randomBool) {
            yPos = target.getSize().y;
        } else {
            yPos = 0.f;
        }
    } else {
        //randomly place on y axis
        yPos = static_cast<float>(rand() % target.getSize().y);
        // place on either x = 0 or x = width
        randomBool = static_cast<bool>(rand() % 2);
        if (randomBool) {
            xPos = target.getSize().x;
        } else {
            xPos = 0.f;
        }
    }

    m_sprite.setPosition(xPos, yPos);
    m_speed = .6;

    return true;
}

void Enemy::render(sf::RenderTarget& target) {
    target.draw(m_sprite);
}

void Enemy::move(const sf::Vector2f &pos) {

    float x = 0.f;
    float y = 0.f;

    if (abs(pos.x - m_sprite.getPosition().x) >  abs(pos.y - m_sprite.getPosition().y)) {
        // change x position
        if (m_sprite.getPosition().x > pos.x) {
            x = -1.f;
            m_pAnimation->moveLeft();
        } else if (m_sprite.getPosition().x < pos.x) {
            x = 1.f;
            m_pAnimation->moveRight();
        }
    }
    else {
        // change y position
        if (m_sprite.getPosition().y > pos.y) {
            y = -1.f;
            m_pAnimation->moveUp();
        } else if (m_sprite.getPosition().y < pos.y) {
            y = 1.f;
            m_pAnimation->moveDown();
        }
    }

    m_sprite.move(m_speed * x, m_speed * y);
}

bool Enemy::isHit(const sf::Vector2f& pos) {

    if (m_sprite.getGlobalBounds().contains(pos)) {
        return true;
    }

    return false;
}

sf::FloatRect Enemy::getBounds() {
    return m_sprite.getGlobalBounds();
}

void Enemy::increaseSpeed() {
    if (m_speed < 1.7) {
        m_speed += 0.1;
    }
}

bool Enemy::die() {

    // death animation
    return m_pAnimation->die();
}
