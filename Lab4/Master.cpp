// Sets the MCU up as Master, and exchanges data with a slave, sending its own switch positions, and displaying those of the slave.
#include "mbed.h"
SPI MySPI(D11, D12, D13); // mosi, miso, sclk
DigitalOut SSEL(A3); //this acts as “slave select”
AnalogIn Vin(A2);
float send;
float rece;
float PWM_duty;
PwmOut myLed(D5);

int main()
{
    while (1) {
        MySPI.format(32,0);
        MySPI.frequency(1000000);
        //Default settings for SPI Master chosen, no need for further configuration
        //Set up the word to be sent, by testing switch inputs
        send = Vin/(3.3);
        SSEL = 0; //select slave
        rece = MySPI.write(send); //send switch_word and receive data
        SSEL = 1;
        wait_us(10000);  
//set leds according to incoming word from slave
    }
}