/*
New code taking a more simple approach to turning
*/
int main(){
  bool hasLine = true;
  bool inMaze = false;
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
  while(true){
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
        inMaze = true;
        continue;
      }else if(/*front sensor has object*/ && locationLine != 0){ //if we have a ine but theres a wall
        /*code for stopping the robot and opening the gate goes here*/
      }else if((locationLine<(center-(linewidth/2))) || (locationLine>(center-(linewidth/2)) && locationLine<(center+(linewidth/2)) && range>300)){ //this is either a T or 4 way junction or a 90 degree left turn (this might catch sharp left turns to)
        /*code for small turns left, will keep doing it til line is in the middle*/
      }else if(locationLine>(center+(linewidth/2))){
        /*code for turning small turns right, will repeat till line is back in center*/
      }else if(locationLine == 0 && /*left sensor has nothing*/ && /*front sensor has nothing*/){ //lost line, no wall and no gate
        /*coe for small turns will kepp going till line is picked up on scanner, at that point previous two else if will take controll*/
      }else{ //line is in center
        /* go forward*/
      }
    }
  }
}

