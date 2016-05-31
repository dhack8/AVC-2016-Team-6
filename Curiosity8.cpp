//includes and externs
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

//declearing our functions
void turnLeft(int PID, int MOTOR_SPEED);
void turnRight(int PID, int MOTOR_SPEED);
void lostLine(int errorSign);

int main(){
  init(0); //intialize hardware
  int i = 0; //traverse for horizontal line
  int pixel = 0; //pixel value for horizontal line (white level)
  int sum; //sum of ith values that are white
  int numFound; //number of white pixels found in line
  int locationLine; //where the tape is along the horzontal line
  int o = 0; //traversal value for 2 vertical lines
  int pixelLeft = 0; //pixel value for left vertical line
  int pixelRight = 0; //pixel value for right vertical line
  int numFoundLeft = 0; //number of white pixels found in left vertical line
  int numFoundRight = 0; //number of white pixels found in right vertical line
  int error = 0; //error from center of horizontal line
  int center = 160; //center of horizontal line
  int P = 0; //proportianal control
  float kP = 0.7; //proportional gain
  int previousError = 0; //the error before the current error
  int D = 0; //dirivitave controll currently not being used
  float kD = 0; //dirivitave gain currently 0 not being used
  int MOTOR_SPEED = 40; //base motor speed that both mators are at least running at
  int THRESHOLD = 120; //anything below 115 is a black pixel anything above can be considered white
  int NUM_FOUND_THRESH = 30; //constant to decide when there are two few pixels to constitute for the tape
  bool quad3 = false; //Bool for detecting if in quad 3 or not
  int adc_readingfrontleft;
  int adc_readingbackleft;
  
  //network code commented out for easy testing
  
  //connect_to_server("130.195.6.196", 1024); //Connects to server with the ip address 130.195.6.196, port 1024
  //send_to_server("Please");                 //Asks the connected server for the password (nicely)
  //char pass[24];                            //Define the password variable
  //receive_from_server(pass);                //Receives the password from the connected server
  //send_to_server(pass);                     //Sends the password to the server
  //Sleep(2,0);
  
  while(true){ //Continuos loop that goes forever
    take_picture(); //get picture from what the camera is currently viewing
    
    sum = 0; //seting certain values to 0 that need to be reset each run through else they would stack
    numFound = 0;
    locationLine = 0;
    for(i = 0; i < 320; i++){ //traverse 320 pixels same legnth as camera resolution in width 320px
      pixel = get_pixel(i, 40, 3); //get a pixel i along and 40 from the top of the image, vertical resolution = 240
      if (pixel>THRESHOLD){ //if pixel is above a certain value it counts as white
        sum = sum + i; //increacing the sum, we need this for finding the average i value that was white
        numFound++; //keeping track of number of pixels found on the horizontal line, for mean and seeing if we lost the line
      }//if closes here
    }//for loop closes here
    
    if(numFound != 0){ //just so we dont divide by 0 and create a black hole
      locationLine = sum/numFound; //finds the mean location of pixels that were white, can be effected by outlyers
    }//if closes here
    
    if(numFound>300){ //code to detect when quad 3 is reached
      quad3 = true;
      MOTOR_SPEED = 30;
      THRESHOLD = 110;
      kP = 0.5;
      printf("----/ QUAD3 CODE ACTIVATED  \----");
    }
    if(quad3){
      adc_readingfrontleft = read_analog(1);
      adc_readbackleft = read_analog(2);
        if((adc_readingfrontleft >400) && (adc_readingbackleft > 400)){
          printf("----/ QUAD4 CODE ACTIVATED  \----");
          break;
        }
    }
    
    //this is code for if the horizontal line has lost the tape ie numfound < a-threshold-value
    //basically damage control for when following line
    //but first looks if it lost the line due to an intersection
    //note if the intersection has an option to go forwards ie 4 ways and going across the tops of t junctions
    //for those we want to just go forwards (aviods all those annoying turns at the start of quad 3)
    if(numFound < NUM_FOUND_THRESH){ //if lost line (not enough white pixels for there to be a line)
      numFoundLeft = 0; //reseting some values used to find white pixels in vertical lines
      numFoundRight = 0; //left and right
      if(quad3){
        for(o = 0; o < 240; o++){ //traverse along picture from camera downwards
        pixelLeft = get_pixel(60, o, 3); //geting the pixel 40 from the left and oth down and white value (3)
        pixelRight = get_pixel(260, o, 3); //getting the pixel 280 from the left and oth down and the white value (3)
        2.089*10^12
          if(pixelLeft>THRESHOLD){ //if pixel is above a certain value it counts as white for left line
            numFoundLeft++; //increace left line numfound
          }//if closes here
          if(pixelRight>THRESHOLD){ //if pixel is above a certain value it counts as white for right line
            numFoundRight++; //increace right line numfound
          }//if closes here
        }//for loop closes here
      }
      //now we have the number of white pixels in the left and right vertical lines
      if(numFoundLeft > 90){ //either a T juntion or a left turn either way we want to turn left
        printf("T junction/left turn \n");
        set_motor(1, 40);
        set_motor(2, 40);
        Sleep(0, 50000);
        set_motor(1, 0);
        set_motor(2, 120);
        Sleep(0, 500000);
      }else if(numFoundRight > 90){ //a right turn, dont need to check left side bc if the left had tape we would have turned already
        printf("Right turn \n");
        set_motor(1, 40);
        set_motor(2, 40);
        Sleep(0, 50000);
        set_motor(1, 140);
        set_motor(2, 0);
        Sleep(0, 650000);
      }else{ //if horizontal line has nothing and both the vertical lines have nothing must of lost the line on a hard turn (quad 1 or 2)
        lostLine(previousError); //code for finding line again, function is located below
      }//for array ends here
      continue; //continue to get the system to rescan rather then continueing to line following code
    }//middle line lost tape if closes here
    //back to normal line following code
    
    error = center - locationLine; //error = 160 - where the line is, sign of the error tells us which way to turn
    
    D = error - previousError; // Difference between this error and the last to find dirivative, but this isnt being used anymore
    
    P = kP*error; //P is simply the error multiplied by its gain
    
    D = kD*D; //times D by gain, kD currently = 0 therefore D equals 0
    
    //actual line following code here
    if(P>0){//left turn
      turnLeft((P + D), MOTOR_SPEED); //this is a functon we made see below
    }else if(P<0){//right turn
      turnRight((P + D), MOTOR_SPEED); //this is a functon we made see below
    }//line following ends here
    
    previousError = error; //setting previous error after operations at very end
    
  }//end of while loop
  
  //this is where quad 4 code will go
  
return 0;//return nothing
}

void turnLeft(int PID, int MOTOR_SPEED){// left turn code takes PID and motorspeed
  set_motor(1, MOTOR_SPEED); //left wheel, both wheels go at atleast motorspeed
  set_motor(2, MOTOR_SPEED+PID); //right motor goes faster adding PID becasie PID is positive
  Sleep(0, 5000); // 0.005 seconds sleep
}//end of turn left

void turnRight(int PID, int MOTOR_SPEED){// right turn code takes PID and motorspeed
  set_motor(1, MOTOR_SPEED-PID); //left motor goes faster, minus PID becasie PID is negative, subtracting a negative number is the same as adding
  set_motor(2, MOTOR_SPEED); //right motor
  Sleep(0, 5000);// 0.005 seconds sleep
}//end of turn right

void lostLine(int errorSign){ //function for when the middle line looses the tape but its not an intersection
  if(errorSign>0){//left turn
    turnLeft(55, 0); //turn left 45, motorspeed 0 so the bot pivots to the left
  }else if(errorSign<0){//right turn
    turnRight(-55, 0); //turn right 45, motorspeed 0 so the bot pivots to the right
  }
}//end of lostLine

//end of program
