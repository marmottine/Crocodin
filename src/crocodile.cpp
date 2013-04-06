#include <iostream>
#include <math.h>

#include "crocodile.hh"

Crocodile::Crocodile(): position(10, 20), direction(1,0), speed(0.0001) {

    // create the head
    sf::Vector2f size(60.0, 60.0);
    sf::RectangleShape* head = new sf::RectangleShape(size);
    head->setFillColor(sf::Color::Green);
    head->setPosition(position);
    shapes.push_back(head);

    // create the body
    // start at 1 to compensate for the head
    for (int i = 1; i < initial_length; ++i) {
        float radius = 60.0 / 2;
        sf::CircleShape* body_part = new sf::CircleShape(radius);
        body_part->setFillColor(sf::Color::Green);
        body_part->setPosition(position + sf::Vector2f(60.0 * i, 0.0));
        shapes.push_back(body_part);
    }
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

void Crocodile::move(sf::Vector2f new_direction, sf::Time elapsed_time) {
    sf::Int64 elapsed_ms = elapsed_time.asMicroseconds();

    // current shape is the shape we want to update
    std::vector<sf::Shape*>::reverse_iterator current_shape_it = shapes.rbegin();

    std::vector<sf::Shape*>::reverse_iterator next_shape_it;
    for (next_shape_it = current_shape_it + 1;
            next_shape_it != shapes.rend();
            ++next_shape_it) {

        // get shifting direction for the current shape by interpolation
        sf::Vector2f dir = (*next_shape_it)->getPosition()
                - (*current_shape_it)->getPosition();
        // normalise the direction vector
        float length = sqrt(dir.x * dir.x + dir.y * dir.y);
        dir /= length;

        std::cout << dir.x << " " << dir.y << "\n";

        sf::Vector2f shifting = dir * (elapsed_ms * speed);

        sf::Vector2f new_pos = (*current_shape_it)->getPosition() + shifting;
        (*current_shape_it)->setPosition(new_pos);

        current_shape_it = next_shape_it;
    }

    sf::Shape& head = *(*(shapes.begin()));

    if (new_direction != sf::Vector2f(0, 0)) {
        direction = new_direction;
    }

    sf::Vector2f shifting = direction * (elapsed_ms * speed);
    position += shifting;

    head.setPosition(position);

}
