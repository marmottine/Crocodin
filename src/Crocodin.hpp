#ifndef CROCODIN_HPP
#define CROCODIN_HPP

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Crocodile.hpp"
#include "Resources.hpp"
#include "Screen.hpp"

class Crocodin: public Screen {
public:
    Crocodin(sf::RenderWindow& window);
    ~Crocodin();
    int run();
    void update(sf::Time elapsed, sf::Vector2f direction);
    void draw();

private:
    sf::RenderWindow& window;
    Crocodile* crocodile;
    Resources resources;
};

#endif
