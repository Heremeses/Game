#include "Player.h"

void Player::update(const Time& since_last_frame) {
    position.x += speed * since_last_frame.asSeconds();
    speed = 0;

    if (Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {   
        speed = -200.f;
    }
    else if (Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {   
        speed = 200.f;
    }

}