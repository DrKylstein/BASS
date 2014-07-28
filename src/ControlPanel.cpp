#include "ControlPanel.hpp"
int ControlPanel::getTop() {
    if(getPrevious())
        return getPrevious()->getBottom();
    return 0;
}

void ControlPanel::insertAfter(ControlPanel& p) {
    _next = p._next;
    _previous = &p;
    p._next = this;
}
void ControlPanel::dettach() {
    _next->_previous = _previous;
    _previous->_next = _next;
    _next = 0;
    _previous = 0;
}
ControlPanel* ControlPanel::getNext() {
    return _next;
}
ControlPanel* ControlPanel::getPrevious() {
    return _previous;
}

void ControlPanel::_clearLinks() {
    _next = _previous = 0;
}
