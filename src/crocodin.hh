#ifndef CROCODIN_HH
#define CROCODIN_HH

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "crocodile.hh"
#include "resources.hh"

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
