#include "physicspipeline.hpp"

template<typename helper, typename State>
physicspipe<helper, State>::physicspipe(State* initialState) :
    help(std::unique_ptr<helper>(new helper(initialState))) {
    loop.store(false);
}

template<typename helper, typename State>
physicspipe<helper, State>::~physicspipe() {
    pause();
}

template<typename helper, typename State>
void physicspipe<helper, State>::steploopwait() {
    auto wait = std::chrono::high_resolution_clock::now() + ns;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    while(loop.load()) {
        end = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration<double, std::milli>(end-start) > ms) {
            start = end;
            wait = start + ns;
            help->step();
            std::this_thread::sleep_until(wait);
        }
    }
}

template<typename helper, typename State>
void physicspipe<helper, State>::steploop() {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    while(loop.load()) {
        end = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration<double, std::milli>(end-start) > ms) {
            start = end;
            help->step();
        }
    }
}

template<typename helper, typename State>
void physicspipe<helper, State>::start() {
    loop.store(true);
    std::thread sloop(&physicspipe<helper, State>::steploop, this);
    sloop.detach();
}

template<typename helper, typename State>
void physicspipe<helper, State>::pause() {
    loop.store(false);
}
