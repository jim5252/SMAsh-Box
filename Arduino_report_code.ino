int ENA_PIN = 2;     // delares pin2 as input to enable motor A 
 int IN1_PIN = 3;    //  delares pin3 as input to enable motor A
 int IN2_PIN = 4;   //  delares pin4 as input to enable motor A

 int ENB_PIN = 7;   // declares pin 7 as input to enable motor B 
 int IN3_PIN = 5;   // declares pin 5 as input to enable motor B
 int IN4_PIN = 6;  // declares pin 6 as input to enable motor B

 int echopin = 10;  // declares pin 10 as detector for ultrasonic sensor 
 int trigpin = 9;      // declares pin 9 as trigger for ultrasonic sensor

 int detectpin = A7;      // declares pin A7 as the signal pin
 int value = 0;         // declares variable to hold reflectivity  
int threshold = 700;    // threshold to detect black spot (that is detected from’value’ moniter in later stage by ‘Serial.println’command)

long count,distance;      //

void setup() {

Serial.begin(9600);        //initiates serial channel
pinMode(trigpin,OUTPUT);  // declares the trigger pin of ultrasonic sensor as output
pinMode(echopin,INPUT);  // declares the echo pin of the ultrasonic sensor as outout

pinMode(detectpin,INPUT);     // declares the reflectivity detector as an input
  
pinMode(ENA_PIN,OUTPUT); // declares ENA_PIN as an output
pinMode(IN1_PIN,OUTPUT); // declares IN1_PIN as an output
pinMode(IN2_PIN,OUTPUT);// declares IN2_PIN as an output
pinMode(ENB_PIN,OUTPUT); // declares ENB_PIN as an output
pinMode(IN3_PIN,OUTPUT); // declares IN3_PIN as an output
pinMode(IN4_PIN,OUTPUT); // declares IN4_PIN as an output

digitalWrite(ENA_PIN,LOW); // Turns motor A off
digitalWrite(ENB_PIN,LOW);  // Turns motor B off

digitalWrite(trigpin,LOW);   //
delayMicroseconds(2);        //
}

void loop() {

digitalWrite(trigpin,HIGH);  // sets the trigger pin to send out a pulse
delayMicroseconds(10); // delays 10 microseconds before the trigger is turned off
digitalWrite(trigpin,LOW);  // trigger pin is turned off

count = pulseIn(echopin,HIGH);     // measures the time taken for an echo pulse to return
distance = count/58.2;    // calculates distance between sensor and obstacle
delay(50); // delays readings to stabilise the program

value = analogRead(detectpin);    // reads the value of the reflectivity detector

Serial.println(distance);    // prints value of distance to the serial monitor
Serial.println(value);  // prints the values recorded by the reflectivity detector to the serial monitor
delay(50); // delays readings to stabilise the program                                      

if(value<threshold){                  // if the floor is white
  if (distance <10&& distance !=0){    // if there is an obstacle between 0-10cm
    robot_stop();                                    // robot will stop moving
    delay(100);                // robot waits 0.1 seconds                       
    robot_backwards();        // robot moves backwards
    delay(200);   // robot waits 0.2 seconds
robot_left();        // robot turns left
  }else{  // if there is not an obstacle between 0-10cm
    robot_forwards();      //robot will move forwards
}
else{     // if value from the reflectivity reading is greater than the threshold (black)
  robot_stop();  // the robot will stop moving                                             
  }
}
void robot_forwards(){    // moves the robot forwards
  digitalWrite(IN1_PIN,LOW);  // motor A reverse motion OFF
  digitalWrite(IN2_PIN,HIGH);  // motor A forward motion ON
 analogWrite(ENA_PIN,200);   //  motor A at max speed      

 digitalWrite(IN3_PIN,LOW);  // motor B reverse motion OFF      
  digitalWrite(IN4_PIN,HIGH);  // motor B forward motion ON
 analogWrite(ENB_PIN,200);   //  motor B at max speed  

  }
  
void robot_stop(){  // stops the robot
  digitalWrite(ENA_PIN, LOW);     // motor A OFF
  digitalWrite(ENB_PIN, LOW);    // motor B OFF
  }
  
  void robot_left(){    // turns the robot left
 digitalWrite(IN1_PIN,HIGH);      // motor A reverse motion ON  
  digitalWrite(IN2_PIN,LOW);    // motor A forward motion OFF          
 analogWrite(ENA_PIN,200);       // motor A at max speed

 digitalWrite(IN3_PIN,LOW);    // motor B reverse motion OFF               
  digitalWrite(IN4_PIN,HIGH);   // motor B forward motion ON          
 analogWrite(ENB_PIN,200);       // motor B at max speed 
  }

void robot_backwards(){   // moves robot backwards
  digitalWrite(IN1_PIN,HIGH);        // motor A reverse motion ON         
  digitalWrite(IN2_PIN,LOW);         // motor A forward motion OFF
 analogWrite(ENA_PIN,200);         // motor A at max speed 

 digitalWrite(IN3_PIN,HIGH);       // motor B reverse motion ON           
  digitalWrite(IN4_PIN,LOW);      // motor B forward motion OFF          
 analogWrite(ENB_PIN,200);        // motor B at max speed

  }

