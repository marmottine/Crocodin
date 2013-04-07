#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <boost/iterator/iterator_facade.hpp>

// forward decl
template<typename Event>
class ListenerIterator;

template<typename Event>
class ListenerList;

template<typename Event>
class BaseListener {
public:
    typedef enum {
        PREPEND = 0, APPEND = 1
    } Position;

    // avoid silly mistakes, this must always in a list
    explicit BaseListener(BaseListener<Event>& list, Position pos = PREPEND) :
            next(this), prev(this) {
        if (pos == PREPEND) {
            list.push_front(this);
        } else {
            list.push_back(this);
        }
    }

    // insert 'other' after this
    void push_front(BaseListener<Event>* other) {
        other->prev = this;
        next->prev = other;
        other->next = next;
        next = other;
    }

    // insert 'other' before this
    void push_back(BaseListener<Event>* other) {
        other->next = this;
        prev->next = other;
        other->prev = prev;
        prev = other;
    }

    ~BaseListener() {
        prev->next = next;
        next->prev = prev;
    }

private:
    friend class ListenerIterator<Event> ;
    friend class ListenerList<Event> ;

    BaseListener() :
            next(this), prev(this) {
    }

    BaseListener<Event>* next;
    BaseListener<Event>* prev;
};

template<typename Event>
class Listener: public BaseListener<Event>, public Event {
public:
    explicit Listener(BaseListener<Event>& list,
            typename BaseListener<Event>::Position pos =
                    BaseListener<Event>::PREPEND) :
            BaseListener<Event>(list, pos) {
    }

    // since this is meant to be used polymorphically
    virtual ~Listener() {
    }
};

template<typename Event>
class ListenerList: public BaseListener<Event> {
public:
    typedef ListenerIterator<Event> iterator;

    iterator begin() {
        return iterator(this->next);
    }

    iterator end() {
        return iterator(this);
    }

};

template<typename Event>
class ListenerIterator: public boost::iterator_facade<ListenerIterator<Event>,
        Listener<Event>, boost::bidirectional_traversal_tag> {
public:
    ListenerIterator() :
            ptr(NULL) {
    }

    explicit ListenerIterator(BaseListener<Event>* mptr) : ptr(mptr) {
    }

private:
    friend class boost::iterator_core_access;

    void increment() {
        ptr = ptr->next;
    }

    void decrement() {
        ptr = ptr->prev;
    }

    bool equal(const ListenerIterator& other) const {
        return ptr == other.ptr;
    }

    Listener<Event>& dereference() const {
        return *static_cast<Listener<Event>*>(ptr);
    }

    BaseListener<Event>* ptr;
};
#endif
