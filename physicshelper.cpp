#include "physicshelper.hpp"

template<typename State>
physicshelper<State>::physicshelper(State* init) {
    current1 = new State(init);
    current2 = new State(init);
    current.store(current1);
    choose.store(false);
}

template<typename State>
physicshelper<State>::~physicshelper() {
    delete current1;
    delete current2;
}

template<typename State>
void physicshelper<State>::step() {
    if(choose.load(std::memory_order_relaxed)) {
        current1->step();
        current.store(current1);
        choose.store(false, std::memory_order_relaxed);
        *current2 = *current1;
    }
    else {
        current2->step();
        current.store(current2);
        choose.store(true, std::memory_order_relaxed);
        *current1 = *current2;
    }
}
