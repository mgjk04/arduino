int TRIG_PIN = 13;
int ECHO_PIN = 12;
int MOTOR_PIN1 = 6; //left
int MOTOR_PIN2 = 5; //right
int SERVO_PIN = 9;
int SECOND_MS = 1000;
float SPEED_OF_SOUND = 0.0345;
bool IS_REVERSE = false;


float calculate_dist(int, int, float);
void toggle_reverse_state();
void motor_forward(int, int);
void motor_reverse(int, int);
void motor_stop(int, int);

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
  Serial.println(IS_REVERSE);
  if (2 < dist_cm && dist_cm < 30 && !IS_REVERSE) {
    motor_stop(MOTOR_PIN1, MOTOR_PIN2);
    //do something
    delay(SECOND_MS);
    toggle_reverse_state();
    motor_reverse(MOTOR_PIN1, MOTOR_PIN2);
    delay(SECOND_MS / 10);
  } 
  if(IS_REVERSE) {
    motor_reverse(MOTOR_PIN1, MOTOR_PIN2);
  } else {
    motor_forward(MOTOR_PIN1, MOTOR_PIN2);
  }
  delay(SECOND_MS / 100);
}

float calculate_dist(int trig_pin, int echo_pin, float speed_of_sound) {
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  int microsecs = pulseIn(echo_pin, HIGH);
  float dist_cm = microsecs * speed_of_sound / 2;
  return dist_cm;
}

//reverse
void toggle_reverse_state(){
  IS_REVERSE = true;
}

void motor_reverse(int motor_left_pin, int motor_right_pin) {
  digitalWrite(motor_left_pin, HIGH);
  digitalWrite(motor_right_pin, LOW);
}

void motor_forward(int motor_left_pin, int motor_right_pin) {
  digitalWrite(motor_left_pin, LOW);
  digitalWrite(motor_right_pin, HIGH);
}

void motor_stop(int motor_left_pin, int motor_right_pin) {
  digitalWrite(motor_left_pin, LOW);
  digitalWrite(motor_right_pin, LOW);
}