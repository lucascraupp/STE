#ifndef __EVENT_LIST_H__
#define __EVENT_LIST_H__

#include "list.h"
#include "event.h"
#include <avr/interrupt.h>
#include "uart.h"
#include "timer.h"

class EventList
{
public:
    virtual ~EventList() {}
    virtual void pushEvent(Event *e) {}
    virtual void run() {}
};

class EventListPriotiry : public EventList
{
private:
    List<Event *, true> list;

public:
    virtual ~EventListPriotiry() {}

    virtual void pushEvent(Event *e)
    {
        cli();
        list.insert(e);
        sei();
    }

    virtual void run()
    {
        Event *e;
        while (list.size() > 0)
        {
            cli();
            e = list.remove_head();
            sei();
            e->func(e->args);
        }
    }
};

class EventListFIFO : public EventList
{
private:
    List<Event *> list;

public:
    virtual ~EventListFIFO() {}

    virtual void pushEvent(Event *e)
    {
        cli();
        list.insert(e);
        sei();
    }

    virtual void run()
    {
        Event *e;
        while (list.size() > 0)
        {
            cli();
            e = list.remove_head();
            sei();
            e->func(e->args);
        }
    }
};

#endif