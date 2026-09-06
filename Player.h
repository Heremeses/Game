#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
using namespace std;
using namespace sf;

class Player {
    Vector2<float> size{ 100, 400 };
    Vector2<float> position;
    float speed = 0;
    RectangleShape platform{ Vector2f{size.x, size.y} };

public:
    Player() {
        position = { 400, 200 };
    }

    void update(const Time& since_last_frame);

    void draw(RenderWindow& window) {
        platform.setPosition({ position.x, position.y });
        window.draw(platform);
    }

    Vector2<float> get_size() const{
        return { size.x, size.y };
    }

    Vector2<float> get_position() const{
        return { position.x, position.y };
    }

    float get_speed() const {
        return speed;
    }
};