#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>

#include "Crocodile.hpp"

Crocodile::Crocodile(Engine& engine):
Listener<UpdateEvent>(engine.state.updateListeners),
Listener<RenderEvent>(engine.state.renderListeners),
        direction(1,0),
        speed(0.0001),
        gfxNose(engine.resources.get<sf::Texture>("gfx/nose.png")),
        gfxHead(engine.resources.get<sf::Texture>("gfx/head.png")),
        gfxBody(engine.resources.get<sf::Texture>("gfx/body.png"))
{
    sprites.resize(initial_length);

    // create the nose
    sf::Sprite& nose = sprites[0];
    nose.setOrigin(60, 60);
    nose.setTexture(*gfxNose);
    nose.setPosition(sf::Vector2f(60.0, 60.0));

    // create the head
    sf::Sprite& head = sprites[1];
    head.setOrigin(60, 60);
    head.setTexture(*gfxHead);
    head.setPosition(sf::Vector2f(80.0, 60.0));

    // create the body
    // start at 2 to compensate for the nose and head
    for (int i = 2; i < initial_length; ++i) {
        sf::Sprite& body = sprites[i];
        body.setOrigin(60, 60);
        body.setTexture(*gfxBody);
        body.setPosition(sf::Vector2f(60 + 60*i, 0));
    }

    // record first path chunk
    sf::Vector2f head_position(200.0, 200.0);
    float snake_length = dist_between_sprites * initial_length;
    sf::Vector2f tail_position = head_position - (direction * snake_length);

    PathChunk straight_line;
    straight_line.from = direction;
    straight_line.to = direction;
    straight_line.length = snake_length;
    straight_line.position = tail_position;
    path.push_front(straight_line);
}

Crocodile::~Crocodile() {
}

void Crocodile::render(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator shape_it;
    for (shape_it = sprites.begin(); shape_it != sprites.end(); ++shape_it) {
        window.draw(*shape_it);
    }
}

void Crocodile::update(sf::Time elapsed_time) {
    sf::Vector2f previous_direction = direction;
    if (new_direction != sf::Vector2f(0, 0)) {
        direction = new_direction;
    }

    // If the direction has changed, add 2 new path chunks:
    // one for the curve (smooth turn) and one for the straight
    // line that follows.
    if (direction != previous_direction) {
        sf::Vector2f current_head_position = sprites.front().getPosition();

        PathChunk curve;
        curve.from = previous_direction;
        curve.to = direction;
        curve.length = M_PI * curve_radius / 2.0;
        curve.position = current_head_position;
        path.push_front(curve);

        PathChunk straight_line;
        straight_line.from = direction;
        straight_line.to = direction;
        straight_line.length = - curve.length;
        straight_line.position = current_head_position
                + direction*curve_radius
                + previous_direction*curve_radius;
        path.push_front(straight_line);
    }

    // update the distance-to-head of the first path chunk
    sf::Int64 elapsed_ms = elapsed_time.asMicroseconds();
    float velocity = elapsed_ms * speed;
    path.front().length += velocity;

    // update position of all sprites
    std::vector<sf::Sprite>::iterator sprite = sprites.begin();
    std::deque<PathChunk>::iterator chunk = path.begin();
    float chunk_dist_to_head = chunk->length;
    float sprite_dist_to_head = 0.0;

    while (true) {

        if (chunk_dist_to_head >= sprite_dist_to_head) {

            sf::Vector2f prev_pos = sprite->getPosition();

            // Compute new position depending on the type of the path chunk
            sf::Vector2f new_pos;
            // offset is the distance ran on the current path chunk
            float offset = chunk_dist_to_head - sprite_dist_to_head;
            if (chunk->from == chunk->to) { // straight line
                sf::Vector2f shifting = chunk->to * offset;
                new_pos = chunk->position + shifting;
            } else { // curve
                // See http://en.wikipedia.org/wiki/Bezier_curve
                float t = offset / (M_PI * curve_radius / 2.0f);
                sf::Vector2f P0 = chunk->position;
                sf::Vector2f P1 = P0 + chunk->from * curve_radius;
                sf::Vector2f P2 = P1 + chunk->to * curve_radius;
                new_pos = (P0 * ((1.0f - t) * (1.0f - t))) + (P1 * (2.0f * (1.0f - t) * t)) + (P2 * (t * t));
            }

            sprite->setPosition(new_pos);

            sprite->setRotation(atan2(-new_pos.y + prev_pos.y,
                    -new_pos.x + prev_pos.x) * 180 / M_PI);

            sprite++;

            // Once all the sprites are updated,
            // delete useless path chunks and break
            if (sprite == sprites.end()) {
                chunk++;
                path.erase(chunk, path.end());
                break;
            }
            sprite_dist_to_head += dist_between_sprites;

        }
        else {
            chunk++;

            if (chunk == path.end()) {
                std::cout << "oops" << std::endl;
                exit(1);
            }

            chunk_dist_to_head += chunk->length;

        }
    }
}
