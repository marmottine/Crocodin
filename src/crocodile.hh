#ifndef CROCODILE_HH
#define CROCODILE_HH

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Crocodile {

private:
    static const int initial_length = 3;

public:
    Crocodile();
    ~Crocodile();
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f direction, sf::Time elapsed_time);

private:
    std::vector<sf::Shape*> shapes;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
};


#endif
