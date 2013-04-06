#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "crocodile.hh"

Crocodile::Crocodile(): position(60, 100), direction(1,0), speed(0.0001) {

    // create the head
    sf::Vector2f dim(shape_size, shape_size);
    sf::RectangleShape* head = new sf::RectangleShape(dim);
    head->setFillColor(sf::Color::Blue);
    head->setPosition(position);
    shapes.push_back(head);

    // create the body
    // start at 1 to compensate for the head
    for (int i = 1; i < initial_length; ++i) {
        float radius = shape_size / 2;
        sf::CircleShape* body_part = new sf::CircleShape(radius);
        body_part->setFillColor(sf::Color::Green);
        body_part->setPosition(position
                - sf::Vector2f(dist_between_shapes * i, 0.0));
        shapes.push_back(body_part);
    }

    // record first position
    path.push_front(position - sf::Vector2f(dist_between_shapes * initial_length, 0.0));
    path.push_front(position);
}

Crocodile::~Crocodile() {
    std::vector<sf::Shape*>::iterator shape_it;
    for (shape_it = shapes.begin(); shape_it != shapes.end(); ++shape_it) {
        delete *shape_it;
    }
}

void Crocodile::draw(sf::RenderWindow& window) {
    std::vector<sf::Shape*>::iterator shape_it;
    for (shape_it = shapes.begin(); shape_it != shapes.end(); ++shape_it) {
        window.draw(**shape_it);
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
            std::cout << "shape_it is somewhere between " << point.x << " "
                    << point.y << " and " << previous_point.x << " "
                    << previous_point.y << "\n";
            // shape_it is somewhere between previous_point and point.
            sf::Vector2f new_pos = point
                    + point_difference
                            * ((accumulated_dist - dist_to_head) / dist);
            return new_pos;
        }
        previous_point = point;
    }
    assert(false);
}

void Crocodile::move(sf::Vector2f new_direction, sf::Time elapsed_time) {

    std::cout << "path before move: ";
    std::list<sf::Vector2f>::iterator point_it;
    for (point_it = path.begin(); point_it != path.end(); ++point_it) {
        std::cout << "(" << point_it->x << "," << point_it->y << ") ";
    }
    std::cout << "\n";

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
    if (direction != previous_direction) {
        path.push_front(position);
    }

    std::cout << "path after move: ";
    for (point_it = path.begin(); point_it != path.end(); ++point_it) {
        std::cout << "(" << point_it->x << "," << point_it->y << ") ";
    }
    std::cout << "\n";



    sf::Shape& head = *(*(shapes.begin()));
    head.setPosition(position);

    std::vector<sf::Shape*>::iterator shape_it;
    unsigned dist_to_head = 0;
    for (shape_it = shapes.begin(); shape_it != shapes.end(); ++shape_it) {
        if (shape_it == shapes.begin()) {
            continue;
        }

        std::cout << "old pos " << (*shape_it)->getPosition().x << " " << (*shape_it)->getPosition().y << "\n";

        dist_to_head += dist_between_shapes;
        sf::Vector2f new_pos = get_new_position(dist_to_head);
        (*shape_it)->setPosition(new_pos);

        std::cout << "new pos " << (*shape_it)->getPosition().x << " " << (*shape_it)->getPosition().y << "\n";
    }


}
