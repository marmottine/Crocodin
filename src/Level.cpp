#include "Level.hpp"
#include "Menu.hpp"

Level::Level(Engine& mengine) :
        Listener<KeypressEvent>(mengine.state.keypressListeners), engine(
                mengine) {
    // preload textures
    const char* textures[] = { "gfx/head.png", "gfx/nose.png", "gfx/body.png" };
    for (unsigned i = 0; i < sizeof(textures) / sizeof(const char*); i++) {
        std::shared_ptr<sf::Texture> texture;
        texture = engine.resources.get<sf::Texture>(textures[i]);
        texture->setSmooth(true);
    }

    crocodile = new Crocodile(engine);
}

void Level::keypress(sf::Event::KeyEvent& key) {
    if (key.code == sf::Keyboard::Left) {
        crocodile->new_direction = sf::Vector2f(-1, 0);
    } else if (key.code == sf::Keyboard::Right) {
        crocodile->new_direction = sf::Vector2f(1, 0);
    } else if (key.code == sf::Keyboard::Up) {
        crocodile->new_direction = sf::Vector2f(0, -1);
    } else if (key.code == sf::Keyboard::Down) {
        crocodile->new_direction = sf::Vector2f(0, 1);
    } else if (key.code == sf::Keyboard::Escape) {
        //State* state = new State();
        //std::swap(engine.state, *state);
        //Menu* menu = new Menu(engine, state);
    }
}

Level::~Level() {
    delete crocodile;
}
