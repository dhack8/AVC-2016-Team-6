/*
Just some pseudo code i (david) am putting togethet based on lectures and what i think up in the shower :D
*/
//Includes and extern stuff here
int main(){
  bool hasLine = true;
  int sum = 0;
  int locationLine;
  int center = 160;
  int range = 0;
  int error = 0;
  int numFound = 0;
  int p = 0; //pixel variable
  int minP;
  int maxP;
  int lineWidth = 10;//dont actully know what the line width will be but this value should be slightly larger then the line with in pixels
  while(true){//loops forever
    while(hasLine){//loops while robot has line
      sum = 0; //reset sum
      take_picture();
      minP = 319;
      maxP = 0;
      for(int i = 0; i<320; i++){ // loop across image
        p = get_pixel(120,i,3); // p equals pixel
        if(p>240){ p = 255; } else { p = 0; } // flattens anything that isnt COMPLETElY white to 0 (black)
        if(p == 255){ //if pixel was white
          sum = sum + i; //add i location to sum
          numFound++; //increment number of white pixels found
          if(i< minP){ //code to find the rangeof white pixels found
            minP = i;
          }else if(i>maxP){
            maxP = i;
          }
        }
      }//exit of for loop
      if(numFound != 0){
        locationLine = sum/numFound; // finds middle of white line
      }else{
        locationLine = 0;
      }
      range = maxP -minP;
      error = center - locationLine;
      if(locationLine == 0 && /*left sensor has wall*/){ //code for entering the fourth quad
        hasLine = false;
        continue;
      }else if(/*front sensor has object*/ && locationLine != 0){ //if we have a ine but theres a wall
        /*code for stopping the robot and opening the gate goes here*/
      }else if((locationLine<(center-(linewidth/2))) || (locationLine>(center-(linewidth/2)) && locationLine<(center+(linewidth/2)) && range>300)){ //this is either a T or 4 way junction or a 90 degree left turn (this might catch sharp left turns to)
        /*code for turning 90 degrees left*/
      }else if(locationLine>(center+(linewidth/2))){ //this is a 90 degree right turn
        /*code for turning 90 degrees right*/
      }else if(locationLine == 0 && /*left sensor has nothing*/ && /*front sensor has nothing*/){ //lost line, no wall and no gate
        /*code for turning 180 degrees*/
      }else{ //just an normal line
        if(error<-3){ //rightish turn
          /*code that makes the left wheel slightly faster then right depending on magnitude of error*/
        }else if(error>3){ //leftish turn
          /*code that makes the right wheel slightly faster then left depending on magnitude of error*/
        }else{ // close enough to center just go straight
          /*code that puts both wheels to same speed*/
        }
      }
    }//none wall maze loop ends
  }
  return 0;
}
