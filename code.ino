
//SPI MASTER (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO 

#include<SPI.h>                             //Library for SPI 
#define LED 8
#define ipbutton 9
int buttonvalue;
int x;
void setup (void)
{
  pinMode(9, INPUT_PULLUP); // set push button pin as input
  pinMode(8, OUTPUT);      // set LED pin as output
  digitalWrite(8, LOW);    // switch off LED pin
  
  Serial.begin(115200);                   //Starts Serial Communication at Baud Rate 115200 
  pinMode(ipbutton,INPUT);                //Sets pin 2 as input 
  pinMode(LED,OUTPUT);                    //Sets pin 7 as Output
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS,HIGH);                  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)

  Serial.println("Press 1 for SPI communication");
  Serial.println("Press 2 for UART communication");
}

void loop(void)
{
  while (Serial.available() == 0)   
  {   }  
    int menuChoice = Serial.parseInt();
  switch (menuChoice) 
  {
    case 1:
    {
      byte Mastersend,Mastereceive;          
      buttonvalue = digitalRead(ipbutton);   //Reads the status of the pin 2
      if(buttonvalue == HIGH)                //Logic for Setting x value (To be sent to slave) depending upon input from pin 2
      {
        x = 1;
      }
      else
      {
        x = 0;
      }
      digitalWrite(SS, LOW);                  //Starts communication with Slave connected to master
      Mastersend = x;                            
      Mastereceive=SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave
      Serial.print(x);
      Serial.print(Mastereceive);
      if(Mastereceive == 0)                   //Logic for setting the LED output depending upon value received from slave
      {
        digitalWrite(LED,LOW);              //Sets pin 7 HIGH
        Serial.println("Master LED OFF");
      }
      else
      {
      digitalWrite(LED,HIGH);               //Sets pin 7 LOW
      Serial.println("Master LED ON");
      }
      delay(1000);
    }

    case 2:
    {
    if (Serial.available()) 
    {
      char data_rcvd = Serial.read();   // read one byte from serial buffer and save to data_rcvd
	    Serial.println(data_rcvd);
      if (data_rcvd == '1') 
      {
        digitalWrite(8, HIGH); // switch LED On
      }  
      if (data_rcvd == '0') 
      {
        digitalWrite(8, LOW);  // switch LED Off    
      }
    }
    if (digitalRead(9) == HIGH) 
      Serial.write('1');    // send the char '0' to serial if button is not pressed.
    else 
      Serial.write('0');                           // send the char '1' to serial if button is pressed.
    }
  }
}