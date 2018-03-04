#ifndef STATE_H
#define STATE_H

#include<functional>
#include<condition_variable>
#include<SDL2/SDL.h>

class State {
    public:
    State() = default;
    State(State* copy) :
        count(copy->count),
        x(copy->x),
        y(copy->y),
        radius(copy->radius),
        vx(copy->vx),
        vy(copy->vy),
        quit(copy->quit) {};
    ~State();
    void step();
    int count = 0;
    float x = 960;
    float y = 540;
    int radius = 10;
    float vx = 400.0;
    float vy = 400.0;
    std::condition_variable* quit;
};

#endif //STATE_H
