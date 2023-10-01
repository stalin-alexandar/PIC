#include <xc.h>
#define _XTAL_FREQ 20000000
#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC2

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
    PORTC = data;
    RS = 1; // Set RS for data
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_command(unsigned char cmd)
{
    PORTC = cmd;
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

    lcd_initialise();

    while (1)
    {
        lcd_command(0x80); // Set cursor to the beginning of the first line
        lcd_string("HI I AM ALEX", 12);

        lcd_command(0xC0); // Set cursor to the beginning of the second line
        lcd_string("bye", 3);
    }

    return;
}
