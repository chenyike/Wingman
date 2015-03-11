//
//  Settings.c
//  Speakers
//
//  Created by Francisco de Villalobos on 10/6/13.
//  Copyright (c) 2013 Francisco de Villalobos. All rights reserved.
//

#include <stdio.h>
#include "m_general.h"
#include "m_bus.h"
#include "m_rf.h"
#include "m_usb.h"


void init(void){
    m_clockdivide(0);

    
/******************************************************************************************/
/*****************                    Initialization                      *****************/
/******************************************************************************************/
    
    m_clockdivide(0);                   // 16MHz
    m_disableJTAG();                    // Disable JTAG.
    
    m_bus_init();
	m_usb_init();                       // Initialize the USB connection.
    
    sei();                              // Enable Interrupts
    
    
    
/******************************************************************************************/
// Define Timer 1 Settings
// Master Motors Velocity Control
// 10 Hz Timer
    
    // Define Prescaler as 1024.
    clear(TCCR1B, CS12);
    set(TCCR1B, CS11);
    set(TCCR1B, CS10);
    
    // Set Mode 15: UP to OCR1A, PWN Mode.
    set(TCCR1B, WGM13);
    set(TCCR1B, WGM12);
    set(TCCR1A, WGM11);
    set(TCCR1A, WGM10);
    
    // No change on OC1A, to B5.
    clear(TCCR1A, COM1A1);
    clear(TCCR1A, COM1A0);
    
    // Clear at OCR1B, set at rollover. B6.
    set(TCCR1A, COM1B1);
    clear(TCCR1A, COM1B0);
    
    // Toggle Mode on OC1C, which is multiplexed to B7
    set(DDRB, 7);
    clear(TCCR1A, COM1C1);
    clear(TCCR1A, COM1C0);
    
    // Set the OCR1A.
    OCR1A = 15625;  //15625
    OCR1C = 5000;
    
    // Set the OCR1A, OCR1B and OCR1C.
    OCR1A = 15625;  //15625
    OCR1B = 10000;
    OCR1C = 5000;
    
    // Enable Timer 1 Interrupt(s)
    set(TIMSK1, TOIE1);
    
/******************************************************************************************/
// Define Timer 3 Settings
// Servo Control Timer.
// From 1.5ms to 1.55ms. 10 Hz Timer
    
    // Define Prescaler as /1024.
	set(TCCR3B,CS32);
	clear(TCCR3B,CS31);
	set(TCCR3B,CS30);
    
    // Set Mode 14: UP to ICR3
	set(TCCR3B,WGM33);
	set(TCCR3B,WGM32);
    set(TCCR3A,WGM31);
	clear(TCCR3A,WGM30);
    
    // No change at OC3A, clear at rollover which is multiplexed to C6
    clear(TCCR3A,COM3A1);
    clear(TCCR3A,COM3A0);

    OCR3A = 156;
    ICR3  = 156;
//    ICR3H = 0x9C;
//    ICR3L = 0x40;
//    OCR3AH = 0x90;
//    OCR3AL = 0x09;
    
    // Enable Interrupt at Rollover
    set(TIMSK3, TOIE3);
    
    
/******************************************************************************************/
// Define Timer 4 Settings
// We are going to use Timer 4 (10-bit) as the PWM modulated signal to generate
// the velocity control of the Slave Motors (To Enable pin on h-bridge).
    
	// Define Prescaler as /4.
	clear(TCCR4B,CS43);
	clear(TCCR4B,CS42);
	set(TCCR4B,CS41);
	set(TCCR4B,CS40);
	
	// Set Mode 15: UP to OCR4C = 0x00FF, reset to 0x0000
	clear(TCCR4D,WGM41);
	clear(TCCR4D,WGM40);
	
	//Set the timer ceiling to 0xFF (8-bit mode), H-byte then L-byte
//    cli();
	//TC4H  = 0x03; //HB of 10-bit mode
	OCR4C = 0xFF;
	
	//Use output compares to generate PWM
	//Compare Output OC4A in C7.
    // DISCONECTED NOW!!!!
    clear(TCCR4A, PWM4A);
	clear(TCCR4C, COM4A1);
	clear(TCCR4C, COM4A0);
	
	//Use output compares to generate PWM
	//Disconnect Output B6.
    clear(TCCR4A, PWM4B);
	clear(TCCR4A, COM4B1);
	clear(TCCR4A, COM4B0);
	
	//Use output compares to generate PWM
	//Output D. D7. DISCONNECTED
    clear(TCCR4C, PWM4D);
	clear(TCCR4C, COM4D1);
	clear(TCCR4C, COM4D0);
    
    OCR4A = OCR4C / 4;
	OCR4D = OCR4C / 4;
    
    

/******************************************************************************************/
    // Timer 0 for mili seconds
    
    // 1024 Prescaler   ------> 16000000 / 1024 = 15625 counts/sec
//    set(TCCR0B, CS02);
//    clear(TCCR0B, CS01);
//    set(TCCR0B, CS00);
//    
//    // UP to OCR0A
//    set(TCCR0B, WGM02);
//    clear(TCCR0A, WGM01);
//    clear(TCCR0A, WGM00);
//    OCR0A = 156;         // 156counts / 15.625counts/s =~ 0.01s = 10ms
//    
//    // No Change Pin B7
//    clear(TCCR0A, COM0A1);
//    clear(TCCR0A, COM0A0);
//    
//    // Enable OverFlow Interrupt
//    set(TIMSK0, OCIE0A);
    
    
/******************************************************************************************/
//ADC Initialization
    
//    //Vcc Voltage Reference
//    clear(ADMUX,REFS1);
//    set(ADMUX,REFS0);
//    
//    //ADC Prescaler (Keep between 50 and 200kHz)
//    // = /128
//    set(ADCSRA,ADPS2);
//    set(ADCSRA,ADPS1);
//    set(ADCSRA,ADPS0);
//    
//    //Disable digital inputs for ADC use.
//    set(DIDR0,ADC0D);       // F0
//    set(DIDR0,ADC1D);       // F1
//    set(DIDR0,ADC4D);       // F4
//    set(DIDR0,ADC5D);       // F5
//    set(DIDR0,ADC6D);       // F6
//    set(DIDR0,ADC7D);       // F7
//    
//    //Enable Auto-Conversion
//    set(ADCSRA,ADATE);
//    
//    //Disable ADC Subsystem.
//    clear(ADCSRA,ADEN);
//    //Connect F0 to the ADC Unit.
//    clear(ADCSRB,MUX5);
//    clear(ADMUX,MUX2);
//    clear(ADMUX,MUX1);
//    clear(ADMUX,MUX0);
//    
//    //Enable ADC Subsystem
//    set(ADCSRA,ADEN);
//    
//    //Start Conversion (Only 1 time needed to start because of Auto-Conversion)
//    set(ADCSRA,ADSC);
//    
//    // ACD Variable Returns Conversion from 0 to 1023.
    
}