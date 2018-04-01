#include "graphicspipeline.hpp"

template<typename helper, typename State>
graphicspipe<helper, State>::graphicspipe(State* initialState, const int width, const int height) :
    s_width(width),
    s_height(height),
    init(*initialState),
    phys(std::unique_ptr<physicspipe<helper, State> >(new physicspipe<helper, State>(initialState))) {
    background = new texture();
    for(int i = 0; i < 3; i++) {
        sprites[i] = new texture();
    }
    for(int i = 0; i < 10; i++) {
        characters[i] = new texture();
    }
    loop.store(false);
}

template<typename helper, typename State>
graphicspipe<helper, State>::~graphicspipe() {
    pause();
    for(int i = 0; i < 3; i++) {
        delete sprites[i];
    }
    for(int i = 0; i < 10; i++) {
        delete characters[i];
    }
    delete background;
}

template<typename helper, typename State>
void graphicspipe<helper, State>::rendloopFRAMERATE() {
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
    loadBackground(renderer, "sprites/bkgrd.png");
    std::string paths[3] = {"sprites/ball.png", "sprites/barsprite.png", "sprites/barsprite2.png"};
    loadTextures(renderer, paths);
    render(&init, renderer);
    SDL_RenderPresent(renderer);
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    while(loop.load()) {
        render(phys->help->current.load(), renderer);
        SDL_RenderPresent(renderer);
        framerate++;
        end = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration<float, std::milli>(end-start) > std::chrono::milliseconds(1000)) {
            start = std::chrono::high_resolution_clock::now();
            std::cout << framerate << std::endl;
            framerate = 0;
        }
    }
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
    loadBackground(renderer, "sprites/bkgrd.png");
    std::string paths[3] = {"sprites/ball.png", "sprites/barsprite.png", "sprites/barsprite2.png"};
    loadTextures(renderer, paths);
    loadNumbers(renderer);
    render(&init, renderer);
    SDL_RenderPresent(renderer);
    while(loop.load()) {
        render(phys->help->current.load(), renderer);
        SDL_RenderPresent(renderer);
    }
}

template<typename helper, typename State>
inline void graphicspipe<helper, State>::render(State* s, SDL_Renderer* rend) {
    SDL_RenderClear(rend);
    background->render(rend);
    sprites[0]->render(rend, s->x, s->y);
    sprites[1]->render(rend, s->p1.x, s->p1.y);
    sprites[2]->render(rend, s->p2.x, s->p2.y);
    characters[s->scorel]->render(rend, 900, 20);
    characters[s->scorer]->render(rend, 980, 20);
}

template<typename helper, typename State>
void graphicspipe<helper, State>::loadTextures(SDL_Renderer* rend, std::string path[3]) {
    for(int i = 0; i < 3; i++) {
        sprites[i]->loadTexture(path[i], rend);
    }
}

template<typename helper, typename State>
void graphicspipe<helper, State>::loadNumbers(SDL_Renderer* rend) {
    characters[0]->loadTexture("sprites/zero.png", rend);
    characters[1]->loadTexture("sprites/one.png", rend);
    characters[2]->loadTexture("sprites/two.png", rend);
    characters[3]->loadTexture("sprites/three.png", rend);
    characters[4]->loadTexture("sprites/four.png", rend);
    characters[5]->loadTexture("sprites/five.png", rend);
    characters[6]->loadTexture("sprites/six.png", rend);
    characters[7]->loadTexture("sprites/seven.png", rend);
    characters[8]->loadTexture("sprites/eight.png", rend);
    characters[9]->loadTexture("sprites/nine.png", rend);
}

template<typename helper, typename State>
void graphicspipe<helper, State>::loadBackground(SDL_Renderer* rend, std::string path) {
    background->loadTexture(path, rend);
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
