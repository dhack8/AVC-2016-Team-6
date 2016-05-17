//Make an error signal out of the average of the two side sensors.
sideSensors = (rightSensorFront + rightSensorBack)/2
sideErrorSignal = sideSensors - numberThatMakesTheValue0WhenItIsTheCorrectDistance
  //This is because when driving straight we want to keep the wall a set distance away (PID)
    //insert PID straight driving code from quads 1 and 2 but use sideErrorSignal instead of the line error signal
  //until the front sensor is close to a wall
    if(frontSensor<closeDistanceThreshold){
      //if the right sensors sense a wall, turn left. If not , turn right.
      if(sideSensorFront<closeDistanceThreshold){
        //turn left
          //Semi-hardcoded turn until sensors are around the right distance/parrallel 
      }
      else{
        //turn right
          //Semi-hardcoded turn until sensors are around the right distance/parrallel 
      }
      //then back to the PID until another corner is found
  }
  
