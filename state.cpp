#include "state.hpp"

State::~State() {
}

void State::processEvents() {
    SDL_Event* e = event.get();
    while(SDL_PollEvent(e)) {
        switch(e->type) {
            case SDL_KEYDOWN:
                if(e->key.state == SDL_PRESSED) {
                    switch(e->key.keysym.sym) {
                        case SDLK_w:
                            v1y = -500.0;
                        break;
                        case SDLK_s:
                            v1y = 500.0;
                        break;
                        case SDLK_UP:
                            v2y = -500.0;
                        break;
                        case SDLK_DOWN:
                            v2y = 500.0;
                        break;
                    }
                }
            break;
            case SDL_KEYUP:
                if(e->key.state == SDL_RELEASED) {
                    switch(e->key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_s:
                            v1y = 0;
                        break;
                        case SDLK_DOWN:
                        case SDLK_UP:
                            v2y = 0;
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
    p1y += 0.005*v1y;
    p2y += 0.005*v2y;
    if(x <= 0 || x >= 1920) {
        x = x < 1 ? 0 : 1920;
        vx = -vx;
    }
    if(y <= 0 || y >= 1080) {
        y = y < 1 ? 0 : 1080;
        vy = -vy;
    }
    if(p1y < -500.0 || p1y > 500.0) {
        p1y = p1y < 0 ? -500.0 : 500.0;
        v1y = 0;
    }
    if(p2y < -500.0 || p2y > 500.0) {
        p2y = p2y < 0 ? -500.0 : 500.0;
        v2y = 0;
    }
    p1 = {20, (int)(500.0 + p1y), 20, 80};
    p2 = {1880, (int)(500.0 + p2y), 20, 80};
    if(((x <= p1.x + p1.w) && (x >= p1.x))) {
        if(y >= p1.y && y <= p1.y + p1.h)
            vx = -vx;
    }
    if(((x >= p2.x) && (x <= p2.x + p2.w))) {
        if(y >= p2.y && y <= p2.y + p2.h)
            vx = -vx;
    }
    //vx += 0.005*ax;
    //vy += 0.005*ay;
    /*float magx = std::pow(vx, 2);
    float magy = std::pow(vy, 2);
    float mag = magx + magy;
    if(mag > 750.0) {
        vx = 750.0*(magx/mag)*((vx < 0.0) - (0.0 < vx));
        vx = 750.0*(magy/mag)*((vy < 0.0) - (0.0 < vy));
    }*/
}
