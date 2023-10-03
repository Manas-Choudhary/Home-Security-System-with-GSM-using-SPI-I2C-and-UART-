int LED = 13; // Use the onboard Uno LED
int isObstaclePin = 4; // This is our input pin
int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE
char data_rcvd[10];
void setup() 
{
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
  }

  else
  {
    Serial.println("clear");
    digitalWrite(LED, LOW);
  }
  delay(200);

  if (Serial.available()) 
  {
    data_rcvd[]= Serial.read();  
	  Serial.println(data_rcvd);
    if (data_rcvd[] == 'clear') 
    {
      digitalWrite(8, HIGH); // switch LED On
    }

  }
  if (digitalRead(9) == HIGH) 
    Serial.write('1');    // send the char '0' to serial if button is not pressed.
  else 
    Serial.write('0');                           // send the char '1' to serial if button is pressed.
}
