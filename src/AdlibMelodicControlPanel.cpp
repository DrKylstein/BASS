#include "AdlibMelodicControlPanel.hpp"

static const int _positions[20][2] = {
    {6,1},{10,1},{14,1},{18,1},{22,1},{26,1}, {30,1},{34,1},{38,1}, {44,1},{48,1},
    {6,2},{10,2},{14,2},{18,2},{22,2},{26,2}, {30,2},{34,2},{38,2}
};

static const char* labels[11] = {
    "Atk","Dcy","Stn","Rls","Vol","Frq","Hld","Trm","Vib","FM","Fbk"
};

AdlibMelodicControlPanel::AdlibMelodicControlPanel(TextScreen screen) {
    _screen = screen;
}

void AdlibMelodicControlPanel::updateParameter(int id, int value) {
    _screen.print("00",0x82,_positions[id][0],_positions[id][1]);
    _screen.print(value,0x82,_positions[id][0]+1,_positions[id][1]);
}

void AdlibMelodicControlPanel::drawStatic() {
    _screen.print("OP1",0x07,2,1);
    _screen.print("OP1",0x07,2,2);
    for(int i = 0; i < 11; i++) {
        _screen.print(labels[i],0x07,_positions[i][0],_positions[i][1]-1);
    }
    for(int i = 0; i < 16; i++) {
        _screen.print("00",0x82,_positions[i][0],_positions[i][1]);
    }
}
