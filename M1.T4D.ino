//Pins
volatile int orange = 0; // state changes on something that the program can't predict -- motion from user
volatile int blue = 0; // state changes on something that the program can't predict -- motion from user
volatile int green = 0; // state changes on something that the program can't predict -- motion from user
const int red = PB1;

// Counter & Compare Values
const uint16_t t1_load = 0;
const uint16_t t1_comp = 31250;

// Set up pins and enable the serial monitor to display info.
void setup()
{
  Serial.begin(9600);
  // Set LED pins to output 5V
  DDRB |= (1<< 11);// Setting the pin 11 to output 5V
  DDRB |= (1<<12);// Setting the pin 12 to output 5V
  DDRB |= (1<<13); // Setting the pin 13 to output 5V
  DDRB |= (1<< red); // Setting red led to output
  
  // Reset Timer 1 Control Reg A
  TCCR1A = 0;
  
  // Set prescaler of 256
  TCCR1B |=(1<< CS12);
  TCCR1B &= ~(1<<CS11);
  TCCR1B &= ~(1<<CS10);
  
  //Reset Timer1 and set compare value
  TCNT1 = t1_load;
  OCR1A = t1_comp;
  
  //Enable Timer1 compare interrupt
  TIMSK1 = (1<<OCIE1A);
  
  //Enable global interrupts
  sei();
  
  // Set Signal Pin to be an Input with Pullup
  DDRD &= ~(1<<2); // Clearing bit before assignment
  PORTD |= (1<<2);// Setting the pin 2 as an input
  
  DDRD &= ~(1<<4); // Clearing bit before assignment
  PORTD |= (1<<4); // Setting the pin 4 as an input
  
  
  DDRD &= ~(1<<7); // Clearing bit before assignment
  PORTD |= (1<<7); // Setting the pin 7 as an input
  
  // opening all the ports for interrupts
  PCICR |= 0b00000111; 
  PCMSK2 |= 0b10010100; // enabling pins 2, 4 and 7 for interrupts
}

void loop()
{
  digitalWrite(12, blue);
  digitalWrite(11, orange);
  digitalWrite(13, green);
  
  // when the value of 4 is returned this means the blue led has been powered on
  if(blue == 4){
    Serial.println("Left Sensor Activated"); // print to console
  }
  // when the value of 16 is returned this means the orange led has been powered on
  if(orange == 16){
    Serial.println("Centre Sensor Activated"); // print to console
  }
  // when the value of 256 is returned this means the green led has been powered on
  if(green == 128){
    Serial.println("Right Sensor Activated"); // print to console
  }
}

// Setting up Interrupt Service Routine (ISR) for the PCINT2 interrupt vector
ISR(PCINT2_vect) {
  blue = PIND & B00000100; // Check the input value from pin if it was turned on and pass the resulting value to blue
  orange = PIND & B00010000; // Check the input value from pin if it was turned on and pass the resulting value to orange
  green = PIND & B10000000; // Check the input value from pin if it was turned on and pass the resulting value to green
}

// Setting up Interrupt Service Routine (ISR) for the TIMER1_COMPA interrupt vector
ISR(TIMER1_COMPA_vect) {
  TCNT1 = t1_load;
  PORTB ^=(1<<red);
}