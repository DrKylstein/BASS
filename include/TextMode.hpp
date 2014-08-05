#ifndef TEXTMODE_HPP
#define TEXTMODE_HPP
#include <cstdint>
#include <string>

class TextMode {
    public:
        TextMode();
        void fill(char c, std::uint8_t attrib, int x, int y, int width, int height);
        void print(char c, std::uint8_t attrib, int x, int y);
        std::uint16_t get(int x, int y);
        void print(std::string str, std::uint8_t attrib, int x, int y);
        void print(int num, std::uint8_t attrib, int x, int y);
        void printHex(int num, std::uint8_t attrib, int x, int y);
        void box(std::uint8_t attrib, int x, int y, int width, int height);
        void hbar(std::uint8_t attrib, int x, int y, int width);
    
        void moveCursorTo(std::uint8_t x, std::uint8_t y);
        void moveCursorBy(std::uint8_t x, std::uint8_t y);
        void hideCursor();
        void showCursor();
        void setCursorHeight(int h);

    private:
        std::uint8_t _x, _y;
        std::uint8_t _top, _bottom;
};
#endif
