#include "Player.h"

void Player::update(const Time& since_last_frame) {
    if (Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        position.first += -50.f * since_last_frame.asSeconds();
    }
    else if (Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        position.first += 50.f * since_last_frame.asSeconds();
    }
}