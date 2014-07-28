#ifndef BEEPERCONTROLPANEL_HPP
#define BEEPERCONTROLPANEL_HPP
#include "ControlPanel.hpp"
class BeeperControlPanel : public ControlPanel {
    public:
        BeeperControlPanel(TextScreen screen);
        ~BeeperControlPanel();
        void updateParameter(int id, int value);
        void drawStatic();
        int getBottom();
    
        std::pair<int, int> getPosition(int item);
        int getParameterCount();
    private:
        TextScreen _screen;
        int _lastPos;
};
#endif