#include <iostream>
#include "crocodin.hh"

bool Crocodin::run() {
    const sf::VideoMode& desktop = sf::VideoMode::getDesktopMode();
    unsigned depth = desktop.bitsPerPixel;
    unsigned stencil = 8;
    unsigned antialiasing = 4;
    unsigned width = 800;
    unsigned height = 600;
    unsigned left = (desktop.width - width) / 2;
    unsigned top = (desktop.height - height) / 2;
    bool vsync = true;
    unsigned framerate = 60;
    bool fullscreen = false;
    const std::string title("Super Crocro!");

    window.create(sf::VideoMode(width, height, depth),
            title,
            (fullscreen ? sf::Style::Fullscreen : sf::Style::Default),
            sf::ContextSettings(depth, stencil, antialiasing));
    window.setPosition(sf::Vector2i(left, top));
    window.setVerticalSyncEnabled(vsync);
    window.setFramerateLimit(framerate);

    sf::Clock clock;

    while (window.isOpen()) {

        sf::Time elapsed = clock.restart();

        sf::Event event;
        sf::Vector2f direction(0, 0);
        while (window.pollEvent(event)) {
            switch (event.type) {
            // user request to close the window
            case sf::Event::Closed:
                window.close();
                return true;
            case sf::Event::Resized:
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left) {
                    direction = sf::Vector2f(-1, 0);
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    direction = sf::Vector2f(1, 0);
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    direction = sf::Vector2f(0, -1);
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    direction = sf::Vector2f(0, 1);
                }
                break;
            default:
                break;
            }
        }

        update(elapsed, direction);

        window.clear();
        draw();
        window.display();
    }

    return true;
}

void Crocodin::update(sf::Time elapsed, sf::Vector2f direction) {
    crocodile.move(direction, elapsed);
}

void Crocodin::draw() {
    crocodile.draw(window);
}