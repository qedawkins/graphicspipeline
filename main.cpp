#include<stdio.h>
#include<chrono>
#include<thread>
#include "graphicspipeline.hpp"
#include "graphicspipeline.cpp"
#include "physicspipeline.hpp"
#include "physicspipeline.cpp"

struct State {
    int count = 0;
};

void evolve(State& s) {
    s.count += 1;
}

frame render(State* s) {
    frame* fr = new frame();
    fr->count = s->count;
    return *fr;
}

int main(int argc, char** argv) {
    State* is = new State();
    std::function<void(State&)> evo = evolve;
    std::function<frame(State*)> rend = render;
    graphicspipe<State>* graph = new graphicspipe<State>(is, evo, rend);
    auto begin = std::chrono::high_resolution_clock::now();
    graph->start();
    while(std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now()-begin).count() < 1000) {
        printf("\r%d", graph->current.count);
    }
    graph->pause();
    return 0;
}
