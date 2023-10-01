#include <xc.h>
#define _XTAL_FREQ 20000000
#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC2

//keypad
#define D0 PORTDbits.RD0
#define D1 PORTDbits.RD1
#define D2 PORTDbits.RD2
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void lcd_data(unsigned char data)
{
    PORTB = data;
    RS = 1; // Set RS for data
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_command(unsigned char cmd)
{
    PORTB = cmd;
    RS = 0; // Set RS for command
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_string(const unsigned char *str, unsigned char num)
{
    unsigned char i;
    for (i = 0; i < num; i++)
    {
        lcd_data(str[i]);
    }
}
void keypad(){
    
    D0=1;
    D1=0;
    D2=0;
    if(D4==1)
    {
        lcd_data('1');
        while(D4==1);
    }
     if(D5==1)
    {
        lcd_data('4');
        while(D5==1);
    }
     if(D6==1)
    {
        lcd_data('7');
        while(D6==1);
    }
     if(D7==1)
    {
        lcd_data('*');
        while(D7==1);
    }
     D0=0;
    D1=1;
    D2=0;
    if(D4==1)
    {
        lcd_data('2');
        while(D4==1);
    }
     if(D5==1)
    {
        lcd_data('5');
        while(D5==1);
    }
     if(D6==1)
    {
        lcd_data('8');
        while(D6==1);
    }
     if(D7==1)
    {
        lcd_data('0');
        while(D7==1);
    }
     D0=0;
    D1=0;
    D2=1;
    if(D4==1)
    {
        lcd_data('3');
        while(D4==1);
    }
     if(D5==1)
    {
        lcd_data('6');
        while(D5==1);
    }
     if(D6==1)
    {
        lcd_data('9');
        while(D6==1);
    }
     if(D7==1)
    {
        lcd_data('#');
        while(D7==1);
    }
}

void lcd_initialise()
{
    lcd_command(0x38); // 2 lines, 5x7 matrix
    lcd_command(0x06); // Increment cursor (shift cursor to right)
    lcd_command(0x0C); // Display on, cursor off
    lcd_command(0x01); // Clear display
}

void main(void)
{
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD= 0xF0;
    lcd_initialise();
    lcd_command(0x80);
    lcd_string("Keyword",7);
    lcd_command(0xC0);

    while (1)
    {
        keypad();
    }

    return;
}
