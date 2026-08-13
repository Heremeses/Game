#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.h"

using namespace std;

void Ball::update(float dt, sf::Vector3<float> bounce_vector) {
    float false_timing_of_motion = bounce_vector.z;
    if (false_timing_of_motion == 0.0) {
        position.first += speed.first * dt; position.second += speed.second * dt;
    }
    else {
        speed.second = bounce_vector.y * speed.second;
        position = { position.first + speed.first * dt, position.second + speed.second * dt - 2 * false_timing_of_motion * speed.second * dt };
        cout << position.second << ' ' << false_timing_of_motion << '\n';
    }

    speed.first -= speed.first * 0.5 * dt;
    speed.second += G * dt;

}