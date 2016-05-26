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
extern "C" void set_pixel(int col, int row, char red,char green,$

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
  int numfound;    
  int numfoundleft;
  int numfoundright;
  int pixel;
  int pixell;
  int pixelr;
  int THRESH = 110;
  while(true){  
   numfound = 0;    
   numfoundleft = 0; 
   numfoundright = 0;
   take_picture();
   open_screen_stream();

for(int i = 0; i < 320; i++){ 
     pixel = get_pixel(i, 40, 3);
     set_pixel(i, 40, 0, 0, 254);
     if(pixel > THRESH){
      numfound++;
     }
   }
   for(int o = 0; o<240; o++){    
     pixell = get_pixel(40, o, 3);
     pixelr = get_pixel(280, o, 3);
     set_pixel(40, o, 0, 254, 0);
     set_pixel(280, o, 254,0,0);
     if(pixell > THRESH){
       numfoundleft++;
     }
     if(pixelr > THRESH){
       numfoundright++;
     }
   }
   update_screen();
   printf("num found: %d \n", numfound);
   printf("num found left: %d \n", numfoundleft);
   printf("num found right: %d \n", numfoundright);
 }
return 0;
}
