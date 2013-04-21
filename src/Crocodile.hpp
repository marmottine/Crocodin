#ifndef CROCODILE_HPP
#define CROCODILE_HPP

#include <deque>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Resources.hpp"

class Crocodile {

private:
    static const int initial_length = 7;
    static const float shape_size = 120.0;
    static const float dist_between_sprites = 60.0;
    static const float curve_radius = 200.0;

public:
    explicit Crocodile(Resources& resources);
    ~Crocodile();
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f direction, sf::Time elapsed_time);

private:
    std::vector<sf::Sprite> sprites;
    sf::Vector2f direction;
    float speed;
    std::shared_ptr<sf::Texture> gfxNose;
    std::shared_ptr<sf::Texture> gfxHead;
    std::shared_ptr<sf::Texture> gfxBody;

    struct PathChunk {
        sf::Vector2f position;
        sf::Vector2f from;
        sf::Vector2f to;
        float length;
    };

    // points where the crocodile changed direction.
    // TODO: remove points when the body is no longer at these points.
    std::deque<PathChunk> path;
};


#endif
