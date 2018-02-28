#include<stdio.h>
#include<chrono>
#include<thread>
#include "graphicspipeline.hpp"
#include "graphicspipeline.cpp"
#include "physicspipeline.hpp"
#include "physicspipeline.cpp"
#include "state.hpp"

void evolve(State* s) {
    s->pos = ((s->pos+1) & (~(!(s->pos >> 4))+1));
}

frame* render(State* s, frame* fr) {
    printf("\r");
    for(int i = 0; i < s->pos; i++) {
        printf(" ");
    }
    printf("%c", s->move);
    return fr;
}

int main(int argc, char** argv) {
    State* is = new State();
    std::function<void(State*)> evo = evolve;
    std::function<frame*(State*,frame*)> rend = render;
    graphicspipe<State>* graph = new graphicspipe<State>(is, evo, rend);
    auto begin = std::chrono::high_resolution_clock::now();
    graph->start();
    while(std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now()-begin).count() < 10000) {
        //printf("\r%d", graph->current);
    }
    graph->pause();
    return 0;
}
