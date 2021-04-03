//
// Created by const on 4/2/2021.
//

#ifndef CLOCK_SFML_ANALOGUE_H
#define CLOCK_SFML_ANALOGUE_H

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <cstring>
#include <iostream>

#define PI 3.14159265

class sfml_analogue {

public:

    sfml_analogue();

    virtual ~sfml_analogue();

    void Run();

private:

    enum class LimbType{
        hour,
        minute,
        second
    };

    float calculate_angle(LimbType type);

private:

    sf::RenderWindow *window;

    sf::CircleShape center_circle;
    sf::CircleShape exterior_circle;

    sf::Vertex hour_limb[2];
    sf::Vertex minute_limb[2];
    sf::Vertex second_limb[2];

    int radius;
    sf::Vector2f center;

    sf::Text digital_text;
};


#endif //CLOCK_SFML_ANALOGUE_H
