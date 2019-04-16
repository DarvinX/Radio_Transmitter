/* 
 *  This is the final code for transmitter of DIY 2.4 GHz radio Transmitter-Receiver 
 *  define the pins of the connected joysticks in the macros
 *  pin 9,10,11,12 and 13 are reserved for nrf24 spi connection
 *  
 *  written by Tamal Hansda, 14-03-2019
 */

#include <SPI.h>
#include "RF24.h"

//joystick pins
#define left_X_pin        A2
#define left_Y_pin        A3
#define left_button_pin   3
#define right_X_pin       A0
#define right_Y_pin       A1
#define right_button_pin  2

RF24 radio(9,10); //chipe enable and chipe select pin
byte address[][6] = {"0"};

//arrange transmitter state in a single package
struct package {
  int left_X = 0;
  int left_Y = 0;
  bool left_button = true;
  int right_X = 0;
  int right_Y = 0;
  bool right_button = true;
};

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(115200);
  
  //defining input pins
  pinMode(right_button_pin,INPUT);  digitalWrite(right_button_pin,HIGH);
  pinMode(left_button_pin,INPUT);   digitalWrite(left_button_pin,HIGH);
  pinMode(right_X_pin,INPUT);
  pinMode(right_Y_pin,INPUT);
  pinMode(left_X_pin,INPUT);
  pinMode(left_Y_pin,INPUT);

  //configure the nrf24l01
  radio.begin();
  radio.setChannel(120);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address[0]);
  delay(1000);
}

void loop() {
  
  //get input fron both joystick
  data.left_X        = analogRead(left_X_pin);
  data.left_Y        = analogRead(left_Y_pin);
  data.left_button   = digitalRead(left_button_pin);
  data.right_X       = analogRead(right_X_pin);
  data.right_Y       = analogRead(right_Y_pin);
  data.right_button  = digitalRead(right_button_pin);

  //printing values for debugging
  Serial.print(data.left_X);       Serial.print("  ");
  Serial.print(data.left_Y);       Serial.print("  ");
  Serial.print(data.right_X);      Serial.print("  ");
  Serial.print(data.right_Y);      Serial.print("  ");
  Serial.print(data.left_button);  Serial.print("  ");
  Serial.print(data.right_button); Serial.println("");

  radio.write(&data, sizeof(data)); //sending the data
}
