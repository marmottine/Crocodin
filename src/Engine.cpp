#include <iostream>

#include "Engine.hpp"

bool Engine::run() {
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
        while (window.pollEvent(event)) {
            switch (event.type) {
                // user request to close the window
                case sf::Event::Closed:
                    window.close();
                    return true;
                case sf::Event::Resized:
                    break;
                case sf::Event::KeyPressed:
                    keypress(event.key);
                    break;
                default:
                    break;
            }
        }

        update(elapsed);

        window.clear();
        render(window);
        window.display();
    }
    return false;
}

void Engine::update(sf::Time elapsed) {
    for (ListenerList<UpdateEvent>::iterator it = state.updateListeners.begin();
            it != state.updateListeners.end(); ++it) {
        it->update(elapsed);
    }
}

void Engine::render(sf::RenderWindow& window) {
    for (ListenerList<RenderEvent>::iterator it = state.renderListeners.begin();
            it != state.renderListeners.end(); ++it) {
        it->render(window);
    }
}

void Engine::keypress(sf::Event::KeyEvent& key) {
    ListenerList<KeypressEvent>::iterator it;
    for (it = state.keypressListeners.begin();
            it != state.keypressListeners.end(); ++it) {
        it->keypress(key);
    }
}
