#include <iostream>
#include <math.h>

#include "crocodile.hh"

sf::Texture gfxHead;
sf::Texture gfxNose;
sf::Texture gfxBody;

Crocodile::Crocodile(): position(10, 20), direction(1,0), speed(0.0001) {

    if (!gfxHead.loadFromFile("gfx/head.png")) {
        std::cout << "fail to load gfx/head.png\n";
        abort();
    }

    if (!gfxNose.loadFromFile("gfx/nose.png")) {
        std::cout << "fail to load gfx/nose.png\n";
        abort();
    }

    if (!gfxBody.loadFromFile("gfx/body.png")) {
        std::cout << "fail to load gfx/body.png\n";
        abort();
    }

    shapes.resize(initial_length);

    // create the nose
    sf::Sprite& nose = shapes[0];
    nose.setTexture(gfxNose);
    nose.setPosition(sf::Vector2f(60.0, 60.0));

    // create the head
    sf::Sprite& head = shapes[1];
    head.setTexture(gfxHead);
    head.setPosition(sf::Vector2f(80.0, 60.0));

    // create the body
    // start at 2 to compensate for the nose and head
    for (int i = 2; i < initial_length; ++i) {
        sf::Sprite& body = shapes[i];
        body.setTexture(gfxBody);
        body.setPosition(sf::Vector2f(60 + 60*i, 0));
    }
}

Crocodile::~Crocodile() {
}

void Crocodile::draw(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator shape_it;
    for (shape_it = shapes.begin(); shape_it != shapes.end(); ++shape_it) {
       window.draw(*shape_it);
    }
}

void Crocodile::move(sf::Vector2f new_direction, sf::Time elapsed_time) {
    sf::Int64 elapsed_ms = elapsed_time.asMicroseconds();

    // current shape is the shape we want to update
    std::vector<sf::Sprite>::reverse_iterator current_shape_it = shapes.rbegin();

    std::vector<sf::Sprite>::reverse_iterator next_shape_it;
    for (next_shape_it = current_shape_it+ 1;
            next_shape_it != shapes.rend();
            ++next_shape_it) {

        // get shifting direction for the current shape by interpolation
        sf::Vector2f dir = (*next_shape_it).getPosition()
                - (*current_shape_it).getPosition();
        // normalise the direction vector
        float length = sqrt(dir.x * dir.x + dir.y * dir.y*4)*4;
        dir /= length;

        //std::cout << dir.x << " " << dir.y << "\n";

        sf::Vector2f shifting = dir * (elapsed_ms * speed);

        sf::Vector2f new_pos = (*current_shape_it).getPosition() + shifting;
        (*current_shape_it).setPosition(new_pos);

        current_shape_it = next_shape_it;
    }

    sf::Sprite& head = shapes.front();

    if (new_direction != sf::Vector2f(0, 0)) {
        direction = new_direction;
    }

    sf::Vector2f shifting = direction * (elapsed_ms * speed);
    position += shifting;

    head.setPosition(position);

}
