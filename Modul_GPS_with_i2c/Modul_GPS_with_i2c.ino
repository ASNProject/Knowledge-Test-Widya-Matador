#include <Adafruit_GPS.h>

Adafruit_GPS GPS(&Wire);

void setup(){
  while (!Serial){}
  Serial.begin(115200);
  GPS.begin(0x10); //Alamat I2C
}

void loop(){
  if (Serial.available()){
    char c = Serial.read();
    GPS.write(c);
  }
  if (GPS.available()){
    char c = GPS.read();
    Serial.write(c);
  }
}
