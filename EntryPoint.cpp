#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <iostream>

#include "Ball.h"
#include "Player.h"

using namespace sf;
using namespace std;

const int FIELD_WIDTH = 900, FIELD_HEIGHT = 600;

Vector3<float> calculate_collision(const Ball& ball, const Player& player, float dt) {
    Vector2<float> ball_speed = ball.get_speed();
    Vector2<float> ball_position = ball.get_position();
    float ball_radius = ball.get_radius();

    //set origin to the center to make x axis collision detection easier
    ball_position.x = ball_position.x + ball_radius;
    ball_position.y = ball_position.y + ball_radius;
    Vector2<float> ball_next_position = { ball_position.x + ball_speed.x * dt, ball_position.y + ball_speed.y * dt };

    float player_speed = player.get_speed();
    Vector2<float> player_position = player.get_position();
    Vector2<float> player_size = player.get_size();

    player_position.x = player_position.x + player_size.x / 2;
    player_position.y = player_position.y + player_size.y / 2;
    Vector2<float> player_next_position = { player_position.x + player_speed * dt, player_position.y };

    if (abs(ball_next_position.x - player_next_position.x) <= player_size.x / 2 + ball_radius and abs(ball_next_position.y - player_next_position.y) <= player_size.y / 2 + ball_radius) {
        if (abs(ball_next_position.x - player_next_position.x) <= player_size.x / 2) {
            //cout << "top";
            float false_timing_of_motion = (ball_next_position.y + ball_radius - FIELD_HEIGHT + player_size.y) / (ball_next_position.y - ball_position.y);
            //return { 1.0, -0.6, false_timing_of_motion };

            Vector2<float> normal = {0, -1};
            cout << "normal.x: " << normal.x << " normal.y: " << normal.y << '\n';
            cout << "normal.length(): " << normal.length() << '\n';
            if (normal.length() <= ball_radius + 2) {
                normal = normal.normalized();
                Vector2<float> ball_speed_normalized = ball_speed.normalized();
                Vector2<float> result = -2 * (normal.dot(ball_speed_normalized)) * normal + ball_speed_normalized;

                cout << "ball_speed_normalized.x: " << ball_speed_normalized.x << " ball_speed_normalized.y: " << ball_speed_normalized.y << '\n';
                cout << "result: " << result.x << ' ' << result.y << "\n\n";

                return { result.x, result.y, false_timing_of_motion };
            }
            else {
                return { 0, 0, 0 };
            }
        }
        else if (abs(ball_next_position.y - player_next_position.y) <= player_size.y / 2) {
            //cout << "side ";
            //if (player_speed == 0) {
            //    float false_part_of_motion = player_size.x / 2 - abs(player_next_position.x - ball_next_position.x) + ball_radius;
            //    return { -0.6f, 0.7, false_part_of_motion / (ball_next_position.x - ball_position.x) };
            //}
            float false_part_of_motion = player_size.x / 2 - abs(player_next_position.x - ball_next_position.x) + ball_radius;
            float false_part_of_ball_motion = false_part_of_motion * ball_speed.x / player_speed;
            //cout << "false_part_of_ball_motion:" << false_part_of_ball_motion << " false_part_of_motion:" << false_part_of_motion;
            float false_timing_of_motion = false_part_of_ball_motion / false_part_of_motion;

            Vector2<float> normal = { 1, 0 };
            if (ball_position.x < player_position.x) {
                normal.x = -1;
            }
            cout << "normal.x: " << normal.x << " normal.y: " << normal.y << '\n';
            cout << "normal.length(): " << normal.length() << '\n';
            if (normal.length() <= ball_radius + 2) {
                normal = normal.normalized();
                Vector2<float> ball_speed_normalized = ball_speed.normalized();
                Vector2<float> result = -2 * (normal.dot(ball_speed_normalized)) * normal + ball_speed_normalized;

                cout << "ball_speed_normalized.x: " << ball_speed_normalized.x << " ball_speed_normalized.y: " << ball_speed_normalized.y << '\n';
                cout << "result: " << result.x << ' ' << result.y << "\n\n";

                if (player_speed * ball_speed.x > 0) {
                    cout << " same direction\n";
                    result.x *= 2;
                }
                else if (player_speed == 0) {
                    float false_part_of_motion = player_size.x / 2 - abs(player_next_position.x - ball_next_position.x) + ball_radius;
                    return { result.x, result.y, false_part_of_motion / (ball_next_position.x - ball_position.x) };
                }
                else { 
                    cout << " diff direction\n";
                }

                return { result.x, result.y, false_timing_of_motion };
            }
            else {
                return { 0, 0, 0 };
            }
        }
        else {
            Vector2<float> angleCoords;
            if (ball_position.x < player_position.x) {
                angleCoords = { player_next_position.x - player_size.x / 2, player_next_position.y - player_size.y / 2 };
            }
            else {
                angleCoords = { player_next_position.x + player_size.x / 2, player_next_position.y - player_size.y / 2 };
            }
            Vector2<float> normal = { ball_next_position.x - angleCoords.x, ball_next_position.y - angleCoords.y };
            cout << "normal.x: " << normal.x << " normal.y: " << normal.y << '\n';
            cout << "normal.length(): " << normal.length() << '\n';
            if (normal.length() <= ball_radius + 2) {
                normal = normal.normalized();
                Vector2<float> ball_speed_normalized = ball_speed.normalized();
                Vector2<float> result = -2 * (normal.dot(ball_speed_normalized)) * normal + ball_speed_normalized;

                cout << "ball_speed_normalized.x: " << ball_speed_normalized.x << " ball_speed_normalized.y: " << ball_speed_normalized.y << '\n';
                cout << "result: " << result.x << ' ' << result.y << "\n\n";

                return { result.x, result.y, 0.5 };
            }
            else {
                return { 0, 0, 0 };
            }
        }
    }
    else { 
        return {0, 0, 0}; 
    }
}

class BallManager {
public:
    BallManager() {};
    vector<pair<Ball, CircleShape>> balls{ {Ball{300.0f, 0.0f} , CircleShape{20.0f}} };

    void update(const Time& since_last_frame, const Player& player) {
        for (auto& ball : balls) {
            ball.first.update(since_last_frame.asSeconds(), calculate_collision(ball.first, player, since_last_frame.asSeconds()));
        }
    }

    void draw(RenderWindow& window) {
        for (auto& ball : balls) {
            ball.second.setPosition({ ball.first.get_position().x, ball.first.get_position().y } );
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
    RenderWindow window(VideoMode({ FIELD_WIDTH, FIELD_HEIGHT }), L"Эволв", Style::Default);
    Clock clock;
    GameManager gm;

    window.setVerticalSyncEnabled(true);

    clock.getElapsedTime();

    while (window.isOpen())
    {   
        Time since_last_frame = clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
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
