#include <iostream>

#include "Crocodin.hpp"
#include "Screens.hpp"


Crocodin::Crocodin(sf::RenderWindow& window): window(window) {
    // load textures
    const char* textures[] = { "gfx/head.png", "gfx/nose.png", "gfx/body.png" };
    for (unsigned i = 0; i < sizeof(textures)/sizeof(const char*); i++) {
        std::shared_ptr<sf::Texture> texture;
        texture = resources.get<sf::Texture>(textures[i]);
        texture->setSmooth(true);
    }

    crocodile = new Crocodile(resources);
}

Crocodin::~Crocodin() {
    delete crocodile;
}

int Crocodin::run() {

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
                goto cleanup;
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
                else if (event.key.code == sf::Keyboard::Escape) {
                    return Screens::MENU;
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

cleanup:

    // exit application
    return -1;
}

void Crocodin::update(sf::Time elapsed, sf::Vector2f direction) {
    crocodile->move(direction, elapsed);
}

void Crocodin::draw() {
    crocodile->draw(window);
}
