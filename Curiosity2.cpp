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

int main(){
  init(0);
  int i = 0; //pixel across image
  int pixel = 0;
  int sum; //amount of white pixels across
  int numFound; //amount of white pixels
  int locationLine; // gets the place in the photo of where the line is
  int error = 0; //distance from the center of the line
  int center = 160; // center pixel
  int P = 0; //proportional
  float kP = 0.9; //proportionality constant
  while(true){ //loops forever
    take_picture(); //takes picture
    //resets values
    sum = 0;
    numFound = 0;
    locationLine = 0;
    //
    for(i = 0; i < 320; i++){ //gets pixels across image
      pixel = get_pixel(i, 1, 3);
      if (pixel>105){//if the pixel is close enough to white
        sum = sum + i;
        numFound++;
      }
    }
    if(numFound != 0){
      locationLine = sum/numFound; // finds middle of white line
    }
    if(numFound < 15){//reverses (straight back) untill finds line again
      set_motor(1, -35);
      set_motor(2, -35);
      Sleep(0, 500000);
      continue;
    }
    error = center - locationLine;
    P = kP*error;
    if(P>0){//left turn
      set_motor(1, 35));
      set_motor(2, 35+P);
      Sleep(0, 50000);
    }else if(P<0){//right turn
      set_motor(1, 35-P);
      set_motor(2, 35);
      Sleep(0, 50000);
    }
  }
  return 0;
}
