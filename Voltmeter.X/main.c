// CONFIG
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF

// Define the oscillator frequency, needed for delays
#define _XTAL_FREQ  4000000

#include <xc.h>
// Include ADC and LCD library
#include "adc.h"
#include "lcd.h"
// Storage for the raw ADC value
unsigned int adcVal = 0;
// Voltage Value
unsigned int voltage;

void main(void) {
    TRISB = 0b01000000; // RB7 INPUT
    TRISA = 0b00000;
    // Set CS high and CLK low for ADC
    CS = 1;
    CLK = 0;
    // Set the R/W LCD pin to Write
    RW = 0;
    // Init the LCD
    Lcd_Init();
    while (1) {
        // Get the current ADC output code as an integer
        adcVal = readADC();
        // TODO: Convert integer code into integer voltage, see data sheet
        unsigned int d1 = adcVal* 5 / 1020;
        unsigned int temp = d1 * 204 ;
        unsigned int decimalpart = adcVal - temp;
        unsigned int d2 = decimalpart  *50/1020;
        
        unsigned int temp2 = d2 * 1020/50 ;
        unsigned int decimalpart2 = adcVal - temp - temp2;
        unsigned int d3 = decimalpart2  *500/1020;
        
        
        
        //
        // TODO: Display voltage on LCD
        //TEST GITHUB
        //TEST GITHUB NO2
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_Int(d1);
        Lcd_Set_Cursor(1, 2);
        Lcd_Write_Char('.');
        Lcd_Set_Cursor(1, 3);
        Lcd_Write_Int(d2);
        Lcd_Set_Cursor(1, 4);
        Lcd_Write_Int(d3);
        // Wait a while
        __delay_ms(200);

    }
    return;
}

void welcomeMessage(void) {
    //On power-up the LCD should display a welcome message to the user that includes the range of possible input voltages.
}
