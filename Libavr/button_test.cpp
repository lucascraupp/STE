#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "event_queue.h"

#include <avr/interrupt.h>
#include <stdio.h>

void button_pressed();

GPIO led(13, GPIO::OUTPUT);
GPIO button(3, GPIO::INTERRUPT_RISING, button_pressed);
UART uart;
ADC_Channel adc0(0);
ADC_Channel adc1(1);
Timer timer(1000);

volatile bool state;
Ticks ticks_1s;

EventQueue<16> equeue;
Event buttonEvent;

void button_pressed()
{
    state = 1;
    buttonEvent.args = (void *)2;
    equeue.push(&buttonEvent);
}

void handleButtonEvent(void *arg)
{
    int button_number = (int)arg;

    char buff[16];
    sprintf(buff, "Botão %d\n", button_number);
    uart.sync_puts(buff);
}

void loop()
{
    equeue.run();
}

void setup()
{
    buttonEvent.func = handleButtonEvent;
    sei();
    uart.puts("Setup\n");
    state = 0;
    ticks_1s = timer.ms_to_ticks(1000);
}

// void loop()
// {
//     // char buf[32];

//     // led.write(state);
//     // if (button.read() == 1)
//     //     uart.puts("Button\n");

//     // while (uart.available() > 0)
//     // {
//     //     char c = uart.get() + 1;

//     //     sprintf(buf, "O valor incrementado é: %c\n", c);
//     //     uart.puts(buf);
//     // }

//     // _delay_ms(10000);
//     // adc0.start();
//     // sprintf(buf, "O valor lido do adc0 é: %d\n", adc0.get());
//     // uart.puts(buf);
//     // adc0.stop();

//     // _delay_ms(10000);
//     // adc1.start();
//     // sprintf(buf, "O valor lido do adc1 é: %d\n", adc1.get());
//     // uart.puts(buf);
//     // adc1.stop();

//     timer.delay(ticks_1s);
//     uart.sync_put('\n');

//     // int tks;
//     // if ((tks = timer.get_ticks()) % 1000 == 0)
//     // {
//     //     // sprintf(buf, "O valor de ticks é: %u\n", tks);
//     //     // uart.puts(buf);
//     //     uart.sync_put('\n');
//     // }
// }

int main()
{
    setup();
    while (true)
        loop();
}
