#include<stdio.h>
#include<chrono>
#include<thread>
#include "graphicspipeline.hpp"
#include "graphicspipeline.cpp"
#include "physicspipeline.hpp"
#include "physicspipeline.cpp"
#include "state.hpp"

void evolve(State* s) {
    s->count += 1;
}

void render(State* s, std::unique_ptr<frame>& fr) {
    fr->count = s->count;
}

int main(int argc, char** argv) {
    State* is = new State();
    graphicspipe<State>* graph = new graphicspipe<State>(is, evolve, render);
    graph->start();
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(std::chrono::milliseconds(10000)));
    graph->pause();
    return 0;
}
