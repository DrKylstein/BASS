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
        static const int PARAMETER_COUNT = 22;
        static const unsigned char _positions[AdlibMelodicControlPanel::PARAMETER_COUNT][2];
        TextScreen _screen;
        int _lastPos;
        int _values[PARAMETER_COUNT];
};
#endif