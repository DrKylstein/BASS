#ifndef OPLDRIVER_HPP
#define OPLDRIVER_HPP
#include <cstdint>
using std::uint8_t;
using std::uint16_t;
class OPLDriver {
    public:
        enum SynthMode {
            FM_SYNTH,
            ADDITIVE_SYNTH
        };
        static const int CHANNEL_COUNT = 9;
        static const int OPERATOR_COUNT = 18;
        static const int MAX_VOLUME = 0x3F;
        OPLDriver();
        ~OPLDriver();
        void reset();
        void write(uint8_t reg, uint8_t value);
        uint8_t read(uint8_t reg);
        void silence();
        void setMode(int channel, SynthMode mode);
        void setVolume(int channel, int op, int level);
        void setADSR(int channel, int op, int attack, int decay, int sustain, int release);
        void keyOn(int channel, uint16_t freq);
        void keyOff(int channel);
    private:
        uint16_t _ioBase;
    
};
#endif
