#pragma once
#include <utility>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const float G = 9.8;

class Ball {
    Vector2<float> speed;
    Vector2<float> position;
    float radius = 20;
    int mass = 20;
public:

    Ball(float x, float y) : speed{ x, y } {}

    void update(float dt, sf::Vector3<float> bounce_vector);

    float get_radius() const{
        return { radius };
    }

    Vector2<float> get_position() const{
        return { position.x, position.y };
    }

    Vector2<float> get_speed() const{
        return { speed.x, speed.y };
    }
};