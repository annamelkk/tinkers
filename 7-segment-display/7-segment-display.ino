// common cathode implementation

// defining the arduino pins to be used for the decoder
const int bcdPins[4] = {2, 3, 4, 5};

// potentiometer analog pin
const int potPin = A0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(bcdPins[i], OUTPUT);
  }
  pinMode(potPin, INPUT);
}

void loop() {
  int segmentVal = analogRead(potPin);  // 0–1023

  // clamping to max 999 
  if (segmentVal > 999) segmentVal = 999;

  // divide by 100 to get a digit 0–9
  int digit = segmentVal / 100;

  // display
  displayDigit(digit);

  delay(100);  // delay for stability
}

void displayDigit(int digit) {
  // Constrain the input to 0–9 to prevent invalid BCD codes
  digit = constrain(digit, 0, 9);

  // using bitwise operator to send each bit to corresponding pin
  for (int i = 0; i < 4; i++) {
    digitalWrite(bcdPins[i], (digit >> i) & 0x01);
  }
}

