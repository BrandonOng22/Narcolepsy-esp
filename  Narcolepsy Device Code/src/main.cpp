#include <Arduino.h>
#define motor 0
#define powerLED 4
#define lowBat 5
#define light 21
#define unknown 26
#define buzzer 32
#define snoozeIn 15
#define snoozeOut 14

void startup(int cd1) {
  for(int i = cd1; i>0; i--){
    digitalWrite(powerLED, HIGH);      // startup() is to show the device is powering up
    delay(500);
    digitalWrite(powerLED, LOW);
    delay(500);                
  }
  return;
}

void timer(int cd2){
  bool buttonSnooze = LOW;
  for(int i = 0; i<cd2; i++){
    buttonSnooze = digitalRead(snoozeIn);
    if(buttonSnooze) {          // if the button is pressed, then the timer will be reset to 0 seconds.
      i = 0;
    }
    digitalWrite(light, HIGH);     // the blinking light is to show when each second goes by.
    delay(100);
    digitalWrite(light, LOW);
    delay(900);
  }
  return;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  startup(5);                 // initialize the board and let it set up for about 5 seconds
  pinMode(motor, OUTPUT); // Vibrating Motor
  pinMode(powerLED, OUTPUT); // Power LED
  pinMode(lowBat, OUTPUT); // Low Battery Indicator LED
  pinMode(light, OUTPUT); // Lights
  pinMode(unknown, OUTPUT); //  ???
  pinMode(buzzer, OUTPUT); // Buzzer
  pinMode(snoozeIn, INPUT);  // Snooze button reciever
  pinMode(snoozeOut, OUTPUT); // Snooze button transmitter

  digitalWrite(motor, LOW); // Set all outputs to LOW after initializing them
  digitalWrite(lowBat, LOW); 
  digitalWrite(light, LOW);
  digitalWrite(unknown, LOW);
  digitalWrite(buzzer, LOW);

  digitalWrite(powerLED, HIGH);
  digitalWrite(snoozeOut, HIGH);
}

void loop() {
  int time1 = 60;              // time1 is how many seconds in the countdown until the alarm goes off
  bool button = LOW;              // initializing button to snooze alarm
  int halfPeriod = 250;                // 1/2 period is 1/4 of a second
  timer(time1);                // timer() is for the countdown sequence

  while(button = LOW){
    button = digitalRead(snoozeIn);
    digitalWrite(motor, HIGH);
    digitalWrite(light, HIGH);
    digitalWrite(unknown, HIGH);
    digitalWrite(buzzer, HIGH);     // The alarms, lights, and motor will go off and on at a period of half a second.
    delay(halfPeriod);
    digitalWrite(motor, HIGH);
    digitalWrite(light, HIGH);
    digitalWrite(unknown, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(halfPeriod);
  }
}