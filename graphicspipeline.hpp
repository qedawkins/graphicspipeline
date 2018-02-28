#ifndef GRAPHICS_H
#define GRAPHICS_H

#include<thread>
#include<functional>
#include<chrono>
#include "physicspipeline.hpp"
#include "frame.hpp"

template<typename State>
class graphicspipe {
    public:
        graphicspipe<State>();
        graphicspipe<State>(State initialState, std::function<void(State&)> evolve, std::function<frame(State*)> rend);
        ~graphicspipe();
        frame current;
        void start();
        void pause();
    private:
        bool loop = false;
        std::function<frame(State*)> render;
        void rendloop();
        std::thread gloop;
        physicspipe<State> phys;
};

#endif //GRAPHICS_H
