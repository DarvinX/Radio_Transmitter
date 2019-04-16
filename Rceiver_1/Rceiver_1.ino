/* 
 *  This is the final code for transmitter of DIY 2.4 GHz radio Transmitter-Receiver 
 *  define the pins of the connected joysticks in the macros
 *  pin 8,7,11,12 and 13 are reserved for nrf24 spi connection
 *  
 *  written by Tamal Hansda, 14-03-2019
 */
 
#include <SPI.h>
#include "RF24.h"

//output pins
#define CH1 9
#define CH2 6
#define CH3 5
#define CH4 2
#define CH5  
#define CH6 

RF24 radio(8,7); //chip enable and chipe select pins
byte address[][6] = {"0"}; //same address as sete on the transmitter

//transmitter transmittes data as a package
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
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  radio.begin();
  radio.setChannel(120);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, address[0]);
  radio.startListening();
  delay(1000);
}

void loop() {
  if(radio.available()){ //whene connection is available
    radio.read(&data,sizeof(data));//read data
    
    //getting the packet data and printing them
    Serial.print(data.left_X);       Serial.print("  ");
    Serial.print(data.left_Y);       Serial.print("  ");
    Serial.print(data.right_X);      Serial.print("  ");
    Serial.print(data.right_Y);      Serial.print("  ");
    Serial.print(data.left_button);  Serial.print("  ");
    Serial.print(data.right_button); Serial.println(""); 

    //use the packet values to handle the pin state
  }
}
