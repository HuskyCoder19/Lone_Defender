#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "player/player.hpp"
#include "enemy/enemy.hpp"
#include "hitMarker.hpp"

class Game {

    public:

        Game();

        ~Game();

        bool initialize();

        void gameLoop();

    private:

        // init functions
        void initFonts();
        void initText();

        // main game loop funcions
        void pollEvent();
        void update();
        void render();
        
        // enemy functions
        void updateEnemies();
        void renderEnemies();
        void spawnEnemies();
        void updateDyingEnemies();
        void renderDyingEnemies();

        // text functions 
        void updateText();
        void renderText();

        // game functions 
        void hitPlayer();
        void hitEnemy();
        void nextLevel();

        // window variables
        sf::RenderWindow* m_window;
        sf::VideoMode m_videoMode;
        sf::Event m_event;

        //resources
        sf::Font m_font;
        sf::Text m_pointsText;
        sf::Text m_healthText;
        sf::Text m_levelText;
        sf::Text m_overText;

        // player vars
        Player* m_player;
        HitMarker* m_hitMarker;
        bool m_isHit;
        int m_markerCount;

        // enemy variables
        std::vector<Enemy*> m_enemies;
        std::vector<Enemy*> m_dyingEnemies;
        int m_maxEnemies;
        float m_enemySpawnTimer;
        float m_enemySpawnTimerMax;

        // game vars
        int m_level;
        bool m_isOver;
        int m_levelIncr;
        int m_levelUpVal; // required score to increment level

        // button pressed booleans
        bool m_mouseLeft;

};