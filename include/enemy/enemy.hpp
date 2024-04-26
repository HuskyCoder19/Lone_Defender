#pragma once
#include <iostream>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "animation/enemyAnimation.hpp"

class Enemy {

    public:

        Enemy();

        ~Enemy();

        bool initialize(sf::RenderTarget& target);

        void render(sf::RenderTarget& target);

        void move(const sf::Vector2f &pos);

        bool isHit(const sf::Vector2f& pos);

        sf::FloatRect getBounds();

        void increaseSpeed();

        bool die();

    private:

        bool initSprite(sf::RenderTarget& target);

        // enemy animation object
        EnemyAnimation* m_pAnimation;

        // sprite variables
        sf::Sprite m_sprite;
        sf::Texture m_texture;

        float m_speed;

};