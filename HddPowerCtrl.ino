

#define power_control_pin 2 // D2

void setup() {
  pinMode(power_control_pin, OUTPUT);
  digitalWrite(power_control_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    char ctrl = Serial.read();
    if(ctrl== 'p') digitalWrite(power_control_pin, LOW);
    if(ctrl== 'o') digitalWrite(power_control_pin, HIGH);
  }
}

