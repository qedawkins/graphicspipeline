#include<stdio.h>
#include<chrono>
#include<thread>
#include<mutex>
#include<condition_variable>
#include "graphicspipeline.hpp"
#include "graphicspipeline.cpp"
#include "state.hpp"
#include "state.cpp"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
std::mutex mtx;
std::condition_variable quit;

void render(State* s, SDL_Surface* surface, SDL_Renderer* renderer) {
    SDL_Rect rect = {(int)s->x - s->radius, (int)s->y - s->radius, s->radius, s->radius};
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
    printf("\r%f", s->x);
}

void lockThread() {
    std::unique_lock<std::mutex> lck(mtx);
    quit.wait(lck);
}

int main(int argc, char** argv) {
    State* is = new State();
    is->quit = &quit;
    graphicspipe<State>* graph = new graphicspipe<State>(is, render, SCREEN_WIDTH, SCREEN_HEIGHT);
    graph->start();
    std::thread wait(lockThread);
    wait.join();
    //std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(std::chrono::milliseconds(10000)));
    graph->pause();
    return 0;
}
