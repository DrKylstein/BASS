#ifndef OPLDRIVER_HPP
#define OPLDRIVER_HPP
#include <cstdint>
using std::uint8_t;
using std::uint16_t;
class OPLDriver {
    public:
        static const int CHANNEL_COUNT = 9;
        static const int OPERATOR_COUNT = 18;
        static const int MAX_VOLUME = 0x3F;
        OPLDriver();
        ~OPLDriver();
        void reset();
        void write(uint8_t reg, uint8_t value);
        uint8_t read(uint8_t reg);
        void silence();
        void enableFM(int channel, uint8_t factor);
        void disableFM(int channel);
        void setVolume(int channel, int op, int level);
        void setADSR(int channel, int op, int attack, int decay, int sustain, int release);
        void setFlags(int channel, int op, bool tremolo, bool vibrato, bool sustain, bool ksr, uint8_t fmult);
        void keyOn(int channel, uint16_t freq);
        void keyOff(int channel, uint16_t freq);
    private:
        uint16_t _ioBase;
    
};
#endif
