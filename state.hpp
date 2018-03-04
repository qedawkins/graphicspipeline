#ifndef STATE_H
#define STATE_H

#include<functional>
#include<condition_variable>
#include<cmath>
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
        quit(copy->quit),
        event(copy->event) {};
    ~State();
    void step();
    void processEvents();
    int count = 0;
    float x = 960;
    float y = 540;
    int radius = 10;
    float vx = 0.0;
    float vy = 0.0;
    float ax = 0.0;
    float ay = 0.0;
    std::condition_variable* quit;
    std::shared_ptr<SDL_Event> event;
};

#endif //STATE_H
