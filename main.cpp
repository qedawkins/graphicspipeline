#include<stdio.h>
#include<chrono>
#include<thread>
#include<mutex>
#include<condition_variable>
#include "graphicspipeline.hpp"
#include "graphicspipeline.cpp"
#include "state.hpp"
#include "state.cpp"
#include "physicshelper.hpp"
#include "physicshelper.cpp"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
std::mutex mtx;
std::condition_variable quit;

void lockThread() {
    std::unique_lock<std::mutex> lck(mtx);
    quit.wait(lck);
}

int main(int argc, char** argv) {
    State* is = new State();
    std::shared_ptr<SDL_Event> e = std::make_shared<SDL_Event>();
    is->quit = &quit;
    is->event = e;
    graphicspipe<physicshelper<State>, State>* graph = new graphicspipe<physicshelper<State>, State>(is, SCREEN_WIDTH, SCREEN_HEIGHT);
    graph->start();
    std::thread wait(lockThread);
    wait.join();
    graph->pause();
    return 0;
}
