#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.h"

using namespace std;

void Ball::update(float dt, sf::Vector3<float> bounce_vector) {
    float false_timing_of_motion = bounce_vector.z;
     
    if (false_timing_of_motion == 0.0) {
        position.x += speed.x * dt; position.y += speed.y * dt;
    }
    else {
        float length = speed.length();
        speed.x = bounce_vector.x * length;
        speed.y = bounce_vector.y * length;
        position = { position.x + speed.x * dt + 2 * false_timing_of_motion * speed.x * dt, position.y + speed.y * dt + 2 * false_timing_of_motion * speed.y * dt };
    } 

    speed.x -= speed.x * 0.4 * dt;
    speed.y += G * dt;

}