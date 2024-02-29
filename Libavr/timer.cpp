#include "timer.h"
#include <avr/io.h>
#include "avr/interrupt.h"

Timer *Timer::current_timer = 0;

Timer::Timer(Microseconds tl)
    : tick_lenght(tl), ticks(0)
{
    unsigned char prescaler = 5;
    int pulse_count = 256;

    switch (tl)
    {
    case 100:
        prescaler = 3; // div_64
        pulse_count = 25;
        break;

    case 500:
        prescaler = 3; // div_64
        pulse_count = 125;
        break;

    case 1000:
        prescaler = 3; // div_64
        pulse_count = 250;
        break;

    case 2000:
        prescaler = 4; // div_256
        pulse_count = 250;
        break;

    case 4000:
        prescaler = 5; // div_1024
        pulse_count = 250;
        break;

    case 8000:
        prescaler = 5; // div_1024
        pulse_count = 125;
        break;

    case 9984:
        prescaler = 5; // div_1024
        pulse_count = 156;

    case 16000:
        prescaler = 5; // div_1024
        pulse_count = 250;
        break;

    default:
        prescaler = 5; // div_1024
        pulse_count = 256;
        tick_lenght = 16384;
        break;
    }

    TCCR0A = (unsigned char)0;
    TCCR0B = (unsigned char)(prescaler & 0x07);
    TIMSK0 = (unsigned char)(1 << TOIE0);

    tcnt_base = 0xff - pulse_count + 1;
    TCNT0 = tcnt_base;

    current_timer = this;
}

Timer::~Timer()
{
}

Ticks Timer::get_ticks()
{
    return ticks;
}

Microseconds Timer::get_ticks_length()
{
    return tick_lenght;
}

Ticks Timer::ms_to_ticks(Milliseconds ms)
{
    return ms / (get_ticks_length() / 1000);
}

Milliseconds Timer::ticks_to_ms(Ticks tk)
{
    Milliseconds ms = get_ticks_length() / 1000;
    return ms / tk;
}

Ticks Timer::us_to_ticks(Microseconds us)
{
    return us / get_ticks_length();
}

Microseconds Timer::ticks_to_us(Ticks tk)
{
    Microseconds us = get_ticks_length();
    return us / tk;
}

void Timer::delay(Ticks tk)
{
    Ticks end = ticks + tk;
    while (ticks < end)
        ;
}

void Timer::register_observer(Observer<Microseconds> *obs)
{
    this->observers.insert(obs);
}

ISR(TIMER0_OVF_vect)
{
    Timer::current_timer->isr_handler();
}

void Timer::isr_handler()
{
    TCNT0 = tcnt_base;
    ticks++;

    for (int i = 0; i < observers.size(); i++)
    {
        observers.get(i)->update(this->tick_lenght);
    }
}