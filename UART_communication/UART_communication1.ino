// Arduino 2

const int RED = 4;
const int GREEN = 5;

void setup() {
  DDRD |= (1 << RED) | (1 << GREEN); // leds as outputs

  PORTD &= ~((1 << RED) | (1 << GREEN)); // turn off

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    
    // received var as whatever is read
    char received = Serial.read();
    
    // skip newlines and carriage return
    if (received == '\n' || received == '\r') return;
    Serial.print("Received: "); 
    Serial.println(received);
    
    if (received == 'R') {
      PORTD |=  (1 << RED);    // red on
      PORTD &= ~(1 << GREEN);  // green off
    }
    else if (received == 'G') {
      PORTD |=  (1 << GREEN);  // green on
      PORTD &= ~(1 << RED);    // red off
    }
  }
}
