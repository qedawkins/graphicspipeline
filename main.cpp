#include<stdio.h>
#include<chrono>
#include<thread>
#include "graphicspipeline.hpp"
#include "graphicspipeline.cpp"
#include "state.hpp"
#include "state.cpp"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

void render(State* s, SDL_Surface* surface) {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, s->count, 0, 255-s->count));
    printf("\r%d", s->count);
}

int main(int argc, char** argv) {
    State* is = new State();
    graphicspipe<State>* graph = new graphicspipe<State>(is, render, SCREEN_WIDTH, SCREEN_HEIGHT);
    graph->start();
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(std::chrono::milliseconds(10000)));
    graph->pause();
    return 0;
}
