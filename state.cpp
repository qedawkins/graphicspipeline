#include "state.hpp"

State::~State() {
}

void State::step() {
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
    if(count == 0xFE)
        quit->notify_all();
}
