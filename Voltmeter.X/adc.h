// ADC Functions for the MCP3001
// B.W.Metcalfe 2016

// Define the oscillator frequency, needed for delays
#define _XTAL_FREQ  4000000

// Define the ping connections
#define CS RB7
#define CLK RB5
#define DIN1 RB6
#define DIN2 RA3

// Read a single (8-bit) sample from the ADC
unsigned int readADC1();
unsigned int readADC2();