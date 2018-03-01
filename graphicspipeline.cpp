#include "graphicspipeline.hpp"

template<typename State>
graphicspipe<State>::graphicspipe() {
}

template<typename State>
graphicspipe<State>::graphicspipe(State* initialState, std::function<void(State*)> evolve, std::function<void(State*,std::unique_ptr<frame>&)> rend) {
    render = rend;
    phys = std::unique_ptr<physicspipe<State> >(new physicspipe<State>(initialState, evolve));
    current = std::unique_ptr<frame>(new frame());
    render(initialState, current);
}

template<typename State>
graphicspipe<State>::~graphicspipe() {
    pause();
}

template<typename State>
void graphicspipe<State>::rendloop() {
    while(loop) {
        render(phys->current, current);
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
