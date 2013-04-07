#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Engine.hpp"
#include "Crocodile.hpp"

class Level: public Listener<KeypressEvent> {
public:
    Level(Engine& mengine);
    virtual ~Level();
    virtual void keypress(sf::Event::KeyEvent& key);

private:
    Crocodile* crocodile;
    Engine& engine;
};

#endif
