#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
using namespace std;

const float G = 9.8;

class Ball {
    pair<float, float> speed;
    pair<float, float> position;
    float radius = 20;
    int mass = 20;
public:

    Ball(float x, float y) : speed{ x, y } {}

    void update(float dt, sf::Vector3<float> bounce_vector);

    float get_radius() const{
        return { radius };
    }

    pair<float, float> get_position() const{
        return { position.first, position.second };
    }

    pair<float, float> get_speed() const{
        return { speed.first, speed.second };
    }
};