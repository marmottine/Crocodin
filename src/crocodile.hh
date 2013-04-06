#ifndef CROCODILE_HH
#define CROCODILE_HH

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "resources.hh"

class Crocodile {

private:
    static const int initial_length = 4;

public:
    explicit Crocodile(Resources& resources);
    ~Crocodile();
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f direction, sf::Time elapsed_time);

private:
    std::vector<sf::Sprite> shapes;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    std::shared_ptr<sf::Texture> gfxNose;
    std::shared_ptr<sf::Texture> gfxHead;
    std::shared_ptr<sf::Texture> gfxBody;
};


#endif
