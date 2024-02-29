#ifndef __EVENTSCHEDULE_H__
#define __EVENTSCHEDULE_H__

#include "list.h"
#include "event.h"
#include "event_list.h"
#include "observer.h"

class EventSchedule : public Observer<Microseconds>
{
private:
    List<Event *, true, Microseconds, true> events;
    EventList *elist;

public:
    EventSchedule(EventList *el) : elist(el) {}
    ~EventSchedule() {}

    void schedule_event(Event *e)
    {
        if (e->deadline == 0)
        {
            events.insert_ordered(e, e->realease_time);
        }
        else
            events.insert_ordered(e, e->deadline);
    }

    void update(Microseconds v)
    {
        Microseconds updated = events.update_head_rank(v);

        if (updated <= 0)
        {
            Event *e = events.remove_head();
            elist->pushEvent(e);
        }
    }
};

#endif