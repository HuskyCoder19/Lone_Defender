#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "animation/playerAnimation.hpp"

class Player {

    public:

        Player();

        ~Player();

        bool initialize(sf::RenderTarget& target);

        void update();

        void render(sf::RenderTarget& target);

        void move(float x, float y);

        bool attack();

        sf::Vector2f getPosition();

        sf::Vector2f getSwordPos();

        void hitPlayer();

        void hitEnemy();

        int getScore();

        int getHealth();

        void addHealth();

        bool isAlive();

        bool playerDie();

        bool canAttack();

        bool isAttacking();

        void enableAttack();

    private:

        bool initSprite(sf::RenderTarget& target);

        sf::Sprite m_sprite;
        sf::Texture m_texture;

        float m_xBound;
        float m_yBound;

        int m_health;
        int m_score;

        bool m_canAttack;
        bool m_isAttacking;

        PlayerAnimation* m_pAnimation;

        float m_speed;

};