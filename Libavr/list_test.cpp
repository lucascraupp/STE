#include "uart.h"
#include <avr/interrupt.h>
#include <stdio.h>

#include "list.h"

UART uart;

void setup()
{
    sei();
    uart.puts("Setup\n");
}

List<int> ord_list;

int main()
{
    setup();

    ord_list.insert_tail(5);
    ord_list.insert_tail(3);
    ord_list.insert_tail(564);
    ord_list.insert_tail(-654);

    char buf[16];
    for (int i = 0; i < ord_list.size(); i++)
    {
        sprintf(buf, "Item %d: %d\n", i, ord_list.get(i));
        uart.puts(buf);
    }

    int rem = ord_list.remove_tail();
    sprintf(buf, "Removido: %d\n", rem);
    uart.puts(buf);

    for (int i = 0; i < ord_list.size(); i++)
    {
        sprintf(buf, "Item %d: %d\n", i, ord_list.get(i));
        uart.puts(buf);
    }

    rem = ord_list.remove_head();
    sprintf(buf, "Removido: %d\n", rem);
    uart.puts(buf);

    for (int i = 0; i < ord_list.size(); i++)
    {
        sprintf(buf, "Item %d: %d\n", i, ord_list.get(i));
        uart.puts(buf);
    }

    while (1)
        ;
}
