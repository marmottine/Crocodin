#ifndef CROCODILE_HPP
#define CROCODILE_HPP

#include <deque>
#include <vector>

#include "Engine.hpp"

class Crocodile: public Listener<UpdateEvent>, public Listener<RenderEvent> {

private:
    // at least 2 for the nose and the eyes.
    static const int initial_length = 7;

    static const float shape_size = 120.0;
    static const float dist_between_sprites = 60.0;
    static const float curve_radius = 100.0;

public:
    explicit Crocodile(Engine& engine);
    virtual ~Crocodile();
    virtual void update(sf::Time elapsed_time);
    virtual void render(sf::RenderWindow& window);

    // set by the level, so public for now, maybe move keypress to here?
    sf::Vector2f new_direction;

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
    std::deque<PathChunk> path;
};

#endif
