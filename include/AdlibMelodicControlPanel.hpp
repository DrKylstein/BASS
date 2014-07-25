#ifndef ADLIBMELODICCONTROLPANEL_HPP
#define ADLIBMELODICCONTROLPANEL_HPP
#include "ControlPanel.hpp"
class AdlibMelodicControlPanel : public ControlPanel {
    public:
        AdlibMelodicControlPanel(TextScreen screen);
        void updateParameter(int id, int value);
        void drawStatic();
    private:
        TextScreen _screen;
};
#endif