#include "mbed.h"

AnalogIn ACEPT(A1);
PwmOut PWM1(D9);
SPISlave MySPI(D11,D12,D13,A3);
float receive_value;
float transmit_value;
int main(){

    MySPI.frequency (1000);
    MySPI.format(32.0);
   
          while(1){
               transmit_value=ACEPT;
              if(MySPI.receive()){
                  receive_value=MySPI.read();
                  MySPI.reply(transmit_value);
                  }
                  PWM1.period(5);
                  PWM1.write(receive_value);
                  }
          }