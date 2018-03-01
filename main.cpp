#include<stdio.h>
#include<chrono>
#include<thread>
#include "graphicspipeline.hpp"
#include "graphicspipeline.cpp"
#include "physicspipeline.hpp"
#include "physicspipeline.cpp"
#include "state.hpp"

void evolve(State* s) {
    //s->pos = ((s->pos+1) & (~(!(s->pos >> 4))+1));
    s->count += 1;
}

void render(State* s, std::unique_ptr<frame>& fr) {
    fr->count = s->count;
}

int main(int argc, char** argv) {
    State* is = new State();
    graphicspipe<State>* graph = new graphicspipe<State>(is, evolve, render);
    auto begin = std::chrono::high_resolution_clock::now();
    graph->start();
    while(std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now()-begin).count() < 10000) {
        printf("\r%d", graph->current->count);
    }
    graph->pause();
    return 0;
}
