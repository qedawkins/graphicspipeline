#include "frame.hpp"

frame::frame() {
    count = 0;
}

frame::~frame() {
}

void frame::operator=(frame f) {
    count = f.count;
}
