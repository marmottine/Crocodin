#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Resources.hpp"
#include "Listener.hpp"

class UpdateEvent {
public:
    virtual void update(sf::Time elapsed) = 0;
protected:
    // not meant to be used polymorphically, so protected non-virtual
    ~UpdateEvent() {
    }
};

class RenderEvent {
public:
    virtual void render(sf::RenderWindow& window) = 0;
protected:
    // not meant to be used polymorphically, so protected non-virtual
    ~RenderEvent() {
    }
};

class KeypressEvent {
public:
    virtual void keypress(sf::Event::KeyEvent& key) = 0;
protected:
    // not meant to be used polymorphically, so protected non-virtual
    ~KeypressEvent() {
    }
};

class State {
public:
    ListenerList<UpdateEvent> updateListeners;
    ListenerList<RenderEvent> renderListeners;
    ListenerList<KeypressEvent> keypressListeners;
};

class Engine: protected UpdateEvent,
        protected RenderEvent,
        protected KeypressEvent {
public:
    virtual bool run();

    // maybe should move to protected for these?
    // swapping state invalidates iterators
    // should be some kind of stack
    State state;
    Resources resources;

protected:
    std::string title;
    virtual void update(sf::Time elapsed);
    virtual void render(sf::RenderWindow& window);
    virtual void keypress(sf::Event::KeyEvent& key);
    ~Engine() {
    }
};

#endif
