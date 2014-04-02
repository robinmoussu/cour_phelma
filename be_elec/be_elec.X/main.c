/* 
 * File:   main.c
 * Author: robin
 *
 * Created on 23 mars 2014, 14:57
 */

#include <p18cxxx.h>
#include <GenericTypeDefs.h>


void SysInit(void);

/*
 * 
 */
void main(void) {
    SysInit();

    PORTBbits.RB1 = 1;

    while(1) {
        ;
    }
}

void SysInit(void)
{
  TRISA = 0xFF;                        // All PortA pins as inputs
  TRISB = 0x01;
  TRISC = 0xBB;
  TRISD = 0x00;
  TRISE = 0xFF;

  LATA = 0x00;
  LATB = 0x00;
  LATC = 0x80;

//*****************************************************************************
// Analog Select; Analog = 1; Digital = 0;
//*****************************************************************************
//  ANSELA = 0x01;
//  ANSELB = 0x00;
//  ANSELCbits.ANSC3 = 0;			// <-- Used In I2C. SCL
//  ANSELCbits.ANSC4 = 0;			// <-- Used In I2C. SDA
//  ANSELD = 0x00;
//  ANSELE = 0x00;

// PLL is disabled; 4 MHz; Clock determined by FOSC in Config Word 1.
//  OSCCON = SYS_OSC;                 	             // Set Internal RC to X MHz

//*****************************************************************************
// Timer and Interrupts
//*****************************************************************************

/*************** default clock on 16F1937 is 500 KHz at startup ***************/

// All weak pull-ups are disabled; Interrupt on rising edge of RB0/INT pin;
// Internal Instruction Cycle clock (FOSC/4);
// Increment on high-to-low Transition on RA4/T0CKl pin; Prescaler is assigned
// to TMR0; Prescaller is set to: 1:256.

//    T0CON = TIMER0;						// Configure TMR0 for 4 mS increment
//
//    // Set up Interrupts for timer		// Set up timer itself
//    TMR0H = CLEAR;                      	// Clear timer - always write upper byte first
//    TMR0L = CLEAR;							// Clear Timer - lower bits
//	INTCONbits.TMR0IF = CLEAR;				// Timer 0 Interrupt Flag
//    INTCONbits.TMR0IE = ENABLE;				// Timer 0 Interrupt Enabled
//
//    // Set up switch interrupt on INT0
//    INTCON2bits.INTEDG0 = CLEAR;    	// Interrupt on falling edge of INT0 (switch pressed)
//    INTCONbits.INT0IF = CLEAR;      	// Ensure flag is cleared
//    INTCONbits.INT0IE = ENABLE;      		// Enable INT0 interrupt
//    // NOTE: INT0 is ALWAYS a high priority interrupt
//
//    // Set up global interrupts
//	RCONbits.IPEN	= ENABLE;				// Enable priority levels on interrupts
//    INTCONbits.GIEL = ENABLE;        		// Peripheral Interrupt enable
//    INTCONbits.GIEH = ENABLE;        		// General Interrupt enable
//
//    // Interrupt Priority
//    INTCON2bits.TMR0IP = CLEAR;             // Timer0 is low priority interrupt
//	IPR1bits.RC1IP	= CLEAR;				// EUSART1 Receive Interrupt Priority bit
//	IPR1bits.TX1IP	= CLEAR;				// EUSART1 Transmit Interrupt Priority bit
//
////*****************************************************************************
//// Initial Conditions
////*****************************************************************************
//
//  VOLTInit();            // Go Initialize ADC Module For Voltmeter Functionality
//  RTCInit();			 // Go Initialize the clock
//  LCDInit();			 // Go Initialize the LCD
//  //I2CInit();             // Go Initialize Temp Sensor Interface
//  SNDInit();             // Go Initilize the sound module
//  ButtonsInit();         // Go initilize the Buttons module for input operations

#ifdef SERIAL_COM		 // If Serial Com is being used do action; else skip
  SERInit();			 // Initialized Serieal Come
  SERTxSave('\r');		 // Carriage return
  SERTxSave('\n');		 // Line Feed
  SERSendNext();  		 // Go send next available character To initialize Transmission
#endif
}
