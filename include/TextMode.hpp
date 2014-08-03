#ifndef TEXTMODE_HPP
#define TEXTMODE_HPP
#include <cstdint>
#include <string>
using std::uint16_t;
using std::uint8_t;

class TextMode {
    public:
        TextMode();
        void fill(char c, uint8_t attrib, int x, int y, int width, int height);
        void print(std::string str, uint8_t attrib, int x, int y);
        void print(int num, uint8_t attrib, int x, int y);
        void printHex(int num, uint8_t attrib, int x, int y);
        void box(uint8_t attrib, int x, int y, int width, int height);
        void hbar(uint8_t attrib, int x, int y, int width);
        void setAttrib(uint8_t attrib, int x, int y, int width, int height);
    private:
        uint16_t far* mScreen;
};
#endif
