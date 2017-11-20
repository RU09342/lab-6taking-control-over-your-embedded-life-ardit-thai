## Lab 6: Ardit Pranvoku and Thai Nghiem <br /> Precision Control

### PWM Part 2

We used a PWM built in CodeComposer to output an AC signal into a TL072 Op-Amp. 
We output the AC signal onto a GPIO pin, and then connected that pin to the input of the Op-Amp.
The circuit we built used the TL072 as a low-pass filter and an integrator, which can be seen below. <br />
![pwe_integrater_circuit](https://user-images.githubusercontent.com/30231031/32421096-bc14f24c-c262-11e7-96e7-5ef9ac55d913.jpg)
![pwm_part2_schem](https://user-images.githubusercontent.com/30231031/32421097-bef9a69c-c262-11e7-81cb-c2f087c3ab1a.png)
<br />
We did this by changing TA0CCR0 and TA0CCR1, and having a button control it. 
Because we always kept TA0CCR0 and TA0CCR1 at a 2:1 ratio, we were able to maintain the 50% duty cycle while changing the frequency. 
We measured the cut off frequency of our Op - Amp to be 10kHz, so we were able to notice differences amongst the differency frequency signals we passed into the Op-Amp. 
For example, at 5kHz there is a conspicuous flattening out of the sawtooth curve before it drops, but this flattening out lessens at 10kHz and disappears at 5kHz. 
<br /> Input: 5kHz <br />
![inpwm5](https://user-images.githubusercontent.com/30231031/32466244-43906574-c314-11e7-81a1-67aca73b1a79.png)
<br /> Output: 5kHz <br />
![inmsp42](https://user-images.githubusercontent.com/30231031/32421114-e9549258-c262-11e7-85eb-8018b35b5894.png)
<br /> Input: 10kHz <br />
![inpwm9](https://user-images.githubusercontent.com/30231031/32466249-47c06040-c314-11e7-9eec-1180f4c720f7.png)
<br /> Output: 10kHz <br />
![inmsp35](https://user-images.githubusercontent.com/30231031/32421113-e94a7f70-c262-11e7-9a40-a13a83416f42.png)
<br /> Input: 20kHz <br />
![inpwm](https://user-images.githubusercontent.com/30231031/32466253-48ea3fae-c314-11e7-9d0b-21ff82744f62.png)
<br /> Output: 20kHz <br />
![inmsp52](https://user-images.githubusercontent.com/30231031/32421115-e95e13a0-c262-11e7-80a8-4a8d82905a88.png)

Overall, the integrator circuit worked successfully, 
as we saw our square wave input be integrated into a sawtooth wave output, which was what we expected.

### R2R DAC
An 8 Bit ladder works by using 8 resistors (In our schematic, this refers to the 10k resistors) to split an incoming voltage coming in by 2 to the power of its place in the binary number, counting from left to right. The resistor closest to the output is controlled by the most significant bit, or the first bit, and splits the voltage by 2^1, contributing half of the total voltage. The resistor farthest from the output is controlled by the least significant bit, or the eighth bit and splits the voltage by 2^8, contributing 1/256 of the total voltage. If the binary input was 1001 0001, the output voltage would be the total voltage*(1/2 + 1/16 + 1/256). 1/2 of the total voltage is being controlled by the first 1, 1/16 of the total voltage is being controlled by the 4th 1, and the final 1/256 of the total voltage is being controlled by the 8th 1. The 0s in the binary number are connected to ground, and contribute nothing.
We built a digital to analog circuit using an 8-bit R2R ladder. <br />
![r2r_dac_schem](https://user-images.githubusercontent.com/30231031/32421233-42895d08-c264-11e7-9c85-8ea193d4f999.png)
<br />
In order to test our circuit, we picked a random number from 0 - 255, and chose 160. (1010 0000) 
We coded the appropriate GPIO pins on the F5529 as outputs if the bit was on, and left them off if the bit was off. 
We then used 8 wires to connect the pins to the breadboard. The voltage on the output was what we accepted as our experimental result. The theoretical output was expected to be 2.07V given an input of 1010 0000 from the MSP430. 
Our results are shown in the table below. <br />
![dac_table](https://user-images.githubusercontent.com/30231031/32421223-1f1b9282-c264-11e7-91cc-7f49cc97738e.png) 
<br />
![dac_reading](https://user-images.githubusercontent.com/30231031/32421228-3885a280-c264-11e7-89cf-c0ba8e49f3db.JPG)
<br />
Below is the circuit we built: <br />
![dac_circuit](https://user-images.githubusercontent.com/30231031/32421247-67fe7a0a-c264-11e7-811a-0dbcc9ba5d17.JPG)
<br />

### Loading Effect
In order to test the effect of a load attached to the output of our integrator, we put different resistors in series with the output of our integrator. We used three resistors with values of 100 Ohms, 220k Ohms, and 810k Ohms to see what kind of effect it would have on our sawtooth wave. Below are the results. 
<br/>
![100 ohm integrator](https://user-images.githubusercontent.com/14367479/32998009-3a259756-cd65-11e7-9a63-e7a3962ce74a.jpg)
A 100 Ohm load doesn't have an apparent effect on the sawtooth wave from the integrator.

![220k ohm integrator](https://user-images.githubusercontent.com/14367479/32998010-3b7cd40c-cd65-11e7-8a19-c63a0f998029.jpg)
Putting a 220k Ohm resistor in series with the output seems to cause the peaks to become less sharp, so that it's not reaching the original peak to peak voltage. The peak to peak voltage drops from 3.7 V to 3.04 V.

![810k ohm integrator](https://user-images.githubusercontent.com/14367479/32998011-3cb41556-cd65-11e7-944b-24cbbde39cf9.jpg)
A 810k Ohm resistor seems to further intensify the softening effect, and further reduces the peak to peak voltage from 3.04V too 1.95V. Overall however, the wave maintains its sawtooth shape. 
<br/>


### Bill of Material 
![billofmaterial](https://user-images.githubusercontent.com/30231031/32694469-7d63bde8-c70e-11e7-8cbf-2dc978e872e9.png)
### Digikey Cart link
http://www.digikey.com/short/q37db1