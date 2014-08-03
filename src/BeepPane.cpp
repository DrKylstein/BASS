#include "BeepPane.hpp"

BeepPane::BeepPane(TextMode* screen) {
    _screen = screen;
    _lastPos = -1;
    _clearLinks();
}

BeepPane::~BeepPane() {
    dettach();
}

void BeepPane::updateParameter(int id, int value) {
}

void BeepPane::drawStatic() {
    _screen->box(0x07, 0, getTop(), 80, 3);
    _screen->print("Beeper", 0x07, getTop()+1,0);
}

void BeepPane::redrawParameters() {
    
}

int BeepPane::getParameterCount() {
    return 0;
}
int BeepPane::getBottom() {
    return getTop() + 3;
}

std::pair<int, int> BeepPane::getPosition(int item) {
    return std::pair<int,int>(0,0);
}
