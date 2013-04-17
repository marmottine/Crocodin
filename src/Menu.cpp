#include <iostream>

#include "Menu.hpp"
#include "Screens.hpp"

namespace Entries {
    enum {BACK=0, QUIT=1};
}

Menu::Menu(sf::RenderWindow& window):
        window(window), selected_entry(0) {
    font.loadFromFile("fonts/arial.ttf");

    sf::Text back("back to game", font, 40);
    back.setPosition(200, 100);
    back.setColor(sf::Color::Red);
    entries.push_back(back);

    sf::Text quit("exit", font, 40);
    quit.setPosition(200, 200);
    quit.setColor(sf::Color::Red);
    entries.push_back(quit);
}

int Menu::run() {

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
            // user request to close the window
            case sf::Event::Closed:
                window.close();
                return -1;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Return) {
                    if (selected_entry == Entries::BACK) {
                        return Screens::GAME;
                    }
                    else {
                        return -1;
                    }
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    if (selected_entry > 0) {
                        selected_entry--;
                    }
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    if (selected_entry < entries.size() - 1) {
                        selected_entry++;
                    }
                }
                break;
            default:
                break;
            }
        }

        window.clear();
        draw();
        window.display();
    }
    return -1;
}

void Menu::draw() {

    unsigned int entry_number = 0;
    std::vector<sf::Text>::iterator text_it;
    for (text_it = entries.begin(); text_it != entries.end(); ++text_it) {
        if (entry_number == selected_entry) {
            text_it->setStyle(sf::Text::Bold);
        }
        else {
            text_it->setStyle(sf::Text::Regular);
        }
        window.draw(*text_it);
        ++entry_number;
    }
}
