## Lab6 Open Loop Systems - Ardit Pranvoku and Thai Nghiem

### Overview
The purpose of the lab was to control a fan using pulse width modulation based on the input of a temperature sensor. The temperature sensor we used was an LM35. We used a 5v voltage regulator to regulate a 20 volt voltage down to 5 volts. Doing so causes the 5v volt regulator to heat up, which then dissipates heat from its heat sink. Due to the close proximity of the temperature sensor, it also heats up.

Based on the heat sensed by the LM35, it will output voltage using a scale of 10mV/C. It is powered directly from the voltage supplied by the voltage regulator, while simultaneously using the heat from the heat sink to control its output. 

The output of the LM35 is input into the MSP430. The MSP430 will convert the digital value of the voltage to an analog value using its 12 bit ADC. Using the analog output from the ADC, a PWM signal is generated. We will go into more detail about this in the code below. The PWM signal from the MSP430 is output into a TL072, amplified 21x, and finally is used to control a fan. 

### Code

The code starts off by intializing the ADC. 
```c
  ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Designates sampling time, uses ADC12
  ADC12CTL1 = ADC12SHP;                     // Using ADC12 pulse mode
  ADC12IE = 0x01;                           // Enable interrupt
  ADC12CTL0 |= ADC12ENC;					// Enable conversion
```
After, we designate the proper pins as outputs and inputs, specifically P6.0 as the input from the temperature sensor. We also set the timer up for the PWM.
```c
  P1DIR |= 0x01;                            // Sets P1.0 as output
  P1DIR |= BIT2;							// Sets P1.2 as output.
  P1SEL |= BIT2;							// Sets P1.2 as GPIO.
  P6SEL |= 0x01;                            // Sets P6.0 as ADC input.
  
  TA0CCR0 = 4500;
  TA0CCTL1 = OUTMOD_7;						// Sets TA0CCR0 to set, sets TA0CCR1 to reset.
  TA0CTL = TASSEL_2 + MC_1 + TACLR;			// Uses SMCLK, UPMODE, and clears TA.
```
The main loop for the program is used as the ADC waits for an incoming voltage to generate an interrupt and begin conversion.
```c
while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    __bis_SR_register(LPM0_bits + GIE);     // LPM0, ADC12_ISR will force exit
    __no_operation();                       // For debugger
  }
}
```

After conversion is complete, we take the new value stored in ADC12MEM0 and save it to 
TA0CCR1.
```c
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0

        TA0CCR1 = ADC12MEM0; //Sets TA0CCR1 to digital value; changes duty cycle.

    __bic_SR_register_on_exit(LPM0_bits);   // Exit active CPU
  default: break;
  }
}
```
This will change the duty cycle of the PWM, so that as temperature increases, the duty cycle will also increase. As the duty cycle increases, the fan will run faster, providing greater airflow to the LM35 and decreasing its temperature.


### LM35 Temperature Sensor

Below is the output voltage from the LM35. Over a period of 50 seconds, the voltage increases by around 50 mV, or 5 degrees celcius. It increased from 220 mV to 270 mV. </br> 

![slope](https://user-images.githubusercontent.com/14367479/32695403-8d5ab9d0-c728-11e7-8368-4f664b387207.JPG)

### Breadboard

Our breadboard configuration is shown below </br>

![fancontrol_board](https://user-images.githubusercontent.com/14367479/32695446-637e9b52-c72a-11e7-833a-5a14deec7a50.JPG)

The lightbulb is used to test the output of our PWM to troubleshoot.

### Schematic

Somethings not covered in the overview is the 100 Ohm resistor located right after the voltage regulator. This is used to dissipate power. The OP amp is used as a noninverting amplifier. The 100k resistor and the 5k resistor result in a gain of (100/5)+1, or 21x. This is because the signal coming out of the MSP430 PWM is not strong enough to drive the fan, and must be amplified. 
</br>
![fancontrol](https://user-images.githubusercontent.com/14367479/32695454-98d61cf8-c72a-11e7-9941-7654398765ab.png)





