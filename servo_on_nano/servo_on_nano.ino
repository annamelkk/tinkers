#include <Servo.h>

#define servo_pin  3
#define x_pin A0
#define y_pin A1
#define SW_pin 2

Servo yo_serve;

void setup() {
    Serial.begin(9600);
    pinMode(SW_pin, INPUT_PULLUP);
    yo_serve.attach(servo_pin, 500, 2400); // attach with standard pulse widths
}

void loop() {

  int x = map(analogRead(x_pin), 0, 1023, -507, 507);
  int y = map(analogRead(y_pin), 0, 1023, -507, 507);

  bool pressed = (digitalRead(SW_pin) == LOW);

  Serial.print("X: "); Serial.print(x);
  Serial.print(" | Y: "); Serial.print(y);
  Serial.print(" | Button: "); Serial.println(pressed ? "PRESSED" : "released");

  if (x > 20)
    servo_kd(0);  // center
  else if (x < -20)
    servo_kd(180); // left
  else 
    servo_kd(90);   // right

  delay(15);
}

void servo_kd(int k) { yo_serve.write(k); } // 0-90 degrees
