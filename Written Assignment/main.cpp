#include<mbed.h>

Serial Mbed(USBTX, USBRX);
int input,req_time = 0;
int Password = 2613982;
DigitalOut led_green(A2);
DigitalOut led_red(A3);
AnalogIn Button(A6);
BusOut display(D11,D12,D4,D3,D2,D10,D9,D6); //Segments A,B,C,D,E,F,G,DP

int main()
{
    Mbed.baud(9600);
    Mbed.printf("UESTC 2004 2021/22 - Password Security System\n");
    Mbed.printf("=======================================\n");
    Mbed.printf("\n");
    Mbed.printf("Please enter the password:      ");
    int x = Mbed.scanf("%d",&input);
    /* start of loop */
    while(1){
        if(req_time < 2){//if request times less than 3
            if(x == 1){
                Mbed.printf("%d\n",input);
            }//test if input is int_type

            if(input != Password || x != 1){
                Mbed.printf("The password is incorrect, please reenter it:      ");
                led_red = 1;
                int x = Mbed.scanf("%d",&input);
                req_time += 1;
            }//end of if(wrong or not int_type)

            if(input == Password){
                Mbed.printf("Correct password");
                led_red = 0;
                led_green = 1;
                wait(1);
                display = 0x5B;wait(1); //2
                display = 0x7d;wait(1); //6
                display = 0x06;wait(1); //1
                display = 0x4F;wait(1); //3
                display = 0x6f;wait(1); //9
                display = 0x7f;wait(1); //8
                display = 0x5B;wait(1); //2
                display = 0x00; //None
                led_green = 0;
                break;//break of main loop
            }//ned of if(correct)    
        }//end of if(req_time) 

        if(req_time >= 2){//if request times more than 3
            Mbed.printf("System is locked, please reset!\n");
            while(1){//wait for button
                if(Button.read() > 0.8){//if button pushed
                    Mbed.printf("Please enter the password:      ");
                    int x = Mbed.scanf("%d",&input);
                    req_time = 0;//reset req_time
                    break;
                }
            }
        }//end of if(req_time)
    }//end of while
    /* end of loop */
}//end of main