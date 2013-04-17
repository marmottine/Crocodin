#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>

#include "Crocodile.hpp"

Crocodile::Crocodile(Resources& resources):
        position(60, 100), direction(1,0), speed(0.0001),
        gfxNose(resources.get<sf::Texture>("gfx/nose.png")),
        gfxHead(resources.get<sf::Texture>("gfx/head.png")),
        gfxBody(resources.get<sf::Texture>("gfx/body.png"))
{
    shapes.resize(initial_length);

    // create the nose
    sf::Sprite& nose = shapes[0];
    nose.setOrigin(60, 60);
    nose.setTexture(*gfxNose);
    nose.setPosition(sf::Vector2f(60.0, 60.0));

    // create the head
    sf::Sprite& head = shapes[1];
    head.setOrigin(60, 60);
    head.setTexture(*gfxHead);
    head.setPosition(sf::Vector2f(80.0, 60.0));

    // create the body
    // start at 2 to compensate for the nose and head
    for (int i = 2; i < initial_length; ++i) {
        sf::Sprite& body = shapes[i];
        body.setOrigin(60, 60);
        body.setTexture(*gfxBody);
        body.setPosition(sf::Vector2f(60 + 60*i, 0));
    }

    // record first position
    path.push_front(position - sf::Vector2f(dist_between_shapes * initial_length, 0.0));
    path.push_front(position);
}

Crocodile::~Crocodile() {
}

void Crocodile::draw(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator shape_it;
    for (shape_it = shapes.begin(); shape_it != shapes.end(); ++shape_it) {
       window.draw(*shape_it);
    }
}

sf::Vector2f Crocodile::get_new_position(unsigned dist_to_head) {
    float accumulated_dist = 0;

    sf::Vector2f previous_point = position;
    std::list<sf::Vector2f>::iterator point_it;
    for (point_it = path.begin(); point_it != path.end(); ++point_it) {
        sf::Vector2f point = *point_it;
        sf::Vector2f point_difference = previous_point - point;
        float dist = abs(point_difference.x) + abs(point_difference.y);

        accumulated_dist += dist;

        if (accumulated_dist >= dist_to_head) {
            // new_pos is somewhere between previous_point and point.
            float ratio = (accumulated_dist - dist_to_head) / dist;
            sf::Vector2f new_pos = point + point_difference * ratio;
            return new_pos;
        }
        previous_point = point;
    }
    // should not reach this point, return a default to be safe
    return sf::Vector2f(0.0, 0.0);
}

void Crocodile::move(sf::Vector2f new_direction, sf::Time elapsed_time) {

    sf::Int64 elapsed_ms = elapsed_time.asMicroseconds();

    sf::Vector2f previous_direction = direction;
    if (new_direction != sf::Vector2f(0, 0)) {
        direction = new_direction;
    }

    sf::Vector2f shifting = direction * (elapsed_ms * speed);
    position += shifting;

    if (direction == previous_direction) {
        path.front() = position;
    }
    else {
        path.push_front(position);
    }

    sf::Sprite& head = shapes.front();
    head.setPosition(position);
    head.setRotation(atan2(-shifting.y, -shifting.x) * 180 / M_PI);

    // skip head
    std::vector<sf::Sprite>::iterator cur_shape = shapes.begin();
    std::vector<sf::Sprite>::iterator prev_shape = cur_shape++;
    unsigned dist_to_head = 0;
    for (; cur_shape != shapes.end(); prev_shape = cur_shape++) {
        dist_to_head += dist_between_shapes;
        sf::Vector2f new_pos = get_new_position(dist_to_head);
        cur_shape->setPosition(new_pos);
        const sf::Vector2f& prev_pos = prev_shape->getPosition();
        cur_shape->setRotation(atan2(new_pos.y - prev_pos.y,
                new_pos.x - prev_pos.x) * 180 / M_PI);
    }
}
