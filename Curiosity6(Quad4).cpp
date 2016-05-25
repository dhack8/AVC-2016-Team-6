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
    int adc_readingrightside; //not on the robot yet
   
    int leftintialspeed =60;
    int rightintialspeed =60;
    int leftSpeed;
    int rightSpeed;
   
    while(true){
        leftSpeed = 0; //resets the leftSpeed each loop
        rightSpeed = 0; //resets the rightSpeed each loop
        set_motor(1, leftintialspeed); //sets the speed at 60 going in the current direction 
        set_motor(2, rightintialspeed);
        // takes the 3 (soon to be 4) readings which will be runned thorugh the if statements.
        adc_readingfront = read_analog(0);
        adc_readingfrontleft = read_analog(1);
        adc_readingbackleft = read_analog(2);
        //printf(adc_readingfront);
        
        //code for a 180 degree turn//
        //has to be at start as it has to happen before anything else if it is true
        if (adc_readingfrontleft >400 && adc_readingfront >400 && adc_readingrightside >400) {
            //adc_readingrightside isn't on the robot 
            
            //not sure if correct took from the github pages (under 180 turn)
            //set_motor(1, 40);
            //set_motor(2, 40);
            //Sleep(1,0);
            //set_motor(1, -62);
            //set_motor(2, 62);
            //Sleep(0,500000);
            //set_motor(1, 0);
            //set_motor(2, 0);
            //Sleep(0,50000);
        }
        //code for making the 90 degree turns 
        if (adc_readingfront > 200){ 
            Sleep(0,250000);
            if ((adc_readingfrontleft) > 400){   //has a wall on the left so will turn right
                rightSpeed = -60; 
                leftSpeed = 60;
            }
            if ((adc_readingfrontleft) < 400){    //has no wall on the left so will turn left
                rightSpeed = 60; 
                leftSpeed = -60;
            }
            //moves the robot for .5secs to do the 90degree turn
            set_motor(1, rightSpeed); 
            set_motor(2, leftSpeed);
            Sleep(0,500000);
            //sets it back to the original speed after the turn 
            set_motor(1, rightintialspeed); 
            set_motor(2, leftintialspeed);
   
        }
        //error correcting code
        // if both sensors aren't parallel to the wall make them
        //this means the robot will be going straight
        if (adc_readingfrontleft > adc_readingbackleft){
            leftSpeed = 10;
            set_motor(2, leftintialspeed+leftSpeed);
            sleep(0,100000);
            
        }
        else if (adc_readingfrontleft < adc_readingbackleft){
            rightSpeed = 10;
            set_motor(1, rightintialspeed+rightSpeed);
            sleep(0,100000);
        
        }    
        //need to add code to make sure that they dont get too close to either of the walls
        //if (adc_readingfrontleft>really close to the wall){
            //leftSpeed = 5;
            //rightSpeed = -5;
            //set_motor(1, leftintialspeed+rightSpeed);
            //set_motor(2, leftintialspeed+leftSpeed);
            //sleep(0,100000);
        //}
        //if (adc_readingbackleft>really close to the wall){
            //leftSpeed = -5;
            //rightSpeed = 5;
            //set_motor(1, leftintialspeed+rightSpeed);
            //set_motor(2, leftintialspeed+leftSpeed);
            //sleep(0,100000);
        //}
        
    }
return 0;}
