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
        graphicspipe<State>(State* initialState, std::function<void(State*)> evolve, std::function<void(State*,std::unique_ptr<frame>&)> rend);
        ~graphicspipe();
        std::unique_ptr<frame> current;
        void start();
        void pause();
    private:
        bool loop = false;
        std::function<void(State*,std::unique_ptr<frame>&)> render;
        void rendloop();
        std::thread gloop;
        std::unique_ptr<physicspipe<State> > phys;
};

#endif //GRAPHICS_H
