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

inline void render(State* s, SDL_Renderer* renderer) {
    SDL_Rect rect = {(int)s->x - s->radius, (int)s->y - s->radius, s->radius, s->radius};
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, s->count, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &s->p1);
    SDL_RenderFillRect(renderer, &s->p2);
}

void lockThread() {
    std::unique_lock<std::mutex> lck(mtx);
    quit.wait(lck);
}

int main(int argc, char** argv) {
    State* is = new State();
    std::shared_ptr<SDL_Event> e = std::make_shared<SDL_Event>();
    is->quit = &quit;
    is->event = e;
    graphicspipe<State>* graph = new graphicspipe<State>(is, render, SCREEN_WIDTH, SCREEN_HEIGHT);
    graph->start();
    std::thread wait(lockThread);
    wait.join();
    graph->pause();
    return 0;
}
