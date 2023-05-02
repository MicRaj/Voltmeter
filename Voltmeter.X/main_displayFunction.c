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
#include "string.h"
// =====================================================

// global variables
// =====================================================
unsigned short int adcVal = 0; // Storage for the raw ADC value
unsigned volatile char toggleHold = 0b0; // global variable for toggle button
// =====================================================

// ISR
// =====================================================
void __interrupt() isr() {
    INTCONbits.INTF = 0; // reset interrupt flag
    toggleHold = ~toggleHold; // invert toggleHold variable
    delay_100ms();
    return;
}
// =====================================================

// delay functions
// =====================================================
void delay_100ms() {
    __delay_ms(100);
    return;
}
// 100ms delay function - done to optimise storage on pic

void delay_2000ms() {
    for (int i = 0; i < 20; i++) {
        delay_100ms();
    }
    return;
}
// 2000ms delay function - just loops the delay 100ms 20 times
// =====================================================

// welcome function
// =====================================================
void welcomeMessage(void) {
    char msg[] = "Hi"; // welcome message
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String(msg);
    delay_2000ms();
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    strcpy(msg, "0-5V"); // voltage range
    Lcd_Write_String(msg);
    delay_2000ms();
    Lcd_Clear();
}
// =====================================================

// LCD write function
// =====================================================
void LCD_Writer(int digit1, int digit2, int digit3, int digit4) {
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_Int(digit1);
    Lcd_Set_Cursor(1, 2);
    Lcd_Write_Char('.');
    Lcd_Set_Cursor(1, 3);
    Lcd_Write_Int(digit2);
    Lcd_Set_Cursor(1, 6);
    Lcd_Write_Int(digit3);
    Lcd_Set_Cursor(1, 7);
    Lcd_Write_Char('.');
    Lcd_Set_Cursor(1, 8);
    Lcd_Write_Int(digit4);
    // function that writes the 4 digits from the ADC onto the screen, with decimals
}
// =====================================================

// main
// =====================================================
void main(void) {
    // main initialisation
    // ----------------------------
    TRISB = 0b01000001; // RB7 INPUT
    TRISA = 0b01000;
    // Set CS high and CLK low for ADC
    CS = 1;
    CLK = 0;
    // Set the R/W LCD pin to Write
    RW = 0;
    // ----------------------------

    //interrupt set
    // ----------------------------
    // Interrupt on the rising edge
    OPTION_REGbits.INTEDG = 1;
    // Enable the external interrupt
    INTCONbits.INTE = 1;
    // Global interrupt enable
    INTCONbits.GIE = 1;
    // ----------------------------

    Lcd_Init(); // initialise the LCD
    welcomeMessage(); // calls welcome message function
    unsigned short int ADC1_Digit1;
    unsigned short int ADC1_Digit2;
    unsigned short int ADC2_Digit1;
    unsigned short int ADC2_Digit2;
    while (1) {
        while (toggleHold) {
            LCD_Writer(ADC1_Digit1, ADC1_Digit2, ADC2_Digit1, ADC2_Digit2);
            // hold loop for when button is toggled
        }
        // reading ADCs
        // ----------------------------
        adcVal = readADC1(); // reads the 1st ADC
        ADC1_Digit1 = adcVal / 204;
        ADC1_Digit2 = ((adcVal % 204)*10 / 204);
        adcVal = readADC2(); // reads 2nd ADC
        ADC2_Digit1 = adcVal / 204;
        ADC2_Digit2 = ((adcVal % 204)*10 / 204);
        // turns the ADC data output into a set of 2 digits per ADC to display on the lcd
        // ----------------------------
        LCD_Writer(ADC1_Digit1, ADC1_Digit2, ADC2_Digit1, ADC2_Digit2);
        delay_100ms();
    }
    return;
}
// =====================================================
