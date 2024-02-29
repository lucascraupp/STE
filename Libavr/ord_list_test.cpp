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

List<char, true, int, true> ord_list;

int main()
{
    setup();

    ord_list.insert('c', 5);
    ord_list.insert('b', 3);
    ord_list.insert('d', 7);
    ord_list.insert('a', 1);

    while (ord_list.size() > 0)
    {
        char buf[16];
        for (int i = 0; i < ord_list.size(); i++)
        {
            sprintf(buf, "Item %d: %c, %d\n", i, ord_list.get(i), ord_list.get_rank(i));
            uart.puts(buf);
        }

        char rem = ord_list.remove_tail();
        sprintf(buf, "Removido: %c\n", rem);
        uart.puts(buf);

        for (int i = 0; i < ord_list.size(); i++)
        {
            sprintf(buf, "Item %d: %c, %d\n", i, ord_list.get(i), ord_list.get_rank(i));
            uart.puts(buf);
        }

        rem = ord_list.remove_head();
        sprintf(buf, "Removido: %c\n", rem);
        uart.puts(buf);

        for (int i = 0; i < ord_list.size(); i++)
        {
            sprintf(buf, "Item %d: %c, %d\n", i, ord_list.get(i), ord_list.get_rank(i));
            uart.puts(buf);
        }
    }

    while (1)
        ;
}
