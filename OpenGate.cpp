//Includes
# include <stdio.h>
# include <time.h>

//Externs
extern "C" int init(int d_lev);
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int main (){
   
   init(1);                                  //This sets up the RPi hardware and ensures everything is working correctly
   
   connect_to_server("130.195.6.196", 1024); //Connects to server with the ip address 130.195.6.196, port 1024
   send_to_server("Please");                 //Asks the connected server for the password (nicely)
   char pass[24];                            //Define the password variable
   receive_from_server(pass);                //Receives the password from the connected server
   send_to_server(pass);                     //Sends the password to the server
return 0;}
