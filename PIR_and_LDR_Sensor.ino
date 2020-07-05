#include "Countimer.h"
Countimer timer;

#define potentiometer  A0  //10k Variable Resistor
#define LDR_Pin A1 // choose the input pin (for LDR sensor) 
#define PIR_Pin A2 // choose the input pin (for PIR sensor)  

#define R_led 2 // choose the pin for the Red Led
#define G_led 3 // choose the pin for the Green Led
#define Relay 6 // choose the pin for the Relay moudel

int ldr, pir;
int Brightness;
int read_ADC;
int set_timer;
int seconds;
int Start =0;

void setup(){ // put your setup code here, to run once

Serial.begin(9600);// initialize serial communication at 9600 bits per second:

pinMode(potentiometer, INPUT); // declare potentiometer as input  
pinMode(LDR_Pin, INPUT); // declare sensor as input
pinMode(PIR_Pin, INPUT); // declare sensor as input

pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(G_led,OUTPUT); // declare Green LED as output
pinMode(Relay,OUTPUT); // declare Relay as output
digitalWrite(Relay, HIGH);// Relay Turn Off

timer.setInterval(print_time, 999);
delay(1000); // Waiting for a while
}

void print_time(){seconds = seconds+1;}

void loop(){
timer.run(); // Cell the (Countimer.h) file
  
read_ADC = analogRead(potentiometer); // read analogue to digital value 0 to 1023
set_timer = read_ADC /1.705; // Maximum value analogue to digital 1023 / 1.705

ldr = analogRead(LDR_Pin); // read analogue to digital value 0 to 1023
Brightness = ldr /10.23; // Maximum value analogue to digital 1023 / 10.23

pir = digitalRead(PIR_Pin);

Serial.print("Timer:");
Serial.println(set_timer);

Serial.print("LRD:");
Serial.println(Brightness);

Serial.print("PIR:");
Serial.println(pir);

if(Brightness<40){ // Brightness Down to 40 Start PIR Sensor Working
Start = 1;  
}

if(Brightness>70){ // Brightness Up to 70 Stop PIR Sensor Working
Start = 0;  
}

if(Start==1){ 
digitalWrite(R_led, HIGH); // LED Turn On 
if(pir==1){
Serial.println("Motion detected!");
digitalWrite(G_led, HIGH); // LED Turn On 
digitalWrite(Relay, LOW); // Relay Turn On 
seconds = 0; // Reset Timer  
timer.start(); // Start Timer 
}
else{
Serial.println("Motion stopped!");
digitalWrite(G_led, LOW); // LED Turn Off.  
}

if(seconds>set_timer){ // Up to Set poit for potentiometer
seconds = 0; // Reset Timer   
timer.stop(); // Stop Timer
digitalWrite(Relay, HIGH); // Relay Turn Off   
}
}

if(Start==0){ 
  digitalWrite(Relay, HIGH); // Relay Turn Off 
  digitalWrite(R_led, LOW); // LED Turn Off. 
  digitalWrite(G_led, LOW); // LED Turn Off.  
  timer.stop();
}

delay(100);
}
