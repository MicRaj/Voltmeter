// config
// =====================================================
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF

#define _XTAL_FREQ  4000000 // clock speed

#include <xc.h> // Include ADC and LCD library
#include "adc.h"
#include "lcd.h"
// =====================================================

// global variables
// =====================================================
unsigned short int adcVal = 0; // Storage for the raw ADC value
unsigned short int voltage; // Voltage Value
unsigned short int lowerV = 0; // minimum voltage value
unsigned short int upperV = 5; // max voltage value
// =====================================================

// welcome function
// =====================================================
void welcomeMessage(void) {
    //On power-up the LCD should display a welcome message to the user that includes the range of possible input voltages.
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
   // Lcd_Write_String("Hi Min: %d Max: %d ", lowerV, upperV);
    __delay_ms(1000);
    Lcd_Clear();
}
// =====================================================

// main
// =====================================================

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
    welcomeMessage();
    while (1) {
        // Get the current ADC output code as an integer
        adcVal = readADC();
        // TODO: Convert integer code into integer voltage, see data sheet
        unsigned short int d1;
        unsigned short int d2;
        unsigned short int d3;
        
        d1 = adcVal / 204;
        d2 = (adcVal % 204)*10/204;
        d3 = ((adcVal*10)%204)*10/204;
        
        
      
        
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
// =====================================================


