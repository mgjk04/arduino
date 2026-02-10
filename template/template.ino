int TRIG_PIN = 13;
int ECHO_PIN = 12;
int MOTOR_PIN1 = 6;
int MOTOR_PIN2 = 5;
float SPEED_OF_SOUND = 0.0345;

float calculate_dist(int trig_pin, int echo_pin, int speed_of_sound) {
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  int microsecs = pulseIn(echo_pin, HIGH);
  float dist_cm = microsecs * speed_of_sound / 2;
  return dist_cm;
}

void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  Serial.println("setup complete!"); //Debug IO statement
}

void loop() {
  Serial.println("loop!"); // Debug IO statement
  int dist_cm = calculate_dist(TRIG_PIN, ECHO_PIN, SPEED_OF_SOUND);
  Serial.println(dist_cm);
  if (dist_cm < 30) {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
  } else {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, HIGH);
  }
  delay(10);
}