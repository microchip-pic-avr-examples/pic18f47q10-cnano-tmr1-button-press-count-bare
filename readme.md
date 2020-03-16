![](images/MicrochipLogo.png)

# PIC18F47Q10 Using TMR1 Gate to measure short vs long button press

## Objective:
This example shows how to use the TMR1 configured in gate single pulse mode. It will start counting on a falling edge when the button is pressed. Two different interrupts will be activated based on how long the button was pressed. If the leading edge appears, a gate interrupt will be generated, denoting that the button was short pressed. If the timer overflows before the leading edge appears, an overflow interrupt will be generated, denoting that the button was long pressed.

## Resources:
- Technical Brief Link [(linkTBD)](http://www.microchip.com/)
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)
- [PIC18F47Q10 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40002043D.pdf) for more information or specifications.

## Hardware Configuration:

The PIC18F47Q10 Curiosity Nano Development Board [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029) is used as a test platform.

![](images/PIC18F47Q10-Curiosity-Nano.png)

## Demo:
Run the code in debug mode. Set breakpoints inside "TMR1_GATE_ISR()" and "TMR1_ISR()" functions. The button signal is read from the pin RB5. When the button is short pressed, the code will stop at the breakpoint set in the "TMR1_GATE_ISR()" function. When the button is long pressed, the code will stop at the breakpoint set in the "TMR1_ISR()" function.
