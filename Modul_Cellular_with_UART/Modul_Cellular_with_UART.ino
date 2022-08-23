#include <SoftwareSerial.h>
SoftwareSerial serial1(11, 10); //TX,RX


void setup(){
  Serial.begin(115200);
  serial1.begin(115200);  
}

void loop(){
  serial1.println("AT");//test
  serialupdate();
  serial1.println("AT+CSQ");//test kualitas sinyal 
  serialupdate();
  serial1.println("AT+CCID");//cek sim terpasang
  serialupdate();
  serial1.println("AT+CREG");//network terdaftar cek
  serialupdate();
  serial1.println("AT+SNFS=0");//mode earphone (1 microphone mode)
  serialupdate();
  serial1.println("AT+CRSL=2");//volume
  serialupdate();

  while(1)
  {
    if(serial1.available()){
      Serial.write(serial1.read());
      if (Serial.available())
      {
        serial1.write(Serial.read());
      }
    }
  }
}

void serialupdate(){
  delay(2000);
  while (Serial.available()){
    serial1.write(Serial.read());//forward serial to software serial port
  }
  while(serial1.available()){
    Serial.write(serial1.read());//forward software serial to serialport
  }
}
