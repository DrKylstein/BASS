#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP
#include "TextScreen.hpp"
class ControlPanel {
    public:
        virtual void updateParameter(int id, int value) = 0;
        virtual void drawStatic() = 0;
};
#endif