#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
using namespace std;
using namespace sf;

class Player {
    pair<float, float> size{ 100, 20 };
    pair<float, float> position;
    RectangleShape platform{ Vector2f{size.first, size.second} };

public:
    Player() {
        position = { 0, 580 };
    }

    void update(const Time& since_last_frame);

    void draw(RenderWindow& window) {
        platform.setPosition(position.first, position.second);
        window.draw(platform);
    }

    pair<float, float> get_size() const{
        return { size.first, size.second };
    }

    pair<float, float> get_position() const{
        return { position.first, position.second };
    }
};