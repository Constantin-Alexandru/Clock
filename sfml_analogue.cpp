//
// Created by const on 4/2/2021.
//

#include "sfml_analogue.h"

/**
 * Constructor: sets the clock up
 */
sfml_analogue::sfml_analogue() {

	// Creates the context settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Creates a new window to display the clock on
    window = new sf::RenderWindow(sf::VideoMode(480, 480), "CLOCK", sf::Style::Default, settings);

    //Creates the center circle
    center_circle = sf::CircleShape(float(std::min(window->getSize().x, window->getSize().y) / 20));
    center_circle.setOrigin(-float(window->getSize().x)/2 + center_circle.getRadius(), -float(window->getSize().y)/2 + center_circle.getRadius());
    center_circle.setFillColor(sf::Color::White);

    //Creates the clock outline
    exterior_circle = sf::CircleShape(float(std::min(window->getSize().x, window->getSize().y) / 2) - 1.f);
    exterior_circle.setOutlineThickness(5.f);
    exterior_circle.setOutlineColor(sf::Color::White);
    exterior_circle.setFillColor(sf::Color::Black);

    //Stores the exterior circle's radius
    radius = float(std::min(window->getSize().x, window->getSize().y) / 2);

    //Stores the center of the clock as a 2D Vector
    center = sf::Vector2f(radius, radius);

    //Creates the vertex points that correspond to the hour limb
    hour_limb[0].position = center;
    hour_limb[1].position = sf::Vector2f(radius, 10);

    //Sets the colour of said vertex points
    hour_limb[0].color = sf::Color::Red;
    hour_limb[1].color = sf::Color::Red;

	//Creates the vertex points that correspond to the minute limb
    minute_limb[0].position = center;
    minute_limb[1].position = sf::Vector2f(radius, 5);

	//Sets the colour of said vertex points
    minute_limb[0].color = sf::Color::Green;
    minute_limb[1].color = sf::Color::Green;

	//Creates the vertex points that correspond to the second limb
    second_limb[0].position = center;
    second_limb[1].position = sf::Vector2f(radius, 0);

	//Sets the colour of said vertex points
    second_limb[0].color = sf::Color::Blue;
    second_limb[1].color = sf::Color::Blue;
}

/**
 * Destructor: destroys the window object
 */
sfml_analogue::~sfml_analogue() {
    delete window;
}

/**
 * Run: Takes care of the main logic
 */
void sfml_analogue::Run() {


	//Creates the font
    sf::Font font;

    //Loads the font
    if(!font.loadFromFile("DelaGothic.ttf"))
    {
        printf("Unable to load arial font");
    }

    //Generates the digital clock
    digital_text.setFont(font);
    digital_text.setCharacterSize(18);
    digital_text.setFillColor(sf::Color::White);
    digital_text.setPosition( radius - 145.5f, 2 * radius - 100 );
    digital_text.setString("Test");

    // Main loop
    while(window->isOpen())
    {
        sf::Event event = sf::Event();

        //Checks for events
        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        //Generates the limb's angles in radians
        float hour_angle = PI * -calculate_angle(LimbType::hour) / 180.f;
        float minute_angle = PI * -calculate_angle(LimbType::minute) / 180.f;
        float second_angle = PI * -calculate_angle(LimbType::second) / 180.f;

        //Creates the new second point of the vertex for each limb
        hour_limb[1].position = sf::Vector2f(std::cos(hour_angle) * radius + radius, std::sin(hour_angle) * radius + radius);
        minute_limb[1].position = sf::Vector2f(std::cos(minute_angle) * radius + radius, std::sin(minute_angle) * radius + radius);
        second_limb[1].position = sf::Vector2f(std::cos(second_angle) * radius + radius, std::sin(second_angle) * radius + radius);

        //Draws the screen
        window->clear();
        window->draw(exterior_circle);
        window->draw(digital_text);
        window->draw(hour_limb, 2, sf::Lines);
        window->draw(minute_limb, 2, sf::Lines);
        window->draw(second_limb, 2, sf::Lines);
        window->draw(center_circle);
        window->display();
    }

}

/**
 *
 * @param: type - hour/minute/second
 * @return: angle in degrees
 */
float sfml_analogue::calculate_angle(sfml_analogue::LimbType type) {

	//Gets the current system time
    time_t current_time = time(NULL);

    //Converts the time to a string
    char* time_str = ctime(&current_time);

    //Sets the text object to the current time
    digital_text.setString(time_str);

    //Stores the hour, minute and second as strings
    char hour_str[3];
    char minute_str[3];
    char second_str[3];

	//Stores the hour, minute and second as integers
    int hour = -1;
    int minute = -1;
    int second = -1;

	//Copies the hour, minute and string from the main time string
    strncpy(hour_str, time_str + 11, 2);
    strncpy(minute_str, time_str + 14, 2);
    strncpy(second_str, time_str + 17, 2);

    //Converts them to integers
    hour = atoi(hour_str);
    minute = atoi(minute_str);
    second = atoi(second_str);

    //Returns the current degree of the limb based on the type
    switch (type) {
        case LimbType::hour:
            return -(360.f * hour / 24) + 90;
        case LimbType::minute:
            return -(360.f * minute / 60) + 90;
        case LimbType::second:
            return -(360.f * second / 60) + 90;
    }

    return 0;

}
