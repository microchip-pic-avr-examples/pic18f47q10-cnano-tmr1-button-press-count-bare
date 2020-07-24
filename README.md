<div id="readme" class="Box-body readme blob js-code-block-container">
 <article class="markdown-body entry-content p-3 p-md-6" itemprop="This needs to locked down and 'never' changed"><p><a href="https://www.microchip.com" rel="nofollow"><img src="images/MicrochipLogo.png" alt="MCHP" style="max-width:40%;"></a></p>

# PIC18F47Q10 Using TMR1 Gate to measure short vs long button press

The PIC18F47Q10 features Timers with Gate Control.
This example shows how to use the TMR1 configured in gate single pulse mode. It will start counting on a falling edge when the button is pressed. Two different interrupts will be activated based on how long the button was pressed. If the leading edge appears, a gate interrupt will be generated, denoting that the button was short pressed. If the timer overflows before the leading edge appears, an overflow interrupt will be generated, denoting that the button was long pressed.

## Related Documentation
- [PIC18F-Q10 Family Product Page](https://www.microchip.com/design-centers/8-bit/pic-mcus/device-selection/pic18f-q10-product-family)
- [PIC18F47Q10 Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40002043D.pdf)

## Software Used
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or a newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- Microchip PIC18F-Q Series Device Support (1.4.109) or newer [(packs.download.microchip.com/)](https://packs.download.microchip.com/)

## Hardware Used
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)

## Setup
The PIC18F47Q10 Curiosity Nano Development Board is used as the test platform.

The following configurations must be made for this project:

|Pin           | Configuration      |
| :----------: | :----------------: |
|RB5           | Digital Input      |

## Demo:
Connect a button to Pin RB5. Run the code in debug mode. Set breakpoints inside "TMR1_GATE_ISR()" and "TMR1_ISR()" functions. The button signal is read from the pin RB5. When the button is short pressed, the code will stop at the breakpoint set in the "TMR1_GATE_ISR()" function. When the button is long pressed, the code will stop at the breakpoint set in the "TMR1_ISR()" function.

<img src="images/PIC18F47Q10-Curiosity-Nano.png" alt="Hardware Setup"/>
