#include <iostream>

#include "Crocodin.hpp"
#include "Screens.hpp"
#include "Crocodile.hpp"
#include "Level.hpp"

Crocodin::Crocodin() {
    level = new Level(*this);
}

Crocodin::~Crocodin() {
    delete level;
}

bool Crocodin::run() {
    title = "Crocodin!";
    return Engine::run();
}
