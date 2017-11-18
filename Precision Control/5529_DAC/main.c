//  MSP430FR5994 MileStone
//      Communication using UART
//
//   Description:
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO~1MHz
//
//                MSP430FR2311
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P6.0|<--Sensors
//
//   Thai Nghiem and Ardit Pranvoku
//   Rowan University
//   September 2017
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430.h> 

unsigned int adc_value =0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //Configure the port to be used as ADC input

    P1DIR = BIT2 + BIT3 + BIT4 + BIT5;
    P1OUT &= ~(BIT2 + BIT3 + BIT4 + BIT5);

    P2DIR = BIT4 + BIT5;
    P2OUT &= ~(BIT4 + BIT5);

    P4DIR = BIT0 + BIT3;
    P4OUT &= ~(BIT0 + BIT3);

    P3SEL |= BIT3;          // UART TX
    P3SEL |= BIT4;          // UART RX
    UCA0CTL1 |= UCSWRST;    // Resets state machine
    UCA0CTL1 |= UCSSEL_2;   // SMCLK
    UCA0BR0 = 6;            // 9600 Baud Rate
    UCA0BR1 = 0;            // 9600 Baud Rate
    UCA0MCTL |= UCBRS_0;    // Modulation
    UCA0MCTL |= UCBRF_13;   // Modulation
    UCA0MCTL |= UCOS16;     // Modulation
    UCA0CTL1 &= ~UCSWRST;   // Initializes the state machine
    UCA0IE |= UCRXIE;


    __bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
    __no_operation(); // For debugger
}

// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{

    while (!(UCA0IFG&UCTXIFG)); // USCI_A0 TX buffer ready?

    char characterIN = UCA0RXBUF;
    UCA0TXBUF = UCA0RXBUF;
    int output[8];
    int i;
    for (i = 0; i < 8; i++) {
        output[i] = (characterIN >> i) & 1;
    }
    if(output[0] == 1){
        P1OUT |= BIT2;
    }
    else{
        P1OUT &= ~BIT2;
    }
    if(output[1] == 1){
        P1OUT |= BIT3;
    }
    else{
        P1OUT &= ~BIT3;
    }
    if(output[2] == 1){
        P1OUT |= BIT4;
    }
    else{
        P1OUT &= ~BIT4;
    }
    if(output[3] == 1){
        P1OUT |= BIT5;
    }
    else{
        P1OUT &= ~BIT5;
    }
    if(output[4] == 1){
        P2OUT |= BIT4;
    }
    else{
        P2OUT &= ~BIT4;
    }
    if(output[5] == 1){
        P2OUT |= BIT5;
    }
    else{
        P2OUT &= ~BIT5;
    }
    if(output[6] == 1){
        P4OUT |= BIT0;
    }
    else{
        P4OUT &= ~BIT0;
    }
    if(output[7] == 1){
        P4OUT |= BIT3;
    }
    else{
        P4OUT &= ~BIT3;
    }




}

