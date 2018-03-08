#include "graphicspipeline.hpp"

template<typename helper, typename State>
graphicspipe<helper, State>::graphicspipe(State* initialState, const int width, const int height) :
    s_width(width),
    s_height(height),
    init(*initialState),
    phys(std::unique_ptr<physicspipe<helper, State> >(new physicspipe<helper, State>(initialState))) {
    loop.store(false);
}

template<typename helper, typename State>
graphicspipe<helper, State>::~graphicspipe() {
    pause();
}

template<typename helper, typename State>
void graphicspipe<helper, State>::rendloop() {
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
        render(phys->help->current.load(), renderer);
        SDL_RenderPresent(renderer);
    }
}

template<typename helper, typename State>
void graphicspipe<helper, State>::render(State* s, SDL_Renderer* rend) {
    SDL_Rect rect = {(int)s->x - s->radius, (int)s->y - s->radius, s->radius, s->radius};
    SDL_SetRenderDrawColor(rend, 0xff, 0xff, s->count, 0xff);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 0x0, 0x0, 0x0, 0xff);
    SDL_RenderFillRect(rend, &rect);
    SDL_RenderFillRect(rend, &s->p1);
    SDL_RenderFillRect(rend, &s->p2);
}

template<typename helper, typename State>
void graphicspipe<helper, State>::start() {
    loop.store(true);
    phys->start();
    std::thread gloop(&graphicspipe<helper, State>::rendloop, this);
    gloop.detach();
}

template<typename helper, typename State>
void graphicspipe<helper, State>::pause() {
    loop.store(false);
}
