// Arduino 1
const int BTN1 = 2;
const int BTN2 = 3;
const int TX   = 1;

void setup() {

  DDRD &= ~((1 << BTN1) | (1 << BTN2));  // set as input
  PORTD |= (1 << BTN1) | (1 << BTN2); // pull-ups

  DDRD |= (1 << TX); // add tx as output
    
  Serial.begin(9600);
}

void loop() {  
  if (!(PIND & (1 << BTN1))) 
  {
    Serial.println('R'); // send 'R'
    delay(200); // debounce
  }
  else if (!(PIND & (1 << BTN2)))
  {
    Serial.println('G'); // send 'G'
    delay(200); // debounce
  }
}
