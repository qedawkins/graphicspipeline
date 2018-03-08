#ifndef GRAPHICS_H
#define GRAPHICS_H

#include<stdexcept>
#include<iostream>
#include "physicspipeline.hpp"
#include "physicspipeline.cpp"
#include<SDL2/SDL.h>
#include<system_error>

template<typename helper, typename State>
class graphicspipe {
    public:
        graphicspipe<helper, State>() = default;
        graphicspipe<helper, State>(State* initialState, std::function<void(State*, SDL_Renderer*)> rend, const int width, const int height);
        ~graphicspipe();
        void start();
        void pause();
    private:
        int s_width;
        int s_height;
        State init;
        std::atomic<bool> loop;
        std::function<void(State*, SDL_Renderer*)> render;
        void rendloop();
        std::thread gloop;
        std::unique_ptr<physicspipe<helper, State> > phys;
};

#endif //GRAPHICS_H
