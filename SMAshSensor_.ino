#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <BridgeSSLClient.h>
#include <BridgeUdp.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <YunClient.h>
#include <YunServer.h>

#include <Process.h>

#include <dht.h>

#include <Password.h>//use password library
#include <Keypad.h>


#define SensorPin A2          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;


int val;
int tempPin = A4;


const int read = A5; //Sensor AO pin to Arduino pin A0
int value;          //Variable to store the incomming data


dht DHT;
#define DHT11_PIN 13


float cel;
int Level;
float HmV;
float phValue;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 1}; //connect to the column pinouts of the keypad

#define RELAY1 8 //Defining the pin 8 of the Arduino for the 4 relay module
 #define RELAY2 9 //Defining the pin 9 of the Arduino for the 4 relay module
 #define RELAY3 10 //Defining the pin 10 of the Arduino for the 4 relay module
 #define RELAY4 11 //Defining the pin 11 of the Arduino for the 4 relay module

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte RELAY1 = 8;       
byte Relay15 = 9;       
boolean ledPin_state;
boolean state1 = false;
boolean state2 = false;





void setup() {  
{
    Bridge.begin();
    Console.begin();
    while(!Console);
    
    runCurl();    
}
 {
 pinMode(RELAY1, OUTPUT); //Defining the pin 8 of the Arduino as output
 pinMode(RELAY2, OUTPUT); //Defining the pin 9 of the Arduino as output
 pinMode(RELAY3, OUTPUT); //Defining the pin 10 of the Arduino as output
 pinMode(RELAY4, OUTPUT); //Defining the pin 11 of the Arduino as output
 }
}

void loop()
{
  {
val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
cel = mv/10;
float farh = (cel*9)/5 + 32;

Console.print("Temperature = ");
Console.print(cel);
Console.print("*C");
Console.println();
delay(1000);

}

if (cel < 15 ){
  digitalWrite (RELAY1, HIGH); // turn water heater on
}
else {
  digitalWrite (RELAY1, LOW); // turn water heater off
}
if (cel > 30 ){
  digitalWrite (RELAY1, LOW); // turn water heater on
}
 else{
  digitalWrite (RELAY, HIGH); // turn water heater off
 delay (1000); 
 }
 


{
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }


{
  value = analogRead(read); //Read data from analog pin and store it to value variable
  
  if (value<=480){ 
    Console.println("Water level: 0mm - Empty!");
    Level=0; 
  }
  else if (value>480 && value<=530){ 
    Console.println("Water level: 0mm to 5mm"); 
    Level=2.5;
  }
  else if (value>530 && value<=615){ 
    Console.println("Water level: 5mm to 10mm"); 
    Level=7.5;
  }
  else if (value>615 && value<=660){ 
    Console.println("Water level: 10mm to 15mm"); 
        Level=12.5; 
  } 
  else if (value>660 && value<=680){ 
    Console.println("Water level: 15mm to 20mm"); 
    Level=17.5;
  }
  else if (value>680 && value<=690){ 
    Console.println("Water level: 20mm to 25mm"); 
    Level=22.5;
  }
  else if (value>690 && value<=700){ 
    Console.println("Water level: 25mm to 30mm"); 
    Level=27.5;
  }
  else if (value>700 && value<=705){ 
    Console.println("Water level: 30mm to 35mm");
    Level=32.5; 
  }
  else if (value>705){ 
    Console.println("Water level: 35mm to 40mm"); 
    Level=37.5;
  }
  
  delay(5000); // Check for new value every 5 sec
}

if (value < 680){
  digitalWrite (RELAY2, HIGH); // turn water pump on
}
else{
  digitalWrite (RELAY2, LOW); // turn water pump off
}
if (value > 705 ){
  digitalWrite (RELAY2, LOW); // turn water pump on
}
else {
  digitalWrite (RELAY 2, HIGH); // turn water pump off
delay (1000);
}

{
  int chk = DHT.read11(DHT11_PIN);
  Console.print("Humidity (%) = ");
  HmV=DHT.humidity;
  Console.println(HmV);
  delay(1000);
}

{
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  Console.print("    pH:");  
  Console.print(phValue,2);
  Console.println(" ");
  

}

}

{
 char key = keypad.getKey();
 
if (key){
   Console.println(key);

if (key == '1')  {
     state1 = !state1;
     if (state1) {
          digitalWrite(RELAY1,HIGH); // turn heater on
      } else {
          digitalWrite(RELAY1,LOW); // turn heater off
      }
 } 
if (key == '2')  {
     state2 = !state2;
     if (state2) {
          digitalWrite(RELAY2,HIGH); // turn pump on
      } else {
          digitalWrite(RELAY2,LOW); // turn pump off
      }
 } 
    }                 
   }


void runCurl() {
  Process XX;        // Create a process and call it "p"
  XX.begin("curl");  // Process that launch the "curl" command
  XX.addParameter("http://dweet.io/dweet/for/SMAsh-Box?temp="+String(cel,2)+"&Displacement="+String(Level,2)+"&pH="+String(phValue,2)+"&Humidity="+String(HmV,2)+"&SinceRun="+String(millis())  ); 
 // Add the URL parameter to "curl"
  XX.run();      // Run the process and wait for its termination
  while (XX.available()>0) {
    char c = XX.read();
    Console.print(c);
  }
  Console.flush();
}






 

