#include "physicspipeline.hpp"

template<typename State>
physicspipe<State>::physicspipe() {
    step = [](State* s) { };
    current = new State();
}

template<typename State>
physicspipe<State>::physicspipe(State* initialState, std::function<void(State*)> evolve) {
    step = evolve;
    current = initialState;
}

template<typename State>
physicspipe<State>::~physicspipe() {
    pause();
}

template<typename State>
void physicspipe<State>::steploop() {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    while(loop) {
        end = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration<double, std::milli>(end-start).count() > ms) {
            start = end;
            step(current);
        }
    }
}

template<typename State>
void physicspipe<State>::start() {
    loop = true;
    std::thread sloop(&physicspipe<State>::steploop, this);
    sloop.detach();
}

template<typename State>
void physicspipe<State>::pause() {
    loop = false;
}
