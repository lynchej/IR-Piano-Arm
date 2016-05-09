#include <Servo.h> 
#include <IRremote.h>

int RECV_PIN = 12;
int Number = 0xC098;
IRrecv irrecv(RECV_PIN);

decode_results results;
/*
 * Initializes the servo motors, as well as the callibration for each
 */
Servo middle, left, right, claw;
int leftCallib = 45;
int rightCallib = 45;
int middleCallib = 90;
int clawCallib = 0;

/*
 * Initializes each servo to its output pin on the arduino uno
 */
void setup() {
  Serial.begin(9600);
  middle.attach(11);
  left.attach(10);
  right.attach(9);
  claw.attach(6);

  Serial.begin(9600);
  irrecv.enableIRIn();
}

/*
 * Inputs: x is the desired location and y is the current location
 * rotates the middle servo in the base to the desired location
 */
void turn(int x, int y){
  int i = y;
  while(i <= x){
    middle.write(i);
    delay(50);
    i = i + 5;
  }
}

/*
 * raises the left and right arm to desired locations
 * which readies the arm to play the piano
 */
void up(){
  int i = 45;
  int j = 45;
  while(i > 0 && j < 90){
    left.write(j);
    right.write(i);
    delay(50);
    i = i - 5;
    j = j + 5;
  }
}

/*
 * Inputs: x is the desired location, y is the desired location
 * rotates the crane back towards the callibration location
 */
void turnBack(int x, int y){
  int i = x;
  while(i > y){
    middle.write(i);
    delay(50);
    i = i - 5;
  }
}

/*
 * lowers the left and right arms to play a note on the piano
 */
void playNote(){
  left.write(0);
  right.write(90);
  delay(1000);
  
 
}
/*
 * uses playNote, up, turn, and turnBack in order to play
 * the desired notes (a C major tetrachord)
 */
void playTetra(){
  int x = 90; //initiatlizes the current position for use in turn
  int y = 65; //initializes the first desired position for turnBack
  int z = 90; //initializes the first current position for turnBack
  
  up(); //sets arms to playing position
  delay(1000); 
  turn(x, 0); //resets the base to the playing position
  delay(1000);
  playNote(); //runs the playNote function to play 'C'
  delay(1000);
  
  up(); 
  delay(1000);
  turnBack(z, y); //turns the arm towards the next note that will be played
  delay(1000);
  playNote(); //runs the playNote function to play 'D'
  z = y; //stores the current location for turnBack
  y = 55; //sets the next location for the crane
  delay(1000);
  
  up();
  delay(1000);
  turnBack(z, y);
  delay(1000);
  playNote(); //runs the playNote function to play 'E'
  z = y;
  y = 40;
  delay(1000);
  
  up();
  delay(1000);
  turnBack(z, y);
  delay(1000);
  playNote(); //runs the playNote function to play 'F'
 
}

/*
 * Loops the playTetra function to play the desired notes
 * currently playing a C major tetrachord
 */

void loop() {
  if(irrecv.decode(&results)){
   // Serial.println(results.value, HEX);
    Serial.println(results.value);
      while(results.value == 49304){
        playTetra();
        delay(2000);
        irrecv.resume();
      }
      
      if(results.value == 49304){
          playTetra();
          delay(2000);
          results.value = 0;
      }
  }

  }
