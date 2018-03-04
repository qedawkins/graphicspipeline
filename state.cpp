#include "state.hpp"

State::~State() {
}

void State::processEvents() {
    SDL_Event e = *event.get();
    while(!SDL_PollEvent(event.get())) {
        switch(e.type) {
            case SDL_KEYDOWN:
                if(e.key.state == SDL_PRESSED) {
                    switch(e.key.keysym.sym) {
                        case SDLK_w:
                            ay = -10.0;
                        break;
                        case SDLK_s:
                            ay = 10.0;
                        break;
                        case SDLK_a:
                            ax = -10.0;
                        break;
                        case SDLK_d:
                            ax = 10.0;
                        break;
                    }
                }
            break;
            case SDL_KEYUP:
                if(e.key.state == SDL_RELEASED) {
                    switch(e.key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_s:
                            ay = 0;
                        break;
                        case SDLK_a:
                        case SDLK_d:
                            ax = 0;
                        break;
                    }
                }
            break;
            case SDL_QUIT:
                quit->notify_all();
                return;
            break;
        }
    }
}

void State::step() {
    processEvents();
    if(count == 0xFF)
        count = 0;
    else
        count += 1;
    x += 0.005*vx;
    y += 0.005*vy;
    if(x <= 0 || x >= 1920) {
        x = x < 1 ? 0 : 1920;
        vx = -vx;
    }
    if(y <= 0 || y >= 1080) {
        y = y < 1 ? 0 : 1080;
        vy = -vy;
    }
    vx += 0.005*ax;
    vy += 0.005*ay;
    int magx = std::pow(vx, 2);
    int magy = std::pow(vy, 2);
    int mag = magx + magy;
    if(mag > 750.0) {
        vx = 750.0*(magx/mag);
        vx = 750.0*(magy/mag);
    }
}
