#include "graphicspipeline.hpp"

template<typename State>
graphicspipe<State>::graphicspipe(State* initialState, std::function<void(State*, SDL_Renderer*)> rend, const int width, const int height) :
    s_width(width),
    s_height(height),
    init(*initialState),
    render(rend),
    phys(std::unique_ptr<physicspipe<State> >(new physicspipe<State>(initialState))) {
    loop.store(false);
}

template<typename State>
graphicspipe<State>::~graphicspipe() {
    pause();
}

template<typename State>
void graphicspipe<State>::rendloop() {
    SDL_Window* window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s_width, s_height, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(window == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        throw std::runtime_error("window creation failed");
    }
    if(renderer == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        throw std::runtime_error("renderer creation failed");
    }
    render(&init, renderer);
    SDL_RenderPresent(renderer);
    while(loop.load()) {
        if(phys->choose.load()) {
            render(phys->current1, renderer);
        }
        else {
            render(phys->current2, renderer);
        }
        SDL_RenderPresent(renderer);
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
