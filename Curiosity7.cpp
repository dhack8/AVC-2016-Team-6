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
extern "C" int receive_from_server(char message[24]);

void turnLeft(int PID, int MOTOR_SPEED);
void turnRight(int PID, int MOTOR_SPEED);
void lostLine(int errorSign);

int main(){
  init(0);
  int i = 0;
  int pixel = 0;
  int sum;
  int numFound;
  int locationLine;
  int error = 0;
  int center = 160;
  int P = 0;
  float kP = 0.9;
  int previousError = 0;
  int D = 0;
  float kD = 0;
  int MOTOR_SPEED = 40;
  bool lostLine = false;
  int errorSign;
  
  //connect_to_server("130.195.6.196", 1024); //Connects to server with the ip address 130.195.6.196, port 1024
  //send_to_server("Please");                 //Asks the connected server for the password (nicely)
  //char pass[24];                            //Define the password variable
  //receive_from_server(pass);                //Receives the password from the connected server
  //send_to_server(pass);                     //Sends the password to the server
  //Sleep(2,0);
  
  while(true){ //Continuos loop that goes forever
    take_picture(); //grab camera pic
    sum = 0; //reset key values
    numFound = 0;
    locationLine = 0;
    for(i = 0; i < 320; i++){ //traverse along picture in middle
      pixel = get_pixel(i, 1, 3);
      if (pixel>115){ //flattening finding white pixels
        sum = sum + i;
        numFound++;
      }
    }
    
    if(numFound != 0){
      locationLine = sum/numFound; // finds middle of white line
    }
    
    if(sum > 12880){
      printf("found an intersection \n");
    }
    
    if(numFound < 18){ // if lost line (not enough white pixels for there to be a line)
      errorSign = previousError;
      lostLine(errorSign);
      continue;
    }
    
    error = center - locationLine; //our error signal
    
    D = error - previousError; // Difference between this error and the last
    
    previousError = error; //setting previous error after operation
    
    P = kP*error; //times P by gain
    
    D = kD*D; //times D by gain
    
    if(P>0){//left turn
      turnLeft((P + D), MOTOR_SPEED);
    }else if(P<0){//right turn
      turnRight((P + D), MOTOR_SPEED);
    }
  }
  return 0; //return nothing
}

void turnLeft(int PID, int MOTOR_SPEED){
  set_motor(1, MOTOR_SPEED);
  set_motor(2, MOTOR_SPEED+PID); //right motor goes faster
  Sleep(0, 50000); // 0.05 seconds sleep
}

void turnRight(int PID, int MOTOR_SPEED){
  set_motor(1, MOTOR_SPEED-PID); //left motor goes faster
  set_motor(2, MOTOR_SPEED);
  Sleep(0, 50000);// 0.05 seconds sleep
}

void lostLine(int errorSign){
  if(errorSign>0){//left turn
    turnLeft(45, 0);
  }else if(errorSign<0){//right turn
    turnRight(-45, 0);
  }
}
