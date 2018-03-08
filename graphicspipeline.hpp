#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "physicspipeline.hpp"
#include "physicspipeline.cpp"
#include "texture.hpp"
#include "texture.cpp"
#include<system_error>
#include<string>

template<typename helper, typename State>
class graphicspipe {
    public:
        graphicspipe<helper, State>() = default;
        graphicspipe<helper, State>(State* initialState, const int width, const int height);
        ~graphicspipe();
        void start();
        void pause();
    private:
        int s_width;
        int s_height;
        texture* background;
        texture* sprites[3];
        State init;
        std::atomic<bool> loop;
        void render(State* s, SDL_Renderer* rend);
        void rendloop();
        void loadTextures(SDL_Renderer* rend, std::string path[3]);
        void loadBackground(SDL_Renderer* rend, std::string path);
        std::thread gloop;
        std::unique_ptr<physicspipe<helper, State> > phys;
};

#endif //GRAPHICS_H
