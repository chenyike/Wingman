/* Name: main.c
 * Author: Ecko
 * Copyright: Ecko
 * License: Ecko
 */


#include <avr/interrupt.h>
#include <avr/io.h>
#include "math.h"
#include "m_usb.h"
#include "m_general.h"
#include "m_bus.h"
#include "m_rf.h"

#define CLOCK_FREQ 16000000 //Hz

#define CHANNEL 1
#define RXADDRESS 0x11
#define TXADDRESS 0x01
#define PACKET_LENGTH 1

volatile long timer0_ticks = 0;
volatile float trigle = 0;
volatile char buffer[PACKET_LENGTH];
volatile char send_buffer[PACKET_LENGTH];

void initializeTimers(void)
{
    clear(TCCR0B,WGM02); //Set Timer 0 to run up to OxFF
    clear(TCCR0A,WGM01);
    clear(TCCR0A,WGM00);
    
    set(TIMSK0,TOIE0); //Interrupt on overflow
    
    clear(TCCR0B,CS02); //Stop for now 
    clear(TCCR0B, CS01);
    clear(TCCR0B, CS00);
}

void start_timer(void)
{
    set(TCCR0B,CS02); //Start running at 1024
    clear(TCCR0B, CS01);
    set(TCCR0B, CS00);
}

void stop_timer(void)
{
    clear(TCCR0B,CS02); 
    clear(TCCR0B, CS01);
    clear(TCCR0B, CS00);
}


int main(void)
{
    m_clockdivide(0);
    sei();
    m_usb_init();

    m_bus_init();
    m_rf_open(CHANNEL,RXADDRESS,PACKET_LENGTH);

    initializeTimers();

    clear(DDRD,3);   //set D3 as input
    set(DDRD,4);   // set D4 as output
    

    while (1)
    {
        trigle = check(PIND,3);    //get the reading from D3

        
        switch((int)buffer[0])
        {
            case 1:
            set(PORTD,4);
            break;

            case 0:
            clear(PORTD,4);
            break;
        }
        


        if ((int)trigle == 1 )   // if the botton's been pressed
        { 
            char send_buffer[PACKET_LENGTH] = {trigle};
            m_usb_tx_int((int)send_buffer[0]); m_usb_tx_string(" ");
            m_wait(33);
            m_rf_send(TXADDRESS,send_buffer,PACKET_LENGTH);

        }

        else if ((int)trigle == 0 )
        {
            char send_buffer[PACKET_LENGTH] = {trigle};
            m_usb_tx_int((int)send_buffer[0]); m_usb_tx_string(" ");
            m_wait(33);
            m_rf_send(TXADDRESS,send_buffer,PACKET_LENGTH);
        }

    }
}


ISR(TIMER0_OVF_vect)
{
    timer0_ticks += 1;
}


ISR(INT2_vect)
{
    m_rf_read(buffer,PACKET_LENGTH);
    m_usb_tx_int((int)buffer[0]); m_usb_tx_string("\n");
    m_green(TOGGLE);
}



