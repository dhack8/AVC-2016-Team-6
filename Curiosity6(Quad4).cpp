#include <stdio.h>
#include <time.h>

\\these load specific methods from the ENGR101 library
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
    int adc_reading;
    int sensors = 3;
    for(int i = 0; i < sensors; i++){
      adc_reading = read_analog(i);
      printf("sensor"+i+": %d\n",adc_reading);
      Sleep(0,500000); 
    }
    }
return 0;}
