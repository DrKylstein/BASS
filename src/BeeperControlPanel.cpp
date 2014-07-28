#include "BeeperControlPanel.hpp"

BeeperControlPanel::BeeperControlPanel(TextScreen screen) {
    _screen = screen;
    _lastPos = -1;
    _clearLinks();
}

BeeperControlPanel::~BeeperControlPanel() {
    dettach();
}

void BeeperControlPanel::updateParameter(int id, int value) {
}

void BeeperControlPanel::drawStatic() {
    _screen.box(0x07, 0, getTop(), 80, 3);
    _screen.print("Beeper", 0x07, getTop()+1,0);
}

int BeeperControlPanel::getParameterCount() {
    return 0;
}
int BeeperControlPanel::getBottom() {
    return getTop() + 3;
}

std::pair<int, int> BeeperControlPanel::getPosition(int item) {
    return std::pair<int,int>(0,0);
}
