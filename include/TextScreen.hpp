#ifndef TEXTSCREEN_HPP
#define TEXTSCREEN_HPP
#include <cstdint>
#include <string>
using std::uint16_t;
using std::uint8_t;

class TextScreen {
    public:
        TextScreen();
        void fill(char c, uint8_t attrib, int x, int y, int width, int height);
        void print(std::string str, uint8_t attrib, int x, int y);
        void print(int num, uint8_t attrib, int x, int y);
        void box(uint8_t attrib, int x, int y, int width, int height);
        void hbar(uint8_t attrib, int x, int y, int width);
        void setAttrib(uint8_t attrib, int x, int y, int width, int height);
        TextScreen subScreen(int x, int y);
    private:
        uint16_t far* mScreen;
        TextScreen(uint16_t far* screen);
};
#endif
