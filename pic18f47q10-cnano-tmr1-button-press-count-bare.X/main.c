/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/* WDT operating mode->WDT Disabled */
#pragma config WDTE = OFF
/* Low voltage programming enabled, RE3 pin is MCLR */
#pragma config LVP = ON 

#include <xc.h>
#include <stdint.h>

static void CLK_init(void);
static void PORT_init(void);
static void TMR1_init(void);
static void INTERRUPT_init(void);

static void TMR1_ISR(void);
static void TMR1_GATE_ISR(void);
static void TMR1_writeTimer(uint16_t timerValue);

/* Clock initialization function */
static void CLK_init(void)
{
    /* set HFINTOSC as new oscillator source */
    OSCCON1 = _OSCCON1_NOSC1_MASK | _OSCCON1_NOSC2_MASK;

    /* set Clock Div by 32 */
    OSCCON1 |= _OSCCON1_NDIV0_MASK | _OSCCON1_NDIV2_MASK;       
    
    /* set HFFRQ to 32MHz */
    OSCFRQ = _OSCFRQ_FRQ1_MASK | _OSCFRQ_FRQ2_MASK;             
}

/* Port initialization function */
static void PORT_init(void)
{
    /* configure RB5 as input */
    TRISB |= _TRISB_TRISB5_MASK;
    
    /* configure RB5 as digital */
    ANSELB &= ~(_ANSELB_ANSELB5_MASK);
}

/* TMR1 initialization function */
static void TMR1_init(void)
{
    T1GCON = _T1GCON_GE_MASK        /* Timer controlled by gate function */
           | _T1GCON_T1GGO_MASK     /* Timer acquistion is ready */
           | _T1GCON_GSPM_MASK;     /* Timer gate single pulse mode enabled */
        
    T1CLK = _T1CLK_T1CS0_MASK;      /* Source Clock FOSC/4 */
    
    /* Clearing IF flag before enabling the interrupt */
    PIR4 &= ~_PIR4_TMR1IF_MASK;
    
    /* Enabling TMR1 interrupt */
    PIE4 = _PIE4_TMR1IE_MASK;                                              
    
    /* Clearing gate IF flag before enabling the interrupt */
    PIR5 &= ~_PIR5_TMR1GIF_MASK;

    /* Enabling TMR1 gate interrupt */     
    PIE5 = _PIE5_TMR1GIE_MASK;
    
    T1CON = _T1CON_CKPS_MASK        /* CLK Prescaler 1:8 */
          | _T1CON_TMR1ON_MASK;     /* TMR1 enabled */
}

/* Interrupt initialization function */
static void INTERRUPT_init(void)
{
    INTCON = _INTCON_GIE_MASK      /* Enable the Global Interrupts */
           | _INTCON_PEIE_MASK;    /* Enable the Peripheral Interrupts */
}

/* Interrupt handler function */
static void __interrupt() INTERRUPT_interruptManager(void)
{
    // Check if interrupts were enabled
    if(INTCON & _INTCON_PEIE_MASK)
    {
        /* Check if TMR1 interrupt is enabled and if the interrupt flag is true */
        if((PIE4 & _PIE4_TMR1IE_MASK) && (PIR4 & _PIR4_TMR1IF_MASK))
        {
            TMR1_ISR();
        } 
        
        /* Check if TMR1 gate interrupt is enabled and if the interrupt flag is true */
        if((PIE5 & _PIE5_TMR1GIE_MASK) && (PIR5 & _PIR5_TMR1GIF_MASK))  
        {
            TMR1_GATE_ISR();
        } 
    }
}

/* TMR1 ISR function */
static void TMR1_ISR(void)
{  
    /* Stop Gate control */
    T1GCON &= ~_T1GCON_T1GGO_MASK;                                      
    
    /* Clearing overflow IF flag */
    PIR4 &= ~_PIR4_TMR1IF_MASK;
    
    /* Clearing gate IF flag */
    PIR5 &= ~_PIR5_TMR1GIF_MASK;                                        
    
    /* Reset the counted value */
    TMR1_writeTimer(0);                                                 
    
    /* Prepare for next read */
    T1GCON |= _T1GCON_T1GGO_MASK;                                       
}

/* TMR1 GATE ISR function */
static void TMR1_GATE_ISR(void)
{    
    /* Clearing gate IF flag after button release */
    PIR5 &= ~(_PIR5_TMR1GIF_MASK);                                     

    /* Reset the counted value */
    TMR1_writeTimer(0);                                                 
    
    /* Prepare for next read */
    T1GCON |= _T1GCON_T1GGO_MASK;                                       
}

/* TMR1 write counter value function */
static void TMR1_writeTimer(uint16_t timerValue)
{
    /* Write TMR1H value */
    TMR1H = timerValue >> 8;
    
    /* Write TMR1L value */
    TMR1L = timerValue;                                                 
}

void main(void)
{
    CLK_init();
    PORT_init();
    TMR1_init();
    INTERRUPT_init();
     
    while (1)
    {   
        ;
    }
}

