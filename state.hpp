#ifndef STATE_H
#define STATE_H

#include<functional>

class State {
    public:
    State() = default;
    State(State* copy) :
        count(copy->count),
        x(copy->x),
        y(copy->y),
        radius(copy->radius),
        vx(copy->vx),
        vy(copy->vy) {};
    ~State();
    void step();
    int count = 0;
    float x = 960;
    float y = 540;
    int radius = 10;
    float vx = 2.0;
    float vy = 2.0;
};

#endif //STATE_H
