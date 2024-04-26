#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class EnemyAnimation {

    public:

        EnemyAnimation();

        ~EnemyAnimation();

        bool initialize(sf::Sprite* pSprite);

        void moveDown();

        void moveUp();

        void moveRight();

        void moveLeft();

        bool die();

    private:

        enum Direction {
            right,
            left,
            up,
            down
        };

        sf::Sprite* m_pSprite;

        Direction m_dir;

        // vector frame indexes
        int m_downInd;
        int m_rightInd;
        int m_upInd;
        int m_leftInd;

        // vector storing frames for each type of movement within sprite sheet
        std::vector<sf::IntRect> m_leftFrames;
        std::vector<sf::IntRect> m_rightFrames;
        std::vector<sf::IntRect> m_upFrames;
        std::vector<sf::IntRect> m_downFrames;

        // variables for the death animation sprite rotation
        float m_dieInd;
        int m_dieCount;

};