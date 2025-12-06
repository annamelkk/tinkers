 // pin mapping

const int data_pin  = 2;   // SER
const int latch_pin = 3;   // RCLK
const int clock_pin = 4;   // SRCLK
int digit_pins[4] = {5, 6, 7, 8};
const int BTN_UP    = 9;
const int BTN_DOWN  = 10;
const int BTN_LEFT  = 11;
const int BTN_RIGHT = 12;

// Segment patterns
const uint8_t pattern_top    = 0b11000110; // ABFG ie upper circle
const uint8_t pattern_bottom = 0b00111010; // GEDC ie lower cicle
const uint8_t blank         = 0;

// State
int cursor_digit = 0;
bool bottom = false;

// debuf variable becuase i was having issues with pushbuttons
bool debug = false;

// debounce 
unsigned long last_deb[4] = {0,0,0,0};
bool last_read[4] = {HIGH, HIGH, HIGH, HIGH};
bool btn_state[4] = {HIGH, HIGH, HIGH, HIGH};  // stable debounced state
const int deb = 40;

unsigned long last_mux = 0;
int mux_digit = 0;
const int mux_delay = 100;

int btn_pins[4] = {BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT};



void setup() 
{
  Serial.begin(115200); // for debugging again
  pinMode(data_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  
  // setting up all pins to be used
  for (int i=0; i<4; i++) {
    pinMode(digit_pins[i], OUTPUT);
    digitalWrite(digit_pins[i], LOW);
    pinMode(btn_pins[i], INPUT_PULLUP);
  }
  
  Serial.println("System ready");
}

void writeSegments(uint8_t val) 
{
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, MSBFIRST, val); // using built in shiftOut()
  digitalWrite(latch_pin, HIGH);
}

uint8_t getPattern(int d) 
{
  // debug mode: show which digit is which
  if (debug) {
    // display digit 0=top, 1=top+bottom, 2=bottom, 3=both circles
    if (d == 0) return pattern_top;
    if (d == 1) return pattern_top | pattern_bottom;
    if (d == 2) return pattern_bottom;
    if (d == 3) return pattern_top | pattern_bottom;
  }
  
  if (d == cursor_digit)
    return bottom ? pattern_bottom : pattern_top;
  return blank;
}

void handlePress(int id) 
{
  if (id == 0) {
    bottom = false;
    Serial.println("UP - Top circle");
  }
  else if (id == 1) 
  {
    bottom = true;
    Serial.println("DOWN - Bottom circle");
  }
  else if (id == 2) 
  {
    // move left (decrease digit number)
    cursor_digit = (cursor_digit + 1) % 4;
    Serial.print("LEFT - Digit: ");
    Serial.println(cursor_digit);
  }
  else if (id == 3) 
  {
    // move right (increase digit number)
    cursor_digit = (cursor_digit + 3) % 4;
    Serial.print("RIGHT - Digit: ");
    Serial.println(cursor_digit);
  }
}

void loop() 
{
  // multiplex 
  if (micros() - last_mux >= mux_delay) 
  {
    last_mux = micros();
    
    //turn off current digit
    digitalWrite(digit_pins[mux_digit], LOW);
    
    // move to next digit
    mux_digit = (mux_digit + 1) % 4;
    
    // write pattern and turn on new digit
    writeSegments(getPattern(mux_digit));
    digitalWrite(digit_pins[mux_digit], HIGH);
  }
  
  // button checks 
  for (int i=0; i<4; i++) {
    bool reading = digitalRead(btn_pins[i]);
    
    // if the reading changed, reset the debounce timer
    if (reading != last_read[i]) {
      last_deb[i] = millis();
    }
    
    // if enough time has passed, accept the reading as the new state
    if ((millis() - last_deb[i]) > deb) {
      // only act if the state actually changed
      if (reading != btn_state[i]) {
        btn_state[i] = reading;
        
        // detect falling edge (button press with INPUT_PULLUP)
        if (btn_state[i] == LOW) {
          handlePress(i);
        }
      }
    }
    
    last_read[i] = reading;
  }
}
