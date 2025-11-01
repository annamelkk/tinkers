const uint8_t YELLOW = 0; //8
const uint8_t GREEN = 1; //9

volatile uint8_t seconds = 0;
volatile bool pb0State = false; // start with false
volatile bool pb1State = false;

void setup()
{
  DDRB |= (1 << YELLOW) | (1 << GREEN); // set as output
  PORTB &= ~((1 << YELLOW) | (1 << GREEN)); //turn off
  noInterrupts();
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  TCCR1B |= (1 << WGM12); // CTC mode
  
  OCR1A = 15624; // 1Hz 
  
  TIMSK1 |= (1 << OCIE1A); // enable timer1 compare inter
  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
  
  interrupts();
}



void loop()
{
  delay(10);
}


ISR(TIMER1_COMPA_vect)
{
  // toggling yello
  pb0State = !pb0State;
  if (pb0State) PORTB |= (1 << YELLOW);
  else PORTB &= ~(1 << YELLOW);

  seconds++;
  if (seconds >= 60)
  {
    // toggling green
    pb1State = !pb1State;
    if (pb1State) PORTB |= (1 << GREEN);
    else PORTB &= ~(1 << GREEN);
    seconds = 0;
  }
  
}
