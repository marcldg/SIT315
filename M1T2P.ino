int pirPin = 2;  // the digital pin connected to the PIR sensor's output
int ledPin = 13; // the digital pin connected to the led
volatile int state = LOW; // state changes on something that the program can't predict -- motion from user

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pirPin), interruptChange, RISING);
}

void loop()
{
  if(state == HIGH){
    digitalWrite(ledPin, HIGH); //turn on led
    delay(500);
    state = LOW; // set the state to LOW
    digitalWrite(ledPin, LOW);
  }
}

void interruptChange(){
  	state = HIGH; // interrupt and changes the state to HIGH
  	Serial.println("Motion Detected !");
  }
  