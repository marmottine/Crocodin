#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Crocodin.hpp"
#include "Menu.hpp"
#include "Screens.hpp"

int main(int argc, char* argv[])  {

    // create window
    sf::RenderWindow window;
    const sf::VideoMode& desktop = sf::VideoMode::getDesktopMode();
    unsigned depth = desktop.bitsPerPixel;
    unsigned stencil = 8;
    unsigned antialiasing = 4;
    unsigned width = 1024;
    unsigned height = 768;
    unsigned left = (desktop.width - width) / 2;
    unsigned top = (desktop.height - height) / 2;
    bool vsync = true;
    unsigned framerate = 60;
    bool fullscreen = false;
    const std::string title("Crocodin!");

    window.create(sf::VideoMode(width, height, depth),
            title,
            (fullscreen ? sf::Style::Fullscreen : sf::Style::Default),
            sf::ContextSettings(depth, stencil, antialiasing));
    window.setPosition(sf::Vector2i(left, top));
    window.setVerticalSyncEnabled(vsync);
    window.setFramerateLimit(framerate);

    std::vector<Screen*> screens;
    Menu menu(window);
    screens.push_back(&menu);
    Crocodin crocodin(window);
    screens.push_back(&crocodin);

    int screen = Screens::GAME;
    while (screen >= 0)
    {
        screen = screens[screen]->run();
    }

    return EXIT_SUCCESS;

}
