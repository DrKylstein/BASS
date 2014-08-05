#include <dos.h>
#include <conio.h>
#include "Timer.hpp"


#define TIMER_PULSE 0x0012305E
#define TIMER_HZ SECOND
#define TIMER_DIVISOR TIMER_PULSE / TIMER_HZ
#define BIOS_DIVISOR 0x10000
#define BIOS_STEP BIOS_DIVISOR / TIMER_DIVISOR

static interrupts::isr_ptr Timer::_prev_int_8 = 0;
static void (__far* Timer::_task)() = 0;
static volatile Timer::tics_t Timer::_count = 0;
static volatile Timer::tics_t Timer::_lastBiosCount = 0;


Timer::Timer(): _nextCount(0) {
    interrupts::atomic lock;
    _prev_int_8 = _dos_getvect(8);
    _dos_setvect(8, _timer_int);
    //set a more precise interval
    outp(0x43, 0x36);
    outp(0x40, TIMER_DIVISOR & 0xFF);
    outp(0x40, TIMER_DIVISOR >> 8);
}
Timer::~Timer() {
    interrupts::atomic lock;
    //reset interval, 0x0000 = 0x10000
    outp(0x43, 0x36);
    outp(0x40, 0);
    outp(0x40, 0);
    _dos_setvect(8, _prev_int_8);
}
static void __interrupt __far Timer::_timer_int() {
    _count++;
    if(_task != 0) {
        _task();
    }
    if(_count > _lastBiosCount + BIOS_STEP) {
        _chain_intr(_prev_int_8);
        _lastBiosCount = _count;
    } else {
        //notify Programmable Interrupt Controller that we've finished
        outp(0x20, 0x20);
    }
}
void Timer::throttle(int fps) {
    tics_t newCount;
    do {
        interrupts::atomic lock;
        newCount = _count;
    } while(newCount < _nextCount);
    
    long int period = TIMER_HZ / fps;
    _nextCount = newCount + period;
}
void Timer::setTask(void (__far* task)()) {
    _task = task;
}
Timer::tics_t Timer::getTics() {
    interrupts::atomic lock;
    return _count;
}
