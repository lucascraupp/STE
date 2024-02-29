#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__

#include "fifo.h"
#include <avr/interrupt.h>
#include "event.h"

template <int FSIZE>
class EventQueue
{
private:
    Fifo<Event *, FSIZE> events;

public:
    EventQueue() {}
    ~EventQueue() {}

    void push(Event *e)
    {
        cli();
        events.push(e);
        sei();
    }

    void run()
    {
        Event *e;
        while (events.size() > 0)
        {
            cli();
            e = events.pop();
            sei();
            e->func(e->args);
        }
    }
};

#endif
