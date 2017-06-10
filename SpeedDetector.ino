// The sensor send and recieve code is based off David Mellis and Tom Igoe's code PING)))

// Created by Jacob Gus June 9th 2017

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 7;



void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  
  // establish variables for duration of the ping,
  // and the distance result in inches:
  float duration1, duration2, inches1, inches2, differencePost, differencePreABS, distanceA, distanceB, startTime, elapsedTime, elapsedSeconds, FPS, IPS, MPH;
  
if (1){ 
  //Value 1 starts here 
  
  //Start the timmer 
  startTime = millis();
  
  // PING triggered
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(20000);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(20000);
  digitalWrite(pingPin, LOW);

  //Listen for PING back on same pin
  pinMode(pingPin, INPUT);
  duration1 = pulseIn(pingPin, HIGH);

 //End of Value 1

  delay(100);

 //Value 2 Starts here
 
 // PING triggered
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(20000);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(20000);
  digitalWrite(pingPin, LOW);

  //Listen for PING back on same pin
  pinMode(pingPin, INPUT);
  duration2 = pulseIn(pingPin, HIGH);

  //End of Value 2

  //Take the elapsed time between millis started and stopped and subtract it
  elapsedTime = millis() - startTime;

  //Divide by 1000 to change milliseconds into seconds
  elapsedSeconds = (elapsedTime / 1000);


}
  // convert the first time into a distance
  inches1 = microsecondsToInches(duration1);

  //set our distance of Value 1 
  distanceA = inches1;
  
  //convert the second time into a distance
  inches2 = microsecondsToInches(duration2);

  //set our distance  of Value 2
  distanceB = inches2;

  //Find difference in distance A and B
  differencePreABS = distanceA - distanceB;

//Find absolute value of distance incase the object is moving in a direction that would produce a negative number
if (differencePreABS < 0){
  differencePost = differencePreABS * -1;
  }
  else{
    differencePost = differencePreABS * 1;
  }
//IPS = Inches Per Second, FPS = Feet Per Second, MPH = Miles Per Hour

//Find our Inches Per Second
  IPS = (differencePost / elapsedSeconds);

  //Divide by Inches Per Second by 12 to get Feet Per second
  FPS = (IPS / 12);

  //Multiple Feet Per Second by .6818 to get Miles Per Hour
  MPH = (FPS * .6818);

  //Print all the data 
  Serial.print("Speed in MPH: ");
  Serial.print(MPH);
  Serial.println();
  Serial.print("________________________________________________");
  Serial.println();
  
  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

