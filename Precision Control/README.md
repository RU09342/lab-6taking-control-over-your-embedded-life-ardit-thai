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
An 8 Bit ladder works by splitting every voltage coming in by 2 the power of its significance in the binary number. The most significant number is split by 2, the next most is split by 4, and so on. So if I were to input 1010, the the first voltage would be split by 2 to the power of 1, because the first 1 (that represents an 8 in decimal) is the most significant. Thus, it will contribute half of the incoming voltage. In contrast to this, the 3rd most significant 1 (that represents a 2) will be split by 2 to the power of 3. Thus, it will contribute an eighth of the incoming voltage. The 0s in the binary number are connected to ground, and contribute nothing.
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
In order to get a general idea of the loading effects of the MSP boards, we built a model in TINA-TI to approximate the effect of the boards. When we put a low resistance to represent the MSP430 (R17) in our R2R ladder, the loading effect was low, and output voltage was close to the expected value. However, when we increased the representative resistance of our MSP430 to higher resistances, our output voltage decreased, as the MSP430 resistor took a larger voltage drop from the power source. Thus, we theorize that the true resistance of the MSP430 is close to 100 Ohms, because our analytical output voltage in our R2R ladder was close to our experimental value. (Within .1 Volts) In our model, setting R17 as 100 Ohms resulted in our output voltage being 0.03 Volts lower than our expected  value.
Below is the simulation result we got in TINA_TI. <br \>
![loadingeffect_schem](https://user-images.githubusercontent.com/30231031/32421486-28614f32-c267-11e7-9d8e-d2f21dc4ef3f.png)

### Bill of Material 
![billofmaterial](https://user-images.githubusercontent.com/30231031/32694469-7d63bde8-c70e-11e7-8cbf-2dc978e872e9.png)
### Digikey Cart link
http://www.digikey.com/short/q37db1