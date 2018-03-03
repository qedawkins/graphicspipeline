#include "physicspipeline.hpp"

template<typename State>
physicspipe<State>::physicspipe() {
    step = [](State* s) { };
    current1 = new State();
    current2 = new State();
    choose.store(false);
    loop.store(false);
}

template<typename State>
physicspipe<State>::physicspipe(State* initialState, std::function<void(State*)> evolve) {
    step = evolve;
    current1 = initialState;
    current2 = new State();
    choose.store(false);
    loop.store(false);
}

template<typename State>
physicspipe<State>::~physicspipe() {
    pause();
}

template<typename State>
void physicspipe<State>::steploopwait() {
    auto wait = std::chrono::high_resolution_clock::now() + ns;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    while(loop.load()) {
        end = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration<double, std::milli>(end-start) > ms) {
            start = end;
            wait = start + ns;
            if(choose.load()) {
                step(current1);
                choose.store(false, std::memory_order_acquire);
                *current2 = *current1;
            }
            else {
                step(current2);
                choose.store(true, std::memory_order_acquire);
                *current1 = *current2;
            }
            std::this_thread::sleep_until(wait);
        }
    }
}

template<typename State>
void physicspipe<State>::steploop() {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    while(loop.load()) {
        end = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration<double, std::milli>(end-start) > ms) {
            start = end;
            if(choose.load()) {
                step(current1);
                choose.store(false, std::memory_order_acquire);
                *current2 = *current1;
            }
            else {
                step(current2);
                choose.store(true, std::memory_order_acquire);
                *current1 = *current2;
            }
        }
    }
}

template<typename State>
void physicspipe<State>::start() {
    loop.store(true);
    std::thread sloop(&physicspipe<State>::steploop, this);
    sloop.detach();
}

template<typename State>
void physicspipe<State>::pause() {
    loop.store(false);
}
