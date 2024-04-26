#include "animation/playerAnimation.hpp"

PlayerAnimation::PlayerAnimation() {}

PlayerAnimation::~PlayerAnimation() {}

bool PlayerAnimation::initilaize(sf::Sprite* pSprite) {

    m_pSprite = pSprite;
    
    // initialize indexes of the frame vectors
    m_downInd = 0;
    m_rightInd = 0;
    m_upInd = 0;
    m_leftInd = 0;

    m_attackInd = 0;
    m_attacking = false;

    m_dieInd = 0;

    m_dir = down;

    m_swordPos.x = 0.f;
    m_swordPos.y = 0.f;

    // loop through the texture png dimenstions -- this is highly specific right now
    // store left, right, up, down frames in the sprite sheet
    
    int pixelFrame = 0;
    
    for (int i = 1 ; i <= 11 ; i++) {
        if (i <= 8) {
            m_downFrames.push_back(sf::IntRect(pixelFrame, 0, 64, 64));
            m_rightFrames.push_back(sf::IntRect(pixelFrame, 64, 64, 64));
            m_upFrames.push_back(sf::IntRect(pixelFrame, 128, 64, 64));
            m_leftFrames.push_back(sf::IntRect(pixelFrame, 192, 64, 64));
            pixelFrame += 64;
        } else {

            sf::IntRect downRect = sf::IntRect(pixelFrame, 0, 61, 64);
            sf::IntRect rightRect = sf::IntRect(pixelFrame, 64, 61, 64);
            sf::IntRect upRect = sf::IntRect(pixelFrame, 128, 61, 64);
            sf::IntRect leftRect = sf::IntRect(pixelFrame, 192, 61, 64);

            for (int j = 1 ; j <= 4 ; j++) {
                m_downAttackFrames.push_back(downRect);
                m_rightAttackFrames.push_back(rightRect);
                m_upAttackFrames.push_back(upRect);
                m_leftAttackFrames.push_back(leftRect);
            }

            pixelFrame += 61;
        }
        if (i == 8) pixelFrame += 9; 
    }

    // build full attack animation off of initial three frames
    std::reverse(m_downAttackFrames.begin(), m_downAttackFrames.end());
    std::reverse(m_rightAttackFrames.begin(), m_rightAttackFrames.end());
    std::reverse(m_upAttackFrames.begin(), m_upAttackFrames.end());
    std::reverse(m_leftAttackFrames.begin(), m_leftAttackFrames.end());

    for (int i = m_downAttackFrames.size()-1 ; i >= 0 ; i--) {
        if (i == m_downAttackFrames.size()-1) {
            for (int j = 1 ; j <= 10 ; j++) {
                m_downAttackFrames.push_back(m_downAttackFrames[i]);
                m_rightAttackFrames.push_back(m_rightAttackFrames[i]);
                m_upAttackFrames.push_back(m_upAttackFrames[i]);
                m_leftAttackFrames.push_back(m_leftAttackFrames[i]);
            }
        }
        m_downAttackFrames.push_back(m_downAttackFrames[i]);
        m_rightAttackFrames.push_back(m_rightAttackFrames[i]);
        m_upAttackFrames.push_back(m_upAttackFrames[i]);
        m_leftAttackFrames.push_back(m_leftAttackFrames[i]);
    }

    pixelFrame = 0;

    // death frames
    for (int i = 1 ; i <= 5 ; i++) {

        sf::IntRect dieRect(pixelFrame, 256, 64, 64);
        for (int j = 1 ; j <= 15 ; j++) {
            m_dieFrames.push_back(dieRect);
        }
        pixelFrame += 64;
    }

    return true;
}

void PlayerAnimation::moveDown() {

    m_dir = down;

    if (m_attacking) {
        return;
    }

    if (m_downInd >= m_downFrames.size()) {
        m_downInd = 0;
    }

    m_pSprite->setTextureRect(m_downFrames[m_downInd]);
    m_downInd++;
}

void PlayerAnimation::moveRight() {

    m_dir = right;

    if (m_attacking) {
        return;
    }

    if (m_rightInd >= m_rightFrames.size()) {
        m_rightInd = 0;
    }

    m_pSprite->setTextureRect(m_rightFrames[m_rightInd]);
    m_rightInd++;
}

void PlayerAnimation::moveUp() {

    m_dir = up;

    if (m_attacking) {
        return;
    }

    if (m_upInd >= m_upFrames.size()) {
        m_upInd = 0;
    }

    m_pSprite->setTextureRect(m_upFrames[m_upInd]);
    m_upInd++;
}

void PlayerAnimation::moveLeft() {

    m_dir = left;

    if (m_attacking) {
        return;
    }

    if (m_leftInd >= m_leftFrames.size()) {
        m_leftInd = 0;
    }

    m_pSprite->setTextureRect(m_leftFrames[m_leftInd]);
    m_leftInd++;
}

bool PlayerAnimation::attack() {

    m_attacking = true;
    return renderAttack();
}

bool PlayerAnimation::renderAttack() {

    if (m_attackInd >= m_downAttackFrames.size()) {
        m_attacking = false;
        m_attackInd = 0;
        return false;
    }

    switch (m_dir) {
        case down:
            m_pSprite->setTextureRect(m_downAttackFrames[m_attackInd]);
            m_swordPos.x = -10.f;
            m_swordPos.y = 32.f;
            break;
        case right:
            m_pSprite->setTextureRect(m_rightAttackFrames[m_attackInd]);
            m_swordPos.x = 30.f;
            m_swordPos.y = -5.f;
            break;
        case up:
            m_pSprite->setTextureRect(m_upAttackFrames[m_attackInd]);
            m_swordPos.x = 10.f;
            m_swordPos.y = -32.f;
            break;
        case left:
            m_pSprite->setTextureRect(m_leftAttackFrames[m_attackInd]);
            m_swordPos.x = -30.f;
            m_swordPos.y = -5.f;
            break;
        default:
            break;
    }

    m_attackInd++;

    return true;
}

sf::Vector2f PlayerAnimation::getSwordPos() {

    return m_pSprite->getPosition() + m_swordPos;

}

bool PlayerAnimation::die() {
    if (m_dieInd < m_dieFrames.size()) {
        m_pSprite->setTextureRect(m_dieFrames[m_dieInd]);
        m_dieInd++;
        return false;
    }
    return true;
}
