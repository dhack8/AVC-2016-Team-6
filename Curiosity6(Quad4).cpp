//includes
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);

extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);//includes
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);

extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);//includes
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>



extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);

extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
//these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
/*
0 = Front
1 = Front Side
2 = Back Side
3 = Right side not yet

*/
int main(){
    //This sets up the RPi hardware and ensures 
    //everything is working correctly
    init(0);
    //We declare an integer variable to store the ADC data
    int adc_readingfront;
    int adc_readingfrontleft;
    int adc_readingbackleft;
    int sensors = 3;
    int leftintialspeed =60;
    int rightintialspeed =60;
    int leftSpeed;
    int rightSpeed;
   
    while(true){
        set_motor(1, leftintialspeed); 
        set_motor(2, rightintialspeed);
        adc_readingfront = read_analog(0);
        adc_readingfrontleft = read_analog(1);
        adc_readingbackleft = read_analog(2);
        //printf(adc_readingfront);
        if (adc_readingfront > 200){
            Sleep(0,250000);
            if ((adc_readingfrontleft) > 400){
                rightSpeed = -60; 
                leftSpeed = 60;
               
                //printf(">400 \n");
            }
            if ((adc_readingfrontleft) < 400){
                rightSpeed = 60; 
                leftSpeed = -60;
                
                //printf("<400 \n");
            }
            set_motor(1, rightSpeed); //reverse
            set_motor(2, leftSpeed);
            Sleep(0,500000);
            
        //printf("sensor %d: %d\n", i, adc_reading);
        //printf("got to end \n");
        }
        if (adc_readingfrontleft > adc_readingbackleft){
            leftSpeed = leftSpeed +10;
            set_motor(2, leftSpeed);
            sleep(0,100000);
        }
        else if (adc_readingfrontleft < adc_readingbackleft){
            rightSpeed = rightSpeed +10;
            set_motor(1, rightSpeed);
            sleep(0,100000);
        }
    }
return 0;}
