#ifndef GRAPHICS_H
#define GRAPHICS_H

#include<stdexcept>
#include "physicspipeline.hpp"
#include "physicspipeline.cpp"
#include "windowresources.hpp"

template<typename State>
class graphicspipe {
    public:
        graphicspipe<State>() = default;
        graphicspipe<State>(State* initialState, std::function<void(State*, SDL_Surface*, SDL_Renderer*)> rend, const int width, const int height);
        ~graphicspipe();
        void start();
        void pause();
    private:
        int s_width;
        int s_height;
        std::atomic<bool> loop;
        std::function<void(State*,SDL_Surface*, SDL_Renderer*)> render;
        void rendloop();
        std::thread gloop;
        std::unique_ptr<physicspipe<State> > phys;
        sdl2::window_ptr_t window;
        sdl2::renderer_ptr_t renderer;
        SDL_Surface* surface;
};

#endif //GRAPHICS_H
