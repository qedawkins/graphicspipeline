#include "frame.hpp"

frame::frame() {
    count = 0;
}

frame::~frame() {
}

void frame::display() {
    printf("\r%d", count);
}
