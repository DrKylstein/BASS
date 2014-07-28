#ifndef ADLIBMELODICCONTROLPANEL_HPP
#define ADLIBMELODICCONTROLPANEL_HPP
#include "ControlPanel.hpp"
class AdlibMelodicControlPanel : public ControlPanel {
    public:
        AdlibMelodicControlPanel(TextScreen screen);
        ~AdlibMelodicControlPanel();
        void updateParameter(int id, int value);
        void drawStatic();
        int getBottom();
    
        std::pair<int, int> getPosition(int item);
        int getParameterCount();
    private:
        TextScreen _screen;
        int _lastPos;
        int _values[20];
};
#endif