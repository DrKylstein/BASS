#ifndef TEXTCURSOR_HPP
#define TEXTCURSOR_HPP
#include <cstdint>
class TextCursor {
    public:
        TextCursor();
        void moveTo(std::uint8_t x, std::uint8_t y);
        void moveBy(std::uint8_t x, std::uint8_t y);
        void hide();
        void show();
    private:
        std::uint8_t _x, _y;
        std::uint8_t _top, _bottom;
};
#endif