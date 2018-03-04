#include "graphicspipeline.hpp"

template<typename State>
graphicspipe<State>::graphicspipe(State* initialState, std::function<void(State*)> evolve, std::function<void(State*, SDL_Surface*)> rend, const int width, const int height) :
    window(sdl2::make_window("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN)) {
    render = rend;
    phys = std::unique_ptr<physicspipe<State> >(new physicspipe<State>(initialState, evolve));
    s_width = width;
    s_height = height;
    if(window == nullptr)
        throw std::runtime_error("window creation failed");
    surface = SDL_GetWindowSurface(window.get());
    loop.store(false);
    render(initialState, surface);
    SDL_UpdateWindowSurface(window.get());
}

template<typename State>
graphicspipe<State>::~graphicspipe() {
    pause();
}

template<typename State>
void graphicspipe<State>::rendloop() {
    while(loop.load()) {
        if(phys->choose.load())
            render(phys->current1, surface);
        else
            render(phys->current2, surface);
        SDL_UpdateWindowSurface(window.get());
    }
}

template<typename State>
void graphicspipe<State>::start() {
    loop.store(true);
    phys->start();
    std::thread gloop(&graphicspipe<State>::rendloop, this);
    gloop.detach();
}

template<typename State>
void graphicspipe<State>::pause() {
    loop.store(false);
}
