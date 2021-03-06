#include <msp430fr4133.h>
int main(void)
{
 WDTCTL = WDTPW + WDTHOLD;           // Stop Watchdog Timer. This line of code is needed at the beginning of most MSP430 projects
                                     //This turns off the watchdog timer, which can reset the device after a certain period of time
                                     // Configure GPIO
 P4DIR |= 0x01;                      // P4DIR is a register that configures the direction (DIR) or a port pin as an output or an input
                                     // To set a specific pin as output or input, we write a '1' or '0' on the appropriate bit of the register.
                                     // P4DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>
                                     // Since we want to blink the LED2, we want to set the direction of Port 4, Pin 0 (P4.0) as an output
                                     // We do that by writing a 1 on the PIN0 bit of the P4DIR register

                                     // P4DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>

                                     // P4DIR = 0000 0001

                                     // P4DIR = 0x01 <-- this is the hexadecimal conversion of 0000 0001

                                     // The OR command (|) will always SET A BIT

                                     // P4DIR|= 0x01 is equivalent to P4DIR = P4DIR | 0x01
                                     // Regardless of value in P4DIR, this OR operation will set Bit0 (or Pin0) to 1-> (1|0 = 1, 1|1 = 1)

 P1DIR |= 0x01 ;                     // P1DIR register is configured to be an output! Pin P1.0 controls LED01 (P4.0 controlled LED02)


 PM5CTL0 &= ~LOCKLPM5;               // Disable the GPIO power-on default high-impedance mode to activate previously configured port settings

 P1OUT = 0x00;                       // These two lines set the state of the P4.0 and P1.0 to LOW. We alternatively can set both to HIGH by using 0x01. We do this
                                     // so that both LED's are in the same state before we start our loops below. (i.e. so both led's are either both on or off at the
                                     // same time. This was just preference and doesn't matter at all in the testing of our board/led(s)
 P4OUT = 0x00;

 while(1)                            // This while(1) loop will cause the lines of code inside it to loop infinitely
 {
     P4OUT ^= 0x01;                  // Toggle P4.0 using exclusive-OR operation (^=)
                                     // P4OUT is another register which holds the status of the LED.
                                     // '1' specifies that it's ON or HIGH, while '0' specifies that it's OFF or LOW
                                     // Since our LED is tied to P4.0, we will toggle the 0 bit of the P4OUT register
                                     // The exclusive-OR command (^) will always toggle a bit at a certain position
                                     // P4OUT^= 0x01 is equivalent to P4DIR = P4DIR ^ 0x01
                                     // Regardless of value in P4OUT, this OR operation will toggle Bit0 (or Pin0) (1^0 = 1, 1^1 = 0)

     P1OUT ^= 0x01;                  //this will toggle led01 --- exactly the same as above with LED02 using P4OUT

     __delay_cycles(1000000);        //in old versions of my code, I would use " for(i=0; i<10000000;i++)
 }
}
