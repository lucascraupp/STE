#include "adc.h"
#include <avr/io.h>
#include "avr/interrupt.h"
#include "uart.h"

UART teste;

ADC_Channel *ADC_Channel::active_channel;

ADC_Channel::ADC_Channel(int ch) : channel(ch)
{
    ADMUX &= 0xF0;

    ADMUX |= (1 << REFS0) | (ch & 0x0f);

    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

ADC_Channel::~ADC_Channel()
{
}

int ADC_Channel::sample()
{
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC))
        ;

    return ADC;
}

void ADC_Channel::start()
{
    active_channel = this;

    ADMUX &= 0xF0;
    ADMUX |= (1 << REFS0) | (channel & 0x0F);
    ADCSRA |= (1 << ADIE) | (1 << ADEN) | (1 << ADSC);
}

void ADC_Channel::stop()
{
    ADCSRA &= ~(1 << ADEN);
}

int ADC_Channel::get()
{
    while (adc_fifo.size() == 0)
        ;

    cli();
    int data = adc_fifo.pop();
    sei();

    return data;
}

ISR(ADC_vect)
{
    ADC_Channel::adc_isr_handler();
}

void ADC_Channel::adc_isr_handler()
{
    active_channel->adc_fifo.push(ADC);
}