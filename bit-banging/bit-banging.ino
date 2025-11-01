volatile int duty = 0; // PWM duty cycle
volatile int counter = 0;


ISR(TIMER1_COMPA_vect) {
  counter++;
  if (counter >= 256) counter = 0; // reset counter
  if (counter < duty)
    PORTB |= (1 << PB0); // turn ON
  else
    PORTB &= ~(1 << PB0); // OFF
}

ISR(ADC_vect) {
  unsigned int temp = ADCL;
  temp |= (ADCH << 8); // combine high and low bytes

  duty = 255 - (temp / 4); // map 0-1023 to 255-0

  ADCSRA |= (1 << ADSC); // start next conversion
}


void setup()
{
  DDRB |= (1 << PB0); // set LED as output
  pinMode(A0, INPUT);
  
  
  noInterrupts();
  //timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  OCR1A = 62;
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS11); // prc = 8
  TIMSK1 |= (1 << OCIE1A); // timer1 compare interr enabling
  //adc
  ADMUX = (1 << REFS0); // Avcc as ref
  ADCSRA |= (1 << ADEN);  // enable ADC
  ADCSRA |= (1 << ADIE);  // enable ADC interrupt
  ADCSRA |= (1 << ADSC);  // start first conversion

  
  interrupts();
}

void loop() {}
