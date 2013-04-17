#include<vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Screen.hpp"

class Menu: public Screen {
public:
    Menu(sf::RenderWindow &window);
    virtual int run();

private:
    sf::RenderWindow& window;
    std::vector<sf::Text> entries;
    sf::Font font;
    unsigned int selected_entry;

    void draw();
};
