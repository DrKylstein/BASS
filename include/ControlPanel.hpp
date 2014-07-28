#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP
#include "TextScreen.hpp"
#include <utility>
class ControlPanel {
    public:
        virtual void updateParameter(int id, int value) = 0;
        virtual void drawStatic() = 0;
        virtual int getBottom() = 0;
        int getTop();
    
        virtual std::pair<int, int> getPosition(int item) = 0;
        virtual int getParameterCount() = 0;
    
        void insertAfter(ControlPanel& p);
        void dettach();
        ControlPanel* getNext();
        ControlPanel* getPrevious();
    protected:
        void _clearLinks();
    private:
        ControlPanel* _next;
        ControlPanel* _previous;
};
#endif