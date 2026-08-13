#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#include "Ball.h"
#include "Player.h"

using namespace sf;
using namespace std;

const int FIELD_WIDTH = 900, FIELD_HEIGHT = 600;

Vector3<float> calculate_collision(const Ball& ball, const Player& player, float dt) {
    pair<float, float> ball_speed = ball.get_speed();
    pair<float, float> ball_position = ball.get_position();
    float ball_radius = ball.get_radius();
    pair<float, float> player_position = player.get_position();
    pair<float, float> player_size = player.get_size();

    float next_frame_position_x = ball_position.first + ball_speed.first * dt, next_frame_position_y = ball_position.second + ball_speed.second * dt;
    if (next_frame_position_y + 2 * ball_radius >= FIELD_HEIGHT - player_size.second) {
        if (((ball_position.first < player_position.first) and (player_position.first - ball_position.first <= ball_radius)) or ((ball_position.first > player_position.first) and (ball_position.first - player_position.first <= player_size.first - ball_radius))) {
            cout << "intersection ";
            float false_timing_of_motion = (next_frame_position_y + 2 * ball_radius - 580) / (next_frame_position_y - ball_position.second);
            return { 0, -0.6, false_timing_of_motion };
        }
        if () {
            return {}
        }

    }
    else { return {0, 0, 0}; }
}

class BallManager {
public:
    BallManager() {};
    vector<pair<Ball, CircleShape>> balls{ {Ball{100.0f, 0.0f} , CircleShape{20.0f}} };

    void update(const Time& since_last_frame, const Player& player) {
        for (auto& ball : balls) {
            ball.first.update(since_last_frame.asSeconds(), calculate_collision(ball.first, player, since_last_frame.asSeconds()));
        }
    }

    void draw(RenderWindow& window) {
        for (auto& ball : balls) {
            ball.second.setPosition(ball.first.get_position().first, ball.first.get_position().second);
            window.draw(ball.second);
        }
    }
};

class GameManager {
    Player player;
    BallManager blmg;

public:
    void update(const Time& since_last_frame, RenderWindow& window) {
        blmg.update(since_last_frame, player);
        player.update(since_last_frame);
    }

    void draw(RenderWindow& window) {
        blmg.draw(window);
        player.draw(window);
    }
};

int main()
{
    RenderWindow window(VideoMode(FIELD_WIDTH, FIELD_HEIGHT), L"Эволв", Style::Default);
    Clock clock;
    GameManager gm;

    window.setVerticalSyncEnabled(true);

    clock.getElapsedTime();

    while (window.isOpen())
    {   
        Time since_last_frame = clock.restart();
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        gm.update(since_last_frame, window);
        gm.draw(window);

        window.display();
        window.clear(Color::Black);
        clock.getElapsedTime();
    }
    return 0;
}
