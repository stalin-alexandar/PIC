// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
// 'C' source line config statements
#define _XTAL_FREQ 20000000
#define RS PORTBbits.RB0
#define RW PORTBbits.RB1
#define EN PORTBbits.RB2

void lcd_cmd(unsigned char cmd){
    
    PORTC = ((cmd)&(0xF0));
    EN = 1;
    RW = 0;
    RS = 0;
    __delay_ms(2);
    EN=0;
    PORTC = ((cmd<<4)&(0xF0));
    EN = 1;
    RW = 0;
    RS = 0;
    __delay_ms(2);
    EN = 0;
}
void lcd_data(unsigned char data){
    PORTC = ((data)&(0xF0));
     EN = 1;
    RW = 0;
    RS = 1;
    __delay_ms(2);
    EN = 0;
    PORTC = ((data<<4)&(0xF0));
    EN = 1;
    RW =0;
    RS = 1;
    __delay_ms(2);
    EN = 0;
}

 void lcd_string(unsigned char *str, unsigned char len){
     unsigned char i;
     for(i=0;i<len;i++){
         lcd_data(str[i]);
     }
 }
      void lcd_initialise()
    {
        lcd_cmd(0x02);
        lcd_cmd(0x28);
        lcd_cmd(0x06);
        lcd_cmd(0x0C);
        lcd_cmd(0x01);
        
    }


void main(void) {
    TRISB=0x00;
    TRISC=0x00;
    lcd_initialise();
   
    while(1)
    {
        lcd_cmd(0x80);
        lcd_string("Alex Clown",10);
        lcd_cmd(0xC0);
        lcd_string("Punda",5);
    }
    
    return;
}
