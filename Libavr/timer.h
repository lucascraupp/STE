#ifndef __TIMER_H__
#define __TIMER_H__

#include "observer.h"
#include "list.h"

typedef unsigned long long Ticks;
typedef Ticks Microseconds;
typedef Ticks Milliseconds;

class Timer
{
private:
    Microseconds tick_lenght;
    Ticks ticks;
    unsigned char tcnt_base;

    List<Observer<Microseconds> *> observers;

public:
    static Timer *current_timer;

    Timer(Microseconds tl);
    ~Timer();

    Ticks get_ticks();
    Microseconds get_ticks_length();

    Ticks ms_to_ticks(Milliseconds ms);
    Milliseconds ticks_to_ms(Ticks tk);

    Ticks us_to_ticks(Microseconds us);
    Microseconds ticks_to_us(Ticks tk);

    void delay(Ticks tk); // busy wait

    void register_observer(Observer<Microseconds> *obs);

    void isr_handler();
};

#endif