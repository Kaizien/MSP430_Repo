/*
 *  Code Written by Grant Hinkle -- basic reference code examples for the MSP430 Launchpad line of boards from TI. Board used for this example: MSP430FR4133
 *
 *  This code is very basic and just used as a reference for utilizing the GPIO interrupts. When you press button 1 (pin 1.2) the LED on the device will toggle
 *  the state of LED1 between High and Low (pin 1.0)
 *
 */

#include <msp430fr4133.h>


/*
 *  This routine is used to toggle the state of Pin 1.0 in this "Port 1 interrupt service routine"
 *  This routine will be called every time the state of an interrupt enabled P1 bin changes from high to low. (the button associated with P1.3 on the MSP430FR4133 board is an active-low)
 */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^=  BIT0;  // Toggle P1.0 but XOR'ing the current state of the pin
    P1IFG &= ~BIT2; // P1.2 interrupt flag cleared/set back to 0
}


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;               // Disable the GPIO power-on default high-impedance mode to activate previously configured port settings

	P1DIR |= (BIT0 | BIT2);     // set pin1.0 to an output and since we used the OR bitwise operator, we also set P1.2 (our interrupt pin) to an input. (Also all the other bits in the register to 0/input (P1.1, P1.2, P1.4-P1.7)
	                            // Since this is the case, we don't need to set P1.2 to an input using P1 |= BIT2;
	                            // if we wanted to set P1.0 and P1.2 direction at the same time, you could use P1DIR |= (BIT0 | BIT2) which would set both pins to outputs

    //P1OUT |= BIT2;            //P1OUT |= 0x04;   Sets P1.2 to an output -- this line isnt necessary since we already set P1.2 to an output in the previous statement
	P1OUT &= ~BIT0;             // Sets P1.0 to low/off

	P1REN |= BIT2;              //P1REN |= 0x04;   This turns on the pullup resistor on pin1.2


	P1IE  |= BIT2;              // P1.2 interrupt enabled
	P1IES |= BIT2;
	P1IFG &= ~BIT2;             // P1.2 interrupt flag cleared --- used an AND operator with an inverted value of the current state of the bit always sets the pin state to 0/LOW

	__bis_SR_register(GIE);     // Enable all interrupts  -- this is a built in function that enables all the interrupts by setting the GIE (Global Interrupt Enable) bit in the status register of the MSP430FR4133. This function can
	                            // also be used to enter low-power modes



	//forever loop
	for(;;)
	{

	}



	return 0;
}



