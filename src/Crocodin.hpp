#ifndef CROCODIN_HPP
#define CROCODIN_HPP

#include "Engine.hpp"
#include "Level.hpp"

class Crocodin: public Engine {
public:
    Crocodin();
    virtual ~Crocodin();
    virtual bool run();

private:
    Level* level;
};

#endif
