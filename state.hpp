#ifndef STATE_H
#define STATE_H

#include<functional>
#include<condition_variable>
#include<cmath>
#include<iostream>
#include<SDL2/SDL.h>

class State {
    public:
    State() = default;
    State(State* copy) :
        count(copy->count),
        x(copy->x),
        y(copy->y),
        ax(copy->ax),
        ay(copy->ay),
        radius(copy->radius),
        vx(copy->vx),
        vy(copy->vy),
        p1y(copy->p1y),
        p2y(copy->p2y),
        v1y(copy->v1y),
        v2y(copy->v2y),
        scorel(copy->scorel),
        scorer(copy->scorer),
        p1(copy->p1),
        p2(copy->p2),
        quit(copy->quit),
        event(copy->event) {};
    ~State();
    void step();
    void processEvents();
    int count = 0;
    float x = 960;
    float y = 540;
    float ax = 0.0;
    float ay = 0.0;
    int radius = 10;
    float vx = 750.0;
    float vy = 750.0;
    float p1y = 0.0;
    float p2y = 0.0;
    float v1y = 0.0;
    float v2y = 0.0;
    uint16_t scorel = 0;
    uint16_t scorer = 0;
    SDL_Rect p1 = {20, 500, 20, 80};
    SDL_Rect p2 = {1880, 500, 20, 80};
    std::condition_variable* quit;
    std::shared_ptr<SDL_Event> event;
};

#endif //STATE_H
