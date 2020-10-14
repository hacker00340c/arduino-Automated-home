
    //esp8266
#include <SoftwareSerial.h>
SoftwareSerial esp8266(2,3);
#define DEBUG true
#define led_pin 3 

//servo
#include <Servo.h>
Servo myservo_sanitizer;
Servo myservo_tap; 

//ultrasonic

#define trig1  5
#define echo1  6
#define trig2  10
#define echo2  11
#define trig3  12
#define echo3  13
#define buzzpin 5



void setup() { 
  //servo
myservo_sanitizer.attach(9); 
myservo_tap.attach(7);
  
  //ulttrasonic 
    Serial.begin(9600);  
  Serial.println("Initialising..!!");
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  
  //esp8266
  pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);
    Serial.begin(9600);
    esp8266.begin(115200); //Baud rate for communicating with ESP8266. Your's might be different.
    esp8266Serial("AT+RST\r\n", 5000, DEBUG); // Reset the ESP8266
    esp8266Serial("AT+CWMODE=1\r\n", 5000, DEBUG); //Set station mode Operation
    esp8266Serial("AT+CWJAP=\"SSID\",\"Password\"\r\n", 5000, DEBUG);//Enter your WiFi network's SSID and Password.
                                   
    while(!esp8266.find("OK")) 
    {
      }
    esp8266Serial("AT+CIFSR\r\n", 5000, DEBUG);//You will get the IP Address of the ESP8266 from this command. 
    esp8266Serial("AT+CIPMUX=1\r\n", 5000, DEBUG);
    esp8266Serial("AT+CIPSERVER=1,80\r\n", 5000, DEBUG);
  
}
void loop() {
  
//ultrasonic installation
long duration1, distance1; // start the scan
  digitalWrite(trig1, LOW); 
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trig1, HIGH); 
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = (duration1/2) / 29.1;// convert the distance to centimeters.

  long duration2, distance2; // start the scan
  digitalWrite(trig2, LOW); 
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trig2, HIGH); 
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = (duration2/2) / 29.1;  // convert the distance to centimeters.

  long duration3, distance3; // start the scan
  digitalWrite(trig3, LOW); 
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trig3, HIGH); 
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trig3, LOW);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = (duration3/2) / 29.1; // convert the distance to centimeters.

  
    //ultrasonic installation finish finish
  //ultrasonic cammanding
  
  if(distance1<7){
    digitalWrite(buzzpin,HIGH);
  }
  else{
    digitalWrite(buzzpin,LOW);
  }
  if(distance2<7){
    myservo_sanitizer.write(HIGH);
  }
  else{
    myservo_sanitizer.write(LOW);
  }
  if(distance3<7){
    myservo_tap.write(HIGH);
  }
  else{
    myservo_tap.write(LOW);
  }
    
    //esp8266
    if (esp8266.available())
      {
        if (esp8266.find("+IPD,"))
          {
            String msg;
            esp8266.find("?");
            msg = esp8266.readStringUntil(' ');
            String command1 = msg.substring(0, 3);
            String command2 = msg.substring(4);
                        
            if (DEBUG) 
              {
                Serial.println(command1);//Must print "led"
                Serial.println(command2);//Must print "ON" or "OFF"
              }
            delay(100);

              if (command2 == "ON") 
                    {
                      digitalWrite(led_pin, HIGH);
                    }
                   else 
                     {
                       digitalWrite(led_pin, LOW);
                     }
          }
      }
   }
  String esp8266Serial(String command, const int timeout, boolean debug)
  {
    String response = "";
    esp8266.print(command);
    long int time = millis();
    while ( (time + timeout) > millis())
      {
        while (esp8266.available())
          {
            char c = esp8266.read();
            response += c;
          }
      }
    if (debug)
      {
        Serial.print(response);
      }
    return response;
  }
 //ultrasonic finish
  // code finish
