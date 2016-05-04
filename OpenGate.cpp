# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int main (){
   // This sets up the RPi hardware and ensures
   // everything is working correctly
   init(1);
   //connects to server with the ip address 130.195.6.196, port 1024
   connect_to_server("130.195.6.196", 1024);
   //Asks the connected server for the password (nicely)
   send_to_server("Please");
   //receives the password from the connected server
   char pass[24];
   receive_from_server(pass);
   send_to_server(pass);
return 0;}
