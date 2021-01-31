//(c) Arnov Sharma

#include <SoftSerial.h>    

#define RxD 1
#define TxD 0

SoftSerial blueToothSerial(RxD,TxD);

int led = 2 ;
 
void setup() 
{ 
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  
  pinMode(led,OUTPUT);
} 
 
void loop() 
{ 
  char recvChar;
  while(1){
    //check if there's any data sent from the remote bluetooth shield
    if(blueToothSerial.available()){
      recvChar = blueToothSerial.read();

        switch(recvChar)
      {
        case '1': digitalWrite(led,LOW); break; // the relay coil energizes when In1 of the relay board is LOW
        case '0': digitalWrite(led,HIGH); break; 
        default : break;
      }
    }
  }
} 
 
void setupBlueToothConnection()
{
  blueToothSerial.begin(9600); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=HC-05\r\n"); //set the bluetooth name as "HC-05"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  
  delay(2000); // This delay is required.
  
  blueToothSerial.print("bluetooth connected!\n");
  
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}
