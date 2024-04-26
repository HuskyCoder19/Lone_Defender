#include "animation/enemyAnimation.hpp"

EnemyAnimation::EnemyAnimation() {}

EnemyAnimation::~EnemyAnimation() {}

bool EnemyAnimation::initialize(sf::Sprite* pSprite) {

    m_pSprite = pSprite;

    m_dir = up;
    
    // initialize indexes of the frame vectors
    m_downInd = 0;
    m_rightInd = 0;
    m_upInd = 0;
    m_leftInd = 0;

    float pixelFrame = 0.f;

    for (int i = 1 ; i <= 9 ; i++) {

        m_upFrames.push_back(sf::IntRect(pixelFrame, 0, 64, 64));
        m_leftFrames.push_back(sf::IntRect(pixelFrame, 64, 64, 64));
        m_downFrames.push_back(sf::IntRect(pixelFrame, 128, 64, 64));
        m_rightFrames.push_back(sf::IntRect(pixelFrame, 192, 64, 64));

        pixelFrame += 64;
    }

    m_dieInd = 0.f;
    m_dieCount = 0;

    return true;
}

void EnemyAnimation::moveUp() {

    m_dir = up;

    if (m_upInd >= m_upFrames.size()) {
        m_upInd = 0;
    }

    m_pSprite->setTextureRect(m_upFrames[m_upInd]);
    m_upInd++;
}

void EnemyAnimation::moveLeft() {

    m_dir = left;

    if (m_leftInd >= m_leftFrames.size()) {
        m_leftInd = 0;
    }

    m_pSprite->setTextureRect(m_leftFrames[m_leftInd]);
    m_leftInd++;
}

void EnemyAnimation::moveDown() {

    m_dir = down;

    if (m_downInd >= m_downFrames.size()) {
        m_downInd = 0;
    }

    m_pSprite->setTextureRect(m_downFrames[m_downInd]);
    m_downInd++;
}

void EnemyAnimation::moveRight() {

    m_dir = right;

    if (m_rightInd >= m_rightFrames.size()) {
        m_rightInd = 0;
    }

    m_pSprite->setTextureRect(m_rightFrames[m_rightInd]);
    m_rightInd++;
}

bool EnemyAnimation::die() {


    if (m_dieCount == 100) return true;

    if (m_dieInd == 14) {
        m_dieCount++;
    } 
    else {

        if (m_dir == up || m_dir == left) {
            if (m_dieInd == 0) m_pSprite->setTextureRect(m_leftFrames[0]);
            m_pSprite->rotate(m_dieInd);
        } else {
            if (m_dieInd == 0) m_pSprite->setTextureRect(m_rightFrames[0]);
            m_pSprite->rotate(-m_dieInd);
        }

        m_dieInd += 1;

    }

    return false;

}
