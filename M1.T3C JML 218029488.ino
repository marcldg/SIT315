//Pins
volatile int orange = 0; // state changes on something that the program can't predict -- motion from user
volatile int blue = 0; // state changes on something that the program can't predict -- motion from user

// Set up pins and enable the serial monitor to display info.
void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT); // Setting the pin 11 to output 5V
  pinMode(12, OUTPUT); // Setting the pin 12 to output 5V
  pinMode(2, INPUT); // Setting the pin 2 as an input
  pinMode(4, INPUT); // Setting the pin 4 as an input
  
  PCICR |= 0b00000111; // opening all the ports for interrupts
  PCMSK2 |= 0b10010100; // enabling pins 2 and 4 for interrupts
}

void loop()
{
  digitalWrite(12, blue);
  digitalWrite(11, orange);
  // when the value of 4 is returned this means the blue led has been powered on
  if(blue == 4){
    Serial.println("Left Sensor Activated"); // print to console
  }
  // when the value of 16 is returned this means the blue led has been powered on
  if(orange == 16){
    Serial.println("Right Sensor Activated"); // print to console
  }
}

// Setting up Interrupt Service Routine (ISR) for the PCINT2 interrupt vector
ISR(PCINT2_vect) {
  blue = PIND & B00000100; // Check the input value from pin if it was turned on and pass the resulting value to blue
  orange = PIND & B00010000; // Check the input value from pin if it was turned on and pass the resulting value to orange
}