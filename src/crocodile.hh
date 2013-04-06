#ifndef CROCODILE_HH
#define CROCODILE_HH

#include <list>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Crocodile {

private:
    static const int initial_length = 4;
    static const float shape_size = 60.0;
    static const float dist_between_shapes = 30.0;

public:
    Crocodile();
    ~Crocodile();
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f direction, sf::Time elapsed_time);

private:
    std::vector<sf::Shape*> shapes;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    // points where the crocodile made a turn.
    // points are removed when the body is no longer at these points.
    std::list<sf::Vector2f> path;
    sf::Vector2f get_new_position(unsigned dist_to_head);
};


#endif
