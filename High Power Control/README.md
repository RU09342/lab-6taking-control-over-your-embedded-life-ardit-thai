## Ardit Pranvoku and Thai Nghiem LCD display

### High Power Control

When driving loads that take more than 3.3 volts to drive, which is what the MSP430 is able to cover, then we must figure out an alternative way to power bigger devices such as fans or motors. Two ways two do this are mosfets and relays. We tested both and found that mosfets are preferable, though both have their own advantages and disadvantages.

### N-Channel Mosfet Switching

In order to test our mosfet, we implemented it in the following schematic with the MSP430 providing a PWM signal. </br>
![mosfethighpower](https://user-images.githubusercontent.com/14367479/32818587-2075ff98-c992-11e7-8c45-ea35fd09e82b.png)
![mosfethighpower](https://user-images.githubusercontent.com/14367479/32818606-3b77b390-c992-11e7-95d4-53a7486a7832.JPG)

The advantage of MOSFETs is that they have a very low voltage threshold. This means that the voltage provided by almost any voltage source is strong enough to activate a MOSFET. Our MSP4305529 was easily able to accomplish this with the 3.3 Volts coming off of the GPIOs. When the MOSFET is activated, it provides a path for a stronger power source to a load, while still allowing the MSP to control the device.

![mosfethighpower 1](https://user-images.githubusercontent.com/14367479/32819401-143c91d8-c997-11e7-95a5-67638fef0911.gif)

### Relay Switching

The relay works by using an inductor to control a mechanical switch. Below is the schematic we used to build our relay.</br>
![relayhighpower](https://user-images.githubusercontent.com/14367479/32819397-0f20aac2-c997-11e7-9c55-a1e4b5b0066c.png)</br>
When passing a constant current through an inductor, the inductors generates an electromagnetic field that pulls the switch, providing a path for a power source to a load. Because the relay is mechanical, it carries risks when used at higher frequencies. If the relay is used with a PWM cycle above 500 Hz, it runs the risks of welding to a contact, or otherwise failing to make contact with the closed (activated) contact when an EMF is generated.
</br>
![ezgif com-crop](https://user-images.githubusercontent.com/30231031/32976728-7a05dffa-cbeb-11e7-8fe8-3658e0766133.gif) 
</br>
### Conclusion

Although relays can be used to completely remove loading effects from a circuit, as it uses an EMF to control the switch, we find the shortcomings to be too significant to use over a MOSFET. MOSFETs can be used at much higher frequencies than relies with no worry of welding or failure. Since in the future we plan on driving devices with high frequency PWMs, we believe MOSFETs are the better option in this application. 

### High Current Application

The following circuit can be used for high current applications where the MSP4305529 is incapable of providing the voltage or current needed to drive the device. Both a MOSFET and a relay are used. <br>

![optimalhighpower 1](https://user-images.githubusercontent.com/14367479/32819469-770c4682-c997-11e7-849d-5550714dde9b.png)