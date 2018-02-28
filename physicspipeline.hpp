#ifndef PHYSICS_H
#define PHYSICS_H

#include<thread>
#include<functional>
#include<chrono>

template<typename State>
class physicspipe {
    public:
        physicspipe<State>();
        physicspipe<State>(State* initialState, std::function<void(State&)> evolve);
        ~physicspipe();
        State* current;
        void start();
        void pause();
    private:
        float ms = 5.0;
        bool loop = false;
        std::function<void(State&)> step;
        void steploop();
        std::thread sloop;
};

#endif //PHYSICS_H
