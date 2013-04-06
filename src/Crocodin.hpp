#ifndef CROCODIN_HPP
#define CROCODIN_HPP

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Crocodile.hpp"
#include "Resources.hpp"

class Crocodin {
public:
    bool run();
    void update(sf::Time elapsed, sf::Vector2f direction);
    void draw();

private:
    sf::RenderWindow window;
    Crocodile* crocodile;
    Resources resources;
};

#endif
