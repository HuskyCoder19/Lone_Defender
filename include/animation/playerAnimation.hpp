#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// builds the animation for the player from sprite sheet

class PlayerAnimation {

    public:

        PlayerAnimation();

        ~PlayerAnimation();

        bool initilaize(sf::Sprite* pSprite);

        void moveRight();

        void moveLeft();

        void moveUp();

        void moveDown();

        bool attack();

        sf::Vector2f getSwordPos();

        bool die();

    private:

        enum Direction {
            right,
            left,
            up,
            down
        };

        bool renderAttack();

        sf::Sprite* m_pSprite;

        // vector frame indexes
        int m_downInd;
        int m_rightInd;
        int m_upInd;
        int m_leftInd;
        
        int m_attackInd;
        bool m_attacking;

        int m_dieInd;

        Direction m_dir;

        sf::Vector2f m_swordPos;

        // vector storing frames for each type of movement within sprite sheet
        std::vector<sf::IntRect> m_leftFrames;
        std::vector<sf::IntRect> m_rightFrames;
        std::vector<sf::IntRect> m_upFrames;
        std::vector<sf::IntRect> m_downFrames;

        std::vector<sf::IntRect> m_leftAttackFrames;
        std::vector<sf::IntRect> m_rightAttackFrames;
        std::vector<sf::IntRect> m_upAttackFrames;
        std::vector<sf::IntRect> m_downAttackFrames;

        std::vector<sf::IntRect> m_dieFrames;

};