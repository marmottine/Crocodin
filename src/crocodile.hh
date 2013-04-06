#ifndef CROCODILE_HH
#define CROCODILE_HH

#include <list>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "resources.hh"

class Crocodile {

private:
    static const int initial_length = 4;
    static const float shape_size = 120.0;
    static const float dist_between_shapes = 60.0;

public:
    explicit Crocodile(Resources& resources);
    ~Crocodile();
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f direction, sf::Time elapsed_time);

private:
    std::vector<sf::Sprite> shapes;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    std::shared_ptr<sf::Texture> gfxNose;
    std::shared_ptr<sf::Texture> gfxHead;
    std::shared_ptr<sf::Texture> gfxBody;

    // points where the crocodile made a turn.
    // points are removed when the body is no longer at these points.
    std::list<sf::Vector2f> path;
    sf::Vector2f get_new_position(unsigned dist_to_head);
};


#endif
