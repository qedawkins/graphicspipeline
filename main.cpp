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
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, s->count, 0xff, 0xff-s->count));
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
    SDL_FillRect(surface, &s->p1, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
    SDL_FillRect(surface, &s->p2, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
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
