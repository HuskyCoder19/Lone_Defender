#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class HitMarker {

    public:

        HitMarker();

        ~HitMarker();

        bool initialize();

        void setPosition(sf::Vector2f pos);

        void render(sf::RenderTarget& target);

    private:

        sf::RectangleShape m_criss;

        sf::RectangleShape m_cross;

};