#include "AdlibMelodicControlPanel.hpp"

static const int _positions[20][2] = {
    {6,2},{10,2},{14,2},{18,2},{22,2},{26,2}, {30,2},{34,2},{38,2}, {44,2},{48,2},
    {6,3},{10,3},{14,3},{18,3},{22,3},{26,3}, {30,3},{34,3},{38,3}
};

static const char* labels[11] = {
    "Atk","Dcy","Stn","Rls","Vol","Frq","Hld","Trm","Vib","FM","Fbk"
};

AdlibMelodicControlPanel::AdlibMelodicControlPanel(TextScreen screen) {
    _clearLinks();
    _screen = screen;
    _lastPos = -1;
}

std::pair<int, int> AdlibMelodicControlPanel::getPosition(int item) {
    return std::pair<int,int>(_positions[item][0], _positions[item][1]+getTop());
}


AdlibMelodicControlPanel::~AdlibMelodicControlPanel() {
    dettach();
}

void AdlibMelodicControlPanel::updateParameter(int id, int value) {
    _values[id] = value;
    _screen.print("00",0x82,_positions[id][0],_positions[id][1]+getTop());
    _screen.print(value,0x82,_positions[id][0]+1,_positions[id][1]+getTop());
}

void AdlibMelodicControlPanel::drawStatic() {
    _screen.box(0x07, 0, getTop(), 80, 5);
    _screen.print("Adlib Melodic", 0x07, 1, getTop());
    _screen.print("OP1",0x07,2,getTop()+2);
    _screen.print("OP1",0x07,2,getTop()+3);
    for(int i = 0; i < 11; i++) {
        _screen.print(labels[i],0x07,_positions[i][0],_positions[i][1]-1+getTop());
    }
    for(int i = 0; i < 16; i++) {
        _screen.print("00",0x82,_positions[i][0],_positions[i][1]+getTop());
    }
}

int AdlibMelodicControlPanel::getParameterCount() {
    return 20;
}

int AdlibMelodicControlPanel::getBottom() {
    return getTop() + 5;
}
