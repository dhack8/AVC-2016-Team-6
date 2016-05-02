//includes
#include <stdio.h>
#include <time.h>
#include <string.h>


extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red, char green, char blue);
extern "C" set_motor(int motor, int speed);
extern "C" Sleep(int sec, int usec);
extern "C" read_analog(int ch_adc);
extern "C" write_digital(int chan, int direct);
extern "C" read_digital(int chan);

int main(){
  bool hasLine = true;
  int sum = 0;
  int error = 0;
  int range = 0;
  int pixel = 0;
  int minP = 319;
  int maxP = 0;
  int center = 160;
  
  while(true){
  
  for(pixelWidth = 0; pixelWidth < 160; pixelWidth++){
    for(pixelHeight = 0; pixelHeight < 120; pixelHeight++){
      take_picture();
      pixel = get_pixel(pixelWidth, pixelHeight, 3);
        if (pixel>240){
          pixel = 255
        }else {
          pixel = 0
        }
        if (pixel = 255){
          sum = sum + pixelHeight
          numFound++;
          if(pixelWidth< minP){ //code to find the rangeof white pixels found
            minP = pixelWidth;
          }else if(pixelWidth>maxP){
            maxP = pixelWidth;
          }
        }
      }
      pixelWidth++;
    }
  }
  if(numFound != 0){
        locationLine = sum/numFound; // finds middle of white line
      }else{
        locationLine = 0;
      }
      range = maxP -minP;
      error = center - locationLine;

  return 0;
}

int movement(int usec, int speed){
  //will make the robot go forward
  set_motor(1, 255);
  set_motor(2, -255);
  
  return 0;
}

int imageProcessing(){
  return 0;
}
