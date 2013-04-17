#ifndef SCREEN_HPP
#define SCREEN_HPP

class Screen {
public:
    virtual ~Screen();
    virtual int run() = 0;
};

inline Screen::~Screen() { }

#endif
