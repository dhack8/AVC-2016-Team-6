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
  bool hasLine = true;
  bool inMaze = false;
  int sum = 0;
  int error = 0;
  int range = 0;
  int pixel = 0;
  int minP = 319;
  int maxP = 0;
  int center = 160;
  int pixelWidth = 0;
  int numFound = 0;
  int locationLine = 0;
  float Kp = 0.5; // proportinalalty thing
 
  init(0);
   
  while(true){ //The program never makes it back to this loop, even though hasLine becomes true. Should use a method instead or "class member functions" as they are called in C++
  
  for(pixelWidth = 0; pixelWidth < 320; pixelWidth++){
    take_picture();
    pixel = get_pixel(pixelWidth, 1, 3);
    
      if (pixel>127){
        pixel = 255;
      }else {
         pixel = 0;
       }
       if (pixel == 255){
        numFound++;
        if(pixelWidth< minP){ //code to find the rangeof white pixels found, used for t junc
          minP = pixelWidth;
        }else if(pixelWidth>maxP){
           maxP = pixelWidth;
        }
       }
     }
     hasLine = false;
   }
  
  if(numFound != 0){
    locationLine = sum/numFound; // finds middle of white line
  }else{
    locationLine = 0;
  }
  
  range = maxP -minP; // For T junc
  error = center - locationLine;
  
  porp
      
  bool is_negative = error < 0;
  bool is_positive = error > 0;
  

  if (is_negative){
   set_motor(1, 50);
    set_motor(2, -50);
    Sleep(0, 500000);
   error++;
  }else if(is_positive){
   set_motor(1, -50);
    set_motor(2, 50);
   Sleep(0, 500000);
   error--;
  }else{
   set_motor(1, 50;
   set_motor(2, 50);
  }

  return 0;
}

