#include "player/hitMarker.hpp"

HitMarker::HitMarker() {}

HitMarker::~HitMarker() {}

bool HitMarker::initialize() {

    m_criss = sf::RectangleShape(sf::Vector2f(25, 8));
    m_cross = sf::RectangleShape(sf::Vector2f(25, 8));

    m_criss.setOrigin(m_criss.getLocalBounds().width / 2.0f, m_criss.getLocalBounds().height / 2.0f);
    m_cross.setOrigin(m_cross.getLocalBounds().width / 2.0f, m_cross.getLocalBounds().height / 2.0f);

    m_criss.rotate(45);
    m_cross.rotate(-45);

    m_criss.setFillColor(sf::Color::Red);
    m_cross.setFillColor(sf::Color::Red);

    return true;
}

void HitMarker::setPosition(sf::Vector2f pos) {

    m_criss.setPosition(pos);
    m_cross.setPosition(pos);

}

void HitMarker::render(sf::RenderTarget& target) {
    target.draw(m_criss);
    target.draw(m_cross);
}
