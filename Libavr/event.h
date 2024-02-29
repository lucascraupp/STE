#ifndef __EVENT_H__
#define __EVENT_H__

#include "timer.h"

typedef void (*EventFuncPtr_t)(void *);
struct Event
{
    EventFuncPtr_t func;
    void *args;
    Microseconds realease_time;
    Microseconds deadline;
};

#endif