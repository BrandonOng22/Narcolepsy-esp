#include <Arduino.h>
#define motor 0
#define batteryRead 4
#define lowBat 5
#define light 21
#define bluetooth 26
#define buzzer 32
#define snoozeIn 15
#define snoozeOut 14

void startup(int countDown) {
  for(int i = countDown; i>0; i--){
    digitalWrite(light, HIGH);      // startup() is to show the device is powering up
    delay(500);
    digitalWrite(light, LOW);
    delay(500);                
  }
  return;
}

void timer(int time1, int button, bool blutoo, int batRead){
  for(int i = 0; i<time1; i++){
    button = analogRead(snoozeIn);
    blutoo = digitalRead(bluetooth);
    batRead = analogRead(batteryRead);
    if(batteryRead < 750){
      digitalWrite(lowBat, HIGH);
    }
    else{
      digitalWrite(lowBat, LOW);
      Serial.println("Battery Low...");
    }
    if(button > 2500) {                    // if the button is pressed, then the timer will be reset to 0 seconds.
      i = 0;
      Serial.println("Button pressed! Resetting alarm.");
    }
    digitalWrite(light, HIGH);      // the blinking light is to show when each second goes by.
    delay(100);
    digitalWrite(light, LOW);
    delay(900);
    Serial.println(i);
    Serial.print(button);
    Serial.println("Pin 15 = ");
  } 
  Serial.println("Time's up! Alarm activated!");
  return;
}

void alarm(int time2, int button, bool blutoo, int batRead) {

  while(button < 2500){
    button = analogRead(snoozeIn);
    blutoo = digitalRead(bluetooth);
    batRead = analogRead(batteryRead);
    if(batteryRead < 750){
      digitalWrite(lowBat, HIGH);
    }
    else{
      digitalWrite(lowBat, LOW);
    }
    digitalWrite(motor, HIGH);
    digitalWrite(light, HIGH);
    digitalWrite(buzzer,  HIGH);       // The alarms, lights, and motor will go off and on at a period of half a second.
    delay(time2);
    digitalWrite(motor, LOW);
    digitalWrite(light, LOW);
    digitalWrite(buzzer, LOW);
    delay(time2);
  }
  Serial.println("Alarm Snoozed. Timer restarted.");
  return;
}

void setup() {
  Serial.begin(115200);

  pinMode(motor, OUTPUT);                 // Vibrating Motor
  pinMode(lowBat, OUTPUT);                // Low Battery Indicator LED
  pinMode(light, OUTPUT);                 // Lights                       -- All Output pins
  pinMode(buzzer, OUTPUT);                // Buzzer
  pinMode(snoozeOut, OUTPUT);             // Snooze button transmitter

  pinMode(batteryRead, INPUT);            // Reads the battery voltage
  pinMode(snoozeIn, INPUT);               // Snooze button reciever       -- All Input pins
  pinMode(bluetooth, INPUT);              // Sees if bluetooth is on

  digitalWrite(motor, LOW);               // Set all outputs to LOW after initializing them
  digitalWrite(lowBat, LOW); 
  digitalWrite(bluetooth, LOW);
  digitalWrite(buzzer, LOW);

  startup(5);                             // initialize the board and let it set up for about 5 seconds

  digitalWrite(light, HIGH);
  digitalWrite(snoozeOut, HIGH);
  digitalWrite(buzzer, HIGH);

}

void loop() {
  int time1 = 30;                         // time1 is how many seconds in the countdown until the alarm goes off
  int button = 0;                      // initializing button to snooze alarm
  int halfPeriod = 0.25;                   // 1/2 period is 1/2 of a millisecond making frequency equal to 1000Hz
  bool blutoo = LOW;      
  int batRead = 4095;          
  timer(time1, button, blutoo, batRead);  // timer() is for the countdown sequenc
  alarm(halfPeriod, button, blutoo, batRead);
}