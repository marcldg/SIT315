int pirPin = 2;  // the digital pin connected to the PIR sensor's output
int ledPin = 13; // the digital pin connected to the led

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
}

void loop()
{
  if(digitalRead(pirPin) == HIGH){
    digitalWrite(ledPin, HIGH); //turn on led
    Serial.println("Motion Detected"); //print motion on serial monitor
  }
  if(digitalRead(pirPin) == LOW){
    digitalWrite(ledPin, LOW); // turn off led
    Serial.println("No Motion"); //print no motion on serial monitor
  }      
}