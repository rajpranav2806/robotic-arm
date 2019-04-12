#include  <Servo.h>


// Create servo objects 
Servo servo1;
Servo servo2;

// Create names to the analog input pins 
int pin0 = A0;
int pin1 = A2;


// Setup of angle variables we have to use further down in the program 
int angle1;
int angle2;


// Setup of value variables we have to use further down in the program 
int value1;
int value2;


// Setup of limit values 
long int forservo1 = 2000;
long int forservo2 = 2000;


void setup() 
{ 
  // Attaches the servo on pins to the servo objects 
  Serial.begin(9600);
  servo1.attach(5);
  servo2.attach(6);
  servo1.write(90);
  servo2.write(90);
} 
 
void loop() 
{ 
  // read analog values from joysticks 
  value1 = analogRead(pin0);
  value2 = analogRead(pin1);
  Serial.print(value1);
  // 10 bit value is too big, so we change the scale from 0 - 1023 proportionately to 1 - 29 
  value1 = map(value1, 0, 1023, 1, 29);
  value2 = map(value2, 0, 1023, 1, 29);
  
  // it needs correction of positions, because joysticks are not very precise to stay exactly in the center  
  if(value1  <= 17 && value1 >= 13) // if value1 if between 13-17, then it's equal to 15 */
      value1 = 15;
  if(value2  <= 17 && value2 >= 13)
      value2 = 15;
    
  // Change initial value 'forservo' which is used to turn servo slower. This value has got very big scale.
  // We add or substract (depends on turning direction) difference between analog value and center from 'forservo'  
  forservo1 = forservo1 - (value1 - 15);
  forservo2 = forservo2 - (value2 - 15);
  
  // this part do not let variables 'forservo' go out of the limits 
  if(forservo1  < 1) // if forservo1 is less than 1, then it's equal to 1 
      forservo1 = 1;
  if(forservo1  > 2000) // if forservo1 is greater than 20000, then it's equal to 20000 
      forservo1 = 2000;
  if(forservo2  < 1) 
      forservo2 = 1;
  if(forservo2  > 2000)
      forservo2 = 2000;
  
  // change used value to angle of servo. Angles are adjusted during testing 
  angle1 = map(forservo1, 1, 2000, 0, 180);
  angle2 = map(forservo2, 1, 2000, 0, 180);
  
  // send angles to servos 
  Serial.println(angle1);
  servo1.write(angle1);
  servo2.write(angle2);
  delay(300);

}
