#ifndef HELPER_H
#define HELPER_H

#include<atomic>

template<typename State>
class physicshelper {
    public:
    physicshelper() = default;
    physicshelper(State* init);
    ~physicshelper();
    std::atomic<State*> current;
    void step();
    private:
    std::atomic<bool> choose;
    State* current1;
    State* current2;
};

#endif //HELPER_H
