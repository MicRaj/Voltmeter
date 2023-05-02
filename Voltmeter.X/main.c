// config
// =====================================================
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF

#define _XTAL_FREQ  4000000 // clock speed#


#include <xc.h> // Include ADC and LCD library
#include "adc.h"
#include "lcd.h"
#include "string.h"
// =====================================================

// global variables
// =====================================================
unsigned short int adcVal = 0; // Storage for the raw ADC value
int toggleHold = 0b0;
// =====================================================

// isr
// =====================================================

void delay_100ms() {
    __delay_ms(100);
    return;
}

void delay_1000ms() {
    for (int i = 0; i < 20; i++) {
        delay_100ms();
    }
    return;
}

void __interrupt() isr() {
    // Reset the interrupt flag
    INTCONbits.INTF = 0;
    // Toggle the state of LED2, ~ is the complement
    toggleHold = ~toggleHold;
    delay_100ms();
    return;
}

// =====================================================

// welcome function asfasd
// =====================================================

void welcomeMessage(void) {
    //On power-up the LCD should display a welcome message to the user that includes the range of possible input voltages.
    char msg[] = "Welcome";
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String(msg);
    delay_1000ms();
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    strcpy(msg, "0-5V");

    Lcd_Write_String(msg);
    delay_1000ms();


    Lcd_Clear();
}
// =====================================================

// main
// =====================================================

void main(void) {

    TRISB = 0b01000001; // RB7 INPUT
    TRISA = 0b01000;
    // Set CS high and CLK low for ADC
    CS = 1;
    CLK = 0;
    // Set the R/W LCD pin to Write
    RW = 0;
    // Init the LCD

    // Interrupt on the rising edge
    OPTION_REGbits.INTEDG = 1;
    // Enable the external interrupt
    INTCONbits.INTE = 1;
    // Global interrupt enable
    INTCONbits.GIE = 1;

    Lcd_Init();
    welcomeMessage();
    unsigned short int d1;
    unsigned short int d2;
    unsigned short int d3;
    unsigned short int d4;
    while (1) {
        while (toggleHold) {
            Lcd_Set_Cursor(1, 1);
            Lcd_Write_Int(d1);
            Lcd_Set_Cursor(1, 2);
            Lcd_Write_Char('.');
            Lcd_Set_Cursor(1, 3);
            Lcd_Write_Int(d2);
            Lcd_Set_Cursor(1, 6);
            Lcd_Write_Int(d3);
            Lcd_Set_Cursor(1, 7);
            Lcd_Write_Char('.');
            Lcd_Set_Cursor(1, 8);
            Lcd_Write_Int(d4);


        }


        // Get the current ADC output code as an integer
        adcVal = readADC1();
        d1 = adcVal / 204;
        d2 = ((adcVal % 204) / 51) *25;
        adcVal = readADC2();
        d3 = adcVal / 204;
        d4 = ((adcVal % 204) / 51) *25;


        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_Int(d1);
        Lcd_Set_Cursor(1, 2);
        Lcd_Write_Char('.');
        Lcd_Set_Cursor(1, 3);
        Lcd_Write_Int(d2);
        Lcd_Set_Cursor(1, 6);
        Lcd_Write_Int(d3);
        Lcd_Set_Cursor(1, 7);
        Lcd_Write_Char('.');
        Lcd_Set_Cursor(1, 8);
        Lcd_Write_Int(d4);
        delay_100ms();
    }
    return;
}
// =====================================================

