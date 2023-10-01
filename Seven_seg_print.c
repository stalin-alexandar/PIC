/*
 * File:   Main.c
 * Author: lenovo
 *
 * Created on 16 September, 2023, 9:15 PM
 */
#include <xc.h>
// 'C' source line config statements
#define _XTAL_FREQ 20000000
#define SEGMENT_ON 0
#define SEGMENT_OFF 1

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
unsigned char num=28;
unsigned char segment[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x6f} ,i=0,j=0;
void main(void) {
    TRISB=0x00;
    TRISC=0x00;
    i=num/10;
    j=num%10;
    while(1)
    {
        PORTCbits.RC0=SEGMENT_ON; PORTCbits.RC1=SEGMENT_OFF;
        PORTB=segment[i];
         __delay_ms(10);
          PORTCbits.RC0=SEGMENT_OFF; PORTCbits.RC1=SEGMENT_ON;
          PORTB=segment[j];
         __delay_ms(10);
     
        }
        
    
    return;
}
