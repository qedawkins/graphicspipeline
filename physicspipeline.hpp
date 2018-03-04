#ifndef PHYSICS_H
#define PHYSICS_H

#include<thread>
#include<functional>
#include<atomic>
#include<chrono>

template<typename State>
class physicspipe {
    public:
        physicspipe<State>() = default;
        physicspipe<State>(State* initialState);
        ~physicspipe();
        State* current1;
        State* current2;
        std::atomic<bool> choose;
        void start();
        void pause();
    private:
        std::chrono::nanoseconds ns = std::chrono::nanoseconds(500000);
        std::chrono::milliseconds ms = std::chrono::milliseconds(10);
        std::atomic<bool> loop;
        void steploop();
        void steploopwait();
        std::thread sloop;
};

#endif //PHYSICS_H
