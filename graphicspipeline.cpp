#include "graphicspipeline.hpp"

template<typename State>
graphicspipe<State>::graphicspipe() {
}

template<typename State>
graphicspipe<State>::graphicspipe(State* initialState, std::function<void(State*)> evolve, std::function<frame*(State*,frame*)> rend) {
    render = rend;
    phys = new physicspipe<State>(initialState, evolve);
    frame* fr = new frame();
    current = render(initialState, fr);
}

template<typename State>
graphicspipe<State>::~graphicspipe() {
    pause();
}

template<typename State>
void graphicspipe<State>::rendloop() {
    while(loop) {
        current = render(phys->current, current);
    }
}

template<typename State>
void graphicspipe<State>::start() {
    loop = true;
    phys->start();
    std::thread gloop(&graphicspipe<State>::rendloop, this);
    gloop.detach();
}

template<typename State>
void graphicspipe<State>::pause() {
    loop = false;
}
