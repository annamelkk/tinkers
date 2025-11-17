// common cathode implementation

// defining the arduino pins to be used for the decoder
int minute_ten[4] = {A1, A2, A3, A4};
int minute_digit[4] = {8, 9, 10, 11};
int second_ten[4] = {4, 5, 6, 7};
int second_digit[4] = {0, 1, 2, 3};

volatile uint8_t seconds = -1; // for the sake of syncing with the sumulator timer
volatile uint8_t minutes = 0;
volatile bool flag = false;

// a function for setting each pin as output 
void pin_to_DDR(uint8_t pin)
{
  if (pin <= 7)
    DDRD |= (1 << pin);
  else if (pin >= 8 && pin <= 12)
    DDRB |= (1 << (pin - 8));
  else if (pin >= A1 && pin <= A4)
    DDRC |= (1 << (pin - A1));

}

// fucntion for digits from hw3
void displayDigit(int digit, int *pins) 
{
  // constrain the input to 0–9 to prevent invalid BCD codes
  digit = constrain(digit, 0, 9);

  // using bitwise operator to send each bit to corresponding pin
  for (int i = 0; i < 4; i++) 
  {
    uint8_t bit = (digit >> i) & 0x01;
    port_write(pins[i], bit);
  }
}

// function to set high each port pin
void port_write(uint8_t pin, uint8_t val)
{
  if (pin <= 7)
  {
    if (val)
  		PORTD |= (1 << pin);
    else 
      	PORTD &= ~(1 << pin);
  }
  else if (pin <= 13)
  {
    if (val)
    	PORTB |= (1 << (pin - 8));
    else 
      	PORTB &= ~(1 << (pin - 8));
  }
  else if (pin <= 19)
  {
    if (val)
    	PORTC |= (1 << (pin - 14));
    else 
      	PORTC &= ~(1 << (pin - 14));
  }

}

void setup()
{
  // cleareing the bits for directions and port registers
  DDRB = 0;
  PORTB = 0;
  
  DDRD = 0;
  PORTD = 0;
  
  DDRC = 0;
  PORTC = 0;
  
  // filling in
  for (int i = 0; i < 4; i++)
  {
    pin_to_DDR(minute_ten[i]);
    pin_to_DDR(minute_digit[i]);
    pin_to_DDR(second_ten[i]);
    pin_to_DDR(second_digit[i]);
  }
  
  noInterrupts(); 
  
  // create a PWM signal with one sec....
  
  // clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // enable CTC
  TCCR1B |= (1 << WGM12);
  
  // for 1Hz frequency
  OCR1A = 15624;
  
  // enable timer1 compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  // prescaler = 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  interrupts();
}

void loop() 
{
  // we are going to refresh the screen once per second thanks to the flag
    if (flag) 
    {
        flag = false;

        uint8_t s = seconds;
        uint8_t m = minutes;

        // compute digits
        uint8_t s1 = s % 10;
        uint8_t s10 = s / 10;
        uint8_t m1 = m % 10;
        uint8_t m10 = m / 10;

        // drive outputs
        displayDigit(m10, minute_ten);
        displayDigit(m1,  minute_digit);
        displayDigit(s10, second_ten);
        displayDigit(s1,  second_digit);
    }
}

// the ISR sets the flag to true after each second
ISR(TIMER1_COMPA_vect)
{
  seconds++;
  if (seconds == 59)
  {
    seconds = 0;
    minutes++;
  }
  flag = true; // tell loop that one second has passed
}
